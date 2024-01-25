#include<iostream>
using namespace std;

int parent[100005];
int arr[100005];
int Find(int num) {
	if (num == parent[num])return num;
	return parent[num] = Find(parent[num]); // 경로압축
	// return Find(parent[num]) 이거 하면 시간초과됨
}
int main() {
	int T,n; cin >> T >> n;
	int cnt = 0;
	int stop = 0;
	for (int i = 1; i <= T; i++) parent[i] = i;
	for (int i = 0; i < n; i++) cin >> arr[i];
	for (int i = 0; i < n; i++) {
		int rootA = Find(arr[i]);
		int rootB = rootA-1;
		if (rootA==0)break;
		parent[rootA] = rootB;
		//Union(rootA, rootB); 간단해서 직접함
		cnt++;
	}
	cout << cnt;
	return 0;
}
