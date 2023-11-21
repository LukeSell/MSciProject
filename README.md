Luke Sell

MSci Final Year Project

Metaheuristics

An executable has been built and can be found in src\Metaheuristics\bin\release\Metaheuristics.exe,
run this on a Windows OS and on a 1920 x 1080 resolution display.
In this same directory you will also find folders for results and benchmark,
these contain the results of all metaheuristics used in the last run of the program,
and specific benchmarking data for all the metaheuristics respectively,
as log files with unique identifiers.
Also in the execution directory are files needed for running the program,
namely dlls and font files.

The libraries included in the libs folder are 64/32 bit windows versions of SDL 2 and SDL TTF,
these are originally C libraries,
they are used mainly for rendering a graphic user interface and handling input from the user.
These libraries fall under the zlib license which does not require this project to adhere to anything.
other versions can be downloaded from the SDL website,
as well as GNU GCC/G++ and the C++17 distributions.
If running on another OS system these will need to be built separately.

Documentation can be found in docs\html\index.html,
from there you can browse the documentation using the side bar,
this is generated using the doxygen library which can be downloaded from their website.
It is recommended to view as a web page on a modern browser for UML to display correctly.

All reports can be found in the reports folder,
i.e. the final version of the report, as well as past report submissions.

All code is in src\Metaheuristics,
either in sub directories named for their respective namespaces or in this root directory.

All tests are in test and uses the Catch 2 library which can be downloaded from their GitHub repository,
however this was not implemented due to issues with setting up and understanding the framework.

All UML is in docs and can be viewed on the web page as an interactive svg,
generated using the graphviz library which can be downloaded from their website.

To build the program use the commands below with appropriate edits for your system and directory structure.

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\gui\Application.cpp
-o obj\Release\gui\Application.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\gui\Button.cpp
-o obj\Release\gui\Button.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\gui\Menu.cpp
-o obj\Release\gui\Menu.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\gui\Screen.cpp
-o obj\Release\gui\Screen.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\gui\TravellingSalesmanProblemDisplay.cpp
-o obj\Release\gui\TravellingSalesmanProblemDisplay.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\Logger.cpp
-o obj\Release\Logger.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\main.cpp
-o obj\Release\main.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\mh\GeneticAlgorithm.cpp
-o obj\Release\mh\GeneticAlgorithm.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\mh\IteratedLocalSearch.cpp
-o obj\Release\mh\IteratedLocalSearch.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\mh\MemeticAlgorithm.cpp
-o obj\Release\mh\MemeticAlgorithm.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\mh\TabuSearch.cpp
-o obj\Release\mh\TabuSearch.o

mingw32-g++.exe -fomit-frame-pointer -fexpensive-optimizations -flto -O3 -std=c++1z -m32
-I IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2
-I IndividualProject_2021_Luke.Sell\src\Metaheuristics
-c IndividualProject_2021_Luke.Sell\src\Metaheuristics\opp\TravellingSalesmanProblem.cpp
-o obj\Release\opp\TravellingSalesmanProblem.o

mingw32-g++.exe
-L IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\lib
-L IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\lib
-L IndividualProject_2021_Luke.Sell\src\Metaheuristics
-o bin\Release\Metaheuristics.exe obj\Release\gui\Application.o obj\Release\gui\Button.o
obj\Release\gui\Menu.o obj\Release\gui\Screen.o obj\Release\gui\TravellingSalesmanProblemDisplay.o
obj\Release\Logger.o obj\Release\main.o obj\Release\mh\GeneticAlgorithm.o obj\Release\mh\IteratedLocalSearch.o
obj\Release\mh\MemeticAlgorithm.o obj\Release\mh\TabuSearch.o obj\Release\opp\TravellingSalesmanProblem.o
-lSDL2_ttf -flto -static-libstdc++ -static-libgcc -m32 -lmingw32
-lSDL2main -lSDL2.dll -luser32 -lgdi32 -lwinmm -ldxguid -mwindows

XCOPY IndividualProject_2021_Luke.Sell\libs\SDL2-2.0.10\i686-w64-mingw32\bin\*.dll bin\Release\ /D /Y

XCOPY IndividualProject_2021_Luke.Sell\libs\SDL2_ttf-2.0.15\i686-w64-mingw32\bin\*.dll bin\Release\ /D /Y

To use the program after starting it,
click on the buttons for each metaheuristic to find an optimal solution to the current problem.
This is best done one search at a time as there is no way of selecting which result is displayed,
as each metaheuristic will take some time to complete, up to a couple of minutes,
it could be confusing to have several threads return results at different times.
Results are also saved in the log file.
Benchmarking will provide specific data that can be used to compare the metaheuristics,
this will take a while, up to several minutes depending on the device specifications,
make sure not to exit the program whilst it is running.
New problem will generate a new Travelling Salesman Problem,
and to quit click the button quit.
The current Travelling Salesman Problem and its solution is displayed on the left of the screen.
A red square will show above the GUI buttons to indicate when there are currently running sub threads,
generating a new problem or closing the program during this time will result in incomplete data being logged.
