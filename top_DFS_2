#include<iostream>
using namespace std;

int arr[101][101];
int visited[101];

void dfs(int n, int start) {
	cout << start << " ";
	for (int i = n; i >= 1; i--) {
		if (arr[start][i] == 0)continue;
		if (visited[i] == 1)continue;
		visited[i] = 1;
		dfs(n, i);
	}
}

void redfs(int n, int start) {
	for (int i = n; i >= 1; i--) {
		if (arr[start][i] == 0)continue;
		if (visited[i] == 1)continue;
		visited[i] = 1;
		redfs(n, i);
	}
	cout << start << " ";
}

int main(){
	int n, k,startNode;
	cin >> n >> k>>startNode;
	for (int i = 0; i < k; i++) {
		int from, to;
		cin >> from >> to;
		arr[from][to] = 1;
		//양방향 해도될것 같지만 예외있음
		//arr[to][from] = 1;
	}

	visited[startNode] = 1;
	dfs(n, startNode);

	cout << "\n";
	for (int i = 0; i <= n; i++) {
		visited[i] = 0;
	}

	visited[startNode] = 1;
	redfs(n, startNode);
	


	return 0;
}
