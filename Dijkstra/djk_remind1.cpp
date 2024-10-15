#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node { 
    int to, time;
    bool operator<(Node right) const {
        if (right.time < time)return true;
        if (right.time > time)return false;
        if (right.to > to)return true;
        if (right.to < to)return false;
        return false;
    }
};

int N, M, P;
vector<Node> v[1001];
int visited[1001];
int dist[1001];
int dat[1001];

void djk(int st) {
    priority_queue<Node>q;
    q.push({ st,0 });
    dist[st] = 0;

    while (!q.empty()) {
        Node now = q.top(); q.pop();
        int nowSize = v[now.to].size();
        int nowTime = now.time;
        if (visited[now.to] == 1)continue;
        visited[now.to] = 1;
        for (int i = 0; i < nowSize; i++) {
            int nextNode = v[now.to][i].to;
            int nextTime = v[now.to][i].time;

            if (dist[now.to] + nextTime >= dist[nextNode])continue;
            dist[nextNode] = dist[now.to] + nextTime;

            q.push({ nextNode,dist[nextNode] });
        }
    }
}

void reset() {
    for (int i = 0; i <= N; i++) {
        dist[i] = 21e8;
        visited[i] = 0;
    }

}

int main() {
    cin >> N >> M >> P;

    for (int i = 0; i < M; i++) {
        int from, to, time;
        cin >> from >> to >> time;
        v[from].push_back({ to,time });
    }

    reset();
    djk(P);

    for (int i = 1; i <= N; i++) {
        dat[i] = dist[i];
    }


    int maxim = -1;

    for (int i = 1; i <= N; i++) {
        if (i == P)continue;
        reset();
        djk(i);
        dat[i] += dist[P];

        if (dat[i] > maxim)maxim = dat[i];
    }

    cout << maxim;

    return 0;
}
