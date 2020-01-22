//-------------------------------------------------
//--Extended GCD
//-------------------------------------------------

int_fast64_t extgcd(int_fast64_t a, int_fast64_t b, int_fast64_t &x, int_fast64_t &y)
{
    if (b==0){
        x = 1; y = 0;
        return a;
    }
    int_fast64_t d = extgcd(b,a%b,y,x);
    y -= a/b*x;
    return d;
}
