# Tema 1 PCLP - Danilov Alexandru-Cristian, 315CA

## jocuri_societate

### Functia `main(void)`

In functia `main`, se definesc variabilele:
- `hp` - viata jucatorului.
- `n` - numarul de iteme.
- `shields` - vector pentru scuturi.
- `m` - numarul de atacuri ale boss-ului.
- `boss_damage` - un vector care stocheaza daunele atacurilor boss-ului.

Se citesc datele de intrare pentru viata initiala a jucatorului, numarul de
iteme si scuturile, apoi programul proceseaza aceste informatii, le sorteaza
si elimina elementele nule.

Se afiseaza valoarea initiala a lui `hp` si se initializeaza variabilele
necesare pentru a simula lupta cu boss-ul.

Cat timp jucatorul este in viata, se cites bossi si se apeleaza functia `battle`,
care actualizeaza valoarea lui `hp` in functie de daunele primite. La finalul
fiecarei runde, se afiseaza starea actuala a vietii jucatorului.

---

### Functia `void scan_items(int n, long long shields[], long long *hp)`

Aceasta functie se ocupa de citirea itemelor din input. Se citesc `n` iteme,
iar pentru fiecare item, se identifica tipul:
- Daca este de tip `heal`, valoarea itemului se adauga la `hp`.
- Daca este de tip `shield`, valoarea itemului se adauga in vectorul
`shields`.
- Daca este de alt tip (invalid), se afiseaza un mesaj de eroare.

De asemenea, pentru fiecare item care nu este un scut, se seteaza valoarea
respectiva in vectorul `shields` la `0`.

---

### Functia `void sort_shields(int n, long long shields[])`

Aceasta functie sorteaza vectorul `shields` folosind algoritmul de
**sortare prin selectie** (Selection Sort), care functioneaza astfel:
1. Cautam elementul maxim in vectorul nesortat.
2. Il mutam la inceputul vectorului.
3. Repetam procesul pentru sectiunea ramasa a vectorului, pana cand
vectorul e sortat.

---

### Functia `void remove_zeros(int *n, long long shields[])`

Aceasta functie elimina elementele nule din vectorul `shields` si
actualizeaza dimensiunea vectorului `n` pentru a coincide cu numarul 
de scuturi cu valoare nenula.

---

### Functia `int find_best(long long shields[], int n, long long damage)`

Aceasta functie cauta cel mai bun scut pentru a reduce daunele primite de la
boss. Este implementata folosind **cautare binara**.

---

#### Explicatia cautarii binare:

Cautarea binara presupune un interval de cautare definit de doua limite,
un "stanga" (`left`) si un "dreapta" (`right`), iar la fiecare pas,
jumatatea intervalului este eliminata. Algoritmul functioneaza astfel:
1. Se initializeaza doua variabile: `left = 0` si `right = n-1`.
2. Se calculeaza mijlocul intervalului (`mid = (left + right) / 2`).
3. Se verifica valoarea elementului de la mijloc:
   - Daca valoarea de la mijloc este mai mare decat `damage`, inseamna
     ca acest scut poate reduce daunele si se muta `right` la `mid - 1`.
   - Daca valoarea de la mijloc este mai mica, inseamna ca trebuie sa
     cautam in partea dreapta a intervalului, iar `left` se actualizeaza
     la `mid + 1`.
4. Se repeta acest proces pana cand se gaseste un scut care indeplineste
   cerintele sau pana cand `left > right`.

Daca se gaseste un scut potrivit, se returneaza indexul acestuia; daca nu,
se returneaza `-1`.

---

