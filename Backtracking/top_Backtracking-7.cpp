#include<iostream>
using namespace std;

int arr[11];
int arr_index[11];
char cal[4] = { '*','+','-'};
void back(int n,int level,int sum) {
	if (level == n) {
		if (sum!=0 && sum % 101 == 0) {
			cout << arr[0];
			for (int i = 1; i < n; i++) {
				cout << cal[arr_index[i]] << arr[i];
			}
			cout << "\n";
		}
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			if (arr[level] == 0)continue;//0곱하는경우는 무조건 0나와서 그냥 넘김
			sum *= arr[level];
		}
		if(i==1)sum += arr[level];
		if(i==2)sum -= arr[level];
		arr_index[level] = i;
		back(n, level + 1, sum);
		if (i == 0)sum /= arr[level];
		if (i == 1)sum -= arr[level];
		if (i == 2)sum += arr[level];
	}
}
int main() {
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	back(n, 1,arr[0]);
	return 0;
}
