#ifndef DSML_DSM_DETAIL_DSM_ALGORITHM_HPP_INCLUDED
#define DSML_DSM_DETAIL_DSM_ALGORITHM_HPP_INCLUDED

#include <dsml++/conversion/endian.hpp>
#ifdef   DSM_SPECIALIZE_FSTREAM
#include <dsml++/iostreams/byte_streams.hpp>
#include <fstream>
#endif

namespace dsml
{
namespace detail
{

///Real dsm deserialization algorithm.
template<typename map_t, typename ostream>
bool dsm_do_deserialize_stream(map_t& map, ostream& stream)
    {
    typedef typename ostream::traits_type::char_type temp_char;
    typedef typename map_t::int_type temp_int;
    temp_char b;
    unsigned short height = (unsigned short)map.height(), width = (unsigned short)map.width();
    int id = (int)map.id();
    id = conversion::to_big_endian(id);
    height = conversion::to_big_endian(height);
    width  = conversion::to_big_endian(width);
    if (height <= 0 && width <= 0)
        {
        throw std::exception("map size less than or equal to zero");
        }
    stream.write((temp_char*)&id, sizeof(int));
    stream.write((temp_char*)&height, sizeof(unsigned short));
    stream.write((temp_char*)&width, sizeof(unsigned short));
    if (map.width() % 2)
        {

        for (register temp_int y = 0; y < map.height(); ++y)
            {
            for (register temp_int x = 0; x < (map.width() - 1); x += 2)
                {
                b = (temp_char)map.tile(x, y).flag();
                b = (b << 2) | (temp_char)map.tile(x + 1, y).flag;
                b = (b << 2) | (temp_char)map.tile(x, y).height();
                b = (b << 2) | (temp_char)map.tile(x + 1, y).height();
                stream.write((temp_char*)&b, sizeof(temp_char));
                }
            b = 0;
            b = (temp_char)map.tile(map.width() - 1, y).flag();
            b = (b << 2);
            b = (b << 2) | (temp_char)map.tile(map.width() - 1, y).height();
            b = (b << 2);
            stream.write(&b, sizeof(temp_char));
            }

        }
    else
        {

        for (register temp_int y = 0; y < map.height(); ++y)
            {
            for (register temp_int x = 0; x < map.width(); x += 2)
                {
                b = (temp_char)map.tile(x, y).flag();
                b = (b << 2) | (temp_char)map.tile(x + 1, y).flag;
                b = (b << 2) | (temp_char)map.tile(x, y).height();
                b = (b << 2) | (temp_char)map.tile(x + 1, y).height();
                stream.write((temp_char*)&b, sizeof(temp_char));
                }
            }

        }
    return true;
    }

///Real dsm serialization algorithm.
template<typename map_t, typename istream>
bool dsm_do_serialize_stream(map_t& map, istream& stream)
    {
    typedef typename istream::traits_type::char_type temp_char;
    typedef typename map_t::int_type temp_int;
    typedef typename map_t::tile_type temp_tile;
    typedef typename map_t::row_type temp_row;
    typedef typename map_t::traits_type::flag_type temp_flag;
    temp_char b;
    unsigned short height, width;
    int id;

    stream.read((temp_char*)&id, sizeof(int));
    stream.read((temp_char*)&height, sizeof(unsigned short));
    stream.read((temp_char*)&width, sizeof(unsigned short));

    id = conversion::to_host_endian<int, conversion::big_endian>(id);
    height = conversion::to_host_endian<unsigned short, conversion::big_endian>(height);
    width = conversion::to_host_endian<unsigned short, conversion::big_endian>(width);

    if (height <= 0 && width <= 0)
        {
        throw "map size less than or equal to zero";
        }
    map.id((temp_int)id);

#ifdef DSM_OPTIMIZE_ALGORITHM
    map.height((temp_int)height);
    map.width((temp_int)width);
#else
    map.resize((temp_int)height, (temp_int)width);
#endif

    temp_tile t, t2;

#ifdef DSM_OPTIMIZE_ALGORITHM
    temp_row r((temp_int)width);
#endif

    if (width % 2)
        {

        for (register temp_int y = 0; y < (temp_int)height; ++y)
            {
            for (register temp_int x = 0; x < (temp_int)(width - 1); x += 2)
                {
                stream.read(&b, sizeof(temp_char));
                t.flag((temp_flag)(b >> 6));
                t2.flag((temp_flag)((temp_flag)(b << 2) >> 6));
                t.height((temp_flag)((temp_flag)(b << 4) >> 6));
                t2.height((temp_flag)((temp_flag)(b << 6) >> 6));

#ifdef DSM_OPTIMIZE_ALGORITHM
                r.tile(x, t);
                r.tile(x + 1, t);
#else
                map.tile(x, y, t);
                map.tile(x + 1, y, t2);
#endif

                }
            stream.read(&b, sizeof(temp_char));
            t.flag((temp_flag)(b >> 6));
            t.height((temp_int)((temp_int)(b << 4) >> 6));

#ifdef DSM_OPTIMIZE_ALGORITHM
            r.tile((temp_int)(width - 1), t);
            map.container().push_back(r);
#else
            map.tile((temp_int)(width - 1), y, t);
#endif
            }

        }
    else
        {

        for (register temp_int y = 0; y < (temp_int)height; ++y)
            {
            for (register temp_int x = 0; x < (temp_int)width; x += 2)
                {
                stream.read(&b, sizeof(temp_char));
                t.flag((temp_flag)(b >> 6));
                t2.flag((temp_flag)((temp_flag)(b << 2) >> 6));
                t.height((temp_flag)((temp_flag)(b << 4) >> 6));
                t2.height((temp_flag)((temp_flag)(b << 6) >> 6));

#ifdef DSM_OPTIMIZE_ALGORITHM
                r.tile(x, t);
                r.tile(x + 1, t);
#else
                map.tile(x, y, t);
                map.tile(x + 1, y, t2);
#endif
                }

#ifdef DSM_OPTIMIZE_ALGORITHM
            map.container().push_back(r);
#endif
            }

        }
    return true;
    }

///General proxy structure for proxying the dsm deserialization.
template<typename map_type, typename ostream>
struct dsm_stream_deserialization
    {
    inline bool operator()(map_type& map, ostream& stream)
        {
        return dsm_do_deserialize_stream(map, stream);
        }
    };

///General proxy structure for proxying the dsm serialization.
template<typename map_type, typename istream>
struct dsm_stream_serialization
    {
    inline bool operator()(map_type& map, istream& stream)
        {
        return dsm_do_serialize_stream(map, stream);
        }
    };

#ifdef DSM_SPECIALIZE_FSTREAM
///Specialized proxy dsm deserialization structure for std::ofstream.
template<typename map_type>
struct dsm_stream_deserialization<map_type, std::ofstream>
    {
    typedef typename map_type::int_type temp_int;
    bool operator()(map_type& map, std::ofstream& stream)
        {
        int map_size = ((sizeof(temp_int) * 3) + (map.height() * ((map.width() / 2) + (map.width() % 2))));
        iostreams::byte_stream bstream(map_size);
        bool ret = dsm_do_deserialize_stream(map, bstream);
        stream.write(bstream.get(), bstream.count());
        return ret;
        }
    };

///Specialized proxy dsm serialization structure for std::ifstream.
template<typename map_type>
struct dsm_stream_serialization<map_type, std::ifstream>
    {
    bool operator()(map_type& map, std::ifstream& stream)
        {
        stream.seekg(0, std::ios::end);
        int map_size = stream.tellg();
        stream.seekg(0, std::ios::beg);
        iostreams::byte_stream bstream(map_size);
        stream.read(bstream.get(), map_size);
        return dsm_do_serialize_stream(map, bstream);
        }
    };
#endif

///General dsm deserialization function.
template<typename map_type, typename ostream>
inline bool dsm_deserialize_stream(map_type& map, ostream& stream)
    {
    return dsm_stream_deserialization<map_type, ostream>()(map, stream);
    }

///General dsm serialization function.
template<typename map_type, typename istream>
inline bool dsm_serialize_stream(map_type& map, istream& stream)
    {
    return dsm_stream_serialization<map_type, istream>()(map, stream);
    }

}
} //namespace dsml::detail

#endif
