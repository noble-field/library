//-------------------------------------------------
//--Ford Fulkerson
//-------------------------------------------------
template<typename F>
class FordFulkerson
{
private:
    struct Edge {int to; F cap; int rev;};
    struct EdgeLocation {int from,idx;};
    using FlowGraph = vector<vector<Edge> >;
    const F F_INF;
    FlowGraph G;
    uint32_t time;
    vector<uint32_t> stamp;
    int idx;
    vector<EdgeLocation> eloc;
    F dfs(int v, int t, F flow){
        if (v==t) return flow;
        stamp[v] = time;
        for(Edge &e:G[v]){
            if (stamp[e.to]<time && e.cap>0){
                F res = dfs(e.to,t,min(flow,e.cap));
                if (res>0){
                    e.cap-=res;
                    G[e.to][e.rev].cap+=res;
                    return res;
                }
            }
        }
        return 0;
    }
public:
    FordFulkerson(int N):G(N),idx(0),time(1),stamp(N),F_INF(numeric_limits<F>::max()){}
    int add_edge(int from, int to, F cap){
        G[from].push_back({to,cap,(int)G[to].size()});
        int fidx = G[from].size()-1;
        G[to].push_back({from,0,fidx});
        eloc.push_back({from,fidx});
        return idx++;
    }
    F max_flow(int s, int t){
        F ret=0;
        for(F flow; (flow=dfs(s,t,F_INF))>0; time++)
            ret+=flow;
        return ret;
    }
    F max_flow(int s, int t, F flow_limit){
        F ret=0;
        for(F flow; flow_limit>0 && (flow=dfs(s,t,flow_limit))>0; time++){
            ret+=flow;
            flow_limit-=flow;
        }
        return ret;
    }
    F get_flow(int ei){
        assert(ei<idx);
        const Edge &e = G[eloc[ei].from][eloc[ei].idx];
        return G[e.to][e.rev].cap;
    }
    F get_cap(int ei){
        assert(ei<idx);
        const Edge &e = G[eloc[ei].from][eloc[ei].idx];
        return e.cap+G[e.to][e.rev].cap;
    }
    void change_edge(int ei, F cap, F flow){
        assert(ei<idx && flow<=cap);
        Edge &e = G[eloc[ei].from][eloc[ei].idx];
        e.cap = cap-flow;
        G[e.to][e.rev].cap = flow;
    }
    vector<bool> min_cut(int s){
        vector<bool> ret(G.size());
        ret[s] = true;
        queue<int> que;
        que.emplace(s);
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(Edge &e:G[v]){
                if (!ret[e.to] && e.cap>0){
                    ret[e.to] = true;
                    que.emplace(e.to);
                }
            }
        }
        return ret;
    }
};