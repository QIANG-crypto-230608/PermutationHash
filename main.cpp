#include <iostream>
#include <unordered_map>
#include <bitset>
#include<openssl/sha.h>

using namespace std;

// Permutation-Based Hash class
template<typename T>
class PermutationHash {
private:
    unordered_map<T, T> hashTable; // Hash table

public:
    void insert(const T& element) {
        // Convert the element to bit representation
        bitset<sizeof(T) * 8> bits(element);

        // Split the bits into two parts
        bitset<sizeof(T) * 4> x1, x2;
        for (size_t i = 0; i < sizeof(T) * 4; ++i) {
            x1[i] = bits[i];
            x2[i] = bits[i + sizeof(T) * 4];
        }

        // Get the hash table index using x1 XOR H(x2)
        T index = x1.to_ullong() ^ hash(x2);

        // Store the element in the hash table
        hashTable[index] = hash(element);
        cout << "Element "<< element << " inserted as: " << hash(element) << endl;
    }

    bool find(const T& element) {
        // Convert the element to bit representation
        bitset<sizeof(T) * 8> bits(element);

        // Split the bits into two parts
        bitset<sizeof(T) * 4> x1, x2;
        for (size_t i = 0; i < sizeof(T) * 4; ++i) {
            x1[i] = bits[i];
            x2[i] = bits[i + sizeof(T) * 4];
        }

        // Get the hash table index using x1 XOR H(x2)
        T index = x1.to_ullong() ^ hash(x2);

        // Search for the element in the hash table
        auto it = hashTable.find(index);
        if (it != hashTable.end()) {
            cout << "Element found: " << it->second << std::endl;
            return true;
        }

        // Element not found
        return false;
    }

private:
    T hash(const std::bitset<sizeof(T) * 4>& x2) {
        unsigned char digest[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, x2.to_string().c_str(), x2.to_string.length());
        SHA256_Final(digest, &sha256);

        T hashValue;
        memcpy(&hashValue, digest, sizeof(T));
        return hashValue;
    }
};

int main() {
    PermutationHash<int> hashTable;

    // Insert elements
    hashTable.insert(123);
    hashTable.insert(456);
    hashTable.insert(789);

    // Find elements
    hashTable.find(123);
    hashTable.find(456);
    hashTable.find(789);
    hashTable.find(999); // Not found

    return 0;
}
