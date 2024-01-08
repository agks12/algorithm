#include <iostream>
using namespace std;

int inid[10000000];
int maxim;
int maxim_id;
int main(){
	int a,b;
	cin >> a>>b;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			int c;
			cin >> c;
			inid[c]++;
			if (inid[c] > maxim) {
				maxim = inid[c];
				maxim_id = c;
			}
			else if (inid[c] == maxim) {
				if (c < maxim_id) {
					//maxim = inid[c];
					maxim_id = c;
				}
			}
		}
	}
	cout << maxim_id;
	return 0;
}
