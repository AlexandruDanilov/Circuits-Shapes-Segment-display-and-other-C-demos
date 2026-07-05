# Circuits, Shapes, Segment Display, and Other C Demos

## board_games

### Function `main(void)`

In `main`, the following variables are defined:
- `hp` - the player's health.
- `n` - the number of items.
- `shields` - the shield vector.
- `m` - the number of boss attacks.
- `boss_damage` - the damage value for each boss attack.

The program reads the input data for the player's initial health, the number of
items, and the shields. It then processes this information, sorts the shields,
and removes null elements.

The initial value of `hp` is printed, then the variables needed to simulate the
boss fight are initialized.

While the player is alive, the program reads boss attacks and calls `battle`,
which updates `hp` according to the received damage. At the end of each round,
the player's current health is printed.

---

### Function `void scan_items(int n, long long shields[], long long *hp)`

This function reads the items from input. For each of the `n` items, it
identifies the item type:
- If the item is a heal, its value is added to `hp`.
- If the item is a shield, its value is added to the `shields` vector.
- If the item has another invalid type, an error message is printed.

For each item that is not a shield, the corresponding value in the `shields`
vector is set to `0`.

---

### Function `void sort_shields(int n, long long shields[])`

This function sorts the `shields` vector using **selection sort**, which works
as follows:
1. Find the minimum element in the unsorted vector.
2. Move it to the beginning of the current unsorted section.
3. Repeat the process for the remaining section until the vector is sorted.

---

### Function `void remove_zeros(int *n, long long shields[])`

This function removes null elements from the `shields` vector and updates the
vector size `n` so it matches the number of nonzero shields.

---

### Function `int find_best(long long shields[], int n, long long damage)`

This function searches for the best shield to reduce the damage received from
the boss. It is implemented with **binary search**.

---

#### Binary Search Explanation

Binary search uses a search interval defined by two limits, `left` and `right`.
At each step, half of the interval is eliminated. The algorithm works as
follows:
1. Initialize `left = 0` and `right = n - 1`.
2. Compute the midpoint of the interval with `mid = (left + right) / 2`.
3. Check the value at the midpoint:
   - If the midpoint value is less than or equal to `damage`, this shield is a
     candidate and the search continues to the right.
   - If the midpoint value is greater than `damage`, the search continues to
     the left.
4. Repeat until a suitable shield is found or until `left > right`.

If a suitable shield is found, its index is returned. Otherwise, `-1` is
returned.

---

### Function `void battle(long long *hp, int *n, long long shields[], long long boss_damage)`

This function simulates one boss fight round. If a suitable shield exists, `hp`
is updated based on the boss damage and the selected shield. The used shield is
removed from the `shields` vector so it cannot be used again. The round repeats
until the player dies or there are no more bosses.

---

### Additional Details

- **Selection sort:** In `sort_shields`, selection sort is used. It has
  `O(n^2)` complexity, and although it is not the fastest sorting algorithm, it
  is simple to implement.
- **Binary search:** `find_best` uses two binary searches to find the best
  shield, which improves lookup efficiency. Binary search reduces the lookup
  complexity from `O(n)` to `O(log n)`.

***

## shapes

### Function `main(void)`

In `main`, the following variables are defined:
- `n` - the number of shapes to print.
- `shape` - the shape type.
- `size`, `width`, `height`, `angle` - the parameters required by each shape.

The input data is read and, based on the shape type, the matching function is
called (`print_square`, `print_rectangle`, and so on). Each shape is printed to
the screen, and the program returns `0` at the end.

---

### Function `void normalize_angle(int *angle)`

This function normalizes `angle` so it falls within the interval `[0, 359]`.
This is done with modulo 360 operations.

1. If `angle % 360` is negative, 360 is added to make it positive.
2. `angle = angle % 360` is applied to bring it into `[0, 359]`.

---

### Function `void print_square(int size, int angle)`

This function checks `size` and `angle`:
- If the size or angle is invalid, an error message is printed and the function
  stops.
- If the angle is a multiple of 90, a square with side `size` is printed.
- If the angle is a multiple of 45 but not of 90, a diamond with size `size` is
  printed.

The function calls `normalize_angle` to bring the angle into `[0, 359]`.

---

### Function `void print_rectangle(int width, int height)`

This function prints a rectangle with width `width` and height `height`.
- If at least one dimension is less than or equal to 0, an error message is
  printed and the function stops.
- If the dimensions are valid, the rectangle is printed on the screen.

---

### Function `void print_triangle(int cathetus, int angle)`

The function prints a right triangle with side `cathetus`, rotated according to
`angle`. As with the other functions, the angle is validated:
- If the angle is not a multiple of 90, an error message is printed and the
  function stops.
- Depending on the specified angle, the triangle is rotated accordingly.

The function calls `normalize_angle` to make sure the angle is valid.

---

### Function `void print_cross(int size, int angle)`

This function prints a cross shaped as `+` or `X`, depending on `angle`:
- If `size` is invalid (less than or equal to 0, or even), an error message is
  printed.
- If the angle is not a multiple of 45, an error message is printed.
- If the angle is a multiple of 90, the cross is shaped as `+`; if the angle is
  a multiple of 45 but not of 90, the cross is shaped as `X`.

