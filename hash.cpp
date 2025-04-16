#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <fstream>
#include <unordered_set>
#include <random>

/*
 * Part 1.1: HashTable Implementation
 */
class HashTable {
private:
    std::vector<std::string> table;
    size_t size;
    size_t count;
    float maxLoadFactor;
    int resizeStrategy;

    size_t hash(const std::string& str) {
        return std::hash<std::string>{}(str);
    }

    size_t getIndex(const std::string& str) {
        return hash(str) % size;
    }

    void resize() {
        size_t oldSize = size;
        if (resizeStrategy == 1) {
            size *= 2;
        } else {
            size += 10000;
        }

        std::vector<std::string> oldTable = table;
        table.clear();
        table.resize(size);
        count = 0;

        for (const auto& str : oldTable) {
            if (!str.empty()) {
                insert(str);
            }
        }
    }

public:
    HashTable(size_t initialSize = 16, float maxLoad = 0.75f, int strategy = 1)
        : size(initialSize), count(0), maxLoadFactor(maxLoad), resizeStrategy(strategy) {
        table.resize(size);
    }

    void insert(const std::string& str) {
        if (find(str)) return;

        if ((float)(count + 1) / size > maxLoadFactor) {
            resize();
        }

        size_t index = getIndex(str);
        while (true) {
            if (table[index].empty()) {
                table[index] = str;
                count++;
                return;
            }
            index = (index + 1) % size;
        }
    }

    bool find(const std::string& str) {
        size_t index = getIndex(str);
        size_t start = index;
        
        while (true) {
            if (table[index].empty()) return false;
            if (table[index] == str) return true;
            index = (index + 1) % size;
            if (index == start) return false;
        }
    }

    size_t getSize() const { return size; }
    size_t getCount() const { return count; }
};

/*
 * Part 1.2: Test Cases
 */
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

/*
 * Milestone 2 Implementation
 */
std::vector<std::string> generateUniqueStrings(int count) {
    std::unordered_set<std::string> generated;
    std::vector<std::string> result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000000, 99999999);

    while(result.size() < count) {
        std::string num = std::to_string(dis(gen));
        if(generated.insert(num).second) {
            result.push_back(num);
        }
    }
    return result;
}

void timeRehashCost() {
    std::ofstream out("rehash_times.csv");
    out << "q,no_rehash,doubling,addition\n";
    
    auto wholeList = generateUniqueStrings(131072);
    
    for(int q = 4; q <= 17; q++) {
        int num_values = (0.75 * (1 << q)) - 1;
        
        // No Rehash
        auto start = std::chrono::high_resolution_clock::now();
        HashTable ht_no_rehash(1 << 17, 0.75f, 1);
        for(int i=0; i<num_values; i++) ht_no_rehash.insert(wholeList[i]);
        auto time_no_rehash = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
        
        // Doubling
        start = std::chrono::high_resolution_clock::now();
        HashTable ht_double(1 << q, 0.75f, 1);
        for(int i=0; i<num_values; i++) ht_double.insert(wholeList[i]);
        auto time_double = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
        
        // Addition
        start = std::chrono::high_resolution_clock::now();
        HashTable ht_add(1 << q, 0.75f, 2);
        for(int i=0; i<num_values; i++) ht_add.insert(wholeList[i]);
        auto time_add = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count();

        out << q << "," 
            << time_no_rehash/num_values << ","
            << time_double/num_values << ","
            << time_add/num_values << "\n";
    }
}

void timeLoadFactor() {
    auto wholeList = generateUniqueStrings(131072);
    std::vector<std::string> addValues(wholeList.begin(), wholeList.begin() + 65536);
    std::vector<std::string> checkValues(wholeList.begin() + 65536, wholeList.end());

    std::ofstream out("load_factor_times.csv");
    out << "load_factor,success_time,fail_time\n";
    
    HashTable ht(65536, 1.0f, 1);
    
    for(double target_lf = 0.1; target_lf < 0.99; target_lf += 0.03) {
        int target_count = target_lf * 65536;
        while(ht.getCount() < target_count) {
            ht.insert(addValues[ht.getCount()]);
        }
        
        // Successful searches
        auto start = std::chrono::high_resolution_clock::now();
        for(int i=0; i<target_count; i++) ht.find(addValues[i]);
        double succ_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start).count() / target_count;
        
        // Unsuccessful searches
        start = std::chrono::high_resolution_clock::now();
        for(int i=0; i<target_count; i++) ht.find(checkValues[i]);
        double fail_time = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start).count() / target_count;
        
        out << target_lf << "," << succ_time << "," << fail_time << "\n";
    }
}

int main() {
    runTests();
    timeRehashCost();
    timeLoadFactor();
    std::cout << "Data files generated. Use Python script for plotting.\n";
    return 0;
}