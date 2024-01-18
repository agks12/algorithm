#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string tas;
		cin >> tas;
		
		int left = 0;
		int right = tas.size();
		// _찾는건데 lower(지금)이나 upper(다음)이나 상관없을듯
		// 근데 숫자비교가 아니라 '_'이게 아니면 무조건 더 큰데(right)있는 원리
		// 즉 '_' 랑 같지 않으면 오른쪽으로 이동해야 되므로 left=mid+1
		// 이러면 같은 경우는 작거나같은이므로 lower이자 right 반환값은 '_'시작점
		while (left < right) {
			int mid = (left + right) / 2;
			if (tas[mid] != '_') {// 내가 찾는값이 중앙값보다 큰 경우임
				left = mid + 1;
			}
			else {//여기는 작거나 같은 경우 -> lower임 (작은데 같은이 들어가서)
				right = mid;
			}
		}
		// 전체 개수 tas.size로 나누면 끝(시작되는 인덱스이긴하지만 0부터 시작이라 ㄱㅊ) 
		int ans = int(100*(float(right) / float(tas.size())));
		cout << ans<<"%\n";
	}

	return 0;
}
