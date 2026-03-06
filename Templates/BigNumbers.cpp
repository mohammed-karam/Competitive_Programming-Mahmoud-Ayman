#include<bits/stdc++.h>

using namespace std;
#define mohamed_karam ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); files();
#define ll long long
#define endl '\n'

void files() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
}

const int MOD = 1e9 + 7, N = 1e6 + 5;

const int base = 1e9;
#define EL printf("\n")
#define pb push_back
#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)
typedef vector<int> BigInt;

void Set(BigInt &a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

void Print(BigInt a) {
    Set(a);
    printf("%d", (a.size() == 0) ? 0 : a.back());
    FORD(i,a.size()-2,0) printf("%09d", a[i]); EL;
}

BigInt Integer(string s) {
    BigInt ans;
    if (s[0] == '-') return ans;
    if (s.size() == 0) {ans.pb(0); return ans;}
    while (s.size()%9 != 0) s = '0'+s;
    for (int i=0;i<s.size();i+=9) {
        int v = 0;
        for (int j=i;j<i+9;j++) v = v*10+(s[j]-'0');
        ans.insert(ans.begin(),v);
    }
    Set(ans);
    return ans;
}

BigInt Integer(char c[]) {
    string s = "";
    FOR(i,0,strlen(c)-1) s = s + c[i];
    return Integer(s);
}

BigInt Integer(ll x) {
    string s = "";
    while (x > 0) s = char(x%10+'0') + s, x /= 10;
    return Integer(s);
}

BigInt Integer(int x) {
    return Integer((ll) x);
}

void operator >> (istream &in, BigInt &a) {
    string s;
    getline(cin, s);
    a = Integer(s);
}

void operator << (ostream &out, BigInt a) {
    Print(a);
}

bool operator < (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    if (a.size() != b.size()) return (a.size() < b.size());
    FORD(i,a.size()-1,0)
        if (a[i] != b[i]) return (a[i] < b[i]);
    return false;
}

bool operator > (BigInt a, BigInt b) {
    return (b < a);
}

bool operator == (BigInt a, BigInt b) {
    return (!(a < b) && !(b < a));
}

bool operator <= (BigInt a, BigInt b) {
    return (a < b || a == b);
}

bool operator >= (BigInt a, BigInt b) {
    return (b < a || b == a);
}

bool operator < (BigInt a, int b) {
    return (a < Integer(b));
}

bool operator > (BigInt a, int b) {
    return (a > Integer(b));
}

bool operator == (BigInt a, int b) {
    return (a == Integer(b));
}

bool operator >= (BigInt a, int b) {
    return (a >= Integer(b));
}

bool operator <= (BigInt a, int b) {
    return (a <= Integer(b));
}

BigInt max(BigInt a, BigInt b) {
    if (a > b) return a;
    return b;
}

BigInt min(BigInt a, BigInt b) {
    if (a < b) return a;
    return b;
}

BigInt operator + (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans;
    int carry = 0;
    FOR(i,0,max(a.size(), b.size())-1) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        ans.pb(carry%base);
        carry /= base;
    }
    if (carry) ans.pb(carry);
    Set(ans);
    return ans;
}

BigInt operator + (BigInt a, int b) {
    return a + Integer(b);
}

BigInt operator ++ (BigInt &a) { // ++a
    a = a + 1;
    return a;
}

void operator += (BigInt &a, BigInt b) {
    a = a + b;
}

void operator += (BigInt &a, int b) {
    a = a + b;
}


BigInt operator * (BigInt a, BigInt b) {
    Set(a);
    Set(b);
    BigInt ans(a.size() + b.size(), 0);

    for (int i = 0; i < a.size(); i++) {
        long long carry = 0;
        for (int j = 0; j < b.size() || carry; j++) {
            long long cur = ans[i+j] + carry;
            if (j < b.size()) cur += 1LL * a[i] * b[j];
            ans[i+j] = cur % base;
            carry = cur / base;
        }
    }

    Set(ans);
    return ans;
}

vector<BigInt> pre(2001);

void solve() {
    int n;
    cin >> n;

    vector<int> sells (20001 , -1);
    vector<vector<int>> wins (20001 , vector<int>());

    vector<int> needs;
    for (int i = 0; i < n; i++) {
        string action;
        int x;
        cin >> action >> x;
        if (action == "sell") {
            sells[x] = i;
        }else {
            wins[x].push_back(i);
        }
    }

    for (int x = 2000; x >= 0 ; x--) {
        if (sells[x] != -1 && !wins[x].empty() && sells[x] > wins[x].front()) {
            needs.push_back(x);
        }
    }

    vector<int> bad(n+1 , 0) , t;
    vector<pair<int,int>> ranges;

    for (auto d : needs) {
        int en = sells[d] , st = -1;
        for (int k : wins[d]) {
            if (k > en) {
                break;
            }
            st = k;
        }
        if (st != -1) {
            ranges.emplace_back(st , en);
            t.push_back(d);
        }
    }



    BigInt an = Integer(0);
    for (int d = 0 ; d < ranges.size() ; d++) {
        bool b = false;
        for (int i = ranges[d].first; i <= ranges[d].second; i++ ) {
            if (bad[i]) {
                b = true;
                break;
            }
        }

        if (!b) {an += pre[t[d]];
            for (int i = ranges[d].first; i <= ranges[d].second; i++ ) {
            bad[i] = true;

        }}


    }

    cout << an;

}


void prex() {
    pre[0] = Integer(1);

    for (int i = 1; i <= 2000; i++) {
        pre[i] = pre[i-1] * Integer(2);
    }
}

int main() {
    // إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا
    mohamed_karam;
    int t = 1;
    prex();
    // cin >> t;
    while (t--) solve();
    return 0;
}
