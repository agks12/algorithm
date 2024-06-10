#include<iostream>
#include<algorithm>
#include<vector>

// 같은 방향 애들은 한번에 옮겨야함
// 움직일때 움직인 좌표건드리면 안되서 복사배열 이용해야함 움직이기전에 살아있는 모든애는 복사배열애 넣고 살아있는 모든애 초기화하고 복사배열에 있는에 움직임

using namespace std;
long long loopcnt;
struct MAP { int dead, cnt; vector<int> monster[9] = {}, egg[9] = {}; };
struct Pair { int row, col; };
MAP map[6][6]; // 1~4 만 씀
MAP mapcopy[6][6]; // 1~4 만 씀
//int arrDir[1000001];
//int monsterIndex;
int m, t;
int pRow, pCol;
vector< pair<Pair, Pair>> vec;

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
	//vec.clear();
	// 배열 모든 칸 검사
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			// 몬스터 없으면 넘김
			for (int i = 1; i <= 8; i++) {
				// 지금 좌표에서 각 방향 검사
				if (map[r][c].monster[i].size() == 0)continue;
				// 만약 존재하면 어느방향 즉 어느 좌표로 움직일지 검사해서 저장
				// 알도 까야함 알은 그냥 지금거 그대로 인덱스 필요 없으므로 그냥 바로 복사
				map[r][c].egg[i].clear();
				mapcopy[r][c].monster[i].clear();
				//알까기 
				map[r][c].egg[i].insert(map[r][c].egg[i].end(),map[r][c].monster[i].begin(), map[r][c].monster[i].end());
				mapcopy[r][c].monster[i].insert(mapcopy[r][c].monster[i].end(), map[r][c].monster[i].begin(), map[r][c].monster[i].end());
				int nowSize = map[r][c].monster[i].size();
				map[r][c].cnt += nowSize;
				map[r][c].monster[i].clear();
				// 다음 좌표로 움직일 애들 벡터에 표시 - 몇개 움직일지 표시해야함 그래야
				// 0~몇번 인덱스만 움직일건지 즉 사이즈
				//vec.push_back({ {r,c}, {i,nowSize } });
			}
		}
	}
}

int realMoveMonster(Pair stPoi, int nowdir) {
	// 8가지 방향 모두 검사 처음 가능한 방향으로 ㄱㄱ
	// 지금 방향에서 ++ 해가면서 9되면 1로 갱신 하면 가능
	//int origin = arrDir[nowIndex];

	//int nowSize = nowdir.col;

	int originDir = nowdir;
	int nowMonsterDir = nowdir;
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
		//vector<int> v = {};
		//v.insert(v.end(),map[stPoi.row][stPoi.col].monster[originDir].begin(), map[stPoi.row][stPoi.col].monster[originDir].begin() + nowSize);

		// 새로운 위치에 추가
		//map[nextRow][nextCol].cnt += nowSize;
		//map[nextRow][nextCol].monster[nowMonsterDir].insert(map[nextRow][nextCol].monster[nowMonsterDir].end(),v.begin(),v.end());//.push_back(nowIndex);


		// 기존 거  전부 삭제
		//map[stPoi.row][stPoi.col].monster[originDir].clear();//erase(remove(map[stPoi.row][stPoi.col].monster[originDir].begin(), map[stPoi.row][stPoi.col].monster[originDir].end(), nowIndex), map[stPoi.row][stPoi.col].monster.end());
		//map[stPoi.row][stPoi.col].cnt -= nowSize;
		

		// 방향배열에 지금 몬스터 방향 갱신
		//arrDir[nowIndex] = nowMonsterDir;
		//cout << "\n "<<"방향"<< origin <<"움직이는 애새기" << stPoi.row << ", " << stPoi.col << " ==> " << nextRow << ", " << nextCol << "\n";
		return nowMonsterDir;
	}
	return -1;
}

void moveMonster() {

	// 배열 모든 칸 검사
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			for (int i = 1; i <= 8; i++) {
				//map[r][c].monster[i].clear();
				if (mapcopy[r][c].monster[i].size() == 0)continue;
				int ans = realMoveMonster({r,c}, i);
				if (ans == -1) {
					map[r][c].monster[i].insert(map[r][c].monster[i].end(), mapcopy[r][c].monster[i].begin(), mapcopy[r][c].monster[i].end());

					mapcopy[r][c].monster[i].clear();
					continue;
				}
				int nextRow = r + dr[ans];
				int nextCol = c + dc[ans];

				map[r][c].cnt -= map[r][c].monster[i].size();
				map[nextRow][nextCol].cnt += map[r][c].monster[i].size();
				
				map[nextRow][nextCol].monster[ans].insert(map[nextRow][nextCol].monster[ans].end(), mapcopy[r][c].monster[i].begin(), mapcopy[r][c].monster[i].end());
				
				//map[r][c].monster[i].clear();
				mapcopy[r][c].monster[i].clear();
			}

		}
	}

	//for (int i = 0; i < vec.size(); i++) {
	//	Pair stPoi = vec[i].first;
	//	Pair dir = vec[i].second;
	//	// 좌표랑 방향
	//	realMoveMonster(stPoi, dir);
	//}

}

