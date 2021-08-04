# Tarjan算法求强连通分量

**By jpy_cpp 4th August,2021**

本文具体讲述Tarjan算法系列（强连通分量、割点等）。

## 强连通分量(SCC)

要说强连通分量，还要从强连通图说起。

强连通图是指一张有向图任意两结点都可互相到达。

而强连通分量的定义就是极大的强连通子图。

### DFS生成树

在介绍该算法之前，我们需要先介绍DFS生成树。
![DFS生成树](https://oi-wiki.org/graph/images/scc1.png)
有向图的DFS生成树由4种边组成：

1. 树边（绿）
2. 返祖边 （黄）
3. 横叉边（红）
4. 前向边（蓝）

### Tarjan求强连通分量

对于每一个结点$u$，维护一下几个变量：

+ $dfn[u]$：遍历时它的次序（时间戳）。
+ $low[u]$：以$u$为子树的$dfn$最小值。
+ $instack[u]$：$u$是否在栈中。

同时维护一栈$stack$用于储存结点。

从根开始的一条路径上的$dfn$严格递增，$low$严格不降。

对于$u$的儿子$v$：

1. $v$未被访问：继续对$v$进行$dfs$,$low[u]\leftarrow low[v]$
2. $v$被访问，在栈中：$low[u]\leftarrow dfn[v]$
3. $v$被访问，不在栈中：啥也不干。

将上述操作进行写成伪代码：

```
TARJAN_SEARCH(int u)
    vis[u]=true
    low[u]=dfn[u]=++dfncnt
    push u to the stack
    for each (u,v) then do
        if v hasn't been search then
            TARJAN_SEARCH(v) // 搜索
            low[u]=min(low[u],low[v]) // 回溯
        else if v has been in the stack then
            low[u]=min(low[u],dfn[v])
```

若$dfn[u]=low[u]$，则$u$在最近的$SCC$上，$pop\space stack$即可。

代码（附注释）：

```c++
#include<bits/stdc++.h>
#define N 10010
using namespace std;
int n,m,u,v;
int dfn[N],low[N];
bool instack[N];
vector<int> edge[N];
stack<int> stk;
int cnt=0,cnt_scc=0;
vector<int> scc[N];
void dfs(int x) {
    ++cnt;
    dfn[x]=low[x]=cnt; //初始化dfn,low
    stk.push(x); //进栈
    instack[x]=true;
    for(int i=0;i<edge[x].size();i++) {
        int to=edge[x][i];
        if(!dfn[to]) { //to未被访问过
            dfs(to);
            low[x]=min(low[x],low[to]);
        }
        else if(instack[to]) { //to被访问过且在栈中
            low[x]=min(low[x],dfn[to]);
        }
    }
    if(dfn[x]==low[x]) { //找出scc
        ++cnt_scc;
        int node;
        do
        {
            node=stk.top();
            stk.pop();
            instack[node]=false;
            scc[cnt_scc].push_back(node);
        } while (node!=x);
        
    }
}
bool cmp(vector<int> a,vector<int> b) {
    return a[0]<b[0];
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++) {
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
    }
    for(int i=1;i<=n;i++) {
        if(!dfn[i]) { //防止不连通
            dfs(i);
        }
    }
    //输出
    cout<<cnt_scc<<endl;
    for(int i=1;i<=cnt_scc;i++) {
        sort(scc[i].begin(),scc[i].end());
    }
    sort(scc+1,scc+1+cnt_scc,cmp);
    for(int i=1;i<=cnt_scc;i++) {
        for(int j=0;j<(int)scc[i].size();j++) {
            cout<<scc[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
```
