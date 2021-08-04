#ifdef ACTUAL
int test_type1(int a, int b) {
    return a / b;
}
#else
int test_type1(int a, int b) {
    return a / PERM_TYPECAST(,unsigned int,float) b;
}
#endif

#ifdef ACTUAL
int test_type2(int a, int b) {
    return a / (unsigned int) b;
}
#else
int test_type2(int a, int b) {
    return a / PERM_TYPECAST(,unsigned int,float) b;
}
#endif

#ifdef ACTUAL
int test_type3(int a, int b) {
    return a / (float) b;
}
#else
int test_type3(int a, int b) {
    return a / PERM_TYPECAST(,unsigned int,float) b;
}
#endif