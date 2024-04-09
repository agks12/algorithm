#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair { int row, col, RorS, state, score; };
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
int n, GameCnt, p, PoRu, PoSan, santaFlag;
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


void dfs(int row, int col, int dirRow, int dirCol, int breakCnt, int genIndex) {
	//산타 도착 위치 , 날아갈 방향

	int nowSantaIndex = arr[row][col].index; //인덱스 값이 0 이면 루돌프거나 없는 칸인데 산타연쇄로 루돌프 만날일 없음

	//산타 도착 위치가 배열 범위에 속하는지 검사 속하지 않으면 끝 뒤진애 검사 배열에 추가
	if (row < 1 || col < 1 || row > n || col > n) {
		PlayerList[genIndex].row = row;
		PlayerList[genIndex].col = col;
		v[breakCnt].push_back(genIndex);
		santaFlag++;
		return;
	}

	//여기 오는애들은 범위 만족
	//위에서 받는건 날아온 산타가 도착한 위치의 인덱스
	if (arr[row][col].RorS == 1) { // 산타 있을때만 1임
		//도착한 곳에 산타 있으면 상호작용 발생

		//변화시킬 값 -> 배열 값,인덱스 초기화, 리스트의 값 초기화, 점수는 안변함
		// 
		// 충돌 시킨애 변경 (충돌 시킨애 인덱스 알아야되는데)
		PlayerList[genIndex].row = row;
		PlayerList[genIndex].col = col;

		//충돌 시킨애 값 변경
		arr[PlayerList[genIndex].row][PlayerList[genIndex].col].index = genIndex;

		// 충돌해서 이동할 산타 와 충돌해온 애의 값이 지금은 row,col으로 동일
		//  충돌 당한애 리스트 값 변경
		PlayerList[nowSantaIndex].row -= dirRow;
		PlayerList[nowSantaIndex].col -= dirCol;

		int afterRow = PlayerList[nowSantaIndex].row;
		int afterCol = PlayerList[nowSantaIndex].col;

		//충돌 당한애 범위 확인
		if (afterRow < 1 || afterCol < 1 || afterRow > n || afterCol > n) {
			v[breakCnt].push_back(nowSantaIndex);
			santaFlag++;
			return;
		}

		//만약 충돌 또 일어나면 재귀
		if (arr[afterRow][afterCol].RorS == 1) {
			dfs(afterRow, afterCol, dirRow, dirCol, breakCnt, nowSantaIndex);
		}

		//충돌 당한애로 배열 값 변경
		arr[afterRow][afterCol].index = nowSantaIndex;

	}
	else {
		// 연쇄작용 없음
		// 충돌 시킨애 변경 (충돌 시킨애 인덱스 알아야되는데)
		PlayerList[genIndex].row = row;
		PlayerList[genIndex].col = col;

		//충돌 시킨애 값 변경
		arr[PlayerList[genIndex].row][PlayerList[genIndex].col].index = genIndex;
		arr[PlayerList[genIndex].row][PlayerList[genIndex].col].RorS = 1;

		return;
	}
}

void movsSanta(int row, int col, int afterSantaRow, int afterSantaCol) {

	//새롭게 옮긴 위치 1로하고 원위치 값 초기화
	arr[afterSantaRow][afterSantaCol].RorS = 1;
	
	arr[row][col].RorS = 0;


	//리스트 값도 초기화해야됨
	int nowIndex = arr[row][col].index;
	PlayerList[nowIndex].row = afterSantaRow;
	PlayerList[nowIndex].col = afterSantaCol;
	arr[afterSantaRow][afterSantaCol].index = nowIndex;
	arr[row][col].index = 0;
}

