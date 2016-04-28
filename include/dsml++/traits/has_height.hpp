#ifndef DSML_TRAITS_HAS_HEIGHT_HPP_INCLUDED
#define DSML_TRAITS_HAS_HEIGHT_HPP_INCLUDED

namespace dsml
{

///Template struct to determine whether T has tile height info.
template<typename T>
struct has_height
    {

    static const bool value = false;

    typedef has_height<T> type;

    };

} //namespace dsml

#endif