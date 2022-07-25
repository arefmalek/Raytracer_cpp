set -e

g++ main.cpp
./a.out > temp.ppm
open -a Preview temp.ppm

