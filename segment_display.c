// Danilov Alexandru-Cristian, 315CA
#include <stdio.h>
#include <stdbool.h>

#define NMAX 1000

// When an error occurs, read until the end of the line
void clear_input_buffer(void)
{
	int c;
	while ((c = getchar()) != '\n')
		;
}

// Initialize the matrix with 0
void init_matrix(int n, int m, int display[][NMAX])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			display[i][j] = 0;
		}
	}
}

void print_matrix(int n, int m, int display[][NMAX])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (display[i][j] == 0) {
				printf("  "); // Print two spaces instead of 0
			} else {
				printf("^ "); // Print ^ and a space instead of 1
			}
		}
		printf("\n");
	}
}

void move_up(int display[][NMAX], int lines, int columns, long long steps)
{
	// Shift up
	int aux[NMAX][NMAX];
	steps = steps % lines;
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			int new_row = (i - steps + lines) % lines;
			aux[new_row][j] = display[i][j];
		}
	}

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			display[i][j] = aux[i][j];
		}
	}
}

void move_down(int display[][NMAX], int lines, int columns, long long steps)
{
	// Shift down
	int aux[NMAX][NMAX];
	steps = steps % lines;

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			int new_row = (i + steps) % lines;
			aux[new_row][j] = display[i][j];
		}
	}

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			display[i][j] = aux[i][j];
		}
	}
}

void move_left(int display[][NMAX], int lines, int columns, long long steps)
{
	// Shift left
	int aux[NMAX][NMAX];
	steps = steps % columns;

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			int new_col = (j - steps + columns) % columns;
			aux[i][new_col] = display[i][j];
		}
	}

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			display[i][j] = aux[i][j];
		}
	}
}

void move_right(int display[][NMAX], int lines, int columns, long long steps)
{
	// Shift right
	int aux[NMAX][NMAX];
	steps = steps % columns;

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			int new_col = (j + steps) % columns;
			aux[i][new_col] = display[i][j];
		}
	}

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			display[i][j] = aux[i][j];
		}
	}
}

void fill_digit(int digit, int display[][NMAX], int n, int m, int len, int wid)
{
	int segments[10][7] = {
	//   a  b  c  d  e  f  g
		{1, 1, 1, 1, 1, 1, 0}, // 0
		{0, 1, 1, 0, 0, 0, 0}, // 1
		{1, 1, 0, 1, 1, 0, 1}, // 2
		{1, 1, 1, 1, 0, 0, 1}, // 3
		{0, 1, 1, 0, 0, 1, 1}, // 4
		{1, 0, 1, 1, 0, 1, 1}, // 5
		{1, 0, 1, 1, 1, 1, 1}, // 6
		{1, 1, 1, 0, 0, 0, 0}, // 7
		{1, 1, 1, 1, 1, 1, 1}, // 8
		{1, 1, 1, 1, 0, 1, 1}  // 9
	};
	// The matrix defines which segments are on for each digit

	if (digit < 0 || digit > 9) {
		printf("The input given is not a digit.\n");
		return;
	}

	// If the input is a digit, clear the matrix
	init_matrix(n, m, display);

	int *seg = segments[digit];

	if (seg[0]) { // Segment a
		for (int i = 0; i < wid; i++) {
			for (int j = wid; j < wid + len; j++) {
				display[i][j] = 1;
			}
		}
	}
	if (seg[1]) { // Segment b
		for (int i = wid; i < wid + len; i++) {
			for (int j = m - wid; j < m; j++) {
				display[i][j] = 1;
			}
		}
	}
	if (seg[2]) { // Segment c
		for (int i = n - len - wid; i < n - wid; i++) {
			for (int j = m - wid; j < m; j++) {
				display[i][j] = 1;
			}
		}
	}
	if (seg[3]) { // Segment d
		for (int i = n - wid; i < n; i++) {
			for (int j = wid; j < wid + len; j++) {
				display[i][j] = 1;
			}
		}
	}
	if (seg[4]) { // Segment e
		for (int i = n - len - wid; i < n - wid; i++) {
			for (int j = 0; j < wid; j++) {
				display[i][j] = 1;
			}
		}
	}
	if (seg[5]) { // Segment f
		for (int i = wid; i < wid + len; i++) {
			for (int j = 0; j < wid; j++) {
				display[i][j] = 1;
			}
		}
	}
	if (seg[6]) { // Segment g
		int middle = n / 2 - wid / 2;
		for (int i = middle; i < middle + wid; i++) {
			for (int j = wid; j < wid + len; j++) {
				display[i][j] = 1;
			}
		}
	}
}

int main(void)
{
	int lines, columns, length, width;
	char command;
	int display[NMAX][NMAX];

	scanf("%d %d %d", &lines, &columns, &length);
	width = length / 3;
	init_matrix(lines, columns, display);

	while (true) {
		scanf(" %c", &command);
		if (command == 'Q') {
			break;
		}

		// Call the matching function for each command
		switch (command) {
		case 'F': {
			int digit;
			scanf("%d", &digit);
			fill_digit(digit, display, lines, columns, length, width);
			break;
		}
		case 'W': {
			long long steps;
			scanf("%lld", &steps);
			move_up(display, lines, columns, steps);
			break;
		}
		case 'S': {
			long long steps;
			scanf("%lld", &steps);
			move_down(display, lines, columns, steps);
			break;
		}
		case 'A': {
			long long steps;
			scanf("%lld", &steps);
			move_left(display, lines, columns, steps);
			break;
		}
		case 'D': {
			long long steps;
			scanf("%lld", &steps);
			move_right(display, lines, columns, steps);
			break;
		}
		case 'P': {
			print_matrix(lines, columns, display);
			printf("\n");
			break;
		}
		default:
			printf("Invalid command.\n");
			clear_input_buffer(); // Read the entire line to clear the error
			break;
		}
	}

	return 0;
}
