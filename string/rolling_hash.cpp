//-------------------------------------------------
//--Rolling Hash
//-------------------------------------------------
using ull = unsigned long long;
using Hash = vector<ull>;

const int M_NUM = 2;
const ull mod[4] = {(ull)1e9+33,(ull)1e9+87,(ull)1e9+93,(ull)1e9+97};
const ull base = 9973;

class RollingHash
{
private:
    int n;
    vector<ull> _hash[M_NUM], _pow[M_NUM];
public:
    RollingHash(const string &s){
        n = s.size();
        for(int i=0; i<M_NUM; i++){
            _hash[i].resize(n+1); _hash[i][0] = 0;
            _pow[i].resize(n+1); _pow[i][0] = 1;
            for(int j=0; j<n; j++){
                _pow[i][j+1] = (_pow[i][j]*M_NUM)%mod[i];
                _hash[i][j+1] = (_hash[i][j]*M_NUM+s[j])%mod[i];
            }
        }
    }
    bool match(int l, int r, Hash h){
        bool ret=true;
        for(int i=0; i<M_NUM; i++){
            ull value = _hash[i][r]-(_hash[i][l]*_pow[i][r-l])%mod[i];
            value = (value+mod[i])%mod[i];
            ret&=(value==h[i]);
        }
        return ret;
    }
    vector<int> matches(Hash h, int w){
        vector<int> ret;
        for(int i=0; i<n-w+1; i++)
            if (match(i,i+w,h)) ret.push_back(i);
        return ret;
    }
    static Hash hash(const string &s){
        Hash ret(M_NUM);
        for(int i=0; i<M_NUM; i++)
            for(int j=0; j<s.size(); j++)
                ret[i]=(ret[i]*M_NUM+s[j])%mod[i];
        return ret;
    }
};
