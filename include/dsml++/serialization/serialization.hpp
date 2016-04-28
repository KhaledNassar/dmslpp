#ifndef DSML_SERIALIZATION_HPP_INCLUDED
#define DSML_SERIALIZATION_HPP_INCLUDED

#include <dsml++/serialization/detail/detail.hpp>

namespace dsml
{
namespace serialization
{

template<
typename ostream,
typename map_type
>
struct do_deserialize_stream
    {
    typedef typename map_type::tile_type tile_type;
    inline bool operator()(map_type& map, ostream& stream)
        {
        return detail::map_deserialize_stream<tile_type, ostream, map_type>()(map, stream);
        }
    };

template<
typename istream,
typename map_type
>
struct do_serialize_stream
    {
    typedef typename map_type::tile_type tile_type;
    inline bool operator()(map_type& map, istream& stream)
        {
        return detail::map_serialize_stream<tile_type, istream, map_type>()(map, stream);
        }
    };

template<
typename ostream,
typename map_type
>
inline bool deserialize_stream(map_type& map, ostream& stream)
    {
    return do_deserialize_stream<ostream, map_type>()(map, stream);
    }

template<
typename istream,
typename map_type
>
inline bool serialize_stream(map_type& map, istream& stream)
    {
    return do_serialize_stream<istream, map_type>()(map, stream);
    }

}
} //namespace dsml::serialization

#endif
