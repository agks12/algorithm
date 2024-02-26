#include<iostream>
using namespace std;

int n1, m1, arr[1001][1001], n2, m2,visited[100001], black, white;
int main() {
	cin >> n1 >> m1;
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m1; j++)
			cin >> arr[i][j];
	

	cin >> n2 >> m2;
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < m2; j++) {
			int a;
			cin >> a;
			visited[a] = 1;
		}
	}

	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m1; j++)
			if (visited[arr[i][j]] == 1)black++;
		
	cout << black<<"\n"<<n1*m1-black;
	return 0;
}
