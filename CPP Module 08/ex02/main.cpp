#include <iostream>
#include <list>
#include "MutantStack.hpp"

// =============================================================================
// COLOR CONSTANTS (ANSI Escape Codes)
// =============================================================================

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string BOLD = "\033[1m";

// =============================================================================
// TEST FUNCTIONS
// =============================================================================

void testBasicOperations()
{
    std::cout << "\n" << BOLD << BLUE << "🔧 TEST 1: Basic Stack Operations" << RESET << std::endl;
    std::cout << CYAN << "=====================================" << RESET << std::endl;
    
    MutantStack<int> mstack; // create a stack of integers
    
    // Push some elements
    std::cout << "Pushing elements: 5, 17" << std::endl;
    mstack.push(5);
    mstack.push(17);
    
    // Test top and pop
    std::cout << "Top element: " << mstack.top() << std::endl; //most recent element
    mstack.pop(); // remove from the top of the stack
    std::cout << "Size after pop: " << mstack.size() << std::endl;
    
    // Push more elements
    std::cout << "Pushing more elements: 3, 5, 737, 0" << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "Final stack size: " << mstack.size() << std::endl;
}

void testIteration()
{
    std::cout << "\n" << BOLD << GREEN << "🔄 TEST 2: Iterator Operations" << RESET << std::endl;
    std::cout << GREEN << "=====================================" << RESET << std::endl;
    
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "Stack elements (using iterator):" << std::endl;
    MutantStack<int>::iterator it = mstack.begin(); // save the beginning of the stack to it
    MutantStack<int>::iterator ite = mstack.end(); // save the end of the stack to ite
    
    // Test iterator increment/decrement
    std::cout << "Testing iterator operations:" << std::endl;
    std::cout << "  Starting at: " << *it << std::endl;
    ++it; // increment the iterator to the next element
    std::cout << "  After ++it: " << *it << std::endl;
    --it; // decrement the iterator back to the previous element
    std::cout << "  After --it: " << *it << std::endl;
    
    std::cout << "\nIterating through all elements:" << std::endl;
    int count = 0;
    while (it != ite)
    {
        std::cout << "  Element " << count++ << ": " << *it << std::endl;
        ++it;
    }
    
    std::cout << "\n✅ Iteration completed! Total elements: " << count << std::endl;
    std::cout << "✅ This proves MutantStack is iterable!" << std::endl;
}

void testStringStack()
{
    std::cout << "\n" << BOLD << YELLOW << "📝 TEST 3: String Stack" << RESET << std::endl;
    std::cout << YELLOW << "=====================================" << RESET << std::endl;
    
    MutantStack<std::string> stringStack;
    
    std::cout << "Pushing strings: Hello, World, C++, Module, 08" << std::endl;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("C++");
    stringStack.push("Module");
    stringStack.push("08");
    
    std::cout << "String stack size: " << stringStack.size() << std::endl;
    std::cout << "Top string: " << stringStack.top() << std::endl;
    
    std::cout << "All strings (using iterator):" << std::endl;
    MutantStack<std::string>::iterator str_it = stringStack.begin();
    MutantStack<std::string>::iterator str_ite = stringStack.end();
    
    while (str_it != str_ite)
    {
        std::cout << "  " << *str_it << std::endl;
        ++str_it;
    }
}

void testEmptyStack()
{
    std::cout << "\n" << BOLD << MAGENTA << "📭 TEST 4: Empty Stack" << RESET << std::endl;
    std::cout << MAGENTA << "=====================================" << RESET << std::endl;
    
    MutantStack<int> emptyStack;
    
    std::cout << "Empty stack size: " << emptyStack.size() << std::endl;
    std::cout << "Is empty? " << (emptyStack.empty() ? "Yes" : "No") << std::endl;

    std::cout << "Trying to iterate through the empty stack:" << std::endl;
    MutantStack<int>::iterator it = emptyStack.begin();
    MutantStack<int>::iterator ite = emptyStack.end();
    
    if (it == ite)
        std::cout << "  ✅ begin() == end() for empty stack (correct behavior)" << std::endl;
    else
        std::cout << "  ❌ begin() != end() for empty stack (unexpected)" << std::endl;
    
    int count = 0;
    while (it != ite)
    {
        std::cout << "  We entered the loop (shouldn't happen for empty stack)" << std::endl;
        std::cout << "  " << *it << std::endl;
        ++it;
        count++;
    }
    std::cout << "  Elements found: " << count << " (should be 0)" << std::endl;
}

void testSingleElementStack()
{
    std::cout << "\n" << BOLD << YELLOW << "🔢 TEST 4.5: Single Element Stack" << RESET << std::endl;
    std::cout << YELLOW << "=====================================" << RESET << std::endl;
    
    MutantStack<int> singleStack;
    singleStack.push(42);
    
    std::cout << "Single element stack size: " << singleStack.size() << std::endl;
    std::cout << "Top element: " << singleStack.top() << std::endl;
    
    std::cout << "Iterating through single element:" << std::endl;
    MutantStack<int>::iterator it = singleStack.begin();
    MutantStack<int>::iterator ite = singleStack.end();
    
    int count = 0;
    while (it != ite)
    {
        std::cout << "  Element " << count++ << ": " << *it << std::endl;
        ++it;
    }
    
    std::cout << "✅ Single element iteration completed!" << std::endl;
}

