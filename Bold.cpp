#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n , m;
	cin >> n >> m;
	vector<vector<char>> a(n, vector<char>(m));
	vector<vector<char>> ans(n, vector<char>(m, '.'));
	for(int i = 0;i < n;i ++) {
		for(int j = 0;j < m;j ++) {
			cin >> a[i][j];
			if(a[i][j] == '#') {
				ans[i][j] = '#';
				ans[i + 1][j] = '#';
				ans[i][j + 1] = '#';
				ans[i + 1][j + 1] = '#';
			}
		}
	}
	for(int i = 0;i < n;i ++) {
		for(int j = 0;j < m;j ++) {
			cout << ans[i][j];
		}
		cout << '\n';
	}
	return 0;
}
