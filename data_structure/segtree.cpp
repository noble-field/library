//-------------------------------------------------
//--Segment tree
//-------------------------------------------------
template<typename T>
class SegmentTree
{
private:
    using F = function<T(T,T)>;
    ::std::vector<T> btree;
    F f, _update;
    T e;
    int n;
public:
    SegmentTree(int _n, F f, T e, F g=[](T a,T b){return b;})
         : f(f),e(e),_update(g)
    {
        init(_n);
    }
    SegmentTree(const ::std::vector<T> &v, F f, T e, F g=[](T a,T b){return b;})
         : f(f),e(e),_update(g)
    {
        int _n = v.size();
        init(_n);
        for(int i=0; i<_n; i++) btree[i+n-1] = v[i];
        build();
    }
    void init(int _n){
        n = 1;
        while(_n>n) n<<=1;
        btree.resize(2*n-1, e);
    }
    void build(){
        for(int i=n-2; i>=0; i--) btree[i] = f(btree[2*i+1], btree[2*i+2]);
    }
    void update(int k, T a){
        k += n-1;
        btree[k] = _update(btree[k], a);
        while(k>0){
            --k>>=1;
            btree[k] = f(btree[2*k+1], btree[2*k+2]);
        }
    }
    T query(int a, int b){
        T L=e, R=e;
        a+=n-1; b+=n-1;
        while(a<b){
            if (!(a & 1)) L=f(L, btree[a++]);
            if (!(b & 1)) R=f(btree[--b], R);
            a>>=1; b>>=1;
        }
        return f(L, R);
    }
    T operator[](int k){return btree[k+n-1];}
};
