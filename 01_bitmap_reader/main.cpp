#include <iostream>
#include "./Bitmap.h"

using std::cout;
using std::cerr;
using std::endl;

/**
 * ARGUMENTS
 **/

const char* INPUT_BMP_FILE = "../assets/sample.bmp"; // the input BMP file


int main()
{


    Bitmap bmp(INPUT_BMP_FILE);
    bmp.print_file_header();
    bmp.print_info_header();

    
    return 0;
}
