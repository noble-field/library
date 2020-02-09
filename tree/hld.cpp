//-------------------------------------------------
//--Heavy Light Decomposition
//-------------------------------------------------
class HLD
{
private:
    using Graph = ::std::vector<::std::vector<int> >;
    int n;
    Graph g;
    ::std::vector<int> par, weight, depth;
    ::std::vector<int> head;
    ::std::vector<int> next;
    ::std::vector<int> chain, at;
    ::std::vector<::std::vector<int> > chains;
    void init(){
        par.resize(n);
        weight.resize(n);
        depth.resize(n);
        next.resize(n);
        chain.resize(n);
        at.resize(n);
        head.resize(n);
    }
    void dfs(Graph &g_){
        par[0] = -1;
        depth[0] = 0;
        using P = ::std::pair<int,int>;
        ::std::stack<P> st;
        st.emplace(0,0);
        while(!st.empty()){
            int v = st.top().first;
            int &idx = st.top().second;
            if (idx < g_[v].size()){
                int u = g_[v][idx++];
                if (u==par[v]) continue;
                par[u] = v;
                depth[u] = depth[v]+1;
                st.emplace(u,0);
            }else{
                st.pop();
                int heavy = 0;
                weight[v] = 1;
                for(auto u:g_[v]){
                    if (u==par[v]) continue;
                    weight[v]+=weight[u];
                    if (weight[u]>heavy){
                        heavy = weight[u];
                        next[v] = u;
                    }
                }
            }
        }
    }
    void bfs(Graph &g_){
        int idx=0;
        using P = ::std::pair<int,int>;
        ::std::queue<P> que;
        que.emplace(0,idx++);
        chains.push_back(::std::vector<int>());
        while(!que.empty()){
            int v,c;
            tie(v,c) = que.front(); que.pop();
            chain[v] = c;
            at[v] = chains[c].size();
            chains[c].push_back(v);
            head[v] = chains[c].front();
            for(auto u:g_[v]){
                if (u==par[v]) continue;
                if (u==next[v]){
                    que.emplace(u,c);
                }else{
                    que.emplace(u,idx++);
                    chains.push_back(::std::vector<int>());
                }
            }
        }
    }
    int climb(int v){return par[head[v]];};
public:
    HLD(Graph &g_):n(g_.size()){
        init();
        build(g_);
    }
    HLD(int n_):n(n),g(n){init();}
    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void build(){
        dfs(g);
        bfs(g);
    }
    void build(Graph &g_){
        dfs(g_);
        bfs(g_);
    }
    int lca(int u, int v){
        while(head[u]!=head[v]){
            if (depth[head[u]] > depth[head[v]]){
                u = climb(u);
            }else{
                v = climb(v);
            }
        }
        return (depth[u]<depth[v])?u:v;
    }
};
