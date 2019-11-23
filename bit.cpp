//-------------------------------------------------
//--Binary Indexed Tree
//-------------------------------------------------
template<typename T>
class BIT
{
private:
    using F = function<T(T,T)>;
    using G = function<T(T)>;
    const int n;
    ::std::vector<T> data;
    F f; G g; T e;
public:
    BIT(int n, F f, G g, T e):n(n),data(n+1),f(f),g(g),e(e){
        for(int i=1; i<=n; i++) data[i] = e;
    }
    BIT(const ::std::vector<T> &v, F f, G g, T e)
         : n(v.size()),data(v.size()+1),f(f),g(g),e(e)
    {
        for(int i=1; i<=n; i++) data[i] = v[i-1];
        for(int i=1; i<n; i++)
            data[i+(i&-i)] = f(data[i], data[i+(i&-i)]);
    }
    void add(int k, T x){k++;
        for(int i=k; i<=n; i+=i&-i) data[i] = f(data[i], x);
    }
    T query(int k){
        T ret=e;
        for(int i=k; i>0; i-=i&-i) ret = f(ret, data[i]);
        return ret;
    }
    T query(int a, int b){return f(query(b), g(query(a)));}
    void update(int k, T x){
        T upd = f(x, g(query(k, k+1)));
        add(k, upd);
    }
    T operator[](int k){return query(k, k+1);}
};
