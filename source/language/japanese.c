#include <language.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define none 0

JAPANESE *intialize_japanese_lang() {
    JAPANESE *japanese = malloc(sizeof(JAPANESE));

    char *romanization_lowercase_hiragana[] = {
        {"a",   "i",   "u",   "e",   "o"  },
        {"ka",  "ki",  "ku",  "ke",  "ko" },
        {"sa",  "shi", "su",  "se",  "so" },
        {"ta",  "chi", "tsu", "te",  "to" },
        {"na",  "ni",  "nu",  "ne",  "no" },
        {"ha",  "hi",  "fu",  "he",  "ho" },
        {"ma",  "mi",  "mu",  "me",  "mo" },
        {"ya",  none,  "yu",  none,  "yo" },
        {"ra",  "ri",  "ru",  "re",  "ro" },
        {"wa",  none,  none,  none,  "wo" },
        {"ga",  "gi",  "gu",  "ge",  "go" },
        {"za",  "ji",  "zu",  "ze",  "zo" },
        {"ba",  "bi",  "bu",  "be",  "bo" }, 
        {"pa",  "pi",  "pu",  "pe",  "po" },
        {"kya", none,  "kyu", none,  "kyo"},
        {"sha", none,  "shu", none,  "sho"},
        {"cha", none,  "chu", none,  "cho"},
        {"nya", none,  "nyu", none,  "nyo"},
        {"hya", none,  "hyu", none,  "hyo"},
        {"mya", none,  "myu", none,  "myo"},
        {"rya", none,  "ryu", none,  "ryo"},
        {"jya", none,  "jyu", none,  "jyo"},
        {"gya", none,  "gyu", none,  "gyo"},
        {"bya", none,  "byu", none,  "byo"},
        {"pya", none,  "pyu", none,  "pyo"},
        {"n",   none,  none,  none,  none }
    };

    char *romanization_uppercase_hiragana[] = {
        {"A",   "I",   "U",   "E",   "O"  },
        {"KA",  "KI",  "KU",  "KE",  "KO" },
        {"SA",  "SHI", "SU",  "SE",  "SO" },
        {"TA",  "CHI", "TSU", "TE",  "TO" },
        {"NA",  "NI",  "NU",  "NE",  "NO" },
        {"HA",  "HI",  "FU",  "HE",  "HO" },
        {"MA",  "MI",  "MU",  "ME",  "MO" },
        {"YA",  none,  "YU",  none,  "YO" },
        {"RA",  "RI",  "RU",  "RE",  "RO" },
        {"WA",  none,  none,  none,  "WO" },
        {"GA",  "GI",  "GU",  "GE",  "GO" },
        {"ZA",  "JI",  "ZU",  "ZE",  "ZO" },
        {"BA",  "BI",  "BU",  "BE",  "BO" }, 
        {"PA",  "PI",  "PU",  "PE",  "PO" },
        {"KYA", none,  "KYU", none,  "KYO"},
        {"SHA", none,  "SHU", none,  "SHO"},
        {"CHA", none,  "CHU", none,  "CHO"},
        {"NYA", none,  "NYU", none,  "NYO"},
        {"HYA", none,  "HYU", none,  "HYO"},
        {"MYA", none,  "MYU", none,  "MYO"},
        {"RYA", none,  "RYU", none,  "RYO"},
        {"JYA", none,  "JYU", none,  "JYO"},
        {"GYA", none,  "GYU", none,  "GYO"},
        {"BYA", none,  "BYU", none,  "BYO"},
        {"PYA", none,  "PYU", none,  "PYO"},
        {"n",   none,  none,  none,  none }
    };

    char *romanization_mixed_hiragana[] = {
        {"A",   "I",   "U",   "E",   "O"  },
        {"Ka",  "Ki",  "Ku",  "Ke",  "Ko" },
        {"Sa",  "Shi", "Su",  "Se",  "So" },
        {"Ta",  "Chi", "Tsu", "Te",  "To" },
        {"Na",  "Ni",  "Nu",  "Ne",  "No" },
        {"Ha",  "Hi",  "Fu",  "He",  "Ho" },
        {"Ma",  "Mi",  "Mu",  "Me",  "Mo" },
        {"Ya",  none,  "Yu",  none,  "Yo" },
        {"Ra",  "Ri",  "Ru",  "Re",  "Ro" },
        {"Wa",  none,  none,  none,  "Wo" },
        {"Ga",  "Gi",  "Gu",  "Ge",  "Go" },
        {"Za",  "Ji",  "Zu",  "Ze",  "Zo" },
        {"Ba",  "Bi",  "Bu",  "Be",  "Bo" }, 
        {"Pa",  "Pi",  "Pu",  "Pe",  "Po" },
        {"Kya", none,  "Kyu", none,  "Kyo"},
        {"Sha", none,  "Shu", none,  "Sho"},
        {"Cha", none,  "Chu", none,  "Cho"},
        {"Nya", none,  "Nyu", none,  "Nyo"},
        {"Hya", none,  "Hyu", none,  "Hyo"},
        {"Mya", none,  "Myu", none,  "Myo"},
        {"Rya", none,  "Ryu", none,  "Ryo"},
        {"Jya", none,  "Jyu", none,  "Jyo"},
        {"Gya", none,  "Gyu", none,  "Gyo"},
        {"Bya", none,  "Byu", none,  "Byo"},
        {"Pya", none,  "Pyu", none,  "Pyo"},
        {"n",   none,  none,  none,  none }        
    };

    char *romanization_lowercase_katakana[] = {
        {"a",   "i",   "u",   "e",   "o"  },
        {"ka",  "ki",  "ku",  "ke",  "ko" },
        {"sa",  "shi", "su",  "se",  "so" },
        {"ta",  "chi", "tsu", "te",  "to" },
        {"na",  "ni",  "nu",  "ne",  "no" },
        {"ha",  "hi",  "fu",  "he",  "ho" },
        {"ma",  "mi",  "mu",  "me",  "mo" },
        {"ya",  none,  "yu",  none,  "yo" },
        {"ra",  "ri",  "ru",  "re",  "ro" },
        {"wa",  "wi",  none,  "we",  "wo" },
        {"ga",  "gi",  "gu",  "ge",  "go" },
        {"za",  "ji",  "zu",  "ze",  "zo" },
        {"ba",  "bi",  "bu",  "be",  "bo" }, 
        {"pa",  "pi",  "pu",  "pe",  "po" },
        {"fa",  "fi",  none,  "fe",  "fo" },
        {"va",  "vi",  "vu",  "ve",  "vo" },
        {"kya", none, "kyu",  none,  "kyo"},
        {"sha", none,  "shu", "she", "sho"},
        {"cha", none,  "chu",  "che", "cho"},
        {"nya", none,  "nyu", none,  "nyo"},
        {"hya", none,  "hyu", none,  "hyo"},
        {"mya", none,  "myu", none,  "myo"},
        {"rya", none,  "ryu", none,  "ryo"},
        {"jya", none,  "jyu", none,  "jyo"},
        {"gya", none,  "gyu", none,  "gyo"},
        {"bya", none,  "byu", none,  "byo"},
        {"pya", none,  "pyu", none,  "pyo"},
        {"n",   none,  none,  none,  none },
        {none,  none,  none,  "je",  none }
    };

    char *romanization_uppercase_katakana[] = {
        {"A",   "I",   "U",   "E",   "O"  },
        {"KA",  "KI",  "KU",  "KE",  "KO" },
        {"SA",  "SHI", "SU",  "SE",  "SO" },
        {"TA",  "CHI", "TSU", "TE",  "TO" },
        {"NA",  "NI",  "NU",  "NE",  "NO" },
        {"HA",  "HI",  "FU",  "HE",  "HO" },
        {"MA",  "MI",  "MU",  "ME",  "MO" },
        {"YA",  none,  "YU",  none,  "YO" },
        {"RA",  "RI",  "RU",  "RE",  "RO" },
        {"WA",  "WI",  none,  "WE",  "WO" },
        {"GA",  "GI",  "GU",  "GE",  "GO" },
        {"ZA",  "JI",  "ZU",  "ZE",  "ZO" },
        {"BA",  "BI",  "BU",  "BE",  "BO" }, 
        {"PA",  "PI",  "PU",  "PE",  "PO" },
        {"FA",  "FI",  none,  "FE",  "FO" },
        {"VA",  "VI",  "VU",  "VE",  "VO" },
        {"KYA", none,  "KYU", none,  "KYO"},
        {"SHA", none,  "SHU", "SHE", "SHO"},
        {"CHA", none,  "CHU", "CHE", "CHO"},
        {"NYA", none,  "NYU", none,  "NYO"},
        {"HYA", none,  "HYU", none,  "HYO"},
        {"MYA", none,  "MYU", none,  "MYO"},
        {"RYA", none,  "RYU", none,  "RYO"},
        {"JYA", none,  "JYU", none,  "JYO"},
        {"GYA", none,  "GYU", none,  "GYO"},
        {"BYA", none,  "BYU", none,  "BYO"},
        {"PYA", none,  "PYU", none,  "PYO"},
        {"N",   none,  none,  none,  none },
        {none,  none,  none,  "JE",  none }
    };

    char *romanization_mixed_katakana[] = {
        {"A",   "I",   "U",   "E",   "O"  },
        {"Ka",  "Ki",  "Ku",  "Ke",  "Ko" },
        {"Sa",  "Shi", "Su",  "Se",  "So" },
        {"Ta",  "Chi", "Tsu", "Te",  "To" },
        {"Na",  "Ni",  "Nu",  "Ne",  "No" },
        {"Ha",  "Hi",  "Fu",  "He",  "Ho" },
        {"Ma",  "Mi",  "Mu",  "Me",  "Mo" },
        {"Ya",  none,  "Yu",  none,  "Yo" },
        {"Ra",  "Ri",  "Ru",  "Re",  "Ro" },
        {"Wa",  "Wi",  none,  "We",  "Wo" },
        {"Ga",  "Gi",  "Gu",  "Ge",  "Go" },
        {"Za",  "Ji",  "Zu",  "Ze",  "Zo" },
        {"Ba",  "Bi",  "Bu",  "Be",  "Bo" }, 
        {"Pa",  "Pi",  "Pu",  "Pe",  "Po" },
        {"Fa",  "Fi",  none,  "Fe",  "Fo" },
        {"Va",  "Vi",  "Vu",  "Ve",  "Vo" },
        {"Kya", none,  "Kyu", none,  "Kyo"},
        {"Sha", none,  "Shu", "She", "Sho"},
        {"Cha", none,  "Chu", "Che", "Cho"},
        {"Nya", none,  "Nyu", none,  "Nyo"},
        {"Hya", none,  "Hyu", none,  "Hyo"},
        {"Mya", none,  "Myu", none,  "Myo"},
        {"Rya", none,  "Ryu", none,  "Ryo"},
        {"Jya", none,  "Jyu", none,  "Jyo"},
        {"Gya", none,  "Gyu", none,  "Gyo"},
        {"Bya", none,  "Byu", none,  "Byo"},
        {"Pya", none,  "Pyu", none,  "Pyo"},
        {"N",   none,  none,  none,  none },
        {none,  none,  none,  "Je",  none }
    };

    HIRAGANA *hiragana[] = {
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   none,   "???",   none,   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   none,   none,   none,   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"???",   "???",   "???",   "???",   "???"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"??????", none,   "??????", none, "??????"},
        {"???",   none,   none,  none, none  },
    };

    KATAKANA *katakana[] = {
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   none,   "???",   none,   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "??????", none,   "??????", "???" },
        {"???",   "???",   "???",   "???",    "???"},
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"???",   "???",   "???",   "???",   "???" },
        {"??????", "??????", none,   "??????", "??????"},
        {"??????", "??????", "???",   "??????", "??????"},
        {"??????", none,   "??????", "??????", "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"??????", none,   "??????", none,   "??????"},
        {"???",   none,   none,  none,    none },
        {none,   none,   none,  none,    "??????"},
        
    };

    japanese->hiragana_romanization_lowercase = malloc(sizeof(char) * sizeof(romanization_lowercase_hiragana));
    japanese->hiragana_romanization_uppercase = malloc(sizeof(char) * sizeof(romanization_uppercase_hiragana));
    japanese->hiragana_romanization_mixed     = malloc(sizeof(char) * sizeof(romanization_mixed_hiragana));
    japanese->hiragana                        = malloc(sizeof(char) * sizeof(hiragana));
    japanese->katakana                        = malloc(sizeof(char) * sizeof(katakana));

    memcpy(japanese->hiragana_romanization_lowercase, romanization_lowercase_hiragana, sizeof(romanization_lowercase_hiragana));
    memcpy(japanese->hiragana_romanization_uppercase, romanization_uppercase_hiragana, sizeof(romanization_uppercase_hiragana));
    memcpy(japanese->hiragana_romanization_mixed, romanization_mixed_hiragana, sizeof(romanization_mixed_hiragana));
    memcpy(japanese->hiragana, hiragana, sizeof(hiragana));
    memcpy(japanese->katakana, katakana, sizeof(katakana));

    return japanese;
}

