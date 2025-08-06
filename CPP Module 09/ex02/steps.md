# Ford-Johnson Merge-Insertion Sort Algorithm Steps

## C++ Implementation Constraints (42 School Rules)
- **Compilation**: Must compile with `c++ -Wall -Wextra -Werror -std=c++98`
- **Forbidden**: STL containers (`vector`, `list`, `map`, etc.) and algorithms (`<algorithm>`)
- **Allowed**: Basic C++ standard library functions (`iostream`, `string`, etc.)
- **Memory**: Use `new`/`delete` for dynamic allocation, prevent memory leaks
- **Class Design**: Follow Orthodox Canonical Form (constructors, destructor, copy constructor, assignment operator)
- **Headers**: Include guards required, no function implementation in headers

## Debug and Comparison Tracking
- **Comparison Counter**: Track every comparison between two elements using a static counter
- **Debug Mode**: Controlled by `PmergeMe::enableDebug(bool)` static method
- **Debug Output**: Print containers at each step only when debug mode is enabled
- **Output Format**: Use clear, formatted output with proper indentation and labels

## Input Example
- Sequence: `9 8 3 1 7 6 4 2 5 10 3`
- **Note**: This algorithm works with any number of inputs (even or odd)

## Phase 1: Recursive Pairing and Sorting (Depth-based)

**Important**: Phase 1 continues recursively for any number of depths until reaching the baseline (when only one group remains). The number of depths depends on the input size and can be much larger than shown in this example.

### Recursive Depth Process
- **General Rule**: Continue pairing and sorting at each depth until only one group remains
- **Baseline Condition**: When the number of groups at any depth becomes 1
- **Depth Count**: Can be any number n depending on input size (log₂(n) approximately)
- **Sorting Rule**: At each depth, compare the rightmost element of each group

### Example with 11 elements (3 depths)

#### Depth 0
- **Step 1**: Pair consecutive integers from left to right
  - Input: `9 8 3 1 7 6 4 2 5 10 3`
  - Pairs: `[8, 9], [1, 3], [6, 7], [2, 4], [5, 10]`
  - Leftover: `[3]` (remember: added in depth 0)
  - **General rule**: If n is odd, last element becomes leftover
  - **Debug output** (if enabled):
    ```
    [Depth 0] Input: [9, 8, 3, 1, 7, 6, 4, 2, 5, 10, 3]
    [Depth 0] Pairs: [[8, 9], [1, 3], [6, 7], [2, 4], [5, 10]]
    [Depth 0] Leftover: [3]
    ```

