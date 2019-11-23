//-------------------------------------------------
//--Union Find tree
//-------------------------------------------------
class UnionFind
{
private:
    ::std::vector<int> par;
    ::std::vector<int> rank;
public:
    UnionFind(int n):par(n), rank(n){
        for(int i=0; i<n; i++){
            par[i] = i;
            rank[i] = 0;
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
        if (rank[rx]>rank[ry]){
            par[ry] = rx;
        }else{
            par[rx] = ry;
            if (rx==ry) rank[ry]++;
        }
    }
};
