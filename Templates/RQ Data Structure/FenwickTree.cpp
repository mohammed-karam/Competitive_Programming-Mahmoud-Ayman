struct FenwickTree{
    vector<ll>bit;int sz;
    FenwickTree(int n)
    {
        sz=n+1;
        bit=vector<ll>(sz);
    }
    void update(int idx,ll val)
    {
        while(idx<sz)
        {
            bit[idx]+=val;
            idx+=idx&-idx;
        }
    }
    ll query(int idx)
    {
        ll ret=0;
        while(idx>0)
        {
            ret+=bit[idx];
            idx-=idx&-idx;
        }
        return ret;
    }
    ll prefix(int l,int r)
    {
        return query(r)-query(l-1);
    }
};



void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    FenwickTree ft = FenwickTree(n);
    for (int i = 0; i < n; i++) {
        ft.update(i + 1, a[i]); // ✅ BIT is 1-indexed
    }
}
