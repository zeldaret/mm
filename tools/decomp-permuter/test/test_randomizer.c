void foo(void);
void bar(void);

#ifdef ACTUAL
void test_randomizer(void) {
    foo();
    bar();
}
#else
void test_randomizer(void) {
    PERM_RANDOMIZE(
    bar();
    foo();
    )
}
#endif
