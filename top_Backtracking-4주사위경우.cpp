#include<iostream>
using namespace std;
int arr[100];
int DAT[10];
//주사위
void backing1(int n,int level) {
	//모든경우
	if (level == n) {
		for (int i = 0; i < n; i++)cout << arr[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = 1; i <= 6; i++) {
		arr[level] = i;
		backing1(n, level + 1);
	}
}

void backing2(int n, int level) {
	//중복경우 121 112안되려면 앞에거가 뒤에거보다 크면안됨 - 자주쓸듯
	if (level == n) {
		for (int i = 0; i < n; i++)cout << arr[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = 1; i <= 6; i++) {
		arr[level] = i;
		if (level >= 1 and arr[level-1] > arr[level])continue;
		backing2(n, level + 1);
	}
}

void backing3(int n, int level) {
	//모두 다른경우 DAT사용
	int stop = 0;
	if (level == n) {
		for (int i = 0; i < n; i++)cout << arr[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = 1; i <= 6; i++) {
		if (DAT[i] == 1)continue;
		DAT[i] = 1;
		arr[level] = i;
		backing3(n, level + 1);
		DAT[i] = 0;
	}

}

int main() {
	int n, m;
	cin >> n >> m;
	if(m==1)backing1(n,0);
	if(m==2)backing2(n,0);
	if(m==3)backing3(n,0);
	
	
	return 0;
}
