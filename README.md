# BibleVerse
Fetches passages from Scripture.

## Requirements
- CMake v4.0 minimum
- pkg-config
- The SWORD library
- At least one Bible module installed

## Build
```shell
$ mkdir build && cd build
$ cmake ../CMakeLists.txt
$ make
```

However the user wants to install this binary is up to him.

## Usage
Once built, run `./BibleVerse` and type out your passage location.
### Format
- `verse` - will display all Biblical modules detected on your machine
- `verse <passage> <module>` or
- `verse <module> <passage>` - fetches and displays on `stdout` the requested passage.
### Examples:
- `verse Psalm 1 NASB` - fetches the entire chapter
- `verse John 3:16-18 KJV` - fetches a range of verses (here: 16, 17 and 18)
- `verse 1 Peter 5:7 NASB` - fetches one verse
