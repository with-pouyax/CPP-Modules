# C++98 Casting Guide

## Overview
C++98 provides three main categories of casting:
1. **Implicit Casting** - Automatic conversions by the compiler
2. **Legacy C Casts** - Old C-style casting (not recommended in C++)
3. **Explicit Casts** - Modern C++ casting operators

## 1. Implicit Casting

Implicit casting is performed automatically by the compiler when converting between compatible types.

### Safe Conversions (No Data Loss)
- `int` → `double` - Safe, no data loss
- `short` → `int` - Safe, no data loss
- `float` → `double` - Safe, no data loss

### Potentially Unsafe Conversions (Data Loss Possible)
- `double` → `int` - Decimal part is truncated
- `long` → `int` - May lose precision if value exceeds int range

### Inheritance Casting
- **Upcasting** (Child → Parent): Safe and implicit
- **Downcasting** (Parent → Child): Requires explicit cast, potentially unsafe

## 2. Legacy C Casts

Old C-style casting using `(type)value` syntax:
```cpp
int x = (int)3.14;
```

**Not recommended in C++** - Use explicit casts instead for better type safety and clarity.

## 3. Explicit Casts (Modern C++)

### a) static_cast
- **Purpose**: Compile-time cast for compatible types
- **Use Cases**: Numeric conversions, up/downcasting in inheritance
- **Safety**: No runtime safety checks for downcasting
- **Limitation**: Cannot cast between unrelated types

```cpp
double d = 3.14;
int i = static_cast<int>(d);  // Explicit conversion
```

### b) dynamic_cast
- **Purpose**: Runtime-safe downcasting with RTTI (Run-Time Type Information)
- **Requirements**: 
  - Only works with polymorphic classes (must have at least one virtual function)
  - Base class must have virtual functions to enable RTTI
- **Safety**: Returns `nullptr` (pointers) or throws `std::bad_cast` (references) if cast fails
- **Use Case**: When you have a base class pointer/reference but don't know the actual derived type

#### RTTI and Virtual Tables
- **RTTI**: C++ stores metadata with polymorphic classes to track the real type at runtime
- **Virtual Table (vtable)**: Hidden table created by compiler for classes with virtual functions
- Together, they enable `dynamic_cast` to determine the actual object type at runtime

```cpp
Parent* ptr = getSomeParent();  // we dont know parent o child
Child1* child = dynamic_cast<Child1*>(ptr);
if (child != nullptr) {
    // mean ptr was a child
}
```

### c) const_cast
- **Purpose**: Adding or removing `const` or `volatile` qualifiers
- **Safety**: Only safe if the original object was not actually declared const
- **Use Case**: Calling functions that need non-const parameters when you only have const pointers

```cpp
void modifyValue(int* ptr) { *ptr = 42; }

void callWithConst(const int* ptr) {
    modifyValue(const_cast<int*>(ptr));  // Safe only if original object was non-const
}
```

### d) reinterpret_cast
- **Purpose**: Raw memory-level reinterpretation of bit patterns
- **Safety**: No runtime checks, no safety guarantees
- **Use Case**: Low-level programming where you need to treat one type as another
- **Warning**: Use with extreme caution - you're telling the compiler "I know what I'm doing"

```cpp
int* ptr = reinterpret_cast<int*>(0x12345678);  // Treat address as int pointer
```

## Best Practices

1. **Prefer explicit casts** over implicit conversions for clarity
2. **Use static_cast** for numeric conversions and inheritance upcasting
3. **Use dynamic_cast** for safe downcasting when you need runtime type checking
4. **Use const_cast** sparingly and only when you're certain it's safe
5. **Avoid reinterpret_cast** unless absolutely necessary for low-level operations
6. **Never use C-style casts** in modern C++ code 