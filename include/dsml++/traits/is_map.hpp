#ifndef DSML_TRAITS_IS_MAP_HPP_INCLUDED
#define DSML_TRAITS_IS_MAP_HPP_INCLUDED

namespace dsml
{

///Template struct to determine whether T is a map.
template<typename T>
struct is_map
    {

    static const bool value = false;

    typedef is_map<T> type;
    };

}

#endif