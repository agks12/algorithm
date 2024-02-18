#include<iostream>
#include<unordered_map>
using namespace std;

int n, m,cnt;
unordered_map<int,int> um;
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		um[a]=1;
		//물건마다1개씩 존재
	}
	for (int i = 0; i < m; i++) {
		int a;
		cin >> a;
		int fnum = -a;
		if (um.find(fnum) == um.end())continue;
		//--하면 존재함 0인 값으로
		//그래서 이거 말고 eaeas해야함
		um.erase(fnum);
		cnt++;
	}
	cout << cnt;
	return 0;
}
