// Danilov Alexandru-Cristian, 315CA
#include <stdio.h>

#define NMAX 10000 // numarul maxim de iteme

void scan_items(int n, long long shields[], long long *hp)
{
	char type;
	long long value;

	for (int i = 0; i < n; i++) {
		scanf(" %c %lld", &type, &value);

		if (type == 'H') {
			*hp += value;
			shields[i] = 0;
		} else if (type == 'S') {
			shields[i] = value;
		} else {
			shields[i] = 0;
			printf("Invalid item type.\n");
		}
	}
}

// Elementele heal se aduna la hp.
// Valoarea elementelor shield este copiata in vectorul shields.
// Pentru iteme invalide se afiseaza mesajul de eroare.

void sort_shields(int n, long long shields[])
{
	for (int i = 0; i < n; i++) {
		int pos_min = i;

		for (int j = i + 1; j < n; j++) {
			if (shields[j] < shields[pos_min]) {
				pos_min = j;
			}
		}

		long long aux = shields[i];
		shields[i] = shields[pos_min];
		shields[pos_min] = aux;
	}
}

// Elementele din vectorul shields sunt sortate prin selection sort.

void remove_zeros(int *n, long long shields[])
{
	int new_count = 0;

	for (int i = 0; i < *n; i++) {
		if (shields[i] != 0) {
			shields[new_count] = shields[i];
			new_count++;
		}
	}

	*n = new_count;
}

// Sunt eliminate elementele nule din vectorul shields
// (adica cele care nu sunt scuturi).
// Este actualizat n ca sa coincida cu numarul de scuturi.

int find_best(long long shields[], int n, long long damage)
{
	int left = 0;
	int right = n - 1;
	int best_idx = -1;

	// Cautare binara pentru scutul optim
	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (shields[mid] <= damage) {
			best_idx = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	if (best_idx != -1) {
		return best_idx;
	}

	// Cautare binara pentru scutul minim mai mare decât daunele
	left = 0;
	right = n - 1;
	best_idx = -1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (shields[mid] > damage) {
			best_idx = mid;
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}

	return best_idx;
	// Prin cautare binara se alege scutul optim pentru lupta.
}

void battle(long long *hp, int *n, long long shields[], long long boss_damage)
{
	int best_shield_index = find_best(shields, *n, boss_damage);
	// Se gaseste scutul optim.
	long long used_shield = 0;

	if (best_shield_index != -1) {
		used_shield = shields[best_shield_index];
		long long damage_taken = boss_damage - used_shield;

		if (damage_taken < 0) {
			damage_taken = 0; // Dauna absorbita nu poate fi negativa.
		}

		*hp -= damage_taken;
	} else {
		*hp -= boss_damage;
	}
	// Se modifica hp în functie de daunele suferite.

	if (*hp < 0) {
		*hp = 0; // hp nu poate avea valoare negativa.
	}

	if (used_shield > 0) {
		printf("%lld %lld\n", *hp, used_shield);
	} else {
		printf("%lld\n", *hp);
	}
	// Se afisează hp si scut (daca e cazul) dupa lupta.

	if (best_shield_index != -1) {
		for (int j = best_shield_index; j < *n - 1; j++) {
			shields[j] = shields[j + 1];
		}
		(*n)--;
	}
	// Daca se foloseste un scut, acesta este eliminat
	// pentru a nu fi folosit din nou.
}

int main(void)
{
	long long hp;
	int n;
	long long shields[NMAX];

	scanf("%lld %d", &hp, &n);
	scan_items(n, shields, &hp);
	sort_shields(n, shields);
	remove_zeros(&n, shields);

	printf("Initial health points: %lld\n", hp);
	// Se citesc si se prelucreaza datele specifice itemelor.

	int m;
	scanf("%d", &m);
	long long boss_damage;

	for (int i = 0; i < m; i++) { // Citesc m bossi.
		scanf("%lld", &boss_damage);

		if (hp > 0) {
			battle(&hp, &n, shields, boss_damage);
		} else {
			break;
		}
		// Daca Gigel este viu, pentru fiecare boss se apeleaza
		// functia battle care afiseaza rezultatul si modifică hp.
		// Daca Gigel este mort, se opresc luptele si nu se mai citesc bossi.
	}

	if (hp > 0) {
		printf("Foe Vanquished!\n");
	} else {
		printf("You died.\n");
	}
	// Se afiseaza mesajul final.

	return 0;
}
