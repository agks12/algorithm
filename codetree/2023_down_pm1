#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair { int row, col, RorS,state,score;};
struct arrValue { int RorS, index; };
struct cmp {
	int row, col, index;
	bool operator<(cmp right)const {
		if (row < right.row)return true;
		if (row > right.row)return false;
		if (col < right.col)return true;
		if (col > right.col)return false;
		return false;
	}
};
int n, GameCnt, p, PoRu, PoSan;
arrValue arr[51][51];
int RuRow, RuCol;
Pair SanTa[31];

// 루돌프 우선순위 r먼저 동일시 c먼저
int RuDr[8] = { 1,1,1,0,-1,-1,-1,0 };
int RuDc[8] = { 1,0,-1,1,1,0,-1,-1 };

// 산타 우선순위 상우하좌
int SanDr[4] = { -1,0,1,0 };
int SanDc[4] = { 0,1,0,-0, };

Pair PlayerList[32];
queue<Pair> q;
vector<int> v[31];


void dfs(int row,int col,int dirRow, int dirCol, int breakCnt) {
	//산타 도착 위치 , 날아갈 방향

	//위에서 받는건 날아온 산타가 도착한 위치의 인덱스 이값이 0이면 산타 없음
	int nowSantaIndex = arr[row][col].index;
	if (nowSantaIndex != 0) {
		//도착한 곳에 산타 있으면 상호작용 발생
		if (!(row < 1 || col < 1 || row > n || col > n)) {
			//날아갔는데 산타 안뒤졌으면 위치 갱신 + 기절 
			// 근데 도착한 위치에 산타 있으면 그새끼도 1칸 밀려야되는데 계속

			//충돌한 지점에 있던 산타
			PlayerList[nowSantaIndex].row -= dirRow;//1칸만 움직이니까 방향벡터 반대니까 -
			PlayerList[nowSantaIndex].col -= dirCol;//1칸만 움직이니까 방향벡터 반대니까 -

		}
		else if (row < 1 || col < 1 || row > n || col > n) {
			//날아갔는데 산타 뒤졌으면 턴+인덱스 
			v[breakCnt].push_back(tarSanta.index);
		}
	}
	else if ((!(row < 1 || col < 1 || row > n || col > n)) && nowSantaIndex == 0) {
		// 연쇄작용 없음
		return;
	}

	
}


