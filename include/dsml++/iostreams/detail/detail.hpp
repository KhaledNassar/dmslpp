#ifndef DSML_IOSTREAMS_DETAIL_HPP_INCLUDED
#define DSML_IOSTREAMS_DETAIL_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory.h>
#include <boost/scoped_ptr.hpp>

namespace dsml
{
namespace iostreams
{
namespace detail
{

template<typename T, typename Traits>
class basic_byte_stream
    {
    public:
        typedef T char_type;
        typedef Traits traits_type;

        basic_byte_stream(char_type * raw_buffer, std::size_t length)
                : m_buffer(raw_buffer)
                , m_count(length)
                , r_ptr(0)
                , w_ptr(0) { }

        basic_byte_stream(std::size_t count)
                : m_buffer(new char_type[count])
                , m_count(count)
                , r_ptr(0)
                , w_ptr(0) { }

        inline void read(char_type * dst_buffer, std::size_t count)
            {
            memcpy(dst_buffer, m_buffer.get() + r_ptr, count);
            r_ptr += count;
            }

        inline void write(char_type * src_buffer, std::size_t count)
            {
            memcpy(m_buffer.get() + w_ptr, src_buffer, count);
            w_ptr += count;
            }

        inline std::size_t count()
            {
            return m_count;
            }

        inline char_type * get()
            {
            return m_buffer.get();
            }

        inline char_type * get() const
            {
            return m_buffer.get();
            }

    protected:

        std::size_t m_count;
        std::size_t r_ptr;
        std::size_t w_ptr;
        boost::scoped_ptr<char_type> m_buffer;
    };

}
}
}

#endif
