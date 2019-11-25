//-------------------------------------------------
//--Range Set Counter
//-------------------------------------------------
template<typename T>
class RangeSet
{
private:
    ::std::vector<T> v;
    ::std::unordered_map<T, ::std::vector<int> > data;
public:
    RangeSet(const ::std::vector<T> &v_):v(v_){
        int sz = v.size();
        for(int i=0;i<sz;i++){
            T t = v[i];
            data[t].push_back(i);
        }
    }
    int query(T x){
        if (!data.count(x)) return 0;
        return data[x].size();
    }
    int query(int a, int b, T x){
        if (a>b) return 0;
        if (!data.count(x)) return 0;
        auto right = ::std::upper_bound(data[x].begin(),data[x].end(),b);
        auto left  = ::std::lower_bound(data[x].begin(),data[x].end(),a);
        return right-left;
    }
    void update(int k, T x){
        int ei = v[k];
        auto eitr = ::std::lower_bound(data[ei].begin(),data[ei].end(),k);
        data[ei].erase(eitr);
        v[k] = x;
        if (data.count(x)){
            auto itr = ::std::lower_bound(data[x].begin(),data[x].end(),k);
            data[x].insert(itr, k);
        }else{
            data[x].push_back(k);
        }
    }
};
