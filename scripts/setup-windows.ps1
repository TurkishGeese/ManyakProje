Set-Location ../
New-Item -ItemType Directory -Force -Path 3rdParty
Set-Location 3rdParty

# Setup vcpkg
git clone https://github.com/Microsoft/vcpkg.git
Set-Location vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install
.\vcpkg.exe install sdl2:x64-windows
.\vcpkg.exe install sdl2-image:x64-windows
.\vcpkg.exe install sdl2-ttf:x64-windows
.\vcpkg.exe install sdl2-net:x64-windows
Set-Location ../