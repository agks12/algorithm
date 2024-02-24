#include<iostream>
#include<vector>
using namespace std;

int n, m, x, cnt, under,front;
int possibleFront, possibleBack;
int arr[100001];
vector<int> vback[100001];
vector<int> vfront[100001];
int visited[100001];

void findunder(int now) {
	for (int i = 0; i < vback[now].size(); i++) {
		int next = vback[now][i];
		if (visited[next] == 1)continue;
		visited[next] = 1;
		under++;
		findunder(next);
	}
}
void findfront(int now) {
	for (int i = 0; i < vfront[now].size(); i++) {
		int next = vfront[now][i];
		if (visited[next] == 1)continue;
		visited[next] = 1;
		front++;
		findfront(next);
	}
}
int main() {
	cin >> n >> m >> x;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		vback[a].push_back(b);
		vfront[b].push_back(a);
	}
	findunder(x);
	for (int i = 0; i < n; i++)visited[i] = 0;
	findfront(x);
	possibleFront = front+1;
	possibleBack = n - under;
	cout << possibleFront <<"\n" << possibleBack;
	return 0;
}
