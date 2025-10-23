// Danilov Alexandru-Cristian, 315CA
#include <stdio.h>

// Normalizeaza unghiul in intervalul [0, 360)
void normalize_angle(int *angle)
{
	*angle = (*angle % 360 + 360) % 360;
}

// Afiseaza un patrat de dimensiune `size` rotit cu un unghi `angle`
void print_square(int size, int angle)
{
	normalize_angle(&angle); // Se normalizeaza unghiul

	if (size <= 0) {
		printf("Unsupported size to display shape\n");
		return;
	}
	if (angle % 45 != 0) {
		printf("Unsupported angle to display shape\n");
		return;
	}

	if (angle % 90 == 0) { // Unghi 0 sau 180
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("*");
			}
			printf("\n");
		}
	} else if (angle % 45 == 0) { // Unghi 45 sau 135
		int spaces = size;
		int stars = 1;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < spaces; j++) {
				printf(" ");
			}
			for (int j = 0; j < stars; j++) {
				printf("*");
			}
			printf("\n");
			spaces--;
			stars += 2;
		}

		spaces++;
		stars -= 2;

		for (int i = 0; i < (size - 1); i++) {
			spaces++;
			stars -= 2;
			for (int j = 0; j < spaces; j++) {
				printf(" ");
			}
			for (int j = 0; j < stars; j++) {
				printf("*");
			}
			printf("\n");
		}
	}
}

// Afiseaza un dreptunghi cu latimea `width` si inaltimea `height`
void print_rectangle(int width, int height)
{
	if (width <= 0 || height <= 0) {
		printf("Unsupported size to display shape\n");
		return;
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("*");
		}
		printf("\n");
	}
}

// Afiseaza un triunghi cu cateta `cathetus` și unghiul `angle`
void print_triangle(int cathetus, int angle)
{
	normalize_angle(&angle);

	if (cathetus <= 0) {
		printf("Unsupported size to display shape\n");
		return;
	}
	if (angle % 90 != 0) {
		printf("Unsupported angle to display shape\n");
		return;
	}

	switch (angle % 360) {
	case 0: // Unghi 0
		for (int i = 1; i <= cathetus; i++) {
			for (int j = 0; j < i; j++) {
				printf("*");
			}
			printf("\n");
		}
		break;
	case 90: // Unghi 90
		for (int i = cathetus; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				printf("*");
			}
			printf("\n");
		}
		break;
	case 180: // Unghi 180
		for (int i = cathetus; i > 0; i--) {
			for (int j = 0; j < cathetus - i + 1; j++) {
				printf(" ");
			}
			for (int j = 0; j < i; j++) {
				printf("*");
			}
			printf("\n");
		}
		break;
	case 270: // Unghi 270
		for (int i = 1; i <= cathetus; i++) {
			for (int j = 0; j < cathetus - i; j++) {
				printf(" ");
			}
			for (int j = 0; j < i; j++) {
				printf("*");
			}
			printf("\n");
		}
	}
}

// Afiseaza o cruce de dimensiune `size` rotita cu un unghi `angle`
void print_cross(int size, int angle)
{
	normalize_angle(&angle);

	if (size <= 0 || size % 2 == 0) {
		printf("Unsupported size to display shape\n");
		return;
	}
	if (angle % 45 != 0) {
		printf("Unsupported angle to display shape\n");
		return;
	}

	if (angle % 90 == 0) { // Unghi 0 sau 180
		int middle = size / 2;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == middle || j == middle) {
					printf("*");
				} else {
					printf(" ");
				}
			}
			printf("\n");
		}
	} else if (angle % 45 == 0) { // Unghi 45 sau 135
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == j || i + j == size - 1) {
					printf("*");
				} else {
					printf(" ");
				}
			}
			printf("\n");
		}
	}
}

// Afiseaza o fereastra de dimensiune `size`
void print_window(int size)
{
	if (size <= 0 || size % 2 == 0) {
		printf("Unsupported size to display shape\n");
		return;
	}

	int mid = size / 2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == mid || j == mid) {
				printf("*");
			} else if (i == 0 || j == 0) {
				printf("*");
			} else if (i == size - 1 || j == size - 1) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(void)
{
	int n;
	scanf("%d", &n); // Citim numarul de forme
	for (int i = 0; i < n; i++) {
		char shape;
		int size, width, height, angle;

		scanf(" %c", &shape); // Citim forma
		switch (shape) {
		case 'p': // patrat
			scanf("%d %d", &size, &angle);
			print_square(size, angle);
			break;
		case 'd': // dreptunghi
			scanf("%d %d", &width, &height);
			print_rectangle(width, height);
			break;

		case 't': // triunghi
			scanf("%d %d", &size, &angle);
			print_triangle(size, angle);
			break;
		case 'c': // cruce
			scanf("%d %d", &size, &angle);
			print_cross(size, angle);
			break;
		case 'f': // fereastra
			scanf("%d", &size);
			print_window(size);
			break;
		default:
			printf("Unsupported shape\n");
			break;
		}
		if (i < n - 1) {
			printf("\n"); // Se lasa un rand liber intre forme
		}
	}
	return 0;
}