//움직이기 전 정보
void search(int RuRow, int RuCol, int row, int col,int afterRow,int afterCol, int UnitDirRow, int UnitDirCol, int breakCnt) {

	// 산타 위치 변경
	int afterSantaRow = row + afterRow;
	int afterSantaCol = col + afterCol;

	int nowSantaIndex = arr[row][col].index;

	if (arr[afterSantaRow][afterSantaCol].RorS == 1) {
		// 산타있는 경우
		// 다음선택이 좀 애매 같은 row,col에 있으면 안움직임 즉 상하좌우로 움직이는 경우
		if ((row == RuRow) || (col == RuCol)) {
			//같은 라인에 있으면 안움직이고 끝남
			return;
		}
		else {
			// 대각선으로 움직이는 경우에는 각각2가지 경우가 있음
			// 대각선이라는 거는 방향벡터가 // (1,1), (1,-1), (-1,1), (-1,-1) 
			// 위 중 하나 
			// 상우하좌 순서로 
			//(1,1) 이면 (1,0 or 0,1) 하 우
			//(1,-1) 이면 (1,0 or 0,-1) 하 좌
			//(-1,1) 이면 (-1,0 or 0,1) 상 우
			// (-1,-1) 이면 (-1,0 or 0,-1) 상 좌

			if (UnitDirRow == 1 && UnitDirCol == 1) {
				//하 우 방향인 경우는 col이 우선순위

				//먼저 우 방향
				int RedgRow = row;
				int RedgCol = col + UnitDirCol; //어차피 다 1칸이라 그냥 1로 넣도 딯듯

				// 하 방향
				int UedgRow = row + UnitDirRow;
				int UedgCol = col;
				// 기존위치 , 바뀔위치
				if (arr[RedgRow][RedgCol].RorS != 1)movsSanta(row, col, RedgRow, RedgCol);
				else if (arr[UedgRow][UedgCol].RorS != 1)movsSanta(row, col, UedgRow, UedgCol);
				else return;
			}
			else {
				//먼저  방향
				int RedgRow = row + UnitDirRow;
				int RedgCol = col; //어차피 다 1칸이라 그냥 1로 넣도 딯듯

				// 하 방향
				int UedgRow = row;
				int UedgCol = col + UnitDirCol;
				// 기존위치 , 바뀔위치
				if (arr[RedgRow][RedgCol].RorS != 1)movsSanta(row, col, RedgRow, RedgCol);
				else if (arr[UedgRow][UedgCol].RorS != 1)movsSanta(row, col, UedgRow, UedgCol);
				else return;
			}
		}
	}
	else if (arr[afterSantaRow][afterSantaCol].RorS == 2) {

		if ((row == RuRow) || (col == RuCol)) {
			//루돌프와 충돌인 경우
			// 산타연쇄충돌 모듈 사용해야돼
			int afterRuAccRow = afterSantaRow + (PoSan * -afterRow);
			int afterRuAccCol = afterSantaCol + (PoSan * -afterCol);

			PlayerList[nowSantaIndex].score += PoSan;
			PlayerList[nowSantaIndex].state = breakCnt;

			arr[row][col] = { 0,0 };
			dfs(afterRuAccRow, afterRuAccCol, afterRow, afterCol, breakCnt, nowSantaIndex);

			return;
		}
		else{
			// 대각선으로 움직이는 경우에는 각각2가지 경우가 있음
			// 대각선이라는 거는 방향벡터가 // (1,1), (1,-1), (-1,1), (-1,-1) 
			// 위 중 하나 
			// 상우하좌 순서로 
			//(1,1) 이면 (1,0 or 0,1) 하 우
			//(1,-1) 이면 (1,0 or 0,-1) 하 좌
			//(-1,1) 이면 (-1,0 or 0,1) 상 우
			// (-1,-1) 이면 (-1,0 or 0,-1) 상 좌

			if (UnitDirRow == 1 && UnitDirCol == 1) {
				//하 우 방향인 경우는 col이 우선순위

				//먼저 우 방향
				int RedgRow = row;
				int RedgCol = col + UnitDirCol; //어차피 다 1칸이라 그냥 1로 넣도 딯듯

				// 하 방향
				int UedgRow = row + UnitDirRow;
				int UedgCol = col;
				// 기존위치 , 바뀔위치
				if (arr[RedgRow][RedgCol].RorS != 1)movsSanta(row, col, RedgRow, RedgCol);
				else if (arr[UedgRow][UedgCol].RorS != 1)movsSanta(row, col, UedgRow, UedgCol);
				else return;
			}
			else {
				//먼저  방향
				int RedgRow = row + UnitDirRow;
				int RedgCol = col; //어차피 다 1칸이라 그냥 1로 넣도 딯듯

				// 하 방향
				int UedgRow = row;
				int UedgCol = col + UnitDirCol;
				// 기존위치 , 바뀔위치
				if (arr[RedgRow][RedgCol].RorS != 1)movsSanta(row, col, RedgRow, RedgCol);
				else if (arr[UedgRow][UedgCol].RorS != 1)movsSanta(row, col, UedgRow, UedgCol);
				else return;
			}
		}
	}
	else {
		//아무것도 없어서 그냥 이동함

		//이동하는 함수
		movsSanta(row, col, afterSantaRow, afterSantaCol);

		return;
	}
}

