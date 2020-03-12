//-------------------------------------------------
//--Polygon (depends on Geometry Template)
//-------------------------------------------------

//anti-clockwise
struct Polygon {
    vector<V> ps; int n;
    Polygon():n(0){}
    Polygon(int n):n(n),ps(n){}
    void push(const V &v){ps.push_back(v), n++;}
    void pop(){ps.pop_back(), n--;}
    V& operator[](int k){return ps[k%n];}
};

lf area(Polygon &p){
    lf ret=0;
    for(int i=0; i<p.n; i++)
        ret+=det(p[i],p[i+1])/2;
    return ret;
}

V gravity(Polygon &p){
    V ret(0,0); lf wsum=0.0;
    for(int i=0; i<p.n; i++){
        lf w = det(p[i],p[i+1]);
        ret+=(p[i]+p[i+1])*w;
        wsum+=w;
    }
    return ret/wsum/3;
}

bool convex(Polygon &p){
    for(int i=0; i<p.n; i++)
        if (sgn(det(p[i]-p[i+1],p[i+1]-p[i+2]))<0) return false;
    return true;
}

Polygon convex_full(vector<V> &ps){
    Polygon ret;
    sort(ps.begin(), ps.end());
    for(int i=0; i<ps.size(); i++){
        while(ret.n>1 && sgn(det(ret[ret.n-1]-ret[ret.n-2],ps[i]-ret[ret.n-1]))<=0) ret.pop();
        ret.push(ps[i]);
    }
    for(int i=ps.size()-2, t=ret.n; i>=0; i--){
        while(ret.n>t && sgn(det(ret[ret.n-1]-ret[ret.n-2],ps[i]-ret[ret.n-1]))<=0) ret.pop();
        ret.push(ps[i]);
    }
    ret.pop();
    return ret;
}

lf diameter(Polygon &p){
    if (p.n==2) return distance(p[0],p[1]);
    lf ret=0;
    int s=0,t=0;
    for(int i=0; i<p.n; i++)
        if (p[t]<p[i]) t = i;
    int ed=t;
    while(s!=ed || t!=p.n){
        chmax(ret, distance(p[s],p[t]));
        (sgn(det(p[s+1]-p[s], p[t]-p[t+1]))>0)? s++ : t++;
    }
    return ret;
}

Polygon convex_cut(Polygon &p, Line &l){
    Polygon ret;
    for(int i=0; i<p.n; i++){
        if (ccw(l.p,l.q,p[i])!=-1) ret.push(p[i]);
        if (ccw(l.p,l.q,p[i])*ccw(l.p,l.q,p[i+1])==-1){
            Segment s(p[i+1],p[i]);
            ret.push(cpoint(l,s));
        }
    }
    return ret;
}

// OUT=0, ON=1, IN=2
int contain(Polygon &p, const V &v){
    int ret=0;
    for(int i=0; i<p.n; i++){
        V a=p[i]-v, b=p[i+1]-v;
        if (a.y>b.y) swap(a,b);
        if (sgn(a.y)<0 && sgn(b.y)>=0 && sgn(det(a,b))<0) ret=2-ret;
        if (EQ(det(a,b),0.0) && dot(a,b)<0) return 1;
    }
    return ret;
}

// OUT=0, ON=1, IN=2
int convex_contain(Polygon &p, V &v){
    V g = (p[0]+p[p.n/3]+p[p.n*2/3])/3;
    int lo=0, hi=p.n;
    while(hi-lo>1){
        int c=(lo+hi)/2;
        if (sgn(det(p[lo]-g,p[c]-g))>0){
            (sgn(det(p[lo]-g,v-g))>0 && sgn(det(p[c]-g,v-g))<0)? hi=c: lo=c;
        }else{
            (sgn(det(p[lo]-g,v-g))<0 && sgn(det(p[c]-g,v-g))>0)? lo=c: hi=c;
        }
    }
    return sgn(det(p[lo]-v,p[hi]-v))+1;
}

lf carea(Polygon &p, Circle &c){
    lf ret=0;
    for(int i=0; i<p.n; i++){
        lf da = distance(p[i],c.p);
        lf db = distance(p[i+1],c.p);
        Segment s(p[i],p[i+1]);
        auto cps = cpoint(c,s);
        if (sgn(max(da,db)-c.r)<=0){
            ret+=det(p[i]-c.p,p[i+1]-c.p)/2;
        }else if(cps.empty()){
            lf t = acos(dot((p[i]-c.p).unit(),(p[i+1]-c.p).unit()));
            t *= sgn(det(p[i]-c.p,p[i+1]-c.p));
            ret+=c.area(t);
        }else{
            if (cps.size()==1) cps.push_back(cps[0]);
            ret+=det(cps[1]-c.p,cps[0]-c.p)/2;
            if (sgn(da-c.r)<=0) ret+=det(s.p-c.p,cps[1]-c.p)/2;
            else{
                lf t = acos(dot((s.p-c.p).unit(),(cps[1]-c.p).unit()));
                t *= sgn(det(s.p-c.p,cps[1]-c.p));
                ret+=c.area(t);
            }
            if (sgn(db-c.r)<=0) ret+=det(cps[0]-c.p,s.q-c.p)/2;
            else{
                lf t = acos(dot((cps[0]-c.p).unit(),(s.q-c.p).unit()));
                t *= sgn(det(cps[0]-c.p,s.q-c.p));
                ret+=c.area(t);
            }
        }
    }
    return ret;
}
