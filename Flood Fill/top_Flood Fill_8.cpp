#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair { int row, col; };
int n, m, Max, cntA,cntB;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
char arr[201][201];
int floodfill(int strow,int stcol,char nowchr) {
	int cnt = 0;
	queue<Pair> q;
	q.push({ strow,stcol });
	arr[strow][stcol] = '_';
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		cnt++;
		for (int i = 0; i < 4; i++) {
			int nextrow = now.row + dr[i];
			int nextcol = now.col + dc[i];
			if (nextrow < 0 || nextcol < 0 || nextrow >= n || nextcol >= m)continue;
			if (arr[nextrow][nextcol] == '_')continue;
			if (arr[nextrow][nextcol] != nowchr)continue;
			arr[nextrow][nextcol] = '_';
			q.push({ nextrow,nextcol });
		}
	}
	return cnt;
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == '_')continue;
			if (arr[i][j] == 'A')cntA++;
			else cntB++;
			int ans = floodfill(i,j,arr[i][j]);
			if (ans > Max)Max = ans;
		}
	}
	cout << cntA<<" " << cntB << "\n" << Max;
	return 0;
}
