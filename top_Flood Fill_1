#include<iostream>
#include<queue>
using namespace std;

struct Pair {
	int row,col;
};

int visited[6][6];
int arr[6][6];
int dr[4] = { -1,0,0,1 };
int dc[4] = { 0,1,-1,0 };
queue<Pair> q;

void ff(int row, int col) {
	q.push({ row,col });
	arr[row][col] = 1;
	visited[row][col] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= 5 || nextCol >= 5)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			visited[nextRow][nextCol] = 1;
			arr[nextRow][nextCol] = arr[now.row][now.col]+1;
			q.push({ nextRow,nextCol });
		}
	}
}

int main() {
	int y, x;
	cin >> y >> x;

	ff(y, x);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << arr[i][j]<<" ";
		}
		cout << "\n";
	}
	return 0;
}
