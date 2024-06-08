#include<iostream>
#include<queue>
using namespace std;

// dfs여러번 쓸때 visited 무조건 쓰면서 초기화 안하려면 visited[][]=1, dfs(), visited[][]=0 하면됨 - 이러면 visited1개로 가능


struct Pair { int row, col; };
struct Team { int stRow, stCol, endRow, endCol, point; };
struct MAP { int val, teamN; };
int n, m, k;
MAP map[21][21];
int visited[21][21] = { 0 };
int visitedHead[21][21];
Team teamArr[6];
int Head;
int dr[4] = { 0,1,0,-1 };
int dc[4] = { -1,0,1,0 };

void findSE(Pair stPoi, int teamN) {
	queue<Pair> q;
	q.push(stPoi);
	visited[stPoi.row][stPoi.col] = 1;
	map[stPoi.row][stPoi.col].teamN = teamN;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		if (map[now.row][now.col].val == 1) {
			// 지금팀의 시작위치 찾음
			teamArr[teamN].stRow = now.row;
			teamArr[teamN].stCol = now.col;
		}
		if (map[now.row][now.col].val == 3) {
			// 지금팀의 마지막위치 찾음
			teamArr[teamN].endRow = now.row;
			teamArr[teamN].endCol = now.col;
		}
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n)continue;
			if (map[nextRow][nextCol].val == 0)continue;
			if (visited[nextRow][nextCol] == 1)continue;

			map[nextRow][nextCol].teamN = teamN;



			visited[nextRow][nextCol] = 1;
			q.push({ nextRow,nextCol });
		}
	}
}

Pair findStDir(Pair nowStPoi, int teamN) {
	Pair nowEndPoi = { teamArr[teamN].endRow, teamArr[teamN].endCol };
	for (int i = 0; i < 4; i++) {
		int nextRow = nowStPoi.row + dr[i];
		int nextCol = nowStPoi.col + dc[i];
		if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n)continue;
		// 머리의 다음경로는 무저간 4번값있는곳
		if (map[nextRow][nextCol].val == 4 || map[nextRow][nextCol].val == 3) {
			return { nextRow,nextCol };
		}
	}
}

//void spcace(Pair stPoi, int teamN) {
//	for (int i = 0; i < 4; i++) {
//		int nextRow = stPoi.row + dr[i];
//		int nextCol = stPoi.col + dc[i];
//		if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n)continue;
//		if (map[nextRow][nextCol].val == 0)continue;
//		if (map[nextRow][nextCol].val == 4)continue;
//
//		if (map[nextRow][nextCol].val == 2) {
//			// 여기는 1로 바꿈
//			map[nextRow][nextCol].val = 1;
//			teamArr[teamN].stRow = nextRow;
//			teamArr[teamN].stCol = nextCol;
//		}
//		else if (map[nextRow][nextCol].val == 3) {
//			// 여기는 2로 바꿈
//			map[nextRow][nextCol].val = 2;
//		}
//	}
//	// stpoi는 3으로 바꿈
//	map[stPoi.row][stPoi.col].val = 3;
//	teamArr[teamN].endRow = stPoi.row;
//	teamArr[teamN].endCol = stPoi.col;
//}

void spcace(Pair stPoi, int teamN) {
	for (int i = 0; i < 4; i++) {
		int nextRow = stPoi.row + dr[i];
		int nextCol = stPoi.col + dc[i];
		if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n)continue;
		if (map[nextRow][nextCol].val == 0)continue;
		if (map[nextRow][nextCol].val == 4)continue;

		if (map[nextRow][nextCol].val == 2) {
			// 여기는 3로 바꿈
			map[nextRow][nextCol].val = 3;
			teamArr[teamN].endRow = nextRow;
			teamArr[teamN].endCol = nextCol;
		}
		else if (map[nextRow][nextCol].val == 1) {
			// 여기는 2로 바꿈
			map[nextRow][nextCol].val = 2;
		}
	}
	// stpoi는 1으로 바꿈
	map[stPoi.row][stPoi.col].val = 1;
	teamArr[teamN].stRow = stPoi.row;
	teamArr[teamN].stCol = stPoi.col;
}

