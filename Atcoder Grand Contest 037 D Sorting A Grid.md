# Atcoder Grand Contest 037 D Sorting A Grid

[题目链接](https://atcoder.jp/contests/agc037/tasks/agc037_d)

## 题意

给定一个$n\times m$的矩阵，$1\to nm$每个数恰好出现一次，设第$i$行第$j$列的数为$a_{i,j}$。

你将需要进行3次操作：

1. 将$n$行中的每一行里的数字重新排列。
2. 将$m$列中的每一列里的数字重新排列。
3. 将$n$行中的每一行里的数字重新排列。

操作结束后，这个矩阵需要满足$\forall i,j,a_{i,j}=m(i-1)+j$，请给出第1、2次操作结束后的序列。（可以保证一定存在这样的操作）

## 输入和输出

输入：
$$
n\space m\\
\begin{matrix}
a_{1,1}&a_{1,2}&\cdots&a_{1,m}\\
a_{2,1}&a_{2,2}&\cdots&a_{2,m}\\
\cdots&\cdots&\cdots&\cdots\\
a_{n,1}&a_{n,2}&\cdots&a_{n,m}
\end{matrix}
$$
输出：
$$
\begin{matrix}
b_{1,1}&b_{1,2}&\cdots&b_{1,m}\\
b_{2,1}&b_{2,2}&\cdots&b_{2,m}\\
\cdots&\cdots&\cdots&\cdots\\
b_{n,1}&b_{n,2}&\cdots&b_{n,m}
\end{matrix}\\
\begin{matrix}
c_{1,1}&c_{1,2}&\cdots&c_{1,m}\\
c_{2,1}&c_{2,2}&\cdots&c_{2,m}\\
\cdots&\cdots&\cdots&\cdots\\
c_{n,1}&c_{n,2}&\cdots&c_{n,m}
\end{matrix}
$$

## 做法

### 法一

因为这道题数据范围比较小，所以可以考虑比较暴力的做法。

设$to_{i,j}$为$a_{i,j}$最后应该被换到的行的编号。

则有：$to_{i,j}=\left\lfloor\frac{a_{i,j}+m-1}{m}\right\rfloor$。

考虑到如果第1次操作之后存在$i_1$,$i_2$，使得：$to_{i_1,j}=to_{i_2,j}$。因为第2次操作不改变元素所在的列，所以第2次操作之后依然存在$i_1,i_2$，使得：$to_{i_1,j}=to_{i_2,j}$。但第三次操作不能改变列的编号了，所以存在两个应该在同一行的不同元素被分在了同一列。显然，这不满足题目要求，所以我们要使得第一次操作之后不存在$to_{i_1,j}=to_{i_2,j}$。即：在第一次操作之后，每一列的$to$值都应该是一个$1\to n$的排列。

将题目转化以后，我们可以把开始时不同$to$值的元素分开考虑。对于开始时在$to$值相同且在同一列的元素，我们要通过把他们和其他的元素交换使得他们不在同一行（重新排列$\Leftrightarrow$不限次数的交换）。

自然地，我们记$cnt_{j,i}$表示当前在第$j$列，最后要到第$i$行的元素的个数。

若$cnt_{j,i}\ge 2$，则必须要将其中的$cnt_{j,i}-1$个交换的别的列里，不妨设$j\leftrightarrow j+1$，剩下暴力模拟即可，时间复杂度$O(n^2m^2)$。

代码如下：

[法一AC代码](https://atcoder.jp/contests/agc037/submissions/24626040)

```c++
#include<bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define REP(i,n) for(int i=1;i<=n;i++)
#define forn(i,a,b) for(int i=a;i<=b;i++)
#define N 110
using namespace std;
inline int readint() {
    char ch=getchar();
    int x=0;
    bool flag=true;
    while(!isdigit(ch)) {
        if(ch=='-') flag=false;
        ch=getchar();
    }
    while(isdigit(ch)) {
        x=x*10+ch-'0';
        ch=getchar();
    }
    if(flag) return x;
    else return -x;
}
int n,m,a[N][N],b[N][N],c[N][N],cnt[N][N];
int main() {
    n=readint(),m=readint();
    REP(i,n) {
        REP(j,m) {
            a[i][j]=readint();
        }
    }
    //the first step
    memset(cnt,0,sizeof(cnt));
    REP(i,n) {
        REP(j,m) {
            b[i][j]=a[i][j];
            cnt[j][(b[i][j]+m-1)/m]++;
        }
    }
    rep(t,n*m) {
        forn(j,1,m-1) {
            REP(i,n) {
                if(cnt[j][(b[i][j]+m-1)/m]>1) {
                    cnt[j][(b[i][j]+m-1)/m]--;
                    cnt[j+1][(b[i][j]+m-1)/m]++;
                    cnt[j][(b[i][j+1]+m-1)/m]++;
                    cnt[j+1][(b[i][j+1]+m-1)/m]--;
                    swap(b[i][j],b[i][j+1]);
                }
            }
        }
    }
    REP(i,n) {
        REP(j,m) {
            cout<<b[i][j]<<' ';
        }
        cout<<endl;
    }
    //the second step
    REP(i,n) {
        REP(j,m) {
            c[(b[i][j]+m-1)/m][j]=b[i][j];
        }
    }
    REP(i,n) {
        REP(j,m) {
            cout<<c[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
```

## 法二

对每一个$a_{i,j}$根据行的编号染色，记函数$color(x)=\left\lfloor\frac{x-1}{m}\right\rfloor+1$。

分析与上一种方法类似。要补充的是，可以将$i$和$color_{i,j}$连边，然后跑一下$dfs$即可。

代码如下：

[法二AC代码](https://atcoder.jp/contests/agc037/submissions/24725530)

```c++
#include<bits/stdc++.h>
#define sz(x) (int)((x).size())
#define N 110
using namespace std;
int n,m,a[N][N],b[N][N],c[N][N],from[N],to[N];
vector<int> g[N];
bool stk[N],vis[N][N];
int color(int x) {
	return (x-1)/m+1;
}
bool match(int x) {
	stk[x]=true;
	for(int i=0;i<sz(g[x]);i++) {
		int y=g[x][i];
		if(!from[y]||(!stk[from[y]]&&match(from[y]))) {
			to[x]=y;
			from[y]=x;
			return true;
		}
	}
	return false;
}
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin>>a[i][j];
		}
	}
	for(int col=1;col<=m;col++) {
		for(int i=1;i<=n;i++) {
			from[i]=to[i]=0;
			g[i].clear();
		}
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				if(!vis[i][j]) {
					g[i].push_back(color(a[i][j]));
				}
			}
		}
		for(int i=1;i<=n;i++) {
			memset(stk,0,sizeof(stk));
			match(i);
		}
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				if(!vis[i][j]&&color(a[i][j])==to[i]) {
					b[i][col]=a[i][j];
					vis[i][j]=true;
					break; 
				}
			}
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			c[color(b[i][j])][j]=b[i][j];
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

## 法三

与法二类似，用$dinic$算法跑二分图匹配。

证明（HALL定理）：

[度娘解释](https://baike.baidu.com/item/Hall%E5%AE%9A%E7%90%86/5111749)

HALL定理是用来判定二分图是否存在完美匹配的定理。

完美匹配：是指最大匹配数为$\min(|x|,|y|)$，也就是$X$或$Y$集合其中一个集合所有点都被匹配了。

存在完美匹配的充分必要条件是对于任意一个$X$的子集(subset)，设大小为$k$，那么和这个子集相连的$Y$必须不小于k个。

证明：

+ 必要性证明

  反证。假设一个二分图$G$存在完美匹配且不满足HALL定理。

  对于某$k$个点，它们连向的不足$k$个点，根据抽屉原理，显然不能匹配，矛盾！

  所以必要性正确。

+ 充分性证明

  反证。假设一个二分图$G$不存在完美匹配且满足HALL定理，必然可以找到至少一个未匹配的点。

  因为$G$满足HALL定理，所以这个点一定连向了至少一个点。

  若这个点不在最大匹配中，必然不匹配，矛盾。

  所以这个点必然在最大匹配中，所以必然存在一个点与之匹配。

  此时，可以找到一条增广路，矛盾！

综上，证明了HALL定理的正确性。

[法三AC代码](https://atcoder.jp/contests/agc037/submissions/24727404)

```c++
#include<bits/stdc++.h>
#define maxn 210
using namespace std;
int n,m,N,np,d[maxn],q[maxn],tp,b[maxn][maxn];
bool vis[maxn][maxn];
stack<int> a[maxn][maxn];
bool bfs() {
	memset(d,0,sizeof(d));
	q[0]=N;
	d[q[0]]=1;
	tp=1;
	for(int i=0; i<tp; i++) {
		int x=q[i];
		for(int j=0; j<=np; j++) {
			if(vis[x][j] && !d[j]) {
				q[tp]=j;
				d[q[tp]]=d[x]+1;
				tp++;
			}
		}
	}
	return d[np];
}
bool dfs(int x,int y) {
	if(x==np) {
		return y;
	}
	bool f1=false,f2=false;
	for(int i=0; i<=np; i++) {
		if(y && vis[x][i] && d[i]==d[x]+1) {
			f1=dfs(i,1);
			f2|=f1;
			y-=f1;
			vis[x][i]^=f1;
			vis[i][x]^=f1;
		}
	}
	return f2;
}
int main() {
	cin>>n>>m;
	N=n*2;
	np=N+1;
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			int x;
			cin>>x;
			a[i][(x-1)/m].push(x);
		}
	}
	for(int i=0; i<m; i++) {
		memset(vis,0,sizeof(vis));
		for(int j=0; j<n; j++) {
			vis[N][j]=true;
			vis[n+j][np]=true;
			for(int k=0; k<n; k++) {
				vis[j][n+k]=a[j][k].size();
			}
		}
		for(; bfs(); dfs(N,210));
		for(int j=0; j<n; j++) {
			for(int k=0; k<n; k++) {
				if(vis[k+n][j]) {
					b[i][j]=a[j][k].top();
					a[j][k].pop();
				}
			}
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			cout<<b[j][i]<<' ';
		}
		cout<<endl;
	}
	for(int i=0; i<m; i++) {
		sort(b[i],b[i]+n);
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			cout<<b[j][i]<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```

学习资料：

[HALL定理证明](https://blog.csdn.net/werkeytom_ftd/article/details/65658944)

[orz顾万钧](https://blog.csdn.net/qq_42925924/article/details/105148723?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162787496116780357261917%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162787496116780357261917&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-4-105148723.first_rank_v2_pc_rank_v29&utm_term=agc037d&spm=1018.2226.3001.4187)

[这道题讲的比较清楚](https://blog.csdn.net/jokerwyt/article/details/102725307?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162787366316780271596956%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=162787366316780271596956&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v29-1-102725307.first_rank_v2_pc_rank_v29&utm_term=agc037d+Sorting+a+Grid&spm=1018.2226.3001.4187)

[oi-wiki系统性讲解最大流](https://oi-wiki.org/graph/flow/max-flow/)

[一道模板题](https://www.luogu.com.cn/problem/P3376)

[双倍经验~~（危）~~](https://www.luogu.com.cn/problem/P2740)

[加强版](https://www.luogu.com.cn/problem/P4722)
