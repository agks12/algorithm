#include<iostream>
#include<queue>
using namespace std;

int mi,sc;
int arr[100002];
// +-1, *2

int bfs(int st){
    queue<int> q;
    queue<int> t;
    t.push(0);
    q.push(st);
    arr[st]=1;
    while(!q.empty()){
        int now = q.front();q.pop();
        int nowt = t.front();t.pop();
        int next = now;
        if(now==sc)return nowt;
        for(int i=0;i<3;i++){
            if(i==0)next = now+1;
            else if(i==1)next = now-1;
            else if(i==2)next = now*2;
            if(next>100000)continue;
            if(next<0)continue;
            if(arr[next]==1)continue;
            arr[next]=1;
            q.push(next);
            t.push(nowt+1);
        }
    }
    return 0;
}

int main(){
    
    //min값에서 sc값 되야함 최단으로
    cin >> mi>>sc;
    int ans = bfs(mi);
    cout<<ans;
    
    
    return 0;
}
