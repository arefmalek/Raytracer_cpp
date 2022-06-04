set -e

g++ main.cpp
./a.out > temp.ppm
gwenview temp.ppm
