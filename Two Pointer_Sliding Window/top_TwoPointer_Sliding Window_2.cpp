#include<iostream>
using namespace std;

int N, W;
int arr[100001];
int max3 = -1e9;
int maxLeft = 0;
int maxRight = 0;

void input() {
	cin >> N >> W;
	for (int i = 0; i < N; i++)cin >> arr[i];
	max3 = -1e9;
	maxLeft = 0;
	maxRight = 0;
	int left = 0;
	int right = 0;
	int sum = arr[0];
	W--;
	while (right < N) {
		if ( (right - left  ) < W ) {
			right++;
			sum += arr[right];
		}
		else if( (right - left ) > W ){
			sum -= arr[left];
			left++;
		}
		if ((right - left) == W) {
			if (sum > max3) {
				max3 = sum;
				maxLeft = left;
				maxRight = right;
			}
			right++;
			sum += arr[right];
		}
	}
}

int main() {
	int tc; cin >> tc;
	for (int i = 1; i <= tc; i++) {
		input();
		cout << "#" << i <<" " << maxLeft << " " << maxRight << " " << max3 << "\n";
	}
	return 0;
}

// 고정칸인 경우 쓰는법
#include<iostream>
using namespace std;

int N, W;
int arr[100001];
int max3 = -1e9;
int maxLeft = 0;
int maxRight = 0;

void input() {
	cin >> N >> W;
	for (int i = 0; i < N; i++)cin >> arr[i];
	max3 = -1e9;
	maxLeft = 0;
	maxRight = 0;
	int left = 0;
	int right = W-1;
	int sum = 0;
	// 고정칸이므로 셋팅시작
	for (int i = 0; i < right; i++) {
		sum += arr[i];
	}
	while (right < N) {
		sum += arr[right];
		if (sum > max3) {
			max3 = sum;
			maxLeft = left;
			maxRight = right;
		}
		sum -= arr[left];
		right++;
		left++;
	}
}

int main() {
	int tc; cin >> tc;
	for (int i = 1; i <= tc; i++) {
		input();
		cout << "#" << i <<" " << maxLeft << " " << maxRight << " " << max3 << "\n";
	}
	return 0;
}
