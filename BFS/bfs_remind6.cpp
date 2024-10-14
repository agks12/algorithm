#include<iostream>
#include<queue>
#include<vector>
#include<string.h>
using namespace std;

struct Pair { int row, col; };

Pair stPoi;
vector<Pair> v;
int N, cnt;
char map[21][21];
int visited[21][21];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
int minim = 21e8;

int bfs(Pair st) {
    queue<Pair> q;
    queue<int> turn;
    q.push(st);
    turn.push(1);
    visited[st.row][st.col] = 1;

    int score = 0;

    while (!q.empty()) {
        Pair now = q.front(); q.pop();
        int nowTurn = turn.front(); turn.pop();
        for (int i = 0; i < 4; i++) {
            int nextRow = now.row + dr[i];
            int nextCol = now.col + dc[i];
            if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N)continue;
            if (visited[nextRow][nextCol] == 1)continue;
            if (map[nextRow][nextCol] == '#')continue;
            visited[nextRow][nextCol] = 1;

            if (nextRow == stPoi.row && nextCol == stPoi.col)score += nowTurn;
            if (map[nextRow][nextCol] == '$') {
                score += nowTurn;
                continue;
            }

            q.push({ nextRow,nextCol });
            turn.push(nowTurn + 1);
        }
    }
    return score;
}

void search() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (map[i][j] == 'A')v.push_back({ i,j });
    cnt = v.size();
}

void reset() {
    for (int i = 0; i < N; i++) {
        memset(visited[i], 0, N * sizeof(int));
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++)cin >> map[i];
    cin >> stPoi.row >> stPoi.col;
    search();
    for (int i = 0; i < cnt; i++) {
        Pair nowPoi = v[i];
        int ans = bfs(nowPoi);
        if (ans < minim)minim = ans;
        reset();
    }

    cout << minim;
    return 0;
}
