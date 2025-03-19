# My Awesome PhoneBook - Comprehensive Project Plan

### Author: Pouya
### Date: 2025-03-19

---

## 📌 Project Overview
Implement a simple PhoneBook software in C++ without dynamic memory allocation. It uses two classes: `Contact` and `PhoneBook`, storing up to 8 contacts, overwriting oldest ones after the limit. The software provides three user commands: `ADD`, `SEARCH`, and `EXIT`.

---

## 🧠 Phase 1: Planning

### Step 1: Project Overview and Constraints
- No dynamic memory allocation (`new`, `delete`, `malloc`, `free` forbidden).
- Fixed-size storage for 8 contacts.
- On adding the 9th contact, overwrite the oldest.
- Three commands: `ADD`, `SEARCH`, and `EXIT`.

### Step 2: Create Project Structure
```
ex01/
├── Makefile
├── Contact.hpp
├── Contact.cpp
├── PhoneBook.hpp
├── PhoneBook.cpp
└── main.cpp
```

---

## 🎨 Phase 2: Class Design

### 2.1: Contact Class - Attributes
- `std::string _firstName`
- `std::string _lastName`
- `std::string _nickname`
- `std::string _phoneNumber`
- `std::string _darkestSecret`
- `int _index` *(optional)*
- `bool _isFilled`

### 2.2: Contact Methods
#### Constructors / Destructors:
- `Contact()`
- `~Contact()`

#### Setters:
- `setFirstName()`
- `setLastName()`
- `setNickname()`
- `setPhoneNumber()`
- `setDarkestSecret()`
- `setIsFilled()`
- `setIndex()` *(optional)*
- `setContactFields()`

#### Getters:
- `getFirstName()`
- `getLastName()`
- `getNickname()`
- `getPhoneNumber()`
- `getDarkestSecret()`
- `getIndex()` *(optional)*
- `isFilled()`

#### Display Methods:
- `displaySummary()`
- `displayDetails()`

### 2.3: Helper Function
- `truncateTo10(const std::string&)`

### 2.4: PhoneBook Class - Attributes
- `Contact _contacts[8]`
- `int _nextIndex`
- `int _contactCount`

### 2.5: PhoneBook Methods
- `addContact()`
- `searchContacts()`

---

## ⚙️ Phase 3: Implementation

### Contact Class
- Inline initialize attributes.
- Implement setters and getters.
- Implement display methods using `std::setw(10)` and `std::right`.
- Use `truncateTo10()` in `displaySummary()`.

### Helper Function
```cpp
std::string truncateTo10(const std::string &str) {
    if (str.length() <= 10)
        return str;
    return str.substr(0, 9) + ".";
}
```

### PhoneBook Class
#### addContact():
- Prompt user for each field.
- Reject empty inputs.
- Use `setContactFields()`.
- Mark contact filled.
- Update `_nextIndex` and `_contactCount`.

#### searchContacts():
- Print headers.
- Display contacts using `displaySummary()`.
- Prompt for index and validate.
- Call `displayDetails()`.

### main.cpp
```cpp
int main() {
    PhoneBook phonebook;
    std::string command;

    while (true) {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);
        if (command == "ADD")
            phonebook.addContact();
        else if (command == "SEARCH")
            phonebook.searchContacts();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Invalid command." << std::endl;
    }
    return 0;
}
```

---

## 🧪 Phase 4: Testing & Debugging

### Functional Testing
- Add 8+ contacts and check circular buffer logic.
- Validate formatting in search.
- Test full detail view.
- Test `EXIT` command.

### Edge Case Testing
- Reject empty fields.
- Test invalid index.
- Long input strings (truncated correctly).

---

## 🎯 Phase 5: Finalization

- Review code for 42 standards.
- No dynamic memory.
- Complete Makefile.
- Ensure all files in correct directory.

---

## ✅ Why These Methods Were Chosen
- Encapsulation for safety.
- Circular buffer for efficient overwrite.
- Inline initialization for clarity.
- `std::setw(10)` and `truncateTo10()` for formatting.
- Clear method separation for readability and maintainability.
