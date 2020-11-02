compileMac:
	clang++ src/*.cpp -o Game -Ivendor/mac/SDL2.framework/Headers -Fvendor/mac -framework SDL2 -std=c++17

buildMac: compileMac
	rm -rf -f build/mac/Game.app/Contents/Resources/assets
	cp -rf assets build/mac/Game.app/Contents/Resources/
	rm -f build/mac/Game.app/Contents/MacOS/Game
	cp Game build/mac/Game.app/Contents/MacOS/
	open build/mac

compileRunMac: compileMac
	./Game

compileWindows:
	g++ src/*.cpp -o Game.exe -Wl,-subsystem,windows -Ivendor/windows/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2 -Lvendor/windows/SDL2-2.0.12/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2  -std=c++17 -v

buildWindows: compileWindows
	rm -rf -f build/windows/assets
	cp -rf assets build/windows/
	rm -f build/windows/Game.exe
	cp Game.exe build/windows/

compileRunWindows: compileWindows
	PATH=build/windows ./Game.exe
