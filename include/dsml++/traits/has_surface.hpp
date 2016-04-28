#ifndef DSML_TRAITS_HAS_SURFACE_HPP_INCLUDED
#define DSML_TRAITS_HAS_SURFACE_HPP_INCLUDED

namespace dsml
{

///Template struct to determine whether T has tile surface info.
template<typename T>
struct has_surface
    {

    static const bool value = false;

    typedef has_surface<T> type;

    };

} //namespace dsml

#endif