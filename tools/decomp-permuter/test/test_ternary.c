#ifdef ACTUAL
int test_ternary1(int cond) {
    int test;
    if (cond)
        test = 1;
    else
        test = 2;
    return test;
}
#else
int test_ternary1(int cond) {
    int test;
    PERM_TERNARY(test = ,cond,1,2)
    return test;
}
#endif

#ifdef ACTUAL
int test_ternary2(int cond) {
    int test;
    test = cond ? 1 : 2;
    return test;
}
#else
int test_ternary2(int cond) {
    int test;
    PERM_TERNARY(test = ,cond,1,2)
    return test;
}
#endif