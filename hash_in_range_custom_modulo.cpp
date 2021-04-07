struct Hash{
	int P, mod;
	int n;
	vector<int> a, pw;
	Hash(string &s, int PP, int mmod){
		P = PP, mod = mmod;
		n = s.size();
		a.resize(n,0);
		pw.resize(n+1,1);
		for(int i=1;i<=n;i++)pw[i] = (long long)pw[i-1]*P%mod;
		a[0] = s[0]-'A'+1;
		for(int i=1;i<n;i++){
			a[i] = ((long long)a[i-1]*P + (s[i]-'A'+1))%mod;
		}
	}
	int get(int l, int r){
		if(l == 0)return a[r];
		return ((a[r] - ((long long)a[l-1]*pw[r-l+1])%mod)%mod+mod)%mod;
	}
};
