/**
 * A simple class to represent a bitmap file.
 * 
 * A tool like xxd is useful in inspecting the hex values of the BMP file.
 * For instance, `xxd image.bmp | head` should print the BMP's header data.
 * 
 * References:
 *  - https://en.wikipedia.org/wiki/BMP_file_format#File_structure
 **/

#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

using std::cout;
using std::cerr;
using std::endl;
using std::fstream;
using std::ifstream;

/**
 * DATA STRUCTURES
 * to represent the tables on the wikipedia page
 **/

#pragma pack(push, r1, 1)
typedef struct BitmapFileHeader
{
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_address;

} BITMAP_FILE_HEADER;

typedef struct BitmapInfoHeader
{
    uint32_t header_size;
     int32_t width;
     int32_t height;
    uint16_t color_planes_count;
    uint16_t color_depth;
    uint32_t compression_method;
    uint32_t image_size;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t palette_color_count;
    uint32_t important_color_count;
} BITMAP_INFO_HEADER;
#pragma pack(pop, r1)

/**
 * The Bitmap class
 */

class Bitmap
{
    private:

        /**
         * hex value for ASCII string "BM" (bytes are swapped to make up for endianess)
         * Could use char[2] for BitmapFileHeader::file_type if you don't want to deal with an integer constant
         * but then again, the string won't be NULL terminated by default -- easier this way.
         **/
        const uint16_t BITMAP_TYPE_BM   = 0x4d42; 

        BITMAP_FILE_HEADER file_header;
        BITMAP_INFO_HEADER info_header;

        void validate_file_header()
        {
            if(file_header.file_type != BITMAP_TYPE_BM)
            {
                cerr << "The file is not supported." << endl;
                throw std::runtime_error("The file does not have a type BM.");
            }
        }

        void validate_info_header()
        {
            if(info_header.compression_method != 0)
            {
                cerr << "Compressed bitmaps are not currently supported." << endl;
                throw std::runtime_error("A compressed bitmap was encountered.");
            }
        }

    public:

        Bitmap(const char* bitmap_file_path)
        {
            ifstream bmp(bitmap_file_path, fstream::binary);
            if(!bmp)
            {
                cerr << "The file " << bitmap_file_path 
                     << " could not be opened." << endl;
                throw std::runtime_error("The file could not be opened.");
            }

            bmp.read((char*)&file_header, sizeof(BITMAP_FILE_HEADER));
            validate_file_header();

            bmp.read((char*)&info_header, sizeof(BITMAP_INFO_HEADER));;
            validate_info_header();
        }

        void print_file_header()
        {
            cout << "File Type: " << std::hex << "0x" << file_header.file_type << std::dec <<endl;
            cout << "File Size: " << file_header.file_size << endl;
            cout << "Data Addr: " << std::hex << "0x" << file_header.data_address << std::dec <<endl;
        }

        void print_info_header()
        {
            cout << "Header size:           " << info_header.header_size << endl;
            cout << "Width:                 " << info_header.width << endl;
            cout << "Height:                " << info_header.height << endl;
            cout << "Color planes:          " << info_header.color_planes_count << endl;
            cout << "Color depth:           " << info_header.color_depth << endl;
            cout << "Compression method:    " << info_header.compression_method << endl;
            cout << "Image size:            " << info_header.image_size << endl;
            cout << "Horizontal resolution: " << info_header.horizontal_resolution << endl;
            cout << "Vertical resolution:   " << info_header.vertical_resolution << endl;
            cout << "Palette colors:        " << info_header.palette_color_count << endl;
            cout << "Important colors:      " << info_header.important_color_count << endl;
        }

};
