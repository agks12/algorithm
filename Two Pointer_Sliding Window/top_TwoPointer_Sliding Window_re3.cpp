#include<iostream>
using namespace std;

int n, Maxleft, Maxright, arr[100001], arrValue[100001];
int main() {
	cin >> n;
	int sum2 = 0;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		sum2 += arr[i];
		arrValue[i] = sum2;
	}

	int Max = -21e8;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = i; j < n; j++) {
			sum += arr[j];
			if (sum > Max) {
				Max = sum;
				Maxleft = i;
				Maxright = j;
			}
		}
	}
	//
	//int left = 0;
	//int right = 1;
	//int sum = arr[0];
	//int Max = -21e8;
	//int now = 0;
	//while (left < right) {
	//	sum += arr[right];
	//	if (sum > Max) {
	//		Max = sum;
	//		Maxleft = left;
	//		Maxright = right;
	//	}
	//	if (sum > now)right++;
	//	if (sum < now)left++;
	//	now = sum;
	//	
	//}
	cout << Max << "\n" << Maxleft << " " << Maxright;
	return 0;
}
