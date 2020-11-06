//-------------------------------------------------
//--Binary Indexed Tree (Sum only)
//-------------------------------------------------
template<typename T>
class BIT
{
private:
    const int N;
    vector<T> bit;
public:
    BIT(){}
    BIT(int n):N(n),bit(n+1,0){}
    BIT(const vector<T> &v):N(v.size()),bit(v.size()+1){
        for(int i=1; i<=N; i++) bit[i] = v[i-1];
        for(int i=1; i<N; i++){
            if (i+(i&-i)>N) continue;
            bit[i+(i&-i)] += bit[i];
        }
    }
    void add(int k, T x){
        for(int i=k+1; i<=N; i+=i&-i) bit[i]+=x;
    }
    T sum(int k){
        T ret=0;
        for(int i=k; i>0; i-=i&-i) ret+=bit[i];
        return ret;
    }
    T sum(int l, int r){return sum(r)-sum(l);}
    void set(int k, T x){
        T upd = x-sum(k,k+1);
        add(k,upd);
    }
    T operator[](int k){return sum(k+1)-sum(k);}
};