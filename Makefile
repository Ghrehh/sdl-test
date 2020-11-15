compileMac:
	clang++ src/*.cpp -o Game \
		-Wl,-rpath,@loader_path/../Frameworks \
 		-Ivendor/mac/SDL2.framework/Headers \
		-Ivendor/mac/SDL2_image.framework/Headers \
		-Ivendor/mac/SDL2_ttf.framework/Headers \
		-Ivendor/shared/nlohmann \
 		-Fvendor/mac \
 		-framework SDL2 \
	 	-framework SDL2_image \
	 	-framework SDL2_ttf \
	 	-std=c++17 

buildMac: compileMac
	rm -rf -f build/mac/Game.app/Contents/Resources/assets
	cp -rf assets build/mac/Game.app/Contents/Resources/
	rm -f build/mac/Game.app/Contents/MacOS/Game
	cp Game build/mac/Game.app/Contents/MacOS/
	open build/mac

compileRunMac: compileMac
	DYLD_FRAMEWORK_PATH=vendor/mac ./Game

compileWindows:
	g++ src/*.cpp -o Game.exe -Wl,-subsystem,windows \
		-Ivendor/windows/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2 \
		-Ivendor/windows/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2 \
		-Ivendor/shared/nlohmann \
		-Lvendor/windows/SDL2-2.0.12/x86_64-w64-mingw32/lib \
		-Lvendor/windows/SDL2_image-2.0.5/x86_64-w64-mingw32/lib \
		-lmingw32 \
		-lSDL2main \
		-lSDL2  \
		-lSDL2_image  \
		-std=c++17 \
		-v

buildWindows: compileWindows
	rm -rf -f build/windows/assets
	cp -rf assets build/windows/
	rm -f build/windows/Game.exe
	cp Game.exe build/windows/

compileRunWindows: compileWindows
	PATH=build/windows ./Game.exe


c: compileMac
b: buildMac
cr: compileRunMac