#### Depth 1
- **Step 2**: Pair consecutive pairs and sort them
  - **Sorting rule**: Compare the rightmost integer of each pair
  - Input pairs: `[8, 9], [1, 3], [6, 7], [2, 4], [5, 10]`
  - Compare `[1, 3]` vs `[8, 9]` → `[1, 3]` comes first (3 < 9) [comparison #1]
  - Compare `[2, 4]` vs `[6, 7]` → `[2, 4]` comes first (4 < 7) [comparison #2]
  - Result: `[([1, 3], [8, 9]), ([2, 4], [6, 7])]`
  - Leftover: `[5, 10]` (remember: added in depth 1)
  - **General rule**: If number of pairs is odd, last pair becomes leftover
  - **Debug output** (if enabled):
    ```
    [Depth 1] Input pairs: [[8, 9], [1, 3], [6, 7], [2, 4], [5, 10]]
    [Depth 1] Sorted pairs: [[1, 3], [8, 9], [2, 4], [6, 7]]
    [Depth 1] Leftover: [5, 10]
    [Depth 1] Comparisons: 2
    ```

#### Depth 2 (Baseline)
- **Step 3**: Final pairing at baseline
  - Input: `[([1, 3], [8, 9]), ([2, 4], [6, 7])]`
  - Compare `([2, 4], [6, 7])` vs `([1, 3], [8, 9])` → `([2, 4], [6, 7])` comes first (7 < 9) [comparison #3]
  - Result: `[{([2, 4], [6, 7]), ([1, 3], [8, 9])}]`
  - **Baseline reached**: Only one group remains, start backtracking
  - **Debug output** (if enabled):
    ```
    [Depth 2] Input groups: [[1, 3], [8, 9]], [[2, 4], [6, 7]]
    [Depth 2] Sorted groups: [[2, 4], [6, 7]], [[1, 3], [8, 9]]
    [Depth 2] Baseline reached
    [Depth 2] Comparisons: 1
    ```

### Larger Example: 15 elements (4 depths)

#### Depth 0
- Input: `15 14 13 12 11 10 9 8 7 6 5 4 3 2 1`
- Pairs: `[14, 15], [12, 13], [10, 11], [8, 9], [6, 7], [4, 5], [2, 3]`
- Leftover: `[1]`

#### Depth 1
- Input pairs: `[14, 15], [12, 13], [10, 11], [8, 9], [6, 7], [4, 5], [2, 3]`
- Sorted pairs: `[2, 3], [4, 5], [6, 7], [8, 9], [10, 11], [12, 13], [14, 15]`
- Groups: `[([2, 3], [4, 5]), ([6, 7], [8, 9]), ([10, 11], [12, 13])]`
- Leftover: `[14, 15]`

#### Depth 2
- Input groups: `[([2, 3], [4, 5]), ([6, 7], [8, 9]), ([10, 11], [12, 13])]`
- Sorted groups: `[([2, 3], [4, 5]), ([6, 7], [8, 9]), ([10, 11], [12, 13])]`
- Groups: `[([([2, 3], [4, 5]), ([6, 7], [8, 9])], [([10, 11], [12, 13])])]`
- Leftover: `[14, 15]`

#### Depth 3 (Baseline)
- Input: `[([([2, 3], [4, 5]), ([6, 7], [8, 9])], [([10, 11], [12, 13])])]`
- Compare and sort: `[([([2, 3], [4, 5]), ([6, 7], [8, 9])], [([10, 11], [12, 13])])]`
- **Baseline reached**: Only one group remains

### Recursive Implementation Strategy
- **Base case**: When number of groups ≤ 1 (baseline reached)
- **Recursive case**: Continue pairing and sorting at next depth
- **Memory management**: Store leftovers at each depth for reconstruction
- **Comparison tracking**: Count all comparisons during sorting at each depth

## Phase 2: Recursive Chain Reconstruction (Backtracking)

**Important**: Phase 2 must reconstruct the sequence by backtracking through all depths in reverse order, starting from the baseline and working back to depth 0. Each depth's reconstruction depends on the result from the previous depth.

### Recursive Reconstruction Process
- **Start from baseline**: Begin reconstruction from the deepest depth (baseline)
- **Backtrack through all depths**: Process each depth in reverse order (n, n-1, ..., 0)
- **Dependency chain**: Each depth's result becomes input for the next depth's reconstruction
- **Leftover handling**: Each depth must handle its own leftover from Phase 1

### Example with 11 elements (3 depths)

#### Depth 2 Chain Call (Baseline)
- **Step 4**: Reconstruct from baseline depth 2
  - Input: `[{([2, 4], [6, 7]), ([1, 3], [8, 9])}]` and leftover `[5, 10]`
  - **Step 4a**: Split into rights and lefts
    - Rights: `[([1, 3], [8, 9])]` (sorted)
    - Lefts: `[([2, 4], [6, 7])]`
  - **Step 4b**: Add leftover to lefts
    - Lefts: `[([2, 4], [6, 7]), [5, 10]]`
  - **Step 4c**: Generate Jacobsthal numbers for size 3
    - Jacobsthal sequence: `[0, 2, 1]`
  - **Step 4d**: Insert elements using Jacobsthal sequence
    - Insert lefts[0] = `([2, 4], [6, 7])` at beginning of rights (no comparison)
    - Insert lefts[2] = `[5, 10]` using binary insertion (search range: index 0 to 2 in rights)
    - Insert lefts[1] = `[5, 10]` using binary insertion (search range: index 0 to 1 in rights)
  - **Result**: `[[1, 3], [2, 4], [6, 7], [8, 9], [5, 10]]`
  - **Debug output** (if enabled):
    ```
    [Chain Depth 2] Input: [[2, 4], [6, 7]], [[1, 3], [8, 9]] + leftover: [5, 10]
    [Chain Depth 2] Rights: [[1, 3], [8, 9]]
    [Chain Depth 2] Lefts: [[2, 4], [6, 7], [5, 10]]
    [Chain Depth 2] Jacobsthal sequence: [0, 2, 1]
    [Chain Depth 2] Result: [[1, 3], [2, 4], [6, 7], [8, 9], [5, 10]]
    [Chain Depth 2] Binary insertions: 2 comparisons
    ```

#### Depth 1 Chain Call
- **Step 5**: Reconstruct from depth 1
  - Input: `[[1, 3], [2, 4], [6, 7], [8, 9], [5, 10]]` and leftover `[3]`
  - **Step 5a**: Split into rights and lefts
    - Rights: `[3, 4, 7, 9, 10]` (extract rightmost from each pair)
    - Lefts: `[1, 2, 6, 8, 5]` (extract leftmost from each pair)
  - **Step 5b**: Add leftover to lefts
    - Lefts: `[1, 2, 6, 8, 5, 3]`
  - **Step 5c**: Generate Jacobsthal numbers for size 6
    - Jacobsthal sequence: `[0, 2, 1, 4, 3, 5]`
  - **Step 5d**: Insert elements using Jacobsthal sequence
    - Insert lefts[0] = `1` at beginning of rights (no comparison)
    - Insert lefts[2] = `6` using binary insertion (search range: index 0 to 2 in rights)
    - Insert lefts[1] = `2` using binary insertion (search range: index 0 to 1 in rights)
    - Insert lefts[4] = `5` using binary insertion (search range: index 0 to 4 in rights)
    - Insert lefts[3] = `8` using binary insertion (search range: index 0 to 3 in rights)
    - Insert lefts[5] = `3` using binary insertion (search range: index 0 to 5 in rights)
  - **Important**: Track original indexes in rights before any modifications
  - **Result**: Fully sorted sequence
  - **Debug output** (if enabled):
    ```
    [Chain Depth 1] Input: [[1, 3], [2, 4], [6, 7], [8, 9], [5, 10]] + leftover: [3]
    [Chain Depth 1] Rights: [3, 4, 7, 9, 10]
    [Chain Depth 1] Lefts: [1, 2, 6, 8, 5, 3]
    [Chain Depth 1] Jacobsthal sequence: [0, 2, 1, 4, 3, 5]
    [Chain Depth 1] Binary insertions: 5 comparisons
    [Chain Depth 1] Final result: [1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10]
    ```

### Larger Example: 15 elements (4 depths)

#### Depth 3 Chain Call (Baseline)
- Input: `[([([2, 3], [4, 5]), ([6, 7], [8, 9])], [([10, 11], [12, 13])])]` + leftover `[14, 15]`
- Result: `[[2, 3], [4, 5], [6, 7], [8, 9], [10, 11], [12, 13], [14, 15]]`

#### Depth 2 Chain Call
- Input: Result from depth 3 + leftover `[1]`
- Result: `[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]`

### Recursive Implementation Strategy
- **Stack-based approach**: Store depth information and leftovers during Phase 1
- **Reverse iteration**: Process depths from baseline back to depth 0
- **State preservation**: Maintain the structure and order from Phase 1
- **Memory efficiency**: Reuse containers where possible during reconstruction

## Algorithm Structure Overview

### Recursive Depth Calculation
- **Depth count**: For n elements, approximately log₂(n) depths
- **Examples**:
  - 11 elements → 3 depths (log₂(11) ≈ 3.46)
  - 15 elements → 4 depths (log₂(15) ≈ 3.91)
  - 31 elements → 5 depths (log₂(31) ≈ 4.95)
  - 63 elements → 6 depths (log₂(63) ≈ 5.98)

### Phase 1: Recursive Descent
```
Depth 0: [elements] → [pairs] + leftover
Depth 1: [pairs] → [groups of pairs] + leftover
Depth 2: [groups] → [groups of groups] + leftover
...
Depth n: [final group] → baseline reached
```

### Phase 2: Recursive Ascent
```
Depth n: baseline → [reconstructed groups]
Depth n-1: [groups] + leftover → [reconstructed pairs]
Depth n-2: [pairs] + leftover → [reconstructed elements]
...
Depth 0: [elements] + leftover → final sorted sequence
```

### Implementation Requirements
- **Dynamic depth handling**: Algorithm must work with any number of depths
- **State tracking**: Maintain structure and leftovers from each depth
- **Recursive functions**: Implement both descent (Phase 1) and ascent (Phase 2)
- **Memory management**: Handle dynamic allocation for variable depth structures

## Key Implementation Notes

### Sorting Rules
- **Depth 0**: Compare individual integers
- **Depth 1+**: Compare the rightmost integer of each pair/group

### Jacobsthal Numbers
- Used to determine insertion order during chain reconstruction
- Formula: J(n) = J(n-1) + 2*J(n-2) with J(0) = 0, J(1) = 1
- Generate sequence for any size n: `[0, 2, 1, 4, 3, 5, 7, 6, 8, 10, 9, 11, ...]`
- Example for size 6: `[0, 2, 1, 4, 3, 5]`
- Example for size 10: `[0, 2, 1, 4, 3, 6, 5, 8, 7, 9]`

### Binary Insertion Sort
- Used to insert elements from lefts into rights
- Search range: from index 0 to current Jacobsthal index in rights
- Must track original indexes before modifications
- **Implementation constraint**: Cannot use STL algorithms, must implement manually

### Original Index Tracking Strategy
- **Problem**: As we insert elements from lefts into rights, the indexes of rights change
- **Solution**: Create a mapping system to track original positions
- **Implementation**:
  - Create `original_indexes` array: `[0, 1, 2, 3, 4, 5, ...]` (initial positions)
  - Create `current_indexes` array: `[0, 1, 2, 3, 4, 5, ...]` (current positions)
  - When inserting element at position `i` in rights:
    - Update `current_indexes` to reflect new positions
    - Use `original_indexes` to determine the actual search range
  - **Example**:
    - Rights: `[3, 4, 7, 9, 10]` with original_indexes: `[0, 1, 2, 3, 4]`
    - After inserting `1` at beginning: Rights: `[1, 3, 4, 7, 9, 10]`
    - Update current_indexes: `[0, 1, 2, 3, 4, 5]`
    - For next insertion (Jacobsthal index 2), search range is still `[0, 2]` in current rights

### Leftover Tracking
- Each depth must remember which elements were added as leftovers
- Leftovers are always added to the lefts container during reconstruction
- **General handling**: 
  - For odd number of elements: last element becomes leftover
  - For odd number of pairs: last pair becomes leftover
  - Always exactly one leftover per depth (except at baseline)

## Data Structure Requirements

### Custom Container Implementation
- **Cannot use STL containers**: Must implement custom data structures
- **Suggested structures**:
  - Custom `Pair` class for storing paired elements
  - Custom `Group` class for storing groups of pairs
  - Custom dynamic arrays for storing sequences
  - Custom linked list or array-based list for leftovers

### Memory Management
- **Dynamic allocation**: Use `new`/`delete` for dynamic arrays
- **Memory leaks**: Ensure proper cleanup in destructors
- **Copy semantics**: Implement proper copy constructors and assignment operators

### Class Design (Orthodox Canonical Form)
- **Required methods**:
  - Default constructor
  - Copy constructor
  - Assignment operator
  - Destructor
- **Header structure**:
  ```cpp
  #ifndef CLASSNAME_HPP
  #define CLASSNAME_HPP
  // Class declaration only
  #endif
  ```

## Debug Implementation Requirements

### Comparison Counter
- **Static counter**: `static int comparisonCount` to track all comparisons
- **Increment on every comparison**: Between any two elements during sorting
- **Reset capability**: Method to reset counter for new sorts
- **Access method**: `static int getComparisonCount()` to retrieve total

### Debug Mode Control
- **Static flag**: `static bool debugMode` controlled by `enableDebug(bool)`
- **Debug method**: `static void enableDebug(bool enable)` to toggle debug output
- **Conditional printing**: All debug output wrapped in `if (debugMode)`

### Debug Output Format
- **Consistent formatting**: Use `[Depth X]` and `[Chain Depth X]` prefixes
- **Container display**: Show input, intermediate, and output containers clearly
- **Comparison tracking**: Display comparison count at each step
- **Jacobsthal numbers**: Show generated sequence when used
- **Binary insertion details**: Show search ranges and insertion points

### Example Debug Output Structure
```
[Depth 0] Input: [9, 8, 3, 1, 7, 6, 4, 2, 5, 10, 3]
[Depth 0] Pairs: [[8, 9], [1, 3], [6, 7], [2, 4], [5, 10]]
[Depth 0] Leftover: [3]
[Depth 0] Comparisons: 0

[Depth 1] Input pairs: [[8, 9], [1, 3], [6, 7], [2, 4], [5, 10]]
[Depth 1] Sorted pairs: [[1, 3], [8, 9], [2, 4], [6, 7]]
[Depth 1] Leftover: [5, 10]
[Depth 1] Comparisons: 2

[Chain Depth 1] Jacobsthal sequence: [0, 2, 1]
[Chain Depth 1] Binary insertions: 2 comparisons
[Chain Depth 1] Result: [[1, 3], [2, 4], [6, 7], [8, 9], [5, 10]]

Total comparisons: 10
``` 