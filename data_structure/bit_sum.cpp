//-------------------------------------------------
//--Binary Indexed Tree (Sum only)
//-------------------------------------------------
template<typename T>
class BIT
{
private:
    const int n;
    ::std::vector<T> data;
public:
    BIT(int n):n(n),data(n+1){
        for(int i=1; i<=n; i++) data[i] = 0;
    }
    BIT(const ::std::vector<T> &v):n(v.size()),data(v.size()+1){
        for(int i=1; i<=n; i++) data[i] = v[i-1];
        for(int i=1; i<n; i++)
            data[i+(i&-i)] += data[i];
    }
    void add(int k, T x){k++;
        for(int i=k; i<=n; i+=i&-i) data[i] += x;
    }
    T query(int k){
        T ret=0;
        for(int i=k; i>0; i-=i&-i) ret += data[i];
        return ret;
    }
    T query(int a, int b){return query(b)-query(a);}
    void update(int k, T x){
        T upd = x-query(k, k+1);
        add(k, upd);
    }
    T operator[](int k){return query(k, k+1);}
};
