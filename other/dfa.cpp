//-------------------------------------------------
//--Deterministic Finite Automaton
//-------------------------------------------------
class DFA
{
private:
    using P = pair<int,char>;
    using F = void (*)(string &S, char c);

    map<P,int> stf;
    map<P,F> cnv;
    set<int> accepts;
    int st;
public:
    DFA(int s):st(s){}
    void add_edge(int u, char input, int v, F f=nullptr){
        stf[P(u,input)] = v;
        if (f!=nullptr) cnv[P(u,input)] = f;
    }
    void add_edge(int u, int type, int v, F f=nullptr){
        char l,r;
        if (type==LOWER_CASE) l='a', r='z';
        if (type==UPPER_CASE) l='A', r='Z';
        if (type==NUMBER_CASE) l='0', r='9';
        for(char i=l; i<=r; i++)
            add_edge(u,i,v,f);
    }
    void add_accept(int ac){
        accepts.insert(ac);
    }
    void add_accepts(vi acs){
        for(auto ac:acs)
            accepts.insert(ac);
    }
    bool match(const string &S){
        int cur = st;
        for(auto c:S){
            P param(cur,c);
            if (stf.count(param)) cur = stf[param];
            else cur=-1;
        }
        return accepts.count(cur);
    }
    bool convert(const string &S, string &dest){
        string res;
        int cur = st;
        for(auto c:S){
            P param(cur,c);
            if (stf.count(param)){
                if (cnv.count(param)) cnv[param](res,c);
                cur = stf[param];
            }else{
                cur = -1;
            }
        }
        if (accepts.count(cur)){
            swap(dest,res);
            return true;
        }
        return false;
    }
};