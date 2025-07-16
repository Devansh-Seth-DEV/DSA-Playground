#include <bits/stdc++.h>
using namespace std;

int isPalindrome(string& s, int i, int j,
                vector<vector<int>>& memo) { // helper function
    if(i>=j) return 1;
    
    if (memo[i][j] != -1)
        return memo[i][j];
        
    if (s[i] == s[j])
        return memo[i][j] = isPalindrome(s, i+1, j-1, memo);
    return memo[i][j] = 0;
}

string longestPalindrome(string& s) {
    const int n = s.length();
    
    // memo(i, j) represent the state of substring from i-th to j-th index
    // -1: indicates state not processed
    // 1: indicates substring is palindrome
    // 0: indicates substring is not a palindrome
    vector<vector<int>> memo(n, vector<int>(n, -1));
    
    int substrMaxLen = 0, substrIdx = 0;
    
    for(int i=0; i<n; i++) {
        for(int j=i; j<n; j++) {
            // check each time the substring is palindrome of not
            // if the substring is palindrome & its len > substrMaxLen
            // then we'll update our maxLen & substrIdx to this new substring
            if(isPalindrome(s, i, j, memo)==1 && j-i+1 > substrMaxLen) {
                substrMaxLen = j-i+1;
                substrIdx = i;
            }
        }
    }
    
    // substring from i=th index till its maxLen
    return s.substr(substrIdx, substrMaxLen);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    cin.ignore();
    
    string palindromeStr = longestPalindrome(s);
    cout << palindromeStr << "\n";
    
    return 0;
}
