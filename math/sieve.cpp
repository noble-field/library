//-------------------------------------------------
//--Sieve of Eratosthenes
//-------------------------------------------------
class Sieve
{
private:
    ::std::vector<bool> prime;
public:
    Sieve(int n):prime(n+1, true){
        prime[0] = prime[1] = false;
        for(int i=2; i*i<=n; i++){
            if (!prime[i]) continue;
            for(int j=i*2; j<=n; j+=i){
                prime[j] = false;
            }
        }
    }
    bool isprime(int x){return prime[x];}
};
