//-------------------------------------------------
//--Prim
//-------------------------------------------------
template<class T=int, class E>
T prim(Graph<E> &G, int s=0)
{
    T ret=0;
    using P=pair<T,int>;
    int V = G.size();
    vector<bool> use(V);
    priority_queue<P,vector<P>,greater<P> > que;
    que.push(P(0,s));
    while(!que.empty()){
        T cost; int v;
        tie(cost,v) = que.top(); que.pop();
        if (use[v]) continue;
        ret+=cost; use[v]=true;
        for(auto e:G[v])if(!use[e.to]){
            que.push(P(e.cost,e.to));
        }
    }
    return ret;
}

template<class T=int, class E>
T prim_naive(Graph<E> &G, int s=0)
{
    T ret=0;
    int V = G.size();
    vector<T> mincost(V,inf); mincost[s]=0;
    vector<bool> use(V);
    while(true){
        int v=-1;
        for(int i=0;i<V;i++){
            if (!use[i] && (v==-1||mincost[i]<mincost[v])){
                v=i;
            }
        }
        if (v==-1) break;
        ret+=mincost[v]; use[v]=true;
        for(auto e:G[v]){
            mincost[e.to]=min(mincost[e.to],e.cost);
        }
    }
}
