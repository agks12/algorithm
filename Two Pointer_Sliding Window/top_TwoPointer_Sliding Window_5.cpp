#include<iostream>
using namespace std;

int arr[200001];
int main() {
	int n, m, k;
	int cnt = 0;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		arr[n + i] = arr[i];
	}
	int left = 0;
	int right = m;
	int sum = 0;
	for (int i = 0; i < right; i++) sum += arr[i];
	//몇번 도는지가 좀 까다로움
	while (left < n) {
		if (sum < k)cnt++;
		sum -= arr[left];
		left++;
		sum += arr[right];
		right++;
	}
	cout << cnt;
	return 0;
}
