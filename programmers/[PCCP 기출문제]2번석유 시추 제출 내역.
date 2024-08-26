#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct MAP{
  int dir,num;  
};

MAP map[502][502];
int visited[502][502];

int visited2[250001]={0};

int item[250001];
int itemIndex=1;

struct Pair{
    int row,col;
};

int R,C;

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int startBfs(int stRow, int stCol){
    queue<Pair> q;
    q.push({stRow,stCol});
    visited[stRow][stCol]=1;
    int cnt=1;
    
    while(!q.empty()){
        Pair now = q.front();q.pop();
        for(int i=0;i<4;i++){
            int nextRow = now.row + dr[i];
            int nextCol = now.col + dc[i];
            if(nextRow < 0 || nextCol < 0 || nextRow >= R || nextCol >=C)continue;
            if(visited[nextRow][nextCol]==1)continue;
            if(map[nextRow][nextCol].dir==0)continue;
            visited[nextRow][nextCol]=1;
            map[nextRow][nextCol].num = itemIndex;
            cnt++;
            q.push({nextRow,nextCol});
        }
    }

    return cnt;
}


int fill(vector<vector<int>> land){
    
    // 2차원 배열에 저장
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            map[i][j].dir = land[i][j];
        }
    }
    
    int maxValue = -1;
    // 붙어있는거 개수 세기
    for(int i=0;i<C;i++){
        int nowRowCnt = 0;
        queue<int> q;
        
        //int visited2[250001]={0}; 여기서 이거 선언하는 것만으로 시간초과됨
        
        for(int j=0;j<R;j++){
            if(map[j][i].dir==0)continue;
            if(visited[j][i]==1){
                if(visited2[map[j][i].num]>0)continue;
                nowRowCnt += item[map[j][i].num];
                visited2[map[j][i].num]=1;
                q.push(map[j][i].num);
                continue;
            }
            
            int nowCnt = startBfs(j,i);
            nowRowCnt+=nowCnt;
            item[itemIndex] = nowCnt;
            
            
            visited2[itemIndex]=1;
            q.push(itemIndex);
            itemIndex++;
        }
        
        // 1차 for 루프 안에서 visited 250000선언하는것도 시간 초과됨
        while(!q.empty()){
            int nowV = q.front();q.pop();
            visited2[nowV]=0;
        }
        
        
        if(nowRowCnt > maxValue)maxValue = nowRowCnt;
    }
    
    return maxValue;
}

int solution(vector<vector<int>> land) {
    R = land.size();
    C = land[0].size();
    int answer = fill(land); // 일단 2차원맵에 개수로 표현 끝
    return answer;
}
