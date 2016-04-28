#ifndef DSML_IOSTREAMS_BYTE_STREAMS_HPP_INCLUDED
#define DSML_IOSTREAMS_BYTE_STREAMS_HPP_INCLUDED

#include <iostream>

namespace dsml
{
namespace iostreams
{

namespace detail
{
template<typename T, typename Traits>
class basic_byte_stream;
}

typedef detail::basic_byte_stream< char, std::char_traits<char> > byte_stream;
typedef detail::basic_byte_stream< wchar_t, std::char_traits<wchar_t> > wbyte_stream;

}
} //namespace dsml::iostreams

#include <dsml++/iostreams/detail/detail.hpp>

#endif