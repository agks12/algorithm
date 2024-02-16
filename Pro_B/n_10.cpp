extern bool checkCards(int mIndexA, int mIndexB, int mDiff);
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;
vector<int> v[50001];
void playGame(int N)
{
    for (int i = 0; i <= N; i++) v[i].clear();

    //모든 인덱스 차이값검사 
    for (int i = 1; i < 2*N; i++) {
        int ret = 0;
        int left = 0;
        int right = N;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (checkCards(0, i, mid)) {//차이가 차이가 mid 보다 작거나 같으면 여기 들감
                right = mid - 1;
            }
            else {
                left = mid + 1;//차이가 mid 보다 크면 여기 들감
                ret = left;
            }
        }
        v[ret].push_back(i);
    }

    checkCards(0, v[0][0], 0); //0번인덱스거 찾기

    //v[1] 부터 짝맞추기
    for (int i = 1; i < N; i++) {
        if (v[i].size() == 2) {
            checkCards(v[i][0], v[i][1], 0);
            continue;
        }
        for (int j = 1; j < v[i].size(); j++) {
            if (!checkCards(v[i][0], v[i][j], 0))continue;
            checkCards(v[i][0], v[i][j], 0);
            if (j == 1)checkCards(v[i][2], v[i][3], 0);
            if (j == 2)checkCards(v[i][1], v[i][3], 0);
            if (j == 3)checkCards(v[i][1], v[i][2], 0);
            break;
        }
    }
}
