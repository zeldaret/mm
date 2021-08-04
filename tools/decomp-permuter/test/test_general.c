#ifdef ACTUAL
int test_general() {
    return 64;
}
#else
int test_general() {
    return PERM_GENERAL(32,64);
}
#endif

#ifdef ACTUAL
int test_general_3() {
    return 64;
}
#else
int test_general_3() {
    return PERM_GENERAL(32,48,64);
}
#endif

#ifdef ACTUAL
int test_general_multiple() {
    return 9;
}
#else
int test_general_multiple() {
    return PERM_GENERAL(1,2,3) + PERM_GENERAL(4,5,6);
} 
#endif