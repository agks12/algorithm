#include<iostream>
#include<queue>
using namespace std;

// 주사위 움직임 구현만 하면 간단한 문제

struct Pair { int row, col; };
struct Dice { int down, front; };
int n, m;

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1};

int map[21][21];
int startflag = 0;
int nowDir = 1;
int nowDiceV = 6;
Pair nowPoi = { 1,1 };
Dice nowDice = { 6,2 };


Dice arr[7][7][4] = {
	// 좌 우로 구르는거는 앞은 무조건 같은데?
	{}, // 아래 
	{ // 아래가 1인 경우
		{},//0
		{},// 상 우 하 좌
		{{5,1},{4,2},{2,6},{3,2}},
		{{4,1},{2,3},{3,6},{5,3}},
		{{3,1},{5,4},{4,6},{2,4}},
		{{2,1},{3,5},{5,6},{4,5}},
		{},
	},
	{// 아래가 2인 경우
		{},//0
		{{6,2},{3,1},{1,5},{4,1}},
		{},
		{{4,2},{6,3},{3,5},{1,3}},
		{{3,2},{1,4},{4,5},{6,4}},
		{},
		{{1,2},{4,6},{6,5},{3,6}},
	},
	{// 아래가 3인 경우
		{},//0
		{{6,3},{5,1},{1,4},{2,1}},
		{{5,3},{1,2},{2,4},{6,2}},
		{},
		{},
		{{2,3},{6,5},{5,4},{1,5}},
		{{1,3},{2,6},{6,4},{5,6}},
	},
	{// 아래가4인 경우
		{},//0
		{{6,4},{2,1},{1,3},{5,1}},
		{{5,4},{6,2},{2,3},{1,2}},
		{},
		{},
		{{2,4},{1,5},{5,3},{6,5}},
		{{1,4},{5,6},{6,3},{2,6}},
	},
	{// 아래가 5인 경우
		{},//0
		{{6,5},{4,1},{1,2},{3,1}},
		{},
		{{4,5},{1,3},{3,2},{6,3}},
		{{3,5},{6,4},{4,2},{1,4}},
		{},
		{{1,5},{3,6},{6,2},{4,6}},
	},
	{// 아래가 6인 경우
		{},//0
		{},
		{{5,6},{3,2},{2,1},{4,2}},
		{{4,6},{5,3},{3,1},{2,3}},
		{{3,6},{2,4},{4,1},{5,4}},
		{{2,6},{4,5},{5,1},{3,5}},
		{},
	}
};

//Dice arr[7][7][4] = {
//	// 좌 우로 구르는거는 앞은 무조건 같은데?
//	{}, // 아래 
//	{ // 아래가 1인 경우
//		{},//0
//		{},
//		{{5,1},{4,2},{2,6},{3,2}},
//		{{4,1},{2,3},{3,6},{5,3}},
//		{{3,1},{5,4},{4,6},{2,4}},
//		{{2,1},{3,5},{5,6},{4,5}},
//		{},
//	},
//	{// 아래가 2인 경우
//		{},//0
//		{{6,2},{3,1},{1,5},{4,1}},
//		{},
//		{{4,2},{6,3},{3,5},{1,3}},
//		{{3,2},{1,4},{4,5},{6,4}},
//		{},
//		{{1,2},{4,6},{6,5},{3,6}},
//	},
//	{// 아래가 3인 경우
//		{},//0
//		{{6,3},{5,1},{1,4},{2,1}},
//		{{5,3},{1,2},{2,4},{6,2}},
//		{},
//		{},
//		{{2,3},{6,5},{5,4},{1,5}},
//		{{1,3},{2,6},{5,4},{5,6}},
//	},
//	{// 아래가4인 경우
//		{},//0
//		{{6,4},{2,1},{1,3},{5,1}},
//		{{5,4},{6,2},{2,3},{1,2}},
//		{},
//		{},
//		{{2,4},{1,5},{5,3},{6,5}},
//		{{1,4},{5,6},{6,3},{2,6}},
//	},
//	{// 아래가 5인 경우
//		{},//0
//		{{6,5},{4,1},{1,2},{3,1}},
//		{},
//		{{4,6},{1,3},{3,2},{6,3}},
//		{{3,5},{6,4},{4,2},{1,4}},
//		{},
//		{{1,5},{3,6},{6,2},{4,6}},
//	},
//	{// 아래가 6인 경우
//		{},//0
//		{},
//		{{5,6},{3,2},{2,1},{4,2}},
//		{{4,6},{5,3},{3,1},{2,3}},
//		{{3,6},{2,4},{4,1},{3,5}},
//		{{2,6},{4,5},{5,1},{5,4}},
//		{},
//	}
//};

void moveDice() {
	if (startflag == 1) {
		if (map[nowPoi.row][nowPoi.col] > nowDiceV) {
			// 반시계 방햐ㅕㅇ
			nowDir--;
			if (nowDir == -1)nowDir = 3;
			//cout << "내가 작아서 반시계";
		}
		else if (map[nowPoi.row][nowPoi.col] < nowDiceV) {
			// 시계방향
			nowDir++;
			if (nowDir == 4)nowDir = 0;
			//cout << "내가 커서 시계";
		}
		else {
			//cout << "똑같음";
		}
	}
	startflag = 1;

	// 같으면 그대로
	int nextRow = nowPoi.row + dr[nowDir];
	int nextCol = nowPoi.col + dc[nowDir];
	if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n) {
		// 범위 초과이면 방향 정반다로 바꿈
		if (nowDir == 0)nowDir = 2;
		else if (nowDir == 1)nowDir = 3;
		else if (nowDir == 2)nowDir = 0;
		else if (nowDir == 3)nowDir = 1;
	}

	// 방향 설정 끝났으므로 움직임
	nowPoi.row += dr[nowDir];
	nowPoi.col += dc[nowDir];
	//cout << "지금값"<<nowDiceV << "바뀐 좌표" << nowPoi.row << " " << nowPoi.col << "\n";
	// 주사위 갱신
	// 지금 아래방향 값
	int nowDown = nowDice.down;
	// 지금 정면 값
	int nowFront = nowDice.front;
	nowDice = arr[nowDown][nowFront][nowDir];
	nowDiceV = nowDice.down;

	//cout << nowDown << " " << nowFront << " " << nowDir << "==>" << nowDice.down << " " << nowDice.front << "\n\n";
	
}


int getPoint() {
	int nowPoiV = map[nowPoi.row][nowPoi.col];
	int point = nowPoiV;
	queue<Pair> q;
	q.push(nowPoi);
	int visited[21][21] = { 0 };
	visited[nowPoi.row][nowPoi.col] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n)continue;
			if (visited[nextRow][nextCol] > 0)continue;
			if (map[nextRow][nextCol] != nowPoiV)continue;
			point += map[nextRow][nextCol];
			visited[nextRow][nextCol] = 1;
			q.push({ nextRow,nextCol });
		}
	}
	return point;
}


int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	int sumCnt = 0;
	for (int i = 1; i <= m; i++) {
		// 움직이는거먼저
		moveDice();
		int ans = getPoint();
		sumCnt += ans;
		//cout << ans<<"\n";
	}

	cout << sumCnt;

	return 0;
}
