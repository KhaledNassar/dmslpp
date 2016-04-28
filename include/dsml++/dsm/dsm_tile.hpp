#ifndef DSML_DSM_TILE_HPP_INCLUDED
#define DSML_DSM_TILE_HPP_INCLUDED

#include <dsml++/traits/tile_traits.hpp>
#include <dsml++/traits/has_height.hpp>
#include <dsml++/traits/has_portal.hpp>
#include <dsml++/traits/is_tile.hpp>

namespace dsml
{

///dsm_tile class declaration.
class dsm_tile
    {
    public:
        ///typedef for the int_type.
        typedef unsigned short int_type;

        ///typedef for the flag_type.
        typedef unsigned char  flag_type;

        ///The flags enumeration
        enum { invalid_flag = 1, portal_flag = 2 };

        ///Returns true if the tile has the invalid_flag set.
        inline bool const invalid() const
            {
            return (m_flags == invalid_flag);
            }

        ///Returns true if the tile has the portal_flag set.
        inline bool const portal() const
            {
            return (m_flags == portal_flag);
            }

        ///Set the flag of the tile.
        inline void flag(flag_type flag)
            {
            m_flags = flag;
            }

        ///Returns the flag of the tile.
        inline flag_type flag() const
            {
            return m_flags;
            }

        ///Sets the height of the tile.
        inline void height(int_type height)
            {
            m_height = height;
            }

        ///Returns the height of the tile.
        inline int_type height() const
            {
            return m_height;
            }

    protected:

        flag_type m_flags;
        int_type  m_height;
    };

///tile_traits specialization for dsm_tile.
template<>
struct tile_traits<dsm_tile>
    {
    typedef dsm_tile::int_type int_type;
    typedef dsm_tile::flag_type flag_type;
    };

///is_tile specialization for dsm_tile.
template<>
struct is_tile<dsm_tile>
    {
    static const bool value = true;
    typedef is_tile<dsm_tile> type;
    };

///has_height specialization for dsm_tile.
template<>
struct has_height<dsm_tile>
    {
    static const bool value = true;
    };

///has_portal specialization for dsm_tile.
template<>
struct has_portal<dsm_tile>
    {
    static const bool value = true;
    };

} //namespace dsml

#endif
