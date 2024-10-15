#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Node {
	int to, cost, cnt;
	bool operator<(Node right)const {
		if (right.cost < cost)return true;
		if (right.cost > cost)return false;
		if (right.to > to)return true;
		if (right.to < to)return false;
		return false;
	}
};

int n, m;
vector<Node> v[101];
int visited[101];
int dist[101];
int traceDAT[101];

void djk() {
	for (int i = 0; i <= n; i++)dist[i] = 21e8;

	// 이동경로 저장

	priority_queue<Node> pq;
	pq.push({ 1,0,1 });
	dist[1] = 0;

	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();
		int nowCost = now.cost; // 쓸모없음 pq저장될 때만?
		int nowSize = v[now.to].size();
		int nowCnt = now.cnt;
		//cout << "지금시작점" << now.to<<" "<<nowSize << "\n";
		if (visited[now.to] == 1)continue;
		visited[now.to] = 1;
		
		for (int i = 0; i < nowSize; i++) {
			int nextNode = v[now.to][i].to;
			int nextCost = v[now.to][i].cost;


			if (dist[now.to] + nextCost > dist[nextNode])continue;
			if (dist[now.to] + nextCost == dist[nextNode]) {
				if (nowCnt + 1 >= traceDAT[nextNode])continue;
			}

			dist[nextNode] = dist[now.to] + nextCost;
			traceDAT[nextNode] = nowCnt+1;
			pq.push({ nextNode,dist[nextNode],nowCnt+1 });
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int from, to, cost, costPerMin, time; // time * costPerMin 한 값이 최종비용에 플러스
		cin >> from >> to >> cost >> costPerMin >> time;
		if (time > 10) {
			// 추가 요금 계산
			int plusCost = (time - 10) * costPerMin;
			cost += plusCost;
		}
		v[from].push_back({ to,cost });
	}

	// 무조건 1에서 n까지 최소비용 dist[n]
	djk();

	if (dist[n] == 21e8)cout << -1;
	else {
		cout << dist[n] << " " << traceDAT[n];
	}

	return 0;
}

// 벡터로 경로추적해서 경로 길이 계산하는데 왜 틀리지?
//#include<iostream>
//#include<queue>
//#include<vector>
//using namespace std;
//
//struct Node {
//	int to, cost;
//	bool operator<(Node right)const {
//		if (right.cost < cost)return true;
//		if (right.cost > cost)return false;
//		if (right.to > to)return true;
//		if (right.to < to)return false;
//		return false;
//	}
//};
//
//int n, m;
//vector<Node> v[101];
//int visited[101];
//int dist[101];
//int traceDAT[101];
//
//void djk() {
//	for (int i = 0; i <= n; i++)dist[i] = 21e8;
//
//	// 이동경로 저장
//	queue<vector<int>> q;
//	vector<int> trace;
//	trace.push_back(1);
//	q.push(trace);
//
//	priority_queue<Node> pq;
//	pq.push({ 1,0 });
//	dist[1] = 0;
//
//	while (!pq.empty()) {
//		Node now = pq.top(); pq.pop();
//		int nowCost = now.cost; // 쓸모없음 pq저장될 때만?
//		int nowSize = v[now.to].size();
//
//		//cout << "지금시작점" << now.to<<" "<<nowSize << "\n";
//		if (visited[now.to] == 1)continue;
//		visited[now.to] = 1;
//
//		vector<int> nowTrace = q.front(); q.pop();
//		for (int i = 0; i < nowSize; i++) {
//			int nextNode = v[now.to][i].to;
//			int nextCost = v[now.to][i].cost;
//
//			vector<int> copyVector = nowTrace;
//
//			//cout << "cost" << dist[now.to] << " " << nextCost << " " << dist[nextNode]<<"\n";
//			if (dist[now.to] + nextCost > dist[nextNode])continue;
//			if (dist[now.to] + nextCost == dist[nextNode]) {
//				if (copyVector.size() + 1 >= traceDAT[nextNode])continue;
//			}
//			copyVector.push_back(nextNode);
//			q.push(copyVector);
//
//			//cout << "지금 이동경로 합" << copyVector.size() << "\n";
//			dist[nextNode] = dist[now.to] + nextCost;
//			traceDAT[nextNode] = copyVector.size();
//			//cout << nextNode << " " << dist[nextNode] << "\n";
//			pq.push({ nextNode,dist[nextNode] });
//		}
//	}
//}
//
//int main() {
//	cin >> n >> m;
//	for (int i = 0; i < m; i++) {
//		int from, to, cost, costPerMin, time; // time * costPerMin 한 값이 최종비용에 플러스
//		cin >> from >> to >> cost >> costPerMin >> time;
//		if (time > 10) {
//			// 추가 요금 계산
//			int plusCost = (time - 10) * costPerMin;
//			cost += plusCost;
//		}
//		v[from].push_back({ to,cost });
//	}
//
//	// 무조건 1에서 n까지 최소비용 dist[n]
//	djk();
//
//	if (dist[n] == 21e8)cout << -1;
//	else {
//		cout << dist[n] << " " << traceDAT[n];
//	}
//
//	return 0;
//}
