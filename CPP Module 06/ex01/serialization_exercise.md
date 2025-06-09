
# 🧪 Exercise 01 — Serialization

## 📁 Folder to turn in:
```
ex01/
```

## 📦 Files to turn in:
- `Makefile`
- All `.cpp` and `.h` / `.hpp` files
- Including the file where your `Data` struct is defined

---

## 📝 What you must do:

### 1. Create a `Data` structure
- Must **not** be empty.
- It should have at least **one data member** (e.g., `int age;`, `std::string name;`, etc.)

---

### 2. Create a `Serializer` class
- The class **must not be instantiable**.  
  (Make the constructor private or delete it.)
- It must contain only **static** methods:

```cpp
static uintptr_t serialize(Data* ptr);
static Data* deserialize(uintptr_t raw);
```

#### 🔹 `serialize()`:
- Takes a `Data*` (pointer to Data)
- Returns the same pointer as an integer (`uintptr_t`)

#### 🔹 `deserialize()`:
- Takes an integer of type `uintptr_t`
- Converts it back to a `Data*` (pointer)

---

### 3. Write a test program (in `main.cpp`)
- Create a `Data` object and set some values
- Use `serialize()` on its address to get an integer
- Use `deserialize()` on that integer to get back a pointer
- ✅ Confirm that the deserialized pointer is the **same** as the original
- ✅ Print the data from the deserialized pointer to prove it works

---

### ✅ Example test logic:

```cpp
Data data;
data.id = 123;
data.name = "Pouya";

uintptr_t raw = Serializer::serialize(&data);
Data* ptr = Serializer::deserialize(raw);

if (ptr == &data)
    std::cout << "Success: pointers match!" << std::endl;

std::cout << "ID: " << ptr->id << ", Name: " << ptr->name << std::endl;
```

---

### 🚫 Forbidden Functions:
- **None** — you're allowed to use anything.
