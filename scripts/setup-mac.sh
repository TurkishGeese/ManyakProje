#!/bin/bash

CUR_DIR=$(pwd)

if [[ -d ./resources ]]
then
  mkdir -p './3rdParty/headers'
  mkdir './build'
  EXTERNAL_LOC='./3rdParty'
elif [[ -d ../resources ]]
then
  mkdir -p '../3rdParty/headers'
  mkdir '../build'
  EXTERNAL_LOC='../3rdParty'
else
  echo "Where are you running this script from???"
  exit 1
fi

SDL_DMG_LOC="${EXTERNAL_LOC}/SDL2.dmg"
SDL_IMG_DMG_LOC="${EXTERNAL_LOC}/SDL2_Image.dmg"
SDL_TTF_DMG_LOC="${EXTERNAL_LOC}/SDL2_ttf.dmg"


curl -o ${SDL_DMG_LOC} "https://www.libsdl.org/release/SDL2-2.0.12.dmg" 
curl -o ${SDL_IMG_DMG_LOC} "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.dmg"
curl -o ${SDL_TTF_DMG_LOC} "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.dmg"

# Copy SDL2 to /Library/Framework
sudo hdiutil attach ${SDL_DMG_LOC}
sudo cp -r /Volumes/SDL2/SDL2.framework /Library/Frameworks
sudo hdiutil detach /Volumes/SDL2 

# Copy SDL2_Image to /Library/Framework
sudo hdiutil attach ${SDL_IMG_DMG_LOC}
sudo cp -r /Volumes/SDL2_image/SDL2_image.framework /Library/Frameworks
sudo hdiutil detach /Volumes/SDL2_image

# Copy SDL2_ttf to /Library/Framework
sudo hdiutil attach ${SDL_TTF_DMG_LOC}
sudo cp -r /Volumes/SDL2_ttf/SDL2_ttf.framework /Library/Frameworks
sudo hdiutil detach /Volumes/SDL2_ttf

# Codesign SDL2 and copy the headers over
cd /Library/Frameworks/SDL2.framework
mkdir $CUR_DIR/$EXTERNAL_LOC/headers/SDL2
sudo cp -r /Library/Frameworks/SDL2.framework/Headers/ $CUR_DIR/$EXTERNAL_LOC/headers/SDL2
codesign -f -s - SDL2

# Codesign SDL2_Image and copy the headers over
cd /Library/Frameworks/SDL2_image.framework
mkdir $CUR_DIR/$EXTERNAL_LOC/headers/SDL2_image
sudo cp -r /Library/Frameworks/SDL2_image.framework/Headers/ $CUR_DIR/$EXTERNAL_LOC/headers/SDL2_image
codesign -f -s - SDL2_image

# Codesign SDL2_ttf and copy the headers over
cd /Library/Frameworks/SDL2_ttf.framework
mkdir $CUR_DIR/$EXTERNAL_LOC/headers/SDL2_ttf
sudo cp -r /Library/Frameworks/SDL2_ttf.framework/Headers/ $CUR_DIR/$EXTERNAL_LOC/headers/SDL2_ttf
codesign -f -s - SDL2_ttf

cd $CUR_DIR

if [[ -d ./resources ]]
then
  cd './3rdParty'
elif [[ -d ../resources ]]
then
  cd '../3rdParty'
fi

# Build and Install box2d
git clone https://github.com/erincatto/box2d.git
cd box2d
mkdir build
cd build
cmake -DBOX2D_BUILD_DOCS=OFF ..
cmake --build .
cmake --build . --target INSTALL

cd $CUR_DIR