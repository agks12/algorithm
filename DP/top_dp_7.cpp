//Bottom-Up 
#include<iostream>
#include<vector>

using namespace std;
int N, M, H;
vector<int>v[51];
long memo[51][1001];


int main() {
	//freopen("10.in", "r", stdin);
	//freopen("10.out", "w", stdout);
	cin >> N >> M >> H;
	for (int i = 1; i < N+1; i++) {
		for (int j = 0; j < M; j++) {
			int now;
			cin >> now;
			if (now != -1) {
				v[i].push_back(now);
			}
		}
	}
	for (int i = 0; i <= N; i++)memo[i][0] = 1;
	for (int i = 1; i < N+1; i++) {
		for (int j = 1; j < H + 1; j++) {
			for (int k = 0; k < v[i].size(); k++) {
				int block = v[i][k];
				if (j - block >= 0) {
					memo[i][j] = memo[i][j] + memo[i - 1][j - block];
				}
				
			}
			memo[i][j] = memo[i][j] + memo[i - 1][j];
		}
	}

	cout << memo[N][H];
	return 0;
}
 

//Top-Down
#include <iostream>
#include <vector>
using namespace std; 

int N, M, H; 
int blocks[50][10] = { 0, }; 
long dp[50][1001]; 

long func(int idx, int height) {
	if (height == 0)
		return 1; 

	if (idx >= N || height < 0)
		return 0;

	if (dp[idx][height] != 0)
		return dp[idx][height]; 

	long cnt = 0;
	// 안둔다
	cnt += func(idx + 1, height); 
	
	// 일단 둔다
	for (int i = 0; i < M; i++) {
		if (blocks[idx][i] == -1)
			continue;
		cnt += func(idx+1, height - blocks[idx][i]);
	}

	dp[idx][height] = cnt;
	return dp[idx][height];
}

int main() {
	cin >> N >> M >> H; 
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> blocks[i][j]; 
		}
	}
	cout << func(0, H);
}
