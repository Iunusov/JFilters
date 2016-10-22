@echo off

echo Sync started.

echo DSPFilters...
if not exist DSPFilters (
    (git clone https://github.com/Iunusov/DSPFilters.git)
) else (
    (cd DSPFilters) && (git pull) && (cd ..)
)

echo VST_SDK_2.4...
if not exist VST_SDK_2.4 (
    (git clone https://github.com/Iunusov/VST_SDK_2.4.git)
) else (
    (cd VST_SDK_2.4) && (git pull) && (cd ..)
)


echo Done.
