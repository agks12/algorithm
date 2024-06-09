#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
long long loopcnt;
struct MAP { int dead; vector<int> monster, egg; };
struct Pair { int row, col; };
MAP map[6][6]; // 1~4 만 씀
int arrDir[1000001];
int monsterIndex;
int m, t;
int pRow, pCol;
vector< pair<Pair, int>> vec;

int arr[65][3];

// 팩맨 dfs용
int visited[6][6];
int packmanCatchMonster;
int maxCatch;
int packMaxDir[4];
int realMaxDir[4];

// 1~ 8 씀
int dr[9] = { 0, -1 , -1, 0, 1, 1, 1, 0, -1 };
int dc[9] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };

// 팩맨 상하죄우 우선순위 방향
int pdr[4] = { -1,0,1,0 };
int pdc[4] = { 0,-1,0,1 };

void copyMonster() {
	vec.clear();
	// 배열 모든 칸 검사
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			// 몬스터 없으면 넘김
			if (map[r][c].monster.size() == 0)continue;
			// 몬스터 있으면 알 생성
			int monsterSize = map[r][c].monster.size();
			for (int i = 0; i < monsterSize; i++) {

				int index = map[r][c].monster[i];
				vec.push_back({ {r,c}, index });

				loopcnt++;
				int nowMonsterIndex = map[r][c].monster[i];
				int nowMonsterDir = arrDir[nowMonsterIndex];
				map[r][c].egg.push_back(monsterIndex); // 맵에 번호로 저장
				arrDir[monsterIndex] = nowMonsterDir; // 배열에 방향저장
				monsterIndex++;
			}
		}
	}
}

void realMoveMonster(Pair stPoi, int nowIndex) {
	// 8가지 방향 모두 검사 처음 가능한 방향으로 ㄱㄱ
	// 지금 방향에서 ++ 해가면서 9되면 1로 갱신 하면 가능
	int origin = arrDir[nowIndex];
	int nowMonsterDir = arrDir[nowIndex];
	for (int i = 0; i < 8; i++) {
		if (nowMonsterDir == 9)nowMonsterDir = 1;
		int nextRow = stPoi.row + dr[nowMonsterDir];
		int nextCol = stPoi.col + dc[nowMonsterDir];
		loopcnt++;
		// 범위초과
		if (nextRow <= 0 || nextCol <= 0 || nextRow > 4 || nextCol > 4) {
			// 방향전환
			nowMonsterDir++;
			continue;
		}
		// 시체있음 나 팩맨있음
		if (map[nextRow][nextCol].dead > 0 || (nextRow == pRow && nextCol == pCol)) {
			// 방향전환
			nowMonsterDir++;
			continue;
		}
		
		// 여기 도달하면 갈수 있는 위치여서 가고 리턴하면 끝
		// 맵 갱신

		// 기존 거 삭제
		map[stPoi.row][stPoi.col].monster.erase(remove(map[stPoi.row][stPoi.col].monster.begin(), map[stPoi.row][stPoi.col].monster.end(), nowIndex), map[stPoi.row][stPoi.col].monster.end());

		// 새로운 위치에 추가
		map[nextRow][nextCol].monster.push_back(nowIndex);

		// 방향배열에 지금 몬스터 방향 갱신
		arrDir[nowIndex] = nowMonsterDir;
		//cout << "\n "<<"방향"<< origin <<"움직이는 애새기" << stPoi.row << ", " << stPoi.col << " ==> " << nextRow << ", " << nextCol << "\n";
		return;
	}
}

void moveMonster() {

	// 배열 모든 칸 검사 하면 안됨 무한이동됨
	// 좌표저장하면 안되고 애들 번호로 해야함
	//for (int r = 1; r <= 4; r++) {
	//	for (int c = 1; c <= 4; c++) {
	//		// 몬스터 없으면 넘김
	//		if (map[r][c].monster.size() == 0)continue;
	//		int monsterSize = map[r][c].monster.size();
	//		for (int i = 0; i < monsterSize; i++) {
	//			int index = map[r][c].monster[i];
	//			// 몬스터 있으면 몬스터 모두 저장
	//			vec.push_back({ {r,c}, index });
	//		}
	//	}
	//}
	for (int i = 0; i < vec.size(); i++) {
		Pair stPoi = vec[i].first;
		int index = vec[i].second;
		realMoveMonster(stPoi, index);
	}
	//int monsterPoiSize = v.size();
	//for (int s = 0; s < monsterPoiSize; s++) {
	//	int r = v[s].row;
	//	int c = v[s].col;
	//	int monsterSize = map[r][c].monster.size();
	//	for (int i = 0; i < monsterSize; i++) {
	//		int nowMonsterIndex = map[r][c].monster[i];
	//		realMoveMonster({ r,c }, nowMonsterIndex);
	//	}
	//}

}


