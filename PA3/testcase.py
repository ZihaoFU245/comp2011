import subprocess
import os


def run_single_test(num , save=True , printOut=False):
    exe_path = os.path.join(os.getcwd(), "pa3_test.exe")
    output_file = os.path.join("output", f"output_{num}.txt")

    proc = subprocess.run([exe_path] , input=f"{num}\n" , capture_output=True , text=True)
    try:
        with open(output_file , 'r') as f:
            expected = f.read()
    except FileNotFoundError:
        print("expected file not found")
        expected = ""
    
    if printOut:
        print(proc.stdout)

        out_list = proc.stdout.split('\n')
        exp_list = expected.split('\n')

        if (len(out_list) != len(exp_list)):
            print("Warning, not equal length")



    AreEqual = proc.stdout == expected
    print(f"Testcase {num} Are equal: {AreEqual}")

    if save:
        os.makedirs(os.path.abspath("./Myoutput"), exist_ok=True)
        if not AreEqual:
            with open(f"./Myoutput/ActualOut{num}.txt" , 'w') as f:
                f.write(proc.stdout)

# testcase 1 - 8 passed

def test_all():
    for i in range(1 , 29):
        run_single_test(i , save=True , printOut=False)

run_single_test(32 , printOut=True)


