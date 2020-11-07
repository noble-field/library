//-------------------------------------------------
//--Rolling Hash
//-------------------------------------------------

class Rolling_Hash
{
private:
    using ull = unsigned long long;
    using Hash = vector<ull>;
    static const int MOD_NUM = 2;
    static const ull base = 9973;
    static const ull mod[4];
    int N;
    vector<ull> pow[MOD_NUM],hash[MOD_NUM];
public:
    template<typename T>
    Rolling_Hash(const T &s):N(s.size()){
        for(int i=0; i<MOD_NUM; i++){
            pow[i].resize(N+1,0);
            hash[i].resize(N+1,0);
            pow[i][0] = 1;
            for(int j=0; j<N; j++){
                pow[i][j+1]=(pow[i][j]*base)%mod[i];
                hash[i][j+1]=(hash[i][j]*base+s[j])%mod[i];
            }
        }
    }
    bool match(int l, int r, Hash hs){
        bool ret=true;
        for(int i=0; i<MOD_NUM; i++){
            ull right = hash[i][r];
            ull left = pow[i][r-l]*hash[i][l]%mod[i];
            ull val = (right<left)?(right+mod[i]-left):right-left;
            ret&=(val==hs[i]);
        }
        return ret;
    }
    vector<int> matches(Hash hs, int sz){
        vector<int> ret;
        for(int i=0; i<N-sz+1; i++){
            if (match(i,i+sz,hs)) ret.push_back(i);
        }
        return ret;
    }
    template<typename T>
    static Hash get_hash(const T &s){
        Hash ret(MOD_NUM);
        for(int i=0; i<MOD_NUM; i++)
            for(int j=0; j<s.size(); j++)
                ret[i]=(ret[i]*base+s[j])%mod[i];
        return ret;
    }
};
const unsigned long long Rolling_Hash::mod[4]={
    1000000033,1000000087,1000000093,1000000097
};