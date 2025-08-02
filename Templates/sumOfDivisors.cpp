#include <bits/stdc++.h>
using namespace std;
 
#define endl '\n'
#define ll long long
 
const int N = 1e8;
bitset<N + 1> is_prime;
vector<int> primes;
 
void sieve() {
    is_prime.set(); // All true initially
    is_prime[0] = is_prime[1] = 0;
    for (ll i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= N; j += i)
                is_prime[j] = 0;
        }
    }
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i])
            primes.push_back(i);
    }
}
 
ll power(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
 
void solve() {
    ll n; cin >> n;
    ll f = n;
    ll out = 1;
    for (size_t i = 0; i < primes.size() && (ll)primes[i] * primes[i] <= n; ++i) {
        int p = primes[i];
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                cnt++;
            }
            out *= (power(p, cnt + 1) - 1) / (p - 1);
        }
    }
    if (n > 1) out *= (n + 1);
    cout << out - f << endl;  // proper divisors sum
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    sieve();
 
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
