#include<iostream>
#include<queue>
using namespace std;

// dp안쓰고 dfs쓰면 오져서 시간초과 bfs쓰면 큐에 존나 많이 담겨서 메모리 초과 되는듯


//struct map {int index, exitFlag;};
struct Pair { int row, col; };
struct Pindex { int row, col, index; };

int R, C, K;
int arr[71][71];
Pair indexMatchExit[1001];
int indexMatchCenter[1001];
//int visited[1001];
int maxValue = -1;
int sumScore;

// 지금 우주선에 도착하면 최대값은 얼마인지 저장하는 배열
int maxDp[1001];

// 십자가 전체 
int dr[5] = { 0,-1,0,1,0 };
int dc[5] = { 0,0,1,0,-1 };

// 출구 방향
int Edr[4] = { -1,0,1,0 };
int Edc[4] = { 0,1,0,-1 };

// 아래 방향 검사
int Ddr[3] = {1,2,1};
int Ddc[3] = {-1,0,1};

// 왼쪽 방향 - 오른쪽 방향 검사
int LRdr[5] = {-1,0,1,1,2};
int Ldc[5] = {-1,-2,-2,-1,-1}; // 오른쪽은 부호 반대

void Reset(int index) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			//arr[i][j].exitFlag = 0;
			arr[i][j] = 0;
		}
	}
	// 이거 할 필요 없음 어차피 인덱스 한번 쓰면 다시 안씀 배열만 초기화하면 쓸일없음
	//for (int i = 1; i <= index; i++) {
	//	indexMatchExit[i] = { 0 };
	//	indexMatchCenter[i] = 0;;
	//}
}

bool goDown(Pair nowPoi, int index) {
	for (int i = 0; i < 3; i++) {
		int nextRow = nowPoi.row + Ddr[i];
		int nextCol = nowPoi.col + Ddc[i];
		if (nextCol < 0 || nextCol >= C || nextRow >= R || (nextRow >= 0 &&  arr[nextRow][nextCol]>0 && arr[nextRow][nextCol] != index)) {
			// 지도 초과 및 우주선 있는 경우 못감
			return false;
		}
	}
	return true;
}

bool goLR(Pair nowPoi, int dir, int index) {
	for (int i = 0; i < 5; i++) {
		int nextRow = nowPoi.row + LRdr[i];
		int nextCol = nowPoi.col + (dir *Ldc[i]); {
			if (nextCol < 0 || nextCol >= C || nextRow >= R || (nextRow >=0 && arr[nextRow][nextCol] > 0 && arr[nextRow][nextCol] != index)) {
				// 지도 초과 및 우주선 있는 경우 못감
				return false;
			}
		}
	}
	return true;
}


void moveDown(Pair nowPoi, int index) {
	if (nowPoi.row >= 1){
		arr[nowPoi.row + 1][nowPoi.col - 1] = arr[nowPoi.row][nowPoi.col - 1];
		arr[nowPoi.row][nowPoi.col - 1] = { 0};
		arr[nowPoi.row + 1][nowPoi.col + 1] = arr[nowPoi.row][nowPoi.col + 1];
		arr[nowPoi.row][nowPoi.col + 1] = { 0};
		arr[nowPoi.row + 2][nowPoi.col] = arr[nowPoi.row - 1][nowPoi.col];
		arr[nowPoi.row - 1][nowPoi.col] = { 0};
	}
	else {
		for (int i = 0; i < 5; i++) {
			//제거
			int nextRow = nowPoi.row + dr[i];
			int nextCol = nowPoi.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= R || nextCol >= C)continue;
			arr[nextRow][nextCol] = 0;
		}
		nowPoi.row += 1;
		for (int i = 0; i < 5; i++) {
			//생성
			int nextRow = nowPoi.row + dr[i];
			int nextCol = nowPoi.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= R || nextCol >= C)continue;
			arr[nextRow][nextCol] = index;
		}
	}
}

void moveLR(Pair nowPoi, int LR, int index) {
	if (nowPoi.row >= 1) {
		arr[nowPoi.row + 1][nowPoi.col + 1 * LR] = arr[nowPoi.row][nowPoi.col];
		arr[nowPoi.row][nowPoi.col] = { 0};
		arr[nowPoi.row + 1][nowPoi.col + 2 * LR] = arr[nowPoi.row - 1][nowPoi.col];
		arr[nowPoi.row - 1][nowPoi.col] = { 0};
		arr[nowPoi.row + 2][nowPoi.col + 1 * LR] = arr[nowPoi.row][nowPoi.col - 1 * LR];
		arr[nowPoi.row][nowPoi.col - 1 * LR] = { 0};
	}
	else {
		for (int i = 0; i < 5; i++) {
			//제거
			int nextRow = nowPoi.row + dr[i];
			int nextCol = nowPoi.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= R || nextCol >= C)continue;
			arr[nextRow][nextCol] = 0;
		}
		// 이 점을 중심으로 십자가 채우면 알아서 회전경우 됨
		nowPoi.row += 1;
		nowPoi.col += 1 * LR; 
		for (int i = 0; i < 5; i++) {
			//생성
			int nextRow = nowPoi.row + dr[i];
			int nextCol = nowPoi.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= R || nextCol >= C)continue;
			arr[nextRow][nextCol] = index;
		}
	}
}

