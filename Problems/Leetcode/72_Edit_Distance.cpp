#include <bits/stdc++.h>
using namespace std;

int minEditDistance(string& s1, string& s2) {
    // for each step we've 3 choices
    // - insert: insert any letter in s1 to match s2 at i'th step
    // - delete: delete any letter from s1 to match s2 at i'th step
    // - replace: replace any letter in s1 to match s2 at i'th step
    
    // so we want best cost of all 3 operations at i'th step
    // apply DP on all 3 and find the best of all 3 at i'th step
    
    // State Definition
    // Tbl(i, j): represent the minimum number of operations needed
    //              for converting s1 of length i into s2 of length j
    
    // Bottom Up (Tabulation)
    
    const int m = s1.length();
    const int n = s2.length();
    
    vector<vector<int>> tbl(m+1, vector<int>(n+1));
    
    for(int i=0; i<=m; i++) {
        for(int j=0; j<=n; j++) {
            // if any of them is zero then operations is
            // delete i elements from s1 or insert j elements in s1
            if(i==0 || j==0)
                tbl[i][j] = i+j;
            
            // if letters are equal then no operation is performed
            else if(s1[i-1] == s2[j-1])
                tbl[i][j] = tbl[i-1][j-1];
                
            // if letters are not equal then
            // above all 3 operation, choose the one with minimum operations
            else
                tbl[i][j] = 1 + min({tbl[i][j-1],       // insert operation
                                    tbl[i-1][j],        // delete operation
                                    tbl[i-1][j-1]});    // replace operation
        }
    }
    
    return tbl[m][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string word1, word2;
    cin >> word1 >> word2;
    cin.ignore();
    
    int minDist = minEditDistance(word1, word2);
    cout << minDist << "\n";
    
    return 0;
}
