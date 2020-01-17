//-------------------------------------------------
//--Lazy Evaluation Segment tree (Proportional)
//-------------------------------------------------
template<typename T, typename E>
class LazySegmentTree
{
private:
    using F = ::std::function<T(T,T)>;
    using G = ::std::function<T(T,E)>;
    using H = ::std::function<E(E,E)>;
    F f; G g; H h;
    int n, height;
    ::std::vector<T> seg;
    ::std::vector<E> lazy;
    T te; E ee;
public:
    LazySegmentTree(int _n, F f, G g, H h, T te, E ee)
        : f(f),g(g),h(h),te(te),ee(ee)
    {
        init(_n);
    }
    LazySegmentTree(::std::vector<T> &v, F f, G g, H h, T te, E ee)
        : f(f),g(g),h(h),te(te),ee(ee)
    {
        int _n = v.size();
        init(_n);
        for(int i=n; i<n+_n; i++) seg[i] = v[i-n];
        build();
    }
    void init(int _n){
        n = 1; height=0;
        while(n<_n) n<<=1, height++;
        seg.resize(2*n, te);
        lazy.resize(2*n, ee);
    }
    void build(){
        for(int i=n-1; i>0; i--) seg[i] = f(seg[i<<1], seg[i<<1|1]);
    }
    T eval(int k){
        int c = breadth(k);
        return (lazy[k]==ee) ? seg[k] : g(seg[k],quantify(lazy[k], c));
    }
    void waveto(int k){
        for(int i=height; i>0; i--) wave(k>>i);
    }
    void wave(int k){
        seg[k] = eval(k);
        lazy[k<<1] = h(lazy[k<<1],lazy[k]);
        lazy[k<<1|1] = h(lazy[k<<1|1],lazy[k]);
        lazy[k] = ee;
    }
    void recalc(int k){
        for(int i=1; i<=height; i++){
            int m = k>>i;
            seg[m] = f(eval(m<<1), eval(m<<1|1));
        }
    }
    void update(int a, int b, E x){
        if (b<=a) return;
        waveto(a+=n);
        waveto(b+=n-1);
        T L=ee, R=ee;
        int l=a, r=b;
        while(l<=r){
            if (l&1) lazy[l] = h(lazy[l], x), l++;
            if (!(r&1)) lazy[r] = h(lazy[r], x), r--;
            l>>=1; r>>=1;
        }
        recalc(a);
        recalc(b);
    }
    T query(int a, int b){
        waveto(a+=n);
        waveto(b+=n-1);
        T L=te, R=te;
        int l=a, r=b;
        while(l<=r){
            if (l&1) L = f(L, eval(l++));
            if (!(r&1)) R = f(eval(r--), R);
            l>>=1; r>>=1;
        }
        return f(L,R);
    }
    T operator[](int k){return query(k, k+1);};
    inline int breadth(int k){
        int ret = height-31+__builtin_clz(k);
        return 1<<ret;
    }
    //return value proportional to segment's width
    inline E quantify(E laz, int c){
        return laz*c;
    }
};
