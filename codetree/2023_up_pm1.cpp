#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct AtoE { int strow, endrow, stcol, endcol; };
struct Pair { int row, col; };
struct PairArr { bool TF = { 0 }; vector<int> v; };
int N, M, K, nowLife, moveCnt, arr[11][11], copyArr[11][11];
Pair parti[11];
PairArr vArr[11][11], copyvArr[11][11]; //참가자와 출구만 있는 배열
Pair Exit;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
int dr8[8] = { -1,-1,0,1,1,-1,0,1 }; // 이거순서로 정사각형 만드는 법 달라짐
int dc8[8] = { -1,0,-1,-1,0,1,1,1 };

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

		if (nowRow == -1)continue;
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
		if (vArr[nowRow][nowCol].v.size() == 1) {
			vArr[nowRow][nowCol].TF = false;
			vArr[nowRow][nowCol].v.clear();
		}
		else {
			//2명 이상이면 1새기 죽여야함 여기 파라미터는 변경 전 값
			for (int k = 0; k < vArr[nowRow][nowCol].v.size(); k++) {
				int nNode = vArr[nowRow][nowCol].v[k];//인덱스 1개만 추출

				if (nNode == i) {
					vArr[nowRow][nowCol].v.erase(vArr[nowRow][nowCol].v.begin() + k);
					break;
				}
				//추출된 인덱스의 리스트값검사 이러면 중복 필요 없는데 인덱스만 제거 하는 거라서
				//if ( (parti[nNode].row = nowRow) && (parti[nNode].col = nowCol) ) {
				//	vArr[nowRow][nowCol].v.erase(vArr[nowRow][nowCol].v.begin() + k);
				//	break;
				//}
			}
		}


		if (parti[i].row == Exit.row && parti[i].col == Exit.col) {
			parti[i].row = -1;
			parti[i].col = -1;
			nowLife--;
			continue;
		}
		//참가자 배열 다음값 적용
		vArr[parti[i].row][parti[i].col].TF = true;
		vArr[parti[i].row][parti[i].col].v.push_back(i);
	}
}

vector<Pair> findClose() {
	queue<Pair> q;
	//queue<Pair> q2;
	vector<Pair> v;
	int flag = 0;
	int flag2 = 0;
	q.push(Exit);
	//q2.push(Exit);
	int visited[11][11] = { 0 };
	//int visited2[11][11] = { 0 };
	visited[Exit.row][Exit.col] = 1;

	//while (!q2.empty()) {
	//	Pair now = q2.front(); q2.pop();
	//	for (int i = 0; i < 8; i++) {
	//		int nextRow = now.row + dr[i];
	//		int nextCol = now.col + dc[i];
	//		if (nextRow<1 || nextRow > N || nextCol < 1 || nextCol>N)continue;
	//		if (visited2[nextRow][nextCol] > 0)continue;
	//		visited2[nextRow][nextCol] = 1;
	//		q2.push({ nextRow,nextCol });

	//	}
	//}


	//while (!q.empty()) {
	//	// 퍼저나가는 n+1 값이 정사각형 크기
	//	Pair now = q.front(); q.pop();
	//	if (flag2 == 1 && flag <= visited[now.row][now.col]) {
	//		return v;
	//	}
	//	for (int i = 0; i < 8; i++) {
	//		int nextRow = now.row + dr8[i];
	//		int nextCol = now.col + dc8[i];
	//		if (nextRow<1 || nextRow > N || nextCol < 1 || nextCol>N)continue;
	//		if (visited[nextRow][nextCol] > 0)continue;
	//		if (vArr[nextRow][nextCol].TF == true) {
	//			//그냥 좌표만 반환하면 정사각형 어캐 판단하냐 // 가까운 모든 거 찾아서 가장 작은거 구해야됨
	//			v.push_back({nextRow,nextCol});
	//			flag = visited[now.row][now.col] +1;
	//			flag2 = 1;
	//			visited[nextRow][nextCol] = visited[now.row][now.col] + 1;
	//			continue;
	//		}
	//		visited[nextRow][nextCol] = visited[now.row][now.col] + 1;
	//		q.push({ nextRow,nextCol });
	//	}
	//}

	while (!q.empty()) {
		// 퍼저나가는 n+1 값이 정사각형 크기
		Pair now = q.front(); q.pop();
		if (flag2 == 1 && flag <= visited[now.row][now.col]) {
			return v;
		}
		for (int i = 0; i < 8; i++) {
			int nextRow = now.row + dr8[i];
			int nextCol = now.col + dc8[i];
			if (nextRow<1 || nextRow > N || nextCol < 1 || nextCol>N)continue;
			if (visited[nextRow][nextCol] > 0)continue;
			if (vArr[nextRow][nextCol].TF == true) {
				//그냥 좌표만 반환하면 정사각형 어캐 판단하냐 // 가까운 모든 거 찾아서 가장 작은거 구해야됨
				v.push_back({nextRow,nextCol});
				flag = visited[now.row][now.col] +1;
				flag2 = 1;
				visited[nextRow][nextCol] = visited[now.row][now.col] + 1;
				continue;
			}
			visited[nextRow][nextCol] = visited[now.row][now.col] + 1;
			q.push({ nextRow,nextCol });
		}
	}
	//v.clear();
	//v.push_back({ -1,-1 });
	return v;
}

