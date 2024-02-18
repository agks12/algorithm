#include<iostream>
#include<unordered_map>
using namespace std;

int n, m;
unordered_map<int,int> um;

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		um[a]++;
	}
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		cout << um[a]<<"\n";
	}
	return 0;
}
