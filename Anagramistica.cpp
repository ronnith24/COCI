#include <bits/stdc++.h>

using namespace std;

//#define RANDOM chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count()
//ll mult(ll a,ll b){return (a * b) % modF;}
//ll add(ll a,ll b){return (a + b) % modF;}
//ll sub(ll a,ll b){return (a - b + modF) % modF;}
//
//struct hassh{
//	ll h1,h2;
//	hassh():hassh(0,0){}
//	hassh(ll h,ll hh):h1(h),h2(hh){}
//	bool operator<(const hassh& b) const {
//		if(h1 == b.h1)return h2 < b.h2;
//		return h1 < b.h1;
//	}
//	bool operator==(const hassh& b) const {
//		if(h1 == b.h1 and h2 == b.h2) return true;
//		return false;
//	}
//};
//ll b1 = (RANDOM) % modF;
//ll b2 = (RANDOM) % modF;
//struct StringHash{
//	ll N;
//	vector<ll> pw1, pw2;vector<hassh> hsh;
//	StringHash(const string& s){
//		N = sz(s);
//		hsh.assign(N,hassh(0,0));pw1.assign(N + 1,1);pw2.assign(N + 1,1);
//		FOR(i,1,N + 1){
//			pw1[i] = mult(b1, pw1[i - 1]);
//			pw2[i] = mult(b2, pw2[i - 1]);
//		}
//		FOR(i,0,N){
//			if(i == 0){
//				hsh[i].h1 = s[i];hsh[i].h2 = s[i];
//			} else {
//				hsh[i].h1 = add(mult(hsh[i - 1].h1, b1), s[i]);hsh[i].h2 = add(mult(hsh[i - 1].h2, b2), s[i]);
//			}
//		}
//	}
//	hassh find_hash(ll l,ll r){
//		ll H1 = hsh[r].h1, H2 = hsh[r].h2;
//		if(l != 0){
//			H1 = sub(H1, mult(hsh[l - 1].h1, pw1[r - l + 1])), H2 = sub(H2, mult(hsh[l - 1].h2, pw2[r - l + 1]));
//		}
//		return hassh(H1,H2);
//	}
//};

const long long mod = (int)1e9 + 7;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	vector<int> val;
	map<vector<int>, int> an;
	for(int i = 0;i < n;i ++) {
		string x;
		cin >> x;
		vector<int> fr(26, 0);
		for(int j = 0;j < (int)x.size();j ++) {
			fr[x[j] - 'a'] ++;
		}
		an[fr] ++;
	}
	for(auto e : an) {
		val.push_back(e.second);
	}
	vector<vector<int>> c(2001, vector<int>(2001, 0));
	for(int i = 0;i < 2001;i ++) {
		for(int j = 0;j <= i;j ++) {
			if(i == 0 && j == 0) {
				c[i][j] = 1;
			} else {
				if(i != j) {
					c[i][j] = (c[i][j] + c[i - 1][j]) % mod;
				}
				if(j != 0) {
					c[i][j] = (c[i][j] + c[i - 1][j - 1]) % mod;
				}
			}
		}
	}
	int cnt = (int)val.size();
//	for(int i = 0;i < cnt;i ++) {
//		cerr << val[i] << ' ';
//	}
//	cerr << '\n';
	vector<vector<int>> dp(cnt, vector<int>(k + 1, 0));
	for(int i = 0;i < cnt;i ++) {
		for(int j = 0;j < k + 1;j ++) {
			for(int rep = 0;rep <= val[i];rep ++) {
				int value = (rep * (rep - 1)) / 2;
				if(value > j) {
					break;
				}
				if(i == 0) {
					dp[i][j] = (dp[i][j] + (j == value ? c[val[i]][rep] : 0)) % mod;
				} else {
					dp[i][j] = (dp[i][j] + ((long long)c[val[i]][rep] * ((dp[i - 1][j - value]) % mod)) % mod) % mod;
				}
			}
//			cerr << dp[i][j] << ' ';
		}
//		cerr << '\n';
	}
	cout << dp[cnt - 1][k] << '\n';
	return 0;
}
