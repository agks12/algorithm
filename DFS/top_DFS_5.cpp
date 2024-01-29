#include<iostream>
using namespace std;

int arr[13][13];
int visited[13];
int sum;
int Min=100000;
void dfs(int n, int to, int level) {
	if (sum > Min)return; //시간 줄이기 필요없는경우 리턴
	//마지막까지 갈필요없이 전단계에서 검사 실시
	//시작위치는 처음에만 visited하고 절대 갈일없음 마지막 전단계에서
	//연결되어었으면 더하고 없으면 리턴
	if (level == n - 1) {
		if (arr[to][0] == 0)return;
		sum += arr[to][0];
		if (sum < Min)Min = sum;
		sum -= arr[to][0];
		return;
	}
	for (int i = 0; i < n; i++) {
		if (arr[to][i] == 0)continue;
		if (visited[i] == 1)continue;
		visited[i] = 1;
		sum += arr[to][i];
		dfs(n, i,level+1);
		visited[i] = 0;
		sum -= arr[to][i];
	}
}
int main() {
	int n; cin >> n;
	for (int i = 0; i < n; i++)
		for(int j=0;j<n;j++)
			cin >> arr[i][j];
	visited[0] = 1;
	dfs(n, 0, 0);
	cout << Min;
	return 0;
}
