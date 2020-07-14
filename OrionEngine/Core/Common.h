#pragma once

namespace oe {

//template <size_t S> struct _EnumFlagIntForSize;
//template <> struct _EnumFlagIntForSize<1> { typedef signed char type; };
//template <> struct _EnumFlagIntForSize<2> { typedef signed short type; };
//template <> struct _EnumFlagIntForSize<4> { typedef signed int type; };
//template <class T> struct _EnumFlagSizedInt { typedef typename _EnumFlagIntForSize<sizeof(T)>::type type; };
//
//#define OE_DECL_ENUM_OPS(enumType) \
//    inline enumType operator | (enumType a, enumType b) \
//        { return enumType(((_EnumFlagSizedInt<enumType>::type)a) | ((_EnumFlagSizedInt<enumType>::type)b)); } \
//    inline enumType &operator |= (enumType &a, enumType b) \
//        { return (enumType &)(((_EnumFlagSizedInt<enumType>::type &)a) |= ((_EnumFlagSizedInt<enumType>::type)b)); } \
//    inline enumType operator & (enumType a, enumType b) \
//        { return enumType(((_EnumFlagSizedInt<enumType>::type)a) & ((_EnumFlagSizedInt<enumType>::type)b)); } \
//    inline enumType &operator &= (enumType &a, enumType b) \
//        { return (enumType &)(((_EnumFlagSizedInt<enumType>::type &)a) &= ((_EnumFlagSizedInt<enumType>::type)b)); } \
//    inline enumType operator ~ (enumType a) \
//        { return enumType(~((_EnumFlagSizedInt<enumType>::type)a)); } \
//    inline enumType operator ^ (enumType a, enumType b) \
//        { return enumType(((_EnumFlagSizedInt<enumType>::type)a) ^ ((_EnumFlagSizedInt<enumType>::type)b)); } \
//    inline enumType &operator ^= (enumType &a, enumType b) \
//        { return (enumType &)(((_EnumFlagSizedInt<enumType>::type &)a) ^= ((_EnumFlagSizedInt<enumType>::type)b)); }
#define OE_SAFE_DELETE(obj) { delete (obj); (obj) = nullptr; }
#define OE_SAFE_DELETE_ARRAY(obj) { delete[] (obj); (obj) = nullptr; }
#define OE_ZERO_MEMORY(obj) memset(&(obj), 0, sizeof((obj)))
#define OE_ARRAY_SIZE(obj) (sizeof((obj)) / sizeof((obj)[0]))
#define OE_FLAG_EXIST(flags, flag) (((flags) & (flag)) == (flag))

typedef unsigned int uint;
typedef signed int sint;
typedef unsigned char uchar;
typedef unsigned short ushort;

template<typename T, typename Tag, T DefaultValue>
struct Handle {
    inline explicit Handle(const T &value) : value(value) { }

    inline Handle() { }

    inline Handle(const Handle &h) : value(h.value) { }

    inline Handle &operator=(const Handle &right) {
        this->value = right.value;
        return *this;
    }

    inline Handle &operator=(const T &right) {
        this->value = right;
        return *this;
    }

    inline bool operator==(const Handle &right) const {
        return this->value == right.value;
    }

    inline bool operator!=(const Handle &right) const {
        return this->value != right.value;
    }

    inline friend bool operator==(const Handle &left, const Handle &right) {
        return left.value == right.value;
    }

    inline bool IsValid() const {
        return this->value != static_cast<T>(DefaultValue);
    }

    inline static Handle Invalid() {
        return Handle(static_cast<T>(DefaultValue));
    }

    T value = static_cast<T>(DefaultValue);
};

}