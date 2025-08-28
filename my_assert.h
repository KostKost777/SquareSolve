#ifndef my_assert
#define my_assert

#ifndef NMA
#define DETAIL_ASSERT(condition)                            \
if(!(condition)) {                                            \
    printf( "Сработал Assert:\n"                            \
            "В файле %s\n"                                  \
            "В функции %s\n"                                \
            "В %d строке\n"                                 \
            "Не выполнилось условие: " #condition           \
            "\nПрограмма завершена\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    action;                                                 \
}

#define FUNCTIONAL_ASSERT(condition, action)                \
if(!(condition)) {                                            \
    printf( "Сработал Assert:\n"                            \
            "В файле %s\n"                                  \
            "В функции %s\n"                                \
            "В %d строке\n"                                 \
            "Не выполнилось условие: " #condition           \
            "\nВыполнено дейстие: " #action                 \
            "\nПрограмма завершена\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    action;                                                 \
}

#else

#define DETAIL_ASSERT(condition)
#define FUNCTIONAL_ASSERT(condition, action)

#endif // my_assert
#endif // DETAIL_ASSERT
