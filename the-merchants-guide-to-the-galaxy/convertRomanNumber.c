#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "convertRomanNumber.h"

typedef struct roman_number
{
    char roman_letter;
    int equivalent_number;
} roman_number;

roman_number romans_table[] =
    {{'M', 1000},
     {'D', 500},
     {'C', 100},
     {'L', 50},
     {'X', 10},
     {'V', 5},
     {'I', 1}};

int upper_string(char *source, char *dest, int len1)
{
    for (int i = 0; i < len1; i++)
        dest[i] = toupper((unsigned char)source[i]);

    dest[len1] = '\0';

    int len2 = strlen(dest);

    if (len1 != len2)
    {
        puts("String error!");
        return -1;
    }

    return 0;
}

int roman2int(char roman)
{
    int roman_table_size = sizeof(romans_table) / sizeof(romans_table[0]);
    for (int i = 0; i < roman_table_size; i++)
    {
        if (romans_table[i].roman_letter == roman)
            return romans_table[i].equivalent_number;
    }

    return 0;
}

int parseRomanStr(char *roman, int len)
{
    if (len <= 0)
        return 0;
    if (len == 1)
        return roman2int(*roman);
    else
    {
        int currentRomanInt = roman2int(roman[0]);
        int nextRomanInt = roman2int(roman[1]);
        if (currentRomanInt == 0 || nextRomanInt == 0)
            return 0;
        if (nextRomanInt > currentRomanInt)
            return (nextRomanInt - currentRomanInt) + parseRomanStr(roman + 2, len - 2);

        return currentRomanInt + parseRomanStr(roman + 1, len - 1);
    }
}

int convertRomanNumber(char *roman)
{
    int len = strlen(roman);
    if (len <= 0)
        return 0;

    char roman_copy[len + 1];
    upper_string(roman, roman_copy, len);

    return parseRomanStr(roman_copy, len);
}
