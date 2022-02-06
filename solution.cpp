#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define maxn 100005

struct edge {
    ll to;
    ll w;
    edge (ll to, ll w) {
        this -> to = to;
        this -> w = w;
    }
};
vector<edge> adjList[maxn];
ll totalFreq[maxn];
ll freq[maxn];
ll dist[maxn];

ll costFor1stRoot(ll u, ll p) {
    totalFreq[u] += freq[u]; // Computes total frequency
    ll total = (ll) freq[u] * (ll) dist[u]; // Adds current travel to the total
    for (edge e : adjList[u]) {
        ll v = e.to;
        if (v == p) continue;
        dist[v] = dist[u] + e.w; // Computes distance to each node
        total += costFor1stRoot(v, u); // Adds travels from child to current node
        totalFreq[u] += totalFreq[v]; // Adds frequency from the child to current node
    }
    return total;
}

void rotate(ll u, ll p, ll currentTotal, vector<ll>& totalCost) {
    totalCost[u] = currentTotal;
    for (edge e : adjList[u]) {
        ll v = e.to;
        if (v == p) continue;
        // For each child, we convert it to the new 
        currentTotal -= (ll) totalFreq[v] * e.w; // the frequency of v does not need to pass the edge v to u
        totalFreq[u] -= totalFreq[v]; // u is now a child from v
        currentTotal += (ll) totalFreq[u] * e.w; // the frequency of u needs to pass the edge u to v
        totalFreq[v] += totalFreq[u]; // u is now a child from v
        rotate(v, u, currentTotal, totalCost);
        // Once we return from v, u has to be the root again
        totalFreq[v] -= totalFreq[u];
        currentTotal -= (ll) totalFreq[u] * e.w;
        totalFreq[u] += totalFreq[v];
        currentTotal += (ll) totalFreq[v] * e.w;
    }
}

int main() {
    ll n;
    cin >> n;
    for (ll i = 1; i <= n - 1; i++) {
        ll a, b, w;
        cin >> a >> b >> w;
        adjList[a].push_back(edge(b, w));
        adjList[b].push_back(edge(a, w));
    }
    ll m;
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        ll to, times;
        cin >> to >> times;
        freq[to] = times;
    }
    
    ll firstCost = costFor1stRoot(1, 0);
    ll minimum = LLONG_MAX;
    vector<ll> totalCost(n + 1, 0); // To store the total cost of each place
    vector<ll> answer;
    rotate(1, 0, firstCost, totalCost);
    
    for (ll i = 1; i <= n; i++) {
        if (totalCost[i] < minimum) {
            minimum = totalCost[i];
            answer.clear();
            answer.push_back(i);
        }
        else if (totalCost[i] == minimum) {
            answer.push_back(i);
        }
    }
    
    minimum = minimum * 2; // Each travel is round trip
    cout << minimum << '\n';
    for (ll i = 0; i < answer.size(); i++) {
        cout << answer[i];
        if (i < answer.size() - 1)
            cout << ' ';
    }
    cout << '\n';
    return 0;
}