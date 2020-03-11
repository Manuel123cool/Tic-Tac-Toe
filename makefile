files = game.cpp game_grid.cpp game_symbols.cpp main.cpp 
sfml = -lsfml-graphics -lsfml-window -lsfml-system
Tic-Tac-Toe: $(files)
	g++ -o Tic-Tac-Toe $(files) $(sfml) -I.
