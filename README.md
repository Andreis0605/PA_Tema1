# Tema 1 PA

## Problema 1: Servere

### Principiu de rezolvare

> Initial, am incercat sa folosesc Brute Force pentru a intelege mai bine problema. Am observat ca functia care da puterea clusterului de servere are un singur maxim pe intervalul dat de valoarea minima si valoarea maxima a tensiunii de alimentare pentru servere.

> Dupa aceasta observatie, am ales sa folosesc cautarea binara pentru a gasi acest maxim. Astfel, caut in intervalul dat de maximul si minimul teniunilor de alimentare optime. Aflu mijlocului intervalului curent si ma uit la stanga si la dreapta acestuia. Daca puterea clusterului alimentat la cele doua valori este egala, atunci am gasit maximul. Daca nu, deduc panta facand diferenta intre stanga si dreapta si continui cautarea catre maxim. 

### Functii declarate si folosite la rezolvarea problemei

- `double min_pow(int N, vector<pair<int, int>> servers, double current)`
    > Functie care primeste un vector de servere, lungimea acestuia si o tensiunea de alimentare si returneaza puterea de calcul a clusterului de servere, calculata dupa formula din enunt 

- `void bsearch_maximum(double min_val, double max_val, int N,vector<pair<int, int>> servers, double &result)`
    > Functia primeste un interval de tensiuni de alimentare, un vector de servere, numarul de elemente din vector si o variablia in care va intoarce rezultatul. Aceasta cauta maximul functiei de putere in intervalul dat. Functia gaseste mijlocul intervalului si se uita in stanga (mijloc - 0.1) si in dreapta (mijloc + 0.1) si calculeaza puterea clusterului pentru aceste doua tensiuni de alimentare. Daca puterile in stanga si in dreapta sunt egale, acel punct e maxim. Daca nu, se deduce panta si se continua cautarea inspre maxim. 

## Problema 2:

### Principiu de rezolvare

>Se observa ca numarul total de combinatii de culori este dat de o formula. Aceasta depinde de tipul primei zone si de trecerile de la o zona la alta (in special de la orizontal la vertical si invers). Pentru a putea calcula numarul de zone, folosim ridicarea la putere in timp logaritmic, deoarece valorile exponentilor pot fi foarte mari, iar o ridicare la puterere liniara nu ar fi eficienta. In plus, aceasta metoda usureaza limitarea valorilor la maximul impus de problema.

### Functii declarate si folosite la rezolvarea problemei

- `unsigned long long logarithmic_power(unsigned long long base, int exponent`
    >Functia primeste o baza si un exponet. Aceasta efectueaza ridicarea la putere in timp logaritmic, asa cum a fost prezentata la curs si la laborator. Valoarea rezultatului este limitata de valoarea 10<sup>9</sup> + 7 data de problema.

## Problema 3: Compresie

### Principiu de rezolvare

> Pentru a putea rezolva problema, am ales sa parcurg cele doua siruri in paralel (similar cu interclasarea), folosind doua sume (una pentru fiecare sir). Iinitial, cele doua sume au valoarea primului element din fiecare sir. Apoi, principiul de rezolvare este urmatorul: daca cele doua sume sunt egale, am gasit o zona care se poate compresa, o numar, resetez sumele si trec la urmatorul element in ambele siruri; daca nu, adun la cea mai mica suma elementul urmator din sirul respectiv. La final, verific ca am terminat de parcurs ambele siruri. Daca nu, inseamna ca nu se poate efectua compresia.

## Problema 4: Criptat

### Principiu de rezolvare

> La citire, prelucrez cuvintele pentru a le retine doar frecventa literelor si lungimea. Folosesc un vector de codificari pentru a da fiecarei din cele 8 litere o valoare pentru a le putea marca mai usor in vectorii de frecventa.

> Dupa aceea, calculez lungimea celei mai mari parole posibile si marchez intr-un vector toate lungimile posibile ale parolei

> Pentru fiecare litera in parte, folosesc un vector cu semnificatia dp[i] = frecventa literei curente in parola de lungimea i. La fiecare pas trebuie sa verific ca o parola de acesata lungime este posibila. La sfarsit, parcurg vectorul si caut cea mai lunga parola posibila care are litera curenta dominanta. Dupa ce efectuez aceasta operatiune pentru fiecare litera in parte, voi gasi cea mai lunga parola posibila.

### Functii si structuri declarate si folosite la rezolvarea problemei

- `typedef struct word { int frq[10]; int len; } word;`

    > Structura care va retine frecventa literelor unui cuvant si lungimea acesuia

- `int total_len_freq_array(int *array)`
    > Functie care primeste un vector de frecventa si face suma tuturor campurilor din acel vector (aceasta functie este corecta doar pentru problema curenta, deoarece depinde de limitarile acesteia).

## Problema 5: Oferta

### Pirncipiu de rezolvare
> Initial, tratez cele trei cazuri de baza: cand am un singur produs, doua produse sau trei produse. In continuare, tratez cazul general. Folosesc un vector cu semnificatia dp[i] = pretul cel mai mic pe care il putem obtine folosind i produse. Marchez cazurile de baza si incep sa calculez valorile din vector folosind formula de recurenta(in care p1, p2, p3 este o secventa de produse, in aceasta ordine) : dp[i] = min(dp[i-1] + p3, dp[i-2] + oferta_doua(p2, p3), dp[i-3] + oferta_trei(p1, p2, p3)). La final, valoarea cautata se gaseste in dp[N].

### Functii declarate si folosite la rezolvarea problemei

- `double two_discount(int product1, int product2)`
    > Functia primeste pretul a doua produse si returneaza pretul total dupa aplicarea ofertei pentru doua produse.

- `double three_discount(int product1, int product2, int product3)`
    > Functia primeste pretul a trei produse si returneaza pretul total dupa aplicarea ofertei pentru trei produse.