### Functia `void battle(long long *hp, int *n, long long shields[], long
long boss_damage)`

Aceasta functie simuleaza o runda de lupta cu boss-ul. Daca exista un
scut care respecta cerinta, valoarea de `hp` este actualizata tinand
cont de daunele primite de la boss si scut. Scutul utilizat este
eliminat din vectorul `shields`, pentru a nu fi folosit din nou. Runda
se repeta pana cand jucatorul moare sau ramane fara bossi.

---

### Detalii suplimentare

- **Algoritmul de sortare prin selectie:** In cadrul functiei
`sort_shields`, se aplica Selection Sort, un algoritm de complexitate O(n^2),
care, desi nu este cel mai rapid, este simplu de implementat.

- **Cautare binara:** Functia `find_best` utilizeaza doua cautari binare
pentru a gasi cel mai bun scut, ceea ce duce la o eficienta mai mare in
cautarea scuturilor. Cautarea binara reduce complexitatea fata de o cautare
liniara, transformand complexitatea de la O(n) la O(log n).

***

## forme

### Functia `main(void)`

In functia `main`, sunt definite variabilele:
- `n` - numarul de forme de afisat.
- `shape` - tipul formei.
- `size`, `width`, `height`, `angle` - caracteristici necesare fiecarei forme.

Se citesc datele de intrare si in functie de tipul formei (`shape`), se
apeleaza functia (`print_square`, `print_rectangle`, etc).
Fiecare forma este afisata pe ecran, iar programul returneaza `0` la final.

---

### Functia `void normalize_angle(int *angle)`

Aceasta functie normalizeaza unghiul `angle` pentru a se incadra in intervalul
[0, 359]. Acest lucru se face prin operatii de modulo 360 pentru a aduce unghiul
in intervalul corect.

1. Daca `angle % 360` este negativ, se adauga 360 pentru a-l face pozitiv.
2. Se aplica `angle = angle % 360` pentru a-l aduce in intervalul [0, 359].

---

### Functia `void print_square(int size, int angle)`

In aceasta functie se verifica dimensiunea `size` si unghiul `angle`:
- Daca dimensiunea sau unghiul sunt invalide, se afiseaza un mesaj
de eroare si functia se opreste.
- Daca unghiul este multiplu de 90, se afiseaza un patrat cu latura `size`.
- Daca unghiul este multiplu de 45, dar nu si de 90, se afiseaza un romb cu
dimensiunea `size`.

Functia apeleaza `normalize_angle` pentru a aduce unghiul in intervalul [0, 359].

---

### Functia `void print_rectangle(int width, int height)`

Aceasta functie afiseaza un dreptunghi cu latimea `width` si inaltimea `height`.
- Daca macar una dintre dimensiuni este mai mica sau egala cu 0, se afiseaza
un mesaj de eroare si functia se opreste.
- Daca dimensiunile sunt valide, dreptunghiul este afisat pe ecran.

---

### Functia `void print_triangle(int cathetus, int angle)`

Functia afiseaza un triunghi dreptunghic cu cateta `cathetus`, rotit conform
unghiului `angle`. La fel ca in celelalte functii, se verifica daca unghiul
este valid:
- Daca unghiul nu este multiplu de 90, se afiseaza un mesaj de eroare si
functia se opreste.
- In functie de unghiul specificat, triunghiul este rotit

Functia apeleaza `normalize_angle` pentru a se asigura ca unghiul este valid.

---

### Functia `void print_cross(int size, int angle)`

Aceasta functie afiseaza o cruce in forma de "+" sau "X" in functie de `angle`:
- Daca `size` este invalid (mai mic sau egal cu 0 sau par), se afiseaza
un mesaj de eroare.
- Daca unghiul nu este multiplu de 45, se afiseaza un mesaj de eroare.
- Daca unghiul este multiplu de 90, crucea este in forma de "+", iar daca
este multiplu de 45 (dar nu de 90), crucea este in forma de "X".

---

### Functia `void print_window(int size)`

Aceasta functie afiseaza o fereastra de dimensiune `size`. Fereastra are margini
si o cruce in centru. Verificarea dimensiunii:
- Daca `size` este mai mica sau egala cu 0 sau este un numar par, se afiseaza
un mesaj de eroare.
- Daca dimensiunea este valida, fereastra este afisata pe ecran.

***

## circuite

### Functia `main(void)`

In functia `main`, programul incepe prin citirea tipului de lege 
care va fi verificata: „I” pentru Legea I a lui Kirchhoff sau „II” 
pentru Legea II a lui Kirchhoff. Se citesc si numarul de noduri `n` 
si numarul de fire `w`. In continuare, se aloca memorie pentru 
firele din circuit, folosind un vector de structuri `wire`. 
Programul verifica apoi legea aleasa si apeleaza functiile aferente.

---

### Functia `read_kirchoff_1(struct wire *wires, int w)`

Aceasta functie citeste datele pentru Legea I a lui Kirchhoff:
- Nodurile de inceput si sfarsit ale fiecarui fir.
- Curentul care circula prin fiecare fir.

Se citeste pentru fiecare fir:
- Nodul de inceput
- Nodul de sfarsit
- Curentul care circula prin fir

Datele sunt stocate in structura `wire` corespunzatoare fiecarui fir. 

---

### Functia `read_kirchoff_2(struct wire *wires, int w, bool *valid)`

Aceasta functie citeste datele necesare pentru Legea II a lui Kirchhoff:
- Nodurile de inceput si sfarsit pentru fiecare fir.
- Curentul care circula prin fiecare fir.
- Componentele (rezistori si surse de tensiune) de pe fiecare fir.

Pentru fiecare fir:
- Se aloca dinamic memoria pentru componente.
- Se citesc tipul (rezistor sau sursa de tensiune) si valoarea fiecarei componente.

Programul verifica validitatea fiecarui tip de componenta:
- Rezistorul (`R`) este valid.
- Sursa de tensiune (`E`) trebuie sa aiba valoare > 0.

---

### Functia `check_open(struct wire *wires, int n, int w, bool *valid)`

Aceasta functie verifica daca exista noduri deschise:
- Un nod este considerat deschis daca nu are cel putin un fir care sa il lege de 
alte noduri.

Se creeaza un vector `connections` pentru a inregistra nodurile care au conexiuni 
si se verifica daca fiecare nod are cel putin 2 conexiuni (inceput si sfarsit).

Daca un nod nu are suficiente conexiuni, programul afiseaza un mesaj de eroare 
si opreste executia.

---

### Functia `check_kirchoff_1(struct wire *wires, int n, int w)`

Aceasta functie verifica Legea I a lui Kirchhoff:

Pentru fiecare nod:
- Se calculeaza curentul care intra in nod (curentul care circula pe firele 
care ajung la nod).
- Se calculeaza curentul care iese din nod (curentul care circula pe firele 
care pleaca din nod).

Daca curentul de intrare este diferit de cel de iesire cu mai mult de epsilon,
programul afiseaza un mesaj de eroare si opreste executia.

---

### Functia `check_kirchoff_2(struct wire *wires, int n, int w)`

Aceasta functie verifica Legea II a lui Kirchhoff:

Pentru fiecare fir:
- Se calculeaza caderea de tensiune pe rezistoare (folosind formula `V = I * R`).
- Se calculeaza tensiunea generata de sursele de tensiune (`E`).

Daca suma tensiunilor este aproximativ egala pentru caderea de tensiune 
si pentru sursele de tensiune, legea este respectata. In caz contrar, 
programul afiseaza un mesaj de eroare.

---

### Eliberarea memoriei

La finalul executiei, memoria alocata dinamic pentru componentele 
fiecarui fir este eliberata utilizand functia `free()`. De asemenea, 
memoria alocata pentru vectorul de fire este eliberata.

***

## Segment_display

### Functia `main(void)`

In functia `main`, programul citeste dimensiunile matricei (numarul de
linii si coloane) si lungimea segmentelor care formeaza cifra ce va fi
afisata. Dupa aceasta, programul intra intr-un loop infinit in care
citeste comenzi de la utilizator, executand operatiile corespunzatoare pe
matricea de display, pana cand utilizatorul alege sa incheie programul prin
comanda `Q`. Comenzile posibile sunt: `F` (pentru a adauga o cifra pe
display), `W` (pentru a misca afisajul in sus), `S` (pentru a misca
afisajul in jos), `A` (pentru a misca afisajul spre stanga), `D` (pentru
a misca afisajul spre dreapta), `P` (pentru a printa matricea curenta).

---

### Functia `clear_input_buffer(void)`

Aceasta functie citeste un rand intreg dupa ce depisteaza o eroare pe
respectivul rand. Face asta pentru a nu afisa de mai multe ori decat este
necesar mesajul de eroare pentru comanda invalida.

---

### Functia `init_matrix(int n, int m, int display[][NMAX])`

Aceasta functie initializeaza matricea care reprezinta display-ul. Toate
valorile din matrice sunt setate la 0.

---

### Functia `print_matrix(int n, int m, int display[][NMAX])`

Aceasta functie este responsabila pentru afisarea matricei pe ecran. Pentru
fiecare element din matrice:
- Daca valoarea este 0, se afiseaza doua spatii
- Daca valoarea este 1, se afiseaza simbolul `^` urmat de un spatiu

---

### Functia `move_up(int display[][NMAX], int lines, int columns, long long
steps)`

Aceasta functie muta intregul display in sus. Mutarea se face pe baza unui
numar de pasi, care este efectiv redus la valoarea modulo `% lines`. 

---

### Functia `move_down(int display[][NMAX], int lines, int columns, long long
steps)`

Aceasta functie muta intregul display in jos. La fel ca in functia `move_up`,
mutarea este efectuata pe baza unui numar de pasi care este redus la valoarea
`% lines`.

---

### Functia `move_left(int display[][NMAX], int lines, int columns, long long
steps)`

Aceasta functie muta intregul display spre stanga. La fel ca in celelalte
functii de mutare, numarul de pasi este reduceri la valoarea `% columns`.

---

### Functia `move_right(int display[][NMAX], int lines, int columns, long long
steps)`

Aceasta functie muta intregul display spre dreapta. La fel ca in functiile de
mai sus, mutarea este efectuata pe baza unui numar de pasi ce este redus
`% columns`.

---

### Functia `fill_digit(int digit, int display[][NMAX], int n, int m, int len,
int wid)`

Aceasta functie umple matricea de display cu segmentele asociate unui
numar (digit) de la 0 la 9. Utilizand matricea predefinita de segmente pentru
fiecare cifra, functia seteaza valorile corespunzatoare in matricea `display`
pentru a reprezenta fiecare cifra. Matricea segments reprezinta un set de date
care defineste structura fiecarei cifre afisate pe display.
Fiecare rand al matricei corespunde unei cifre (de la 0 la 9), iar fiecare
coloana a matricei reprezinta segmentul aferent (a, b, c ...), fiecare element
indicand daca un anumit segment al cifrei este activ (1) sau inactiv (0).

## Instructiuni utilizare

Programele se compileaza cu regula make build, executabilele se sterg cu 
regula make clean, se ruleaza din terminal su comanda ./nume_program