void testCopyConstructor()
{
    std::cout << "\n" << BOLD << RED << "📋 TEST 5: Copy Constructor" << RESET << std::endl;
    std::cout << RED << "=====================================" << RESET << std::endl;
    
    // Create original stack
    MutantStack<int> original;
    original.push(10);
    original.push(20);
    original.push(30);
    
    std::cout << "Original stack:" << std::endl;
    std::cout << "  Size: " << original.size() << std::endl;
    std::cout << "  Top: " << original.top() << std::endl;
    
    // Create copy
    MutantStack<int> copy(original);
    
    std::cout << "Copied stack:" << std::endl;
    std::cout << "  Size: " << copy.size() << std::endl;
    std::cout << "  Top: " << copy.top() << std::endl;
    
    // Verify they are independent
    original.push(40);
    std::cout << "After pushing 40 to original:" << std::endl;
    std::cout << "  Original top: " << original.top() << std::endl;
    std::cout << "  Copy top: " << copy.top() << std::endl;
}

void testAssignmentOperator()
{
    std::cout << "\n" << BOLD << BLUE << "📝 TEST 6: Assignment Operator" << RESET << std::endl;
    std::cout << BLUE << "=====================================" << RESET << std::endl;
    
    // Create source stack
    MutantStack<int> source; // source stack
    source.push(100);
    source.push(200);
    source.push(300);
    
    std::cout << "Source stack:" << std::endl;
    std::cout << "  Size: " << source.size() << std::endl;
    std::cout << "  Top: " << source.top() << std::endl;
    
    // Create target stack and assign
    MutantStack<int> target; // target stack
    target.push(999);  // This will be overwritten
    
    std::cout << "Target stack before assignment:" << std::endl;
    std::cout << "  Size: " << target.size() << std::endl;
    std::cout << "  Top: " << target.top() << std::endl;
    
    target = source;
    
    std::cout << "Target stack after assignment:" << std::endl;
    std::cout << "  Size: " << target.size() << std::endl;
    std::cout << "  Top: " << target.top() << std::endl;
}

void testStdStackConversion()
{
    std::cout << "\n" << BOLD << CYAN << "🔄 TEST 7: std::stack Conversion" << RESET << std::endl;
    std::cout << CYAN << "=====================================" << RESET << std::endl;
    
    MutantStack<int> mstack;
    mstack.push(1);
    mstack.push(2);
    mstack.push(3);
    
    std::cout << "MutantStack:" << std::endl;
    std::cout << "  Size: " << mstack.size() << std::endl;
    std::cout << "  Top: " << mstack.top() << std::endl;
    
    // Convert to std::stack
    std::stack<int> regularStack(mstack);  // we can do this because MutantStack inherits from std::stack
                                           // we used the copy constructor of std::stack for this
    
    std::cout << "Converted to std::stack:" << std::endl;
    std::cout << "  Size: " << regularStack.size() << std::endl;
    std::cout << "  Top: " << regularStack.top() << std::endl;
}

void testComparisonWithList()
{
    std::cout << "\n" << BOLD << GREEN << "📊 TEST 8: Comparison with std::list" << RESET << std::endl;
    std::cout << GREEN << "=====================================" << RESET << std::endl;
    
    std::cout << "Creating MutantStack with same elements as list..." << std::endl;
    
    // MutantStack version
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "MutantStack elements:" << std::endl;
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    while (it != ite)
    {
        std::cout << "  " << *it << std::endl;
        ++it;
    }
    
    // std::list version
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(17);
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);
    
    std::cout << "std::list elements:" << std::endl;
    std::list<int>::iterator lst_it = lst.begin();
    std::list<int>::iterator lst_ite = lst.end();
    while (lst_it != lst_ite)
    {
        std::cout << "  " << *lst_it << std::endl;
        ++lst_it;
    }
    
    std::cout << GREEN << "✅ Both containers produce the same output!" << RESET << std::endl;
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main()
{
    std::cout << BOLD << MAGENTA << "🚀 MUTANTSTACK TESTING PROGRAM" << RESET << std::endl;
    std::cout << MAGENTA << "================================" << RESET << std::endl;
    std::cout << "Testing all MutantStack functionality..." << std::endl;
    
    // Run all tests
    testBasicOperations();  //push, pop,  size
    testIteration();        //iterator operations
    testStringStack();      //string stack
    testEmptyStack();
    testSingleElementStack();
    testCopyConstructor(); //top
    testAssignmentOperator();
    testStdStackConversion();
    testComparisonWithList();
    
    std::cout << "\n" << BOLD << GREEN << "🎉 ALL TESTS COMPLETED SUCCESSFULLY!" << RESET << std::endl;
    std::cout << GREEN << "=====================================" << RESET << std::endl;
    
    return 0;
} 