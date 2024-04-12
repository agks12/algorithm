#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair { int row, col; };
struct track { Pair dir; vector<Pair> v; };
int N, M, K, life;
Pair arr[11][11];

int dr[4] = { 0,1,0,-1 }; // 우 하 좌 상 우선순위
int dc[4] = { 1,0,-1,0 };

int dr8[8] = { 0,1,0,-1 , -1,-1,1,1 }; // 우 하 좌 상 우선순위
int dc8[8] = { 1,0,-1,0, -1,1,-1,1 };

Pair findMin() {

	int Min = 10000;
	int minRow = -1;
	int minCol = -1;
	int lastN = -1;
	int addRC = -1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			if (arr[i][j].row <= 0)continue; // 죽은애 넘김

			if (arr[i][j].row <= Min) {
				// 만약 1번 조건 2개 이상인 경우
				if (arr[i][j].row == Min) {
					// 가장 최근거 선택
					if (arr[i][j].col >= lastN) {
						// 만약 2번 조건 2개 인 경우
						if (arr[i][j].col == lastN) {
							//행 열 합 제일 큰거 선택
							if (i + j >= addRC) {
								//만약 3번 조건이 2개 인 경우
								if (i + j == addRC) {
									// 열 가장 큰거 선택
									if (i > minCol) {
										//2차 조건에서 끝
										Min = arr[i][j].row;
										minRow = i;
										minCol = j;
										lastN = arr[i][j].col;
										addRC = i + j;
									}
								}
								else {
									//3차 조건에서 끝
									Min = arr[i][j].row;
									minRow = i;
									minCol = j;
									lastN = arr[i][j].col;
									addRC = i + j;
								}
							}
						}
						else {
							//2차 조건에서 끝
							Min = arr[i][j].row;
							minRow = i;
							minCol = j;
							lastN = arr[i][j].col;
							addRC = i + j;
						}
					}
				}
				else {
					//1차 조건에서 끝
					Min = arr[i][j].row;
					minRow = i;
					minCol = j;
					lastN = arr[i][j].col;
					addRC = i + j;
				}
			}
		}
	}

	return { minRow,minCol };
}


Pair findMax(Pair minPair) {

	int Max = -1;
	int maxRow = -1;
	int maxCol = -1;
	int lastN = -1;
	int addRC = -1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			if (arr[i][j].row <= 0)continue; // 죽은애 넘김
			if (minPair.row == i && minPair.col == j)continue; // 선택된 최소값 선택 안하기

			if (arr[i][j].row >= Max) {
				// 만약 1번 조건 2개 이상인 경우
				if (arr[i][j].row == Max) {
					// 가장 최근거 선택
					if (arr[i][j].col <= lastN) {
						// 만약 2번 조건 2개 인 경우
						if (arr[i][j].col == lastN) {
							//행 열 합 제일 큰거 선택
							if (i + j <= addRC) {
								//만약 3번 조건이 2개 인 경우
								if (i + j == addRC) {
									// 열 가장 큰거 선택
									if (i < maxCol) {
										//2차 조건에서 끝
										Max = arr[i][j].row;
										maxRow = i;
										maxCol = j;
										lastN = arr[i][j].col;
										addRC = i + j;
									}
								}
								else {
									//3차 조건에서 끝
									Max = arr[i][j].row;
									maxRow = i;
									maxCol = j;
									lastN = arr[i][j].col;
									addRC = i + j;
								}
							}
						}
						else {
							//2차 조건에서 끝
							Max = arr[i][j].row;
							maxRow = i;
							maxCol = j;
							lastN = arr[i][j].col;
							addRC = i + j;
						}
					}
				}
				else {
					//1차 조건에서 끝
					Max = arr[i][j].row;
					maxRow = i;
					maxCol = j;
					lastN = arr[i][j].col;
					addRC = i + j;
				}
			}
		}
	}

	return { maxRow,maxCol };
}

vector<Pair> LaserAttact(Pair attPair, Pair recivePair) {
	queue<track> q;
	q.push({ attPair.row, attPair.col });
	int visited[11][11] = { 0 };
	visited[attPair.row][attPair.col] = 1;

	while (!q.empty()) {
		track now = q.front(); q.pop();
		
		vector<Pair> v2;
		for (int i = 0; i < 4; i++) {
			v2 = now.v;
			int nextRow = now.dir.row + dr[i];
			int nextCol = now.dir.col + dc[i];
			if (nextRow == -1)nextRow = N - 1; // 상 으로 초과하면 하에서 나타남
			else if (nextRow == N)nextRow = 0; // 하 에서 초과하면 상에서 나타남

			if (nextCol == -1)nextCol = M - 1; // 좌 으로 초과하면 우에서 나타남
			else if (nextCol == M)nextCol = 0; // 우 에서 초과하면 좌에서 나타남

			if (arr[nextRow][nextCol].row <= 0)continue;
			if (visited[nextRow][nextCol] > 0)continue;
			visited[nextRow][nextCol] = 1;

			v2.push_back({ nextRow,nextCol });
			q.push({{ nextRow,nextCol }, v2 });
			if (nextRow == recivePair.row && nextCol == recivePair.col) {
				return v2;
			}
		}
	}

	vector<Pair> v2;
	v2.push_back({ -1,-1 });
	return v2;
}

