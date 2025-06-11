// Default constructor
template<typename T>
Array<T>::Array() : _array(NULL), _size(0) {} //Array::Array() {} means: We're implementing the constructor of a normal (non-template) class Array 
                                             //Array<T>::Array() {} means: We're implementing the constructor of a template class Array<T> — meaning a class that works for any type T

// Constructor with size make an array of size n and each element is default initialized to T's default value (e.g., 0 for int, "" for std::string, etc.)
template<typename T>
Array<T>::Array(unsigned int n) : _size(n) { //set the default size to n
    try {
        _array = new T[n](); // () initializes each element to T's default value, like 0 for int, "" for std::string, etc.
    } catch (const std::bad_alloc& e) { // If memory allocation fails
        _size = 0; // Set size to 0 because the array could not be created
        _array = NULL; // Set _array to NULL to avoid dangling pointer
        std::cerr << "Error: Failed to allocate memory for array of size " << n << std::endl;
        throw; // Re-throw the exception to signal the error to the caller
    }
}

// Copy constructor
template<typename T>
Array<T>::Array(const Array& other) : _size(other._size) {   // our copy constructor receives a const reference to another Array object, and as default value, it gives the size of the other array to _size of the new array.
    try {
        _array = new T[_size](); // Value initialization
        for (unsigned int i = 0; i < _size; i++) { // we loop through the elements of the other array and copy them to the new array.
            _array[i] = other._array[i];
        }
    } catch (const std::bad_alloc& e) { // If memory allocation fails
        _size = 0; 
        _array = NULL;
        std::cerr << "Error: Failed to allocate memory while copying array of size " << _size << std::endl;
        throw; // Re-throw the exception to signal the error to the caller
    }
}

// Assignment operator
template<typename T>
Array<T>& Array<T>::operator=(const Array& other) { // Array<T>& Array<T> -> Array<T>& is the return type, Array<T> is the class name, const Array& other is the reference to the other Array object we want to assign to current object.
    if (this != &other) { // if they are not the same
        T* new_array = NULL;
        try {
            new_array = new T[other._size](); // Value initialization
            for (unsigned int i = 0; i < other._size; i++) { // loop through the elements of the other array and copy them to the new array.
                new_array[i] = other._array[i]; // deep copy the elements
            }
            // If we reach here, the new array has been successfully created and filled.
            if (_array != NULL) // Check if _array exists before deleting
                delete[] _array; // delete the old array to avoid memory leak
            _array = new_array; // assign the new array to the current object's _array
            _size = other._size; // update the size of the current object to match the other array's size
        } catch (const std::bad_alloc& e) {
            delete[] new_array;
            _array = NULL; // Set _array to NULL to avoid dangling pointer
            _size = 0; // Set size to 0 because the array could not be created
            std::cerr << "Error: Failed to allocate memory during array assignment of size " << other._size << std::endl;
            throw; // Re-throw the exception to signal the error to the caller
        }
    }
    return *this;
}

// Destructor
template<typename T>
Array<T>::~Array() {
    if (_array != NULL) // Check if _array exists before deleting
        delete[] _array;
}

// Subscript operator (indexing operator)
template<typename T>
T& Array<T>::operator[](unsigned int index) {
    if (index >= _size) // if index is out of bounds
        throw std::out_of_range("Index out of bounds"); // in caller we can print the error message using e.what()
    return _array[index]; // if throw calls we never reach this line, so always index should be protected in caller
}

// Const subscript operator
template<typename T>
const T& Array<T>::operator[](unsigned int index) const {
    if (index >= _size)
        throw std::out_of_range("Index out of bounds");
    return _array[index];
}

// Size function
template<typename T>
unsigned int Array<T>::size() const { // This function returns the number of elements in the array of type T.
    return _size;
}
