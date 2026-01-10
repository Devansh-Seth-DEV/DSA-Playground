#include <bits/stdc++.h>
using namespace std;

inline void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
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
        int n;
        cin >> n;

        vector<int> seqB(n);
        for(int& b: seqB) cin >> b;

        auto result = process(n, seqB);

        printer.print(result.size());
        printer.print(result);
    }

    vector<int> process(int n, vector<int>& seqB) {
        vector<int> result;
        
        result.push_back(seqB[0]);
        for(int i=1; i<n; i++) {
            if (seqB[i] >= seqB[i-1])
                result.push_back(seqB[i]);
            else {
                result.push_back(seqB[i]);
                result.push_back(seqB[i]);
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