#include<iostream>
using namespace std;

int parent[1001];

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
	int n;
	int now;
	int flag = 0;
	cin >> n;
	for (int i = 0; i < n; i++)parent[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> now;
			if (now == 0)continue;
			if (Find(i) == Find(j))flag = 1;
			if (i > j)Union(i, j);
		}
	}
	if (flag == 1)cout << "WARNING";
	else cout << "STABLE";
	
	return 0;
}
