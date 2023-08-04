# Author

Thierry Vilmart
t.vilmart@gmail.com

Important:
It was required to spend half a day. Not to make the best project during a longer time (with multi-threading, more DI, unit tests, etc).
// I tried to use more DI with boost/di.hpp, but it has a conflict with the data structures as soon as I add an unordered_map in it.
// di::bind<ChainModel>().to(ChainModel)

The Chain of Responsibility design pattern was used.
It solves these 2 problems, for an industrial approach:
--Coupling the sender of a request to its receiver should be avoided.
--It should be possible that more than one receiver can handle a request.
--It allows to parallelize the task more easily.

# Example to run on Debian/Ubuntu (change the path to the file)

clear; g++ -std=c++17 -o parse Main.cpp chain/*.cpp utilities/*.cpp -Ithird_party -Iutilities -Ichain -Imodels && ./parse /home/thierry/repos/test_intrasense/data/sample.txt
