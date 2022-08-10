#include <bits/stdc++.h>
#define sz(x) (int)(x.size())
using namespace std;
const int mod=1e9+7,Base=233,inf=0x3f3f3f3f;
const long long INF=0x3f3f3f3f3f3f3f3f;
template<typename T>inline void chmax(T &a, T b){a=max(a,b);}
template<typename T>inline void chmin(T &a, T b){a=min(a,b);}
inline void trans(int &a,int b){a+=b;if(a>mod)a-=mod;}
const int maxn=3000+5;
int n,m;
long long a[maxn],presum[maxn],f[maxn],g[maxn],q[maxn],head,tail;
long long X(int x)
{
	return presum[x];
}
long long Y(int x)
{
	return g[x]+presum[x]*presum[x];
}
double slope(int x,int y)
{
	return (double)(Y(y)-Y(x))/(double)(X(y)-X(x));
}
int main()
{
//    #ifndef _DEBUG
//		freopen("a.in","r",stdin);
//		freopen("a.out","w",stdout);
//    #endif
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    	presum[i]=presum[i-1]+a[i];
    	g[i]=presum[i]*presum[i];
	}
    for(int i=1;i<m;i++)
	{
		head=1,tail=1;
		q[1]=i;
		for(int j=i+1;j<=n;j++)
		{
			while(head<tail&&slope(q[head],q[head+1])<2.0*X(j))
				head++;
			f[j]=g[q[head]]+(presum[j]-presum[q[head]])*(presum[j]-presum[q[head]]);
			while(head<tail&&slope(q[tail-1],j)<slope(q[tail-1],q[tail]))
				tail--;
			q[++tail]=j;
		}
		for(int j=1;j<=n;j++)
			g[j]=f[j];
	}
	cout<<-presum[n]*presum[n]+m*f[n]<<"\n";
    return 0;
}
