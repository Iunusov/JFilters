#VST Filters
Simple VST filters set (with no GUI), based on DSPFilters library: https://github.com/vinniefalco/DSPFilters

Contains Low-Pass, High-Pass, Band-Pass filter.

Tested in Cubase, FL Studio and Reaper.

#Dependencies
CMake >= 3.0

https://cmake.org/download/

#How to build 
```bash
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
