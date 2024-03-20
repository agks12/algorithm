#include<iostream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;
int n;
int visited[11];
int print[11];
vector<vector<int>> dic;
int subdic[11];
//중복하지 않고 서로다른 2개를 뽑아야함 1 2 와 2 1은 같은거임
int a, b, totalA, totalB, Max;
vector<int> maxArr;

// void cal() {
//     a = 0;
//     b = 0;
//     for (int i = 0; i < n; i++) {
//         //a인경우
//         int nowValue = dic[i][subdic[i]];
//         if (visited[i] == 1) {
//             a += nowValue;
//         }
//         else b += nowValue;
//     }
//     if (a > b)totalA++;
//     else if (a < b) totalB++;

// }

//무조건 1296번 즉 모든 경우의수 계산함 - 시간초과
// void dfs2(int level) {
//     if (level == n) {
//         //cal();
//         if (a > b)totalA++;
//         else if (a < b) totalB++;
//         return;
//     }
//     for (int i = 0; i < 6; i++) {
//         //subdic[level] = i;
//         //여기 까지 오면 확정
//         if(visited[level]==1) a+=dic[level][i];
//         else b+=dic[level][i];
//         dfs2(level + 1);
//         if(visited[level]==1) a-=dic[level][i];
//         else b-=dic[level][i];
//     }

// }



vector<int> aman;
vector<int> bman;

int aadd[8000];
int badd[8000];

int now,sum3,cnt_all_c,cnt_all_n;
//주사위 모든 합 구하기
void caladda(int level){
    if (level==n/2){
        aadd[now] = sum3;
        now+=1;
        return;
    }
    
    for(int i=0;i<6;i++){
        int ns = dic[aman[level]][i];
        sum3 += ns;
        caladda(level+1);
        sum3 -= ns;
    }
}


void caladdb(int level){
    if (level==n/2){
        badd[now] = sum3;
        now+=1;
        return;
    }
    
    for(int i=0;i<6;i++){
        int ns = dic[bman[level]][i];
        sum3 += ns;
        caladdb(level+1);
        sum3 -= ns;
    }
}

void sort_cal(){
    // n = 2일때 (6^2)=36개 조합 생성
    // 정렬 후 1번부터 비교하면서 이기고 진 횟수 수해서 확률로?
    int aIndex = 0;
    int bIndex = 0;

    int win=0;
    for(int i=0;i<cnt_all_c;i++){
        int st = 0;
        int targetValue = aadd[i];
        int nowBvalue=0;
        while(badd[nowBvalue] < targetValue && nowBvalue<cnt_all_c) {
            if(badd[nowBvalue] < targetValue)nowBvalue++;
        }
        win+=nowBvalue;
    }

    if (win > Max) {
        maxArr.clear();
        Max = win;
        for (int i = 0; i < n / 2; i++) {
            maxArr.push_back(print[i]+1);
        }
    }
}

void newcal(){

    for(int i=0;i<n;i++){
        if(visited[i]==1) aman.push_back(i);
        else bman.push_back(i);
    }
    caladda(0);
    now=0;
    caladdb(0);
    now=0;
    cout<<"\n";
    
    //합은 무조건 6의 n/2승개
    cnt_all_c=1;
    for(int i=0;i<n;i++){
        if(i<n/2)cnt_all_c*=6;
        cnt_all_n*=6;
    }
    
    sort(aadd,aadd+cnt_all_c,less<>());
    sort(badd,badd+cnt_all_c,less<>());
    
    sort_cal();
    aman.clear();
    bman.clear();

}

void dfs(int level) {
    //이거가 a가 가지는 하나의 경우의수 
    if (level == n / 2) {
        newcal();
        return;
    }

    for (int i = 0; i < n; i++) {
        if (level > 0 && print[level - 1] > i)continue;
        if (visited[i] == 1)continue;
        visited[i] = 1;
        print[level] = i;
        dfs(level + 1);
        visited[i] = 0;
    }
}

vector<int> solution(vector<vector<int>> dice) {
    dic.assign(dice.begin(), dice.end());
    n = dice.size();
    dfs(0);
    return maxArr;
}
