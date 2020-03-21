# MANYAK PROJE

## SETUP

### MAC

Currently only vscode is supported.
Change your directory to the code base directory.
Run:

```
./scripts/setup-mac.sh
```

Note that

## BUILDING & RUNNING

### TERMINAL

To compile:
```
cd build/
cmake -G \"Unix Makefiles\" - DCMAKE_BUILD_TYPE=Debug ..
make -j 8
```

To run:
```
./build/manyak_project
```

### VSCODE

Run the task `cmake` and then `make` in order to compile the program.
Run the task `run` in order to run the compiled program.
