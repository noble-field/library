//-------------------------------------------------
//--Kruskal (Based on UnionFind)
//-------------------------------------------------
template<class T=int, class E>
T kruskal(Graph<E> &G)
{
    T ret=0;
    struct kEdge{
        int from,to; T cost;
        bool operator<(const kEdge &e){return cost<e.cost;};
    };

    int V = G.size();
    UnionFind uf(V);
    vector<kEdge> es;
    for(int v=0;v<V;v++)for(auto e:G[v])
        es.push_back({v,e.to,e.cost});
    sort(es.begin(),es.end());
    for(auto e:es){
        if (!uf.same(e.from,e.to)){
            uf.unite(e.from,e.to);
            ret+=e.cost;
        }
    }
    return ret;
}
