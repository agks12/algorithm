#include<iostream>
#include<queue>
using namespace std;

struct Santa { int stun, dead, score, row, col; };// 산타 기절, 사망 , 점수 배열
struct Pair { int row, col; };
int N, M, P, C, D;
int Rrow, Rcol;
Santa arr[32];
int Map[52][52]; // 값은 오직 산타 번호
int life;
// 루돌프가 산타 찾는 8칸우선순위 방향
//int dr[8] = {1,1,1,0,0,-1,-1,-1};
//int dc[8] = {1,0,-1,1,-1,1,0,-1};

int dr[8] = { 1,0,0,-1,1,1,-1,-1 };
int dc[8] = { 0,1,-1,0,1,-1,1,-1 };

// 산타 이동 우선순위 상 우 하 좌
int Sdr[4] = { -1,0,1,0 };
int Sdc[4] = { 0,1,0,-1 };

struct cmp { 
	int row, col;
	bool operator<(cmp right) const{
		if (right.row > row)return true;
		if (right.row < row)return false;
		if (right.col > col)return true;
		if (right.col < col)return false;
		return false;
	}
};

// 이거 좀 이상 8순위 r > c 순서 그대로 아니고 대각선보다 상하좌우가 우선
//Pair findSanta() {
//	priority_queue<cmp> saveQ;
//	int visited[52][52] = { 0 };
//	queue<Pair> q;
//	int firstVisited = 1;
//	q.push({ Rrow,Rcol });
//	visited[Rrow][Rcol] = 1;
//	int flag = 0;
//	int flag2 = 0;
//	while (!q.empty()) {
//		Pair now = q.front(); q.pop();
//		for (int i = 0; i < 8; i++) {
//			int nextRow = now.row + dr[i];
//			int nextCol = now.col + dc[i];
//
//			// 1,1 부토 시작하는 좌표임
//			if (nextRow < 1 || nextCol < 1 || nextRow > N || nextCol > N)continue;
//			if (visited[nextRow][nextCol] > 0)continue;
//			visited[nextRow][nextCol] = visited[now.row][now.col]+1;
//
//			// 산타 발견
//			if (Map[nextRow][nextCol] > 0) {
//				if (flag == 1) {
//					if (firstVisited == visited[nextRow][nextCol]) {
//						saveQ.push({ nextRow,nextCol });
//					}
//					else if (firstVisited < visited[nextRow][nextCol]) {
//						flag2 = 1;
//						break;
//					}
//				}
//				else {
//					saveQ.push({ nextRow,nextCol });
//					firstVisited = visited[nextRow][nextCol];
//					flag = 1;
//				}
//
//				//return { nextRow,nextCol };
//			}
//
//			q.push({ nextRow,nextCol });
//		}
//		if (flag2 == 1)break;
//	}
//	cmp nowP = { 0 };
//	if(!saveQ.empty())nowP = saveQ.top();
//	
//	return { nowP.row,nowP.col };
//}





int distance(Pair first, Pair second) {
	int diffRow = (first.row - second.row) * (first.row - second.row);
	int diffCol = (first.col - second.col) * (first.col - second.col);
	return (diffRow + diffCol);
}

struct node {
	int diff, row, col;
	bool operator<(node right) const{
		if (right.diff < diff)return true;
		if (right.diff > diff)return false;
		if (right.row > row)return true;
		if (right.row < row)return false;
		if (right.col > col)return true;
		if (right.col < col)return false;

	}
};

Pair findSanta() {
	priority_queue<node> q;
	Pair poi = { 0 };
	int minim = 21e8;
	for (int i = N; i > 0; i--) {
		for (int j = N; j > 0; j--) {
			if (Map[i][j] <= 0)continue;
			int index = Map[i][j];
			int row = arr[index].row;
			int col = arr[index].col;
			int dis = distance({ Rrow,Rcol }, { row,col });
			q.push({ dis ,row,col});
			if (dis < minim) {
				minim = dis;
				poi.row = row;
				poi.col = col;
			}
		}
	}
	node now = q.top();
	return {now.row,now.col};
}

