#!/bin/sh
set -e
echo "Sync started."
for i in \
https://github.com/Iunusov/DSPFilters.git \
https://github.com/Iunusov/VST_SDK_2.4.git
do
filename="$(basename "$i")"
dir="${filename%.*}"
echo $dir
if [ ! -d "$dir" ]; then
  git clone "$i"
else
  cd "$dir"
  git pull
  cd ..
fi
done
echo "Done."
