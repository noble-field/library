//-------------------------------------------------
//--Enum various numbers
//-------------------------------------------------
namespace Enum
{
    using fint = ::std::int_fast64_t;
    //素因数分解(素因数列挙)
    ::std::map<fint,int> factor(fint n)
    {
        ::std::map<fint,int> ret;
        for(fint i=2; i*i<=n; i++){
            while(n%i==0){
                ret[i]++;
                n/=i;
            }
        }
        if (n!=1) ret[n]++;
        return ret;
    }
    //約数列挙
    ::std::vector<fint> divisor(fint n)
    {
        ::std::vector<fint> ret;
        for(fint i=1; i*i<=n; i++){
            if (n%i==0){
                ret.push_back(i);
                if (i*i!=n) ret.push_back(n/i);
            }
        }
        return ret;
    }
    //商列挙(割る最小の数と商のペア)
    ::std::vector<::std::pair<fint,fint> > quotient(fint n)
    {
        ::std::vector<::std::pair<fint,fint> > ret;
        fint i=0;
        for(i=1; i*i<=n; i++){
            ret.emplace_back(i,n/i);
        }
        for(; i<=n; i++){
            fint d = n/i;
            ret.emplace_back(i,d);
            i+=(n-d*i)/d;
        }
        return ret;
    }
    //素数判定(おまけ)
    bool isprime(fint n)
    {
        for(fint i=2; i*i<=n; i++){
            if (n%i==0) return false;
        }
        return true;
    }
}