Pair findCloseDir(Pair closeSanta) {
	// 지금위치에서 산타까지 거리
	int originDis = distance({ Rrow,Rcol }, closeSanta);

	// 지금위치에서의 거리랑 상관없이 무조건 8개중 가장 짧은거로 가는듯
	int minDis = 21e8;
	int dirRow = -1;
	int dirCol = -1;
	for (int i = 0; i < 8; i++) {
		int nextRow = Rrow + dr[i];
		int nextCol = Rcol + dc[i];
		if (nextRow < 1 || nextCol < 1 || nextRow > N || nextCol > N)continue;
		int nowDis = distance({ nextRow,nextCol }, closeSanta);
		if (nowDis < minDis) {
			minDis = nowDis;
			dirRow = dr[i];
			dirCol = dc[i];
		}
	}
	return { dirRow,dirCol };
}

//int interAction(Pair firstPoi, Pair secondPoi, Pair dir, int firstindex) {
//	
//	int firstRow = firstPoi.row;
//	int firstCol = firstPoi.col;
//	int firstIndex = firstindex;
//
//	int secondRow = secondPoi.row;
//	int secondCol = secondPoi.col;
//	int secondIndex = Map[secondPoi.row][secondPoi.col];
//
//	while (1 == 1) {
//
//		if (secondRow < 1 || secondCol < 1 || secondRow > N || secondCol > N) {
//			// 도착지점이 범위 밖인 경우
//			Map[firstRow][firstRow] = 0;
//			// 새로운 좌표 적용 할 필요 없음
//			//Map[targetRow][targetCol] = index;
//			// 산타 배열 초기화
//			arr[firstIndex].row = secondRow;
//			arr[firstIndex].col = secondCol;
//			// 즉음 표시
//			arr[firstIndex].dead = 1;
//			life--;
//			if (life <= 0)return -1;
//			break;
//		}
//		else if (Map[secondRow][secondCol] <= 0) {
//			// 도착지점에 아무것도 없는 경우
//			// 날아온 애 도착 시키기 연쇄가정인 경우 이거 하면 안됨
//			//Map[firstRow][firstCol] = 0;
//			// 새로운 좌표 적용
//			Map[secondRow][secondCol] = firstIndex;
//			// 산타 배열 초기화
//			arr[firstIndex].row = secondRow;
//			arr[firstIndex].col = secondCol;
//			break;
//		}
//
//		// 여기 오면 또 산타 만난 경우
//		// 2번를 1번으로 갱신 해야함
//		// 새로운 좌표를 2번으로 갱신하고
//		
//		// 일단 첫번째로 날라온애 2번째 좌표에 갱신
//		Map[firstRow][firstCol] = 0; // 이것도 하면 안됨 이전애거 줘야되는데
//
//		// 산타 배열 초기화
//		arr[firstIndex].row = secondRow;
//		arr[firstIndex].col = secondCol;
//
//
//		// 새로운 좌표 적용
//		//Map[secondRow][secondCol] = firstIndex;
//		//그리고 2번째 좌표인애는 첫번째 걸로 갱신
//		// 머를 갱신해야되지 index
//		firstIndex = secondIndex;
//		firstRow = secondRow;
//		firstCol = secondCol;
//
//		// 새로운 좌표 즉 second를 dir 로 1칸 움직인 좌표
//		int newPoiRow = secondRow + dir.row;
//		int newPoiCol = secondCol + dir.col;
//		int newIndex = Map[newPoiRow][newPoiCol];
//		// 위 값이 second가 됨
//		secondRow = newPoiRow;
//		secondCol = newPoiCol;
//		secondIndex = newIndex;
//	}
//	return 0;
//}
void interAction2(Pair firstPoi, Pair secondPoi, Pair dir, int firstindex) {

	int nextRow = firstPoi.row + dir.row;
	int nextCol = firstPoi.col + dir.col;

	if (nextRow < 1 || nextCol < 1 || nextRow > N || nextCol > N) {
		// 범위 초과
		//Map[nextRow][nextCol] = firstindex;
		arr[firstindex].row = nextRow;
		arr[firstindex].col = nextCol;
		arr[firstindex].dead = 1;
		life--;
		return;
	}
	else if (Map[nextRow][nextCol] <= 0) {
		// 아무도 없어
		Map[nextRow][nextCol] = firstindex;
		arr[firstindex].row = nextRow;
		arr[firstindex].col = nextCol;
		return;
	}

	int nextIndex = Map[nextRow][nextCol];
	interAction2({ nextRow,nextCol }, { nextRow,nextCol }, dir, nextIndex);

	Map[nextRow][nextCol] = firstindex;
	arr[firstindex].row = nextRow;
	arr[firstindex].col = nextCol;
}

