#include <stdexcept>
#include <iostream>
#include <ctime>
#include "FordJohnsonVectorSorter.hpp"
#include "FordJohnsonDequeSorter.hpp"
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc >= 2) // if we have at least 2 arguments (program name and list of positive integers)
    {
        FordJohnsonVectorSorter vectorSorter; // we create a vector sorter object
        FordJohnsonDequeSorter dequeSorter;   // we create a deque sorter object
        try {
            // ___________ PARSING ___________
            std::vector<int> valuesVector; // vector to store the values
            std::deque<int> valuesDeque;   // deque to store the values
            parseArgsToContainers(argc, argv, valuesVector, valuesDeque); // parse the input and store it in our containers
            // _______________________________

            
            // ___________ VECTOR SORT ___________
            std::clock_t startTime = std::clock();
            vectorSorter.performSort(valuesVector); // call performSort method from vectorSorter object with our vector as argument
            std::clock_t endTime = std::clock();
            double vectorElapsed = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000000.0; // calculate the duration of the sort in microseconds
            // _______________________________


            // ___________ DEQUE SORT ____________
            startTime = std::clock();
            dequeSorter.performSort(valuesDeque); // call performSort method from dequeSorter object with our deque as argument
            endTime = std::clock();
            double dequeElapsed = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000000.0; // calculate the duration of the sort in microseconds
            // ___________________________________


            // ___________ PRINTING ______________
            vectorSorter.printResults();
            std::cout << "Time to process a range of " << vectorSorter.getInputSize() << " elements with std::vector : " << vectorElapsed << " us" << std::endl;
            std::cout << "Time to process a range of " << dequeSorter.getInputSize()  << " elements with std::deque : "  << dequeElapsed  << " us" << std::endl;
#ifdef PMERGEME_SHOW_COMPARISONS
            std::cout << "Number of comparisons (vector): " << vectorSorter.getTotalComparisons() << std::endl;
            std::cout << "Number of comparisons (deque):  " << dequeSorter.getTotalComparisons() << std::endl;
#endif
            // ___________________________________
        }



        //___________________ ERROR HANDLING ____________________
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
        return 0;
    }
    else {
        std::cerr << "Error: Invalid number of arguments, Must be at least 2 (program name and list of positive integers)" << std::endl;
        return 1;
    }
    return 0;
}
