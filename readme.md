# What is this project ?
It is a proof of concept that It is possible to create a fmu with openmodelica and use it in a C++ code to create a simulator.
The FMU model : Two tanks linked by a pipe whose flow is controlled by a vave.
The Simulator : A person can change the opening of the valve through the GUI (made with qt).

# Compilation / Installation (with qt creator)
- get fmi4cpp from https://github.com/NTNU-IHB/FMI4cpp/tree/master
- compile it :
    - get dependances with : "sudo apt-get install libzip-dev libpugixml-dev"
    - mkdir build && cd build 
    - cmake -DFMI4CPP_BUILD_EXAMPLES=ON .. 
    - make
- open this project with qtcreator (select the .pro to build the whole project)
- In qtcreator, click on the name of the project on the arborescence on the left --> Add Library...
--> External Library --> "Library File" is the path toward libfmi4cpp.so
--> "Include path" is the path toward fmi4cpp/include.


# Credits
developped by Alexis Valencia, december 2023

