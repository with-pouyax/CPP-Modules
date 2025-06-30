# Why std::map for Bitcoin Exchange

## What We Need
- Store dates and their exchange rates
- Find the closest date when exact date is missing
- Fast lookups

## Why std::map is Best

### 1. **Key-Value Pairs**
- Map stores date → exchange rate
- Perfect for this data

### 2. **Auto-Sorted**
- Dates stay in order automatically
- No extra work needed

### 3. **Fast Search**
- Finds dates quickly
- Much faster than checking one by one

### 4. **Find Closest Date**
- If no exact date, finds the closest one before it
- Exactly what the exercise asks for

## Why Not Other Containers?

### **Array/Vector**
- Need to sort manually
- Need to search one by one (slow)
- Hard to find closest date

### **Stack**
- Can only access top element
- Can't search by date
- Wrong for this problem

### **Deque**
- No automatic sorting
- Need to search one by one
- Hard to find closest date

### **List**
- No automatic sorting
- Need to search one by one
- Hard to find closest date

## Conclusion
Map gives us everything we need: fast lookups, automatic sorting, and the ability to find the closest date easily. 