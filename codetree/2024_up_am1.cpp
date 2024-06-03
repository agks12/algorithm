#include<iostream>
#include<vector>
#include<queue>
using namespace std;

# 회전할때 우선순위 열부터인데 행부터로 해서 틀림 / 실수

struct Pair { int row, col; };
struct MaxInfo { Pair maxDir; int maxCnt, maxDeg; };
int K, M;
int Map[6][6];
int arr[301];
int visited[6][6];
int Mindex;
struct Node {
	int row, col;
	bool operator<(Node right) const{
		if (right.col < col)return true;
		if (right.col > col)return false;
		if (right.row > row)return true;
		if (right.row < row)return false;
		//if (right.row == row && right.col < col)true;
		return false;
	}
};

// 중심좌표 주변 8좌표 왼상부터 시계방향
// 90도 회전시 복사배열은 6 부터 시작해야 매치됨 기본 배열에 +6, +4 만함
int dr[8] = { -1,-1,-1,0,1,1,1,0 }; //int dr90[8] = {1,0,-1,-1,-1,0,1,1};
int dc[8] = { -1,0,1,1,1,0,-1,-1 }; //int dc90[8] = {-1,-1,-1,0,1,1,1,0};

// bfs용
int dr4[4] = { -1,1,0,0 };
int dc4[4] = { 0,0,1,-1 };


void rotate(Pair center, int deg) {
	int copyMap[5][5] = { 0 };
	for (int i = 0; i < 8; i++) {
		int nextRow = center.row + dr[i];
		int nextCol = center.col + dc[i];
		copyMap[nextRow][nextCol] = Map[nextRow][nextCol];
	}
	for (int i = 0; i < 8; i++) {
		int nextOriginRow = center.row + dr[i];
		int nextOriginCol = center.col + dc[i];
		int copyIndex = i + deg;
		if (copyIndex >= 8) copyIndex -= 8; // 각도에 따라서 올바른 인덱스 계산
		int nextCopyRow = center.row + dr[copyIndex];
		int nextCopyCol = center.col + dc[copyIndex];
		Map[nextOriginRow][nextOriginCol] = copyMap[nextCopyRow][nextCopyCol];
	}
}

// 개수만 찾는 함수
int bfs(Pair center) {
	int cnt = 1;
	visited[center.row][center.col] = 1;
	queue<Pair> q;
	q.push(center);
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr4[i];
			int nextCol = now.col + dc4[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= 5 || nextCol >= 5)continue;
			if (Map[now.row][now.col] != Map[nextRow][nextCol])continue; // 유물 안이어짐
			if (visited[nextRow][nextCol] > 0)continue;
			cnt++; // 이게 3개 이상이여야 유물
			visited[nextRow][nextCol] = 1;
			q.push({ nextRow,nextCol });
		}
	}
	return cnt;
}

// 1인 bfs 전용
vector<Pair> bfsQ(Pair center) {
	vector<Pair> v;
	v.push_back(center);
	visited[center.row][center.col] = 1;
	queue<Pair> q;
	q.push(center);
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr4[i];
			int nextCol = now.col + dc4[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= 5 || nextCol >= 5)continue;
			if (Map[now.row][now.col] != Map[nextRow][nextCol])continue; // 유물 안이어짐
			if (visited[nextRow][nextCol] > 0)continue;
			v.push_back({ nextRow,nextCol }); // 이게 3개 이상이여야 유물
			visited[nextRow][nextCol] = 1;
			q.push({ nextRow,nextCol });
		}
	}
	return v;
}

int findUm() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// 초기화
			visited[i][j] = 0;
		}
	}
	int Count = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// 이미가면 못감
			if (visited[i][j] > 0)continue;
			Pair center = { i, j };
			int ans = bfs(center);
			if (ans < 3)continue; // 3보다 작은 유물이면 버림
			// 유물 찾으면 기록해야함 
			Count += ans;
		}
	}
	return Count; // 총 유물개수
}

