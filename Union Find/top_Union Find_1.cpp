#include<iostream>
using namespace std;

int parent[1001];

int Find(int a) {
	if (parent[a] == a)return a;
	return Find(parent[a]);
}

void Union(int a, int b) {
	int rootA = Find(a);
	int rootB = Find(b);
	if (rootA == rootB)return;
	parent[rootA] = rootB;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i <= n; i++)parent[i]=i;

	for (int i = 0; i < m; i++) {
		int stu, a, b;
		cin >> stu >> a >> b;
		if (stu == 1)Union(a,b);
		else {
			if (Find(a) == Find(b))cout << "YES\n";
			else cout << "NO\n";
		}
	}

	return 0;
}
