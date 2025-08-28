#ifndef my_assert
#define my_assert

#ifndef NMA
#define DETAIL_ASSERT(condition)                            \
if(!(condition)) {                                            \
    printf( "�������� Assert:\n"                            \
            "� ����� %s\n"                                  \
            "� ������� %s\n"                                \
            "� %d ������\n"                                 \
            "�� ����������� �������: " #condition           \
            "\n��������� ���������\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    action;                                                 \
}

#define FUNCTIONAL_ASSERT(condition, action)                \
if(!(condition)) {                                            \
    printf( "�������� Assert:\n"                            \
            "� ����� %s\n"                                  \
            "� ������� %s\n"                                \
            "� %d ������\n"                                 \
            "�� ����������� �������: " #condition           \
            "\n��������� �������: " #action                 \
            "\n��������� ���������\n",                      \
             __FILE__, __PRETTY_FUNCTION__, __LINE__);      \
    action;                                                 \
}

#else

#define DETAIL_ASSERT(condition)
#define FUNCTIONAL_ASSERT(condition, action)

#endif // my_assert
#endif // DETAIL_ASSERT
