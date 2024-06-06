#include<iostream>
#include<queue>
#include<vector>
using namespace std;


// 아래 부분에서 dis가 거리 반환 못하는 경우도 있는데 그거 여예 처리 안해서 안됨
// -1이 리턴이 아니라 21e8리턴 했어야함
// 자동으로 위 좌 우 하 우선순위 적용
//int dis = closeDis({ nextRow,nextCol }, target);
//if (dis != -1 && dis < minDis) {
//	minDis = dis;
//	minPoi = { nextRow,nextCol };
//}


struct findBase { 
	int dis, row, col;
	bool operator<(findBase right) const{
		if (right.dis < dis)return true;
		if (right.dis > dis)return false;
		if (right.row < row)return true;
		if (right.row > row)return false;
		if (right.col < col)return true;
		if (right.col > col)return false;
		return false;
	}
};
struct MAP { int base, del; };
struct Pair { int row, col; };
int vis[225];
MAP Map[16][16];
Pair miniStop[225]; // 편의점 위치 배열
Pair man[225]; // 사람 위치 배열
int n, m;
int life;
//int base[16][16];
// 시작 위치 찾는 방향 위 좌 우  하
int dr[4] = { -1,0,0,1 };
int dc[4] = { 0,-1,1,0 };

int closeDis( Pair stPoi, Pair target ){
	queue<Pair> q;
	q.push(stPoi);
	int visited[16][16] = { 0 };
	visited[stPoi.row][stPoi.col] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n)continue;
			if (Map[nextRow][nextCol].del == 1)continue;
			if (visited[nextRow][nextCol] > 0)continue;
			visited[nextRow][nextCol] = visited[now.row][now.col]+1;
			if (nextRow == target.row && nextCol == target.col) {
				return visited[nextRow][nextCol];
			}
			q.push({ nextRow,nextCol });
		}
	}
	return  -1;
}

int realMove(int nowN) {
	// 지금 애 위치 
	Pair nowPoi = man[nowN];
	// 타겟 편의점 위치
	Pair target = miniStop[nowN];

	int minDis = 21e8;
	Pair minPoi = { 0 };

	for (int i = 0; i < 4; i++) {
		// 4가지 방향 모두에 대해서 편의점 까지 거리 계산후 가장 짧은 거 사용
		// 멀어지는 경우이면 그게 제일 짧은거라서 안움직이는 경우는 없음
		int nextRow = nowPoi.row + dr[i];
		int nextCol = nowPoi.col + dc[i];
		if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n)continue;
		if (Map[nextRow][nextCol].del == 1)continue;
		// 이제 이 곳에서 bfs로 최단거리 검색
		// 만약 여기서 편의점 도달이면 바로 끝
		if (nextRow == target.row && nextCol == target.col) {
			man[nowN] = { nextRow,nextCol }; // 지금애 위치변경
			//Map[nextRow][nextCol].del = 1; 여기서 삭제하면 안됨
			return 1; // 1이면 도착한뜻 즉 1인애들은 샂게 
		}
		
		// 자동으로 위 좌 우 하 우선순위 적용
		int dis = closeDis({ nextRow,nextCol }, target);
		if (dis!=-1 && dis < minDis) {
			minDis = dis;
			minPoi = { nextRow,nextCol };
		}
	}

	// 지금 애 위치 변경
	man[nowN] = minPoi;
	// 지금애 편의점 도착
	if (minPoi.row == target.row && minPoi.col == target.col) {
		return 1;
	}
	return 0;
}

vector<int> moveToMS(int nowNum) {
	vector<int> v;

	if (nowNum > m)nowNum = m+1;
	// 2(번)분이면 1번만 움직임 
	for (int i = 1; i <= m; i++) {
		// 1번 부터 차례로 편의점으로 이동

		// 근데 편의점 도착한 애는 버림
		Pair nowManPoi = man[i];
		Pair nowStopPoi = miniStop[i];
		if (vis[i] == 1)continue;
		if (nowManPoi.row == 0 && nowManPoi.col == 0)continue;// 시작 안한애 버림
		//if (nowManPoi.row == nowStopPoi.row && nowManPoi.col == nowStopPoi.col)continue;
		//cout << "\n c처도는새기" << nowManPoi.row << "," << nowManPoi.col << "편의점위치 " << nowStopPoi.row << "," << nowStopPoi.col << "\n";
		int ans = realMove(i);
		if (ans == 1) {// 편의점 도착
			v.push_back(i);// 저장
		}
	}

	return v;
}

