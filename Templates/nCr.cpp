#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;

ll fact[N], invFact[N];

// Modular exponentiation
ll power(ll a, ll b, ll m = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and their inverses
void init() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        invFact[i] = power(fact[i], MOD - 2);
    }
}

// Compute nCr % MOD
ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}
