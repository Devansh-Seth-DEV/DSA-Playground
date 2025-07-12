#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> directions = {
	{-1, -2},	// 1-up, 2-left
    {1, -2}, 	// 1-up, 2-right
    {-2, -1}, 	// 2-left, 1-up
    {2, -1}, 	// 2-right, 1-up
	{-2, 1}, 	// 2-left, 1-down
    {2, 1}, 	// 2-right, 1-down
    {-1, 2}, 	// 1-down, 2-left
    {1, 2}		// 1-down, 2-right
};

int minimumMoves(char src[], char dest[]) {
    const int N = 8, M = 8;
    auto inBounds = [&](int x, int y) -> bool {
        return (x>=0 && x<N && y>=0 && y<M);
    };
    
    int level = 0;
    vector<vector<bool>> visited(8, vector<bool>(8, false));
    queue<pair<int, int>> que;
    
    pair<int, int> U = {8-(src[1]-'0'), src[0]-'a'}; // src node
    pair<int, int> V = {8-(dest[1]-'0'), dest[0]-'a'}; // dest node
    
    // if source and destination are same then no need to traverse further
    // return 0 in that case
    if (U==V) return 0;
    
    // performing BFS on source node U
    que.push(U);
    visited[U.first][U.second] = true;
    
    while(!que.empty()) {
        int size = que.size();
        
        while(size--) {
            auto p = que.front();
            que.pop();
            int x = p.first, y = p.second;
            
            for(auto& dir: directions) {
                int x_ = x + dir.first;
                int y_ = y + dir.second;
                
                if (inBounds(x_, y_) && !visited[x_][y_]) {
                    if(x_ == V.first && y_ == V.second)
                        return level+1;
                    que.push({x_, y_});
                    visited[x_][y_] = true;
                }
            }
        }
        
        level++;
    }
    
    return -1; // unreachable
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while(T--) {
        char src[3];
        char dest[3];
        
        cin >> src[0] >> src[1] >> dest[0] >> dest[1];
        src[2] = '\0', dest[2] = '\0';
        
        int moves = minimumMoves(src, dest);
        cout << moves << "\n";
    }
    
    return 0;
}
