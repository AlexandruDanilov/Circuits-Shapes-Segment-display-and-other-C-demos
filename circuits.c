// Danilov Alexandru-Cristian, 315CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define NMAX 1000
#define EPSILON 0.00000001

struct component {
	char type; // 'R' pentru rezistor, 'E' pentru sursa
	double value;
}; // Structura pentru fire

struct wire {
	int start_node;
	int end_node;
	double current;
	int num_components;
	struct component *components;
	// Folosim pointer pentru a aloca dinamic componentele
};

void read_kirchoff_1(struct wire *wires, int w)
{ // Functia pentru citirea datelor pentru legea 1
	for (int i = 1; i <= w; i++) {
		scanf("%d", &wires[i].start_node);
		scanf("%d", &wires[i].end_node);
		scanf("%lf", &wires[i].current);
	}
}

void read_kirchoff_2(struct wire *wires, int w, bool *valid)
{ // Functia pentru citirea datelor pentru legea 2
	for (int i = 1; i <= w; i++) {
		scanf("%d", &wires[i].start_node);
		scanf("%d", &wires[i].end_node);
		scanf("%lf", &wires[i].current);
		scanf("%d", &wires[i].num_components);

		// Alocam dinamic memoria pentru componente
		wires[i].components = (struct component *)
		malloc(wires[i].num_components * sizeof(struct component));

		if (!wires[i].components) {
			printf("Eroare la alocarea memoriei pentru componente.\n");
			*valid = false;
			return;
		}

		for (int j = 0; j < wires[i].num_components; j++) {
			scanf(" %c", &wires[i].components[j].type);
			scanf("%lf", &wires[i].components[j].value);
			if (wires[i].components[j].type != 'R') {
				if (wires[i].components[j].type != 'E') {
					printf("Componenta dorita nu exista.\n");
				}
			}
			if (wires[i].components[j].type == 'E') {
				if (wires[i].components[j].value < 0) {
					printf("Sursa de tensiune nu poate fi negativa.\n");
					*valid = false;
				}
			}
		}
	}
}

// Functia pentru verificarea daca exista noduri deschise
void check_open(struct wire *wires, int n, int w, bool *valid)
{
	int connections[NMAX] = {0};

	// Inregistram nodurile drept capete ale fiecarui fir
	for (int i = 1; i <= w; i++) {
		connections[wires[i].start_node]++;
		connections[wires[i].end_node]++;
	}

	// Verificam daca fiecare nod are o conexiune de inceput si sfarsit
	for (int i = 1; i <= n; i++) {
		if (connections[i] < 2) {
			printf("Circuitul este deschis in nodul %d.\n", i);
			*valid = false;
			return;
		}
	}
}

// Functia pentru verificarea Legii 1
void check_kirchoff_1(struct wire *wires, int n, int w)
{
	//  Parcurgem fiecare nod pentru a verifica Legea 1
	for (int node = 1; node <= n; node++) {
		double incoming_current = 0.0;
		double outgoing_current = 0.0;

		// Parcurgem fiecare fir si calculam curentul de intrare si iesire
		for (int i = 1; i <= w; i++) {
			// Daca nodul este final, curentul este de intrare
			if (wires[i].end_node == node) {
				incoming_current += wires[i].current;
			}
			// Daca nodul e de inceput, curentul este de iesire
			if (wires[i].start_node == node) {
				outgoing_current += wires[i].current;
			}
		}

		// Verificam daca circuitul respecta legea
		if (fabs(incoming_current - outgoing_current) > EPSILON) {
			// Afisam rezultatele cu precizie de 9 zecimale
			printf("Legea 1 a lui Kirchhoff nu se respecta pentru egalitatea "
			"%.9lfA = %.9lfA in nodul %d.\n",
			incoming_current, outgoing_current, node);

			return;
		}
	}

	// Daca toate nodurile respecta Legea 1
	printf("Legea 1 a lui Kirchhoff se respecta pentru circuitul dat.\n");
}

// Functia pentru verificarea Legii 2
void check_kirchoff_2(struct wire *wires, int w)
{
	double voltage_drop_r = 0.0;
	double voltage_drop_e = 0.0;

	for (int i = 1; i <= w; i++) {
		for (int j = 0; j < wires[i].num_components; j++) {
			if (wires[i].components[j].type == 'R') {
				double drop = wires[i].components[j].value * wires[i].current;
				voltage_drop_r += drop;
			}
			if (wires[i].components[j].type == 'E') {
				voltage_drop_e += wires[i].components[j].value;
			}
		}
	}

	// Verificam daca tensiunile sunt egale cu precizie epsilon
	if (fabs(voltage_drop_e - voltage_drop_r) < EPSILON) {
		printf("Legea a 2-a lui Kirchhoff se respecta pentru circuitul dat.\n");
	} else {
		printf("Legea a 2-a lui Kirchhoff nu se respecta pentru egalitatea "
		"%.9lfV = %.9lfV.\n", voltage_drop_r, voltage_drop_e);
	}
}

int main(void)
{
	char law[3];
	int n, w;

	scanf("%s", law);
	scanf("%d %d", &n, &w);

	struct wire *wires = (struct wire *)malloc((w + 1) * sizeof(struct wire));
	// Alocam memorie pentru fire

	bool valid = true;

	if (strcmp(law, "I") == 0) {
		read_kirchoff_1(wires, w);
		check_open(wires, n, w, &valid);
		if (valid) {
			check_kirchoff_1(wires, n, w);
		}
	} else if (strcmp(law, "II") == 0) {
		read_kirchoff_2(wires, w, &valid);
		if (valid) {
			check_open(wires, n, w, &valid);
			if (valid) {
				check_kirchoff_2(wires, w);
			}
		}
	} else {
		printf("Legile existente sunt doar Legea 1 si Legea a 2-a\n");
	}

	// Eliberam memoria pentru componentele fiecarui fir
	for (int i = 1; i <= w; i++) {
		free(wires[i].components);
	}

	// Eliberam memoria alocata pentru fire
	free(wires);

	return 0;
}
