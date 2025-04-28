import subprocess
import os


def run_single_test(num , save=True , printOut=False):
    exe_path = os.path.join(os.getcwd(), "pa3_test.exe")
    output_file = os.path.join("output", f"output_{num}.txt")

    proc = subprocess.run([exe_path] , input=f"{num}\n" , capture_output=True , text=True)
    with open(output_file , 'r') as f:
        expected = f.read()
    
    if printOut:
        out_list = proc.stdout.split('\n')
        exp_list = expected.split('\n')

        if (len(out_list) != len(exp_list)):
            print("Warning, not equal length")

        try:
            for i , line in enumerate(exp_list):
                if (line != out_list[i]):
                    print(f"At line {i} , expected:\n{line}\nactual:\n{out_list[i]}")
        
        except IndexError:
            print(f"Expected: {expected}")
            print(f"Actual: {proc.stdout}")
            print("expected and actual at not at equal length.")
        
        except Exception as e:
            print(f"Exception : {e}")

    AreEqual = proc.stdout == expected
    print(f"Testcase {num} Are equal: {AreEqual}")

    if save:
        os.makedirs(os.path.abspath("./Myoutput"), exist_ok=True)
        if not AreEqual:
            with open(f"./Myoutput/ActualOut{num}.txt" , 'w') as f:
                f.write(proc.stdout)

# testcase 1 - 8 passed

def test_all():
    for i in range(1 , 30):
        run_single_test(i , save=True , printOut=False)

test_all()


