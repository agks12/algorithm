#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 시작점부터 하지않고 끝점을 기준으로 봐야되는듯

bool cmp(vector<int> &v1, vector<int> &v2){
    //if(v1[0]==v2[0])
    return v1[0]<v2[0];
    //else return v1[0] < v2[0];
}


int solution(vector<vector<int>> targets) {


     int missileCnt = targets.size();
    

    sort(targets.begin(), targets.end(), cmp);
    
   
    
    int nowV = 1;
    int nextV = 0;
    int cnt=0;
    
    int minV = 21e8;
    
    for(int i=0;i<missileCnt;i++){
        int st = targets[i][0];// 지금 차례 미사일 시작값
        int end = targets[i][1];// 지금 차례 미사일 끝값
        
        //if(st < nowV)continue;
        
        if(end < minV)minV = end;
        
        if(st != nowV){
            if(st < nowV){
                //cout<<"시작점보다 작음\n";
                continue;
            }
            
            // 시작점 다른경우
            //cout<<"전환점"<<nowV<<"\n";
            nowV = minV;
            minV = 21e8; // 초기화
            cnt++;

            continue;
        }

    }

    
    
    
    int answer = cnt+1;
    return answer;
}
