#ifndef DSML_BASIC_MAP_DEC_HPP_INCLUDED
#define DSML_BASIC_MAP_DEC_HPP_INCLUDED

#include <dsml++/traits/tile_traits.hpp>
#include <dsml++/basic_row.hpp>
#include <vector>
#include <boost/noncopyable.hpp>

namespace dsml
{

///The basic_map template class.
template<
typename TileT,
typename RowT = basic_row<TileT>,
typename RowContainerT = std::vector<RowT>
>
class basic_map
        : private boost::noncopyable
    {
    public:

        ///The type of the tile.
        typedef TileT   tile_type;

        ///The traits type of the tile.
        typedef tile_traits<tile_type> traits_type;

        ///The type of the row used to contain tile.
        typedef RowT    row_type;

        ///The type of the row container.
        typedef RowContainerT    row_container_type;

        ///The integer type of the tile.
        typedef typename traits_type::int_type int_type;

        ///Returns a const reference to the container that holds the rows of the map object.
        inline row_container_type const& container() const
            {
            return m_rows;
            }

        ///Returns a reference to the container that holds the rows of the map object.
        inline row_container_type& container()
            {
            return m_rows;
            }

        ///Returns a const reference to the tile at (x, y).
        inline tile_type const& tile(int_type x, int_type y) const
            {
            return container().at(y).tile(x);
            }

        ///Returns the tile at (x, y).
        inline tile_type& tile(int_type x, int_type y)
            {
            return container().at(y).tile(x);
            }

        ///Returns the height of the map object.
        inline int_type const height() const
            {
            return m_height;
            }

        ///Returns the width of the map object.
        inline int_type const width() const
            {
            return m_width;
            }

        ///Returns true if the map is empty(), false if not.
        inline bool const empty() const
            {
            return m_rows.empty();
            }

        ///Returns the id of the map object.
        inline int_type const id() const
            {
            return m_id;
            }

        ///Sets the tile at (x, y) to t.
        inline void tile(int_type x, int_type y, tile_type& t)
            {
            container().at(y).tile(x) = t;
            }

        ///Sets the height of the map to the specified value, resizing the map if asked to.
        inline void height(int_type val, bool resize = false)
            {
            m_height = val;
            if (resize)
                {
                this->resize(m_height, m_width);
                }
            }

        ///Sets the width of the map to the specified value, resizing the map if asked to.
        inline void width(int_type val, bool resize = false)
            {
            m_width = val;
            if (resize)
                {
                this->resize(m_height, m_width);
                }
            }

        ///Sets the id of the map.
        inline void id(int_type val)
            {
            m_id = val;
            }

        ///Resizes the map object to the specified height and width.
        inline void resize(int_type height, int_type width)
            {
            m_height = height;
            m_width  = width;
            container().resize(height, row_type(width));
            }

        ///Default constructor.
        basic_map()
                : m_height(0)
                , m_width(0)
                , m_id(0)
            {
            }

        ///Construct a basic_map object with specified height and width.
        basic_map(int_type height, int_type width)
            {
            m_rows.resize(height, width);
            }

    protected:

        int_type m_id;
        int_type m_height;
        int_type m_width;
        row_container_type m_rows;
    };

}//namespace dsml
#endif
