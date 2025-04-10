# Hash Table Analysis Project

## Specifications
- **Language**: C++17
- **Compiler**: g++ or clang++ with C++17 support
- **IDE**: Any C++ compatible IDE (VS Code, CLion, etc.)
- **Dependencies**: Standard Library only

## Building and Running
```bash
g++ -std=c++17 src/*.cpp -o hashtable
./hashtable
```

## Hashing Implementation Basics

### Core Structure
- **Storage**: Direct string storage using a dynamic array
- **Collision Resolution**: Linear probing
- **Load Factor**: Threshold configurable at construction (default: 0.75)

### Hashing Mechanism
1. Uses `std::hash<string>` for primary hashing
2. Modulo operation maps hash to table indices
3. Empty slots marked with empty strings

### Key Operations
| Operation | Behavior |
|-----------|----------|
| `insert(str)` | Adds string if not present, triggers resize when load factor exceeded |
| `find(str)`  | Returns boolean indicating string presence |

### Resizing Strategies
1. **Double Size** (Strategy 1): 
   - New size = current_size × 2
2. **Fixed Addition** (Strategy 2):
   - New size = current_size + 10000

### Performance Characteristics
- **Insert**: O(1) average, O(n) worst-case during resize
- **Search**: O(1) average, O(n) worst-case (all probes)
- **Space**: O(n) where n = table capacity