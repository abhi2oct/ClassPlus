#include<bits/stdc++.h>
using namespace std;

vector<int> adj[100001];
int vis[100001],in[100001],out[100001];
int hotspots[100001];
set<int> st;

void dfs1(int s)
{
	vis[s]=1;
	for(int i=0;i<adj[s].size();i++)
	{
		if(vis[adj[s][i]]==0)
		{
			dfs1(adj[s][i]);
			in[s]=max(in[s],in[adj[s][i]]+1);
		}
	}
}

void dfs2(int s)
{
	vis[s]=1;
	int mx1=-1000000,mx2=-1000000;
	for(int i=0;i<adj[s].size();i++)
	{
		if(vis[adj[s][i]]==0)
		{
			if(in[adj[s][i]]>=mx1)
			{
				mx2=mx1;
				mx1=in[adj[s][i]];
			}
			else if(in[adj[s][i]]>mx2)
			{
				mx2=in[adj[s][i]];
			}
		}
	}
	for(int i=0;i<adj[s].size();i++)
	{
		if(vis[adj[s][i]]==0)
		{
			int use=mx1;
			if(in[adj[s][i]]==mx1)
			use=mx2;
			out[adj[s][i]]=max(out[adj[s][i]],max(use+2,1+out[s]));
			dfs2(adj[s][i]);
		}
	}
	
}

int main()
{
	int n,h,x;
	cin>>n>>h>>x;
	int i;
	for(i=0;i<h;i++){
	cin>>hotspots[i];
	st.insert(hotspots[i]);
	}
	
	int u,v;
	for(i=0;i<n-1;i++)
	{
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	for(i=1;i<=n;i++)
	in[i]=-1000000,out[i]=-1000000;
	
	for(i=0;i<h;i++)
	{
		in[hotspots[i]]=0;
		out[hotspots[i]]=0;
	}
	dfs1(1);
	for(i=1;i<=n;i++)
	vis[i]=0;
	dfs2(1);
	
	int ans=0;
	for(i=1;i<=n;i++)
	{
		if(max(in[i],out[i])<=x&&max(in[i],out[i])>=0)
		ans++;
	}
	
	cout<<ans;
}

