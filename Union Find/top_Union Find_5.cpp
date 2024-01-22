#include<iostream>
using namespace std;

int parent[1000001];
int cnt[1000001];
int visited[1000001];
int maxm = 1;
int Find(int num) {
	if (parent[num] == num)return num;
	return Find(parent[num]);
}
void Union(int a, int b) {
	int rootA = Find(a);
	int rootB = Find(b);
	if (rootA == rootB)return;
	parent[rootA] = rootB;
	cnt[rootB] += cnt[rootA];
	cnt[rootA] = 0;
	if (cnt[rootB] > maxm)maxm = cnt[rootB];
}
int main() {
	int w, n; cin >> w >> n;
	int nowcnt = 0;
	for (int i = 0; i < w; i++) {
		parent[i] = i;
		cnt[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		int in; cin >> in;
		//한쪽만 합쳐지면 전체 집은 그대로 두쪽다 합쳐지면 -1
		//두쪽다 아니면 +1
		int judg = 0;
		if (in != 0 && visited[in - 1] == 1) {
			Union(in, in - 1);
			judg++;
		}
		if (visited[in + 1] == 1) {
			Union(in, in + 1);
			judg++;
		}
		visited[in] = 1;
		if (judg == 0) nowcnt++;
		else if (judg == 2) nowcnt--;
		cout << nowcnt << " "<<maxm<<"\n";
	}
	return 0;
}
