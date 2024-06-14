#include<iostream>
#include<queue>
using namespace std;

// 같은 방식이여도 dfs인 경우는 시가촤과남 bfs는 더빠름
//해당문제에서는 각 격자칸를 노드로 봤을때 인접한 격자간 간선이 있다고 볼 수 있습니다
//이렇게 되면 그래프에서 간선의 가중치는 모두 1로 같습니다
//경로탐색에 있어서 그래프의 간선의 가중치가 모두 같다면 bfs알고리즘은 시간복잡도 O(V)를 가지며, dfs알고리즘은 그래프 형태에 따라 최대 O(V!) 까지도 가집니다
//이때 V는 노드의 개수를 의미합니다

struct Pair { int row, col; };
struct Node { Pair exitPoi; int maxRow; };
Node arrInfo[1002];
int R, C, K;
int map[72][72];
int visited[72][72];

int MR;

// 착지용
int dr5[5] = { 0,1,-1,0,0 };
int dc5[5] = { 0,0,0,-1,1 };

// 출구용
int dr4[4] = { -1,0,1,0 };
int dc4[4] = { 0,1,0,-1 }; 

int goDown(Pair center, int nowIndex) {
	// 이 함수는 무조건 한칸만 가야함
	Pair arr[3] = { 0 };
	Pair stLeft = { center.row + 1,center.col-1 };
	Pair stmid = { center.row + 2,center.col };
	Pair stRight = { center.row + 1,center.col+1 };
	arr[0] = stLeft;
	arr[1] = stmid;
	arr[2] = stRight;


	// 아래 3곳 가능한지 검사
	for (int i = 0; i < 3; i++) {
		int nextRow = arr[i].row;
		int nextCol = arr[i].col;
		if (nextRow <= 0 || nextCol <= 0)continue;
		if (map[nextRow][nextCol] > 0 || nextRow > R || nextCol > C)return -1;
	}

	// 여기 까지 오면 갈 수 있음

	// 먼저 맵 지우기
	for (int i = 0; i < 5; i++) {
		int nextRow = center.row + dr5[i];
		int nextCol = center.col + dc5[i];
		if (nextRow <= 0 || nextCol <= 0)continue; // 큰거는 고려 x
		map[nextRow][nextCol] = 0;
	}

	// 한칸 이동 
	center.row += 1;
	
	// 맵에 새로운 위치 적용
	for (int i = 0; i < 5; i++) {
		int nextRow = center.row + dr5[i];
		int nextCol = center.col + dc5[i];
		if (nextRow <= 0 || nextCol <= 0)continue; // 큰거는 고려 x
		map[nextRow][nextCol] = nowIndex;
	}

	return 0;
}

int goLeft(Pair center, int nowIndex) {
	// 이 함수는 무조건 한칸만 가야함
	Pair arr[5] = { 0 };
	Pair stLeft = { center.row + 1,center.col - 2 };
	Pair stmid = { center.row + 1,center.col - 1 };
	Pair stRight = { center.row + 2,center.col - 1 };
	Pair stRight2 = { center.row - 1,center.col - 1 };
	Pair stRight3 = { center.row,center.col - 2 };
	arr[0] = stLeft;
	arr[1] = stmid;
	arr[2] = stRight;
	arr[3] = stRight2;
	arr[4] = stRight3;


	// 아래 3곳 가능한지 검사
	for (int i = 0; i < 5; i++) {
		int nextRow = arr[i].row;
		int nextCol = arr[i].col;
		if (nextRow <= 0)continue;
		if (map[nextRow][nextCol] > 0 ||nextCol <= 0 || nextRow > R || nextCol > C)return -1;
	}

	// 여기 까지 오면 갈 수 있음

	// 먼저 맵 지우기
	for (int i = 0; i < 5; i++) {
		int nextRow = center.row + dr5[i];
		int nextCol = center.col + dc5[i];
		if (nextRow <= 0 || nextCol <= 0)continue; // 큰거는 고려 x
		map[nextRow][nextCol] = 0;
	}

	// 한칸 이동 
	center.row += 1;
	center.col -= 1;

	// 맵에 새로운 위치 적용
	for (int i = 0; i < 5; i++) {
		int nextRow = center.row + dr5[i];
		int nextCol = center.col + dc5[i];
		if (nextRow <= 0 || nextCol <= 0)continue; // 큰거는 고려 x
		map[nextRow][nextCol] = nowIndex;
	}

	return 0;
}

int goRight(Pair center, int nowIndex) {
	// 이 함수는 무조건 한칸만 가야함
	Pair arr[5] = { 0 };
	Pair stLeft = { center.row + 1,center.col + 2 };
	Pair stmid = { center.row + 1,center.col + 1 };
	Pair stRight = { center.row + 2,center.col + 1 };
	Pair stRight2 = { center.row - 1,center.col + 1 };
	Pair stRight3 = { center.row,center.col + 2 };
	arr[0] = stLeft;
	arr[1] = stmid;
	arr[2] = stRight;
	arr[3] = stRight2;
	arr[4] = stRight3;


	// 아래 3곳 가능한지 검사
	for (int i = 0; i < 5; i++) {
		int nextRow = arr[i].row;
		int nextCol = arr[i].col;
		if (nextRow <= 0)continue;
		if (map[nextRow][nextCol] > 0 || nextCol <= 0 || nextRow > R || nextCol > C)return -1;
	}

	// 여기 까지 오면 갈 수 있음

	// 먼저 맵 지우기
	for (int i = 0; i < 5; i++) {
		int nextRow = center.row + dr5[i];
		int nextCol = center.col + dc5[i];
		if (nextRow <= 0 || nextCol <= 0)continue; // 큰거는 고려 x
		map[nextRow][nextCol] = 0;
	}

	// 한칸 이동 
	center.row += 1;
	center.col += 1;

	// 맵에 새로운 위치 적용
	for (int i = 0; i < 5; i++) {
		int nextRow = center.row + dr5[i];
		int nextCol = center.col + dc5[i];
		if (nextRow <= 0 || nextCol <= 0)continue; // 큰거는 고려 x
		map[nextRow][nextCol] = nowIndex;
	}

	return 0;
}