void moveDfs(Pair nowPoi, Pair nextPoi, Pair nowEndPoi, int teamN) {
	

	// 한칸 전진
	map[nextPoi.row][nextPoi.col] = map[nowPoi.row][nowPoi.col];
	
	if (nextPoi.row == nowEndPoi.row && nextPoi.col == nowEndPoi.col) {
		// 다이어진 4없는 기차인 경우 바로 이거 들어옴
		spcace(nowEndPoi, teamN);
		return;
	}

	// 끝 나는 지점
	if (map[nowPoi.row][nowPoi.col].val == 3) {
		// 팀 위치 배열값 끝값 변경
		teamArr[teamN].endRow = nextPoi.row;
		teamArr[teamN].endCol = nextPoi.col;
		map[nowPoi.row][nowPoi.col].val = 4;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nextRow = nowPoi.row + dr[i];
		int nextCol = nowPoi.col + dc[i];
		if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n)continue;
		if (map[nextRow][nextCol].val == 0)continue;
		if (map[nextRow][nextCol].val == 4)continue;
		if (visitedHead[nextRow][nextCol] == 1)continue;
		//if (visitedDfs[nextRow][nextCol] > 0)continue;
		visitedHead[nextRow][nextCol] = 1;
		moveDfs({ nextRow,nextCol }, nowPoi, nowEndPoi, teamN);
		visitedHead[nextRow][nextCol] = 0;
		return;
	}
}



void startMove(int round) {
	// 팀 개수만큼 
	for (int i = 1; i <= m; i++) {
		Pair nowStPoi = { teamArr[i].stRow, teamArr[i].stCol };
		Pair nextPoi = findStDir(nowStPoi,i);
		// 팀 위치 배열값 시작값 변경
		teamArr[i].stRow = nextPoi.row;
		teamArr[i].stCol = nextPoi.col;
		// 시작위치 다음위치로 dfs시작
		visitedHead[nowStPoi.row][nowStPoi.col] = 1;

		// 끝 원래 3이 있던 우;ㅣㅊ;ㅣ
		Pair nowEndPoi = { teamArr[i].endRow, teamArr[i].endCol };

		visitedHead[nextPoi.row][nextPoi.col] = 1;
		moveDfs(nowStPoi, nextPoi, nowEndPoi, i);
		visitedHead[nextPoi.row][nextPoi.col] = 0;
		visitedHead[nowStPoi.row][nowStPoi.col] = 0;

		// 다음위치 값 4아닐수도 3일수도
		//int val = map[nextPoi.row][nextPoi.col].val;
		//if (val == 4) {
		//	visitedHead[nextPoi.row][nextPoi.col] = 1;
		//	moveDfs(nowStPoi, nextPoi, i, val);
		//	visitedHead[nextPoi.row][nextPoi.col] = 0;

		//}
		//else if(val==3){
		//	// 그냥 1번을 기준으로 1 3(원래 1번 자리) 2
		//	// fh qkRn로 바꾸면됨
		//	spcace(nowStPoi,i);
		//}

		//visitedHead[nowStPoi.row][nowStPoi.col] = 0;

		//cout << i << "\n========시작gn============\n";
		//for (int i = 0; i < n; i++) {
		//	for (int j = 0; j < n; j++) {
		//		cout << map[i][j].val << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n====================\n";


	}
}



void findHead(int level, Pair stPoi) {

	if (map[stPoi.row][stPoi.col].val == 3) {
		return;
	}

	if (map[stPoi.row][stPoi.col].val == 1) {
		Head = level;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nextRow = stPoi.row + dr[i];
		int nextCol = stPoi.col + dc[i];
		if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n)continue;
		if (map[nextRow][nextCol].val == 0 || map[nextRow][nextCol].val == 4 || map[nextRow][nextCol].val==3)continue;
		if (visitedHead[nextRow][nextCol] == 1)continue;
		visitedHead[nextRow][nextCol] = 1;
		findHead(level + 1, { nextRow, nextCol });
		visitedHead[nextRow][nextCol] = 0;
	}
}

void findall(int level, Pair stPoi) {
	Head = level;
	for (int i = 0; i < 4; i++) {
		int nextRow = stPoi.row + dr[i];
		int nextCol = stPoi.col + dc[i];
		if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= n)continue;
		if (map[nextRow][nextCol].val == 0 || map[nextRow][nextCol].val == 4)continue;
		if (visitedHead[nextRow][nextCol] == 1)continue;
		visitedHead[nextRow][nextCol] = 1;
		findall(level + 1, { nextRow, nextCol });
		visitedHead[nextRow][nextCol] = 0;
	}
}