void interAction(Pair firstPoi, Pair secondPoi, Pair dir, int firstindex) {

	int nowRow = firstPoi.row;
	int nowCol = firstPoi.col;
	Map[nowRow][nowCol] = 0;
	int nextIndex = Map[secondPoi.row][secondPoi.col];
	interAction2(secondPoi, secondPoi, dir, nextIndex);
	Map[secondPoi.row][secondPoi.col] = firstindex;
	arr[firstindex].row = secondPoi.row;
	arr[firstindex].col = secondPoi.col;
}



int accident(int nowTurn, Pair nowPoi, Pair dir, int score, int santaIndex) {
	// 새로운 위치
	int nextRow = nowPoi.row + dir.row * score;
	int nextCol = nowPoi.col + dir.col * score;

	// 먼저 점수 등록, 기절 등록
	arr[santaIndex].score += score;
	arr[santaIndex].stun = nowTurn;

	// 범위 밖 죽은 경우
	if (nextRow < 1 || nextCol < 1 || nextRow > N || nextCol > N) {
		// 배열및 산타함수초기화
		//기존배열 초기화
		Map[nowPoi.row][nowPoi.col] = 0;
		// 새로운 좌표 적용 할 필요 없음
		//Map[targetRow][targetCol] = index;
		// 산타 배열 초기화
		arr[santaIndex].row = nextRow;
		arr[santaIndex].col = nextCol;
		// 즉음 표시
		arr[santaIndex].dead = 1;
		life--;
		if (life <= 0)return -1;
	}
	else if (Map[nextRow][nextCol]>0) {
		// 날아간 위치에 산타 있는 경우
		// 상호작용함수 on
		interAction(nowPoi,{ nextRow ,nextCol}, dir,santaIndex);
		if (life <= 0)return -1;

	}
	else {
		// 아무것도 없어서 그냥 초기화만
		//기존배열 초기화
		Map[nowPoi.row][nowPoi.col] = 0;
		// 새로운 좌표 적용 할 필요 없음
		Map[nextRow][nextCol] = santaIndex;
		// 산타 배열 초기화
		arr[santaIndex].row = nextRow;
		arr[santaIndex].col = nextCol;
	}

	return 0;
}

int realMoveRu(Pair closeDir, int nowTurn) {
	int targetRow = Rrow + closeDir.row;
	int targetCol = Rcol + closeDir.col;
	if (Map[targetRow][targetCol] > 0) {
		// 산타 있으면 충돌함수
		int ans = accident(nowTurn,{ targetRow ,targetCol }, closeDir,C, Map[targetRow][targetCol]);
		// 루돌푸 무조건 이동
		Rrow += closeDir.row;
		Rcol += closeDir.col;
		if (ans == -1)return -1;
	}
	else {
		// 아무것도 없으면 그냥 감
		Rrow += closeDir.row;
		Rcol += closeDir.col;
	}

	return 0;
}

int moveRu(int nowTurn) {
	// 먼저 가장 가까운 산타 찾기 bfs 칸
	Pair closeSanta = findSanta();
	// 내 기준 8 방향에서 산타랑 가장 가까운 방향 찾기
	Pair closeDir = findCloseDir(closeSanta);
	// 이동 함수 
	int ans = realMoveRu(closeDir, nowTurn);
	if (ans == -1)return -1;

	return 0;
}

Pair findSantaToRu(Santa nowSanta) {

	// 지금 산타 좌표 
	int nowSRow = nowSanta.row;
	int nowSCol = nowSanta.col;

	// 지금위치에서 루돌프까지 거리
	int originDis = distance({ Rrow,Rcol }, { nowSRow,nowSCol });

	// 지금위치에서의 originDis보다 작은거 있어야 이동 하는듯
	int minDis = 21e8;
	int dirRow = -1;
	int dirCol = -1;
	for (int i = 0; i < 4; i++) {
		int nextRow = nowSRow + Sdr[i];
		int nextCol = nowSCol + Sdc[i];
		if (nextRow < 1 || nextCol < 1 || nextRow > N || nextCol > N)continue;
		if (Map[nextRow][nextCol] > 0)continue; // 산타 있으면 못감
		int nowDis = distance({ nextRow,nextCol }, { Rrow,Rcol });
		
		// 기존 거리보다 크거나 같으면 버림
		if (nowDis >= originDis)continue;

		// 작은것중에 가장 작은거 추출
		if (nowDis < minDis) {
			minDis = nowDis;
			dirRow = Sdr[i];
			dirCol = Sdc[i];
		}
	}
	return { dirRow,dirCol };
}