void removeList(vector<int> list) {
	int loopSize = list.size();
	for (int i = 0; i < loopSize; i++) {
		int nowN = list[i];
		Pair nowDelPoi = miniStop[nowN];
		Map[nowDelPoi.row][nowDelPoi.col].del = 1; // 영구삭제
		//cout << "번호" << nowN << "whkvy" << nowDelPoi.row << "," << nowDelPoi.col << "\n";
		vis[nowN] = 1;
		life--;
	}
}

//Pair startPoi(int nowNum) {
//	// 탐지 시작위치 = 편의점 
//	Pair stPoi = miniStop[nowNum];
//	queue<Pair> q;
//	q.push(stPoi);
//	int visited[16][16] = { 0 };
//	visited[stPoi.row][stPoi.col] = 1;
//	while (!q.empty()) {
//		Pair now = q.front(); q.pop();
//		for (int i = 0; i < 4; i++) {
//			int nextRow = now.row + dr[i];
//			int nextCol = now.col + dc[i];
//			if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n)continue;
//			if (Map[nextRow][nextCol].del == 1)continue;
//			if (visited[nextRow][nextCol] > 0)continue;
//			visited[nextRow][nextCol] = 1;
//			if (Map[nextRow][nextCol].base == 1) {
//				return { nextRow,nextCol };
//			}
//			q.push({ nextRow,nextCol });
//		}
//	}
//	return { -1,-1 };
//}


// 편의점에서 모든 베이스 캠프 찾아내기
Pair startPoi(int nowNum) {
	// 탐지 시작위치 = 편의점 
	Pair stPoi = miniStop[nowNum];
	priority_queue< findBase> pq;

	queue<Pair> q;
	q.push(stPoi);
	int visited[16][16] = { 0 };
	visited[stPoi.row][stPoi.col] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > n || nextCol > n)continue;
			if (Map[nextRow][nextCol].del == 1)continue;
			//if (base[nextRow][nextCol] == 1)continue;
			if (visited[nextRow][nextCol] > 0)continue;
			visited[nextRow][nextCol] = visited[now.row][now.col]+ 1;
			if (Map[nextRow][nextCol].base == 1) {
				pq.push({ visited[now.row][now.col] ,nextRow,nextCol });
			}
			q.push({ nextRow,nextCol });
		}
	}
	findBase first = pq.top();
	return { first.row,first.col };
}




int startGame() {

	int nowNum = 1;
	while (1 == 1) {
		//cout << "\n" << nowNum << "   " << life << "\n";
		//cout << "\n================시작전============\n";

		//for (int i = 1; i <= n; i++) {
		//	for (int j = 1; j <= n; j++) {
		//		
		//		cout<<Map[i][j].del<<" ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n================시작전============\n";

		// 이동 함수
		vector<int> delList = moveToMS(nowNum);
		// 삭제 함수
		removeList(delList);

		if (life == 0) {
			break;
		}
		// 시작위치 함수


		// 만약 시작 다했으면 버림
		if (nowNum > m) {
			// 1분 증가
			nowNum++;
			continue;
		}


		Pair nowStPoi = startPoi(nowNum);
		// 시작 위치 적용
		//cout << "\nwlr" << nowNum << "지금돺ㅅ," << nowStPoi.row << "," << nowStPoi.col;
		man[nowNum] = nowStPoi;
		//base[nowStPoi.row][nowStPoi.col] = 1;
		// 시작한곳 이제 못감
		Map[nowStPoi.row][nowStPoi.col].del = 1;




		//cout << "\n================시작후============\n";

		//for (int i = 1; i <= n; i++) {
		//	for (int j = 1; j <= n; j++) {

		//		cout << Map[i][j].del << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n================시작후============\n";

		nowNum++;

	}
	return nowNum;

}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> Map[i][j].base;
		}
	}
	for (int i = 1; i <= m; i++) {
		cin >> miniStop[i].row >> miniStop[i].col;
	}
	life = m;
	int ans = startGame();
	cout << ans;
	return 0;
}
