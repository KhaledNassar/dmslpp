#ifndef DSML_BASIC_ROW_HPP_INCLUDED
#define DSML_BASIC_ROW_HPP_INCLUDED

#include <dsml++/traits/is_tile.hpp>
#include <dsml++/traits/tile_traits.hpp>
#include <vector>

namespace dsml
{

///The basic_row template class.
template<
typename TileT,
typename TileContainerT = std::vector<TileT>
>
class basic_row
    {
    public:

        ///Definition for the tile type.
        typedef TileT tile_type;

        ///Definition for the tile traits type.
        typedef tile_traits<tile_type> traits_type;

        ///Definition for the tile container type.
        typedef TileContainerT container_type;

        ///Definition for the int type of the tile traits.
        typedef typename traits_type::int_type int_type;

        ///Sets the tile at loc to tile.
        inline void tile(int_type loc, tile_type& tile)
            {
            m_container.at(loc) = tile;
            }

        ///Returns a const reference to the tile at loc.
        inline tile_type const& tile(int_type loc) const
            {
            return m_container.at(loc);
            }

        ///Returns a reference to the tile at loc.
        inline tile_type& tile(int_type loc)
            {
            return m_container.at(loc);
            }

        ///Explicit constructor to construct a row from count tiles.
        explicit basic_row(int_type count)
                : m_container(count)
            {
            if (!is_tile<tile_type>::value)
                {
                throw "not a valid tile type";
                }
            }

    protected:

        container_type m_container;
    };

} //namespace dsml::row

#endif
