#include<iostream>
using namespace std;

int n, m;
int arr[6];
int cnt;

unsigned int visited; // 10자리라서 char 하면 안됨

void back(int level) {
	if (level == n) {
		cnt++;
		return;
	}
	for (int i = 0; i < n; i++) {
		unsigned int now = 1 << (i - 1);
		if (visited & now)continue;
		visited |= now;
		back(level + 1);
		visited &= ~now;
	}
}
int main() {
	cin >> n;

	back(0);
	cout << cnt;
	return 0;
}
