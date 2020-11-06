//-------------------------------------------------
//--Dual Segment tree
//-------------------------------------------------
template<typename T, typename E, T(*g)(T,E), E(*h)(E,E)>
class DualSegmentTree
{
private:
    int N,height;
    vector<T> seg;
    vector<E> lazy;
    const T te;
    const E ee;
public:
    DualSegmentTree(){}
    DualSegmentTree(int n, T te, E ee):te(te),ee(ee){
        init(n);
    }
    DualSegmentTree(vector<T> &v, T te, E ee):te(te),ee(ee){
        int n = v.size();
        init(n);
        for(int i=0; i<n; i++) seg[i] = v[i];
    }
    void init(int n){
        N=height=1;
        while(N<n) N<<=1, height++;
        seg.resize(N,te);
        lazy.resize(N,ee);
    }
    void lazy_apply(int k, E x){
        if (k<N) lazy[k] = h(lazy[k],x);
        else seg[k-N] = (x==ee)?seg[k-N]:g(seg[k-N],x);
    }
    void prop(int k){
        lazy_apply(k<<1,lazy[k]);
        lazy_apply(k<<1|1,lazy[k]);
        lazy[k]=ee;
    }
    void prop_to(int k){
        for(int i=height-1; i>0; i--) prop(k>>i);
    }
    void apply(int a, int b, E x){
        prop_to(a+=N);
        prop_to(b+=N);
        int l=a,r=b;
        while(l<r){
            if (l&1) lazy_apply(l++,x);
            if (r&1) lazy_apply(--r,x);
            l>>=1; r>>=1;
        }
    }
    T get(int k){
        prop_to(k+N);
        return seg[k];
    }
    void set(int k, T x){
        prop_to(k+N);
        seg[k] = x;
    }
    T operator[](int k){return get(k);}
};