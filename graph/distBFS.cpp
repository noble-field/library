//-------------------------------------------------
//--Dist BFS
//-------------------------------------------------
template<class E>
vector<int> distBFS(Graph<E> &G, int s)
{
    vector<int> dist(G.size(),-1); dist[s]=0;
    queue<int> que; que.push(s);
    while(!que.empty()){
        int v = que.front(); que.pop();
        for(auto e:G[v]){
            if (dist[e.to]!=-1) continue;
            dist[e.to]=dist[v]+1;
            que.push(e.to);
        }
    }
    return dist;
}

template<class E>
vector<int> dist01BFS(Graph<E> &G, int s, int inf=1e9)
{
    vector<int> dist(G.size(),inf); dist[s]=0;
    deque<int> deq; deq.push_back(s);
    while(!deq.empty()){
        int v = deq.front(); deq.pop_front();
        for(auto e:G[v]){
            if (dist[e.to]>dist[v]+e.cost){
                dist[e.to]=dist[v]+e.cost;
                if (e.cost>0) deq.push_back(e.to);
                else deq.push_front(e.to);
            }
        }
    }
    return dist;
}
