#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct DoublePair { int stRow, stCol, endRow, endCol; };

// 1,1 부터
struct Pair { int row, col; };
int L, N, Q; // 체스판 크기 , 기사수, 명령수
int map[42][42];

// 덧 저장 배열
Pair holeInfo[1650];
int holeSize;
int visited[1650];

// 기사정보
struct Night { int row, col, hig, wid, life; };
Night kight[35];
int lifeArr[35];

// 방향배열
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

// 지금위치에서 값만 바꾸는 함수
void renewMap(int nowN, int nowValue) {
	Night now = kight[nowN];
	int nowRow = now.row;
	int nowCol = now.col;
	int nowH = now.hig;
	int nowW = now.wid;
	// 세로
	for (int r = nowRow; r < nowRow + nowH; r++) {
		map[r][nowCol] = nowValue;
		map[r][nowCol+nowW-1] = nowValue;
	}
	// 가로
	for (int c = nowCol; c < nowCol + nowW; c++) {
		map[nowRow][c] = nowValue;
		map[nowRow+nowH-1][c] = nowValue;
	}
}


// 지금 기사 dir 방향으로 어떤거 있는지 검사함수
// 시작점 끝점만 반한
DoublePair searchDir(int nowK, int nowdir) {
	Night now = kight[nowK];
	int nowRow = now.row;
	int nowCol = now.col;
	int nowH = now.hig;
	int nowW = now.wid;
	// 좌우인지 상하인지에 따라 달라짐
	// 왼쪽 오른쪽, 위 아래인지에 따라서도 달라지는데
	int stRow = 0;
	int stCol = 0;
	int endRow = 0;
	int endCol = 0;
	// 방향 나머지가 홀수이면좌유

	// 짝수이면 위아래
	// w 길이만큼 row고정 col 검사
	if (nowdir == 0) {
		// 위 방향검사 - 
		// 시작좌표
		stRow = nowRow - 1;
		stCol = nowCol;
		endRow = nowRow - 1;
		endCol = nowCol + nowW - 1;
	}
	else if (nowdir == 2) {
		// 아래 방향검사 - 
		// 시작좌표
		stRow = nowRow + nowH; // 자동으로 +1 크기임
		stCol = nowCol;
		endRow = nowRow + nowH;
		endCol = nowCol + nowW - 1;
	}
	else if (nowdir == 1) {
		// 오른쪽 col 고정 +1 
		stRow = nowRow; // 자동으로 +1 크기임
		stCol = nowCol + nowW;
		endRow = nowRow + nowH -1;
		endCol = nowCol + nowW;
	}
	else if (nowdir == 3) {
		// 왼쪽
		stRow = nowRow; // 자동으로 +1 크기임
		stCol = nowCol-1;
		endRow = nowRow + nowH - 1;
		endCol = nowCol-1;
	}

	return { stRow,stCol,endRow,endCol };
}

vector<int> startSearch(DoublePair startSearch) {
	int stRow = startSearch.stRow;
	int stCol = startSearch.stCol;
	int endRow = startSearch.endRow;
	int endCol = startSearch.endCol;

	// 기사번호 저장
	vector<int> v;

	if (stRow == endRow) {
		// row동일 즉 가로검사
		for (int c = stCol; c <= endCol; c++) {
			if (map[stRow][c] == 2 || stRow <= 0 || c <= 0 || stRow > L || c > L) {
				// 범위 초과이거나 벽만나면 모가서 바로 리턴
				return {-1};
			}
			// 
			if (map[stRow][c] > 2) {
				// 기사 만남
				v.push_back(map[stRow][c]);
			}
		}
	}
	else if (stCol == endCol) {
		// row동일 즉 가로검사
		for (int r = stRow; r <= endRow; r++) {
			if (map[r][stCol] == 2 || r <= 0 || stCol <= 0 || r > L || stCol > L) {
				// 범위 초과이거나 벽만나면 모가서 바로 리턴
				return { -1 };
			}
			if (map[r][stCol] > 2) {
				// 기사 만남
				v.push_back(map[r][stCol]);
			}
		}
	}

	return v;// 이거 크기 0 이면 기사없음

}

vector<int> searchMap(int nowN, int nowdir) {
	// bfs로 검사시작
	
	vector<int> v;
	v.push_back(nowN);
	int visited[35] = { 0 };
	queue<int> q; // 기사번호 저장 큐
	q.push(nowN);
	while (!q.empty()) {
		int nowK = q.front(); q.pop();
		// 지금 기사 dir방향으로 옆에칸 전부 검사해서 기사 있으면 기사 수만큼 반환
		// 벽이나 out이면 -1반환 
		// 아무것도 없으면 0반환?
		DoublePair value = searchDir(nowK,nowdir);
		vector<int> vec = startSearch(value);
		if (vec.size()!=0 && vec[0] == -1) {
			return { -1 };
		}
		// 벽이나 아웃이면 바로 끝남
		// 아니면 q에 삽입
		for (int i = 0; i < vec.size(); i++) {
			if (visited[vec[i]] == 1)continue;
			q.push(vec[i]);
			v.push_back(vec[i]);
			visited[vec[i]] = 1;
		}
	}

	return v;
}

