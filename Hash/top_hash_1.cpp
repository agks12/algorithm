#include<iostream>
#include<unordered_map>
using namespace std;

int n, m;
int visited[100001];
int main() {
	cin >> n >> m;
	//unordered_map 키 밸류 지정하는 DAT같은거
	unordered_map<int, int> um;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		um[a]++;
	}
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		if (um.count(a))cout << um[a] << " ";
		else cout << 0 << " ";
	}

	//visited방식
	/*for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		visited[a]++;
	}
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		cout << visited[a] << " ";
	}*/
	return 0;
}
