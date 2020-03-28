//-------------------------------------------------
//--Manacher Algorithm
//-------------------------------------------------
template <class T>
vector<int> Manacher(const T &s){
    int n = s.size();
    vector<int> ret(n);
    int i=0, j=0;
    while(i<n){
        while(i-j>=0 && i+j<n && s[i-j]==s[i+j]) j++;
        ret[i] = j;
        int k=1;
        while(i-k>0 && k+ret[i-k]<j) ret[i+k]=ret[i-k], k++;
        i+=k; j-=k;
    }
    return ret;
}
