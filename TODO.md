# TODO
* Write a script for setting up Windows/VisualStudio. Currently only needed by Bora. Ask him if you need this.
* Hotloading
* Create gitignored folders during setup phase. Such as `build/`, `3rdParty/` and `3rdParty/headers` because some things depend on this existing.
* Minimize the need for platform specific defines. Either move this specific code to different files and include the correct one based on what platform we're on. Or just declare different headers in which the header has the correct behaviour for all platforms. Instead of having to do this in each file the programmer can just include this new header and be happy.
* Copy resources over to where the binary is so that the resource directory will always be at the same location as the executable.
