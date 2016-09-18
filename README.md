#VST Filters
Simple VST filters set (with no GUI), based on DSPFilters library: https://github.com/vinniefalco/DSPFilters

Contains Low-Pass, High-Pass, Band-Pass filter.

Tested in Cubase, FL Studio and Reaper.

Download Windows binaries: http://www.kvraudio.com/product/jfilters-by-r-tur

<img src="https://static.kvraudio.com/i/b/jfilters.1474117176.png">

Possible view in FL Studio:

<img src="http://static.kvraudio.com/i/b/jfilters.1364275288.png">

#Dependencies

C++11 Compiler (tested with gcc version 4.8.4 and Visual Studio 2015)

CMake >= 3.0 (https://cmake.org/download/)

#How to build 
```bash
cd deps
./sync.sh (sync.bat)
cd ..
mkdir cmake
cd cmake
cmake ..
make (or refer to cmake dir, if you are using Visual Studio)
```

#Installing CMake 3.0 on Ubuntu
```bash
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
sudo apt-get install cmake
```

if cmake is already installed:
```bash
sudo apt-get upgrade
```
