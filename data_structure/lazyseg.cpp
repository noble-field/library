//-------------------------------------------------
//--Lazy Evaluation Segment tree
//-------------------------------------------------
template<typename T, typename E, T(*f)(T,T), T(*g)(T,E), E(*h)(E,E)>
class LazySegmentTree
{
private:
    int n,N,height;
    vector<T> seg;
    vector<E> lazy;
    const T te;
    const E ee;
public:
    LazySegmentTree(){}
    LazySegmentTree(int n, T te, E ee):n(n),te(te),ee(ee){
        init();
    }
    LazySegmentTree(vector<T> &v, T te, E ee):n(v.size()),te(te),ee(ee){
        init();
        for(int i=0; i<n; i++)
            seg[i+N] = v[i];
        build();
    }
    void init(){
        N=height=1;
        while(N<n) N<<=1, height++;
        seg.resize(2*N,te);
        lazy.resize(2*N,ee);
    }
    void build(){
        for(int i=N-1; i>=1; i--) 
            seg[i]=f(seg[i<<1],seg[i<<1|1]);
    }
    T eval(int k){
        return (lazy[k]==ee)?seg[k]:g(seg[k],lazy[k]);
    }
    void prop(int k){
        if (k<N){
            lazy[k<<1] = h(lazy[k<<1],lazy[k]);
            lazy[k<<1|1] = h(lazy[k<<1|1],lazy[k]);
        }
        seg[k] = eval(k);
        lazy[k]=ee;
    }
    void prop_to(int k){
        if (k>=2*N) return;
        for(int i=height-1; i>=0; i--) prop(k>>i);
    }
    void recalc(int k){
        if (k>=2*N) return;
        for(int i=1; i<height; i++){
            int m = k>>i;
            seg[m] = f(eval(m<<1),eval(m<<1|1));
        }
    }
    void apply(int a, int b, E x){
        prop_to(a+=N);
        prop_to(b+=N);
        int l=a,r=b;
        while(l<r){
            if (l&1) lazy[l]=h(lazy[l],x), l++;
            if (r&1) r--, lazy[r]=h(lazy[r],x);
            l>>=1; r>>=1;
        }
        recalc(a);
        recalc(b);
    }
    T get(int k){
        prop_to(k+=N);
        return seg[k];
    }
    void set(int k, T x){
        prop_to(k+=N);
        seg[k] = x;
        recalc(k);
    }
    T query(int a, int b){
        T L=te, R=te;
        prop_to(a+=N);
        prop_to(b+=N);
        while(a<b){
            if (a&1) L = f(L,eval(a++));
            if (b&1) R = f(eval(--b),R);
            a>>=1; b>>=1;
        }
        return f(L,R);
    }
    T for_all(){return eval(1);}
    int left_most(int l, bool(*chk)(T)){
        prop_to(l+=N);
        int r=2*N;
        T val=te;
        while(l<r){
            if (l&1){
                if (chk(f(val,eval(l)))) break;
                val = f(val,eval(l++));
            }
            l>>=1; r>>=1;
        }
        if (l>=r) return n;
        while(l<N){
            l<<=1;
            if (!chk(f(val,eval(l)))){
                val = f(val,eval(l++));
            }
        }
        return l-N;
    }
    T operator[](int k){return get(k);}
};