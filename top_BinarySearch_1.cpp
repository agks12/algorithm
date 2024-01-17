#include<iostream>
#include<algorithm>
using namespace std;

bool node(int a, int b) {
	if (a < b)return true;
	return false;
}

int arr[100001];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n, node);

	int sb;
	cin >> sb;
	
	for (int i = 0; i < sb; i++) {
		int serc;
		cin >> serc;
		int left = 0;
		int right = n-1;
		int flag = 0;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (arr[mid] > serc) right = mid - 1;
			else if (arr[mid] < serc)left = mid +1;
			else if (arr[mid] == serc) {
				flag = 1;
				break;
			}
		}
		if (flag == 1)cout << "O";
		else cout << "X";
	}

	return 0;
}
