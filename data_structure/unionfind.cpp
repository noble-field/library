//-------------------------------------------------
//--Union Find tree
//-------------------------------------------------
class UnionFind
{
private:
    vector<int> par;
    vector<int> rank;
    vector<int> sz;
public:
    UnionFind(int n):par(n),rank(n),sz(n){
        for(int i=0; i<n; i++){
            par[i] = i;
            rank[i] = 0;
            sz[i] = 1;
        }
    }
    int root(int x){
        if (par[x]==x) return x;
        return par[x] = root(par[x]);
    }
    bool same(int x, int y){
        return root(x)==root(y);
    }
    void unite(int x, int y){
        int rx = root(x);
        int ry = root(y);
        if (rx==ry) return;
        if (rank[rx]<rank[ry]){
            par[rx] = par[ry];
            sz[ry] += sz[rx];
        }else{
            par[ry] = par[rx];
            sz[rx] += sz[ry];
            if (rank[rx]==rank[ry]) rank[rx]++;
        }
    }
    int size(int x){
        return sz[root(x)];
    }
};
