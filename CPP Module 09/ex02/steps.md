# PmergeMe Implementation Steps

## Project Structure
- **Makefile** in main directory
- **src/** folder for source files
- **includes/** folder for header files
- **main.cpp** in main directory
- **Important:** All code must be C++98 compliant - no C++11 or later features allowed
- **Important:** Only use C++98 standard library features - no external libraries

## Container Choice
- Use **std::vector<int>** and **std::deque<int>** as the two different containers (C++98 standard library)
- Avoid templates - create two separate classes with different container types
- This ensures we have distinct implementations for each container type
- **Important:** Only use C++98 standard library containers and features

## Main Function Implementation
1. **Argument Parsing:**
   - Accept command line arguments as input
   - Return proper error to stderr for invalid inputs
   - Reject inputs like: `./PmergeMe "1 2" "3 4"` or `./PmergeMe 1 2 3a`
   - **Accept duplicates** (important for proper Ford-Johnson implementation)
   - Accept positive integers up to INT_MAX (signed int maximum)
   - Handle edge cases: empty input, non-numeric values, negative numbers

2. **Data Storage:**
   - Save parsed inputs in both vector and deque containers
   - Create separate instances for each container type

## Sorting Class Design
- Create two similar classes: `PmergeMeVector` and `PmergeMeDeque`
- **Both classes are identical in logic and implementation, only different in container type**
- Each class handles only its specific container type (vector vs deque)
- **Each class includes its own timing mechanism** - starts timer when sorting begins, stops when complete
- Use high-resolution clock for microsecond precision to show differences between containers
- The algorithm implementation is exactly the same, just using different STL containers
- **Classes return both sorted container and timing information**

## Comparison Counting Macro
- Implement conditional compilation macro (e.g., `COMPARISON_COUNT`)
- Default: OFF (macro undefined)
- Enable via compilation flag: `make count` or `-DCOMPARISON_COUNT`
- When enabled, print comparison count to verify Ford-Johnson algorithm correctness
- This is for testing/debugging, not for final submission

## Ford-Johnson Algorithm Implementation

### Step 1: Pairing and Separation
- **Pair adjacent elements** in the container (elements at index 0&1, 2&3, 4&5, etc.)
- **Compare each pair** to determine which is larger and which is smaller
- **Count comparisons:** Increment comparison counter for every comparison between two elements (`<`, `>`, `==`)
- Create two containers: `larger` and `smaller`
- **For each pair:**
  - Put the larger element in `larger` container
  - Put the smaller element in `smaller` container
- **Handle odd-sized containers:** If container has odd number of elements, the last unpaired element goes to `larger` container
- **Maintain pair relationships:** From now on, `smaller[i]` is always the pair of `larger[i]` (same index = same pair)

### Step 2: Jacobstahl Sequence Calculation
- Calculate Jacobstahl numbers using the formula: `(2^(k+1) + (-1)^k) / 3`
- **Store sequence in a std::vector<int>** for easy access and iteration
- **Calculate based on the actual size of the `smaller` container** (now that we have it)
- The Jacobstahl sequence determines insertion order for the smaller elements into the sorted larger elements
- Calculate enough numbers to cover the size of the smaller container

### Step 3: Recursive Sorting
- Recursively sort the `larger` container using merge-insertion sort
- **Critical:** Mirror all movements in `smaller` container to maintain pair relationships
- **Whenever you move an element in `larger` container, move the corresponding element at the same index in `smaller` container**
- **This ensures `smaller[i]` always remains the pair of `larger[i]` throughout the entire sorting process**
- **Count comparisons:** Increment comparison counter for every comparison between two elements (`<`, `>`, `==`)
- Continue recursion until `larger` container has 1 element

### Step 4: Binary Insertion Phase
- **First: Insert smaller[0] (with 0 comparisons)** - this element can be inserted without any comparisons since we know it's smaller than its pair (larger[0])
- Use Jacobstahl sequence to determine insertion order for remaining elements
- **Note:** Index 0 is NOT in the Jacobstahl sequence - the first element (smaller[0]) gets special treatment
- **Start with first Jacobstahl number (index 1)** - this is the first element to insert from the sequence
- **Since smaller[i] is always the pair of larger[i], we can directly access smaller[jacobstahl_index]**
- **Important:** Jacobstahl sequence may reference indices beyond the size of smaller container - skip invalid indices but continue iterating
- **For each Jacobstahl index, check if it's valid (index < smaller.size()) before accessing**
- **Continue through the entire Jacobstahl sequence** - don't stop when encountering invalid indices, keep going to find valid ones
- Insert that element into `larger` container using binary insertion sort
- **Do not move or modify the `smaller` container during binary insertion sort; we only read its elements by their original index.**
- Binary insertion should be iterative, not recursive
- **Count comparisons:** Increment comparison counter for every comparison between two elements (`<`, `>`, `==`)

## Index Tracking Strategy
- Use a "mirroring" approach to maintain pair relationships
- Keep track of original positions throughout the algorithm
- When elements move in `larger` container, apply same movements to `smaller`
- This ensures pairs remain aligned by index position

## Binary Insertion Sort Implementation
- Write custom binary search function (don't use std::find)
- Find correct insertion position using binary search
- Insert element at found position
- Count comparisons when macro is enabled
- This should be iterative, not recursive

## Timing Implementation
- **Each class starts its own timer** when the sorting method is called
- **Each class stops its own timer** when sorting is complete
- **Include all sorting operations and data management within the algorithm**
- Use high-resolution clock for microsecond precision
- **Classes return timing information along with sorted results**
- Format output to clearly show differences between containers

## Main Function Flow
- Parse command line arguments and validate input
- Store parsed integers in both `std::vector` and `std::deque` containers
- Create `PmergeMeVector` instance and pass vector container to it for sorting
- Create `PmergeMeDeque` instance and pass deque container to it for sorting
- **Classes handle their own timing internally** - start timer when sorting begins, stop when complete
- Receive sorted results and timing information from both classes
- Display output in required format

## Output Format
1. **First line:** "Before: [unsorted sequence]"
2. **Second line:** "After: [sorted sequence]"
3. **Third line:** "Time to process a range of [N] elements with std::vector: [time] us"
4. **Fourth line:** "Time to process a range of [N] elements with std::deque: [time] us"
5. **Optional (when macro enabled):** Comparison count information

## Makefile Requirements
- Include all mandatory targets: `all`, `clean`, `fclean`, `re`
- **Use compilation flags:** `c++ -Wall -Wextra -Werror -std=c++98` (C++98 standard required)
- Include `-MMD -MP` flags for dependency generation
- Add `count` target for enabling comparison counting: `make count`
- Ensure no unnecessary recompilations
- **Important:** Must compile with `-std=c++98` flag to ensure C++98 compliance

## Error Handling and Safety
- Handle invalid command line arguments
- Handle non-positive integers
- Handle non-numeric inputs
- Handle empty input
- Display errors to stdout
- **Memory safety:** Use RAII principles, avoid memory leaks
- **Exception safety:** Handle potential exceptions without crashes
- **Input validation:** Validate all inputs before processing
- **Resource management:** Ensure proper cleanup of all resources
- **Performance consideration:** Error handling should not significantly impact sorting performance
- **Exception handling strategy:** Use try-catch for major operations (input parsing, container creation) but avoid excessive try-catch blocks within the core sorting algorithm
- **Safety without try-catch:** Use RAII (automatic cleanup), STL container safety, and input validation to prevent leaks and crashes in performance-critical areas

## Edge Cases and Special Input Handling

### 1. Empty Container
- **Expected behavior:** Return immediately; nothing to sort
- **Implementation:** `if (input.empty()) return;`

### 2. Single Element
- **Expected behavior:** Already sorted; no action required
- **Implementation:** `if (input.size() == 1) return;`

### 3. Two Elements
- **Expected behavior:** Form one pair, compare, insert smaller into sorted larger
- **Steps:**
  - A = [max(x, y)]
  - B = [min(x, y)]
  - Insert B[0] into A using binary insertion

### 4. Odd-Sized Containers
- **Expected behavior:** Handle last unpaired element explicitly
- **Implementation:** Form pairs for first n-1 elements, store last element separately
- **Insert last element** into final chain after all other steps

### 5. Duplicate Elements
- **Expected behavior:** Sorting should function properly with duplicates
- **Implementation notes:**
  - Use `<=` or `>=` for stable comparisons
  - Binary insertion must allow inserting duplicates
  - Don't skip equal elements

### 6. Maximum Values (INT_MAX)
- **Expected behavior:** Handle normally without overflow
- **Implementation:** Use `std::numeric_limits<int>::max()` for testing
- **Avoid arithmetic** that can cause overflow

### 7. Minimum Values
- **Expected behavior:** Handle like duplicates
- **Implementation:** Ensure sorting logic doesn't skip or misplace small values
- **Insertion routine** must maintain correctness regardless of value size

### 8. Invalid Container
- **Expected behavior:** Handle gracefully
- **Implementation:** Check for null pointers if using pointer-based approach
- **STL containers** can't be null, but validate container state

### 9. Already Sorted Input
- **Expected behavior:** Algorithm must run fully (no shortcuts)
- **Important:** Still build pairs, sort, and insert as per Ford-Johnson steps
- **Don't add early exits** just because input appears sorted

### 10. Reverse Sorted Input
- **Expected behavior:** Algorithm should perform correctly in worst-case ordering
- **Implementation:** Ensure merge sort doesn't degrade to quadratic behavior
- **Binary search** should handle maximal shifts efficiently

## Key Implementation Notes
- **No std::find usage** - write custom binary search
- **Handle duplicates properly** - don't reject them
- **Use high-precision timing** for meaningful container comparisons
- **Follow Ford-Johnson algorithm exactly** for optimal comparison count
- **Important:** All code must be C++98 compliant - no C++11 features like auto, range-based for, etc.
- **Important:** Only use C++98 standard library - no external libraries or C++11+ features
- **Important:** No Boost, no modern C++ features, only C++98 standard library allowed
- **Memory safety:** Prevent memory leaks and crashes with proper error handling
- **Performance optimization:** Minimize overhead to stay close to Ford-Johnson theoretical limits
- **C++ best practices:** Use RAII, proper exception handling, and avoid undefined behavior
