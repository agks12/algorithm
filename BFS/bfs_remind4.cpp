#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node { int to, cost; };
vector<Node> v[100001];
int visited[100001];
int n, m, k;

int bfs() {
    queue<Node> q;
    q.push({ 1,0 });
    visited[1] = 0;
    int cnt = 0;

    while (!q.empty()) {
        Node now = q.front(); q.pop();
        int nowNode = now.to;
        int nowCost = now.cost;
        int nowSize = v[nowNode].size();
        //cout<<nowSize;
        // nowCost + nextCost 해야 계속 누적
        for (int i = 0; i < nowSize; i++) {
            int nextNode = v[nowNode][i].to;
            int nextCost = v[nowNode][i].cost;
            if (visited[nextNode] == 1)continue;
            visited[nextNode] == 1;
            int totalCost = nowCost + nextCost;
            if (totalCost > k)continue;
            cnt++; //갈수 있음
            q.push({ nextNode,totalCost });
        }
    }
    return cnt;
}

int main() {
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        v[from].push_back({ to,cost });
    }

    int ans = bfs();
    cout << ans;
    return 0;
}
