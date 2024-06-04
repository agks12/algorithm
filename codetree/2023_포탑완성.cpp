#include<iostream>
#include<queue>
#include<vector>
using namespace std;

// 공격자 받는자 선정할때 행 열 합값 우선순위 정하는게 핵심 작은거 우선순위면 위  왼쪽 으로 가는데 범위초가인 경우 0열(세로) 아래로 다음에 n행(가로) 오른쪽으로 시작점 이동  

struct Pair { int row, col; };
struct MapInfo { int score, recentyT, pari; };
MapInfo Map[11][11];
int N, M, K;
int life;
// bfs 레이저 우선순위 우 하 좌 상
int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };

// 대포공격 8개
int dfdr[8] = { -1,-1,-1,0,1,1,1,0 };
int dfdc[8] = { -1,0,1,1,1,0,-1,-1 };

Pair selectAttach() {
	Pair attach = { 0 };
	int maxRecent = -1;
	int minim = 21e8;

	int nextRow = N - 1;
	int nextCol = M - 1;

	int stRow = N - 1;
	int stCol = M - 1;

	while (1 == 1) {
		//cout << "\n====지금위치 " << nextRow << "," << nextCol << "\n";
		int nowScore = Map[nextRow][nextCol].score;
		if (nowScore <= 0) {
			if (nextRow == 0 && nextCol == 0)break;
			if (nextRow + 1 >= N || nextCol - 1 < 0) {
				// 범위 초과
				// 위로 이동하거나 왼쪽으로 이동
				if (stRow - 1 < 0) {
					// 위로 이동 못함 왼쪽으로 가야함
					// row 는 무조건 0 col 는?
					nextRow = 0;
					stCol--;
					nextCol = stCol;
				}
				else {
					// 위로 이동 col 는 무조건 m-1
					nextCol = M - 1;
					stRow--;
					nextRow = stRow;
				}
			}
			else {
				// 아래 왼쪽으로 가면 됨
				nextRow += 1;
				nextCol -= 1;
			}
			continue;
		}
		if (nowScore < minim) {
			// 자동으로 행열관련 우선순위 적용
			attach.row = nextRow;
			attach.col = nextCol;
			minim = nowScore;
			maxRecent = Map[nextRow][nextCol].recentyT;
		}
		else if (nowScore == minim) {
			// 최근 공격 우선순위 적용
			if (maxRecent < Map[nextRow][nextCol].recentyT) {
				attach.row = nextRow;
				attach.col = nextCol;
				minim = nowScore;
				maxRecent = Map[nextRow][nextCol].recentyT;
			}
		}
		
		if (nextRow == 0 && nextCol == 0)break;
		if (nextRow + 1 >= N || nextCol - 1 < 0) {
			// 범위 초과
			// 위로 이동하거나 왼쪽으로 이동
			if (stRow - 1 < 0) {
				// 위로 이동 못함 왼쪽으로 가야함
				// row 는 무조건 0 col 는?
				nextRow = 0;
				stCol--;
				nextCol = stCol;
			}
			else {
				// 위로 이동 col 는 무조건 m-1
				nextCol = M - 1;
				stRow--;
				nextRow = stRow;
			}
		}
		else {
			// 아래 왼쪽으로 가면 됨
			nextRow += 1;
			nextCol -= 1;
		}
	}
	return attach;
}

//Pair selectAttach() {
//	Pair attach = { 0 };
//	int maxRecent = -1;
//	int minim = 21e8;
//	for (int i = N-1; i >= 0; i--) {
//		for (int j = M-1; j >= 0; j--) {
//			int nowScore = Map[i][j].score;
//			if (nowScore <= 0)continue;
//			if (nowScore < minim) {
//				// 자동으로 행열관련 우선순위 적용
//				attach.row = i;
//				attach.col = j;
//				minim = nowScore;
//				maxRecent = Map[i][j].recentyT;
//			}
//			else if (nowScore == minim) {
//				// 최근 공격 우선순위 적용
//				if (maxRecent < Map[i][j].recentyT) {
//					attach.row = i;
//					attach.col = j;
//					minim = nowScore;
//					maxRecent = Map[i][j].recentyT;
//				}
//			}
//		}
//	}
//	return attach;
//}


