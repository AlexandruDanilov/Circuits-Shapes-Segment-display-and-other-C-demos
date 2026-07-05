build:
	gcc -Wall -Wextra board_games.c -o board_games
	gcc -Wall -Wextra shapes.c -o shapes
	gcc -Wall -Wextra circuits.c -o circuits
	gcc -Wall -Wextra segment_display.c -o segment_display

clean:
	rm board_games
	rm shapes
	rm circuits
	rm segment_display

pack:
	zip -FSr 315CA_DanilovAlexandruCristian_Assignment1.zip README.md Makefile *.c
