#include <bits/stdc++.h>

using namespace std;

int ig;
map<string, int> id;
int find(string x) {
	if(id.find(x) == id.end()) {
		id[x] = ig ++;
	}
	return id[x];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<array<int, 2>> adj[n];
	for(int i = 0;i < m;i ++) {
		int t;
		string x, y;
		cin >> x >> y >> t;
		int X = find(x), Y = find(y);
		adj[X].push_back({Y, t});
	}
	vector<vector<long long>> level(n, vector<long long>(n, LONG_LONG_MAX));
	for(int i = 0;i < n;i ++) {
		priority_queue<array<long long, 2>, vector<array<long long, 2>>, greater<array<long long, 2>>> q;
		q.push({0, i});
		level[i][i] = 0;
		while((int)q.size()) {
			auto x = q.top();
			q.pop();
			for(auto e : adj[x[1]]) {
				if(level[i][e[0]] > level[i][x[1]] + e[1]) {
					level[i][e[0]] = level[i][x[1]] + e[1];
					q.push({level[i][e[0]], e[0]});
				}
			}
		}
	}
	int q;
	cin >> q;
	while(q --) {
		string x, y;
		cin >> x >> y;
		int X = find(x), Y = find(y);
		if(level[X][Y] == LONG_LONG_MAX) {
			cout << "Roger\n";
		} else {
			cout << level[X][Y] << '\n';
		}
	}
	return 0;
}
