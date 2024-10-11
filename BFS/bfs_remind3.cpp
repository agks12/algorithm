#include<iostream>
#include<queue>
#include<string>
using namespace std;


struct Pair{int row,col,turn;};

int n, m;
string arr[2];

int bfs(){
    queue<Pair> q;
    q.push({0,0,0});
    
    while(!q.empty()){
        Pair nowPoi = q.front();q.pop();
        int nowRow = nowPoi.row;
        int nowCol = nowPoi.col;
        int nowTurn = nowPoi.turn;
            
        for(int i=0;i<3;i++){
            if(i==0)nowCol = nowPoi.col -1;
            if(i==1)nowCol = nowPoi.col +1;
            if(i==2){
                nowCol = nowPoi.col + m;
                if(nowRow==0)nowRow=1;
                else nowRow=0;
            }
            
            
            
            if(nowCol>n-1)return 1;
            if(nowCol < nowTurn)continue;
            if(arr[nowRow][nowCol]=='0')continue;
            if(nowCol==n-1)return 1;
            q.push({nowRow,nowCol,nowTurn+1});
        }
    }
    
    return 0;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < 2; i++) {
          cin >> arr[i];
    }
    
    int ans = bfs();
    cout<<ans;

    return 0;
}
