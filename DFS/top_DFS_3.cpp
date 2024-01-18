#include<iostream>
#include<vector>
using namespace std;

vector<int> v[1001];
int visited[1001];
//int arr[101][101];
// 
//이진트리구조여서 벡터가 편함
//무조건 한방향이므로 visited필요x

//예전
//void dfs1(int level)
//{
//	if (level == -1)return;
//
//	for (int i = 0; i < 2; i++)
//	{
//		//if (arr[level][i] == -1)continue;
//
//		dfs1(arr[level][i]);
//		if (arr[level][i] != -1 && visited[arr[level][i]] == 0)
//		{
//			cout << arr[level][i] << " ";
//			visited[arr[level][i]] = 1;
//		}
//		if (level != -1 && visited[level] == 0)
//		{
//			cout << level << " ";
//			visited[level] = 1;
//		}
//	}
//}

void dfs1(int n, int start) {
	for (int i = 0; i < 2; i++) {
		
		//
		if (v[start][0] == -1 and v[start][1] != -1 and visited[start]==0) {
			cout << start << " ";
			visited[start]+=2;
			continue;
		}
		//여기아래는 지금왼쪽아래가 -1이 아닌거라고 가정하고 왼쪽아래->중앙->오른쪽아래
		//하는거라서 위에거로 지금왼쪽아래 -1인경우 고려함
		if (v[start][i] == -1)continue;
		if (visited[start] == 1) {
			cout << start << " ";
		}
		visited[start]++;
		dfs1(n, v[start][i]);
	}
	if (visited[start] <= 1) {
		cout << start << " ";
		visited[start]++;
	}
}

void dfs2(int n, int start) {
	cout << start << " ";
	for (int i = 0; i < 2; i++) {
		if (v[start][i] == -1)continue;
		dfs2(n, v[start][i]);
	}
}

void dfs3(int n, int start) {
	for (int i = 0; i < 2; i++) {
		if (v[start][i] == -1)continue;
		dfs3(n, v[start][i]);
	}
	cout << start << " ";
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i<n; i++) {
		int from, left, right;
		cin >> from >> left >> right;
		v[from].push_back(left);
		v[from].push_back(right);
	}

	dfs1(n, 1);
	cout << "\n";
	dfs2(n, 1);
	cout << "\n";
	dfs3(n, 1);
	return 0;
}
