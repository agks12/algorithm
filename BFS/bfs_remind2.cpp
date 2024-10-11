#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node { 
    int node, turn;
    bool operator<(Node right) const {
        if (right.node < node)return true;
        if (right.node > node)return false;
        return false;
    }
};


priority_queue<Node> pq;

int N, M, K, P;
vector<int> v[200001];
int visited[200001];


void bfs(int st) {
    queue<Node> q;
    q.push({ st,0 });
    visited[st] = 1;

    while (!q.empty()) {
        Node now = q.front(); q.pop();
        int nowNode = now.node;
        int nowTurn = now.turn;

        // 무조건 3턴 다 끝나고 4턴 시작이므로 4턴 시작시 끝냄
        if (nowTurn > K)return;
        
        int nowSize = v[nowNode].size();

        for (int i = 0; i < nowSize; i++) {
            int nextNode = v[nowNode][i];
            if (visited[nextNode] == 1)continue;
            visited[nextNode] = 1;

            if (K == nowTurn + 1) {
                //pq에 저장
                pq.push({ nextNode,0 });
            }

            q.push({ nextNode,nowTurn + 1 });
        }

    }
}

int main() {

    cin >> N >> M >> K >> P;
    for (int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;
        v[from].push_back(to);
    }

    bfs(P);

    if (pq.empty()) {
        cout << -1;
    }
    else {
        while (!pq.empty()) {
            Node nowNode = pq.top(); pq.pop();
            cout << nowNode.node << "\n";
        }
    }


    return 0;
}
