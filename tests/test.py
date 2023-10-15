#write a program that iterates over all of the sub folders in the current directory and for each, runs the file in provided in the arguments for each input file in the folder
#usage: python3 test.py <program to run>
import os
import sys
import subprocess

def main():
    #number of tests
    num_tests = 0
    #number of tests passed
    num_passed = 0
    if len(sys.argv) != 2:
        print("usage: python3 test.py <program to run>")
        exit(1)
    program = sys.argv[1]
    #iterate over all subfolders and print them
    for path, subdirs, files in os.walk("."):
        for name in files:
            #for each file ending in .in, run the program with the file as input and chcek if the output equals the .out file
            if name.endswith(".in"):
                #increment the number of tests
                num_tests += 1
                #if the files are the same, increment the number of tests passed
                expected_rc = int(open(os.path.join(path, name[:-3] + ".rc"), "r").read())
                actual_rc = subprocess.call([program, "-t"], stdin=open(os.path.join(path, name)), stdout=open(os.path.join(path, name[:-3] + ".temp"), "w"))
                if actual_rc != expected_rc:
                    print("Test " + name[:-3] + " failed with return code " + str(actual_rc) + ". Expected return code " + str(expected_rc))
                    continue
            
                if expected_rc == 0:
                    if subprocess.call(["diff", os.path.join(path, name[:-3] + ".temp"), os.path.join(path, name[:-3] + ".out")]) != 0:
                        print("Test " + name[:-3] + " failed")
                        continue
                        
                num_passed += 1

                #remove the temp file
                os.system("rm " + os.path.join(path, name[:-3] + ".temp"))
                #print a newline
    #print the number of tests passed and the number of tests
    print("Tests passed: " + str(num_passed) + "/" + str(num_tests))



main()