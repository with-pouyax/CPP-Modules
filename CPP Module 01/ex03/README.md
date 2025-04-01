
# Unnecessary Violence - Weapon and Human Interaction in C++

This project introduces class composition and object interaction in C++.  
It focuses on modeling a simple scenario involving Humans and their Weapons.

---

## Goal

- Implement a `Weapon` class with the ability to set and get its type.
- Create two types of `Human` classes (`HumanA` and `HumanB`) that interact with the `Weapon` class.
- Learn the difference in how references and pointers behave in object composition.

---

## Weapon Class

The `Weapon` class should have:

- A **private** attribute `type` (string).
- A member function `getType()` that returns a **constant reference** to `type`.
- A member function `setType()` that updates `type` using a given string value.

---

## HumanA and HumanB Classes

Both classes should:

- Have a name.
- Have an `attack()` method that prints:  
  ```
  <name> attacks with their <weapon type>
  ```

### Differences

- `HumanA` **always** has a weapon and receives it **via the constructor** (likely as a reference).
- `HumanB` **might not have a weapon** and gets it **via a setter** (likely as a pointer).

---

## Project Files

- `Makefile`
- `main.cpp`
- `Weapon.cpp` / `Weapon.hpp`
- `HumanA.cpp` / `HumanA.hpp`
- `HumanB.cpp` / `HumanB.hpp`

---

## Example Behavior

```cpp
Weapon club = Weapon("crude spiked club");

HumanA bob("Bob", club);
bob.attack(); // Bob attacks with their crude spiked club

club.setType("some other type of club");
bob.attack(); // Bob attacks with their some other type of club

HumanB jim("Jim");
jim.attack(); // (no weapon assigned â may print nothing or default message)
jim.setWeapon(club);
jim.attack(); // Jim attacks with their some other type of club
```

---

## Summary

This project demonstrates:

- The use of references vs pointers in class composition.
- How objects interact and reflect changes in real-time.
- Proper use of member functions to encapsulate and manage class behavior.
