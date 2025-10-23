build:
	gcc -Wall -Wextra jocuri_societate.c -o jocuri_societate
	gcc -Wall -Wextra forme.c -o forme
	gcc -Wall -Wextra circuits.c -o circuits
	gcc -Wall -Wextra segment_display.c -o segment_display

clean:
	rm jocuri_societate
	rm forme
	rm circuits
	rm segment_display

pack:
	zip -FSr 315CA_DanilovAlexandruCristian_Tema1.zip README Makefile *.c
