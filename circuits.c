// Danilov Alexandru-Cristian, 315CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define NMAX 1000
#define EPSILON 0.00000001

struct component {
	char type; // 'R' for resistor, 'E' for voltage source
	double value;
}; // Component structure

struct wire {
	int start_node;
	int end_node;
	double current;
	int num_components;
	struct component *components;
	// Pointer used for dynamic component allocation
};

void read_kirchoff_1(struct wire *wires, int w)
{ // Reads the input data for the first law
	for (int i = 1; i <= w; i++) {
		scanf("%d", &wires[i].start_node);
		scanf("%d", &wires[i].end_node);
		scanf("%lf", &wires[i].current);
	}
}

void read_kirchoff_2(struct wire *wires, int w, bool *valid)
{ // Reads the input data for the second law
	for (int i = 1; i <= w; i++) {
		scanf("%d", &wires[i].start_node);
		scanf("%d", &wires[i].end_node);
		scanf("%lf", &wires[i].current);
		scanf("%d", &wires[i].num_components);

		// Dynamically allocate memory for the components
		wires[i].components = (struct component *)
		malloc(wires[i].num_components * sizeof(struct component));

		if (!wires[i].components) {
			printf("Memory allocation error for components.\n");
			*valid = false;
			return;
		}

		for (int j = 0; j < wires[i].num_components; j++) {
			scanf(" %c", &wires[i].components[j].type);
			scanf("%lf", &wires[i].components[j].value);
			if (wires[i].components[j].type != 'R') {
				if (wires[i].components[j].type != 'E') {
					printf("The requested component does not exist.\n");
				}
			}
			if (wires[i].components[j].type == 'E') {
				if (wires[i].components[j].value < 0) {
					printf("The voltage source cannot be negative.\n");
					*valid = false;
				}
			}
		}
	}
}

// Checks whether there are open nodes
void check_open(struct wire *wires, int n, int w, bool *valid)
{
	int connections[NMAX] = {0};

	// Register each wire endpoint as a node connection
	for (int i = 1; i <= w; i++) {
		connections[wires[i].start_node]++;
		connections[wires[i].end_node]++;
	}

	// Check whether each node has enough connections
	for (int i = 1; i <= n; i++) {
		if (connections[i] < 2) {
			printf("The circuit is open at node %d.\n", i);
			*valid = false;
			return;
		}
	}
}

// Checks Kirchhoff's first law
void check_kirchoff_1(struct wire *wires, int n, int w)
{
	// Iterate through each node to check the first law
	for (int node = 1; node <= n; node++) {
		double incoming_current = 0.0;
		double outgoing_current = 0.0;

		// Iterate through each wire and compute incoming and outgoing current
		for (int i = 1; i <= w; i++) {
			// If the node is an endpoint, the current is incoming
			if (wires[i].end_node == node) {
				incoming_current += wires[i].current;
			}
			// If the node is a start point, the current is outgoing
			if (wires[i].start_node == node) {
				outgoing_current += wires[i].current;
			}
		}

		// Check whether the circuit satisfies the law
		if (fabs(incoming_current - outgoing_current) > EPSILON) {
			// Print the results with 9-digit decimal precision
			printf("Kirchhoff's first law is not satisfied for equality "
			"%.9lfA = %.9lfA at node %d.\n",
			incoming_current, outgoing_current, node);

			return;
		}
	}

	// All nodes satisfy Kirchhoff's first law
	printf("Kirchhoff's first law is satisfied for the given circuit.\n");
}

// Checks Kirchhoff's second law
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

	// Check whether the voltages are equal within epsilon precision
	if (fabs(voltage_drop_e - voltage_drop_r) < EPSILON) {
		printf("Kirchhoff's second law is satisfied for the given circuit.\n");
	} else {
		printf("Kirchhoff's second law is not satisfied for equality "
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
	// Allocate memory for the wires

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
		printf("The available laws are only Law 1 and Law 2.\n");
	}

	// Free the memory allocated for each wire's components
	for (int i = 1; i <= w; i++) {
		free(wires[i].components);
	}

	// Free the memory allocated for wires
	free(wires);

	return 0;
}