int cnt = 0;

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
			if (nowRow <= 0 || nowCol <= 0 || nowRow > 4 || nowCol > 4) {
				flag = 1;
				break;
			}
			if (visited[nowRow][nowCol] == 1) {
				nowSum += 0;
			}
			else {

				// 8방향 모두 더해야함
				for (int i = 1; i <= 8; i++) {
					nowSum += map[nowRow][nowCol].monster[i].size();
				}

				//nowSum += map[nowRow][nowCol].monster.size();
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
		int flag = 0;
		for (int i = 1; i <= 8; i++) {
			if (map[pRow][pCol].monster[i].size() > 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0)continue;

		int ccc = 0;
		//if (map[pRow][pCol].monster.size() == 0)continue;
		for (int i = 1; i <= 8; i++) {
			ccc += map[pRow][pCol].monster[i].size();
			map[pRow][pCol].monster[i].clear();

		}
		//map[pRow][pCol].monster.clear();
		// 그리고 시체로 만들기
		map[pRow][pCol].dead = nowturn;
		map[pRow][pCol].cnt -= ccc;
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

	//for (int r = 1; r <= 4; r++) {
	//	for (int c = 1; c <= 4; c++) {
	//		int cag = 0;
	//		for (int i = 1; i <= 8; i++) {
	//			cag += map[r][c].monster[i].size();
	//		}
	//		// 알 없으면 넘김
	//		//if (map[r][c].monster.size() == 0)cout << 0;
	//		cout << cag;
	//		cout << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n==========알까기전====================\n";


	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			// 알 없으면 넘김
			loopcnt++;
			for (int i = 1; i <= 8; i++) {
				if (map[r][c].egg[i].size() == 0)continue;
				map[r][c].cnt += map[r][c].egg[i].size();
				map[r][c].monster[i].insert(map[r][c].monster[i].end(), map[r][c].egg[i].begin(), map[r][c].egg[i].end());
				map[r][c].egg[i].clear();
			}
		}
	}


	//for (int r = 1; r <= 4; r++) {
	//	for (int c = 1; c <= 4; c++) {
	//		int cag = 0;
	//		for (int i = 1; i <= 8; i++) {
	//			cag += map[r][c].monster[i].size();
	//		}
	//		// 알 없으면 넘김
	//		//if (map[r][c].monster.size() == 0)cout << 0;
	//		cout << cag;
	//		cout << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n==========알까기후====================\n\n\n\n\n\n";
}

int getMonster() {
	int cnt = 0;
	// 배열 모든 칸 검사




	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 4; c++) {
			// 알 없으면 넘김
			loopcnt++;
			for (int i = 1; i <= 8; i++) {
				if (map[r][c].monster[i].size() == 0)continue;
				cnt += map[r][c].monster[i].size();
			}
			//if (map[r][c].monster.size() == 0)continue;
			//cnt += map[r][c].monster.size();
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
		map[r][c].monster[d].push_back(i);
		//arrDir[i] = d;
	}

	dfsArr(0);

	//monsterIndex = m + 1;
	for (int i = 1; i <= t; i++) {
		copyMonster();
		//cout << "\ncopy" << i << "턴\n";

		//for (int r = 1; r <= 4; r++) {
		//	for (int c = 1; c <= 4; c++) {
		//		// 알 없으면 넘김
		//		//if (map[r][c].monster.size() == 0)cout << 0;
		//		cout << map[r][c].cnt;
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
		//		//if (map[r][c].monster.size() == 0)cout << 0;
		//		cout << map[r][c].cnt;
		//		cout << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << pRow << " " << pCol << " \n";
		//cout << "\n==========움직이고 나서====================\n";
		//for (int r = 1; r <= 4; r++) {
		//	for (int c = 1; c <= 4; c++) {
		//		int cag = 0;
		//		for (int i = 1; i <= 8; i++) {
		//			cag += map[r][c].monster[i].size();
		//		}
		//		// 알 없으면 넘김
		//		//if (map[r][c].monster.size() == 0)cout << 0;
		//		cout << cag;
		//		cout << " ";
		//	}
		//	cout << "\n";
		//}
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
		//		int cag = 0;
		//		for (int i = 1; i <= 8; i++) {
		//			cag += map[r][c].monster[i].size();
		//		}
		//		// 알 없으면 넘김
		//		//if (map[r][c].monster.size() == 0)cout << 0;
		//		cout << cag;
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
