//-------------------------------------------------
//--Get Cycle Any
//-------------------------------------------------
namespace Cycle
{
    stack<int> st;
    vector<bool> seen,finished;
    int pos;

    template<class E>
    void dfs(int v, int p, Graph<E> &G, bool dir=true){
        st.push(v);
        seen[v] = true;
        for(auto e:G[v]){
            if (!dir && e.to==p) continue;
            if (finished[e.to]) continue;
            if (seen[e.to] && !finished[e.to]){
                pos = e.to;
                return;
            }
            dfs(e.to,v,G,dir);
            if (pos!=-1) return;
        }
        finished[v] = true;
        st.pop();
    }

    void init(int V){
        pos = -1; st=stack<int>();
        seen.resize(V,false);
        finished.resize(V,false);
    }

    vector<int> restore(){
        vector<int> ret;
        if (pos==-1) return ret;
        while(!st.empty()){
            int u = st.top(); st.pop();
            ret.push_back(u);
            if (u==pos) break;
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }

    template<class E>
    vector<int> get(Graph<E> &G, bool dir=true){
        int V = G.size();
        init(V);
        for(int i=0;i<V;i++)if(!seen[i]){
            dfs(i,-1,G,dir);
            if (pos!=-1) break;
        }
        return restore();
    }

    template<class E>
    vector<int> get(int v, Graph<E> &G, bool dir=true){
        int V = G.size();
        init(V);
        dfs(v,-1,G,dir);
        return restore();
    }

    template<class E>
    vector<int> minimize(vector<int> &cycle, Graph<E> &G, bool dir=true){
        vector<int> ret;
        int L = cycle.size();
        if (L==0) return ret;
        unordered_map<int,int> Mp;
        for(int j=0;j<L;j++) Mp[cycle[j]]=j;
        int i=0;
        while(i<L){
            ret.push_back(cycle[i]);
            int ni=i;
            for(auto e:G[cycle[i]]){
                if (!dir && i==0 && e.to==cycle[L-1]) continue;
                if (!dir && ret.size()<3 && e.to==cycle[0]) continue;
                if (e.to==cycle[0]){
                    ni=L;
                    break;
                }else{
                    chmax(ni,Mp[e.to]);
                }
            }
            i=ni;
        }
        return ret;
    }
}
