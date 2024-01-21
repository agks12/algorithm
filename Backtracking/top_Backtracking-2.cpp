#include<iostream>
using namespace std;

int backing(int n,int level) {
	if (n == 1) {
		return level;
	}
	
	if (n % 2 == 0)n = n / 2;
	else if (n % 2 == 1)n = 3 * n + 1;
	backing(n, level + 1);
}

int main() {
	int n;
	cin >> n;
	int ans = backing(n,0);
	cout << ans;

	return 0;
}
