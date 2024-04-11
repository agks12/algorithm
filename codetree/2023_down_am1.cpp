#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct AtoE { int strow, endrow, stcol, endcol; };
struct rangeNode { int nowNode, outBool; };
int N, L, Q, OriginArr[42][42], arr[42][42], damege[32], life[32];
AtoE gisa[32]; // 기사 좌상,우하 값저장


int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

AtoE nextArea(int nowNode, int nowdir) {
	int stRow = gisa[nowNode].strow;
	int endRow = gisa[nowNode].endrow;
	int stCol = gisa[nowNode].stcol;
	int endCol = gisa[nowNode].endcol;

	int nextStRow = 0;
	int nextEndRow = 0;
	int nextStCol = 0;
	int nextEndCol = 0;

	if (nowdir == 0) {
		//상
		nextStRow = stRow - 1;
		nextEndRow = stRow - 1;
		nextStCol = stCol;
		nextEndCol = endCol;
	}
	else if (nowdir == 1) {
		//우
		nextStRow = stRow;
		nextEndRow = endRow;
		nextStCol = endCol+1;
		nextEndCol = endCol+1;
	}
	else if (nowdir == 2) {
		//하
		nextStRow = endRow + 1;
		nextEndRow = endRow + 1;
		nextStCol = stCol;
		nextEndCol = endCol;
	}
	else if (nowdir == 3) {
		//좌
		nextStRow = stRow;
		nextEndRow = endRow;
		nextStCol = stCol - 1;
		nextEndCol = stCol - 1;
	}
	
	return { nextStRow ,nextEndRow ,nextStCol,nextEndCol };
}

int testBlock(AtoE Area, int nowNode, int nowdir) {
	//검사할 좌표들
	int stRow = Area.strow;
	int endRow = Area.endrow;
	int stCol = Area.stcol;
	int endCol = Area.endcol;

	if (stRow == endRow) {
		//row줄 검사 - col 만 바꿔 가면서
		for (int i = stCol; i <= endCol; i++) {
			if (OriginArr[stRow][i] == 2)return -1;
		}
	}
	else if (stCol == endCol) {
		//row줄 검사 - col 만 바꿔 가면서
		for (int i = stRow; i <= endRow; i++) {
			if (OriginArr[i][stCol] == 2)return -1;
		}
	}

	return 1;
}

int outRange(AtoE Area) {
	int stRow = Area.strow;
	int endRow = Area.endrow;
	int stCol = Area.stcol;
	int endCol = Area.endcol;

	if (stRow < 1 || stRow > N || endRow < 1 || endRow > N || stCol <1 || stCol > N || endCol < 1 || endCol > N)return -1;
	else return 1;
}

vector<rangeNode> bfs(int nowNode, int nowdir) {
	queue<int> q;
	vector<rangeNode> v;
	q.push(nowNode);
	// 아래 함수 에서 범위 초과인거랑 그냥 0인 빈칸인거랑 구분해야 되는데
	while (!q.empty()) {
		int now = q.front(); q.pop();
		//기사 번호, 방향 인풋일때 검사할 영역 반환하는 함수
		AtoE Area = nextArea(now, nowdir);
		//cout << Area.strow << " " << Area.endrow << " " << Area.stcol << " " << Area.endcol << "\n";
		//영역 인풋받고 벽 있는지 검사하는 함수 1이면 벽없음 -1이면 벽
		int BoolBlock = testBlock(Area, now, nowdir);
		if (BoolBlock == -1) {
			vector<rangeNode> v2;
			v2.push_back({-1,-100});
			return v2;
		}

		int testRange = outRange(Area);
		if (testRange == -1) {
			vector<rangeNode> v2;
			v2.push_back({ -1,-100 });
			return v2;
		}
		v.push_back({ now,testRange});//범위 초과면 -1 아니면 1


		//벽 없으면 다음 기사 찾기
		int stRow = Area.strow;
		int endRow = Area.endrow;
		int stCol = Area.stcol;
		int endCol = Area.endcol;
		
		int visited[32] = { 0 };
		if (stRow == endRow) {
			//row줄 검사 - col 만 바꿔 가면서
			for (int i = stCol; i <= endCol; i++) {
				if (arr[stRow][i] == 0)continue;
				if (visited[arr[stRow][i]] == 1)continue;
				visited[arr[stRow][i]] = 1;
				q.push(arr[stRow][i]);
				//v.push_back(arr[stRow][i]);
			}
		}
		else if (stCol == endCol) {
			//row줄 검사 - col 만 바꿔 가면서
			for (int i = stRow; i <= endRow; i++) {
				if (arr[i][stCol] == 0)continue;
				if (visited[arr[i][stCol]] == 1)continue;
				visited[arr[i][stCol]] = 1;
				q.push(arr[i][stCol]);
				//v.push_back(arr[stRow][i]);
			}
		}
	}

	return v;
}

