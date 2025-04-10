#include <iostream>
#include <vector>
#include <string>
#include <functional>

/*
 * Part 1.1: HashTable Implementation
 * This class implements a hash table with linear probing and configurable resize strategies
 */
class HashTable {
private:
    std::vector<std::string> table;
    size_t size;
    size_t count;
    float maxLoadFactor;
    int resizeStrategy; // 1: double, 2: add 10000

    // Part 1.1.4: Hash function for strings
    size_t hash(const std::string& str) {
        return std::hash<std::string>{}(str);
    }

    // Part 1.1.5: Get index using modulo operation
    size_t getIndex(const std::string& str) {
        return hash(str) % size;
    }

    // Part 1.1.10: Resize and rehash the table
    void resize() {
        size_t oldSize = size;
        if (resizeStrategy == 1) {
            size *= 2; // Strategy 1: double the size
        } else {
            size += 10000; // Strategy 2: add 10000
        }

        std::vector<std::string> oldTable = table;
        table.clear();
        table.resize(size);
        count = 0;

        // Rehash all existing elements
        for (const auto& str : oldTable) {
            if (!str.empty()) {
                insert(str);
            }
        }
    }

public:
    // Part 1.1.2: Constructor with configurable parameters
    HashTable(size_t initialSize = 16, float maxLoad = 0.75f, int strategy = 1)
        : size(initialSize), count(0), maxLoadFactor(maxLoad), resizeStrategy(strategy) {
        table.resize(size);
    }

    // Part 1.1.6: Insert function
    void insert(const std::string& str) {
        if (find(str)) { // Already exists
            return;
        }

        // Part 1.1.10: Check if resize needed
        if ((float)(count + 1) / size > maxLoadFactor) {
            resize();
        }

        size_t index = getIndex(str);
        while (true) {
            // Part 1.1.8: Linear probing for collision resolution
            if (table[index].empty()) {
                table[index] = str;
                count++;
                return;
            } else if (table[index] == str) {
                return;
            }
            index = (index + 1) % size;
        }
    }

    // Part 1.1.7: Find function
    bool find(const std::string& str) {
        size_t index = getIndex(str);
        size_t start = index;
        
        while (true) {
            // Part 1.1.9: Find logic with linear probing
            if (table[index].empty()) {
                return false;
            } else if (table[index] == str) {
                return true;
            }
            index = (index + 1) % size;
            if (index == start) { // Full table cycle
                return false;
            }
        }
    }

    size_t getSize() const { return size; }
    size_t getCount() const { return count; }
};

/*
 * Part 1.2: Test Cases for Correctness Verification
 */
void runTests() {
    std::cout << "=== Running Test Cases ===\n";
    
    // Test Case 1: Basic functionality
    // Part 1.2.1: Add 5 strings and verify find operations
    {
        HashTable ht1;
        std::vector<std::string> testStrings = {"apple", "banana", "cherry", "date", "elderberry"};
        std::vector<std::string> nonExisting = {"fig", "grape", "honeydew", "kiwi", "lemon"};
        
        for (const auto& str : testStrings) {
            ht1.insert(str);
        }
        
        bool allFound = true;
        for (const auto& str : testStrings) {
            if (!ht1.find(str)) {
                allFound = false;
                break;
            }
        }
        
        bool noneFound = true;
        for (const auto& str : nonExisting) {
            if (ht1.find(str)) {
                noneFound = false;
                break;
            }
        }
        
        std::cout << "Test 1 - Basic functionality: " 
                  << (allFound && noneFound ? "PASSED" : "FAILED") << std::endl;
    }
    
    // Test Case 2: Resize with doubling strategy (23 elements)
    // Part 1.2.2: Verify single resize occurs
    {
        HashTable ht2(16, 0.75f, 1);
        std::vector<std::string> strings23;
        for (int i = 0; i < 23; i++) {
            strings23.push_back("str" + std::to_string(i));
            ht2.insert(strings23.back());
        }
        
        bool allFound = true;
        for (const auto& str : strings23) {
            if (!ht2.find(str)) {
                allFound = false;
                break;
            }
        }
        
        std::cout << "Test 2 - Doubling strategy (23 elements):\n"
                  << "  Final size: " << ht2.getSize() << " (Expected: 32)\n"
                  << "  All found: " << (allFound ? "YES" : "NO") << "\n"
                  << "  Result: " << (ht2.getSize() == 32 && allFound ? "PASSED" : "FAILED") << std::endl;
    }
    
    // Test Case 3: Second resize with doubling strategy (24 elements)
    // Part 1.2.3: Verify second resize occurs
    {
        HashTable ht3(16, 0.75f, 1);
        std::vector<std::string> strings24;
        for (int i = 0; i < 24; i++) {
            strings24.push_back("str" + std::to_string(i));
            ht3.insert(strings24.back());
        }
        
        bool allFound = true;
        for (const auto& str : strings24) {
            if (!ht3.find(str)) {
                allFound = false;
                break;
            }
        }
        
        std::cout << "Test 3 - Doubling strategy (24 elements):\n"
                  << "  Final size: " << ht3.getSize() << " (Expected: 64)\n"
                  << "  All found: " << (allFound ? "YES" : "NO") << "\n"
                  << "  Result: " << (ht3.getSize() == 64 && allFound ? "PASSED" : "FAILED") << std::endl;
    }
    
    // Test Case 4: Addition strategy (23 elements)
    // Part 1.2.4: Verify addition strategy
    {
        HashTable ht4(16, 0.75f, 2);
        std::vector<std::string> strings23;
        for (int i = 0; i < 23; i++) {
            strings23.push_back("str" + std::to_string(i));
            ht4.insert(strings23.back());
        }
        
        bool allFound = true;
        for (const auto& str : strings23) {
            if (!ht4.find(str)) {
                allFound = false;
                break;
            }
        }
        
        std::cout << "Test 4 - Addition strategy (23 elements):\n"
                  << "  Final size: " << ht4.getSize() << " (Expected: 10016)\n"
                  << "  All found: " << (allFound ? "YES" : "NO") << "\n"
                  << "  Result: " << (ht4.getSize() == 10016 && allFound ? "PASSED" : "FAILED") << std::endl;
    }
    
    // Test Case 5: Addition strategy (24 elements)
    {
        HashTable ht5(16, 0.75f, 2);
        std::vector<std::string> strings24;
        for (int i = 0; i < 24; i++) {
            strings24.push_back("str" + std::to_string(i));
            ht5.insert(strings24.back());
        }
        
        bool allFound = true;
        for (const auto& str : strings24) {
            if (!ht5.find(str)) {
                allFound = false;
                break;
            }
        }
        
        std::cout << "Test 5 - Addition strategy (24 elements):\n"
                  << "  Final size: " << ht5.getSize() << " (Expected: 10016)\n"
                  << "  All found: " << (allFound ? "YES" : "NO") << "\n"
                  << "  Result: " << (ht5.getSize() == 10016 && allFound ? "PASSED" : "FAILED") << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}