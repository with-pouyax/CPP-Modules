
# C++ Module 00 - Exercise 01: My Awesome PhoneBook

## Overview
In this exercise, you'll create a simple phonebook software using C++. You will practice creating basic classes, managing input/output from the user, and handling data without dynamic memory allocation.

---

## Project Setup

### Directory Structure
- Create a directory named `ex01`.

### Files to Submit
- `Makefile`
- All source files (`*.cpp`)
- All header files (`*.h` or `*.hpp`)

### Important Restriction
- **No dynamic memory allocation allowed** (`new`, `delete`, `malloc`, `free` are forbidden).

---

## Classes to Implement

### 1. **PhoneBook** Class
- Contains an array of contacts.
- Can store up to **8 contacts**.
- When adding a 9th contact, overwrite the oldest contact (replace the first contact added).
- Must explicitly instantiate objects (e.g., `PhoneBook myPhoneBook;`).

### 2. **Contact** Class
- Represents an individual contact.
- Contains the following fields:
  - First name
  - Last name
  - Nickname
  - Phone number
  - Darkest secret
- Fields cannot be empty.
- Must explicitly instantiate objects (e.g., `Contact myContact;`).

**Important:**
- Class attributes should be `private` if they are used only within the class, and `public` if accessed externally.

---

## How Your Program Should Work

Your program starts with an empty phonebook and repeatedly asks the user to input one of three commands:
- `ADD`
- `SEARCH`
- `EXIT`

### Commands Explanation

#### 1. `ADD`
- Prompt the user for each contact field individually:
  1. First name
  2. Last name
  3. Nickname
  4. Phone number
  5. Darkest secret
- None of these fields can be empty.
- After all fields are completed, save the new contact.

#### 2. `SEARCH`
- First, display all stored contacts in a formatted table with exactly four columns:
  ```
  Index | First Name | Last Name | Nickname
  ```
- Each column is exactly **10 characters wide**, separated by a pipe (`|`).
- Text must be **right-aligned**. If text exceeds 10 characters, truncate it and replace the last visible character with a dot (`.`).

**Example:**
```
     Index|First Name| Last Name|  Nickname
         1|       John|       Doe| JohnnyBoy
         2| Alexandr.| Hamilton.| AlexTheGr.
```

- After displaying the list, prompt the user for the contact index they wish to view in detail.
- If the index provided is invalid, clearly inform the user.
- If valid, display each field of the selected contact clearly, one per line.

#### 3. `EXIT`
- Immediately quit the program.
- All contacts are permanently lost upon exit.

#### Other Inputs
- Ignore any other input and re-prompt the user.

---

## Helpful Links
- [C++ String Reference](http://www.cplusplus.com/reference/string/string/)
- [C++ IO Manipulation (iomanip)](http://www.cplusplus.com/reference/iomanip/)

---

## Additional Requirements
- Clearly name your executable (suggested: `phonebook`).
- Ensure your Makefile compiles the program according to the standard practices at 42.

---

Now, you're all set to create your awesome 80s-style phonebook!