int findDamege(AtoE Area) {
	int stRow = Area.strow;
	int endRow = Area.endrow;
	int stCol = Area.stcol;
	int endCol = Area.endcol;

	int hole = 0;

	if (stRow == endRow) {
		//row줄 검사 - col 만 바꿔 가면서
		for (int i = stCol; i <= endCol; i++) {
			if (OriginArr[stRow][i] == 1)hole++;
		}
	}
	else if (stCol == endCol) {
		//row줄 검사 - col 만 바꿔 가면서
		for (int i = stRow; i <= endRow; i++) {
			if (OriginArr[i][stCol] == 1)hole++;
		}
	}

	return hole;
}

void reset(int nowNode) {
	int stRow = gisa[nowNode].strow;
	int endRow = gisa[nowNode].endrow;
	int stCol = gisa[nowNode].stcol;
	int endCol = gisa[nowNode].endcol;

	for (int i = stRow; i <= endRow; i++) {
		arr[i][stCol] = 0;
		arr[i][endCol] = 0;
	}
	for (int i = stCol; i <= endCol; i++) {
		arr[stRow][i] = 0;
		arr[endRow][i] = 0;
	}
}

void move(int nowNode, int nowdir, int turn) {
	//AtoE Area = nextArea(nowNode, nowdir);
	//그냥 옮기면 끝
	int stRow = gisa[nowNode].strow;
	int endRow = gisa[nowNode].endrow;
	int stCol = gisa[nowNode].stcol;
	int endCol = gisa[nowNode].endcol;


	//데미지 계산
	AtoE Area = nextArea(nowNode, nowdir);
	int hole = findDamege(Area);
	if(turn!=0)damege[nowNode] -= hole;
	

	if (damege[nowNode] == 0) {
		//0으로 초기화
		reset(nowNode);
		return;
	}

	//배열 초기화
	if (nowdir == 0) {
		//위 
		for (int j = stCol; j <= endCol; j++) {
			arr[endRow][j] = 0; // 제일 아래 가로줄 초기화
			arr[endRow-1][j] = nowNode; // 옮길 줄 초기화
			arr[stRow - 1][j] = nowNode; // 옮길 위 줄 초기화
			if (!(j == stCol || j == endCol))arr[stRow][j] = 0;
		}
	}
	else if (nowdir == 1) {
		//오른쪽
		for (int j = stRow; j <= endRow; j++) {
			arr[j][stCol] = 0; // 제일 아래 가로줄 초기화
			arr[j][stCol+1] = nowNode; // 옮길 줄 초기화
			arr[j][endCol+1] = nowNode; // 옮길 위 줄 초기화
			if (!(j == stRow || j == endRow))arr[j][endCol] = 0;
		}
	}
	else if (nowdir == 2) {
		//아래
		for (int j = stCol; j <= endCol; j++) {
			arr[stRow][j] = 0; // 제일 아래 가로줄 초기화
			arr[stRow + 1][j] = nowNode; // 옮길 줄 초기화
			arr[endRow + 1][j] = nowNode; // 옮길 위 줄 초기화
			if (!(j == stCol || j == endCol))arr[endRow][j] = 0;
		}
	}
	else if (nowdir == 3) {
		//왼쪽
		for (int j = stRow; j <= endRow; j++) {
			arr[j][endCol] = 0; // 제일 아래 가로줄 초기화
			arr[j][endCol -1 ] = nowNode; // 옮길 줄 초기화
			arr[j][stCol - 1] = nowNode; // 옮길 위 줄 초기화
			if (!(j == stRow || j == endRow))arr[j][stCol] = 0;
		}
	}

	//리스트 초기화
	stRow += dr[nowdir];
	endRow += dr[nowdir];
	stCol += dc[nowdir];
	endCol += dc[nowdir];
	gisa[nowNode] = { stRow ,endRow ,stCol ,endCol };
}