//Pair selectAttach() {
//	Pair attach = { 0 };
//	int maxRecent = -1;
//	int minim = 21e8;
//	int cnt = N * M;
//
//	int nextRow = N - 1;
//	int nextCol = M - 1;
//	// 9 7 4
//	// 8 5 2
// 	// 6 3 1 크기순
//	for (int i = 0; i < cnt; i++) {
//
//		cout << "\n====지금위치 " << nextRow << "," << nextCol<<"\n";
//		int nowScore = Map[nextRow][nextCol].score;
//		if (nowScore <= 0) {
//			if (nextRow + 1 >= N || nextCol - 1 < 0) {
//				// 초과한 범위
//				if (nextCol + 1 >= M) {
//					nextRow -= 1;
//				}
//				else {
//					int diff = M - nextCol;
//					int diffcol = M-1 - nextCol;
//					nextRow -= diff;
//					nextCol += diffcol;
//				}
//			}
//			else {
//				nextRow += 1;
//				nextCol -= 1;
//			}
//			continue;
//		}
//		if (nowScore < minim) {
//			// 자동으로 행열관련 우선순위 적용
//			attach.row = nextRow;
//			attach.col = nextCol;
//			minim = nowScore;
//			maxRecent = Map[nextRow][nextCol].recentyT;
//		}
//		else if (nowScore == minim) {
//			// 최근 공격 우선순위 적용
//			if (maxRecent < Map[nextRow][nextCol].recentyT) {
//				attach.row = nextRow;
//				attach.col = nextCol;
//				minim = nowScore;
//				maxRecent = Map[nextRow][nextCol].recentyT;
//			}
//		}
//
//
//		if (nextRow + 1 >= N || nextCol - 1 < 0) {
//			// 초과한 범위
//			if (nextCol + 1 >= M) {
//				nextRow -= 1;
//			}
//			else {
//				int diff = M - nextCol;
//				int diffcol = M - 1 - nextCol;
//				nextRow -= diff;
//				nextCol += diffcol;
//			}
//			
//		}
//		else {
//			nextRow += 1;
//			nextCol -= 1;
//		}
//	}
//	return attach;
//}

