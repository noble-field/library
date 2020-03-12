//-------------------------------------------------
//--Circle (depends on Geometry Template)
//-------------------------------------------------

struct Circle {
    V p; lf r;
    Circle(){}
    Circle(const V &v, lf r):p(v),r(r){}
    Circle(const Circle &c):p(c.p),r(c.r){}
    lf area(){return r*r*PI;}
    lf area(lf t){return r*r*t/2;}
};

// functons about circles
bool contain(Circle &c, V &v){return sgn(distance(v,c.p)-c.r)<=0;}
bool contain(Circle &c, Segment &s){
    return sgn(max(distance(s.p,c.p),distance(s.q,c.p))-c.r)<=0;
}
bool insec(Circle &c, Line &l){return sgn(distance(l,c.p)-c.r)<=0;}
bool insec(Circle &c, Segment &s){
    return sgn(distance(s,c.p)-c.r)<=0 && sgn(max(distance(s.p,c.p),distance(s.q,c.p))-c.r)>=0;
}

vector<V> cpoint(Circle &a, Circle &b){
    vector<V> ret;
    V ab(b.p-a.p);
    lf d = ab.norm(), dd = ab.sq();
    lf c = (a.r*a.r+dd-b.r*b.r)/(2.0*a.r*d);
    if (sgn(abs(c)-1.0)>0) return ret;
    if (EQ(abs(c),1.0)){
        c = (c>0)?1:-1;
        ret.push_back(a.p+ab.unit().rot(c,0)*a.r);
    }else{
        lf s = sqrt(1.0-c*c);
        ret.push_back(a.p+ab.unit().rot(c,s)*a.r);
        ret.push_back(a.p+ab.unit().rot(c,-s)*a.r);
    }
    return ret;
}

vector<V> cpoint(Circle &c, Line &l){
    vector<V> ret;
    lf d = distance(l,c.p);
    if (sgn(d-c.r)>0) return ret;
    V h = ppfoot(l,c.p);
    if (EQ(d,c.r)){
        ret.push_back(h);
    }else{
        V r = (l.q-l.p).unit()*sqrt(c.r*c.r-d*d);
        ret.push_back(h+r);
        ret.push_back(h-r);
    }
    return ret;
}

vector<V> cpoint(Circle &c, Segment &s){
    vector<V> ret,cand;
    cand = cpoint(c,(Line&)s);
    for(auto p:cand)if(sgn(dot(s.p-p,s.q-p))<=0)
        ret.push_back(p);
    return ret;
}

vector<V> tangent(Circle &c, const V &v){
    lf rr=(c.p-v).sq()-c.r*c.r;
    if (sgn(rr)<0) return vector<V>();
    Circle c2(v,sqrt(rr));
    return cpoint(c,c2);
}

vector<V> tangent(Circle &a, Circle &b){
    vector<V> ret, t;
    ret = tangent(a, subdiv(a.p,b.p,a.r,b.r));
    if (!EQ(a.r,b.r)){
        t = tangent(a, outside(a.p,b.p,a.r,b.r));
    }else{
        V r = (b.p-a.p).unit().rot90()*a.r;
        t.push_back(a.p+r);
        t.push_back(a.p-r);
    }
    for(auto p:t) ret.push_back(p);
    return ret;
}

vector<Line> tangent_line(Circle &c, const V &v){
    vector<Line> ret;
    auto t = tangent(c,v);
    for(auto p:t) ret.push_back(Line(v,p));
    return ret;
}

vector<Line> tangent_line(Circle &a, Circle &b){
    vector<Line> ret,t;
    ret = tangent_line(a, subdiv(a.p,b.p,a.r,b.r));
    if (!EQ(a.r,b.r)){
        t = tangent_line(a, outside(a.p,b.p,a.r,b.r));
    }else{
        V r = (b.p-a.p).unit().rot90()*a.r;
        t.push_back(Line(a.p+r, b.p+r));
        t.push_back(Line(a.p-r, b.p-r));
    }
    for(auto l:t) ret.push_back(l);
    return ret;
}

lf carea(Circle &a, Circle &b){
    lf d = distance(a.p,b.p);
    if (sgn(d+a.r-b.r)<=0) return a.area();
    if (sgn(d+b.r-a.r)<=0) return b.area();
    auto cps = cpoint(a,b);
    if (cps.size()<2) return 0.0;
    lf t1 = acos(dot((cps[1]-a.p).unit(),(cps[0]-a.p).unit()));
    if (sgn(det(cps[1]-a.p,cps[0]-a.p))<0) t1=2*PI-t1;
    lf t2 = acos(dot((cps[0]-b.p).unit(),(cps[1]-b.p).unit()));
    if (sgn(det(cps[0]-b.p,cps[1]-b.p))<0) t2=2*PI-t2;
    return a.area(t1)+b.area(t2)-d*(cps[1]-cps[0]).norm()/2;
}
