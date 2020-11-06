//-------------------------------------------------
//--Strongly Connected Components
//-------------------------------------------------
class SCC
{
private:
    using SCCGraph = vector<vector<int> >;
    int N,sz;
    SCCGraph G, rG;
    stack<int> st;
    vector<bool> seen;
    vector<int> belong;
    
    void dfs(int v){
        seen[v] = true;
        for(auto u:G[v]){
            if (seen[u]) continue;
            dfs(u);
        }
        st.push(v);
    }
    void rdfs(int v, int k){
        seen[v] = true;
        belong[v] = k;
        for(auto u:rG[v]){
            if (seen[u]) continue;
            rdfs(u,k);
        }
    }
public:
    SCC(int n):N(n),G(n),rG(n),seen(n),belong(n){}
    void add_edge(int u, int v){
        G[u].push_back(v);
        rG[v].push_back(u);
    }
    void build(){
        for(int v=0; v<N; v++) seen[v]=0;
        for(int v=0; v<N; v++)
            if (!seen[v]) dfs(v);
        for(int v=0; v<N; v++) seen[v]=0;
        sz=0;
        while(!st.empty()){
            int v = st.top(); st.pop();
            if (!seen[v]) rdfs(v,sz++);
        }
    }
    vector<vector<int> > get_list(){
        vector<vector<int> > ret(sz);
        for(int v=0; v<N; v++)
            ret[belong[v]].push_back(v);
        return ret;
    }
    int size(){return sz;};
    int operator[](int v){return belong[v];}
};