void changeDir(int teamN) {
	
	int headRow = teamArr[teamN].stRow;
	int headCol = teamArr[teamN].stCol;

	teamArr[teamN].stRow = teamArr[teamN].endRow;
	teamArr[teamN].stCol = teamArr[teamN].endCol;
	map[headRow][headCol].val = 3;
	map[teamArr[teamN].endRow][teamArr[teamN].endCol].val = 1;
	teamArr[teamN].endRow = headRow;
	teamArr[teamN].endCol = headCol;
	
}

void startBall(int round) {
	int titleN = (round / n) % 4; // 무조건 0 1 2 3 만 나옴 0 이면 좌  하 우 상 순서
	int subN = round % n; //  0번부터 시작 n-1 이면 마지막 뜻함
	//cout << "\n 지금 라운드" << round << "title, sub" << titleN << "," << subN<<"\n";
	int stRow = -1;
	int stCol = -1;
	int dir = 0;
	if (titleN == 0) {
		stRow = subN;
		stCol = 0;
		dir = 2;
	}
	else if (titleN == 1) {
		stRow = n-1;
		stCol = subN;
		dir = 3;
	}
	else if (titleN == 2) {
		stRow = n-1-subN;
		stCol = n-1;
		dir = 0;
	}
	else if (titleN == 3) {
		stRow = 0;
		stCol = n - 1 - subN;
		dir = 1;
	}

	//cout << "\n 지금 시작좀" << stRow << "," << stCol<<"방향"<<dir << "\n";
	// 공 굴릴 행이나 열 검사 애들있는지
	for (int i = 0; i < n; i++) {

		if (map[stRow][stCol].val == 0 || map[stRow][stCol].val == 4) {
			stRow += dr[dir];
			stCol += dc[dir];
			continue;
		}
		
		// 애들 만남 팀 추출
		int teamNum = map[stRow][stCol].teamN;

		// 자기가 머리인 경우
		if (map[stRow][stCol].val == 1) {
			//cout << "\n 맞은애1짜리" << stRow << "," << stCol << "\n";

			teamArr[teamNum].point += 1;
		}
		else if (map[stRow][stCol].val == 3) {
			Head = 0;
			visitedHead[stRow][stCol] = 1;
			findall(1, { stRow,stCol });
			visitedHead[stRow][stCol] = 0;

			teamArr[teamNum].point += Head * Head;
			//cout << "\n 맞은애 전체 " << stRow << "," << stCol << "," << Head << "\n";

		}
		else {
			Head = 0;
			visitedHead[stRow][stCol] = 1;
			visitedHead[teamArr[teamNum].endRow][teamArr[teamNum].endCol] = 1;
			findHead(1, { stRow,stCol });
			teamArr[teamNum].point += Head * Head;
			visitedHead[teamArr[teamNum].endRow][teamArr[teamNum].endCol] = 0;

			visitedHead[stRow][stCol] = 0;
			//cout << "\n 맞은애" << stRow << "," << stCol << "," << Head<< "\n";

			// 점수 찾는 dfs시작
		}
		// 끝이 맞은 경우 즉 3이 맞은 경우 최대길이
		// 
		// 방향 전환
		changeDir(teamNum);

		break;
	}
}

int getPoint() {
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		cnt += teamArr[i].point;
	}
	return cnt;
}

int main() {
	cin >> n >> m >> k;
	// 0부터 시작해야 라운드 계산시 편함
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j].val;
		}
	}


	// 시작 끝 번호 저장하기
	int teamN = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == 1)continue;
			if (map[i][j].val == 0)continue;
			findSE({i,j},teamN);
			teamN++;
		}
	}

	// 1부터 시작하면 나머지계산이 1230
	// 0부터 해야 편한듯
	for (int i = 0; i < k; i++) {

		//cout << i<<"\n========시작전============\n";
		//for (int i = 0; i < n; i++) {
		//	for (int j = 0; j < n; j++) {
		//		cout<< map[i][j].val<<" ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n====================\n";
		startMove(i);

		//cout << i << "\n========시작gn============\n";
		//for (int i = 0; i < n; i++) {
		//	for (int j = 0; j < n; j++) {
		//		cout << map[i][j].val << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n====================\n";

		startBall(i);

		//cout << i << "\n========시작gn============\n";
		//for (int i = 0; i < n; i++) {
		//	for (int j = 0; j < n; j++) {
		//		cout << map[i][j].val << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n====================\n";
	}

	int ans = getPoint();
	cout << ans;

	return 0;
}
