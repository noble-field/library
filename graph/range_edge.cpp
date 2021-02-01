//-------------------------------------------------
//--Range Add Edge Technique
//-------------------------------------------------

template<class E>
class Range_Edge {
private:
    Graph<E> g;
    const E e0;
    int N;
    int vidx;
public:
    Range_Edge(int n, int m, const E &e0):g(1),e0(e0){
        N = 1;
        while(N<n) N<<=1;
        g.adj.resize(5*N+2*m);
        vidx = 5*N;
        base();
    }
    void base(){
        E e = e0;
        rep(i,N-1){
            e.to = i*2+1+N; g.add_edge(i+N, e);
            e.to++; g.add_edge(i+N, e);
        }
        rep(i,N){
            e.to = i; g.add_edge(i+2*N-1, e);
        }
        rep(i,N-1){
            e.to = i+3*N;
            g.add_edge(i*2+1+3*N, e);
            g.add_edge(i*2+2+3*N, e);
        }
        rep(i,N){
            e.to = i+4*N-1; g.add_edge(i, e);
        }
    }
    void add_edge(int v, E e){
        g.add_edge(v, e);
    }
    void add_edge(int a, int b, int c, int d, E e){
        E ee = e0;
        a+=N; b+=N;
        ee.to = vidx++;
        while(a<b){
            if (a&1){
                g.add_edge(a-1+3*N, ee);
                a++;
            }
            if (b&1){
                b--;
                g.add_edge(b-1+3*N, ee);
            }
            a>>=1; b>>=1;
        }
        c+=N; d+=N;
        while(c<d){
            if (c&1){
                ee.to = c-1+N; g.add_edge(vidx, ee);
                c++;
            }
            if (d&1){
                d--;
                ee.to = d-1+N; g.add_edge(vidx, ee); 
            }
            c>>=1; d>>=1;
        }
        e.to = vidx; g.add_edge(vidx-1, e);
        vidx++;
    }
    Graph<E>& graph(){return g;}
};