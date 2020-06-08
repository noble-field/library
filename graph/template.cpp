//-------------------------------------------------
//--Graph Template
//-------------------------------------------------
template<class E>
struct Graph
{
    vector<vector<E> > adj;
    Graph(int N):adj(N){}
    virtual void add_edge(int v, E e){adj[v].push_back(e);}
    vector<E>& operator[](int v){return adj[v];}
    inline int size(){return adj.size();}
};

struct NormalEdge {
    int to;
    NormalEdge(int to):to(to){}
};

struct UWGraph : public Graph<NormalEdge>
{
    UWGraph(int N):Graph(N){}
    void add_edge(int v, int e){adj[v].push_back({e});}
};
