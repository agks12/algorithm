#include<iostream>
#include<algorithm>
using namespace std;

int arr[100001];

bool cmp(int left, int right) {
	if (left < right)return true;
	if (left > right)return false;
	return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + n, cmp);

	for (int i = 0; i < m; i++) {
		int start, end;
		cin >> start >> end;

		int ret = 0;
		int ret2 = 0;

		//lower bounder 
		int left = 0;
		int right = n;
		while (right > left) {
			int mid = (left + right) / 2;
			if (arr[mid] < start) {
				left = mid + 1;
			}
			else if (arr[mid] >= start) {
				right = mid;
			}
		}
		ret = right;
		//lower bounder끝나면 right 값이 시작하는 지점

		//upper bounder
		left = 0;
		right = n;
		while (right > left) {
			int mid = (left + right) / 2;
			if (arr[mid] <= end) {
				left = mid + 1;
			}
			else if (arr[mid] > end) {
				right = mid;
			}
		}
		ret2 = right;
		//upper bounder끝나면 right값+1이 끝나는 지점
		
		//lower이나 upper 나 모두 처음에 right를 최대인덱스(n-1)보다
		cout << ret2 - ret << "\n";

	}
	return 0;
}
