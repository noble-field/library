//-------------------------------------------------
//--Lagrange Polynomial
//-------------------------------------------------
template <class T>
T lagrange_interpolation(const vector<pair<T,T> > &ps, T x){
    T ret=0;
    int n = ps.size();
    for(int i=0;i<n;i++){
        T s=1,t=1;
        for(int j=0;j<n;j++)if(j!=i){
            s*=x-ps[j].first;
            t*=ps[i].first-ps[j].first;
        }
        ret+=ps[i].second * s/t;
    }
    return ret;
}

template <class T>
class Lagrange
{
private:
    int n;
    vector<T> poly;
public:
    Lagrange(const vector<pair<T,T> > &ps):n(ps.size()){
        vector<T> dp(n+1); dp[0]=1;
        for(int i=0;i<n;i++)for(int j=n;j>=0;j--){
            dp[j]*=-ps[i].first;
            if (j>=1) dp[j]+=dp[j-1];
        }
        reverse(dp.begin(),dp.end());
        poly.resize(n);
        for(int i=0;i<n;i++){
            T inv=1;
            for(int j=0;j<n;j++)if(j!=i)
                inv*=ps[i].first-ps[j].first;
            inv = ps[i].second/inv;
            vector<T> src = dp;
            for(int j=0;j<n;j++)if(src[j]!=0){
                poly[j]+=src[j]*inv;
                src[j+1]+=src[j]*ps[i].first;
            }
        }
    }
    T interpolation(T x){
        T ret=0, c=1;
        for(int i=n-1;i>=0;i--){
            ret+=poly[i]*c;
            c*=x;
        }
        return ret;
    }
    T operator[](int k){return poly[k];}
};
