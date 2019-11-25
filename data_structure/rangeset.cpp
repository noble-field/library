//-------------------------------------------------
//--Range Set Counter
//-------------------------------------------------
template<typename T>
class RangeSet
{
private:
    ::std::vector<int> v;
    ::std::unordered_map<T, int> Map;
    ::std::vector<::std::vector<int> > data;
    int kind;
public:
    RangeSet(const ::std::vector<T> &v_):v(v_.size()){
        int sz = v_.size(); kind = 0;
        for(int i=0;i<sz;i++){
            T t = v_[i];
            if (Map.count(t)){
                data[Map[t]].push_back(i);
            }else{
                Map[t] = kind++;
                data.push_back(::std::vector<int>());
                data.back().push_back(i);
            }
            v[i] = Map[t];
        }
    }
    int query(T x){
        if (!Map.count(x)) return 0;
        return data[Map[x]].size();
    }
    int query(int a, int b, T x){
        if (a>b) return 0;
        if (!Map.count(x)) return 0;
        int xi = Map[x];
        auto right = ::std::upper_bound(data[xi].begin(),data[xi].end(),b);
        auto left  = ::std::lower_bound(data[xi].begin(),data[xi].end(),a);
        return right-left;
    }
    void update(int k, T x){
        int ei = v[k];
        auto eitr = ::std::lower_bound(data[ei].begin(),data[ei].end(),k);
        data[ei].erase(eitr);
        v[k] = Map[x];
        if (Map.count(x)){
            int xi = Map[x];
            auto itr = ::std::lower_bound(data[xi].begin(),data[xi].end(),k);
            data[xi].insert(itr, k);
        }else{
            Map[x] = kind++;
            data.push_back(::std::vector<int>());
            data.back().push_back(k);
        }
    }
};
