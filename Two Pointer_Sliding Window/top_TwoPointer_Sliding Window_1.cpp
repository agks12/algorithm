#include<iostream>
using namespace std;

int arr[10001];
int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)cin >> arr[i];

	int cnt = 0;
	int left = 0;
	int right = 0;
	int sum = arr[0];
	while (right < n) {

		if (sum < m) {
			right++;
			sum += arr[right];
		}
		else if (sum > m) {
			sum -= arr[left];
			left++;
		}
		if (sum == m) {
			cnt++;
			right++;
			sum += arr[right];
		}
	}
	cout << cnt;
	return 0;
}

//-----------
#include<iostream>
using namespace std; 

int main()
{
	int n,m; 
	int arr[100000]; 
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i]; 
	}
	
	int cnt = 0;

	int sum = 0; 
	int b = 0;
	for (int a = 0; a < n; a++)
	{
		while (b < n && sum < m)
		{
			sum += arr[b]; 
			b++; 
		}
		if (b >= n && sum < m) break; 
		// [a,b)
		if (sum == m)
		{
			cnt++; 
		}
		sum -= arr[a];
	}
	cout << cnt; 
	return 0;
}
