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
    return (rand() % 2 == 0) ? false : true;
}

void generate(std::string caseSuffix, int minimumN, int maximumN, std::string method) {
    std::ofstream fout("cases/case" + caseSuffix + ".in");
    const int n = randBetween(minimumN, maximumN);
    const int m = randBetween(1, n);
    const int maxWeight = 1e3;
    const int maxTimes = 1e3;

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
    else if (method == "onestar") {
        int root = randBetween(1, n);
        int currentNode = 1;
        for (int i = 1; i <= n - 1; i++) {
            if (currentNode == root) currentNode++;
            int weight = randBetween(1, maxWeight);
            fout << currentNode++ << " " << root << " " << weight << '\n';
        }
    }
    else if (method == "twostars") {
        int root1 = randBetween(1, n);
        int root2 = randBetween(1, n - 1);
        if (root2 == root1) root2++; // Makes sure that the roots will be different

        int weight = randBetween(1, maxWeight);
        fout << root1 << " " << root2 << " " << weight << '\n'; // Edge between the two roots

        for (int node = 1; node <= n; node++) {
            if (node == root1 || node == root2) continue;
            int selectedRoot = (randDecision()) ? root1 : root2;
            weight = randBetween(1, maxWeight);
            fout << selectedRoot << " " << node << " " << weight << '\n';
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
    else if (method == "complete") {
        std::vector<int> nodes; // Will be the preorder of the tree
        nodes.push_back(0); // To be 1-indexed
        for (int i = 1; i <= n; i++) {
            nodes.push_back(i);
        }
        std::random_shuffle(nodes.begin() + 1, nodes.end());

        // i * 2 is left node
        // i * 2 + 1 is right node

        for (int i = 1; i * 2 + 1 <= n ; i++) {
            int weight = randBetween(1, maxWeight);
            fout << nodes[i] << " " << nodes[i * 2] << " " << weight << '\n';
            weight = randBetween(1, maxWeight);
            fout << nodes[i] << " " << nodes[i * 2 + 1] << " " << weight << '\n';
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
    const int minimumNSet1 = 900;
    const int maximumNSet1 = 1000;

    const int minimumNSet2 = 7 * 1e4;
    const int maximumNSet2 = 1e5;

    const int minimumNSet3 = 7 * 1e4;
    const int maximumNSet3 = 1e5;
    for (int i = 1; i <= 20; i++) {
        if (i <= 6) {
            if (i <= 3)
                generate(std::to_string(i), minimumNSet1, maximumNSet1, "random");
            else if (i == 4)
                generate(std::to_string(i), minimumNSet1, maximumNSet1, "onestar");
            else if (i == 5)
                generate(std::to_string(i), minimumNSet1, maximumNSet1, "twostars");
            else
                generate(std::to_string(i), ((1 << 9) - 1), ((1 << 9) - 1), "complete");
        }
        else if (i <= 10) {
            generate(std::to_string(i), minimumNSet2, maximumNSet2, "line");
        }
        else if (i <= 20) {
            if (i <= 14)
                generate(std::to_string(i), minimumNSet3, maximumNSet3, "random");
            else if (i <= 16)
                generate(std::to_string(i), minimumNSet3, maximumNSet3, "onestar");
            else if (i <= 18)
                generate(std::to_string(i), minimumNSet3, maximumNSet3, "twostars");
            else
                generate(std::to_string(i), ((1 << 16) - 1), ((1 << 16) - 1), "complete");
        }
            
    }
    return 0;
}