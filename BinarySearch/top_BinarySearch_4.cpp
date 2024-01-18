#include<iostream>
using namespace std;

int main() {
	int n; cin >> n;
	int left = 0;
	int right = n;
	while (right > left) {
		long long mid = (left + right) / 2;
		long long sqre = mid * mid;
		if (sqre <= n) {
			left = mid + 1;
		}
		else right = mid;
	}
	if (n == 1)cout << 1; //이런예외케이스 이렇게 하면 안됨
	else cout << right-1;
	return 0;
}

//예전 풀이
#include<iostream>
using namespace std;

int N;
int main() {
	cin >> N;

	int left = 0;
	int right = 3162; //sqer(10,000,000)
	int let = 0;

	while (left <= right) {
		int mid = (left + right) / 2;
		if (mid * mid > N) {
			right = mid - 1;
		}
		else if (mid * mid <= N) {
			left = mid + 1;
			let = mid;
		}
	}
	cout << let;
	return 0;
}