int selectCross(Pair findPair) {
	int exitRow = Exit.row;
	int exitCol = Exit.col;
	int nowRow = findPair.row;
	int nowCol = findPair.col;

	if (exitRow == nowRow || exitCol == nowCol)return 1; // 가로세로에 위치
	else return -1; // 대각선위치
}

// 이거 최대한 r 작고 c 작게 해야함
//AtoE notCrossPair(Pair findPair) {
//	int exitRow = Exit.row;
//	int exitCol = Exit.col;
//	int nowRow = findPair.row;
//	int nowCol = findPair.col;
//	// 가로세로에 위치경우
//	//범위 초과하는지도 판단해야함
//	//상하좌우 4가지 경우 각각에 대해 양옆으로 2가지 경우 있으므로 총 8가지 경우의수
//	int stRow = 0;
//	int endRow = 0;
//	int stCol = 0;
//	int endCol = 0;
//
//
//	if (nowRow == exitRow && nowCol < exitCol) {
//		//좌측
//		int testLength = exitCol - nowCol;
//		// 지금위치에서 특정 값 뺀값이 1이 아닌 최소값이 되야함
//
//		// nowRow = 5 , test = 7  => 5 -7  = -2  ( 이 값이 0보다 작으면 abs(차)만큼 
//		if ((nowRow - testLength) >= 1) {//위에가 우선순위라 먼저검사
//			stRow = nowRow - testLength;
//			endRow = nowRow;
//			stCol = nowCol;
//			endCol = exitCol;
//		}
//		else {//아래쪽으로 
//			stRow = nowRow;
//			endRow = nowRow + testLength;
//			stCol = nowCol;
//			endCol = exitCol;
//		}
//	}
//	else if (nowRow == exitRow && nowCol > exitCol) {
//		//우측
//		int testLength = nowCol - exitCol;
//		if ((nowRow - testLength) >= 1) {//위에가 우선순위라 먼저검사
//			stRow = nowRow - testLength;
//			endRow = nowRow;
//			stCol = exitCol;
//			endCol = nowCol;
//		}
//		else {
//			stRow = nowRow;
//			endRow = nowRow + testLength;
//			stCol = exitCol;
//			endCol = nowCol;
//		}
//	}
//	else if (nowCol == exitCol && nowRow > exitRow) {
//		//하측
//		int testLength = nowRow - exitRow;
//		if ((nowCol - testLength) >= 1) {//위에가 우선순위라 먼저검사
//			stRow = exitRow;
//			endRow = nowRow;
//			stCol = nowCol - testLength;
//			endCol = exitCol;
//		}
//		else {
//			stRow = exitRow;
//			endRow = nowRow;
//			stCol = exitCol;
//			endCol = nowCol + testLength;
//		}
//	}
//	else if (nowCol == exitCol && nowRow < exitRow) {
//		//상측
//		int testLength = exitRow - nowRow;
//		if ((nowCol - testLength) >= 1) {//위에가 우선순위라 먼저검사
//			stRow = nowRow;
//			endRow = exitRow;
//			stCol = nowCol - testLength;
//			endCol = exitCol;
//		}
//		else {
//			stRow = nowRow;
//			endRow = exitRow;
//			stCol = exitCol;
//			endCol = nowCol + testLength;
//		}
//	}
//
//	return { stRow,endRow,stCol,endCol };
//}

