//-------------------------------------------------
//--Triangle (depends on Geometry Template)
//-------------------------------------------------

V gravity(V &a, V &b, V &c){return (a+b+c)/3;}
V circum(V &a, V &b, V &c){
    Line l=vbsector(a,b), m=vbsector(b,c);
    return cpoint(l,m);
}
V inner(V &a, V &b, V &c){
    Line l=absector(c,a,b), m=absector(a,b,c);
    return cpoint(l,m);
}
V ortho(V &a, V &b, V &c){
    Line l=perpend(c,a,b), m=perpend(a,b,c);
    return cpoint(l,m);
}
