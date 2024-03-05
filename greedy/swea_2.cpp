#include<iostream>
#include<algorithm>
using namespace std;

struct Pair { int st, end; };
int tc,n, Max;
Pair arr[101];
static bool cmd(const Pair a, const Pair b) {
	if (a.st < b.st)return true;
	return false;
}
static void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i].st;
		cin >> arr[i].end;
	}
	sort(arr, arr + n, cmd);
}
static void sol(int now,int next,int level) {

	if (next >= 24) {
		if (level > Max)Max = level;
		return;
	}
	for (int i = now; i < n; i++) {
		if (arr[i].st < next)continue;
		int nextValue = arr[i].end;
		sol(i+1, nextValue,level+1);
	}
}
int main() {
	cin >> tc;
	for (int i = 1; i <= tc; i++) {
		input();
		sol(0,0,0);
		cout << &quot;#&quot;<<i<<&quot; &quot; <<Max<< &quot;\n&quot;;
		Max = 0;
	}
	return 0;
}
