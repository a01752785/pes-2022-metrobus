#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <stdlib.h>

class UnionFind {
private:
    std::vector<int> link;
    std::vector<int> setSize;

    int getRoot(int u) {
        if (link[u] == u) return u;
        else return link[u] = getRoot(link[u]);
    }

public:
    UnionFind(int n) {
        link.resize(n + 1);
        setSize.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            link[i] = i;
            setSize[i] = 1;
        }
    }

    void unite(int a, int b) {
        a = getRoot(a);
        b = getRoot(b);
        if (a == b)
            return;
        if (setSize[b] > setSize[a])
            std::swap(a, b);
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

bool randDecision() {
    return (bool) rand() % 2;
}

void generate(std::string caseSuffix, int minimumN, int maximumN, std::string method) {
    std::ofstream fout("cases/case" + caseSuffix + ".in");
    const int n = randBetween(minimumN, maximumN);
    const int m = randBetween(1, n);
    const int maxWeight = 1e4;
    const int maxTimes = 1e4;

    // Part 1 - Generate tree

    fout << n << '\n';
    if (method == "random") {
        std::vector<int> nodes;
        for (int i = 1; i <= n; i++) {
            nodes.push_back(i);
        }
        std::random_shuffle(nodes.begin(), nodes.end());
        std::queue<int> pending;
        for (int node : nodes) {
            pending.push(node);
        }
        while (pending.size() > 1) {
            int nodeA = pending.front(); pending.pop();
            int nodeB = pending.front(); pending.pop();
            int weight = randBetween(1, maxWeight);

            fout << nodeA << " " << nodeB << " " << weight << '\n';

            // Pick one randomly to become the root of the component
            if (randDecision()) 
                std::swap(nodeA, nodeB);
            pending.push(nodeA);
        }
    }
    else if (method == "star") {
        int root = randBetween(1, n);
        int currentNode = 1;
        for (int i = 1; i <= n - 1; i++) {
            if (currentNode == root) currentNode++;
            int weight = randBetween(1, maxWeight);
            fout << currentNode++ << " " << root << " " << weight << '\n';
        }
    }
    else if (method == "line") {
        std::vector<int> nodes;
        for (int i = 1; i <= n; i++) {
            nodes.push_back(i);
        }
        std::random_shuffle(nodes.begin(), nodes.end());
        for (int i = 1; i <= n - 1; i++) {
            int weight = randBetween(1, maxWeight);
            fout << nodes[i - 1] << " " << nodes[i] << " " << weight << '\n';
        }
    }
    // Part 2 - Generate destination nodes

    fout << m << '\n';
    std::vector<int> destinationNodes;
    for (int i = 1; i <= n; i++) {
        destinationNodes.push_back(i);
    }
    std::random_shuffle(destinationNodes.begin(), destinationNodes.end());

    for (int i = 0; i < m; i++) {
        int times = randBetween(1, maxTimes);
        fout << destinationNodes[i] << " " << times << '\n';
    }
    fout.close();
}

int main() {
    generate("21", 10, 10, "line");
    return 0;
    const int minimumNSet1 = 900;
    const int maximumNSet1 = 1000;

    const int minimumNSet2 = 7 * 1e4;
    const int maximumNSet2 = 1e5;

    const int minimumNSet3 = 7 * 1e4;
    const int maximumNSet3 = 1e5;
    for (int i = 2; i <= 20; i++) {
        if (i <= 6)
            generate(std::to_string(i), minimumNSet1, 5, "random");
        else if (i <= 10)
            generate(std::to_string(i), minimumNSet2, maximumNSet2, "random");
        else if (i <= 20)
            generate(std::to_string(i), minimumNSet3, maximumNSet3, "random");
    }
    return 0;
}