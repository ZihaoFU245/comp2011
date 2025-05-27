"""
Runs all testcases, compares the outputs with the expected outputs, and produces diff files.

The `.diff` output file can be open in any text editor. The `.html` output file can be open in any web browser.

You can edit the global variables below to change some of the behaviors.
"""

from asyncio import BoundedSemaphore, TaskGroup, gather, run, timeout, to_thread
from asyncio.subprocess import PIPE, create_subprocess_exec
from dataclasses import dataclass
from difflib import HtmlDiff, unified_diff
from itertools import chain
from logging import INFO, basicConfig, debug, error, info, warning
from os import cpu_count, listdir
from pathlib import Path, PurePath
from re import compile as re_compile
from textwrap import indent
from typing import Collection, Sequence

_THIS_FILENAME = PurePath(__file__).name
_LINE_TERMINATOR = "\n"
_DIFF_OUTPUT_FILE = Path(f"{_THIS_FILENAME}.diff")
_DIFF_HTML_OUTPUT_FILE = Path(f"{_THIS_FILENAME}.html")
_TESTCASE_DIRECTORY = Path("testcase/")
_INPUT_TESTCASE_NAME_FORMAT = re_compile(r"^input(\d*)\.txt$")
_OUTPUT_TESTCASE_NAME_FORMAT = R"output%s.txt"
_RUN_TESTCASE_SEMAPHORE = BoundedSemaphore(cpu_count() or 4)
_RUN_TESTCASE_TIMEOUT = 10
_DIFF_CONTEXT_LINES = 3
_DIFF_HTML_TAB_SIZE = 4
_DIFF_HTML_WRAP_COLUMN = 70
_DIFF_HTML_TESTCASE_SEPARATOR = R"""

    <hr/>
"""
_DIFF_HTML_NO_DIFFERENCES_FOUND = R"&nbsp;No Differences Found&nbsp;"
_DIFF_HTML_FORMAT = R"""<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
          "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html>

<head>
    <meta http-equiv="Content-Type"
          content="text/html; charset=utf-8" />
    <title></title>
    <style type="text/css">
        table.diff {font-family:Courier; border:medium;}
        .diff_header {background-color:#e0e0e0}
        td.diff_header {text-align:right}
        .diff_next {background-color:#c0c0c0}
        .diff_add {background-color:#aaffaa}
        .diff_chg {background-color:#ffff77}
        .diff_sub {background-color:#ffaaaa}
    </style>
</head>

<body>
    <table class="diff" summary="Legends">
        <tr> <th colspan="2"> Legends </th> </tr>
        <tr> <td> <table border="" summary="Colors">
                      <tr><th> Colors </th> </tr>
                      <tr><td class="diff_add">&nbsp;Added&nbsp;</td></tr>
                      <tr><td class="diff_chg">Changed</td> </tr>
                      <tr><td class="diff_sub">Deleted</td> </tr>
                  </table></td>
             <td> <table border="" summary="Links">
                      <tr><th colspan="2"> Links </th> </tr>
                      <tr><td>(f)irst change</td> </tr>
                      <tr><td>(n)ext change</td> </tr>
                      <tr><td>(t)op</td> </tr>
                  </table></td> </tr>
    </table>

    <hr/>
%s
</body>

</html>
"""


@dataclass(frozen=True, kw_only=True, slots=True)
class TestcaseResult:
    output_path: Path
    expected_output: Sequence[str]
    output: Sequence[str]
    error: Sequence[str]
    exit_code: int | str

    def __post_init__(self) -> None:
        object.__setattr__(self, "expected_output", tuple(self.expected_output))
        object.__setattr__(self, "output", tuple(self.output))
        object.__setattr__(self, "error", tuple(self.error))


@dataclass(frozen=True, kw_only=True, slots=True)
class RawTestcaseResult:
    output_path: Path
    expected_output: bytes
    output: bytes
    error: bytes
    exit_code: int | None

    def process(self) -> TestcaseResult:
        def process_output(output: bytes):
            return tuple(
                f"{line}{_LINE_TERMINATOR}"
                for line in output.decode(errors="replace").splitlines()
            )

        return TestcaseResult(
            output_path=self.output_path,
            expected_output=process_output(self.expected_output),
            output=process_output(self.output),
            error=process_output(self.error),
            exit_code="timeout" if self.exit_code is None else self.exit_code,
        )


