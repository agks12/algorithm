#include<iostream>
#include<bitset>
using namespace std;

int n, m;
int arr[6];

unsigned char visited;

void back1(int level) {
	if (level == n) {
		for (int i = 0; i < level; i++) {
			cout << arr[i] << " ";
		}
		cout << "\n";
		return;
	}
	for (int i = 1; i <= 6; i++) {
		arr[level] = i;
		back1(level + 1);
	}
}

void back2(int level) {
	if (level == n) {
		for (int i = 0; i < level; i++)cout << arr[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = 1; i <= 6; i++) {
		if (level > 0 && arr[level - 1] > i)continue;
		arr[level] = i;
		back2(level + 1);
	}

}

void back3(int level) {
	if (level == n) {
		for (int i = 0; i < level; i++) cout << arr[i] << " ";
		cout << "\n";
		return;
	}
	for (int i = 1; i <= 6; i++) {
		unsigned char now = 1 << (i - 1);
		if (visited & now)continue;
		visited |= now;
		arr[level] = i;
		back3(level + 1);
		visited &= ~now;
	}
}

int main() {
	cin >> n >> m;
	if (m == 1)back1(0);
	else if (m == 2)back2(0);
	else back3(0);


	return 0;
}
