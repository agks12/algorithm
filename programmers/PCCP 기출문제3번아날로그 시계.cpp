#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int h1, int m1, int s1, int h2, int m2, int s2) {
    

    // 끝나는 시간 * 12 
    // 지금 분 m1 을 시간에 추가해줘야함
    int nowm = (m1+1) / 12;
    h1+=nowm;
    int nowm2 = (m2+1) / 12;
    h2+=nowm2;
    
    if(m1==59)h1--;
    cout<<h1<<" "<<m1<<" "<<s1<<" "<<h2<<" "<<m2<<" "<<s2<<"\n";
    int cnt=0;
    //int h=1;
    // h, m, s가 가르키는 숫자가 지금 시계의 숫자
    //for(int h=1;h<=120;h++)
    
    int ans=0;
    int flag=0;
    int flags=0;
    while(h1!=121){
        if(h1>121)break;
        for(int m=0;m<=59;m++){
            if(flag==0){
                m=m1;
                //if(m==59)continue;
            }
            
            flag=1;
            
            if((m+1)%12==0){
                //cout<<h1<<" "<<m<<"반올림시\n";
                h1++;
                
            }
            //cout<<m<<"분\n";
            for(int s=0;s<=59;s++){
                if(flags==0){
                    s=s1;
                    //if(s==59)continue;
                }
                flags=1;
                //ans++;
                //cout<<s<<"초\n";
               
                
                if(h1==h2 && m==m2 && s==s2)return cnt;
                
                if(s==m){
                    cnt++;
                    cout<<h1<<"지금시"<<m<<" "<<s<<"분 초 \n";
                    //continue;
                }
                else if(h1==s){
                    cnt++;
                    cout<<h1<<" "<<s<<"시 초 \n";
                    //continue;
                }
                else if(h1==m){
                    cnt++;
                    cout<<h1<<" "<<m<<"시 분 \n";
                    //continue;
                }
                else if(h1==m && h1==s && m==s){
                    cnt++;
                    cout<<h1<<" "<<m<<" "<<s<<"시 분 초 \n";
                    //continue;
                }
                
                
                 
                // 끝내는 조건
                
            }
        }
    }
    
    //cout<<cnt;
    
    //int answer = -1;
    return cnt;
}
