#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

int n;
unordered_map<string,pair<int,int>> um;
int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string teamName;
		int score;
		cin >> teamName >> score;
		um[teamName].first += score;
		um[teamName].second++;
	}
	string my, frend;
	cin >> my >> frend;

	int myTeamCnt = um[my].second;
	int frendTeamCnt = um[frend].second;
	int myTeamScore = um[my].first;
	int frendTeamScore = um[frend].first;

	cout << myTeamCnt <<" "<< myTeamScore<< "\n" << frendTeamCnt <<" " << frendTeamScore<<"\n";
	if (myTeamScore > frendTeamScore)cout << my;
	else cout << frend;

	return 0;
}
