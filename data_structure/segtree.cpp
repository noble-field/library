//-------------------------------------------------
//--Segment tree
//-------------------------------------------------
template<typename T, T(*f)(T,T), T(*g)(T,T)=nullptr>
class SegmentTree
{
private:
    int n,N;
    vector<T> seg;
    const T e;
public:
    SegmentTree(){}
    SegmentTree(int n, T e):n(n),e(e){
        init();
    }
    SegmentTree(vector<T> &v, T e):n(v.size()),e(e){
        init();
        for(int i=0; i<n; i++)
            seg[i+N] = v[i];
        build();
    }
    void init(){
        N=1;
        while(N<n) N<<=1;
        seg.resize(2*N,e);
    }
    void build(){
        for(int i=N-1; i>=1; i--)
            seg[i] = f(seg[i<<1],seg[i<<1|1]);
    }
    void climb(int k){
        while(k>>=1){
            seg[k] = f(seg[k<<1],seg[k<<1|1]);
        }
    }
    void set(int k, T x){
        seg[k+=N] = x;
        climb(k);
    }
    void apply(int k, int x){
        assert(g!=nullptr);
        k+=N;
        seg[k] = g(seg[k],x);
        climb(k);
    }
    T query(int a, int b){
        a+=N; b+=N;
        T L=e, R=e;
        while(a<b){
            if (a&1) L=f(L,seg[a++]);
            if (b&1) R=f(seg[--b],R);
            a>>=1; b>>=1;
        }
        return f(L,R);
    }
    T for_all(){return seg[1];}
    int left_most(int l, bool(*chk)(T)){
        l+=N; int r=2*N;
        T val=e;
        while(l<r){
            if (l&1){
                if (chk(f(val,seg[l]))) break;
                val = f(val,seg[l++]);
            }
            l>>=1; r>>=1;
        }
        if (l>=r) return n;
        while(l<N){
            l<<=1;
            if (!chk(f(val,seg[l]))){
                val = f(val,seg[l++]);
            }
        }
        return l-N;
    }
    int right_most(int r, bool(*chk)(T)){
        r+=N; int l=N-1;
        T val=e;
        while(l<r){
            if (!(r&1) || r==1){
                if (chk(f(seg[r],val))) break;
                val = f(seg[r--],val);
            }
            l>>=1; r>>=1;
        }
        if (l>=r) return -1;
        while(r<N){
            r=r<<1|1;
            if (!chk(f(seg[r],val))){
                val = f(seg[r--],val);
            }
        }
        return r-N;
    }
    T operator[](int k) {return seg[k+N];}
};