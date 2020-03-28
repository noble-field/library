//-------------------------------------------------
//--Z-Algorithm
//-------------------------------------------------
template <class T>
vector<int> z_algo(const T &s){
    int n = s.size();
    vector<int> ret(n); ret[0]=n;
    int i=1,j=0;
    while(i<n){
        while(i+j<n && s[i+j]==s[j]) j++;
        ret[i] = j;
        if (j==0){i++; continue;}
        int k = 1;
        while(i+k<n && k+ret[k]<j) ret[i+k]=ret[k], k++;
        i+=k; j-=k;
    }
    return ret;
}