int realMoveSanta(int nowTurn, int index, Santa nowSanta, Pair closeDir) {
	// 위에서 검사해서 여기는 루돌프 만나거나 아무것도 없어나인경우만 존재
	int targetRow = nowSanta.row + closeDir.row;
	int targetCol = nowSanta.col + closeDir.col;
	if (targetRow == Rrow &&  targetCol==Rcol) {
		// 루돌프 있으면 충돌함수
		// 충돌함수 하기전에 움직여야함
		// 배열이랑 산타함수 초기화
		//기존배열 초기화
		Map[nowSanta.row][nowSanta.col] = 0;
		// 새로운 좌표 적용
		Map[targetRow][targetCol] = index;
		// 산타 배열 초기화
		arr[index].row = targetRow;
		arr[index].col = targetCol;
		int ans = accident(nowTurn,{ targetRow ,targetCol }, { -closeDir.row,-closeDir.col }, D, index);
		if (ans == -1)return -1;
	}
	else {
		// 아무것도 없으면 그냥 감
		// 배열이랑 산타함수 초기화
		//기존배열 초기화
		Map[nowSanta.row][nowSanta.col] = 0;
		// 새로운 좌표 적용
		Map[targetRow][targetCol] = index;
		// 산타 배열 초기화
		arr[index].row = targetRow;
		arr[index].col = targetCol;
	}

	return 0;
}

int moveSantaStart(int nowTurn) {
	// 산타 수만큼 돔
	for (int i = 1; i <= P; i++) {
		Santa nowSanta = arr[i];
		// 범위 밖에 가서 죽은애
		if (nowSanta.dead == 1)continue;
		// 바로 이전턴에 기절한 애들은 못씀
		if (nowTurn - nowSanta.stun <= 1)continue;
		// 상 하 좌 우 에서 가까운 거 추출
		Pair closeDir = findSantaToRu(nowSanta);

		// 가장 가까운 방향으로 갈 수 있는지 없는지 판단
		// 가까워지는 경우 없으면 다음으로
		if (closeDir.row == -1 && closeDir.col == -1)continue;
		else {
			// 가까워 지는거 있음
			// 움직임
			int ans = realMoveSanta(nowTurn, i,nowSanta, closeDir);
			if (ans == -1)return -1;
		}

	}

	return 0;
}

int startGame(int nowTurn) {
	// 루돌프 이동
	int ans2 = moveRu(nowTurn);
	if (ans2 == -1)return -1;
	//cout << "\n==============루돌프이동===========\n";
	//for (int r = 1; r <= N; r++) {
	//	for (int c = 1; c <= N; c++) {
	//		if (r == Rrow && c == Rcol)cout << "-1" << " ";
	//		else cout << Map[r][c] << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n============루돌프이동=============\n";
	// 산타 이동
	int ans = moveSantaStart(nowTurn);
	if (ans == -1)return -1;
	//cout << "\n==============산타이동===========\n";
	//for (int r = 1; r <= N; r++) {
	//	for (int c = 1; c <= N; c++) {
	//		if (r == Rrow && c == Rcol)cout << "-1" << " ";
	//		else cout << Map[r][c] << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n============산타이동=============\n";
	return 0;
}

void getPlus() {
	for (int i = 1; i <= P; i++) {
		if (arr[i].dead == 1)continue;
		arr[i].score++;
	}
}

void getScore() {
	for (int i = 1; i <= P; i++) {
		cout << arr[i].score << " ";
	}
}

int main() {
	cin >> N >> M >> P >> C >> D;
	cin >> Rrow >> Rcol;
	for (int i = 0; i < P; i++) {
		int index, Srow, Scol;
		cin >> index >> Srow >> Scol;
		Map[Srow][Scol] = index;
		arr[index].row = Srow;
		arr[index].col = Scol;
		arr[index].stun = -3;
	}

	life = P;

	for (int i = 1; i <= M; i++) {

		//cout << "\n=========시작전================\n";
		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		if (r == Rrow && c == Rcol)cout << "-1" << " ";
		//		else cout << Map[r][c] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n=========================\n";


		int ans = startGame(i);


		//cout << "\n"<<i<<"번턴끝==================\n";
		//getScore();
		//cout << "\n=========================\n";
		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		if (r == Rrow && c == Rcol)cout << "-1" << " ";
		//		else cout << Map[r][c] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n=========================\n";






		if (ans == -1)break;
		// 살아남은 애들 +1씩
		getPlus();
	}

	getScore();

	return 0;
}
