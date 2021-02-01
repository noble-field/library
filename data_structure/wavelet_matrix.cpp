//-------------------------------------------------
//--Wavelet Matrix
//-------------------------------------------------
class bit_vector
{
private:
    static constexpr size_t BITS = 6;
    static constexpr size_t UMASK = (1<<BITS)-1;

    const size_t nchunks;
    uint64_t *dat;
    int *sum;
public:
    bit_vector(const size_t n):nchunks((n>>BITS)+1){
        sum = (int*)malloc(nchunks*sizeof(int));
        dat = (uint64_t*)malloc(nchunks*sizeof(uint64_t));
        memset(dat,0,nchunks*sizeof(uint64_t));
    }
    inline void set(const int k){dat[k>>BITS]|=1ULL<<(k&UMASK);}
    inline void build(){
        sum[0]=0ULL;
        for(size_t i=1; i!=nchunks; i++){
            sum[i]=sum[i-1]+__builtin_popcountll(dat[i-1]);
        }
    }
    inline int rank1(const int k){
        return sum[k>>BITS] + 
            __builtin_popcountll(dat[k>>BITS]&~(UINT64_MAX<<(k&UMASK)));
    }
    inline int rank0(const int k){return k-rank1(k);}
    inline bool operator[](const int k){return dat[k>>BITS]>>(k&UMASK)&1;};
};
template<typename T, int MAXLOG=18>
class WaveletMatrix
{
private:
    bit_vector *vs[MAXLOG];
    int r0[MAXLOG];
    
    inline int next_idx(const int k, bool f, int i){
        return f ? vs[i]->rank1(k)+r0[i] : vs[i]->rank0(k);
    }
public:
    template<typename E>
    WaveletMatrix(E v){
        const size_t N = v.size();
        E left(N),right(N);
        for(int i=MAXLOG-1; i>=0; i--){
            vs[i] = new bit_vector(N);
            size_t l=0,r=0;
            for(size_t j=0; j<N; j++){
                if (v[j]>>i&1) vs[i]->set(j), right[r++]=v[j];
                else left[l++]=v[j];
            }
            vs[i]->build();
            r0[i] = l;
            v.swap(left);
            for(size_t j=0; j<r; j++)
                v[j+l]=right[j];
        }
    }
    T access(int k){
        T ret=static_cast<T>(0);
        for(int i=MAXLOG-1; i>=0; i--){
            const bool f = (*vs[i])[k];
            ret |= static_cast<T>(f)<<i;
            k = next_idx(k,f,i);
        }
        return ret;
    }
    int rank(int l, int r, const T x){
        for(int i=MAXLOG-1; i>=0; i--){
            const bool f = (x>>i&1);
            l = next_idx(l,f,i);
            r = next_idx(r,f,i);
        }
        return r-l;
    }
    inline int rank(const int k, const T x){return rank(0,k,x);}
    T quantile(int l, int r, int k){
        T ret=static_cast<T>(0);
        for(int i=MAXLOG-1; i>=0; i--){
            const int c0_l = vs[i]->rank0(l);
            const int c0_r = vs[i]->rank0(r);
            const int c0 = c0_r-c0_l;
            const bool f = (c0>k)?(false):(k-=c0,true);
            ret |= static_cast<T>(f)<<i;
            l = f ? l-c0_l+r0[i] : c0_l;
            r = f ? r-c0_r+r0[i] : c0_r;
        }
        return ret;
    }
};