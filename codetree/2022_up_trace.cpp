#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 순방향 역방향 전환시점 고려해야됨 원위치 오고나서 바꿈

struct Pair { int row, col; };
struct runer { int row, col, dir, nowDir, dead; }; // 1 좌우
struct MAP { vector<int> run; int tree; };
int n, m, h, k;
runer arr[10001];
MAP Map[100][100];
runer tracker;
int center;
int dirFlag;
// 좌우 위아래 방향 row 는 0
int lr[2] = {1,-1};// 항상 1 로 시작 오른쪽 또는 아래

int nowCan=1;// 처음에 1칸 갈 수 있음
int nowMoveDir;
int nowDirIndex=1;

// 술래 방향
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int cal(Pair target) {
	Pair center = { tracker.row, tracker.col };

	int dx = abs(center.row - target.row);
	int dy = abs(center.col - target.col);

	return (dx + dy);
}

void realMove(runer nowRun, int nowIndex) {

	int nowRow = arr[nowIndex].row;
	int nowCol = arr[nowIndex].col;

	int nextRow = nowRow;
	int nextCol = nowCol;

	if (arr[nowIndex].dir == 1) {
		// 좌우 col 고정
		nextCol = nowCol + lr[arr[nowIndex].nowDir];

	}
	else if (arr[nowIndex].dir == 2) {
		//상하 row 고정
		nextRow = nowRow + lr[arr[nowIndex].nowDir];
	}

	if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n) {
		// 범위 초과
		arr[nowIndex].nowDir++;
		if (arr[nowIndex].nowDir == 2)arr[nowIndex].nowDir = 0;

		if (arr[nowIndex].dir == 1) {
			// 좌우 col 고정
			nextCol = nowCol + lr[arr[nowIndex].nowDir];

		}
		else if (arr[nowIndex].dir == 2) {
			//상하 row 고정
			nextRow = nowRow + lr[arr[nowIndex].nowDir];
		}
	}
	//범위 초과 x그대로

	if (nextRow == tracker.row && nextCol == tracker.col) {
		return;// 술래 있으면 못감
	}

	// 아니면 그냥 감

	Map[nextRow][nextCol].run.push_back(nowIndex);	
	// 기존 위치 없애기
	Map[nowRow][nowCol].run.erase(remove(Map[nowRow][nowCol].run.begin(), Map[nowRow][nowCol].run.end(), nowIndex), Map[nowRow][nowCol].run.end());
	nowRun.row = nextRow;
	nowRun.col = nextCol;
	arr[nowIndex].row = nextRow;
	arr[nowIndex].col = nextCol;

}

void moveRuner() {
	// 도망자 애들 1번씩 움직이기
	for (int i = 1; i <= m; i++) {
		runer nowRun = arr[i];
		if (nowRun.dead == 1)continue;
		// 거리 계산
		int distance = cal({ nowRun.row, nowRun.col });
		if (distance > 3)continue;// 3 초과거리 버림
		//cout << "\n" << i << " 좌표"<<nowRun.row<<","<<nowRun.col<<"\n";
		realMove(nowRun,i);
	}
}

void popagation() {
	int nextRow = tracker.row + dr[tracker.nowDir];
	int nextCol = tracker.col + dc[tracker.nowDir];
	tracker.row = nextRow;
	tracker.col = nextCol;
	// 아래 과정 끝나면 방향 전환까지 되있음
	nowMoveDir++;
	if (nowCan == nowMoveDir) {
		// 끝가지 가서 방향 전환
		tracker.nowDir++;
		if (tracker.nowDir == 4)tracker.nowDir = 0;
		nowDirIndex++; // 회전 2번 하면 칸수 증갛야함
		if (nowDirIndex == 3) {
			nowDirIndex = 1;
			nowCan++;
		}
		nowMoveDir = 0; // 지금 칸수 
	}

	// 여기서 역방향 검사 해야될듯
	nextRow = tracker.row + dr[tracker.nowDir];
	nextCol = tracker.col + dc[tracker.nowDir];
	if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n) {
		// 역방향 시작
		dirFlag = 1;
		if (tracker.nowDir == 0)tracker.nowDir = 2;
		else if (tracker.nowDir == 1)tracker.nowDir = 3;
		else if (tracker.nowDir == 2)tracker.nowDir = 0;
		else if (tracker.nowDir == 3)tracker.nowDir = 1;
		//nowMoveDir--;
		//cout << "nowMoveDir" << nowMoveDir << "nowDirIndex" << nowDirIndex << "nowCan" << nowCan << "\n";
	}
}

