//-------------------------------------------------
//--Decimal Integer Read & Parse
//-------------------------------------------------
template<class T=long long>
T read_decimal(T excess){
    string s; cin>>s;
    auto pos=s.find('.');
    if (pos!=string::npos){
        T res=stoll(s.substr(0,pos))*excess;
        string t=s.substr(pos+1);
        for(auto c:t){
            excess/=10;
            res+=excess*(c-'0');
        }
        return res;
    }
    return stoll(s)*excess;
}