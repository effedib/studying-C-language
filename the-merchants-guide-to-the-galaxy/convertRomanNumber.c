#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "convertRomanNumber.h"

int romanValue(char roman)
{
    switch (roman)
    {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}

int convertRomanNumber(char *roman)
{
    int len = strlen(roman) - 1;
    int result = 0, prevValue = 0;

    for (int i = len; i >= 0; i--)
    {
        int currentValue = romanValue(toupper(roman[i]));
        if (currentValue >= prevValue)
            result += currentValue;
        else
            result -= currentValue;
        prevValue = currentValue;
    }

    return result;
}
