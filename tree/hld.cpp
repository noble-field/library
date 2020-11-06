//-------------------------------------------------
//--Heavy Light Decomposition
//-------------------------------------------------
class HLD
{
private:
    using Tree = vector<vector<int> >;
    using P = pair<int,int>;
    Tree G;
    vector<int> dep,sz,par,head;
    vector<int> in,out;
    void init(int n){
        sz.resize(n,1);
        par.resize(n);
        head.resize(n);
        in.resize(n);
        out.resize(n);
    }
    void dfs_sz(){
        stack<P> st;
        st.emplace(0,0);
        while(!st.empty()){
            int v = st.top().first;
            int &idx = st.top().second;
            if (idx < G[v].size()){
                int u = G[v][idx++];
                if (u==par[v]) continue;
                par[u] = v;
                st.emplace(u,0);
            }else{
                st.pop();
                for(auto &u:G[v]){
                    sz[v]+=sz[u];
                    if (sz[u] > sz[G[v][0]]){
                        swap(u,G[v][0]);
                    }
                }
            }
        }
    }
    void dfs_hld(){
        int t=0;
        stack<P> st;
        in[0] = t++;
        st.emplace(0,0);
        while(!st.empty()){
            int v = st.top().first;
            int &idx = st.top().second;
            if (idx < G[v].size()){
                int u = G[v][idx++];
                if (u==par[v]) continue;
                in[u] = t++;
                head[u] = (u == G[v][0] ? head[v] : u);
                st.emplace(u,0);
            }else{
                st.pop();
                out[v] = t;
            }
        }
    }
public:
    HLD(int n):G(n){init(n);}
    HLD(const Tree &g){
        G = g;
        init(G.size());
        build();
    }
    void add_edge(int a, int b){
        G[a].pb(b);
        G[b].pb(a);
    }
    void build(){
        dfs_sz();
        dfs_hld();
    }
    inline int operator[](int v){return in[v];};
};