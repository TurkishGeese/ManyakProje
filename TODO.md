# TODO
1. Write a script for setting up Windows/VisualStudio. Currently only needed by Bora. Ask him if you need this.
4. Minimize the need for platform specific defines. Either move this specific code to different files and include the correct one based on what platform we're on. Or just declare different headers in which the header has the correct behaviour for all platforms. Instead of having to do this in each file the programmer can just include this new header and be happy.
5. Copy resources over to where the binary is so that the resource directory will always be at the same location as the executable.
6. Figure out why visual studio code isn't picking up #defines. When we use MANYAK_MAC it fails to realize that it's defined. It still compiles correctly but it doesn't resolve some references which is uber annoying. However, ideally we want to fail in these preprocessor stages to make sure at least one platform is defined. This is not currently possible as the else case needs to refer to mac.
7. Currently hotloading in windows is weird. We used to use ninja for building, however, I could not get cmake/ninja to generate a unique `.pdb` for each time the library is built. This was needed because the pdb was locked (I think!) and we couldn't use the DLL that we rebuilt. This was weirdly not an issue with MSBuild. However, when MSBuild builds a library it locks the handle for about 80ms. So in Windows, currently, we need to wait at least that long to reload the DLL. None of this is ideal. Currently, this works. Therefore this only deserves to be a todo and nothing more. Actually, this is only true because it's annoying to debug these issues and the current solution "works".
9. Instead of letting things fail, we should put asserts with detailed messages. For example, there should never be a problem with loading a texture and if there is, the game should just crash and tell us exactly what happened.
10. TextureManager instead of reloading same textures multiple times.
11. Shouldn't require controllers to be connected at the start of the game.
12. Controller errors should be handled more gracefully because they can easily connect/disconnect.
13. Should support axis movement on controllers.
14. On Windows we use /EHsc to suppress a message. This should be investigated. We don't know why we use the flag.

# COMPLETED
2. Hotloading
3. Create gitignored folders during setup phase. Such as `build/`, `3rdParty/` and `3rdParty/headers` because some things depend on this existing.
8. Currently we render using pos, width and height. Ideally we would like to specify only a position and then the texture is just slapped on correctly. I think this position should be the center of the texture but it might be useful to have the position as the top left of the texture as well. We just need to pick one for now.
