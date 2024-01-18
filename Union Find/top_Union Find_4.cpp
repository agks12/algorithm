#include<iostream>
using namespace std;

int parent[30];
int cnt[30];
int cntMan[30];

int Find(int num) {
	if (num == parent[num])return num;
	return Find(parent[num]);
}
void Union(int a, int b) {
	int rootA = Find(a);
	int rootB = Find(b);
	if (rootA == rootB)return;
	parent[rootA] = rootB;
	cnt[rootB] += cnt[rootA];
	cnt[rootA] = 0;
	cntMan[rootB] += cntMan[rootA];
	cntMan[rootA] = 0;
}
int main() {
	int n,t;
	int minus = 0;
	for (int i = 0; i < 26; i++) {
		parent[i] = i;
		cntMan[i] = 1;
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> cnt[i];
	}
	cin >> t;
	for (int i = 0; i < t; i++) {
		char a[10];
		char b, c;
		cin >> a >> b >> c;
		int traA = int(b) - 65;
		int traB = int(c) - 65;
		if (a[0] == 'a')Union(traA, traB);
		else {
			int oneA = Find(traA);
			int oneB = Find(traB);
			if (cnt[oneA] > cnt[oneB]) {
				cnt[oneB] = 0;
				minus+=cntMan[oneB];
				cntMan[oneB]=0;
			}
			else if (cnt[oneA] < cnt[oneB]) {
				cnt[oneB] = 0;
				minus += cntMan[oneA];
				cntMan[oneA]=0;
			}
			else if (cnt[oneA] == cnt[oneB]) {
				minus += cntMan[oneB];
				minus += cntMan[oneA];
				cntMan[oneB] = 0;
				cntMan[oneA] = 0;
				cnt[oneB] = 0;
				cnt[oneA] = 0;
			}
		}
	}
	cout << n - minus << "\n";
	return 0;
}
