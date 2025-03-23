#include "Zombie.hpp"

int main() {
    // Create a heap zombie
    Zombie* heapZombie = newZombie("Heap_Pouya");
    if (heapZombie) {
        heapZombie->announce();
        
        // Manually delete the heap zombie
        delete heapZombie;
    }
    
    // Create a stack zombie through the randomChump function
    randomChump("Stack_Pouya");
    
    return 0;
} 
