#ifndef DSML_TRAITS_IS_TILE_HPP_INCLUDED
#define DSML_TRAITS_IS_TILE_HPP_INCLUDED

namespace dsml
{

///Template struct to determine whether T is a tile.
template<typename T>
struct is_tile
    {

    static const bool value = false;

    typedef is_tile<T> type;

    };

} //namespace dsml

#endif