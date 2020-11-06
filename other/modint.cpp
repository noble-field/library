//-------------------------------------------------
//--ModInt
//-------------------------------------------------
const uint_fast64_t MOD = 1e9+7;

class mint
{
private:
    using Value = uint_fast64_t;
    Value n;
public:
    mint():n(0){}
    mint(int_fast64_t _n):n(_n<0 ? MOD-(-_n)%MOD : _n%MOD){}
    mint(const mint &m):n(m.n){}

    friend ostream& operator<<(ostream &os, const mint &a){
		return os << a.n;
	}
    friend istream& operator>>(istream &is, mint &a){
        Value temp; is>>temp;
        a = mint(temp);
        return is;
    }

    mint& operator+=(const mint &m){n+=m.n; n=(n<MOD)?n:n-MOD; return *this;}
    mint& operator-=(const mint &m){n+=MOD-m.n; n=(n<MOD)?n:n-MOD; return *this;}
    mint& operator*=(const mint &m){n=n*m.n%MOD; return *this;}
    mint& operator/=(const mint &m){return *this*=m.inv();}
    mint& operator++(){return *this+=1;}
    mint& operator--(){return *this-=1;}

    mint operator+(const mint &m) const {return mint(*this)+=m;}
    mint operator-(const mint &m) const {return mint(*this)-=m;}
    mint operator*(const mint &m) const {return mint(*this)*=m;}
    mint operator/(const mint &m) const {return mint(*this)/=m;}
    mint operator++(int){mint t(*this); *this+=1; return t;}
    mint operator--(int){mint t(*this); *this-=1; return t;}

    bool operator==(const mint &m) const {return n==m.n;}
    bool operator!=(const mint &m) const {return n!=m.n;}
    mint operator-() const {return mint(MOD-n);}

    mint pow(Value b) const {
        mint ret(1), m(*this);
        while(b){
            if (b & 1) ret*=m;
            m*=m;
            b>>=1;
        }
        return ret;
    }

    mint inv() const {return pow(MOD-2);}
};
