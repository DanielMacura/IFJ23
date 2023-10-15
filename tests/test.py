import os
import subprocess
import sys
import xml.etree.ElementTree as ET

def run_tests(program):
    testsuite = ET.Element("testsuite", name="Test Suite", tests="0", failures="0", errors="0", skipped="0")
    for path, subdirs, files in os.walk("."):
        for name in files:
            if name.endswith(".in"):
                test_name = name[:-3]
                classname = path.replace('/', '.')[2:]
                testcase = ET.Element("testcase", name=test_name, classname=classname, time="0")
                expected_rc = int(open(os.path.join(path, test_name + ".rc"), "r").read())
                actual_rc = subprocess.call([program, "-t"], stdin=open(os.path.join(path, name)), stdout=open(os.path.join(path, test_name + ".temp"), "w"))
                if actual_rc != expected_rc:
                    failure = ET.Element("failure", message="Return code does not match expected value", type="AssertionError", text=f"Expected return code {expected_rc}, but got {actual_rc}")
                    testcase.append(failure)
                    testsuite.set("failures", str(int(testsuite.get("failures")) + 1))
                elif expected_rc == 0:
                    diff_rc = subprocess.call(["diff", os.path.join(path, test_name + ".temp"), os.path.join(path, test_name + ".out")])
                    if diff_rc != 0:
                        failure = ET.Element("failure", message="Output does not match expected value", type="AssertionError", text="Output does not match expected value")
                        testcase.append(failure)
                        testsuite.set("failures", str(int(testsuite.get("failures")) + 1))
                if len(testcase.findall("failure")) == 0:
                    testcase.set("time", "0.001")
                testsuite.set("tests", str(int(testsuite.get("tests")) + 1))
                testsuite.append(testcase)
                os.remove(os.path.join(path, test_name + ".temp"))
    with open("test-results.xml", "w") as f:
        f.write(ET.tostring(testsuite, encoding="unicode", method="xml"))
    print(f"Tests passed: {int(testsuite.get('tests')) - int(testsuite.get('failures'))}/{testsuite.get('tests')}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: python3 test_runner.py <program to run>")
        exit(1)
    program = sys.argv[1]
    run_tests(program)