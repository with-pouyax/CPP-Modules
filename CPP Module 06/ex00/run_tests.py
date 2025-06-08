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
    """Parse test cases from the markdown file"""
    test_cases = []
    
    with open(filename, 'r') as f:
        content = f.read()
    
    # Find all ./convert commands in the markdown
    pattern = r'./convert (.+?)(?=\n)'
    matches = re.findall(pattern, content)
    
    for match in matches:
        # Clean up the argument (remove any trailing characters)
        argument = match.strip()
        test_cases.append(argument)
    
    return test_cases

def format_output(argument, output):
    """Format the test case output in a nice visual way"""
    print(f"\n{Fore.CYAN}{'='*60}")
    print(f"{Fore.YELLOW}Input: {Style.BRIGHT}{argument}")
    print(f"{Fore.CYAN}{'='*60}")
    
    if output.startswith("Invalid"):
        print(f"{Fore.RED}{output}")
    elif output.startswith("Error") or output == "Timeout":
        print(f"{Fore.RED}{output}")
    else:
        lines = output.split('\n')
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
    
    # Run each test case
    for i, test_case in enumerate(test_cases, 1):
        print(f"{Fore.WHITE}{Style.DIM}[{i}/{len(test_cases)}]", end="")
        output = run_converter(test_case)
        format_output(test_case, output)
    
    print(f"\n{Fore.GREEN}{Style.BRIGHT}✅ All test cases completed!")
    print(f"{Fore.CYAN}{'='*60}")

if __name__ == "__main__":
    main() 