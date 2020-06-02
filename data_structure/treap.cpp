//-------------------------------------------------
//--Treap
//-------------------------------------------------
template <class T, class E=T>
class Treap
{
public:
    struct Node {
        Node *child[2];
        T val,sum;
        bool rev;
        uint32_t pri;
        int weight;
        Node(){}
        Node(T val, uint32_t pri):val(val),sum(val),pri(pri){
            child[0]=child[1]=nullptr;
            rev = 0; weight=1;
        }
    };
    using np = Node*;
private:
    // functions *
    // inline T f(T x, T y){return ;}
    // inline T g(T x, E y){return ;}
    // inline E h(E x, E y){return ;}

    int n,ptr;
    vector<Node> buf;

    uint32_t xorshift(){
        static uint32_t x = 123456789;
        static uint32_t y = 362436069;
        static uint32_t z = 521288629;
        static uint32_t w = 88675123;
        uint32_t t;
        t = x ^ (x<<11);
        x = y; y = z; z = w;
        w ^= t ^ (t>>8) ^ (w>>19);
        return w;
    }

    inline np make_node(const T &val, uint32_t pri, bool dummy){
        assert(ptr<n);
        np ret = &(buf[ptr]=Node(val,pri));
        if (!dummy) ptr++;
        return ret;
    }
    // inline T sum(np t){return t ? t->sum : e;}
    inline np update(np t){
        t->weight = weight(t->child[0])+weight(t->child[1])+1;
        // t->sum = f(f(sum(t->child[0]),t->val),sum(t->child[1]));
        return t;
    }
    inline void push(np t){
        // propagate to child
        if (t->rev){
            swap(t->child[0], t->child[1]);
            if (t->child[0]) t->child[0]->rev=true;
            if (t->child[1]) t->child[1]->rev=true;
            t->rev = false;
        }
    }
    inline np rotate(np t, int dir){
        np s = t->child[dir];
        t->child[dir] = s->child[1-dir];
        s->child[1-dir] = t;
        update(t); update(s);
        return s;
    }
    np insert(np t, int k, const T &val, uint32_t pri, bool dummy=false){
        if (!t) return make_node(val,pri,dummy);
        push(t);
        int c=weight(t->child[0]), dir=k>c;
        t->child[dir] = insert(t->child[dir],k-dir*(c+1),val,pri,dummy);
        update(t);
        if (t->pri >= t->child[dir]->pri) t = rotate(t,dir);
        return t;
    }
    np _erase(np t, int k, bool rot){
        if (!t) return nullptr;
        push(t);
        int w0=weight(t->child[0]);
        rot = rot||w0==k;
        int dir = k>w0;
        if (rot){
            if (!t->child[0]) return t->child[1];
            if (!t->child[1]) return t->child[0];
            dir = (t->child[0]->pri)<(t->child[1]->pri);
            push(t->child[1-dir]);
            t = rotate(t,1-dir);
            w0=weight(t->child[0]);
        }
        t->child[dir] = _erase(t->child[dir],k-dir*(w0+1),rot);
        update(t);
        return t;
    }
public:
    Treap(int n):n(n),buf(n),ptr(0){};
    inline int weight(np t){return t ? t->weight : 0;}
    void insert(np &t, int k, const T &val){ t = insert(t,k,val,xorshift());}
    void erase(np &t, int k){ t = _erase(t,k,false);}
    void push_back(np &t, const T &val){ t = insert(t,weight(t),val,xorshift());}

    pair<np,np> split(np t, int k){
        t = insert(t,k,0,0,true);
        return make_pair(t->child[0], t->child[1]);
    }
    np merge(np left, np right){
        np t = make_node(0,0,true);
        t->child[0] = left; t->child[1] = right;
        update(t);
        return _erase(t,weight(t->child[0]),true);
    }
    void reverse(np &t, int a, int b){
        auto p = split(t,a);
        auto q = split(p.second,b-a);
        q.first->rev = true;
        t = merge(merge(p.first,q.first),q.second);
    }
    void rotate(np &t, int a, int b, int c){
        auto p = split(t,a);
        auto q = split(p.second,c-a);
        auto r = split(q.first,b-a);
        t = merge(merge(merge(p.first,r.second),r.first),q.second);
    }
    // T query(np &t, int a, int b){
    //     auto p = split(t,a);
    //     auto q = split(p.second,b-a);
    //     T ret = sum(q.first);
    //     t = merge(p.first,merge(q.first,q.second));
    //     return ret;
    // }
    // void assign(np t, int k, T x){
    //     assert(t); push(t);
    //     int c=weight(t->child[0]), dir=k>c;
    //     if (c==k){
    //         t->val = x; update(t);
    //         return;
    //     }
    //     assign(t->child[dir],k-dir*(c+1),x);
    //     update(t);
    // }
    T get(np t, int k){
        assert(t); push(t);
        int c=weight(t->child[0]), dir=k>c;
        if (c==k) return t->val;
        return get(t->child[dir],k-dir*(c+1));
    }
};
