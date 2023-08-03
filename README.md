# Author

Thierry Vilmart
t.vilmart@gmail.com

# Example to run on Debian/Ubuntu (change the path to the file)

clear; g++ -o parse Main.cpp chain/*.cpp utilities/*.cpp -Iutilities -Ichain -Imodels && ./parse /home/thierry/repos/test_intrasense/data/sample.txt

