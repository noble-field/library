//-------------------------------------------------
//--Fast I/O (Chotto Hayai Nyuushutsuryoku)
//-------------------------------------------------
class FastIO
{
private:
    static const int IO_SIZE = 2e7;
    char rbuf[IO_SIZE], wbuf[IO_SIZE], *rp, *wp;
    char temp[19];
    inline bool minus(char c){return c=='-';}
    inline int cnum(char c){return c-'0';}
    inline int numc(int c){return c+'0';}
public:
    FastIO(){
        fread(rbuf,1,IO_SIZE,stdin);
        rp=rbuf; wp=wbuf;
    }
    ~FastIO(){fwrite(wbuf,1,wp-wbuf,stdout);}
    template<typename T=int>
    inline T readInt(){
        bool s; T ret=0;
        while(!isdigit(*rp) && !minus(*rp)) rp++;
        if (s=minus(*rp)) rp++;
        while(isdigit(*rp)) ret=ret*10+cnum(*rp++);
        return s?-ret:ret;
    }
    inline void readStr(string &s){
        string t="";
        while(isspace(*rp)) rp++;
        while(!isspace(*rp)) t+=*rp++;
        s.swap(t);
    }
    inline char getc(){
        while(isspace(*rp)) rp++;
        return *rp++;
    }
    inline void putc(int c){*wp++ = c;}
    inline void puts(const char *s){while(*s!='\0') putc(*s++);}
    inline void writeStr(const string &s){
        for(auto c:s) putc(c);
    }
    template<typename T>
    inline void writeInt(T x){
        if (x==0){putc('0'); return;}
        if (x<0) putc('-'), x=-x;
        char *tp=temp; T y=x;
        do{
            y=x/10;
            *tp++ = numc(x-y*10);
        }while(x=y);
        while(tp!=temp) putc(*(--tp));
    }
    FastIO& operator<<(const char a){putc(a);return *this;}
    FastIO& operator<<(const char *s){puts(s);return *this;}
    FastIO& operator<<(const string &a){writeStr(a);return *this;}
    FastIO& operator<<(const int a){writeInt(a);return *this;}
    FastIO& operator<<(const long long a){writeInt(a);return *this;}
    FastIO& operator>>(char &a){a=getc();return *this;}
    FastIO& operator>>(string &a){readStr(a);return *this;}
    FastIO& operator>>(int &a){a=readInt<int>();return *this;}
    FastIO& operator>>(long long &a){a=readInt<long long>();return *this;}
};
#define br '\n'
FastIO io;
