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
        int n;
        cin >> n;

        int arr[101];
        for(int i=0; i<n; i++) cin >> arr[i];

        auto result = process(n, arr);
        printer.print(result);
    }

    int process(int n, int (&arr)[101]) {
        int result = 0;
        int totalNegOnes = 0;
        int totalPosOnes = 0;

        for(int i=0; i<n; i++) {
            if (arr[i]<0) totalNegOnes++;
            else totalPosOnes++;
        }

        if (!iseven(totalNegOnes)) {
                result++;
                totalNegOnes--;
                totalPosOnes++;
        }
        
        while (totalNegOnes > totalPosOnes) {
            totalNegOnes -= 2;
            totalPosOnes += 2;
            result += 2;
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