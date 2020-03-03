//-------------------------------------------------
//--Matrix
//-------------------------------------------------
template<typename T>
class Matrix
{
private:
    using V = ::std::vector<T>;
    using M = ::std::vector<V>;
    M dat;
    int h,w;
public:
    Matrix(int h_, int w_):h(h_),w(w_){
        dat.resize(h,V(w));
    }
    Matrix(const M &mat){
        h = mat.size();
        w = mat[0].size();
        dat.resize(h,V(w));
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
                dat[i][j]=mat[i][j];
    }
    Matrix(const Matrix &m){
        h = m.h; w = m.w;
        dat.resize(h,V(w));
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
                dat[i][j]=m.dat[i][j];
    }
    static Matrix getI(int n){
        Matrix ret(n,n);
        for(int i=0;i<n;i++) ret[i][i] = 1;
        return ret;
    }
    Matrix& operator+=(const Matrix &m){
        assert(m.h==h && m.w==w);
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
                dat[i][j]+=m.dat[i][j];
        return *this;
    }
    Matrix& operator-=(const Matrix &m){
        assert(m.h==h && m.w==w);
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
                dat[i][j]-=m.dat[i][j];
        return *this;
    }
    Matrix& operator*=(const Matrix &m){
        assert(m.h==w);
        M ret(h, V(m.w));
        for(int i=0; i<h; i++)
            for(int j=0; j<m.w; j++)
                for(int k=0; k<w; k++)
                    ret[i][j]+=dat[i][k]*m.dat[k][j];
        dat.swap(ret); w = m.w;
        return *this;
    }
    Matrix& operator*=(T c){
        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
                dat[i][j]*=c;
        return *this;
    }
    Matrix& operator^=(::std::uint_fast64_t t){
        assert(h==w);
        Matrix ret = Matrix::getI(h);
        Matrix m(*this);
        while(t){
            if (t&1) ret*=m;
            m*=m;
            t>>=1;
        }
        dat.swap(ret.dat);
        return *this;
    }
    Matrix operator+(const Matrix &m) const {return Matrix(*this)+=m;}
    Matrix operator-(const Matrix &m) const {return Matrix(*this)-=m;}
    Matrix operator*(const Matrix &m) const {return Matrix(*this)*=m;}
    Matrix operator*(T c) const {return Matrix(*this)*=c;}
    Matrix operator^(::std::uint_fast64_t t) const {return Matrix(*this)^=t;}
    Matrix operator-() const {return Matrix(*this)*=-1;}
    V& operator[](int h){return dat[h];}
};
