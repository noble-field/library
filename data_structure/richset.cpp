//-------------------------------------------------
//--Rich Set (Treap)
//-------------------------------------------------
template <class T>
class RichMultiSet
{
protected:
    struct Node {
        Node *child[2];
        T key,sum;
        uint32_t pri;
        int weight;
        Node(){}
        Node(T key, uint32_t pri):key(key),sum(key),pri(pri),weight(1){
            child[0]=child[1]=nullptr;
        }
    };
    using np = Node*;
    using F = function<T(T,T)>;

    np root;
    int n,ptr;
    vector<Node> buf;
    const T e; const F f;

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

    inline np make_node(const T &key, uint32_t pri, bool dummy){
        assert(ptr<n);
        np ret = &(buf[ptr]=Node(key,pri));
        if (!dummy) ptr++;
        return ret;
    }

    inline int weight(np t){return t ? t->weight : 0;}
    inline T sum(np t){return t ? t->sum : e;}
    inline np update(np t){
        t->weight = weight(t->child[0])+weight(t->child[1])+1;
        t->sum = f(f(sum(t->child[0]),t->key),sum(t->child[1]));
        return t;
    }
    np rotate(np t, int dir){
        np s = t->child[dir];
        t->child[dir] = s->child[1-dir];
        s->child[1-dir] = t;
        update(t); update(s);
        return s;
    }
    np insert(np t, int k, const T &key, uint32_t pri, bool dummy=false){
        if (empty()) return root = make_node(key,pri,dummy);
        if (!t) return make_node(key,pri,dummy);
        int c=weight(t->child[0]), dir=k>c;
        t->child[dir] = insert(t->child[dir], k-dir*(c+1), key, pri, dummy);
        update(t);
        if (t->pri >= t->child[dir]->pri) t = rotate(t,dir);
        return t;
    }
    np erase(np t, const T &key){
        if (!t) return nullptr;
        bool rot = (key==t->key);
        int dir = key > t->key;;
        if (rot){
            if (!t->child[0]) return t->child[1];
            if (!t->child[1]) return t->child[0];
            dir = (t->child[0]->pri)<(t->child[1]->pri);
            t = rotate(t,1-dir);
        }
        t->child[dir] = erase(t->child[dir],key);
        update(t);
        return t;
    }
    pair<np,np> split(np t, int k){
        t = insert(t,k,e,0,true);
        return make_pair(t->child[0], t->child[1]);
    }
    np merge(np left, np right){
        np t = make_node(e,0,true);
        t->child[0] = left; t->child[1] = right;
        update(t);
        return erase(t,e);
    }
    int lower_bound(np t, const T &key){
        if (!t) return 0;
        if (key <= t->key) return lower_bound(t->child[0],key);
        return lower_bound(t->child[1],key)+weight(t->child[0])+1;
    }
    int upper_bound(np t, const T &key){
        if (!t) return 0;
        if (key < t->key) return upper_bound(t->child[0],key);
        return upper_bound(t->child[1],key)+weight(t->child[0])+1;
    }
    T get(np t, int k){
        assert(t);
        int c=weight(t->child[0]), dir=k>c;
        if (c==k) return t->key;
        return get(t->child[dir], k-dir*(c+1));
    }
public:
    RichMultiSet(int n,F f=[](T a,T b){return a+b;},T e=0):n(n),buf(n),ptr(0),root(nullptr),f(f),e(e){}
    inline bool empty(){return !root;}
    inline int size(){return weight(root);}
    inline int lower_bound(const T &key){return lower_bound(root,key);}
    inline int upper_bound(const T &key){return upper_bound(root,key);}

    int count(const T &key){return upper_bound(root,key)-lower_bound(root,key);}
    void insert(const T &key){root = insert(root,lower_bound(root,key),key,xorshift());}
    void erase(const T &key){root = erase(root,key);}
    T query(int a, int b){
        auto p = split(root,a);
        auto q = split(p.second,b-a);
        T ret = sum(q.first);
        root = merge(p.first, merge(q.first, q.second));
        return ret;
    }
    inline T operator[](int k){return get(root,k);}
};

template <class T>
class RichSet : public RichMultiSet<T>
{
private:
    using RichMultiSet<T>::count;
    using RichMultiSet<T>::root;
    using RichMultiSet<T>::insert;
    using RichMultiSet<T>::xorshift;
    using RichMultiSet<T>::lower_bound;
public:
    using RichMultiSet<T>::RichMultiSet;
    void insert(const T &key){
        if (count(key)) return;
        root = insert(root,lower_bound(root,key),key,xorshift());
    }
};
