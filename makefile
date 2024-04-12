bin/tui : src/tui_test.cpp
	g++ src/tui_test.cpp -o bin/tui -I include -l ftxui-screen -l ftxui-dom -l ftxui-component

run : bin/tui
	./bin/tui