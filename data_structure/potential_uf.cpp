//-------------------------------------------------
//--Union Find tree with potential
//-------------------------------------------------
template<typename T>
class pUnionFind
{
private:
    ::std::vector<int> par;
    ::std::vector<int> rank;
    ::std::vector<T> diff;
public:
    pUnionFind(int n):par(n), rank(n), diff(n){
        for(int i=0; i<n; i++){
            par[i] = i;
            rank[i] = 0;
            diff[i] = 0;
        }
    }
    int root(int x){
        if (par[x]==x) return x;
        int rx = root(par[x]);
        diff[x] += diff[par[x]];
        return par[x] = rx;
    }
    T weight(int x){
        root(x);
        return diff[x];
    }
    T climb(int x, int y){
        return weight(y)-weight(x);
    }
    bool same(int x, int y){
        return root(x)==root(y);
    }
    void unite(int x, int y, T w){
        int rx = root(x);
        int ry = root(y);
        if (rx==ry) return;
        w += weight(x)-weight(y);
        if (rank[rx]>rank[ry]){
            diff[ry] = w;
            par[ry] = rx;
        }else{
            diff[rx] = -w;
            par[rx] = ry;
            if (rx==ry) rank[ry]++;
        }
    }
};
