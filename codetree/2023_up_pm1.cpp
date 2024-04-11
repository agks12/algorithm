#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct AtoE { int strow, endrow, stcol, endcol; };
struct Pair { int row, col; };
struct PairArr { bool TF = { 0 }; vector<int> v; };
int N, M, K, nowLife, moveCnt, arr[11][11] ,copyArr[11][11];
Pair parti[11];
PairArr vArr[11][11], copyvArr[11][11]; //참가자와 출구만 있는 배열
Pair Exit;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
int dr8[8] = { -1,-1,0,-1,0,1,1,1 }; // 이거순서로 정사각형 만드는 법 달라짐
int dc8[8] = { -1,0,-1,1,1,-1,0,1 };

// 2점사이 거리계산
int cal(int exitRow, int exitCol, int nowRow, int nowCol) {
	int diff = abs(exitRow - nowRow) + abs(exitCol - nowCol);
	return diff;
}

void move() {
	int exitRow = Exit.row;
	int exitCol = Exit.col;
	for (int i = 0; i < M; i++) {
		int nowRow = parti[i].row;
		int nowCol = parti[i].col;

		if (nowRow == -1)return;
		int nowDist = cal(exitRow, exitCol, nowRow, nowCol);
		int nowIndex = -1;
		for (int j = 0; j < 4; j++) {
			int nextRow = nowRow + dr[j];
			int nextCol = nowCol + dc[j];
			if (nextRow<1 || nextRow > N || nextCol < 1 || nextCol>N)continue;
			if (arr[nextRow][nextCol] != 0)continue;
			int nowWestDist = cal(exitRow, exitCol, nextRow, nextCol);
			if (nowDist > nowWestDist) {
				nowDist = nowWestDist;
				nowIndex = j;
			}
		}
		if (nowIndex == -1)continue;// 지금 위치에서 어느 방향으로 가도 안작아짐
		//여기 오면 거기로 가면됨
		moveCnt++;
		// 참가자 리스트 초기화
		parti[i].row += dr[nowIndex];
		parti[i].col += dc[nowIndex];
		// 참가자 배열 초기화(이때 기존값을 다음값으로
		vArr[nowRow][nowCol].TF = false;
		vArr[nowRow][nowCol].v.clear();

		if (parti[i].row == Exit.row && parti[i].col == Exit.col) {
			parti[i].row = -1;
			parti[i].col = -1;
			return;
		}
		//참가자 배열 다음값 적용
		vArr[parti[i].row][parti[i].col].TF = true;
		vArr[parti[i].row][parti[i].col].v.push_back(i);
	}
}

Pair findClose() {
	queue<Pair> q;
	q.push(Exit);
	int visited[11][11] = { 0 };
	visited[Exit.row][Exit.col] = 1;
	while (!q.empty()) {
		// 퍼저나가는 n+1 값이 정사각형 크기
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 8; i++) {
			int nextRow = now.row + dr8[i];
			int nextCol = now.col + dc8[i];
			if (nextRow<1 || nextRow > N || nextCol < 1 || nextCol>N)continue;
			if (visited[nextRow][nextCol] > 0)continue;
			if (vArr[nextRow][nextCol].TF == true) {
				//그냥 좌표만 반환하면 정사각형 어캐 판단하냐
				return { nextRow,nextCol };
			}
			visited[nextRow][nextCol] = visited[now.row][now.col]+1;
			q.push({ nextRow,nextCol });
		}
	}
	return { -1,-1 };
}

int selectCross(Pair findPair) {
	int exitRow = Exit.row;
	int exitCol = Exit.col;
	int nowRow = findPair.row;
	int nowCol = findPair.col;

	if (exitRow == nowRow || exitCol == nowCol)return 1; // 가로세로에 위치
	else return -1; // 대각선위치
}

AtoE notCrossPair(Pair findPair) {
	int exitRow = Exit.row;
	int exitCol = Exit.col;
	int nowRow = findPair.row;
	int nowCol = findPair.col;
	// 가로세로에 위치경우
	//범위 초과하는지도 판단해야함
	//상하좌우 4가지 경우 각각에 대해 양옆으로 2가지 경우 있으므로 총 8가지 경우의수
	int stRow = 0;
	int endRow = 0;
	int stCol = 0;
	int endCol = 0;


	if (nowRow == exitRow && nowCol < exitCol) {
		//좌측
		int testLength = exitCol - nowCol;
		if ( (nowRow - testLength) >= 1) {//위에가 우선순위라 먼저검사
			stRow = nowRow - testLength;
			endRow = nowRow;
			stCol = nowCol;
			endCol = exitCol;
		}
		else {
			stRow = nowRow;
			endRow = nowRow + testLength;
			stCol = nowCol;
			endCol = exitCol;
		}
	}
	else if (nowRow == exitRow && nowCol > exitCol) {
		//우측
		int testLength = nowCol - exitCol;
		if ((nowRow - testLength) >= 1) {//위에가 우선순위라 먼저검사
			stRow = nowRow - testLength;
			endRow = nowRow;
			stCol = exitCol;
			endCol = nowCol;
		}
		else {
			stRow = nowRow;
			endRow = nowRow + testLength;
			stCol = exitCol;
			endCol = nowCol;
		}
	}
	else if (nowCol == exitCol && nowRow > exitRow) {
		//하측
		int testLength = nowRow - exitRow;
		if ((nowCol - testLength) >= 1) {//위에가 우선순위라 먼저검사
			stRow = exitRow;
			endRow = nowRow;
			stCol = nowCol - testLength;
			endCol = exitCol;
		}
		else {
			stRow = exitRow;
			endRow = nowRow;
			stCol = exitCol;
			endCol = nowCol + testLength;
		}
	}
	else if (nowCol == exitCol && nowRow < exitRow) {
		//상측
		int testLength = exitRow - nowRow;
		if ((nowCol - testLength) >= 1) {//위에가 우선순위라 먼저검사
			stRow = nowRow;
			endRow = exitRow;
			stCol = nowCol - testLength;
			endCol = exitCol;
		}
		else {
			stRow = nowRow;
			endRow = exitRow;
			stCol = exitCol;
			endCol = nowCol + testLength;
		}
	}

	return { stRow,endRow,stCol,endCol };
}

