#include<iostream>
using namespace std;

int visited[11];
int cnt;
void back(int n,int level) {
	if (level == n) {
		cnt++;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (visited[i] == 1)continue;
		visited[i] = 1;
		back(n, level + 1);
		visited[i] = 0;
	}
}
int main() {
	int n; cin >> n;
	back(n,0);
	cout << cnt;
	return 0;
}
