#include <stdexcept>
#include <iostream>
#include <ctime>
#include "FordJohnsonVectorSorter.hpp"
#include "FordJohnsonDequeSorter.hpp"
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        FordJohnsonVectorSorter vectorSorter; // dedicated vector sorter
        FordJohnsonDequeSorter dequeSorter;   // dedicated deque sorter
        try {
            // ___________ PARSING ___________
            std::vector<int> valuesVector; // vector to store the values (vector sorter)
            std::deque<int> valuesDeque;   // deque to store the values (deque sorter)
            parseArgsToContainers(argc, argv, valuesVector, valuesDeque); // parse the input data into a vector and a deque
            // _______________________________

            
            // ___________ VECTOR SORT ___________
            std::clock_t startTime = std::clock();
            vectorSorter.performSort(valuesVector); // perform the vector sort
            std::clock_t endTime = std::clock(); // stop the timer
            double vectorElapsed = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000000.0;
            // _______________________________


            // ___________ DEQUE SORT ____________
            startTime = std::clock(); // 
            dequeSorter.performSort(valuesDeque);
            endTime = std::clock();
            double dequeElapsed = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000000.0;
            // ___________________________________


            // ___________ PRINTING ______________
            vectorSorter.printResults();
            std::cout << "Time to process a range of " << vectorSorter.getInputSize() << " elements with std::vector : " << vectorElapsed << " us" << std::endl;
            std::cout << "Time to process a range of " << dequeSorter.getInputSize()  << " elements with std::deque : "  << dequeElapsed  << " us" << std::endl;
#ifdef PMERGEME_SHOW_COMPARISONS
            std::cout << "Number of comparisons: " << vectorSorter.getTotalComparisons() << std::endl;
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
