#include<iostream>
using namespace std;

int parent[10001];
int visited[30];

int Find(int num) {
	if (num == parent[num])return num;
	return Find(parent[num]);
}
void Union(int a, int b) {
	int rootA = Find(a);
	int rootB = Find(b);
	if (rootA == rootB)return;
	parent[rootA] = rootB;
}

int main() {
	int N;
	cin >> N;
	int sum = 0;
	int teamCnt = 0;
	int flag = -1;

	for (int i = 0; i < 26; i++)parent[i] = i;
	for (int i = 0; i < N; i++) {
		char a, b;
		cin >> a >> b;
		int transA = int(a) - 65;
		int transB = int(b) - 65;
		visited[transA] = 1;
		visited[transB] = 1;
		Union(transA, transB);
	}

	for (int i = 0; i < 26; i++) {

		if (visited[i] == 1) {
			int now = Find(i);
			if (now == flag)continue;
			flag = now;
			teamCnt++;
		}
		if(visited[i]==0)sum++;
	}
	cout << teamCnt<<"\n";
	cout << sum;

	return 0;
}
