#include <bits/stdc++.h>
using namespace std;

inline void asyncIosStream() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    asyncIosStream();
	
    int boxes[100] = {0};
    
    int testCases;
    cin >> testCases;
    
    while(testCases--) {
        int n, k;
        bool isAllEqual = true;
        
		cin >> n >> k;
        
        for(int i=0; i<n; i++) {
            cin >> boxes[i];
            if (isAllEqual && i>0 && boxes[i-1] > boxes[i])
                isAllEqual = false;
        }
        
        if (1==k && !isAllEqual) cout << "NO\n";
        else cout << "YES\n";
    }
}
