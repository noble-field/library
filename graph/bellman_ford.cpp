//-------------------------------------------------
//--Bellman-Ford
//-------------------------------------------------
template<class T, class E>
vector<T> bellman_ford(Graph<E> &G, int s, T inf)
{
    int V = G.size();
    vector<T> dist(V);
    for(int i=0;i<V;i++) dist[i]=inf; dist[s]=0;
    int idx=0;
    bool update=true;
    while(update){
        update=false;
        for(int v=0;v<V;v++)for(auto e:G[v]){
            if (dist[v]!=inf && dist[e.to]>dist[v]+e.cost){
                dist[e.to]=dist[v]+e.cost;
                update=true;
            }
        }
        if (update && idx==V-1) return vector<T>();
        idx++;
    }
    return dist;
}
