#include<iostream>
using namespace std;

int arr[3][5] = {
    {1, 3, 3, 5, 1},
    {3, 6, 2, 4, 2},
    {1, 9, 2, 6, 5}
};
int visited[100];
int n;
int main() {
    cin >> n;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 5; j++)
            visited[arr[i][j]]++;
       
    
    for (int i = 1; i < 10; i++)
        if (visited[i] == n)cout << i<<" ";
    
	return 0;
}