async def run_testcase(
    prog_path: Path, input_path: Path, output_path: Path
) -> RawTestcaseResult:
    stdout, stderr, exit_code = b"", b"", None

    info(f"running: {input_path} -> {output_path}")
    try:
        async with TaskGroup() as tg:
            input_bytes = tg.create_task(to_thread(input_path.read_bytes))
            output_bytes = tg.create_task(to_thread(output_path.read_bytes))
            async with _RUN_TESTCASE_SEMAPHORE:
                proc = await create_subprocess_exec(
                    prog_path, stdin=PIPE, stdout=PIPE, stderr=PIPE
                )
                try:
                    async with timeout(_RUN_TESTCASE_TIMEOUT):
                        stdout, stderr = await proc.communicate(await input_bytes)
                        exit_code = await proc.wait()
                except TimeoutError as exc:
                    debug("", exc_info=exc)
                    warning(f"timeout: {input_path} -> {output_path}")
                finally:
                    try:
                        proc.kill()
                    except ProcessLookupError as exc:
                        debug("", exc_info=exc)
            output_bytes = await output_bytes
    except Exception:
        error(f"failure: {input_path} -> {output_path}")
        raise
    info(f"success: {input_path} -> {output_path}")

    return RawTestcaseResult(
        output_path=output_path,
        expected_output=output_bytes,
        output=stdout,
        error=stderr,
        exit_code=exit_code,
    )


@dataclass(frozen=True, kw_only=True, slots=True)
class UnifiedDiff:
    diff: str
    error: str
    exit_code: int | str

    def format(self) -> str:
        return f"""{self.diff}
# @@ stderr @@
{indent(self.error, '# ', lambda _:True) or '#'}
# @@ exit code @@
# {self.exit_code}"""


def result_unified_diff(result: TestcaseResult) -> UnifiedDiff:
    from_file = result.output_path.name
    to_file = f"actual_{from_file}"

    diff = "".join(
        unified_diff(
            result.expected_output,
            result.output,
            fromfile=from_file,
            tofile=to_file,
            n=_DIFF_CONTEXT_LINES,
            lineterm=_LINE_TERMINATOR,
        )
    ).rstrip()
    if not diff:
        diff = f"""--- {from_file}
+++ {to_file}
# (no differences found)"""

    return UnifiedDiff(
        diff=diff, error="".join(result.error), exit_code=result.exit_code
    )


def result_html_diff(result: TestcaseResult) -> str:
    from_file = result.output_path.name
    to_file = f"actual_{from_file}"

    html_diff = HtmlDiff(tabsize=_DIFF_HTML_TAB_SIZE, wrapcolumn=_DIFF_HTML_WRAP_COLUMN)
    diff_html = html_diff.make_table(
        result.expected_output,
        result.output,
        fromdesc=from_file,
        todesc=to_file,
        context=True,
        numlines=_DIFF_CONTEXT_LINES,
    )
    error_html = html_diff.make_table(
        result.error,
        (),
        fromdesc=f"{to_file} stderr",
        todesc="(you should not print to stderr)",
        context=True,
        numlines=_DIFF_CONTEXT_LINES,
    ).replace(_DIFF_HTML_NO_DIFFERENCES_FOUND, "&nbsp;")
    exit_code_html = html_diff.make_table(
        (str(result.exit_code),),
        (),
        fromdesc=f"{to_file} exit code",
        todesc="(you should always return 0)",
        context=True,
        numlines=_DIFF_CONTEXT_LINES,
    )

    return f"""{diff_html}{error_html}{exit_code_html}"""


async def run_testcases(prog_path: Path) -> Collection[TestcaseResult]:
    testcase_dir_path = await to_thread(_TESTCASE_DIRECTORY.resolve, strict=True)
    if not await to_thread(testcase_dir_path.is_dir):
        raise NotADirectoryError(testcase_dir_path)

    results = await gather(
        *(
            run_testcase(
                prog_path,
                testcase_dir_path / input_name,
                testcase_dir_path
                / (_OUTPUT_TESTCASE_NAME_FORMAT % input_name_match[1]),
            )
            for input_name in await to_thread(listdir, testcase_dir_path)
            if (input_name_match := _INPUT_TESTCASE_NAME_FORMAT.search(input_name))
        )
    )
    results = tuple(result.process() for result in results)

    return results


async def main() -> None:
    basicConfig(level=INFO)

    prog_path = Path(input("Program path? "))
    prog_path = await to_thread(prog_path.resolve)

    results = await run_testcases(prog_path)

    def print_diff():
        diff = _LINE_TERMINATOR.join(
            result_unified_diff(result).format() for result in results
        )
        info(diff)

    async def write_diff():
        diff = _LINE_TERMINATOR.join(
            chain((result_unified_diff(result).format() for result in results), ("",))
        )
        await to_thread(_DIFF_OUTPUT_FILE.write_text, diff, encoding="UTF-8")

    async def write_diff_html():
        diff_html = _DIFF_HTML_FORMAT % _DIFF_HTML_TESTCASE_SEPARATOR.join(
            result_html_diff(r) for r in results
        )
        await to_thread(_DIFF_HTML_OUTPUT_FILE.write_text, diff_html, encoding="UTF-8")

    async with TaskGroup() as tg:
        tg.create_task(write_diff())
        tg.create_task(write_diff_html())
        print_diff()

    info(
        f"""diff saved to: {_DIFF_OUTPUT_FILE}
diff HTML saved to: {_DIFF_HTML_OUTPUT_FILE}"""
    )


if __name__ == "__main__":
    run(main())
