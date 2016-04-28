#ifndef DSML_ENDIAN_POLICIES_HPP_INCLUDED
#define DSML_ENDIAN_POLICIES_HPP_INCLUDED

namespace dsml
{
namespace conversion
{

enum endianness
    {
    little_endian,
    big_endian
    };

namespace detail
{
template<typename T, int size>
struct swap_endian
    {
    inline T operator()(T arg)
        {
        //TODO: add exception throwing mechanism, perhaps?
        }
    };

template<typename T>
struct swap_endian<T, 1>
    {
    inline T operator()(T arg)
        {
        return arg;
        }
    };

template<typename T>
struct swap_endian<T, 2>
    {
    inline T operator()(T arg)
        {
        return ((((arg) >> 8) & 0xFF) | (((arg) & 0xFF) << 8));
        }
    };

template<typename T>
struct swap_endian<T, 4>
    {
    inline T operator()(T arg)
        {
        return ((((arg) & 0xFF000000) >> 24) | (((arg) & 0x00FF0000) >>  8) |
                (((arg) & 0x0000FF00) <<  8) | (((arg) & 0x000000FF) << 24));
        }
    };

template<typename T>
struct swap_endian<T, 8>
    {
    inline T operator()(T arg)
        {
        return ((((arg) & 0xFF00000000000000ull) >> 56) | (((arg) & 0x00FF000000000000ull) >> 40) |
                (((arg) & 0x0000FF0000000000ull) >> 24) | (((arg) & 0x000000FF00000000ull) >> 8 ) |
                (((arg) & 0x00000000FF000000ull) << 8 ) | (((arg) & 0x0000000000FF0000ull) << 24) |
                (((arg) & 0x000000000000FF00ull) << 40) | (((arg) & 0x00000000000000FFull) << 56));
        }
    };

template<typename T, endianness to, endianness from>
struct do_swap
    {
    inline T operator()(T arg)
        {
        return swap_endian<T, sizeof(T)>()(arg);
        }
    };

template<typename T>
struct do_swap<T, little_endian, little_endian>
    {
    inline T operator()(T arg)
        {
        return arg;
        }
    };

template<typename T>
struct do_swap<T, big_endian, big_endian>
    {
    inline T operator()(T arg)
        {
        return arg;
        }
    };
}

endianness get_endianness()
    {
    const int i = 0x12345678;
    char * p = (char*)&i;
    return ((*(p)) == 0x12) ? big_endian : little_endian;
    }

template<typename T, endianness to, endianness from>
inline T b_swap(T arg)
    {
    return detail::do_swap<T, to, from>()(arg);
    }

template<typename T>
T to_big_endian(T arg)
    {
    if (get_endianness() == little_endian)
        {
        return b_swap<T, big_endian, little_endian>(arg);
        }
    return arg;
    }

template<typename T>
T to_little_endian(T arg)
    {
    if (get_endianness() == big_endian)
        {
        return b_swap<T, little_endian, big_endian>(arg);
        }
    return arg;
    }

template<typename T, endianness from>
T to_host_endian(T arg)
    {
    endianness host = get_endianness();
    if (host == from)
        {
        return arg;
        }
    if (from == little_endian)
        {
        return b_swap<T, big_endian, little_endian>(arg);
        }
    if (from == big_endian)
        {
        return b_swap<T, little_endian, big_endian>(arg);
        }
    }

}
} //namespace dsml::conversion

#endif