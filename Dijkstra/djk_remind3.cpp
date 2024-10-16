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

// bfs는 특정노드로 가는 모든 경우를 보지않아서 bfs는 절대 안되는듯
// 일반적으로 최대노드라는 조건이 있으면 최단경로로 최대비용으로 처럼 조건이 있어야함
// 다익스트라도 최대값으로 하면 dist가 계속 진행할수록 최대로 갱신되므로 모든 노드 계속 거침 
// 다익스트라 최대경로인줄 안 dfs방법 이렇게 하면 그냥 모든 곳 다 거쳐야 최대값이므로 모든 노드 더 거치는 경로나옴
#include<iostream>
//#include<vector>
//using namespace std;
//
//struct Pair { int row, col; };
//int n, m;
//int arr[101][101];
//int visited[101][101];
//
//int dr[4] = { 0,0,1,-1 };
//int dc[4] = { 1,-1,0,0 };
//
//int maxim = -1;
//
//void dfs(int nowRow, int nowCol, int summary, vector<Pair> v) {
//
//	if (nowRow == n - 1 && nowCol == m - 1) {
//		if (summary > maxim) {
//			maxim = summary;
//			cout << "최대값 갱신\n";
//			int sizeLoop = v.size();
//			for (int i = 0; i < sizeLoop; i++) {
//				cout << v[i].row << " " << v[i].col << "\n";
//			}
//		}
//		return;
//	}
//
//	for (int i = 0; i < 4; i++) {
//		int nextRow = nowRow + dr[i];
//		int nextCol = nowCol + dc[i];
//		if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= m)continue;
//		if (visited[nextRow][nextCol] == 1)continue;
//		visited[nextRow][nextCol] = 1;
//		summary += arr[nextRow][nextCol];
//		v.push_back({ nextRow,nextCol });
//		dfs(nextRow, nextCol, summary,v);
//		v.pop_back();
//		summary -= arr[nextRow][nextCol];
//		visited[nextRow][nextCol] = 0;
//	}
//
//}
//
//int main() {
//	int cnt = 0;
//	cin >> n >> m;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < m; j++) {
//			cin >> arr[i][j];
//			cnt += arr[i][j];
//		}
//	}
//	vector<Pair> v;
//	visited[0][0] = 1;
//	v.push_back({ 0,0 });
//	dfs(0,0,arr[0][0],v);
//
//	cout << maxim;
//
//
//	cout << "\n" << cnt;
//	return 0;
//}