//void outmove(int nowNode, int nowdir) {
//	int stRow = gisa[nowNode].strow;
//	int endRow = gisa[nowNode].endrow;
//	int stCol = gisa[nowNode].stcol;
//	int endCol = gisa[nowNode].endcol;
//
//
//
//	//데미지 계산
//	//AtoE Area = nextArea(nowNode, nowdir);
//	//int hole = findDamege(Area);
//
//	//damege[nowNode] -= hole;
//
//	//배열 초기화
//	if (nowdir == 0) {
//		//위 
//		for (int j = stCol; j <= endCol; j++) {
//			arr[endRow][j] = 0; // 제일 아래 가로줄 초기화
//			arr[endRow - 1][j] = nowNode; // 옮길 줄 초기화
//			arr[stRow - 1][j] = nowNode; // 옮길 위 줄 초기화
//			if (!(j == stCol || j == endCol))arr[stRow][j] = 0;
//		}
//	}
//	else if (nowdir == 1) {
//		//오른쪽
//		for (int j = stRow; j <= endRow; j++) {
//			arr[j][stCol] = 0; // 제일 아래 가로줄 초기화
//			arr[j][stCol + 1] = nowNode; // 옮길 줄 초기화
//			arr[j][endCol + 1] = nowNode; // 옮길 위 줄 초기화
//			if (!(j == stRow || j == endRow))arr[j][endCol] = 0;
//		}
//	}
//	else if (nowdir == 2) {
//		//아래
//		for (int j = stCol; j <= endCol; j++) {
//			arr[stRow][j] = 0; // 제일 아래 가로줄 초기화
//			arr[stRow + 1][j] = nowNode; // 옮길 줄 초기화
//			arr[endRow + 1][j] = nowNode; // 옮길 위 줄 초기화
//			if (!(j == stCol || j == endCol))arr[endRow][j] = 0;
//		}
//	}
//	else if (nowdir == 3) {
//		//왼쪽
//		for (int j = stRow; j <= endRow; j++) {
//			arr[j][endCol] = 0; // 제일 아래 가로줄 초기화
//			arr[j][endCol + 1] = nowNode; // 옮길 줄 초기화
//			arr[j][stCol + 1] = nowNode; // 옮길 위 줄 초기화
//			if (!(j == stRow || j == endRow))arr[j][stCol] = 0;
//		}
//	}
//
//	//리스트 초기화
//	stRow += dr[nowdir];
//	endRow += dr[nowdir];
//	stCol += dc[nowdir];
//	endCol += dc[nowdir];
//
//	if (stRow < 1)stRow = 0;
//	else if (stRow > N)stRow = N+1;
//	
//	if (endRow < 1)endRow = 0;
//	else if (endRow > N)endRow = N+1;
//
//	if (stCol < 1)stCol = 0;
//	else if (stCol > N)endCol = N+1;
//
//	if (endCol < 1)endCol = 0;
//	else if (endCol > N)endCol = N+1;
//
//	if ((stRow < 1 && stRow > N) && (endRow < 1 && endRow > N) && (stCol < 1 && stCol > N) && (endCol < 1 && endCol > N)) {
//		damege[nowNode] = 0;
//		reset(nowNode);
//	}
//	gisa[nowNode] = { stRow ,endRow ,stCol ,endCol };
//}


//이거는 범위 1개라도 벗어나면 제거함
//void outmove2(int nowNode, int nowdir) {
//	reset(nowNode);
//	//damege[nowNode];
//}


int main() {
	cin >> N >> L >> Q;
	
	// 기본배열
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> OriginArr[i][j];
		}
	}

	//기사 배열
	for (int i = 1; i <= L; i++) {
		int r, c, h, w, k;
		cin >> r >> c >> h >> w >> k;
		
		//좌상,우하 저장
		gisa[i] = { r,r + h - 1,c,c + w - 1 };
		damege[i] = k; // 손실점수
		life[i] = k; // 손실점수
		//기사배열 초기화
		//cout <<"\nnownow" << r << " " << r + h - 1 << " " << c << " " << c + w - 1 << "\n";
		// 세로줄 2개 초기화
		for (int row = r; row <= r + h - 1; row++) {
			arr[row][c] = i;
			arr[row][c+w-1] = i;
		}
		//가로줄 2개 초기화
		for (int col = c; col <= c + w - 1; col++) {
			arr[r][col] = i;
			arr[r+h-1][col] = i;
		}
	}

	cout << "=======\n";
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "=======\n";


	for (int i = 0; i < Q; i++) {
		int nowNode, nowdir;
		cin >> nowNode >> nowdir;

		if (damege[nowNode] <= 0)continue;

		vector<rangeNode> ans = bfs(nowNode, nowdir);
		rangeNode test = ans[0];
		if (test.nowNode == -1)continue;//벽있는 경우
		else {
			//마지막 부터 옮겨야 겠지?
			for (int j = ans.size()-1; j >= 0; j--) {
				rangeNode now = ans[j];
				int Node = now.nowNode;
				int rangeTest = now.outBool; //-1이면 아웃범위 1 이면 그냥 옯기면 됨

				if (rangeTest == 1)move(Node, nowdir,j);
				//else if (rangeTest == -1)outmove2(Node, nowdir);
			}
		}

		cout << "=======\n";
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout << arr[i][j] << " ";
			}
			cout << "   ";
			for (int j = 1; j <= N; j++) {
				cout << OriginArr[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "=======\n";
		for (int j = 1; j <= L; j++) {
			cout <<"damege"<<j<<" " << damege[j] << " \n";
		}
		cout << "\n";

	}
	
	int sum = 0;
	for (int i = 1; i <= L; i++) {
		if (damege[i] == 0)continue;
		int sumDamage = life[i] - damege[i];
		sum += sumDamage;
	}
	cout << sum;


	return 0;
}





//4 2 7
//0 0 1 1
//2 0 1 0
//1 1 0 1
//0 1 0 0
//4 2 1 3 3
//1 3 2 2 5
//2 2
//2 0
//1 1
//2 2
//1 0
//2 3
//1 1


//5 8 10
//2 0 0 0 1
//1 0 2 0 1
//0 1 1 0 1
//1 1 2 1 0
//0 0 0 0 1
//4 5 2 1 3
//2 1 1 1 8
//2 4 2 2 2
//2 2 1 1 9
//5 4 1 1 5
//4 4 1 1 5
//4 1 2 2 8
//3 3 1 1 10
//8 3
//3 2
//1 0
//5 2
//6 3
//8 3
//1 0
//2 1
//8 1
//5 2
