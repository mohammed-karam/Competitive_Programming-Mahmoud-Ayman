const int N=1e5+5;
struct KMP{
    int longestPrefix[N]={};vector<int>ans;
    void calcPrefix(string patern)
    {
        int n=patern.size();
        for(int i=1,idx=0;i<n;i++)
        {
            while(idx>0&&patern[idx]!=patern[i])idx=longestPrefix[idx-1];
            if(patern[i]==patern[idx])idx++;
            longestPrefix[i]=idx;
        }
    }
    void kmp(string s,string pat)
    {
        int n=s.size(),m=pat.size();
        calcPrefix(pat);
        for(int i=0,idx=0;i<n;i++)
        {
            while(idx>0&&s[i]!=pat[idx])idx=longestPrefix[idx-1];
            if(s[i]==pat[idx])idx++;
            if(idx==m)ans.push_back(i-m+1),idx=longestPrefix[idx-1];
        }
    }
};

    
🔧 Example: Pattern = "ababc"
We want to compute longestPrefix[] for this pattern.

Let's compute it step by step:

i	P[0..i]	    Proper prefixes	        Proper suffixes	                LPS (prefix = suffix)?	longestPrefix[i]
0	a	        -	                        -	                        -	                            0
1	ab	        a	                        b	                        no	                            0
2	aba	        a, ab	                    a, ba	                    a == a	                        1
3	abab	    a, ab, aba                	b, ab, bab	                ab == ab	                    2
4	ababc	    a, ab, aba, abab	        c, bc, abc, bbc            	no	                            0

longestPrefix = [0, 0, 1, 2, 0]
