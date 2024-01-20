#include<iostream>
#include<algorithm>
using namespace std;

int arr[100001];
int main() {
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	sort(arr, arr + n);

	int left = 0;
	int right = n - 1;
	int sum = 0;
	int minLeft = 0;
	int minRight = 0;
	int maxans = 1e9;
	while (left < right) {
		sum = arr[left] + arr[right];
		if (sum == 0) {
			//sum==0인경우절대값가장큰거 뽑아야되는데 정렬된상태이므로
			// 처음오는게 무조건 제일절대값커서 찾으면 바로 끝
			cout << arr[left] << " " << arr[right];
			return 0;
		}
		if (abs(sum) < abs(maxans) ) {
			maxans = sum;
			minLeft = left;
			minRight = right;
		}
		if (sum > 0) right--;
		else if (sum < 0)left++;
	}
	cout << arr[minLeft] << " " << arr[minRight];
	
	return 0;
}
