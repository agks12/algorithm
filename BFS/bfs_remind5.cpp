#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Pair{int row,col;};

Pair ex,tree,boss;
int T,N,M,HP;
char map[11][11];
int visited[11][11];

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int bfs(Pair st, int power){
    queue<Pair> q;
    queue<int> turn;
    q.push(st);
    visited[st.row][st.col]=1;
    turn.push(1);
    
    int to_y=21e8;
    int to_m=21e8;
    
    while(!q.empty()){
        Pair now = q.front();q.pop();
        int nowTurn = turn.front();turn.pop();
        
        for(int i=0;i<4;i++){
            int nextRow = now.row + dr[i];
            int nextCol = now.col + dc[i];
            if(nextRow<0 || nextCol < 0 || nextRow >= N || nextCol >=M)continue;
            if(map[nextRow][nextCol]=='x')continue;
            if(visited[nextRow][nextCol]==1)continue;
            visited[nextRow][nextCol]=1;
            
            if(nextRow==0 && nextCol ==0)to_y=nowTurn; // 용사까지 거리
            if(map[nextRow][nextCol]=='M')to_m=nowTurn; // 보스까지 거리
            
            q.push({nextRow,nextCol});
            turn.push(nowTurn+1);
        }
    }
    
    // 무기가 용사에게 전달못하거나 보스에게 전달안되면 불가능
    if(to_y==21e8 || to_m==21e8)return 21e8;
    // 물리치는거 가능 // 물리치는 시간 = HP/power => 나머지 남으면 +1 해야함
    
    int stack=HP/power;
    if(HP%power!=0)stack++; // 1대 남음 
    int score = to_y + to_m + stack;
    return score;
}

void reset(){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            visited[i][j]=0;
        }
    }
}

int main(){
    cin>>T;
    for(int tc=1;tc<=T;tc++){
        cin>>N>>M;
        for(int i=0;i<N;i++)cin>>map[i];
        cin>>HP;
        // 칼 막대 위치찾기
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                if(map[i][j]=='S')ex={i,j};
                if(map[i][j]=='T')tree={i,j};
                if(map[i][j]=='M')boss={i,j};
            }
        }
        // 칼에서 시작
        int sord = bfs(ex,5);
        reset(); //visited초기화
        // 나무에서 시작
        int Tree = bfs(tree,2);
        reset(); //visited초기화
        
        cout<<"#"<<tc<<" ";
        
        //불가능 
        if(sord==21e8 && Tree==21e8)cout<<"the world is doomed\n";
        else{
            if(sord < Tree)cout<<sord;
            else cout<<Tree;
            cout<<"\n";
        }
        
    }
    
    
    return 0;
}
