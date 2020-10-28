# MANYAK PROJE

## SETUP

### MAC

Currently only vscode is supported.
Make sure cmake is intalled and it's binary location added into PATH variable.
Change your directory to the code base directory.
Run:

```
./scripts/setup-mac.sh
```

Note that it will require super user access with certain commands since it's setting up libraries on mac.

### WINDOWS

Only Visual Studio is supported.
Make sure you have cmake and git installed. Git needs to be in PATH env.
Go to scripts and simply right click on `setup-windows.ps1` and select `Run with PowerShell`.
This will setup the the requirements needed to run the project.

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

### VISUAL STUDIO

Simply generate a Visual Studio project with cmake.
Open the project and build both solutions then run `manyak_project`.
