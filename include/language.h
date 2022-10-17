typedef char LATIN;
typedef int KANJI;
typedef int HIRAGANA;
typedef int KATAKANA;

typedef struct  {
    LATIN **hiragana_romanization_lowercase;
    LATIN **hiragana_romanization_uppercase;
    LATIN **hiragana_romanization_mixed;
    HIRAGANA hiragana;
    KATAKANA katakana;
} JAPANESE;