AtoE notCrossPair2(Pair findPair) {
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
		// 지금위치에서 특정 값 뺀값이 1이 아닌 최소값이 되야함

		// nowRow = 5 , test = 7  => 5 -7  = -2  ( 이 값이 0보다 작으면 abs(차)만큼 
		if ((nowRow - testLength) >= 1) {//위에가 우선순위라 먼저검사
			stRow = nowRow - testLength;
			endRow = nowRow;
			stCol = nowCol;
			endCol = exitCol;
		}
		else if ((nowRow - testLength) < 1) {
			//범위 초과 = > 무조건 row는 1부터 시작
			stRow = 1; // 시작 
			endRow = stRow +testLength; // 이건 현재에서 차이만큼 더함
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
		else if ((nowRow - testLength) < 1) {
			//범위 초과 = > 무조건 row는 1부터 시작
			stRow = 1; // 시작 
			endRow = stRow + testLength; // 이건 현재에서 차이만큼 더함
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
		else if ((nowCol - testLength) < 1) {
			//범위 초과 = > 무조건 row는 1부터 시작
			stRow = exitRow; // 시작 
			endRow = nowRow ; // 이건 현재에서 차이만큼 더함
			stCol = 1;
			endCol = stCol + testLength;
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
		else if ((nowCol - testLength) < 1) {
			//범위 초과 = > 무조건 row는 1부터 시작
			stRow = nowRow; // 시작 
			endRow = exitRow; // 이건 현재에서 차이만큼 더함
			stCol = 1;
			endCol = stCol + testLength;
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
		// 2사분면위치  row 는 그대로 사용 col 만 변경
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

	if ((endRow - stRow) > (endCol - stCol)) {
		//세로가 더 길어서 col늘려야 되는 경우
		int testlength = endRow - stRow;//5
		int nextStRow = stRow;//1
		int nextEndRow = endRow;//6
		int nextStCol = 0;
		int nextEndCol = 0;
		if (stCol - testlength >= 0) {
			nextStCol = endCol - testlength;
			nextEndCol = endCol;
		}
		else if (stCol - testlength < 0) {
			nextStCol = 1;
			nextEndCol = nextStCol + testlength;
		}
		return { nextStRow, nextEndRow, nextStCol, nextEndCol };
	}
	else if ((endRow - stRow) < (endCol - stCol)) {
		//가로가 더 길어서 row 늘려야 되는 경우
		int testlength = endCol - stCol;
		int nextStRow = 0;
		int nextEndRow = 0;
		int nextStCol = stCol;
		int nextEndCol = endCol;
		if (stRow - testlength >= 0) {
			nextStRow = endRow - testlength;
			nextEndRow = endRow;
		}
		else if (stRow - testlength < 0) {
			nextStRow = 1;
			nextEndRow = nextStRow + testlength;
		}

		return { nextStRow, nextEndRow, nextStCol, nextEndCol };
	}
	else if ((endRow - stRow) == (endCol - stCol)) {
		// 그냥 지금 대로 반환
		return { stRow,endRow,stCol,endCol };
	}

}

AtoE subTurn(Pair findPair) {

	//일단 대각선 성분인지 아닌지 판단해야함 
	// 대각선 성분이면 꼭지점이여서 괜찮은데 아니면 늘려줘야함
	//이새끼들은 좌상, 우하 반환하는 역활
	int crossT = selectCross(findPair);
	AtoE doubPair = { 0 };
	if (crossT == 1)doubPair = notCrossPair2(findPair); 
	else doubPair = CrossPair(findPair); // 대각선이면 그대로 해도됨

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

	//cout << "\n" << stRow << "," << stCol << "  " << endRow << "," << endCol << "\n";

	//if ((stRow - endRow) != (stCol - endCol))cout << "\n nonononononononononono\n";

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
			if (vArr[stRow + j - stCol][endCol - i + stRow].TF == true && vArr[stRow + j - stCol][endCol - i + stRow].v.size() != 0) {
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
	while (K > 0) {


		//cout << "====  " << K << "  ====== = \n";
		//for (int i = 1; i <= N; i++) {
		//	for (int j = 1; j <= N; j++) {
		//		cout << arr[i][j] << " ";
		//	}
		//	cout << "   ";
		//	for (int j = 1; j <= N; j++) {
		//		cout << vArr[i][j].TF << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "========" << K << "  =============\n";
		//cout << "EXIT" << Exit.row << " " << Exit.col << "Exit\n";
		move();

		//cout << "====  " << K << "  ====== = \n";
		//for (int i = 1; i <= N; i++) {
		//	for (int j = 1; j <= N; j++) {
		//		cout << arr[i][j] << " ";
		//	}
		//	cout << "   ";
		//	for (int j = 1; j <= N; j++) {
		//		cout << vArr[i][j].TF << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "========" << K << "  =============\n";
		vector<Pair> findPair = findClose();

		if (nowLife == 0)break;
		if (findPair.size() == 0)break;
		if (findPair[0].row == -1 && findPair[0].col==-1)break;//사람새끼 없음

		int row = 100;
		int col = 100;
		AtoE minTurn = { 0 };
		for (int ch = 0; ch < findPair.size(); ch++) {
			AtoE insertTurn = subTurn(findPair[ch]); //양옆이 아니라 가운데 처리 안함
			if (insertTurn.strow < row) {
				row = insertTurn.strow;
				col = insertTurn.stcol;
				minTurn = insertTurn;
			}
			else if (insertTurn.strow == row) {
				if (insertTurn.stcol < col) {
					row = insertTurn.strow;
					col = insertTurn.stcol;
					minTurn = insertTurn;
				}
			}
		}
		
		turn(minTurn);

		//cout << "====  "<<K<<"  ====== = \n";
		//for (int i = 1; i <= N; i++) {
		//	for (int j = 1; j <= N; j++) {
		//		cout << arr[i][j] << " ";
		//	}
		//	cout <<  "   ";
		//	for (int j = 1; j <= N; j++) {
		//		cout << vArr[i][j].TF << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "========" << K << "  =============\n";
		////cout << "find" << findPair.row << " " << findPair.col << "find\n";
		//for (int i = 0; i < M; i++) {
		//	cout << " " << parti[i].row << "," << parti[i].col << " ";
		//}
		//cout << "\n\n\n\n";
		// 
		 


		
		K--;
	}

	cout << moveCnt << "\n" << Exit.row << " " << Exit.col;
	int s = 0;

	return 0;
}
