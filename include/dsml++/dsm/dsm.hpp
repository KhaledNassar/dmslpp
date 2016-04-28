#ifndef DSML_DSM_HPP_INCLUDED
#define DSML_DSM_HPP_INCLUDED

#include <dsml++/dsm/dsm_tile.hpp>
#include <dsml++/basic_map.hpp>
#include <dsml++/traits/is_map.hpp>
#include <dsml++/conversion/endian.hpp>
#include <dsml++/dsm/detail/dsm_algorithm.hpp>
#include <dsml++/serialization/serialization.hpp>

namespace dsml
{

///Definition of dsm_map type.
typedef basic_map<dsm_tile> dsm_map;

///is_map template specialization for dsm_map type.
template<>
struct is_map<dsm_map>
    {
    static const bool value = true;
    typedef is_map<dsm_map> type;
    };

namespace serialization
{
namespace detail
{
template<
typename ostream,
typename map_type
>
struct map_detail_deserialize_stream<dsm_tile, ostream, map_type>
    {
    inline bool operator()(map_type& map, ostream& stream)
        {
        return dsml::detail::dsm_deserialize_stream(map, stream);
        }
    };

template<
typename istream,
typename map_type
>
struct map_detail_serialize_stream<dsm_tile, istream, map_type>
    {
    inline bool operator()(map_type& map, istream& stream)
        {
        return dsml::detail::dsm_serialize_stream(map, stream);
        }
    };

} //namespace detail
} //namespace serialization

} //namespace dsml

#endif