void StartGame() {
	int nowIndex = 0;
	int breakCnt = 0;


	//===============================================
	while (1==1) {
		Pair now = PlayerList[nowIndex];

		//Pair now = q.front(); q.pop();
		if (now.RorS == 1) {//루돌프는 절대 안밀려남
			if (breakCnt != 0) {
				//처음은 아니고 다음천부터 턴 샘
				//여기서 1턴 끝나고 살아남은 애들 +1점씩 줘야되는데
				//마지막에 벡터로 한번에 계산
				breakCnt++; // 한바뀌 돌아야 한턴
			}
			//모든 애들 계산
			int Max = 21e8;
			priority_queue<cmp> pq;
			for (int i = 1; i <= p; i++) {
				Pair nowSanta = PlayerList[i];
				if (nowSanta.row < 1 || nowSanta.col < 1 || nowSanta.row > n || nowSanta.col > n)continue;
				int rowsqer = (now.row - nowSanta.row) * (now.row - nowSanta.row);
				int colsqer = (now.col - nowSanta.col) * (now.col - nowSanta.col);
				int dis = rowsqer + colsqer;
				if (dis <= Max) {
					Max = dis;
					pq.push({ nowSanta.row,nowSanta.col,i });
				}
			}
			//이러면 row > col 순으로 pq제일앞에거가 자동으로 선택될것
			cmp tarSanta = pq.top();//제일 가까운 산타 선택했는데 이새기 방향이 먼지 어캐알름
			// 내위치 - 산타위치
			// 차이 row >= -1 아래, col >= -1 오른쪽, 
			// row >= 1 위쪽 col >= 1 왼쪽, 
			// row ==0 위아래 그대로 col == 0 좌우 그대로
			// 근데 좌표 계산 편하게 하기 위해서는 -곱해줘야 된는데
			// 그것보다 산타위치 - 내위치가 더 편함
			// 그리고 값/절대값으로 계산하면 단위벡테 됨
			int dirRow = tarSanta.row - now.row;
			int dirCol = tarSanta.col - now.col;

			int UnitDirRow = dirRow / abs(dirRow);
			int UnitDirCol = dirCol / abs(dirCol);

			arr[now.row][now.col].RorS = 0; // 지도에서 루돌프 없애기
			now.row += UnitDirRow;
			now.col += UnitDirCol;
			//이값이 아래 해당될 일은 없음 루돌프는 절대
			//if (now.row < 1 || now.col < 1 || now.row > n || now.col > n)

			
			arr[tarSanta.row][tarSanta.col].RorS = 0;//날아갈 산타 위치 없애기
			int SantaJumpRow = tarSanta.row + (PoRu * UnitDirRow);
			int SantaJumpCol = tarSanta.col + (PoRu * UnitDirCol);
			// 리스트에 산타 위치 배열범위 벗어나도 상관없음
			PlayerList[tarSanta.index].row = SantaJumpRow;
			PlayerList[tarSanta.index].col = SantaJumpCol;
			//산타 뒤지든 말든 점수는 받음
			PlayerList[tarSanta.index].score += PoRu;
			

			//루돌프는 한칸만 이동하는데 만약 1칸 이동후 거기에 산타 있는 경우 아래
			if (arr[now.row][now.col].RorS == 1) {
				//만약 루돌프가 가려는데 산타있는 경우
				//위 방향벡터 방향으로 산타는 루돌프 함만큼 점수었고 이동
				
				

				if (!(SantaJumpRow < 1 || SantaJumpCol < 1 || SantaJumpRow > n || SantaJumpCol > n)) {
					//날아갔는데 산타 안뒤졌으면 위치 갱신 + 기절 
					// 근데 도착한 위치에 산타 있으면 그새끼도 1칸 밀려야되는데 계속
					
					// 날아온 곳에 산타 있는 경우
					if (arr[SantaJumpRow][SantaJumpCol].RorS == 1) {
						dfs(SantaJumpRow, SantaJumpCol, UnitDirRow, UnitDirCol, breakCnt);
					}

					//날아온 곳 산타 있든 없는 이 조건은 무조건 실행
					arr[SantaJumpRow][SantaJumpCol].RorS = 1;
					PlayerList[tarSanta.index].state = breakCnt;
					
					// 루돌프가 1번 밀치는 경우 까지 계산하고 밀려난 산타 위치에 산타 있으면 그때 상호작용 dfs시작
					// 인자는 도착 산타 위치 , 방향(반대로 적용해야함)
					
				}
				else if(SantaJumpRow < 1 || SantaJumpCol < 1 || SantaJumpRow > n || SantaJumpCol > n) {
					//날아갔는데 산타 뒤졌으면 턴+인덱스 
					v[breakCnt].push_back(tarSanta.index);
				}
			}
			PlayerList[0].row = now.row;
			PlayerList[0].col = now.col;
			//누구 있든말든 무조건 루돌프위치됨
			arr[now.row][now.col].RorS = 2;// 루돌프 새위치
			// 여기 까지 하면 루돌프 이동은 끝 이제 고려는 부딧치는거
		}
		else {
			//이게 산타경우
			//뒤진 새끼 색출
			if (now.row < 1 || now.col < 1 || now.row > n || now.col > n)continue;
			//기절한 새끼 색출
			// 기절당한 턴넘버와 지금 턴 넘버 비교 해서 1차이나면 기절상태이고 2이상이면 정상임
			if (now.state >= breakCnt - 1)continue;

			//루돌프 위치
			Pair tarRu = PlayerList[0]; 

			//루돌프와내위치 차이
			int dirRow = tarRu.row - now.row;
			int dirCol = tarRu.col - now.col;

			// 루돌프 를 향하는 방향벡터
			int UnitDirRow = dirRow / abs(dirRow);
			int UnitDirCol = dirCol / abs(dirCol);

			arr[now.row][now.col].RorS = 0; // 지도에서 지금산타 없애기
			//산타 옮기기
			now.row += UnitDirRow;
			now.col += UnitDirCol;
			//위 값이 범위 벗어날 경우는 없음 아마도

			//옮겼는데 산타 있는경우 막혀있다고 판단하고 다른데로 가야함
			if (arr[now.row][now.col].RorS == 1) {

				arr[tarSanta.row][tarSanta.col] = 0;//날아갈 산타 위치 없애기
				int SantaJumpRow = tarSanta.row + (PoRu * UnitDirRow);
				int SantaJumpCol = tarSanta.col + (PoRu * UnitDirCol);
				PlayerList[tarSanta.index].row = SantaJumpRow;
				PlayerList[tarSanta.index].col = SantaJumpCol;
				//뒤지든 말든 점수는 받음
				PlayerList[tarSanta.index].score += PoRu;
				if (!(SantaJumpRow < 1 || SantaJumpCol < 1 || SantaJumpRow > n || SantaJumpCol > n)) {
					//날아갔는데 산타 안뒤졌으면 위치 갱신 + 기절
					arr[SantaJumpRow][SantaJumpCol].RorS = 1;
					PlayerList[tarSanta.index].state = breakCnt;
				}
				else if (SantaJumpRow < 1 || SantaJumpCol < 1 || SantaJumpRow > n || SantaJumpCol > n) {
					//날아갔는데 산타 뒤졌으면 턴+인덱스 
					v[breakCnt].push_back(tarSanta.index);
				}
			}
			arr[now.row][now.col].RorS = 2;// 루돌프 새위치
		}

		

	}
}

int main() {
	cin >> n >> GameCnt >> p >> PoRu >> PoSan;
	cin >> RuRow >> RuCol;
	PlayerList[0] = { RuRow ,RuCol,1,0,0 };
	for (int i = 1; i <= p; i++) {
		int Num, row, col;
		cin >> Num >> row >> col;
		SanTa[Num] = { row,col };
	}
	arr[RuRow][RuCol].RorS = 2; // 루돌프는 2로 설정
	q.push({ RuRow, RuCol, 1, 0});
	for (int i = 1; i <= p; i++) {
		Pair now = SanTa[i];
		PlayerList[i] = { now.row,now.col,2,0,0 };
		q.push({ now.row,now.col,2,0,0 });
		arr[now.row][now.col].RorS = 1;
	}
	StartGame();

	return 0;
}
