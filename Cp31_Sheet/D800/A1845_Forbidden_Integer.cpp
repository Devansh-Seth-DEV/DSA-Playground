#include <bits/stdc++.h>
using namespace std;

inline void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

inline bool iseven(long long val) {
    return (val&1)==0;
}

class Printer {
public:
    template <typename T>
    void print(const T& val, const char* end = "\n") {
        cout << val << end;
    }

    void print(bool val, const char* end = "\n") {
        cout << (val ? "YES" : "NO") << end;
    }

    void print(const char* s, const char* end = "\n") {
        cout << s << end;
    }

    void print(const string& s, const char* end = "\n") {
        cout << s << end;
    }

    template <typename T>
    void print(const vector<T>& vec, const char* end = "\n") {
        for (size_t i = 0; i < vec.size(); ++i)
            print(vec[i], i + 1 < vec.size() ? " " : "");
        cout << end;
    }

    void print(const vector<bool>& vec, const char* end = "\n") {
        for (size_t i = 0; i < vec.size(); ++i)
            print(vec[i], i + 1 < vec.size() ? " " : "");
        cout << end;
    }

    template <typename T, size_t N>
    void print(const T (&arr)[N], const char* end = "\n") {
        for (size_t i = 0; i < N; ++i)
            print(arr[i], i + 1 < N ? " " : "");
        cout << end;
    }

    template <size_t N>
    void print(const char (&arr)[N], const char* end = "\n") {
        for (size_t i = 0; i < N; ++i)
            print(arr[i], i + 1 < N ? " " : "");
        cout << end;
    }

    template <typename X, typename Y>
    void print(const pair<X, Y>& p, const char* end = "\n") {
        print(p.first, " ");
        print(p.second, end);
    }
};

class Solver {
private:
    Printer printer;

public:
    void execute() {
        int testCases = 1;
        cin >> testCases;
        while (testCases--) solve();
    }

    void solve() {
        int n, k, x;
        cin >> n >> k >> x;

        vector<int> vec;
        auto result = process(n, k, x, vec);

        printer.print(result);
        if (result) {
            printer.print(vec.size());
            printer.print(vec);
        }
    }

    bool process(int n, int k, int x, vector<int>& vec) {
        bool result = true;

        if (x!=1) {
            for(int i=0; i<n; i++)
                vec.push_back(1);
        } else {
            if (k==1 || (k==2 && !iseven(n)))
                result = false;
            else {
                if (iseven(n)) {
                    for(int i=0; i< n/2; i++)
                        vec.push_back(2);
                } else {
                    vec.push_back(3);
                    for(int i=0; i< (n-3)/2; i++)
                        vec.push_back(2);
                }
            }
        }
        
        return result;
    }
};

int main() {
    fastIO();
    Solver solver;
    solver.execute();
    return 0;
}