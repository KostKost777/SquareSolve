#ifndef my_assert
#define my_assert

#ifndef NMA
#define DETAIL_ASSERT(condition)                            \
if (!(condition))                                             \
{                                                            \
    printf( "Детальный Assert:\n"                            \
            "в файле %s\n"                                  \
            "в функции %s\n"                                \
            "на %d строке\n"                                 \
            "проваленное условие: " #condition           \
            "\nпринудительный останов\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);      \                                                 \
}

#define FUNCTIONAL_ASSERT(condition, action)                \
if (!(condition))                                           \
{                                                            \
    printf( "Функциональный Assert:\n"                            \
            "в файле %s\n"                                  \
            "в функции %s\n"                                \
            "на %d строке\n"                                 \
            "проваленное условие: " #condition           \
            "\nвыполняемое действие: " #action                 \
            "\nпринудительный останов\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    action;                                                 \
}

#else

#define DETAIL_ASSERT(condition)
#define FUNCTIONAL_ASSERT(condition, action)

#endif NMA
#endif my_assert