#include<iostream>
using namespace std;

int n,m;
int arr[10];

void dfs1(int level) {

	if (level == n) {
		for (int i = 0; i < level; i++) {
			cout << arr[i]<<" ";
		}
		cout << "\n";
		return;
	}

	// 주사위는 6개-for루프 개수
	for (int i = 1; i <= 6; i++) {
		arr[level] = i;
		dfs1(level + 1);
	}
}

void dfs2(int level) {

	if (level == n) {
		for (int i = 0; i < level; i++) {
			cout << arr[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 1; i <= 6; i++) {
		if (level != 0 && arr[level - 1] > i)continue;
		arr[level] = i;
		dfs2(level + 1);
	}
}

int visited[10];

void dfs3(int level) {

	if (level == n) {
		for (int i = 0; i < level; i++) {
			cout << arr[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 1; i <= 6; i++) {
		if (visited[i] == 1)continue;
		visited[i] = 1;
		arr[level] = i;
		dfs3(level + 1);
		visited[i] = 0;
	}
}

int main() {

	cin >> n >> m;

	if (m == 1) {
		dfs1(0);
	}
	else if (m == 2) {
		dfs2(0);
	}
	else if (m == 3) {
		dfs3(0);
	}


	return 0;
}
