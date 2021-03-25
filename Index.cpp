#include <bits/stdc++.h>

using namespace std;

int MX = 200000;

struct pseg {
	int cnt, nxt;
	vector<int> root, val, left, right;
	pseg(int n):cnt(0), nxt(0){
		root.assign(n * 20 + 100, 0);
		root[0] = nxt ++;
		cnt ++;
		left.assign(n * 20, 0);
		right.assign(n * 20, 0);
		val.assign(n * 20, 0);
	}
	int update(int x, int add, int l, int r, int id){
		if(x < l or x > r)return id;
		int ID = nxt ++;
		if(l == r){
			val[ID] = val[id] + add;
			return ID;
		}
		int mid = (l + r) / 2;
		left[ID] = update(x, add, l, mid, left[id]);
		right[ID] = update(x, add, mid + 1, r, right[id]);
		val[ID] = val[right[ID]] + val[left[ID]];
		return ID;
	}
	void update(int x, int add){
		root[cnt] = update(x, add, 1, MX, root[cnt - 1]);
		cnt ++;
	}
	int query(int l, int r, int lx, int rx, int id){
		if(rx < l or lx > r)return 0;
		if(lx >= l and rx <= r)return val[id];
		int mid = (lx + rx) / 2;
		return query(l, r, lx, mid, left[id]) + query(l, r, mid + 1, rx, right[id]);
	}
	int query(int ver, int l,int r){
		assert(ver < (int)root.size());
		return query(l, r, 1, MX, root[ver]);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	pseg sg(n);
	for(int i = 0;i < n;i ++) {
		cin >> a[i];
		sg.update(a[i], 1);
	}
	while(q --) {
		int l, r;
		cin >> l >> r;
		int lx = 2, rx = 200000;
		int ans = 1;
		auto check = [&](int x) {
			int val;
			if(l == 0) {
				val = sg.query(r, x, MX);
			} else {
				val = sg.query(r, x, MX) - sg.query(l - 1, x, MX);
			}
			return val >= x;
		};
		while(lx <= rx) {
			int g = lx + (rx - lx) / 2;
			if(check(g)) {
				ans = g;
				lx = g + 1;
			} else {
				rx = g - 1;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
