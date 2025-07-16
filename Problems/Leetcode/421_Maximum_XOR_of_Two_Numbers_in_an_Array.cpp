#include <bits/stdc++.h>
using namespace std;

// trie node
// - left: represent 0 in binary of num
// - right: represent 1 in binary of num
struct Trie {
    Trie* left = nullptr;
    Trie* right = nullptr;
};

void insert(Trie* root, int num) {
    Trie* it = root;

    // O(log(32)_2 --> O(5) --> O(1)
    for(int i=31; i>=0; i--) {
        // tells that i-th bit of num is set-bit or not
        int ibit = (num>>i)&1;
    
        if(ibit==0) {
            // if i-th bit of num is 0 so we need to create
            // new node in left & move iterator to left
            if(!it->left)
                it->left = new Trie();
            it = it->left;
        } else {
            // if i-th bit of num is 0 so we need to create
            // new node in right & move iterator to right
            if (!it->right)
                it->right = new Trie();
            it = it->right;
        }
    }
}

int findMaximumXorBitTrie(Trie* root, int num) {
    int max_xor = 0;
    Trie* it = root;
    
    // find the maximum xor value for this num
    // O(log(32)_2 --> O(5) --> O(1)
    for(int i=31; i>=0; i--) {
        int ibit = (num>>i)&1;
        
        if(ibit==0) {
            // if i-th bit is 0 then we need to find set bit for max xor
            // if no set bit in right, then move to left(not max xor)
            // else do 0 xor 1 = 1, and calculates the value of max_xor
            // by adding 2^i
            if(!it->right)
                it = it->left;
            else {
                max_xor += pow(2, i);
                it = it->right;
            }
        } else {
            // if i-th bit is 1 then we need to find 0 bit for max xor
            // if no 0 bit in left, then move to right(not max xor)
            // else do 1 xor 0 = 1, and calculates the value of max_xor
            // by adding 2^i
            if (!it->left)
                it = it->right;
            else {
                max_xor += pow(2, i);
                it = it->left;
            }
        }
    }
    
    return max_xor;
}

int findMaximumXor(vector<int>& nums) {
    int max_xor = 0;
    Trie* root = new Trie();
    
    // create bit-trie in O(n)
    for(int num: nums)
        insert(root, num); // O(1)
    
    // Time Complexity: O(n)
    for(int num: nums) {
        // find max xor for current num in O(1)
        int maxXorNum = findMaximumXorBitTrie(root, num);
        
        // compare & update current num max xor with global max_xor
        max_xor = max(max_xor, maxXorNum);
    }
    
    return max_xor;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for(int& num: nums) cin >> num;
    
    int max_xor = findMaximumXor(nums);
    cout << max_xor << "\n";
    
    return 0;
}
