#include <bits/stdc++.h>
#define sz(x) (int)(x.size())
using namespace std;
const int mod=1e9+7,Base=233,inf=0x3f3f3f3f;
const long long INF=0x3f3f3f3f3f3f3f3f;
template<typename T>inline void chmax(T &a, T b){a=max(a,b);}
template<typename T>inline void chmin(T &a, T b){a=min(a,b);}
inline void trans(int &a,int b){a+=b;if(a>mod)a-=mod;}
const int maxn=1e6+5;
int n,q[maxn],head=1,tail=1;
long long x[maxn],p[maxn],c[maxn],sum[maxn],sump[maxn],dp[maxn];
long long X(int x)
{
	return sump[x];
}
long long Y(int x)
{
	return dp[x]+sum[x];
}
double slope(int x,int y)
{
	return (double)(Y(y)-Y(x))/(double)(X(y)-X(x));
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",x+i,p+i,c+i);
		sum[i]=sum[i-1]+x[i]*p[i];
		sump[i]=sump[i-1]+p[i];
	}
	for(int i=1;i<=n;i++)
	{
		while(head<tail&&slope(q[head],q[head+1])<x[i])
			head++;
		dp[i]=dp[q[head]]+x[i]*(sump[i]-sump[q[head]])-sum[i]+sum[q[head]]+c[i];
		while(head<tail&&slope(q[tail-1],i)<slope(q[tail-1],q[tail]))
			tail--;
		q[++tail]=i;
	}
	long long ans=dp[n];
	for(int i=n;i>=1;i--)
	{
		if(p[i])
			break;
		chmin(ans,dp[i-1]);
	}
	cout<<ans<<"\n";
    return 0;
}
