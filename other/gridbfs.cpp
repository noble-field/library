//-------------------------------------------------
//--Grid BFS
//-------------------------------------------------

template<typename T>
vector<vector<int> > gBFS(int si, int sj, vector<T> &field)
{
    int dx[]={0,1,0,-1};
    int dy[]={1,0,-1,0};
    int h = field.size();
    int w = field[0].size();
    using P = pair<int,int>;
    queue<P> que;
    que.emplace(si,sj);
    vector<vector<int> > dist(h,vector<int>(w,-1));
    dist[si][sj] = 0;
    while(que.size()){
        int x,y;
        tie(y,x) = que.front(); que.pop();
        for(int i=0; i<4; i++){
            int tx = x+dx[i];
            int ty = y+dy[i];
            if (!(0<=tx&&tx<w&&0<=ty&&ty<h)) continue;
            if (dist[ty][tx]!=-1) continue;
            // 壁の条件(適宜書き換える)
            if (field[ty][tx]=='#') continue;
            dist[ty][tx] = dist[y][x]+1;
            que.emplace(ty,tx);
        }
    }
    return dist;
}
