#include <iostream>
#include<algorithm>
using namespace std;

int tc;
int arr_key[1000000] = { 0 };
int arr_key_sort[1000000] = { 0 };

void sorting(int n) {
	int cnt = 0;
	for (int i = 0; i < n - 1; i++) {
		cnt = 0;
		for (int j = i; j < n - 1; j++) {
			if (arr_key_sort[n - 1 - cnt] > arr_key_sort[n - 1 - cnt - 1]) {
				int cp;
				cp = arr_key_sort[n - 1 - cnt];
				arr_key_sort[n - 1 - cnt] = arr_key_sort[n - 1 - cnt - 1];
				arr_key_sort[n - 1 - cnt - 1] = cp;
			}
			cnt++;
		}
	}
}

int main() {
	cin>>tc;
	for (int testcase = 0; testcase < tc; testcase++) {
		int n;
		int cnt_out = 0;
		int minam = 100000;
		int a = 0;

		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> arr_key[i];
			arr_key_sort[i] = arr_key[i];
		}

		//내림차순정렬
		sorting(n);
		//sort(arr_key_sort, arr_key_sort + n,greater<>());
		for (int i = 0; i < n; i++) {

			cin >> a;
			//arr_key의 i번쨰값이 arr_key_sort의 a번째값이랑
			//같으면 yes1개라도 다르면 no 즉 모두 같아야yes
			if (arr_key[i] == arr_key_sort[a-1])cnt_out++;
		}

		if (cnt_out == n)cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}
