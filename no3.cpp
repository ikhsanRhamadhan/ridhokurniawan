/*
    Program Find Pairs with Sum K
    Nama: Ridho Kurniawan
    NIM: 231011401209
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<pair<int, int>> findPairsWithSumK(const vector<int>& arr1, const vector<int>& arr2, int K) {
    unordered_set<int> elements;
    vector<pair<int, int>> result;
    
    // Insert elements of arr1 into set
    for (int num : arr1) {
        elements.insert(num);
    }

    // Check for complement in arr2
    for (int num : arr2) {
        if (elements.count(K - num)) {
            result.emplace_back(K - num, num);
        }
    }
    return result;
}

int main() {
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {6, 7, 8, 9};
    int K = 10;

    auto pairs = findPairsWithSumK(arr1, arr2, K);
    cout << "Pairs with sum " << K << ":\n";
    for (auto& p : pairs) {
        cout << "(" << p.first << ", " << p.second << ")\n";
    }
    return 0;
}
