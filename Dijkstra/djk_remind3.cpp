#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node{
    int row,col,cost;
    bool operator<(Node right)const{
        if(cost > right.cost)return true;
        if(cost < right.cost)return false;
        if(row < right.row)return true;
        if(row > right.row)return false;
        if(col < right.col)return true;
        if(col > right.col)return false;
        return false;
    }
};

int n,m;
int arr[101][101];
int visited[101][101];
int dist[101][101];

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

void djk(){
    priority_queue<Node> pq;
    pq.push({0,0,arr[0][0]});
    dist[0][0]=arr[0][0];
    
    while(!pq.empty()){
        Node now = pq.top();pq.pop();
        int nowCost = now.cost;
        if(visited[now.row][now.col]==1)continue;
        visited[now.row][now.col]=1;
        for(int i=0;i<4;i++){
            int nextRow = now.row + dr[i];
            int nextCol = now.col + dc[i];
            if(nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >=m)continue;
            int nextCost = arr[nextRow][nextCol];
            
            if(dist[now.row][now.col]+nextCost >= dist[nextRow][nextCol])continue;
            dist[nextRow][nextCol] = dist[now.row][now.col]+nextCost;
                        
            pq.push({nextRow,nextCol,dist[nextRow][nextCol]});
        }
    }
}

int main(){
    cin>>n>>m;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> arr[i][j];            
            dist[i][j]=21e8;
        }
    }
    
    djk();
    
    cout<<dist[n-1][m-1];
        
    return 0;
}