void backPopagation() {



	int nextRow = tracker.row + dr[tracker.nowDir];
	int nextCol = tracker.col + dc[tracker.nowDir];
	tracker.row = nextRow;
	tracker.col = nextCol;
	// 아래 과정 끝나면 방향 전환까지 되있음
	nowMoveDir--;
	if (0 == nowMoveDir) {
		// 끝가지 가서 방향 전환
		tracker.nowDir--;
		if (tracker.nowDir == -1)tracker.nowDir = 3;
		nowDirIndex--; // 회전 2번 하면 칸수 증갛야함
		if (nowDirIndex == 0) {
			nowDirIndex = 2;
			nowCan--;
		}
		nowMoveDir = nowCan;
	}
	//cout << "\n\nnowMoveDir  " << nowMoveDir << "nowDirIndex  " << nowDirIndex << "nowCan  " << nowCan << "\n";

	// 여기서 역방향 검사 해야될듯
	if (tracker.row == center && tracker.col == center) {
		// 순방향 시작
		dirFlag = 0;
		//cout << " 순방향 시작  nowMoveDir" << nowMoveDir << "nowDirIndex" << nowDirIndex << "nowCan" << nowCan << "\n";
		nowMoveDir = 0;
		nowDirIndex = 1;
		nowCan = 1;
		tracker.nowDir = 0;
		return;
	}

}

void moveTrace() {
	int nextRow = tracker.row + dr[tracker.nowDir];
	int nextCol = tracker.col + dc[tracker.nowDir];

	if (dirFlag == 0) {
		// 순방향
		popagation();
	}
	else if (dirFlag == 1) {
		// 역방행
		backPopagation();
	}

}

int getCatch(int nowTurn) {
	int nowRow = tracker.row;
	int nowCol = tracker.col;
	int nowD = tracker.nowDir;

	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		if (nowRow <= 0 || nowCol <= 0 || nowRow > n || nowCol > n || Map[nowRow][nowCol].tree == 1) {
			nowRow += dr[nowD];
			nowCol += dc[nowD];
			continue;
		}

		cnt += Map[nowRow][nowCol].run.size();
		// 애내들 삭제
		int loop = Map[nowRow][nowCol].run.size();
		for (int i = 0; i < loop; i++) {
			int nowPlay = Map[nowRow][nowCol].run[i];
			arr[nowPlay].dead = 1;
		}
		Map[nowRow][nowCol].run.clear();

		nowRow += dr[nowD];
		nowCol += dc[nowD];
	}

	return (nowTurn * cnt);
}

int main() {
	// 술래는 정 중앙에 위치하려면 무조건 인풋배열크기는 홀수여야하는데
	cin >> n >> m >> h >> k;
	for (int i = 1; i <= m; i++) {
		// 도망자 정보
		int r, c, d;
		cin >> r >> c >> d;
		arr[i].row = r;
		arr[i].col = c;
		arr[i].dir = d;
		Map[r][c].run.push_back(i);
	}
	for (int i = 0; i < h; i++) {
		// 나무정보
		int r, c;
		cin >> r >> c;
		Map[r][c].tree = 1;
	}
	// 술래 위치
	tracker.row = (n / 2) + 1;
	tracker.col = (n / 2) + 1;
	tracker.nowDir = 0;
	center = (n / 2) + 1;

	int count = 0;
	for (int i = 1; i <= k; i++) {
		moveRuner();
		moveTrace();

		//cout << "술래 위치" << tracker.row << "," << tracker.col << "  방햔" << tracker.nowDir<<"\n";

		int ans = getCatch(i);
		count += ans;
	}

	cout << count;

	return 0;
}
