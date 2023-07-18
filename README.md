![Squiggly Snake](assets/snake.gif)

---

A basic snake game. I wrote this primarily to try and learn SFML.

## Building

Recursively clone the repository in order to fetch SFML (it is added to the project as a git submodule)

```bash
git clone https://github.com/piigle/sfml-snake.git --recursive
```

Build using CMake (generator of your choice)

```bash
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build .
```

The executable must be run in the same directory as the assets folder
NOTE: You will need to have openal32.dll alongside your executable for it to run. This file can be found in lib\SFML\extlibs\bin\x64

## Music 

"Airship Serenity" Kevin MacLeod (incompetech.com)
Licensed under Creative Commons: By Attribution 4.0 License
http://creativecommons.org/licenses/by/4.0/
