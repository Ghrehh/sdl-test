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
	g++ main.cpp -o Game.exe -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -Ivendor/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include -Lvendor/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib -std=c++17

buildWindows: compileWindows
	rm -rf -f build/windows/assets
	cp -rf assets build/windows/
	rm -f build/windows/Game.exe
	cp Game.exe build/windows/
	explorer build/windows

compileRunWindows: compileWindows
	PATH=build/windows ./Game.exe
