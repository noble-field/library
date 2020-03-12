//-------------------------------------------------
//--Popular Geometry Problems (depends on other)
//-------------------------------------------------

Circle enclose_all(vector<V> &ps){
    lf cx,cy;
    auto g = [&](lf x, lf y){
        lf ret=0;
        V v(x,y);
        for(int i=0; i<ps.size(); i++)
            chmax(ret,distance(v,ps[i]));
        return ret;
    };
    auto f = [&](lf x){
        int u=80;
        lf lo=ps[0].y, hi=ps[0].y;
        for(int i=0; i<ps.size(); i++){
            chmin(lo,ps[i].y);
            chmax(hi,ps[i].y);
        }
        while(u--){
            lf c1 = (lo*2+hi)/3;
            lf c2 = (lo+hi*2)/3;
            (g(x,c1)<g(x,c2))? hi=c2 : lo=c1;
        }
        cy = (hi+lo)/2;
        return g(x,cy);
    };
    int t=80;
    lf lo=ps[0].x, hi=ps[0].x;
    for(int i=0; i<ps.size(); i++){
        chmin(lo,ps[i].x);
        chmax(hi,ps[i].x);
    }
    while(t--){
        lf c1 = (lo*2+hi)/3;
        lf c2 = (lo+hi*2)/3;
        (f(c1)<f(c2))? hi=c2 : lo=c1;
    }
    cx = (hi+lo)/2;
    return Circle(V(cx,cy),g(cx,cy));
}
