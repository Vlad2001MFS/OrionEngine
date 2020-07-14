#pragma once
#include "BgCommon.h"
#include <string>
#include <regex>

class BgStringUtils {
	BG_STATIC_CLASS(BgStringUtils)
public:
    static std::string Format(const char * fmt, ...);
    static int Scan(const std::string &str, const char * fmt, ...);
    static std::smatch RegexScan(const std::string &str, const char *fmt);
    static std::vector<std::string> Split(const std::string &str, char separator);
    static std::string BeforeFirst(const std::string &str, char separator);
    static std::string BeforeLast(const std::string &str, char separator);
    static std::string AfterFirst(const std::string &str, char separator);
    static std::string AfterLast(const std::string &str, char separator);
    static std::string SubStr(const std::string &str, char leftSeparator, char rightSeparator);
    static bool Contains(const std::string &str, const std::string &findStr, bool caseSensitive = false);
    static bool Compare(const std::string &str1, const std::string &str2, bool caseSensetive = true);
    static std::wstring ToWideString(const std::string &str);
    static std::string Utf8ToCp1251(const std::string &utf8str);
    static std::string Upper(const std::string &str);
    static std::string Lower(const std::string &str);
    static uint GetHash(const std::string &str);
    static bool ToBool(const std::string &str);
    static int ToInt(const std::string &str);
    static float ToFloat(const std::string &str);
    static double ToDouble(const std::string &str);
    static std::string FromBool(bool val);
    static std::string FromInt(int val);
    static std::string FromFloat(float val);
    static std::string FromDouble(double val);
};