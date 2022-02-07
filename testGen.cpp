#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stdlib.h>

class UnionFind {
private:
    std::vector<int> link;
    std::vector<int> setSize;
    std::set<int> roots;

    int getRoot(int u) {
        if (link[u] == u) return u;
        else return link[u] = getRoot(u);
    }

public:
    UnionFind(int n) {
        link.resize(n + 1);
        setSize.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            link[i] = i;
            setSize[i] = i;
            roots.insert(i);
        }
    }

    void unite(int a, int b) {
        a = getRoot(a);
        b = getRoot(b);
        if (a == b)
            return;
        if (setSize[b] > setSize[a])
            std::swap(a, b);
        roots.erase(b); // b is no longer a root since will be connected to a
        link[b] = a;
        setSize[a] += setSize[b];
    }

    bool connected(int a, int b) {
        return getRoot(a) == getRoot(b);
    }
};

int randBetween(int a, int b) {
    return rand() % (b - a + 1) + a;
}

void generate(std::string caseSuffix, int minimumN, int maximumN) {
    std::ofstream fout("cases/case" + caseSuffix + ".in");
    const int n = randBetween(minimumN, maximumN);
    fout << n << '\n';
    for (int i = 0; i < n; i++) {
        int actNum = randBetween(1, 3);
        fout << actNum;
        if (i < n - 1) fout << ' ';
    }
    fout << '\n';
    fout.close();
}

int main() {
    const int minimumNSet1 = 1;
    const int maximumNSet1 = 200;

    const int minimumNSet2 = 1000;
    const int maximumNSet2 = 2500;

    const int minimumNSet3 = 5 * 1e5;
    const int maximumNSet3 = 7 * 1e5;
    
    const int minimumNSet4 = 1e6;
    const int maximumNSet4 = 1e6;
    for (int i = 1; i <= 20; i++) {
        if (i <= 4)
            generate(std::to_string(i), minimumNSet1, maximumNSet1);
        else if (i <= 8)
            generate(std::to_string(i), minimumNSet2, maximumNSet2);
        else if (i <= 16)
            generate(std::to_string(i), minimumNSet3, maximumNSet3);
        else 
            generate(std::to_string(i), minimumNSet4, maximumNSet4);
    }
    return 0;
}