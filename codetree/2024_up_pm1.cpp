#include<iostream>
using namespace std;

struct map {int index, exitFlag;};
struct Pair { int row, col; };
int R, C, K;
map arr[71][71];

// 출구 방향
int Edr[4] = { -1,0,1,0 };
int Edc[4] = { 0,1,0,-1 };

// 아래 방향 검사
int Ddr[3] = {1,2,1};
int Ddc[3] = {-1,0,1};

// 왼쪽 방향 - 오른쪽 방향 검사
int LRdr[5] = {-1,0,1,1,2};
int Ldc[5] = {-1,-2,-2,-1,-1}; // 오른쪽은 부호 반대

void Reset() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			arr[i][j].exitFlag = 0;
			arr[i][j].index = 0;
		}
	}
}

bool goDown(Pair nowPoi, int index) {
	for (int i = 0; i < 3; i++) {
		int nextRow = nowPoi.row + Ddr[i];
		int nextCol = nowPoi.col + Ddc[i];
		if (nextCol < 0 || nextCol >= C || nextRow >= R || (arr[nextRow][nextCol].index>0 && arr[nextRow][nextCol].index != index)) {
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
			if (nextCol < 0 || nextCol >= C || nextRow >= R || (arr[nextRow][nextCol].index > 0 && arr[nextRow][nextCol].index != index)) {
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
		arr[nowPoi.row][nowPoi.col - 1] = { 0,0 };
		arr[nowPoi.row + 1][nowPoi.col + 1] = arr[nowPoi.row][nowPoi.col + 1];
		arr[nowPoi.row][nowPoi.col + 1] = { 0,0 };
		arr[nowPoi.row + 2][nowPoi.col] = arr[nowPoi.row - 1][nowPoi.col];
		arr[nowPoi.row - 1][nowPoi.col] = { 0,0 };
	}
	else {
		nowPoi.row += 1;
		for (int i = 0; i < 4; i++) {
			int nextRow = nowPoi.row + Edr[i];
			int nextCol = nowPoi.col + Edc[i];
			if (nextRow < 0)continue;
			arr[nextRow][nextCol].index = index;
		}
		if (nowPoi.row == 1) {
			arr[0][nowPoi.col - 1].index = 0;
			arr[0][nowPoi.col + 1].index = 0;
		}
	}
}

void moveLR(Pair nowPoi, int LR) {
	if (nowPoi.row >= 1) {
		arr[nowPoi.row + 1][nowPoi.col + 1 * LR] = arr[nowPoi.row][nowPoi.col];
		arr[nowPoi.row][nowPoi.col] = { 0,0 };
		arr[nowPoi.row + 1][nowPoi.col + 2 * LR] = arr[nowPoi.row - 1][nowPoi.col];
		arr[nowPoi.row - 1][nowPoi.col] = { 0,0 };
		arr[nowPoi.row + 2][nowPoi.col + 1 * LR] = arr[nowPoi.row][nowPoi.col - 1 * LR];
		arr[nowPoi.row][nowPoi.col - 1 * LR] = { 0,0 };
	}
	else {

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
			moveLR(nowPoi, -1);
			nowPoi.row += 1;
			nowPoi.col -= 1;
			exitDir -= 1; // 여기서만 정하고 (배열에 안정하고) 마지막에 적용
			if (exitDir == -1)exitDir = 3;
			continue;
		}
		if (goLR(nowPoi,-1, index)) {
			// 오른쪽으로
			moveLR(nowPoi, 1);
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
			Reset();
		}
		else {
			// 배열에 지금 착률한애 출구 표시
			arr[nowPoi.row + Edr[exitDir]][nowPoi.col + Edc[exitDir]].exitFlag = 1;
		}

		break;
	}

}

int main() {
	cin >> R >> C >> K;
	for (int i = 1; i <= K; i++) {
		startCol(i); // 1 우주선 출발
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				cout << arr[j][k].index << " ";
			}
			cout << "\n";
		}
		cout << "======================================\n";

	}


	return 0;
}
