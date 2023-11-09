#pragma once
#include <iostream>
#include <locale>

struct ThousandSeparatorLocale : public std::numpunct<char>
{
public:
    static void Setup()
    {
        std::locale comma_locale(std::locale(), new ThousandSeparatorLocale());
        std::cout.imbue(comma_locale);
    }
protected:
    char do_thousands_sep() const override { return ','; }
    std::string do_grouping() const override { return "\03"; }
};
