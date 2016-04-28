#ifndef DSML_SERIALIZATION_DETAIL_DETAIL_HPP_INCLUDED
#define DSML_SERIALIZATION_DETAIL_DETAIL_HPP_INCLUDED

#include <dsml++/traits/is_tile.hpp>
#include <dsml++/traits/is_map.hpp>

namespace dsml
{
namespace serialization
{
namespace detail
{

template<
typename tile_type,
typename ostream,
typename map_type
>
struct map_detail_deserialize_stream
    {
    inline bool operator()(map_type& map, ostream& stream)
        {
        throw "Unknown deserialization algorithm";
        }
    };

template<
typename tile_type,
typename istream,
typename map_type
>
struct map_detail_serialize_stream
    {
    inline bool operator()(map_type& map, istream& stream)
        {
        throw "Unknown serialization algorithm";
        }
    };

template<
typename tile_type,
typename ostream,
typename map_type
>
struct map_deserialize_stream
    {
    inline bool operator()(map_type& map, ostream& stream)
        {
        if (is_tile<tile_type>::type::value)
            {
            if (is_map<map_type>::type::value)
                {
                return map_detail_deserialize_stream<tile_type, ostream, map_type>()(map, stream);
                }
            }
        return false;
        }
    };

template<
typename tile_type,
typename istream,
typename map_type
>
struct map_serialize_stream
    {
    inline bool operator()(map_type& map, istream& stream)
        {
        if (is_tile<tile_type>::type::value)
            {
            if (is_map<map_type>::type::value)
                {
                return map_detail_serialize_stream<tile_type, istream, map_type>()(map, stream);
                }
            }
        return false;

        }
    };

}
}
} //namespace dsml::serialization::detail

#endif
