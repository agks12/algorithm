#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<cstring>
using namespace std;

int tc, n, m, hp, Srow, Scol, Trow, Tcol, Yrow, Ycol, Mrow, Mcol;
char arr[51][51];
int visited[51][51];

struct Pair { int row, col; };
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string a;
		cin >> a;
		for (int j = 0; j < m; j++) {
			char now = a[j];
			arr[i][j] = now;
			if (now == 'S') {
				Srow = i;
				Scol = j;
			}
			if (now == 'T') {
				Trow = i;
				Tcol = j;
			}
			if (now == 'Y') {
				Yrow = i;
				Ycol = j;
			}
			if (now == 'M') {
				Mrow = i;
				Mcol = j;
			}
			visited[i][j] = 0;
		}
	}
	cin >> hp;
}

int bfs(int strow ,int stcol) {
	queue<Pair> q;
	q.push({ strow,stcol });
	visited[strow][stcol] = 0;
	int WtoY = -1;
	int WtoM = -1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextrow = now.row + dr[i];
			int nextcol = now.col + dc[i];
			if (nextrow < 0 || nextcol < 0 || nextrow >= n || nextcol >= m)continue;
			if (visited[nextrow][nextcol] > 0)continue;
			if (arr[nextrow][nextcol] == 'x')continue;
			visited[nextrow][nextcol] = visited[now.row][now.col] + 1;

			if (nextrow == Yrow && nextcol == Ycol)WtoY = visited[nextrow][nextcol];
			if (nextrow == Mrow && nextcol == Mcol)WtoM = visited[nextrow][nextcol];

			//용사나 마왕으로 이어지는거 없느면 이 무기는 사용불가 
			if (WtoY != -1 && WtoM != -1)return WtoY + WtoM;

			q.push({ nextrow,nextcol });
		}
	}
	return -1;
}
int main() {
	cin >> tc;
	for (int testCase = 1; testCase <= tc; testCase++) {
		input();
		//칼에서 시작해서 칼에서 사람 + 칼에서 보스 < 나무에서 사람 + 나무에서 보스
		// 무조건 2번? ss 마왕에서 시작하면 됨 ss 마왕에서 시작하면 안됨 최소경로중복? 같은거때매
		int Sstart = bfs(Srow,Scol);
		for (int i = 0; i < n; i++) memset(visited[i], 0, n * sizeof(int));
		int Tstart = bfs(Trow,Tcol);
		int Yactive = hp/5;
		int Tactive = hp/2;
		if (hp % 5 != 0) Yactive += 1;
		if (hp % 2 != 0) Tactive += 1;
		cout << "#" << testCase << " ";
		if (Sstart == -1 && Tstart == -1)cout << "the world is doomed\n";
		else if (Sstart == -1) cout << Tstart + Tactive << "\n";
		else if (Tstart == -1) cout << Sstart + Yactive << "\n";
		else {
			if (Tstart + Tactive > Sstart + Yactive)cout << Sstart + Yactive << "\n";
			else cout << Tstart + Tactive << "\n";
		}
	}
	return 0;
}
