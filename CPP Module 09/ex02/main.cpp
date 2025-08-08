#include <stdexcept>
#include <iostream>
#include <ctime>
#include "FordJohnsonSorter.hpp"

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        FordJohnsonSorter sortingEngine;
        try {
            std::clock_t startTime = std::clock();
            sortingEngine.loadInputData(argc, argv);
            sortingEngine.performSortOperations();
            std::clock_t endTime = std::clock();
            double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000000.0;
            
            sortingEngine.printResults();
            std::cout << "Time taken to sort Vector of " << sortingEngine.getInputSize() << " elements: " << elapsedTime << " microseconds" << std::endl;
            
            startTime = std::clock();
            endTime = std::clock();
            elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000000.0;
            
            std::cout << "Time taken to sort Deque of " << sortingEngine.getInputSize() << " elements: " << elapsedTime << " microseconds" << std::endl;
            std::cout << "Number of comparisons: " << sortingEngine.getTotalComparisons() << std::endl;
        }
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
