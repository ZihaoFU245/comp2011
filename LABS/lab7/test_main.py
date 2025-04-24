import subprocess
from pathlib import Path
import pytest
import logging

# Log to file for debugging test runs
logging.basicConfig(filename='test_main.log', level=logging.INFO, filemode='w', format='%(message)s')
logger = logging.getLogger(__name__)

# Directory containing test cases
TESTCASE_DIR = Path(__file__).parent / "testcase"
# Path to the executable under test
PROGRAM = Path(__file__).parent / "main.exe"

# Collect all input files
input_files = sorted(TESTCASE_DIR.glob("input*.txt"))

@pytest.mark.parametrize("input_path", input_files)
def test_main_matches_expected(input_path):
    # Initialize result and expected
    result = subprocess.run(
        [str(PROGRAM)],
        stdin=input_path.open('r', encoding='utf-8'),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        check=False
    )
    # Determine expected output path
    expected_path = input_path.with_name(input_path.name.replace("input", "output"))
    assert expected_path.exists(), f"Missing expected output for {input_path.name}"

    # Read actual and expected
    output = result.stdout
    expected = expected_path.read_text(encoding='utf-8')
    # Assertions wrapped to log only on failure
    try:
        assert result.returncode == 0, f"Exit code {result.returncode}"
        assert output == expected, "Output mismatch"
    except AssertionError as e:
        logger.error(f"=== Test {input_path.name} FAILED ===")
        logger.error(f"Return code: {result.returncode}")
        logger.error("Stdout:\n" + result.stdout)
        logger.error("Stderr:\n" + result.stderr)
        raise