//int flags;
//void getDfs(Pair nowPoi, int index) {
//	if (flags == 1)return;
//	int nowMaxRow = indexMatchCenter[index]+2;
//	if (nowMaxRow > maxValue)maxValue = nowMaxRow;
//	if (maxDp[index] == R) {
//		maxValue = R;
//		flags = 1;
//		return;
//	}
//	if (maxValue == R) {
//		flags = 1;
//		return;
//	}
//	//cout << "\n 지금 위치 좌표" << nowPoi.row << "," << nowPoi.col << "지금 최대값" << maxValue << "\n";
//	for (int i = 0; i < 4; i++) {
//		int nextRow = nowPoi.row + Edr[i];
//		int nextCol = nowPoi.col + Edc[i];
//		if (nextRow < 0 || nextCol < 0 || nextRow >= R || nextCol >= C)continue;
//		// 없는칸이거나 내우주선이면 넘김
//		if (arr[nextRow][nextCol].index == 0 || arr[nextRow][nextCol].index == index)continue;
//		if (visited[index] == 1)continue;
//		visited[index] = 1;
//		int nextIndex = arr[nextRow][nextCol].index;
//		Pair nextPoi = indexMatchExit[nextIndex];
//		getDfs(nextPoi, nextIndex);
//		visited[index] = 0; // 초기화될려나
//	}
//}


int visited[1001];
void getBfs(Pair nowPoi, int index) {
	queue<Pindex> q;
	q.push({nowPoi.row,nowPoi.col ,index});
	visited[index] = 1;
	int flag = 0;
	while (!q.empty()) {
		Pindex now = q.front(); q.pop();
		//Pair nowExit = indexMatchExit[index];

		int nowIndex = now.index;
		int nowMaxRow = indexMatchCenter[nowIndex] + 2;
		if (nowMaxRow > maxValue)maxValue = nowMaxRow;

		if (maxValue == R) {
			break;
		}
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + Edr[i];
			int nextCol = now.col + Edc[i];
			if (arr[nextRow][nextCol] == 0 || arr[nextRow][nextCol] == nowIndex)continue;
			int nextIndex = arr[nextRow][nextCol];
			if (visited[nextIndex] == 1)continue;
			Pair nextExit = indexMatchExit[nextIndex];
			if (maxDp[nowIndex] != 0) {
				if (maxDp[nowIndex] > maxValue) {
					flag = 1;
					maxValue = maxDp[nowIndex];
				}
				//cout << "\n dp사용" << nowIndex;
			}
			q.push({ nextExit.row, nextExit.col,nextIndex });
		}
		if (flag == 1)break;
	}
}

void startCol(int index) {
	int stCol, exitDir;
	cin >> stCol >> exitDir; // 시작 col, 출구위치

	Pair nowPoi = { -2,stCol-1 }; // 센터 위치

	while (1 == 1) {
		if (goDown(nowPoi, index)) {
			// 아래로
			moveDown(nowPoi, index);
			nowPoi.row += 1;
			continue;
		}
		if (goLR(nowPoi,1, index)) {
			// 왼쪽으로
			moveLR(nowPoi, -1,index);
			nowPoi.row += 1;
			nowPoi.col -= 1;
			exitDir -= 1; // 여기서만 정하고 (배열에 안정하고) 마지막에 적용
			if (exitDir == -1)exitDir = 3;
			continue;
		}
		if (goLR(nowPoi,-1, index)) {
			// 오른쪽으로
			moveLR(nowPoi, 1,index);
			nowPoi.row += 1;
			nowPoi.col += 1;
			exitDir += 1; // 여기서만 정하고 (배열에 안정하고) 마지막에 적용
			if (exitDir == 4)exitDir = 0;
			continue;
		}
		// 여기 오면 정지
		// 꽉찬지 착륙한지 판단
		if (nowPoi.row < 1) {
			//배열 초기화
			Reset(index);
		}
		else {
			// 배열에 지금 착률한애 출구 표시
			indexMatchExit[index] = {(nowPoi.row + Edr[exitDir]), (nowPoi.col + Edc[exitDir])};
			indexMatchCenter[index] = nowPoi.row; // 무조건 이거보다 1큼
			//arr[nowPoi.row + Edr[exitDir]][nowPoi.col + Edc[exitDir]].exitFlag = 1;
			// 이후 점수계산
			Pair nowExit = indexMatchExit[index];
			maxValue = -1;
			//flags = 0;
			getBfs(nowExit,index);
			maxDp[index] = maxValue;
			for (int i = 0; i <= index; i++)visited[i] = 0;
			//cout << "\n"<<"maxVlaue"<< maxValue <<"\n";
			sumScore += maxValue;
		}
		break;
	}
}

int main() {
	cin >> R >> C >> K;
	for (int i = 1; i <= K; i++) {
		startCol(i); // 1 우주선 출발
		//for (int j = 0; j < R; j++) {
		//	for (int k = 0; k < C; k++) {
		//		cout << arr[j][k] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "======================================\n";

	}
	//cout << "\n 최종점수" << sumScore;
	cout << sumScore;
	return 0;
}
