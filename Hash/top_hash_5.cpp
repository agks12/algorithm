#include<iostream>
#include<unordered_map>
using namespace std;

int n;
unordered_map<string, pair<int,int>> um;
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string fir, sec;
		cin >> fir >> sec;
		um[fir].first++;
		um[sec].second++;
	}

	int good = 0,bad=0,mid=0;
	for (auto& i : um) {//.begin(); i != um.end(); i++) {
		if (i.second.first > i.second.second)good++;
		if (i.second.first < i.second.second)bad++;
		if (i.second.first == i.second.second)mid++;
	}
	cout << good << " " << bad << " " << mid;

	return 0;
}
