//-------------------------------------------------
//--Two SAT
//-------------------------------------------------
class TwoSAT
{
private:
    int N;
    SCC scc;
public:
    TwoSAT(int n):scc(n<<1),N(n){}
    void add_if(int x, bool f, int y, bool g){
        scc.add_edge(x<<1|f,y<<1|g);
        scc.add_edge(y<<1|!g,x<<1|!f);
    }
    void add_clause(int x, bool f, int y, bool g){
        scc.add_edge(x<<1|!f,y<<1|g);
        scc.add_edge(y<<1|!g,x<<1|f);
    }
    void add_var(int x, bool f){
        scc.add_edge(x<<1|!f,x<<1|f);
    }
    vector<bool> solve(){
        scc.build();
        vector<bool> ret(N);
        for(int i=0; i<N; i++){
            int u = scc[i<<1|1];
            int v = scc[i<<1];
            if (u > v)
                ret[i] = true;
            else if(u < v)
                ret[i] = false;
            else
                return vector<bool>();
        }
        return ret;
    }
};