// 총 유뮬 위치 반환
priority_queue<Node> findUmDir() {
	priority_queue<Node> pq;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// 초기화
			visited[i][j] = 0;
		}
	}
	int Count = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// 이미가면 못감
			if (visited[i][j] > 0)continue;
			Pair center = { i, j };
			vector<Pair> ans = bfsQ(center);
			if (ans.size() < 3)continue; // 3보다 작은 유물이면 버림
			// 유물 찾으면 기록해야함 pq에
			int loopSize = ans.size();
			for (int i = 0; i < loopSize; i++) {
				Pair now = ans[i];
				Node nowDir = { 0 };
				nowDir.row = now.row;
				nowDir.col = now.col;
				pq.push(nowDir);
			}
		}
	}
	return pq; // 총 유물개수
}

MaxInfo rotateAllCase() {
	int Maxim = -1;
	MaxInfo maxinfo = { 0 };
	for (int rot = 0; rot < 3; rot++) {
		int deg = 6;
		if (rot == 1)deg = 4;
		if (rot == 2)deg = 2;
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				// 90 도 부터 시작 , 작은 열부터, 작은 행부터 하므로 자동으로 회전순위 맞춤
				Pair center = { j,i }; // 우선순위 열이우선 (세로)
				rotate(center, deg); // 1번 회전


				//cout << "\n";
				//for (int i = 0; i < 5; i++) {
				//	for (int j = 0; j < 5; j++) {
				//		cout << Map[i][j] << " ";
				//	}
				//	cout << "\n";
				//}
				//cout << "\n========================\n";


				//최대유물 계산
				int ans = findUm();
				if (ans > Maxim) {
					maxinfo.maxDir = { j,i };
					maxinfo.maxCnt = ans;
					maxinfo.maxDeg = deg;
					Maxim = ans; //최대값기록
				}
				// 다음 가지전에 회전 배열 원래배열 건드리므로 원상복구해야함
				// 반시계 90도 경우는 deg = 2, 180도는 그대로 4
				int reverce = deg;
				if (deg == 6)reverce = 2;
				else if (deg == 2)reverce = 6;
				rotate(center, reverce); // 1번 역 회전 원상복구
			}
		}
	}
	return maxinfo;
}

int startTurn() {
	MaxInfo Maxinfo = rotateAllCase(); // 모든 회전경우의 수 에서 가장 많은 유물 찾기
	// 일단 회전으로 최대 유물 찾기 끝
	// 유물 없는 경우 근데 항상 발견된데

	//cout << "center"<<Maxinfo.maxDir.row << "," << Maxinfo.maxDir.col<<","<<Maxinfo.maxDeg <<Maxinfo.maxCnt << "\n";

	//cout << "\n";
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		cout << Map[i][j]<<" ";
	//	}
	//	cout<<"\n";
	//}
	//cout << "\n===============회전전=========\n";



	if (Maxinfo.maxCnt < 3)return -1;
	int Score = 0;
	// 첫번째에 유물 있음 - 무조건
	rotate(Maxinfo.maxDir, Maxinfo.maxDeg); // 일단 회전 배열 변경
	//cout << "\n 요기 값" << Maxinfo.maxCnt << "\n";
	//cout << "\n";
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		cout << Map[i][j] << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n============회전후============\n";


	// 연쇄 작용때문에 while 돌려야함
	while (1 == 1) {
		//vector<Pair> removeSet = bfsQ(Maxinfo.maxDir);
		// 1번 유물 전환 끝나면 findUm 써서 유물 있는지 판단
		int flag = findUm();
		if (flag < 3)break;

		//cout << "\n 나 1번 유물 점수" << flag << "\n";
		Score += flag;
		priority_queue<Node> pq = findUmDir(); // 총 유물위치
		while (!pq.empty()) {
			Node now = pq.top(); pq.pop();
			//cout << "\n 지금 변경할 좌표 " << now.row << "," << now.col << "\n";
			Map[now.row][now.col] = arr[Mindex];
			Mindex++;
		}
		//cout << "\n";
		//for (int i = 0; i < 5; i++) {
		//	for (int j = 0; j < 5; j++) {
		//		cout << Map[i][j] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n==============변경후==========\n";

	}
	return Score;
}

int main() {
	cin >> K >> M;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			cin >> Map[i][j];
	for (int i = 0; i < M; i++)cin >> arr[i];
	for (int i = 1; i <= K; i++) {
		int nowTurnScore = startTurn();
		if (nowTurnScore == -1)break;
		cout << nowTurnScore << " ";
	}
	cout << "\n";

	return 0;
}