void noTuachAdd(vector<Pair> noList) {

	int visited[11][11] = { 0 };
	for (int i = 0; i < noList.size(); i++) {
		int row = noList[i].row;
		int col = noList[i].col;
		visited[row][col] = 1;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j].row <= 0)continue;
			if (visited[i][j] == 1)continue;
			arr[i][j].row += 1;
		}
	}
}

void laserStart(vector<Pair> laserTorF, Pair minPair) {
	//레이저 공격 성공
			//벡터  마지막애 빼고 /2 닭고 마지막은 그대로 담
	int damege = arr[minPair.row][minPair.col].row;
	for (int Le = 0; Le < laserTorF.size() - 1; Le++) {
		int nowRow = laserTorF[Le].row;
		int nowCol = laserTorF[Le].col;
		arr[nowRow][nowCol].row -= (damege / 2);
		if (arr[nowRow][nowCol].row <= 0)life--;
	}
	//마지막은 그대로 데미지
	int targetRow = laserTorF[laserTorF.size() - 1].row;
	int targetCol = laserTorF[laserTorF.size() - 1].col;
	arr[targetRow][targetCol].row -= damege;
	if (arr[targetRow][targetCol].row <= 0)life--;
}

vector<Pair> dafoStart(Pair attPair, Pair recivePair) {

	int targetRow = recivePair.row;
	int targetCol = recivePair.col;
	
	int damege = arr[attPair.row][attPair.col].row;

	vector<Pair> v; // 무관한 애들 판별하기 위한 반한값
	v.push_back({ attPair });

	// 주변 1거리인 애들 검사 
	for (int i = 0; i < 8; i++) {
		int nextRow = targetRow + dr8[i];
		int nextCol = targetCol + dc8[i];

		if (nextRow < 0 || nextRow >= N || nextCol < 0 || nextCol >= M)continue;

		//if (nextRow == -1)nextRow = N - 1; // 상 으로 초과하면 하에서 나타남
		//else if (nextRow == N)nextRow = 0; // 하 에서 초과하면 상에서 나타남

		//if (nextCol == -1)nextCol =  M - 1; // 좌 으로 초과하면 우에서 나타남
		//else if (nextCol == M)nextCol = 0; // 우 에서 초과하면 좌에서 나타남

		if (arr[nextRow][nextCol].row <= 0)continue;

		arr[nextRow][nextCol].row -= (damege / 2);
		
		if (arr[nextRow][nextCol].row <= 0)life--;

		if (arr[nextRow][nextCol].row > 0)v.push_back({ nextRow,nextCol });
	}

	// 타겟 타격
	arr[targetRow][targetCol].row -= damege;
	if (arr[targetRow][targetCol].row <= 0)life--;

	if (arr[targetRow][targetCol].row > 0)v.push_back({ recivePair });

	return v;
}


int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j].row;
			if (arr[i][j].row > 0)life++;
		}
	}

	for (int i = 1; i <= K; i++) {
		Pair minPair = findMin();
		Pair maxPair = findMax(minPair);
		cout << "left" << life << " \n";
		//여기 선정되면 무조건 공격할 수 있으므로 값 변경할게 최근 공격으로
		arr[minPair.row][minPair.col].col = i;
		arr[minPair.row][minPair.col].row += N+M;

		vector<Pair> laserTorF = LaserAttact(minPair, maxPair);

		vector<Pair> dafoList;
		//레이저 or 대포 선택
		if (laserTorF[0].row == -1 && laserTorF[0].col == -1) {
			dafoList = dafoStart(minPair, maxPair);// 레이저 공격못함//레이저 공격 못하면 대포 시도		
			noTuachAdd(dafoList);	//무관한 애들 +1 해주기
		}
		else {
			laserStart(laserTorF, minPair);
			laserTorF.push_back({ minPair });
			noTuachAdd(laserTorF);	//무관한 애들 +1 해주기
		}

		
		cout << "left" << life << " \n";

		cout << "\n====================\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << arr[i][j].row << " ";

			}
			cout << "\n";
		}
		cout << "\n====================\n";

		if (life <= 1)break;
	}










	int Maxim = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j].row > Maxim)Maxim = arr[i][j].row;
		}
	}
	cout << Maxim;




	return 0;
}