---

### Function `void print_window(int size)`

This function prints a window of size `size`. The window has borders and a
cross in the center. The size is checked as follows:
- If `size` is less than or equal to 0 or is even, an error message is printed.
- If the size is valid, the window is printed on the screen.

***

## circuits

### Function `main(void)`

In `main`, the program starts by reading the law type to check: `I` for
Kirchhoff's first law or `II` for Kirchhoff's second law. It also reads the
number of nodes `n` and the number of wires `w`. Next, it allocates memory for
the circuit wires using a vector of `wire` structures. The program then checks
the selected law and calls the matching functions.

---

### Function `read_kirchoff_1(struct wire *wires, int w)`

This function reads the data for Kirchhoff's first law:
- The start and end nodes of each wire.
- The current flowing through each wire.

For each wire, it reads:
- The start node.
- The end node.
- The current flowing through the wire.

The data is stored in the corresponding `wire` structure.

---

### Function `read_kirchoff_2(struct wire *wires, int w, bool *valid)`

This function reads the data required for Kirchhoff's second law:
- The start and end nodes of each wire.
- The current flowing through each wire.
- The components, resistors and voltage sources, on each wire.

For each wire:
- Memory is dynamically allocated for the components.
- The type, resistor or voltage source, and value of each component are read.

The program validates each component type:
- The resistor (`R`) is valid.
- The voltage source (`E`) must have a value greater than 0.

---

### Function `check_open(struct wire *wires, int n, int w, bool *valid)`

This function checks whether there are open nodes:
- A node is considered open if it does not have enough wires connecting it to
  other nodes.

A `connections` vector is created to register nodes that have connections, then
the function checks whether each node has at least two connections.

If a node does not have enough connections, the program prints an error message
and stops the check.

---

### Function `check_kirchoff_1(struct wire *wires, int n, int w)`

This function checks Kirchhoff's first law.

For each node:
- It computes the current entering the node, which is the current flowing
  through wires that end at the node.
- It computes the current leaving the node, which is the current flowing
  through wires that start at the node.

If the incoming current differs from the outgoing current by more than epsilon,
the program prints an error message and stops the check.

---

### Function `check_kirchoff_2(struct wire *wires, int w)`

This function checks Kirchhoff's second law.

For each wire:
- It computes the voltage drop on resistors using `V = I * R`.
- It computes the voltage generated by voltage sources (`E`).

If the voltage sums are approximately equal for the voltage drop and the voltage
sources, the law is satisfied. Otherwise, the program prints an error message.

---

### Memory Release

At the end of execution, the dynamically allocated memory for each wire's
components is freed with `free()`. The memory allocated for the wire vector is
also freed.

***

## segment_display

### Function `main(void)`

In `main`, the program reads the matrix dimensions, the number of lines and
columns, and the segment length used to form the digit that will be displayed.
After that, it enters an infinite loop where it reads commands from the user and
executes the matching operations on the display matrix until the user chooses to
end the program with the `Q` command. The possible commands are: `F` to add a
digit to the display, `W` to move the display up, `S` to move the display down,
`A` to move the display left, `D` to move the display right, and `P` to print
the current matrix.

---

### Function `clear_input_buffer(void)`

This function reads a full line after detecting an error on that line. It does
this so the invalid command error message is not printed more times than
necessary.

---

### Function `init_matrix(int n, int m, int display[][NMAX])`

This function initializes the matrix that represents the display. All matrix
values are set to 0.

---

### Function `print_matrix(int n, int m, int display[][NMAX])`

This function prints the matrix to the screen. For each matrix element:
- If the value is 0, two spaces are printed.
- If the value is 1, the `^` symbol followed by a space is printed.

---

### Function `move_up(int display[][NMAX], int lines, int columns, long long steps)`

This function moves the entire display up. The move is based on a number of
steps, reduced modulo `% lines`.

---

### Function `move_down(int display[][NMAX], int lines, int columns, long long steps)`

This function moves the entire display down. As with `move_up`, the move is
based on a number of steps reduced modulo `% lines`.

---

### Function `move_left(int display[][NMAX], int lines, int columns, long long steps)`

This function moves the entire display left. As with the other move functions,
the number of steps is reduced modulo `% columns`.

---

### Function `move_right(int display[][NMAX], int lines, int columns, long long steps)`

This function moves the entire display right. As with the functions above, the
move is based on a number of steps reduced modulo `% columns`.

---

### Function `fill_digit(int digit, int display[][NMAX], int n, int m, int len, int wid)`

This function fills the display matrix with the segments associated with a digit
from 0 to 9. Using the predefined segment matrix for each digit, the function
sets the corresponding values in `display` to represent each digit. The
`segments` matrix defines the structure of each digit displayed on the screen.
Each row of the matrix corresponds to one digit, from 0 to 9, and each column
represents the matching segment (`a`, `b`, `c`, and so on). Each element
indicates whether a given digit segment is active (`1`) or inactive (`0`).

## Usage Instructions

The programs are compiled with `make build`, executables are removed with
`make clean`, and each program is run from the terminal with `./program_name`.