//void visitedReset() {
//	for (int i = 1; i <= 4; i++) {
//		for (int j = 1; j <= 4; j++) {
//			visited[i][j] = 0;
//		}
//	}
//}



int cnt = 0;
//void searchDfs(Pair nowPoi, int level) {
//
//
//	if (level == 3) {
//		//cout << "\n";
//		//cout <<"\n" << packMaxDir[0] << " " << packMaxDir[1] << " " << packMaxDir[2] << "\n";
//		// 3칸 다돔
//
//		//cout << "level" << level << "좌표 ";
//		//for (int i = 0; i < level; i++) {
//		//	cout << packMaxDir[i] << " ";
//		//}
//		//cout << "\n";
//
//
//		if (maxCatch < packmanCatchMonster) {
//			// 최대값보다 지금 잡은게 더큼 갱신해야함
//			maxCatch = packmanCatchMonster;
//			for (int i = 0; i < 3; i++) {
//				realMaxDir[i] = packMaxDir[i];
//			}
//		}
//		return;
//		
//	}
//
//	for (int i = 0; i < 4; i++) {
//		int nextRow = nowPoi.row + pdr[i];
//		int nextCol = nowPoi.col + pdc[i];
//		cnt++;
//		//cout <<"번쨰" << i << " ";
//		if (nextRow <= 0 || nextCol <= 0 || nextRow > 4 || nextCol > 4)continue;
//		
//
//		int nowMonsterCnt = map[nextRow][nextCol].monster.size();
//		if (visited[nextRow][nextCol] == 1) {
//			nowMonsterCnt = 0;
//		}
//		packmanCatchMonster += nowMonsterCnt;
//		packMaxDir[level] = i; // 지금 방향 저장
//
//		visited[nextRow][nextCol] = 1;
//		searchDfs({ nextRow,nextCol },level+1);
//
//		// 이칸 벗어나면 다시 뺴줘야함
//		packmanCatchMonster -= nowMonsterCnt;
//
//		if (level == 0) {
//			visitedReset();
//		}
//		visited[nextRow][nextCol] = 0;
//	}
//}

int maxIndex = -1;

void searchDfs(Pair stPoi,int level) {
	int flag = 0;
	int nowSum = 0;
	int maxim = -1;
	maxIndex = -1;
	for (int i = 0; i < 64; i++) {
		int nowArrIndex = i;
		nowSum = 0;
		flag = 0;
		int visited[5][5] = { 0 };
		int nowRow = stPoi.row;
		int nowCol = stPoi.col;
		for (int r = 0; r < 3; r++) {
			nowRow += pdr[arr[nowArrIndex][r]];
			nowCol += pdc[arr[nowArrIndex][r]];
			loopcnt++;
			if (nowRow <= 0 || nowCol <= 0 || nowCol > 4 || nowCol > 4) {
				flag = 1;
				break;
			}
			if (visited[nowRow][nowCol] == 1) {
				nowSum += 0;
			}
			else {
				nowSum += map[nowRow][nowCol].monster.size();
			}
			visited[nowRow][nowCol] = 1;
		}
		if (flag == 1)continue;
		if (nowSum > maxim) {
			maxim = nowSum;
			maxIndex = nowArrIndex;
		}
	}
}

void movePackman(int nowturn) {
	cnt = 0;
	packmanCatchMonster = 0;
	maxCatch = -1;
	
	//visitedReset();

	searchDfs({pRow,pCol},0);
	//visited[pRow][pCol] = 0;

	for (int i = 0; i < 3; i++) {
		realMaxDir[i] = arr[maxIndex][i];
	}

	// realMaxDir 에 최대로 되는 경로 저장됨 이경로대로 몬스터 시체로 만들면서 아ㅣ동하면됨
	int originRow = pRow;
	int originCol = pCol;
	//cout << "\n 팩맨위치"<<pRow<<","<<pCol << "최대값" << realMaxDir[0] << " " << realMaxDir[1] << " " << realMaxDir[2] << "\n";
	for (int i = 0; i < 3; i++) {
		int nowPackDir = realMaxDir[i];
		pRow += pdr[nowPackDir];
		pCol += pdc[nowPackDir];
		//cout << pRow << "," << pCol<<" ";
		// 지금위치 몬스터 모두 소멸
		//if (pRow == originRow && pCol == originCol)continue;
		if (map[pRow][pCol].monster.size() == 0)continue;
		map[pRow][pCol].monster.clear();
		// 그리고 시체로 만들기
		map[pRow][pCol].dead = nowturn;
	}
	//cout << "\n";
}

