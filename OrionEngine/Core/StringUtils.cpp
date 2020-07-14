#include "BgStringUtils.h"
#include <cstdarg>
#include <sstream>
#include <codecvt>

std::string BgStringUtils::Format(const char * fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    char *buf = new char[_vscprintf(fmt, ap) + 1];
    vsprintf(buf, fmt, ap);

    va_end(ap);

    std::string str = buf;

    delete[] buf;

    return str;
}

int BgStringUtils::Scan(const std::string &str, const char * fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int ret = vsscanf(str.data(), fmt, ap);
    va_end(ap);

    return ret;
}

std::smatch BgStringUtils::RegexScan(const std::string &str, const char *fmt) {
    std::regex rx(fmt);
    std::smatch match;
    std::regex_match(str, match, rx);

    return match;
}

std::vector<std::string> BgStringUtils::Split(const std::string &str, char separator) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> tokens;

    if (Contains(str, BgStringUtils::Format("%c", separator))) {
        while (std::getline(ss, item, separator)) {
            if (!item.empty() && item != str)
                tokens.push_back(item);
        }
    }
    else
        tokens.push_back(str);

    return tokens;
}

std::string BgStringUtils::BeforeFirst(const std::string & str, char separator) {
    return str.substr(0, str.find_first_of(separator));
}

std::string BgStringUtils::BeforeLast(const std::string & str, char separator) {
    return str.substr(0, str.find_last_of(separator));
}

std::string BgStringUtils::AfterFirst(const std::string & str, char separator) {
    return str.substr(str.find_first_of(separator) + 1);
}

std::string BgStringUtils::AfterLast(const std::string & str, char separator) {
    return str.substr(str.find_last_of(separator) + 1);
}

std::string BgStringUtils::SubStr(const std::string &str, char leftSeparator, char rightSeparator) {
    uint offset = str.find_first_of(leftSeparator) + 1;
    uint count = str.find_last_of(rightSeparator) - offset;

    return str.substr(offset, count);
}

bool BgStringUtils::Contains(const std::string & str, const std::string & findStr, bool caseSensitive) {
    if (caseSensitive)
        return str.find(findStr) != str.npos;
    else
        return Lower(str).find(Lower(findStr)) != std::string::npos;
}

bool BgStringUtils::Compare(const std::string & str1, const std::string & str2, bool caseSensetive) {
    return _stricmp(str1.data(), str2.data()) == 0;
}

std::wstring BgStringUtils::ToWideString(const std::string & str) {
    size_t len = str.length() + 1;
    wchar_t* wc = new wchar_t[len];
    mbstowcs(wc, str.data(), len);
    std::wstring buf = wc;
    delete[] wc;

    return buf;
}

std::string BgStringUtils::Utf8ToCp1251(const std::string &utf8str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> wconv;
    std::wstring wstr = wconv.from_bytes(utf8str);

    std::vector<char> buf(wstr.size());
    std::use_facet<std::ctype<wchar_t>>(std::locale(".1251")).narrow(wstr.data(), wstr.data() + wstr.size(), '?', buf.data());

    return std::string(buf.data(), buf.size());
}

std::string BgStringUtils::Upper(const std::string & str) {
    std::string out;
    out.resize(str.size());
    std::transform(str.begin(), str.end(), out.begin(), toupper);

    return out;
}

std::string BgStringUtils::Lower(const std::string & str) {
    std::string out;
    out.resize(str.size());
    std::transform(str.begin(), str.end(), out.begin(), tolower);

    return out;
}

uint BgStringUtils::GetHash(const std::string & str) {
    return std::hash<std::string>()(str);
}

bool BgStringUtils::ToBool(const std::string & str) {
    return Compare(str, "true", false);
}

int BgStringUtils::ToInt(const std::string & str) {
    return atoi(str.data());
}

float BgStringUtils::ToFloat(const std::string & str) {
    return atof(str.data());
}

double BgStringUtils::ToDouble(const std::string & str) {
    return atof(str.data());
}

std::string BgStringUtils::FromBool(bool val) {
    return val ? "true" : "false";
}

std::string BgStringUtils::FromInt(int val) {
    return std::to_string(val);
}

std::string BgStringUtils::FromFloat(float val) {
    return std::to_string(val);
}

std::string BgStringUtils::FromDouble(double val) {
    return std::to_string(val);
}