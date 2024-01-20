#include<iostream>
using namespace std;

int n, r;
int arr[1000001] = { 0 };
int visited[1000001] = { 0 };

int solution() {
	cin >> n >> r;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		arr[n + i] = arr[i];//2*r개만큼배열추가
	}
	int left = 0;
	int right = (2 * r);
	for (int i = 0; i < right; i++) {
		visited[arr[i]]++;
		if (visited[arr[i]] > 2)return -1;
	}
	while (right < n+(2*r) ) {
		visited[arr[right]]++;
		if (visited[arr[right]] > 2)return -1;
		visited[arr[left]]--;
		left++;
		right++;
	}
	return 1;
}

int main() {
	int tc; cin >> tc;
	for (int i = 1; i <= tc; i++) {
		int ans = solution();
		if (ans == -1)cout << "#" << i << " NO\n";
		else cout << "#" << i << " YES\n";
		for (int i = 0; i < n; i++)visited[arr[i]] = 0;
	}
	return 0;
}