void removeDead(int nowturn) {
	// 배열 모든 칸 검사
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			// 시체 없으면 넘김
			loopcnt++;
			if (map[r][c].dead <= 0)continue;
			// 시체 2개 턴 넘었으면 제거
			//cout << "\n 지금턴 시체들" << r << "," << c << " " << nowturn << " " <<map[r][c].dead << " \n";
			if (nowturn - map[r][c].dead >= 2) {
				//cout << "\n 지금턴 삭제시체들" << r << "," << c << " " << nowturn << " " << map[r][c].dead << " \n";

				map[r][c].dead = 0;

			}
		}
	}
}

void createMonster() {
	// 배열 모든 칸 검사
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			// 알 없으면 넘김
			loopcnt++;
			if (map[r][c].egg.size() == 0)continue;
			// 알 몬스터로 변환
			int eggSize = map[r][c].egg.size();
			map[r][c].monster.insert(map[r][c].monster.end(), map[r][c].egg.begin(), map[r][c].egg.end());
			//for (int i = 0; i < eggSize; i++) {
			//	
			//	int nowEgg = map[r][c].egg[i];
			//	// 몬스터에 추가
			//	map[r][c].monster.push_back(nowEgg);
			//}
			// 알제거는 어차피 모든 알 부하시키므로 clear하면 되릇
			map[r][c].egg.clear();
		}
	}
}

int getMonster() {
	int cnt = 0;
	// 배열 모든 칸 검사
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			// 알 없으면 넘김
			loopcnt++;
			if (map[r][c].monster.size() == 0)continue;
			cnt += map[r][c].monster.size();
		}
	}
	return cnt;
}
int subarr[3];
void dfsArr(int level) {
	if (level == 3) {
		for (int i = 0; i < 3; i++) {
			arr[cnt][i] = subarr[i];
		}
		cnt++;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nowdir = i;
		//arr[cnt][level] = i;
		loopcnt++;
		subarr[level] = i;
		dfsArr(level + 1);
	}
}

int main() {
	cin >> m >> t;
	cin >> pRow >> pCol;

	for (int i = 1; i <= m; i++) {
		int r, c, d;
		cin >> r >> c >> d;
		map[r][c].monster.push_back(i);
		arrDir[i] = d;
	}

	dfsArr(0);

	monsterIndex = m + 1;
	for (int i = 1; i <= t; i++) {
		copyMonster();
		//cout << "\ncopy" << i << "턴\n";

		//for (int r = 1; r <= 4; r++) {
		//	for (int c = 1; c <= 4; c++) {
		//		// 알 없으면 넘김
		//		if (map[r][c].monster.size() == 0)cout << 0;
		//		else cout << map[r][c].monster.size();
		//		cout << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n==========움직이기전====================\n";


		moveMonster();
		//cout << "\nmoveMonster" << i << "턴\n";
		
		//for (int r = 1; r <= 4; r++) {
		//	for (int c = 1; c <= 4; c++) {
		//		// 알 없으면 넘김
		//		if (map[r][c].monster.size() == 0)cout << 0;
		//		else cout << map[r][c].monster.size();
		//		cout << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << pRow << " " << pCol << " \n";
		//cout << "\n==========움직이고 나서====================\n";

		movePackman(i);
		//cout << "     " << pRow << " " << pCol << " \n";
		////cout << "\nmovePackman" << i << "턴\n";

		//for (int r = 1; r <= 4; r++) {
		//	for (int c = 1; c <= 4; c++) {
		//		// 알 없으면 넘김
		//		if (map[r][c].monster.size() == 0)cout << 0;
		//		else cout << map[r][c].monster.size();
		//		cout << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n==========팩맨 움직여서 먹히고 나서====================\n";


		removeDead(i);
		//cout << "\nremoveDead" << i << "턴\n";
		createMonster();
		//cout << "\ncreateMonster" << i << "턴\n";
		//for (int r = 1; r <= 4; r++) {
		//	for (int c = 1; c <= 4; c++) {
		//		// 알 없으면 넘김
		//		if (map[r][c].monster.size() == 0)cout << 0;
		//		else cout << map[r][c].monster.size();
		//		cout << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n==========복제되고 생기고 나서====================\n";
	}

	int ans = getMonster();
	cout << ans;
	//cout << "\n" << loopcnt;
	return 0;
}
