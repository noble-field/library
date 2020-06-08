//-------------------------------------------------
//--Dijkstra
//-------------------------------------------------
template<class T, class E>
vector<T> dijkstra(Graph<E> &G, int s, T inf)
{
    using P=pair<T,int>;
    vector<T> dist(G.size(),inf); dist[s]=0;
    priority_queue<P,vector<P>,greater<P> > que;
    que.push(P(0,s));
    while(!que.empty()){
        T cost; int v;
        tie(cost,v) = que.top(); que.pop();
        if (cost>dist[v]) continue;
        for(auto e:G[v]){
            if (dist[e.to]>dist[v]+e.cost){
                dist[e.to]=dist[v]+e.cost;
                que.push(P(dist[e.to],e.to));
            }
        }
    }
    return dist;
}

template<class T, class E>
vector<T> dijkstra_naive(Graph<E> &G, int s, T inf)
{
    int V = G.size();
    vector<T> dist(V,inf); dist[s]=0;
    vector<bool> use(V);
    while(true){
        int v=-1;
        for(int i=0;i<V;i++){
            if(!use[i] && (v==-1||dist[i]<dist[v])){
                v=i;
            }
        }
        if (v==-1) break;
        use[v]=true;
        for(auto e:G[v]){
            chmin(dist[e.to],dist[v]+e.cost);
        }
    }
    return dist;
}
