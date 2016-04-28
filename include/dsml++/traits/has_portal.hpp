#ifndef DSML_TRAITS_HAS_PORTAL_HPP_INCLUDED
#define DSML_TRAITS_HAS_PORTAL_HPP_INCLUDED

namespace dsml
{

///Template struct to determine whether T has tile portal info.
template<typename T>
struct has_portal
    {

    static const bool value = false;

    typedef has_portal<T> type;

    };

} //namespace dsml

#endif