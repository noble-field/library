//-------------------------------------------------
//--Combination (depends on ModInt)
//-------------------------------------------------
class Combination
{
private:
    ::std::vector<mint> _fact;
    ::std::vector<mint> _finv;
public:
    Combination(int n):_fact(n+1), _finv(n+1){
        _fact[0] = _fact[1] = 1;
        _finv[0] = _finv[1] = 1;
        for(int i=2; i<=n; i++){
            _fact[i] = _fact[i-1]*i;
            _finv[i] = _fact[i].inv();
        }
    }
    mint fact(int x){return _fact[x];}
    mint finv(int x){return _finv[x];}
    mint comb(int x, int y){return _fact[x]*_finv[y]*_finv[x-y];}
    mint homo(int x, int y){return comb(x+y-1, y);}
};