//Pair selectReceive() {
//	Pair receive = { 0 };
//	int maxRecent = 21e8;
//	int maxim = -1;
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < M; j++) {
//			int nowScore = Map[j][i].score;
//			if (nowScore <= 0)continue;
//			if (maxim < nowScore) {
//				receive.row = j;
//				receive.col = i;
//				maxim = nowScore;
//				maxRecent = Map[j][i].recentyT;
//			}
//			else if (maxim == nowScore) {
//				if (maxRecent > Map[j][i].recentyT) {
//					receive.row = j;
//					receive.col = i;
//					maxim = nowScore;
//					maxRecent = Map[j][i].recentyT;
//				}
//			}
//		}
//	}
//	return receive;
//}

//Pair selectReceive() {
//	Pair receive = { 0 };
//	int maxRecent = 21e8;
//	int maxim = -1;
//
//	int cnt = N * M;
//
//	int nextRow = 0;
//	int nextCol = 0;
//	// 9 7 4
//	// 8 5 2
//	// 6 3 1 크기순
//	for (int i = 0; i < cnt; i++) {
//		cout << "\n====지금위치 " << nextRow << "," << nextCol << "\n";
//
//		int nowScore = Map[nextRow][nextCol].score;
//		if (nowScore <= 0) {
//			if (nextRow - 1 < 0 || nextCol + 1 >= M) {
//				// 초과한 범위
//
//				if (nextCol - 1 < 0) {
//					nextRow += 1;
//				}
//				else {
//					int diff = nextCol+1;
//					int diffcol = nextCol;
//					nextRow += diff;
//					nextCol -= diffcol;
//
//
//				}
//			}
//			else {
//				nextRow -= 1;
//				nextCol += 1;
//			}
//			continue;
//		}
//		if (maxim < nowScore) {
//			receive.row = nextRow;
//			receive.col = nextCol;
//			maxim = nowScore;
//			maxRecent = Map[nextRow][nextCol].recentyT;
//		}
//		else if (maxim == nowScore) {
//			if (maxRecent > Map[nextRow][nextCol].recentyT) {
//				receive.row = nextRow;
//				receive.col = nextCol;
//				maxim = nowScore;
//				maxRecent = Map[nextRow][nextCol].recentyT;
//			}
//		}
//
//
//		if (nextRow - 1 < 0 || nextCol + 1 >= M) {
//			// 초과한 범위
//			if (nextCol - 1 < 0) {
//				nextRow += 1;
//			}
//			else {
//				int diff = nextCol + 1;
//				int diffcol = nextCol;
//				nextRow += diff;
//				nextCol -= diffcol;
//			}
//		}
//		else {
//			nextRow -= 1;
//			nextCol += 1;
//		}
//
//	}
//	return receive;
//}

Pair selectReceive() {
	Pair receive = { 0 };
	int maxRecent = 21e8;
	int maxim = -1;

	int cnt = N * M;

	int nextRow = 0;
	int nextCol = 0;

	int stRow = 0;
	int stCol = 0;
	// 9 7 4
	// 8 5 2
	// 6 3 1 크기순

	while (1 == 1) {
		//cout << "\n====지금위치 " << nextRow << "," << nextCol << "\n";

		int nowScore = Map[nextRow][nextCol].score;
		if (nowScore <= 0) {
			if (nextRow == N - 1 && nextCol == M - 1)break;
			if (nextRow - 1 < 0 || nextCol + 1 >= M) {
				// 범위 초과
				// 위로 이동하거나 왼쪽으로 이동
				if (stRow + 1 >= N) {
					// 아래로 이동 못함 오른쪽으로 가야함
					// row 는 무조건 N-1 col 는?
					nextRow = N - 1;
					stCol++;
					nextCol = stCol;
				}
				else {
					// 아래로 이동 col 는 무조건 0
					nextCol = 0;
					stRow++;
					nextRow = stRow;
				}
			}
			else {
				// 위에 오른쪽으로 가면 됨
				nextRow -= 1;
				nextCol += 1;
			}
			continue;
		}
		if (maxim < nowScore) {
			receive.row = nextRow;
			receive.col = nextCol;
			maxim = nowScore;
			maxRecent = Map[nextRow][nextCol].recentyT;
		}
		else if (maxim == nowScore) {
			if (maxRecent > Map[nextRow][nextCol].recentyT) {
				receive.row = nextRow;
				receive.col = nextCol;
				maxim = nowScore;
				maxRecent = Map[nextRow][nextCol].recentyT;
			}
		}


		if (nextRow == N-1 && nextCol == M-1)break;
		if (nextRow - 1 <0 || nextCol + 1 >= M) {
			// 범위 초과
			// 위로 이동하거나 왼쪽으로 이동
			if (stRow + 1 >= N) {
				// 아래로 이동 못함 오른쪽으로 가야함
				// row 는 무조건 N-1 col 는?
				nextRow = N-1;
				stCol++;
				nextCol = stCol;
			}
			else {
				// 아래로 이동 col 는 무조건 0
				nextCol = 0;
				stRow++;
				nextRow = stRow;
			}
		}
		else {
			// 위에 오른쪽으로 가면 됨
			nextRow -= 1;
			nextCol += 1;
		}
	}

	return receive;
}





vector<int> startLaser(Pair attach, Pair receive) {
	//bfs 방식
	int visited[11][11] = { 0 };
	queue<Pair> q;
	queue<vector<int>> qv;
	q.push(attach);
	vector<int> v = { 0 };
	qv.push(v);
	visited[attach.row][attach.col] = 1;
	
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		vector<int> nowDir = qv.front(); qv.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			// 지도 효과
			if (nextRow == -1)nextRow = N - 1;
			if (nextCol == -1)nextCol = M - 1;
			if (nextRow == N)nextRow = 0;
			if (nextCol == M)nextCol = 0;
			//if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M)continue;
			if (visited[nextRow][nextCol] > 0)continue;
			if (Map[nextRow][nextCol].score <= 0)continue;
			visited[nextRow][nextCol] = 1;

			
			// 공격지점 도착
			if (nextRow == receive.row && nextCol == receive.col) {
				//while (!q.empty())q.pop();
				//while (!qv.empty())qv.pop();
				return nowDir;
				// 넣기 전해 해야 도착지점 안들어감
			}
			vector<int> nowDir2 = nowDir;
			nowDir2.push_back(i);
			q.push({ nextRow,nextCol });
			qv.push(nowDir2);
			//nowDir.pop_back();// 될려나
		}
	}

	return {-1};
}

int startDafo(Pair attach, Pair receive) {
	
	int allScore = Map[attach.row][attach.col].score;
	int halfScore = allScore / 2;

	for (int i = 0; i < 8; i++) {
		int nextRow = receive.row + dfdr[i];
		int nextCol = receive.col + dfdc[i];
		// 지도 효과
		if (nextRow == -1)nextRow = N - 1;
		if (nextCol == -1)nextCol = M - 1;
		if (nextRow == N)nextRow = 0;
		if (nextCol == M)nextCol = 0;

		//if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M)continue;
		if (Map[nextRow][nextCol].score <= 0)continue;
		// 나는 피 안담
		if (nextRow == attach.row && nextCol == attach.col)continue;

		// 피 깍이기
		Map[nextRow][nextCol].score -= halfScore;
		Map[nextRow][nextCol].pari = 1;
		if (Map[nextRow][nextCol].score <= 0)life--;
		if (life <= 1) return -1;
	}
	// 타겟은 그대로 타격
	Map[receive.row][receive.col].score -= allScore;
	if (Map[receive.row][receive.col].score <= 0)life--;
	if (life <= 1) return -1;
	else return 0;

}

