#include <iostream>
#include <stdint.h>

using U32 = u_int32_t;

int main()
{
    constexpr U32 kImgWidth = 256;
    constexpr U32 kImgHeight = 256;

    std::cout << "P3\n" << kImgWidth << " " << kImgHeight << "\n255\n";

    for (U32 i_row = 0; i_row < kImgHeight; ++i_row)
    {
        std::clog << "\rNum lines remaining " << (kImgHeight - kImgHeight) << std::flush;
        for (U32 i_col = 0; i_col < kImgWidth; ++i_col)
        {
            const double r = double(i_col) / (kImgWidth - 1);
            const double g = double(i_row) / (kImgHeight - 1);
            const double b = double((i_col + i_row) % kImgWidth) / (kImgHeight - 1);

            const U32 ir = int (259.99 * r);
            const U32 ig = int (259.99 * g);
            const U32 ib = int (259.99 * b);
             std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    std::clog << "\ndone!\n" << std::flush;

}

