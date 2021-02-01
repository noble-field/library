//-------------------------------------------------
//--Binary Indexed Tree
//-------------------------------------------------
template<typename T, T(*f)(T,T), T(*inv)(T)>
class BIT
{
private:
    const int N;
    vector<T> bit;
    const T e;
public:
    BIT(int n, T e):N(n),bit(n+1,e),e(e){}
    BIT(const vector<T> &v, T e):N(v.size()),bit(v.size()+1),e(e){
        for(int i=1; i<=N; i++) bit[i] = v[i-1];
        for(int i=1; i<N; i++){
            if (i+(i&-i)>N) continue;
            bit[i+(i&-i)] = f(bit[i],bit[i+(i&-i)]);
        }
    }
    void apply(int k, T x){
        for(int i=k+1; i<=N; i+=i&-i) bit[i] = f(bit[i],x);
    }
    T query(int k){
        T ret=e;
        for(int i=k; i>0; i-=i&-i) ret = f(ret,bit[i]);
        return ret;
    }
    T query(int a, int b){return f(query(b), inv(query(a)));}
    void set(int k, T x){
        T upd = f(x, inv(query(k,k+1)));
        apply(k, upd);
    }
    T operator[](int k){return query(k,k+1);}
};
