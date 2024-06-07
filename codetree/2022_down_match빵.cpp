#include<iostream>
#include<queue>
using namespace std;

struct Node {
	int gun;
	bool operator<(Node right) const{
		if (right.gun > gun)return true;
		if (right.gun < gun)return false;
		return false;
	}
};

struct Pair { int row, col; };
struct MAP { int play; priority_queue<Node> gun; }; // 총은 여러개 가능 한칸에
struct PLAY { int row, col, dir, skil, gun, point; };
int n, m, k;
MAP Map[21][21];
PLAY play[30];

// 방향
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

void compareGun(Pair nowPoi, int num) {
	priority_queue<Node> nowList = Map[nowPoi.row][nowPoi.col].gun;
	
	// 근데 아마 mygun은 0
	int myGun = play[num].gun;
	Node topGun = nowList.top();
	if (myGun >= topGun.gun) {
		// 아무일도 없ㅇ음
		return;
	}
	else {
		play[num].gun = topGun.gun;
		Map[nowPoi.row][nowPoi.col].gun.pop(); //제일 높은거 하나 삭제후 내거 추가
		if (myGun > 0) {
			Map[nowPoi.row][nowPoi.col].gun.push({ myGun });
		}
	}
}

void moveLoser(int num) {
	int nowRow = play[num].row;
	int nowCol = play[num].col;
	int nowDir = play[num].dir;

	for (int i = 0; i < 4; i++) {
		if (nowDir == 4)nowDir = 0;
		int nextRow = nowRow + dr[nowDir];
		int nextCol = nowCol + dc[nowDir];
		// 범위 초과나 플레이어 만나면 90 도 회전 nowDor ++;
		if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n || Map[nextRow][nextCol].play > 0) {
			nowDir++;
			continue;
		}
		else if(Map[nextRow][nextCol].gun.size()>0) {
			// 총 있는 경우
			compareGun({nextRow,nextCol},num);
		}

		Map[nextRow][nextCol].play = num;
		play[num].row = nextRow;
		play[num].col = nextCol;
		play[num].dir = nowDir;
		break;

	}

}

void startMatch(int first, int second) {

	PLAY winerP = play[first];
	PLAY loserP = play[second];

	int winer = first;
	int loser = second;

	// 결투하는 좌표
	Pair matchPoi = { winerP.row, winerP.col };

	int firstPoint = winerP.skil + winerP.gun;
	int secondPoint = loserP.skil + loserP.gun;

	if (firstPoint < secondPoint) {
		winer = second;
		loser = first;
	}
	else if (firstPoint == secondPoint) {
		// 같은경우는 skil만 비교
		if (winerP.skil < loserP.skil) {
			winer = second;
			loser = first;
		}
	}

	// 승부 끝
	// 이긴애 점수 주기
	int addPoint = (play[winer].skil + play[winer].gun) - (play[loser].skil + play[loser].gun);
	play[winer].point += addPoint;

	// 진애 이동하기
	// 먼저 총 내려놓음
	// Map 함수에 플레이서 갱신은 승자는 지금위치로 갱신 패자는 새로운 위치만 갱신

	// 패자 원래 위치 없애야함
	//Map[play[loser].row][play[loser].col].play = 0;

	// 먼저 진애 총 있는지 검사
	if (play[loser].gun > 0) {
		// 총 있음 좌표에 추가
		Map[matchPoi.row][matchPoi.col].gun.push({ play[loser].gun });
		play[loser].gun = 0;
	}
	// 이제 움직일 차례 
	moveLoser(loser);

	// 이제 이긴애 점수는 추가했으므로 Map에 갱신ㄱ하 총 검사
	Map[matchPoi.row][matchPoi.col].play = winer;

	// 총 검사
	if (Map[matchPoi.row][matchPoi.col].gun.size() > 0) {
		compareGun({ matchPoi.row,matchPoi.col }, winer);
	}


}

void startMove(int num) {
	PLAY nowP = play[num];

	int nowRow = nowP.row;
	int nowCol = nowP.col;

	int nextRow = nowRow + dr[nowP.dir];
	int nextCol = nowCol + dc[nowP.dir];
	
	// 무조건 앞이든 뒤든 움직임
	if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n) {
		nextRow = nowRow - dr[nowP.dir];
		nextCol = nowCol - dc[nowP.dir];
		// 이거 하면 반대방향 됨
		if (nowP.dir == 0)play[num].dir = 2;
		else if (nowP.dir == 1)play[num].dir = 3;
		else if (nowP.dir == 2)play[num].dir = 0;
		else if (nowP.dir == 3)play[num].dir = 1;
	}
	else {
		nextRow = nowRow + dr[nowP.dir];
		nextCol = nowCol + dc[nowP.dir];
	}

	// 일단 플레이어 배열의 위치는 움직여놓기 승자패자 선정후 이동할 때 편하게
	// 배열애는 적용 x
	Map[play[num].row][play[num].col].play = 0;
	play[num].row = nextRow;
	play[num].col = nextCol;

	// 움직일 위치에 나서 총있는지 플레이어 있는지 검사
	// 근데 플레이어 있는지 부터 검사해야함
	if (Map[nextRow][nextCol].play > 0) {
		// 먼저 위치한 애랑 나랑 싸움
		startMatch(Map[nextRow][nextCol].play, num);
	}
	else if (Map[nextRow][nextCol].gun.size() > 0) {
		// 플레이어 없고 총 있는 경우
		compareGun({ nextRow,nextCol }, num);
		Map[nextRow][nextCol].play = num;
		Map[nowRow][nowCol].play = 0;
	}
	else {
		Map[nextRow][nextCol].play = num;
		Map[nowRow][nowCol].play = 0;
	}

}

void startGame() {
	// 사람수 만큼 돌기
	for (int i = 1; i <= m; i++) {
		startMove(i);
	}
}

void getPoint() {
	for (int i = 1; i <= m; i++) {
		cout << play[i].point << " ";
	}
}

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int nowGun;
			cin >> nowGun;
			if (nowGun == 0)continue;
			Map[i][j].gun.push({ nowGun });
		}
	}
	for (int i = 1; i <= m; i++) {
		int r, c, d, s;
		cin >> r >> c >> d >> s;
		play[i].row = r;
		play[i].col = c;
		play[i].dir = d;
		play[i].skil = s;
		Map[r][c].play = i;
	}

	for (int i = 1; i <= k; i++) {
		//cout <<i<< "  =============지금턴===============\n";

		//for (int r = 1; r <= n; r++) {
		//	for (int c = 1; c <= n; c++) {
		//		cout << Map[r][c].play << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n=============시작전===============\n";


		startGame();
	}

	getPoint();

	return 0;
}
