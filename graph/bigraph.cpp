//-------------------------------------------------
//--Bipartite Graph Judge
//-------------------------------------------------
namespace BiGraph {
    template<class E>
    int dfs(int v, int c, Graph<E> &G, vector<int> &color)
    {
        int ret=(c==0);
        color[v]=c;
        for(auto e:G[v]){
            if (color[e.to]!=-1){
                if (color[e.to]==c) return -1;
                continue;
            }
            int val = dfs(e.to,1-c,G);
            if (val==-1) return -1;
            ret+=val;
        }
        return ret;
    }
}