AtoE CrossPair(Pair findPair) {
	//대각선에 위치 경우
	int exitRow = Exit.row;
	int exitCol = Exit.col;
	int nowRow = findPair.row;
	int nowCol = findPair.col;

	int stRow = 0;
	int endRow = 0;
	int stCol = 0;
	int endCol = 0;

	if (nowRow < exitRow && nowCol < exitCol) {
		// 2사분면위치 
		stRow = nowRow;
		endRow = exitRow;
		stCol = nowCol;
		endCol = exitCol;
	}
	else if (nowRow < exitRow && nowCol > exitCol) {
		//1 사분면
		stRow = nowRow;
		endRow = exitRow;
		stCol = exitCol;
		endCol = nowCol;
	}
	else if (nowRow > exitRow && nowCol < exitCol) {
		//3사분면
		stRow = exitRow;
		endRow = nowRow;
		stCol = nowCol;
		endCol = exitCol;
	}
	else if (nowRow > exitRow && nowCol > exitCol) {
		//4사분면
		stRow = exitRow;
		endRow = nowRow;
		stCol = exitCol;
		endCol = nowCol;
	}

	return { stRow,endRow,stCol,endCol };
}

AtoE subTurn(Pair findPair) {

	//일단 대각선 성분인지 아닌지 판단해야함 
	// 대각선 성분이면 꼭지점이여서 괜찮은데 아니면 늘려줘야함
	//이새끼들은 좌상, 우하 반환하는 역활
	int crossT = selectCross(findPair);
	AtoE doubPair = { 0 };
	if (crossT == 1)doubPair = notCrossPair(findPair);
	else doubPair = CrossPair(findPair);

	//무조건 좌상우하 반환
	return doubPair;
}

void turn(AtoE area) {
	//arr위치 회전
	//vArr위치 회전
	int stRow = area.strow;
	int endRow = area.endrow;
	int stCol = area.stcol;
	int endCol = area.endcol;

	for (int i = stRow; i <= endRow; i++) {
		for (int j = stCol; j <= endCol; j++) {
			copyArr[i][j] = arr[i][j];
			copyvArr[i][j] = vArr[i][j];
		}
	}

	for (int i = stRow; i <= endRow; i++) {
		for (int j = stCol; j <= endCol; j++) {
			arr[stRow + j - stCol][endCol - i + stRow] = copyArr[i][j] - 1;
			if (arr[stRow + j - stCol][endCol - i + stRow] < 0)arr[stRow + j - stCol][endCol - i + stRow] = 0;
			vArr[stRow + j - stCol][endCol - i + stRow] = copyvArr[i][j];
			if (vArr[stRow + j - stCol][endCol - i + stRow].TF == true && vArr[stRow + j - stCol][endCol - i + stRow].v.size()!=0) {
				for (int k = 0; k < vArr[stRow + j - stCol][endCol - i + stRow].v.size(); k++) {
					int nowNode = vArr[stRow + j - stCol][endCol - i + stRow].v[k];
					parti[nowNode].row = stRow + j - stCol;
					parti[nowNode].col = endCol - i + stRow;
				}
			}
			else if (vArr[stRow + j - stCol][endCol - i + stRow].TF == true && vArr[stRow + j - stCol][endCol - i + stRow].v.size() == 0) {
				Exit.row = stRow + j - stCol;
				Exit.col = endCol - i + stRow;
			}
		}
	}

	//리스트 및 exit 값 초기화
	
}

int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	
	//참가자 좌표
	for (int i = 0; i < M; i++) {
		int r, c;
		cin >> r >> c;
		parti[i].row = r;
		parti[i].col = c;
		vArr[r][c].TF = true;
		vArr[r][c].v.push_back(i); // 이 배엘에 들어가는 번호는 pati 리스트의 인덱스에 해당 즉 r,c 에 해당하는 인덱스 선택하기 위한
	}

	// 출구 좌표
	cin >> Exit.row >> Exit.col;
	vArr[Exit.row][Exit.col].TF = true;


	nowLife = M;//생존자

	//이동함수
	while (K>0) {

		move();
		Pair findPair = findClose();
		if (findPair.row == -1)break;//사람새끼 없음
		AtoE insertTurn = subTurn(findPair); //양옆이 아니라 가운데 처리 안함
		turn(insertTurn);

		cout << "===========================\n";
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout<< arr[i][j]<<" ";
			}
			cout << "\n";
		}
		cout << "===========================\n";
		cout << "EXIT" << Exit.row << " " << Exit.col<<"Exit\n";
		for (int i = 0; i < M; i++) {
			cout << " "<<parti[i].row << "," << parti[i].col<<" ";
		}
		cout << "\n";
		//for (int i = 1; i <= N; i++) {
		//	for (int j = 1; j <= N; j++) {
		//		PairArr now= vArr[i][j];
		//		cout <<"bool" << now.TF<<"bool ";
		//		for (int k = 0; k < now.v.size(); k) {
		//			cout << now.v[k] << " ";
		//		}
		//		cout << "    ";
		//	}
		//	cout << "\n";
		//}

		if (nowLife == 0)break;
		K--;
	}
	
	cout <<moveCnt<<"\n" <<Exit.row << " " << Exit.col;
	int s = 0;

	return 0;
}
