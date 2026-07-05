// Danilov Alexandru-Cristian, 315CA
#include <stdio.h>

#define NMAX 10000 // maximum number of items

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

// Heal items are added to hp.
// Shield item values are copied to the shields vector.
// Invalid items print an error message.

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

// The elements in the shields vector are sorted with selection sort.

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

// Null elements are removed from the shields vector
// (meaning the elements that are not shields).
// n is updated to match the number of shields.

int find_best(long long shields[], int n, long long damage)
{
	int left = 0;
	int right = n - 1;
	int best_idx = -1;

	// Binary search for the optimal shield
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

	// Binary search for the smallest shield greater than the damage
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
	// Binary search is used to choose the optimal shield for the fight.
}

void battle(long long *hp, int *n, long long shields[], long long boss_damage)
{
	int best_shield_index = find_best(shields, *n, boss_damage);
	// Find the optimal shield.
	long long used_shield = 0;

	if (best_shield_index != -1) {
		used_shield = shields[best_shield_index];
		long long damage_taken = boss_damage - used_shield;

		if (damage_taken < 0) {
			damage_taken = 0; // Absorbed damage cannot be negative.
		}

		*hp -= damage_taken;
	} else {
		*hp -= boss_damage;
	}
	// Update hp according to the damage taken.

	if (*hp < 0) {
		*hp = 0; // hp cannot be negative.
	}

	if (used_shield > 0) {
		printf("%lld %lld\n", *hp, used_shield);
	} else {
		printf("%lld\n", *hp);
	}
	// Print hp and the shield, if one was used, after the fight.

	if (best_shield_index != -1) {
		for (int j = best_shield_index; j < *n - 1; j++) {
			shields[j] = shields[j + 1];
		}
		(*n)--;
	}
	// If a shield is used, remove it so it cannot be used again.
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
	// Read and process the item data.

	int m;
	scanf("%d", &m);
	long long boss_damage;

	for (int i = 0; i < m; i++) { // Read m bosses.
		scanf("%lld", &boss_damage);

		if (hp > 0) {
			battle(&hp, &n, shields, boss_damage);
		} else {
			break;
		}
		// If the player is alive, call battle for each boss. The function
		// prints the result and updates hp. If the player is dead, stop
		// the fights and stop reading bosses.
	}

	if (hp > 0) {
		printf("Foe Vanquished!\n");
	} else {
		printf("You died.\n");
	}
	// Print the final message.

	return 0;
}
