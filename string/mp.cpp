//-------------------------------------------------
//--MP Algorithm
//-------------------------------------------------
template <class T>
class MP
{
private:
    int n;
    const T p;
    vector<int> M;
public:
    MP(const T &s):p(s),n(s.size()){
        M.resize(n+1); M[0]=-1;
        int j=-1;
        for(int i=0;i<n;i++){
            while(j>-1 && p[i]!=p[j]) j=M[j];
            M[i+1] = ++j;
        }
    }
    vector<int> matches(const T &s){
        vector<int> ret;
        int j=0;
        rep(i,s.size()){
            while(j>-1 && s[i]!=p[j]) j=M[j];
            if (++j == n){
                ret.push_back(i-j+1);
                j = M[j];
            }
        }
        return ret;
    }
};
