//-------------------------------------------------
//--Geometry Template (Plane)
//-------------------------------------------------

using lf = double;
const lf EPS = 1e-7;
const lf PI = acos(-1);

#define sgn(x) (((x)<-EPS)?-1:((x)>EPS)?1:0)
#define EQ(x,y) (sgn((y)-(x))==0)

struct V {
    lf x,y;
    V(){}
    V(lf x, lf y):x(x),y(y){}
    V(const V &v):x(v.x),y(v.y){}
    V& operator+=(const V &v){x+=v.x; y+=v.y; return *this;}
    V& operator-=(const V &v){x-=v.x; y-=v.y; return *this;}
    V& operator*=(lf k){x*=k; y*=k; return *this;}
    V& operator/=(lf k){x/=k; y/=k; return *this;}
    V operator+(const V &v){return V(*this)+=v;}
    V operator-(const V &v){return V(*this)-=v;}
    V operator*(lf k){return V(*this)*=k;}
    V operator/(lf k){return V(*this)/=k;}
    V operator-(){return V(-x,-y);}
    lf sq(){return x*x+y*y;}
    lf norm(){return sqrt(sq());}
    V unit(){return V(*this)/=norm();}
    lf arg(){return atan2(y,x);}
    V rot(lf c, lf s){return V(x*c-y*s,x*s+y*c);}
    V rot(lf a){return rot(sin(a),cos(a));}
    V rot90(){return V(-y,x);}
    bool operator<(const V &v){
        if (sgn(x-v.x)) return sgn(x-v.x)<0;
        return sgn(y-v.y)<0;
    }
    friend ostream& operator<<(ostream &os, const V &v){return os<<'('<<v.x<<", "<<v.y<<')';}
};

lf dot(const V &a, const V &b){return a.x*b.x+a.y*b.y;}
lf det(const V &a, const V &b){return a.x*b.y-a.y*b.x;}

int ccw(V a, V b, V c){
    b-=a; c-=a;
    if (sgn(det(b,c))>0) return 1;
    else if(sgn(det(b,c))<0) return -1;
    else if(sgn(dot(b,c))<0) return 2;
    else if(sgn(b.norm()-c.norm())<0) return -2;
    return 0;
}

struct Line {
    V p,q;
    Line(){}
    Line(const V &p, const V &q):p(p),q(q){}
    Line(const Line &l):Line(l.p,l.q){}
    V unit(){return (q-p).unit();}
    lf arg(){return (q-p).arg();}
    Line rot(lf c, lf s){return Line(p.rot(c,s),q.rot(c,s));}
    Line rot(lf a){return Line(p.rot(a),q.rot(a));}
    Line rot90(){return Line(p.rot90(),q.rot90());}
};

struct Segment : Line {
    Segment(){}
    Segment(const V &p, const V &q):Line(p,q){}
    Segment(const Segment &s):Line(s){}
    lf sq(){return (Line::q-Line::p).sq();}
    lf norm(){return (Line::q-Line::p).norm();}
};

// functions about lines
bool parallel(const V &a, const V &b){return EQ(det(a,b),0.0);}
bool parallel(Line &a, Line &b){return EQ(det(a.q-a.p,b.q-b.p),0.0);}
bool orthogonal(const V &a, const V &b){return EQ(dot(a,b),0.0);}
bool orthogonal(Line &a, Line &b){return EQ(dot(a.q-a.p,b.q-b.p),0.0);}

bool samel(Line &a, Line &b){return parallel(a,b)&&EQ(det(a.q-a.p,b.p-a.p),0.0);}
bool insec(Line &a, Line &b){return !parallel(a,b);}
bool insec(Segment &a, Segment &b){
    int c1 = ccw(a.p,a.q,b.p)*ccw(a.p,a.q,b.q);
    int c2 = ccw(b.p,b.q,a.p)*ccw(b.p,b.q,a.q);
    return (c1<=0 && c2<=0);
}
bool insec(Line &a, Segment &b){return ccw(a.p,a.q,b.p)*ccw(a.p,a.q,b.q)<=0;}

// use only if lines have intersection
V cpoint(Line &a, Line &b){
    V r(a.q-a.p);
    r *= det(b.p-a.p,b.q-b.p)/det(a.q-a.p,b.q-b.p);
    return a.p+r;
}

lf distance(V &a, V &b){return (b-a).norm();}
lf distance(Line &l, V &v){return abs(det((l.q-l.p).unit(),v-l.p));}
lf distance(Line &a, Line &b){return (parallel(a,b))?distance(a,b.p):0.0;}
lf distance(Segment &s, V &v){
    if (sgn(dot(s.q-s.p,v-s.p))<0) return distance(s.p,v);
    else if(sgn(dot(s.p-s.q,v-s.q))<0) return distance(s.q,v);
    return distance((Line&)s,v);
}
lf distance(Segment &a, Segment &b){
    if (insec(a,b)) return 0.0;
    lf A=min(distance(a,b.p),distance(a,b.q));
    lf B=min(distance(b,a.p),distance(b,a.q));
    return min(A,B);
}
lf distance(Line &a, Segment &b){
    if (insec(a,b)) return 0.0;
    return min(distance(a,b.p),distance(a,b.q));
}

V subdiv(V &a, V &b, lf m, lf n){return (a*n+b*m)/(m+n);}
V outside(V &a, V &b, lf m, lf n){return (-a*n+b*m)/(m-n);}
V ppfoot(Line &l, V &v){
    V u = (l.q-l.p).unit();
    return l.p+u*dot(u,v-l.p);
}
V reflect(Line &l, V &v){
    V f = ppfoot(l,v);
    return f+(f-v);
}

Line vbsector(V &a, V &b){
    V m = (a+b)/2;
    return Line(m, m+(b-a).rot90());
}
Line absector(V &c, V &a, V &b){
    lf m=(a-c).norm(), n=(b-c).norm();
    return Line(c,subdiv(a,b,m,n));
}
Line perpend(V &c, V &a, V &b){return Line(c,c+(b-a).rot90());}
