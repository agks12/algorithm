#include <string>
#include <vector>
#include<iostream>
#include<unordered_map>
using namespace std;

//1번도넛은 처음시작 visited안하고 자기자신으로 오면 됨

// 3번 도넛은 bfs

//나한테서 3개 이상 나간다 => 무조건 타겟
// 나한테서 2개 이상 나가면서 들어오는건 없다 => 무조건 타겟 무조건 구하기 가능 시작은 애 애서
//(from >=  2 and to==0)
//돌아왔다 = > 순환도넛
struct Node{int from,to;};
unordered_map<int,Node> um;
vector<int> v[1000001];
int visited[1000001];
//8자는 무조건 둘어오고 나가는게 2개인 애가 존재하는데 무조건 만남

int flag;
void checkNode(int now){
    if(um[now].from==0){
        flag=1;
    }   //return 1;
    if(um[now].from >=2 && um[now].to >=2){
        flag=3;
        //return 3;
    } 
    if(visited[now]==1)flag=2;//return 2;
    for(int i=0;i<v[now].size();i++){
        if(flag>0)break;
        int nowCheckNode = v[now][i];
        //if(visited[now]==1)continue;
        visited[now] =1;
        checkNode(nowCheckNode);
    }
    
}
int arr[4];

vector<int> solution(vector<vector<int>> edges) {
    int startNode;//시작노드
    vector<int> answer;
    int maxNode;
    for(int i=0;i<edges.size();i++){
        int from = edges[i][0];
        int to = edges[i][1];
        v[from].push_back(to);
        um[from].from++;
        um[to].to++;
        if(um[from].from >= 2 and  um[from].to==0) startNode = from;
        if(um[to].from >= 2 and  um[to].to==0) startNode = to;
        if(from>maxNode)maxNode = from;
        if(to>maxNode)maxNode = to;
    }
    arr[0] = startNode;
    for(int i=0;i<v[startNode].size();i++){
        int now = v[startNode][i];
        checkNode(now);
        if(flag ==1)arr[2]++;
        if(flag ==2)arr[1]++;
        if(flag ==3)arr[3]++;
        flag=0;
    }
    
    for(int i=0;i<4;i++)answer.push_back(arr[i]);
   // for(int i=1;i<=maxNode;i++){
   //     for(int j=0;j<v[i].size();j++){
   //         cout<<v[i][j]<<" ";
   //     }
   //     cout<<"\n";
   // }
    //startNode 구하기
    // for(auto il=um.begin(); il!=um.end();il++){
    //     if( ((*il).second.from<2) || (*il).second.to!=0)continue;
    //     startNode = (*il).first;
    //     cout<< (*il).first<< " "<<(*il).second.from<<" "<<(*il).second.to<<"\n";
    // }
    
    cout<<startNode;
    
    
    return answer;
}
