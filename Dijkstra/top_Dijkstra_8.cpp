#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node { 
	int to, cost; 
	bool operator<(node right) const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		return false;
	}
};
int visited[100001];
int dist[100001];
vector<node> v[100001];
int c, p, k, a, b;
void djk(int a) {
	for (int i = 0; i <= p; i++) {
		dist[i] = 1e9;
		visited[i] = 0;
	}
	priority_queue<node> q;
	q.push({ a,0 });
	dist[a] = 0;
	//visited[a] = 1;
	while (!q.empty()) {
		node now = q.top(); q.pop();
		if (visited[now.to] == 1)continue;
		visited[now.to] = 1;
		for (int i = 0; i < v[now.to].size(); i++) {
			node next = v[now.to][i];
			//if (visited[next.to] == 1)continue;
			if (dist[now.to] + next.cost > dist[next.to])continue;
			dist[next.to] = dist[now.to] + next.cost;
			//visited[next.to] = 1;
			q.push({ next.to,dist[next.to] });
		}
	}
}
int main()
{
	cin >> c >> p >> k >> a >> b;
	for (int i = 0; i < c; i++) {
		int from,to,cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
		v[to].push_back({ from,cost });
	}
	djk(k);
	int ks = dist[a] + dist[b];
	djk(a);
	int as = dist[k] + dist[b];
	djk(b);
	int bs = dist[k] + dist[a];

	int mo = min(ks, as);
	int mt = min(mo, bs);
	cout << mt;

	return 0;
}