void StartGame() {
	int nowIndex = 0;
	int breakCnt = 1;


	//===============================================
	while (1 == 1) {
		if (nowIndex == p + 1) {
			nowIndex = 0;
			
			if (breakCnt == GameCnt)break;
			if (santaFlag == p)break;
			breakCnt++;
		}
		Pair now = PlayerList[nowIndex];

		//Pair now = q.front(); q.pop();
		if (now.RorS == 2) {//루돌프는 절대 안밀려남
			//breakCnt++; // 한바뀌 돌아야 한턴
			//if (breakCnt != 0) {
			//	//처음은 아니고 다음천부터 턴 샘
			//	//여기서 1턴 끝나고 살아남은 애들 +1점씩 줘야되는데
			//	//마지막에 벡터로 한번에 계산

			//}

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

			int UnitDirRow = 0;
			int UnitDirCol = 0;
			if (dirRow != 0)UnitDirRow = dirRow / abs(dirRow);
			if (dirCol != 0)UnitDirCol = dirCol / abs(dirCol);



			arr[now.row][now.col].RorS = 0; // 지도에서 루돌프 없애기
			now.row += UnitDirRow;
			now.col += UnitDirCol;
			//이값이 아래 해당될 일은 없음 루돌프는 절대
			//if (now.row < 1 || now.col < 1 || now.row > n || now.col > n)





			//루돌프는 한칸만 이동하는데 만약 1칸 이동후 거기에 산타 있는 경우 아래
			// 자동으로 위치 벗어난 경우는 아래 ==1 만족할 수 없으므로 고려x
			if (arr[now.row][now.col].RorS == 1) {
				arr[tarSanta.row][tarSanta.col].RorS = 0;//날아갈 산타 위치 없애기
				int SantaJumpRow = tarSanta.row + (PoRu * UnitDirRow);
				int SantaJumpCol = tarSanta.col + (PoRu * UnitDirCol);
				// 리스트에 산타 위치 배열범위 벗어나도 상관없음
				//PlayerList[tarSanta.index].row = SantaJumpRow;
				//PlayerList[tarSanta.index].col = SantaJumpCol;
				//산타 뒤지든 말든 점수는 받음
				PlayerList[tarSanta.index].score += PoRu;
				PlayerList[tarSanta.index].state = breakCnt;

				arr[tarSanta.row][tarSanta.col].index = 0;
				//arr[tarSanta.row][tarSanta.col].RorS = 0;
				//만약 루돌프가 가려는데 산타있는 경우
				//위 방향벡터 방향으로 산타는 루돌프 함만큼 점수었고 이동
				//바로 dfs시작
				//날아간애가 도착한 위치 정보와 방향벡터 그리고 기절에 필요한 지금 턴수
				// 만 있으면됨
				//점프된 애새끼 범위 계산은 아래 함수 안에서
				// 루돌프 계산은 위에서 끝내야함
				//if (arr[SantaJumpRow][SantaJumpCol].RorS == 1)
				dfs(SantaJumpRow, SantaJumpCol, UnitDirRow, UnitDirCol, breakCnt, tarSanta.index);

			}

			//루돌프 무조건 이동 하지만 마지막에 해야 위에서 계산 가능
			PlayerList[0].row = now.row;
			PlayerList[0].col = now.col;
			//누구 있든말든 무조건 루돌프위치됨
			arr[now.row][now.col].RorS = 2;// 루돌프 새위치
			// 여기 까지 하면 루돌프 이동은 끝 이제 고려는 부딧치는거
		}
		else {
			//이게 산타경우
			//뒤진 새끼 색출
			if (now.row < 1 || now.col < 1 || now.row > n || now.col > n) {
				nowIndex++;
				continue;
			}
			//기절한 새끼 색출
			// 기절당한 턴넘버와 지금 턴 넘버 비교 해서 1차이나면 기절상태이고 2이상이면 정상임
			if (now.state >= breakCnt - 1) {
				nowIndex++;
				continue;
			}

			//루돌프 위치
			Pair tarRu = PlayerList[0];

			//루돌프와내위치 차이
			int dirRow = tarRu.row - now.row;
			int dirCol = tarRu.col - now.col;

			// 루돌프 를 향하는 방향벡터
			int UnitDirRow = 0;
			int UnitDirCol = 0;
			if (dirRow != 0)UnitDirRow = dirRow / abs(dirRow);
			if (dirCol != 0)UnitDirCol = dirCol / abs(dirCol);

			int nextRow = 0;
			int nextCol = 0;

			//이렇게 구하면 안됨 나를 기준으로 대각선 4분위 에서 구해야함
			if (dirRow < 0 && dirCol > 0) {
				//1사분면
				// 상
				if (abs(dirRow) > abs(dirCol)) {
					nextRow = -1;
					nextCol = 0;
				}//우
				else if (abs(dirRow) < abs(dirCol)) {
					nextRow = 0;
					nextCol = 1;
				}
			}
			else if (dirRow < 0 && dirCol < 0) {
				//2사분면
				// 상
				if (abs(dirRow) > abs(dirCol)) {
					nextRow = -1;
					nextCol = 0;
				}//좌
				else if (abs(dirRow) < abs(dirCol)) {
					nextRow = 0;
					nextCol = -1;
				}
			}
			else if (dirRow > 0 && dirCol < 0) {
				//3사분면
				// 아
				if (abs(dirRow) > abs(dirCol)) {
					nextRow = 1;
					nextCol = 0;
				}//좌
				else if (abs(dirRow) < abs(dirCol)) {
					nextRow = 0;
					nextCol = -1;
				}
			}
			else if (dirRow > 0 && dirCol > 0) {
				//4사분면
				// 아
				if (abs(dirRow) > abs(dirCol)) {
					nextRow = 1;
					nextCol = 0;
				}//우
				else if (abs(dirRow) < abs(dirCol)) {
					nextRow = 0;
					nextCol = 1;
				}
			}

			if (nextRow == 0 && nextCol == 0) {
				nextRow = UnitDirRow;
				nextCol = UnitDirCol;
			}
			//arr[now.row][now.col].RorS = 0; // 지도에서 지금산타 없애기
			//산타 옮기기
			//now.row += UnitDirRow;
			//now.col += UnitDirCol;
			//위 값이 범위 벗어날 경우는 없음 아마도

			search(tarRu.row, tarRu.col, now.row, now.col, nextRow,nextCol, UnitDirRow, UnitDirCol, breakCnt);

			//옮겼는데 산타 있는경우 막혀있다고 판단하고 다른데로 가야함
			//if (arr[now.row][now.col].RorS == 1) {
			//	//다른데 가는 함수
			//}
			//else if (arr[now.row][now.col].RorS == 2) {
			//	//루돌프인 경우
			//}
		}
		nowIndex++;
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
	arr[RuRow][RuCol].index = 0; // 배열과 리스트 연결하기 위해 배열에 리스트의 인덱스 저장
	PlayerList[0] = { RuRow,RuCol,2,-10,0 };
	q.push({ RuRow, RuCol, 1, 0 });
	for (int i = 1; i <= p; i++) {
		Pair now = SanTa[i];
		PlayerList[i] = { now.row,now.col,1,-10,0 };
		q.push({ now.row,now.col,2,0,0 });
		arr[now.row][now.col].RorS = 1;
		arr[now.row][now.col].index = i;
	}
	StartGame();

	int allScore[51] = { 0 };
	for (int i = 1; i <= GameCnt; i++) {
		int nowScore = i;
		if (v[i].size() == 0)continue;
		for (int j = 0; j < v[i].size(); j++) {
			int nowSanta = v[i][j];
			allScore[nowSanta] = PlayerList[nowSanta].score + nowScore - 1;
		}
	}
	for (int i = 1; i <= p; i++) {
		if (allScore[i] != 0)cout << allScore[i] << " ";
		else cout << PlayerList[i].score + GameCnt << " ";
	}


	return 0;
}
