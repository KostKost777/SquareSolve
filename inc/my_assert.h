#ifndef MY_ASSERT
#define MY_ASSERT

#ifndef NMA

#define DETAIL_ASSERT(condition)                            \
if (!(condition))                                             \
{                                                            \
    printf( "Deatil Assert:\n"                            \
            "In File %s\n"                                  \
            "In Func %s\n"                                \
            "on %d line\n"                                 \
            "wrong expression: " #condition           \
            "\naborting...\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);                                               \
}

#define FUNCTIONAL_ASSERT(condition, action)                \
if (!(condition))                                           \
{                                                            \
    printf( "Functional Assert:\n"                            \
            "In File %s\n"                                  \
            "In Func %s\n"                                \
            "on %d line\n"                                 \
            "wrong expression: " #condition           \
            "\nDone action: " #action                 \
            "\naborting...\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    action;                                                 \
}

#else

#define DETAIL_ASSERT(condition)
#define FUNCTIONAL_ASSERT(condition, action)

#endif
#endif