void resetMap() {
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			map[r][c] = 0;
		}
	}
}

void folling(int nowCol, int nowDir, int nowIndex) {
	Pair center = { -1,nowCol };
	int exitDir = nowDir;
	
	while (1 == 1) {
		// 내려가기
		int gd = goDown(center, nowIndex);
		if (gd == 0) {
			center.row += 1;
			continue;
		}
		// 왼쪽회전
		int gL = goLeft(center, nowIndex);
		if (gL == 0) {
			center.row += 1;
			center.col -= 1;
			exitDir--;
			if (exitDir == -1)exitDir = 3;
			continue;
		}
		// 오른쪽회전
		int gR = goRight(center, nowIndex);
		if (gR == 0) {
			center.row += 1;
			center.col += 1;
			exitDir++;
			if (exitDir == 4)exitDir = 0;
			continue;
		}

		// 여기 까지 오면 갈데 없음 멏워야함
		// 근데 center가 2보다 작으면 reset해야함
		if (center.row < 2)resetMap();
		else {
			// 성공적 착지 이므로 배열에 저장
			int exitRow = center.row + dr4[exitDir];
			int exitCol = center.col + dc4[exitDir];
			arrInfo[nowIndex].exitPoi = { exitRow,exitCol };
			arrInfo[nowIndex].maxRow = center.row + 1;
		}
		break;

	}
}

//void findMaxRow(Pair nowPoi,int nowIndex) {
//	int nowRow = arrInfo[nowIndex].maxRow;
//	if (MR < nowRow) {
//		MR = nowRow;
//		if (MR == R)return;
//	}
//	
//	for (int i = 0; i < 4; i++) {
//		int nextRow = nowPoi.row + dr4[i];
//		int nextCol = nowPoi.col + dc4[i];
//		if (nextRow <= 0 || nextCol <= 0 || nextRow > R || nextCol > C)continue;
//		if (map[nextRow][nextCol] == nowIndex || map[nextRow][nextCol] == 0)continue;
//		if (visited[nextRow][nextCol] == 1)continue;
//		visited[nextRow][nextCol] = 1;
//		// 다음 시작위치는 nextIndex 즉 맵의 값에 해당하는 arrInfo값의 출구 위치
//		int nextIndex = map[nextRow][nextCol];
//		Pair nextPoi = arrInfo[nextIndex].exitPoi;
//		findMaxRow(nextPoi, nextIndex);
//		visited[nextRow][nextCol] = 0;
//	}
//
//
//}

void findMaxRow(Pair nowPoi, int nowIndex) {
	queue<Pair> q;
	q.push(nowPoi);
	int visited2[72][72] = { 0 };
	visited2[nowPoi.row][nowPoi.col] = 1;


	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		int nowIndex = map[now.row][now.col];
		int nowRow = arrInfo[nowIndex].maxRow;
		if (MR < nowRow) {
			MR = nowRow;
			if (MR == R)return;
		}
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr4[i];
			int nextCol = now.col + dc4[i];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > R || nextCol > C)continue;
			if (map[nextRow][nextCol] == nowIndex || map[nextRow][nextCol] == 0)continue;
			if (visited2[nextRow][nextCol] == 1)continue;
			visited2[nextRow][nextCol] = 1;
			// 다음 시작위치는 nextIndex 즉 맵의 값에 해당하는 arrInfo값의 출구 위치
			int nextIndex = map[nextRow][nextCol];
			Pair nextPoi = arrInfo[nextIndex].exitPoi;
			q.push(nextPoi);
			//findMaxRow(nextPoi, nextIndex);
			//visited[nextRow][nextCol] = 0;
		}
	}



}



int main() {
	int getAns = 0;
	cin >> R >> C >> K;
	for (int i = 1; i <= K; i++) {
		int c, d;
		cin >> c >> d;
		folling(c,d,i);
		Pair nowPoi = arrInfo[i].exitPoi; // 시작위치

		//cout << "\n";

		//for (int r = 1; r <= R; r++) {
		//	for (int c = 1; c <= C; c++) {
		//		cout<< map[r][c] <<" ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n==============착지후==================\n\n\n\n";



		MR = -1;
		if (arrInfo[i].maxRow == R) {
			getAns += R;
			//cout << R<<"\n";
			continue;
		}
		visited[nowPoi.row][nowPoi.col] = 1;
		findMaxRow(nowPoi,i);
		visited[nowPoi.row][nowPoi.col] = 0;

		//cout << MR << "\n";
		getAns += MR;
	}

	cout << getAns;
	return 0;
}