int LaserStart(Pair attach, Pair receive, vector<int> trace) {
	int count = trace.size();

	int allScore = Map[attach.row][attach.col].score;
	int halfScore = allScore / 2;
	
	int nextRow = attach.row;
	int nextCol = attach.col;

	for (int i = 1; i < count; i++) {
		// trace[i] 는 0~3 인 상하좌우
		nextRow = nextRow + dr[trace[i]];
		nextCol = nextCol + dc[trace[i]];

		// 지도 효과
		if (nextRow == -1)nextRow = N - 1;
		if (nextCol == -1)nextCol = M - 1;
		if (nextRow == N)nextRow = 0;
		if (nextCol == M)nextCol = 0;

		//if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= M)continue;
		if (Map[nextRow][nextCol].score <= 0)continue;
		// 나는 피 안담
		if (nextRow == attach.row && nextCol == attach.col)continue;


		Map[nextRow][nextCol].score -= halfScore;
		Map[nextRow][nextCol].pari = 1;
		if (Map[nextRow][nextCol].score <= 0)life--;
		if (life <= 1) return -1;
	}
	// 타겟은 그대로 타격
	Map[receive.row][receive.col].score -= allScore;
	if (Map[receive.row][receive.col].score <= 0)life--;
	if (life <= 1) return -1;
	else return 0;
}

void plusPotop(Pair attach, Pair receive) {
	Map[attach.row][attach.col].pari = 1;
	Map[receive.row][receive.col].pari = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Map[i][j].pari == 1) {
				Map[i][j].pari = 0;
				continue;
			}
			if (Map[i][j].score <= 0)continue;
			Map[i][j].score += 1;
		}
	}
}

int startTurn(int nowTurn) {
	// 공격자 선정
	Pair attach = selectAttach();
	//cout << "\n===========공격끝===============\n";
	// 공격 받는애 선정
	Pair receive = selectReceive();

	//cout << "\n=========초기=============\n";
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < M; j++) {
	//		cout << Map[i][j].score << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n======================\n";

	// 공격자 공업
	int sumNM = N + M;
	Map[attach.row][attach.col].score += sumNM;
	Map[attach.row][attach.col].recentyT = nowTurn;
	//cout << "\n 공격자 좌표 " << attach.row << "," << attach.col << "\n";
	//cout << "\n 공격q받는애 좌표 " << receive.row << "," << receive.col << "\n";

	//cout << "\n======공격자 점수추가후================\n";
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < M; j++) {
	//		cout << Map[i][j].score << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n======================\n";
	// 레이저공격 시도
	vector<int> ansLaser = startLaser(attach, receive);
	if (ansLaser[0] == -1) {
		//실패 => 대포 시작 대포는 무조건 됨
		//Pair attach = selectAttach();
		int dafo = startDafo(attach, receive);
		if (dafo == -1)return -1;
	}
	else {
		//성공 점수 깍이기 시작
		int laser = LaserStart(attach, receive, ansLaser);
		if (laser == -1)return -1;
	}

	// 0 인 애들 검사 - 업어도 되는 부분
	if (life <= 1) return -1;

	//cout << "\n==========공격끝난후============\n";
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < M; j++) {
	//		cout << Map[i][j].score<<" ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n======================\n";

	// 관여 안한 애들 +1 씩
	plusPotop(attach, receive);

	//cout << "\n=======+1한 후===============\n";
	//for (int i = 0; i < N; i++) {
	//	for (int j = 0; j < M; j++) {
	//		cout << Map[i][j].score << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n======================\n";
	return 0;

}

int finishScore() {
	int maxim = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int nowScore = Map[i][j].score;
			if (maxim < nowScore) {
				maxim = nowScore;
			}
		}
	}
	return maxim;
}

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j].score;
			if (Map[i][j].score > 0) {
				life++;
			}
		}
	}

	for (int i = 1; i <= K; i++) {
		int ans = startTurn(i);
		if (ans == -1)break;
	}

	// 최종 최대 값
	int ans = finishScore();
	cout << ans;

	return 0;
}
