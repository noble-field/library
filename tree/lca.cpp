//-------------------------------------------------
//--Lowest Common Ancestor (depends on Segment tree)
//-------------------------------------------------
class LCA
{
private:
    using Graph = ::std::vector<::std::vector<int> >;
    // using edge = ::std::pair<int,int>;
    // using Graph = ::std::vector<::std::vector<edge> >;
    using P = ::std::pair<int,int>;
    ::std::vector<P> euler;
    ::std::vector<int> fidx;
    int idx;
    SegmentTree<P> seg;
    void dfs(int v, int p, int d, Graph &adj){
        euler.emplace_back(d, v);
        fidx[v] = idx++;
        for(auto u:adj[v]){
            if (u==p) continue;
            dfs(u,v,d+1,adj);
            euler.emplace_back(d, v); idx++;
        }
        // for(auto e:adj[v]){
        //     int u,att;
        //     tie(u,att) = e;
        //     if (u==p) continue;
        //     dfs(u,v,d+1,adj);
        //     euler.emplace_back(d, v); idx++;
        // }
    }
public:
    LCA(int n, Graph &adj):fidx(n){
        idx = 0;
        dfs(0,-1,0,adj);
        seg = SegmentTree<P>(euler, [](P x, P y){return min(x,y);},make_pair(n,n));
    }
    int query(int u, int v){
        int fmin = min(fidx[u],fidx[v]);
        int fmax = max(fidx[u],fidx[v]);
        return seg.query(fmin,fmax+1).second;
    }
};
