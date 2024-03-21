#include <string>
#include <vector>
#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;

unordered_map<string,int> umGive;
unordered_map<string,int> umRecive;
unordered_map<string,int> presentValue;
unordered_map<string,string> all;


int solution(vector<string> friends, vector<string> gifts) {
    int n = friends.size();
    

    
    
    for(int i=0;i<gifts.size();i++){
        string now = gifts[i];
        
        int spaceIndex = now.find(" ");
        string fir = now.substr(0,spaceIndex);
        string sec = now.substr(spaceIndex+1);
        
        umGive[fir]++;
        umRecive[sec]++;
        // int s = umGive[fir];
        // cout<<s;
        string add = " "+sec+" ";
        all[fir] += add;
    }
    
    
    for(int i=0;i<n;i++){
        string now = friends[i];
        presentValue[now] = umGive[now] - umRecive[now];
    }
    // 모든 애들이랑 거래하는데 거래한적있으면 오고간거 사용 없으면 지수사용
    int Maximcnt = -1;
    for(int i=0;i<n;i++){
        string giveNow = friends[i];
        int myreciveCnt=0;
        for(int j=0;j<n;j++){
            if(i==j)continue;
            string reciveNow = friends[j];
            string mygive = all[giveNow];
            string mygivetar = all[reciveNow];
            //cout<<giveNow<<" "<<reciveNow<<" " << mygive<<" "<<mygivetar<<" ";
            
            int len = reciveNow.size();
            int nowIndex=0;
            int index=0;
            int give_cnt=0;
            //string renewrec
            while(index != string::npos){
                index = mygive.find(" "+reciveNow+" ",nowIndex);
                nowIndex = index + len; // 여기를 수정
                give_cnt++;
            }
            give_cnt--;

           //cout<<give_cnt<<" ";
            
            
            
            
            int len2 = giveNow.size();
            int nowIndex2=0;
            int index2=0;
            int recive_cnt=0;
            while(index2 != string::npos){
                index2 = mygivetar.find(" "+giveNow+" ",nowIndex2);
                nowIndex2 = index2 + len2; // 여기를 수정
                recive_cnt++;
            }
            recive_cnt--;

            //cout<<recive_cnt<<" \n";

            if(recive_cnt==give_cnt || (recive_cnt==0&&give_cnt==0)){
                //지수비교해서 받는지주는지 비교
                if(presentValue[giveNow]<=presentValue[reciveNow])continue;
                if(presentValue[giveNow]>presentValue[reciveNow])myreciveCnt++;
            }
            else if(give_cnt>recive_cnt)myreciveCnt++;
        }
        
        if(myreciveCnt>Maximcnt)Maximcnt=myreciveCnt;
        //cout<<myreciveCnt<<" \n";

    }
    
    
    // for (auto it = all.begin(); it != all.end(); ++it) {
    //     cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    // }
    
    return Maximcnt;
}
