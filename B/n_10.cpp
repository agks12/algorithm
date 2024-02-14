extern bool checkCards(int mIndexA, int mIndexB, int mDiff);
#include<iostream>
#include<vector>




using namespace std;
int visited[50001];
vector<int> v[50001];
int preN;
void playGame(int N)
{
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i <= N; i++) {
        v[i].clear();
    }
    //int Ncnt = 0;
    //for (int i = 1; i < N; i++) { // 차이가 N까지 남 차이 1인거 위아래2개씩 4개 최대최소를 기준으로 잡으면 2개
    //    int cnt = 0;
    //    if (Ncnt >= (2 * N)-1)break;
    //    for (int j = 1; j < 2 * N; j++) { //
    //        if (i !=1 && cnt >= 4)break;
    //        if (!checkCards(0, j, i)) continue;
    //        if (visited[j] == 1)continue;
    //        cnt++;
    //        Ncnt++;
    //        visited[j] = 1;
    //        v[i].push_back(j);
    //    }
    //}
    //int stop = 0;
    //for (int i = 1; i < 2 * N; i++) {
    //    if(!checkCards(0, i, 0))continue;
    //    checkCards(0, i, 0);
    //    stop = i;
    //    break;
    //}

    for (int i = 1; i < 2*N; i++) {
        for (int j = 0; j < N; j++) {
            if (!checkCards(0, i, j)) continue;
            if (visited[j] >= 4)continue;
            visited[j]++;
            v[j].push_back(i);
            break;
        }
    }
    checkCards(0, v[0][0], 0); //0번인덱스거 찾기

    //v[1] 부터 짝맞추기
    for (int i = 1; i < N; i++) {
        if (v[i].size() == 0)break;
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

    // 두 카드의 숫자를 비교하기 위해 아래와 같이 checkCards 함수를 사용합니다.
    // <영문>
    //
    // checkCards(mIndexA, mIndexB, mDiff);
}
