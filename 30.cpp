#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define maxn 50005

struct edge {
    int to;
    int w;
    edge (int to, int w) {
        this -> to = to;
        this -> w = w;
    }
};
vector<edge> adjList[maxn];
int totalFreq[maxn];
int freq[maxn];
int dist[maxn];

ll costFrom(ll u, ll p) {
    totalFreq[u] += freq[u]; // Computes total frequency
    ll total = (ll) freq[u] * (ll) dist[u]; // Adds current travel to the total
    for (edge e : adjList[u]) {
        ll v = e.to;
        if (v == p) continue;
        dist[v] = dist[u] + e.w; // Computes distance to each node
        total += costFrom(v, u); // Adds travels from child to current node
        totalFreq[u] += totalFreq[v]; // Adds frequency from the child to current node
    }
    return total;
}

int main() {
    int t = 1;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            adjList[i].clear();
            freq[i] = 0;
            totalFreq[i] = 0;
            dist[i] = 0;
        }
        for (int i = 1; i <= n - 1; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            adjList[a].push_back(edge(b, w));
            adjList[b].push_back(edge(a, w));
        }
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int to, times;
            cin >> to >> times;
            freq[to] = times;
        }
        ll minimum = LLONG_MAX;
        vector<int> totalCost(n + 1, 0); // To store the total cost of each place
        vector<int> answer;
        
        for (int i = 1; i <= n; i++) {
            for (int u = 1; u <= n; u++) {
                totalFreq[u] = 0;
                dist[u] = 0;
            }
            ll cost = costFrom(i, 0);
            if (cost < minimum) {
                answer.clear();
                answer.push_back(i);
                minimum = cost;
            }
            else if (cost == minimum) {
                answer.push_back(i);
            }
        }
        
        minimum = minimum * 2; // Each travel is round trip
        cout << minimum << '\n';
        for (int i = 0; i < answer.size(); i++) {
            cout << answer[i];
            if (i < answer.size() - 1)
                cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}