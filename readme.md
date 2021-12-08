# Tetris
Simple tetris implementation in C.

## Dependencies
* MinGW (for windows users)
* cmake
* ncurses [tutorial installation](https://e-l.unifi.it/pluginfile.php/805205/mod_resource/content/0/ncurses%20installation%20-%20en.pdf)

## Installation
1. Download the repository
    ```
    git clone https://github.com/Filibertoo/tetris
    ```
2. Install every [dependencies](#dependencies)
3. Go into the repository folder
    ```
    cd ./build
    ```
4. Create CMake files, run:
    ```
    cmake -S . -B ./build
    ```
5. Build (inside build folder)
    * Linux/Mac

        ```
        make
        ```
    * Windows

        ```
        mingw32-make
        ```
6. Done! Now u can play tetris by running 
    ```
    ./tetris
    ```