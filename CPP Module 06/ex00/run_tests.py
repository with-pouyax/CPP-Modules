#!/usr/bin/env python3

import subprocess
import re
import os
from colorama import Fore, Style, init

# Initialize colorama for cross-platform colored output
init(autoreset=True)

def run_converter(argument):
    """Run the convert program with the given argument and return the output"""
    try:
        # Run the convert program
        result = subprocess.run(['./convert', argument], 
                              capture_output=True, 
                              text=True, 
                              timeout=5)
        return result.stdout.strip()
    except subprocess.TimeoutExpired:
        return "Timeout"
    except Exception as e:
        return f"Error: {str(e)}"

def parse_test_cases(filename):
    """Parse test cases from the markdown file with expected outputs"""
    test_cases = []
    
    with open(filename, 'r') as f:
        content = f.read()
    
    # Split content by code blocks
    code_blocks = re.findall(r'```bash\n(.*?)\n```', content, re.DOTALL)
    
    for block in code_blocks:
        lines = block.strip().split('\n')
        i = 0
        while i < len(lines):
            line = lines[i].strip()
            if line.startswith('./convert '):
                # Extract argument
                argument = line.replace('./convert ', '')
                expected_output = []
                
                # Get expected output lines
                i += 1
                while i < len(lines) and not lines[i].strip().startswith('./convert '):
                    output_line = lines[i].strip()
                    if output_line:  # Skip empty lines
                        expected_output.append(output_line)
                    i += 1
                
                if expected_output:
                    test_cases.append({
                        'argument': argument,
                        'expected': '\n'.join(expected_output)
                    })
                continue
            i += 1
    
    return test_cases

def normalize_output(output):
    """Normalize output for comparison by removing extra whitespace"""
    return '\n'.join(line.strip() for line in output.split('\n') if line.strip())

def compare_outputs(actual, expected):
    """Compare actual and expected outputs"""
    actual_norm = normalize_output(actual)
    expected_norm = normalize_output(expected)
    return actual_norm == expected_norm

def format_output(test_case, actual_output, passed):
    """Format the test case output in a nice visual way with pass/fail status"""
    argument = test_case['argument']
    expected_output = test_case['expected']
    
    # Status indicator
    status_icon = f"{Fore.GREEN}✅ PASS" if passed else f"{Fore.RED}❌ FAIL"
    
    print(f"\n{Fore.CYAN}{'='*60}")
    print(f"{Fore.YELLOW}Input: {Style.BRIGHT}{argument} {status_icon}")
    print(f"{Fore.CYAN}{'='*60}")
    
    # Show actual output
    print(f"{Fore.WHITE}{Style.BRIGHT}Actual Output:")
    if actual_output.startswith("Invalid"):
        print(f"{Fore.RED}{actual_output}")
    elif actual_output.startswith("Error") or actual_output == "Timeout":
        print(f"{Fore.RED}{actual_output}")
    else:
        lines = actual_output.split('\n')
        for line in lines:
            if line.strip():
                if 'char:' in line:
                    print(f"{Fore.GREEN}🔤 {line}")
                elif 'int:' in line:
                    print(f"{Fore.BLUE}🔢 {line}")
                elif 'float:' in line:
                    print(f"{Fore.MAGENTA}🔸 {line}")
                elif 'double:' in line:
                    print(f"{Fore.WHITE}🔹 {line}")
                else:
                    print(f"{Fore.WHITE}{line}")
    
    # Show expected output if test failed
    if not passed:
        print(f"\n{Fore.YELLOW}{Style.BRIGHT}Expected Output:")
        lines = expected_output.split('\n')
        for line in lines:
            if line.strip():
                if 'char:' in line:
                    print(f"{Fore.GREEN}🔤 {line}")
                elif 'int:' in line:
                    print(f"{Fore.BLUE}🔢 {line}")
                elif 'float:' in line:
                    print(f"{Fore.MAGENTA}🔸 {line}")
                elif 'double:' in line:
                    print(f"{Fore.WHITE}🔹 {line}")
                else:
                    print(f"{Fore.WHITE}{line}")

def main():
    # Check if convert executable exists
    if not os.path.exists('./convert'):
        print(f"{Fore.RED}Error: ./convert executable not found!")
        print("Please make sure you're in the correct directory and the program is compiled.")
        return
    
    # Parse test cases from markdown file
    try:
        test_cases = parse_test_cases('cases.md')
    except FileNotFoundError:
        print(f"{Fore.RED}Error: cases.md file not found!")
        return
    
    print(f"{Fore.GREEN}{Style.BRIGHT}🚀 ScalarConverter Test Runner")
    print(f"{Fore.WHITE}Running {len(test_cases)} test cases...\n")
    
    passed_count = 0
    failed_count = 0
    
    # Run each test case
    for i, test_case in enumerate(test_cases, 1):
        print(f"{Fore.WHITE}{Style.DIM}[{i}/{len(test_cases)}]", end="")
        actual_output = run_converter(test_case['argument'])
        passed = compare_outputs(actual_output, test_case['expected'])
        
        if passed:
            passed_count += 1
        else:
            failed_count += 1
            
        format_output(test_case, actual_output, passed)
    
    # Summary
    print(f"\n{Fore.CYAN}{'='*60}")
    print(f"{Fore.GREEN}{Style.BRIGHT}📊 Test Results Summary:")
    print(f"{Fore.GREEN}✅ Passed: {passed_count}")
    print(f"{Fore.RED}❌ Failed: {failed_count}")
    print(f"{Fore.WHITE}📈 Success Rate: {(passed_count / len(test_cases) * 100):.1f}%")
    
    if failed_count == 0:
        print(f"{Fore.GREEN}{Style.BRIGHT}🎉 All tests passed!")
    else:
        print(f"{Fore.YELLOW}⚠️  Some tests failed. Please review the failed cases above.")
    
    print(f"{Fore.CYAN}{'='*60}")

if __name__ == "__main__":
    main() 