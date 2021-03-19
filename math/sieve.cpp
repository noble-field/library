//-------------------------------------------------
//--Sieve of Eratosthenes
//-------------------------------------------------
class Sieve
{
private:
    vector<int> minf;
public:
    Sieve(int n):minf(n+1){
        iota(minf.begin(),minf.end(),0);
        for(int i=2; i*i<=n; i++){
            if (minf[i]!=i) continue;
            for(int j=i*2; j<=n; j+=i){
                if (minf[j]==j) minf[j] = i;
            }
        }
    }
    using P = pair<int,int>;
    vector<P> factor(int N){
        vector<P> ret;
        while(N>1){
            int f = minf[N];
            int cnt = 0;
            while(minf[N]==f){
                N/=f;
                cnt++;
            }
            ret.emplace_back(f,cnt);
        }
        return ret;
    }
    bool operator[](int x){return minf[x]==x;}
};
