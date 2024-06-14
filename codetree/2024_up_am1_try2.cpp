#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node { int row, col;
bool operator<(Node right)const {
	if (right.col < col)return true;
	if (right.col > col)return false;
	if (right.row > row)return true;
	if (right.row < row)return false;
	return false;
	}
};
struct Pair { int row, col; };

int K, M;
int map[6][6];
int visited[6][6];
int umol[302];
int umolIndex = 1;

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

void rotateMap(Pair center, int deg) {
	// 일단 맵 복사
	int copyMap[6][6] = { 0 };

	// 시작 좌상, 끝 우하 설정
	int stRow = center.row - 1;
	int stCol = center.col - 1;
	int endRow = center.row + 1;
	int endCol = center.col + 1;
	for (int r = stRow; r <= endRow; r++) {
		for (int c = stCol; c <= endCol; c++) {
			copyMap[r][c] = map[r][c];
		}
	}
	// 3x3 회전
	for (int r = 0; r <= 2; r++) {
		for (int c = 0; c <= 2; c++) {
			if (deg == 0) {
				//90 도
				map[stRow + c][endCol - r] = copyMap[stRow + r][stCol + c];
			}
			else if (deg == 1) {
				// 180도
				map[endRow-r][endCol-c] = copyMap[stRow + r][stCol + c];
			}
			else if (deg == 2) {
				// 270도
				map[endRow - c][stCol+r] = copyMap[stRow + r][stCol + c];
			}
		}
	}
}

int countBFS(Pair nowPoi) {
	int nowValue = map[nowPoi.row][nowPoi.col];
	int cnt = 1;
	queue<Pair> q;
	q.push(nowPoi);
	visited[nowPoi.row][nowPoi.col] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > 5 || nextCol > 5)continue;
			if (map[nextRow][nextCol] != nowValue)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			visited[nextRow][nextCol] = 1;
			cnt++;
			q.push({ nextRow,nextCol });
		}
	}
	// 한 부분에서 2이하이면 유물 아님
	if (cnt <= 2)return 0;
	else return cnt;
}

int countMap() {

	// visited 초기화
	for (int r = 1; r <= 5; r++) {
		for (int c = 1; c <= 5; c++) {
			
			visited[r][c]=0;
		}
	}

	int getSum = 0;
	// 맵 전체 탐색
	for (int r = 1; r <= 5; r++) {
		for (int c = 1; c <= 5; c++) {
			if (visited[r][c] == 1)continue;
			// 지금 위치에서 같은거 탐색시작
			int nowC = countBFS({ r,c });
			getSum += nowC;
		}
	}

	return getSum;
}

int searchMap() {

	int maxCnt = -1;
	Pair maxPoi = { 0 };
	int maxDeg = -1;

	// 각도 열 행 순
	for (int i = 0; i < 3; i++) {
		// 90 180 270 순
		for (int c = 2; c <= 4; c++) {
			for (int r = 2; r <= 4; r++) {
				// 3x3중심좌표이므로 2~4까지

				// r,c 중심으로 회전 // i값이 각도
				rotateMap({ r,c },i);
				// 회전된 상태에서 유뮬 개수 구하기
				int nowCnt = countMap();
				if (nowCnt > maxCnt) {
					maxCnt = nowCnt;
					maxPoi.row = r;
					maxPoi.col = c;
					maxDeg = i;
				}
				// 회 전 원상복구 
				if(i==0)rotateMap({ r,c }, 2);
				else if(i==1)rotateMap({ r,c }, 1);
				else if(i==2)rotateMap({ r,c }, 0);
			}
		}
	}

	if (maxCnt < 3)return -1;
	// 다 찾았으면 maxPoi로 회전 하기
	rotateMap(maxPoi, maxDeg);
	return 0;
}

vector<Pair> subGetBFS(Pair nowPoi) {
	vector<Pair> v = {nowPoi};
	int nowValue = map[nowPoi.row][nowPoi.col];
	int cnt = 1;
	queue<Pair> q;
	q.push(nowPoi);
	visited[nowPoi.row][nowPoi.col] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > 5 || nextCol > 5)continue;
			if (map[nextRow][nextCol] != nowValue)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			visited[nextRow][nextCol] = 1;
			v.push_back({ nextRow,nextCol });
			q.push({ nextRow,nextCol });
		}
	}
	// 한 부분에서 2이하이면 유물 아님
	return v;
}

priority_queue<Node> getBFS() {
	// visited 초기화
	for (int r = 1; r <= 5; r++) {
		for (int c = 1; c <= 5; c++) {

			visited[r][c] = 0;
		}
	}

	priority_queue<Node> pq;
	// 맵 전체 탐색
	for (int r = 1; r <= 5; r++) {
		for (int c = 1; c <= 5; c++) {
			if (visited[r][c] == 1)continue;
			// 지금 위치에서 같은거 탐색시작
			vector<Pair> v = subGetBFS({ r,c });
			if (v.size() <= 2)continue;
			// 유물 된 부분 pq에 삽입
			for (int i = 0; i < v.size(); i++) {
				Pair now = v[i];
				pq.push({now.row,now.col});
			}

		}
	}

	return pq;
}

int startReplace() {
	int nowCnt = 0;
	// 무한 반복 유물 없을떄까지
	while (1==1) {
		// 유물 좌표들
		priority_queue<Node> nowList = getBFS();
		if (nowList.size() < 3)break;
		// 대채하기
		while (!nowList.empty()) {
			nowCnt++;
			Node now = nowList.top(); nowList.pop();
			int nowRow = now.row;
			int nowCol = now.col;
			int nowUmol = umol[umolIndex];

			// 대치
			map[nowRow][nowCol] = nowUmol;

			umolIndex++;
		}
	}
	return nowCnt;
}

int main() {
	cin >> K >> M;
	for (int r = 1; r <= 5; r++) {
		for (int c = 1; c <= 5; c++) {
			cin >> map[r][c];
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> umol[i];
	}

	for (int i= 1; i <= K; i++) {
		int ans = searchMap(); // 이거 끝나면 제일 큰거로 회전 끝
		if (ans == -1)break; // 유물 없으면 바로 종료
		
		// 고정된 맵에서 유뮬 찾고 대채하면 됨
		int getCnt = startReplace();
		cout << getCnt<<" ";
	}

	return 0;
}