void moveStart(int nowN, int nowDir) {
	Night now = kight[nowN];
	int nowRow = now.row;
	int nowCol = now.col;
	int nowH = now.hig;
	int nowW = now.wid;

	for (int r = nowRow; r < nowRow + nowH; r++) {
		for (int c = nowCol; c < nowCol + nowW; c++) {
			//int nextRow = r + dr[nowDir];
			//int nextCol = c + dr[nowDir];
			map[r][c] = 0;
			//map[nextRow][nextCol] = nowN;

		}
	}

	// 기사배열값 갱신
	kight[nowN].row += dr[nowDir];
	kight[nowN].col += dc[nowDir];

	for (int r = kight[nowN].row; r < kight[nowN].row + nowH; r++) {
		for (int c = kight[nowN].col; c < kight[nowN].col + nowW; c++) {
			int nextRow = r + dr[nowDir];
			int nextCol = c + dr[nowDir];
			map[r][c] = nowN;
			//map[nextRow][nextCol] = nowN;

		}
	}

	//// 세로
	//for (int r = nowRow; r < nowRow + nowH; r++) {
	//	// 원래 위치 초기화
	//	map[r][nowCol] = 0;
	//	map[r][nowCol + nowW - 1] = 0;
	//	// 다음위치 갱신
	//	int nextCol = nowCol + dc[nowDir];
	//	map[r][nextCol] = nowN;
	//	map[r][nextCol + nowW - 1] = nowN;
	//}
	//// 가로
	//for (int c = nowCol; c < nowCol + nowW; c++) {
	//	map[nowRow][c] = 0;
	//	map[nowRow + nowH - 1][c] = 0;
	//	// 다음위치 갱신
	//	int nextRow = nowRow + dr[nowDir];
	//	map[nextRow][c] = nowN;
	//	map[nextRow + nowH - 1][c] = nowN;
	//}



}

void realMove(vector<int> v, int nowDir) {
	// 벡터 제일 뒤에거 부터 움직여야함
	int vSize = v.size();
	vSize--; // 0번 부터라 마지막인덱스는 --

	for (int i = vSize; i >= 0; i--) {
		int nowN = v[i];
		moveStart(nowN, nowDir);
	}
}

void holeVisitedReset() {
	for (int i = 0; i <= holeSize; i++) {
		visited[i] = 0;
	}
}

void removeMap(int nowN) {
	Night now = kight[nowN];
	int nowRow = now.row;
	int nowCol = now.col;
	int nowH = now.hig;
	int nowW = now.wid;
	for (int r = nowRow; r < nowRow + nowH; r++) {
		for (int c = nowCol; c < nowCol + nowW; c++) {
			map[r][c] = 0;
			//map[nextRow][nextCol] = nowN;

		}
	}
}

void removeStart(int nowN) {
	Night now = kight[nowN];
	int nowRow = now.row;
	int nowCol = now.col;
	int nowH = now.hig;
	int nowW = now.wid;

	// 덧 1개씩 방패안에 있는지 검사
	for (int i = 0; i <= holeSize; i++) {
		if (visited[i] == 1)continue;
		Pair nowHole = holeInfo[i];
		if (nowRow <= nowHole.row && nowRow + nowH - 1 >= nowHole.row
			&& nowCol <= nowHole.col && nowCol + nowW - 1 >= nowHole.col) {
			//이거면 안에 들어오는 덫임
			kight[nowN].life--; // 점수 깍기
			visited[i] = 1; // 여기서 사용된 덫은 다른방패에서 사용될 수 없음
		}
	}

	// 전체 홀 검사 후 
	// kight[nowN].life 가 0 되었는지 검사
	if (kight[nowN].life <= 0) {
		// 맵에서 삭제
		removeMap(nowN);
	}
}

void removeLife(vector<int> v) {
	// 벡터 제일 뒤에거 부터 움직일 필요는 없음 0번째 꺼만 안하면 됨
	int vSize = v.size();
	vSize--; // 0번 부터라 마지막인덱스는 --
	holeVisitedReset();
	for (int i = vSize; i > 0; i--) {
		int nowN = v[i];
		removeStart(nowN);
	}
}

int getPoint() {
	int cnt = 0;
	for (int i = 3; i <= N + 2; i++) {
		Night now = kight[i];
		int initLife = lifeArr[i];
		if (now.life <= 0)continue; // 죽은애 버림
		int diff = initLife - now.life;
		cnt += diff;
	}
	return cnt;
}

int main() {
	cin >> L >> N >> Q;
	for (int r = 1; r <= L; r++) {
		for (int c = 1; c <= L; c++) {
			int nowv;
			cin >> nowv;
			map[r][c] = nowv;
			if (nowv == 1) {
				// 함정추가
				holeInfo[holeSize] = { r,c };
				holeSize++;
				map[r][c] = 0;
			}
		}
	}
	
	// 기사 3번 부터 시작
	for (int i = 3; i <= N + 2; i++) {
		int r, c, h, w, k;
		cin >> r >> c >> h >> w >> k;
		kight[i] = { r,c,h,w,k };
		// 기사정보 맵에 저장 기사번호로
		renewMap(i,i);
		lifeArr[i] = k;
	}

	// 명령시작
	for (int i = 1; i <= Q; i++) {
		int num, dir;
		cin >> num >> dir;
		// 죽은 애인지 확인하고 죽었으면 다음명령
		if (kight[num+2].life <= 0)continue;
		vector<int> rev = searchMap(num+2,dir);
		if (rev.size()!=0 && rev[0] == -1)continue; // 벽만나면 그냥 다음명령
		// 움직이는 함수
		realMove(rev,dir);
		// 함정피달기 함수
		removeLife(rev);

		//for (int r = 1; r <= L; r++) {
		//	for (int c = 1; c <= L; c++) {
		//		cout << map[r][c]<<" ";
		//	}
		//	cout << "\n";
		//}
		//cout << " \n한턴끝\n\n\n";

	}

	// 살아남은애 점수 계산
	int ans = getPoint();

	cout << ans;

	return 0;
}
