#include<iostream>
#include<algorithm>
using namespace std;

int tc, n, m, arrn[101], arrm[101];
static void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> arrn[i];
	for (int i = 0; i < m; i++) cin >> arrm[i];
	sort(arrn, arrn + n, greater<>());
	sort(arrm, arrm + m, greater<>());
}
static int sol() {
	int nowIndex = 0;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (arrm[nowIndex] < arrn[i])continue;
		sum += arrn[i];
		nowIndex++;
		if (nowIndex == m - 1)break;
	}
	return sum;
}
int main() {
	cin >> tc;
	for (int i = 1; i <= tc; i++) {
		input();
		int ans = sol();
		cout << &quot;#&quot; << i << &quot; &quot; << ans << &quot;\n&quot;;
	}
	return 0;
}
