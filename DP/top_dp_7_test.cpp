#include<iostream>
#include<vector>
using namespace std;

int n, m, h;
vector<int> v[51];
void dp(int now) {
	//애가 이거 하고 안하고.. 모든 경우의수 - 높이가h인 경우 찾기 
	//사람 달라서 중복 x
	// 어떤거를 dp테이블로 써야되는지

	//지금애 선택 or x
	// 변수로 할게 지금애랑 - 지금애의 몇번째 인지 그리고 할지 안할지
	// 
	v[now][]
}
int main() {
	cin >> n >> m >> h;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int ch;
			cin >> ch;
			v[i].push_back(ch);
		}
	}
	dp(0);
	return 0;
}
