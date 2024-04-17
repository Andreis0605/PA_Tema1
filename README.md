# Tema 1 PA

## Problema 1: Servere

### Principiu de rezolvare

> Initial, am incercat sa folosesc Brute Force pentru a intelege mai bine problema. Am observat ca functia care da puterea clusterului de servere are un singur maxim pe intervalul dat de valoarea minima si valoarea maxima a tensiunii de alimentare pentru servere.

> Dupa aceasta observatie, am ales sa folosesc cautarea binara pentru a gasi acest maxim. Astfel, caut in intervalul dat de maximul si minimul teniunilor de alimentare optime. Aflu mijlocului intervalului curent si ma uit la stanga si la dreapta acestuia. Daca puterea clusterului alimentat la cele doua valori este egala, atunci am gasit maximul. daca nu, deduc panta ... 

### Functii declarate si folosite la rezolvarea problemei

- `double min_pow(int N, vector<pair<int, int>> servers, double current)`
    > Functie care primeste un vector de servere, lungimea acestuia si o tensiunea de alimentare si returneaza puterea de calcul a clusterului de servere, calculata dupa formula din enunt 

- `void bsearch_maximum(double min_val, double max_val, int N,vector<pair<int, int>> servers, double &result)`
    > Functia primeste un interval de tensiuni de alimentare, un vector de servere, numarul de elemente din vector si o variablia in care va intoarce rezultatul. Aceasta cauta maximul functiei de putere in intervalul dat. Functia gaseste mijlocul intervalului si se uita in stanga (mijloc - 0.1) si in dreapta (mijloc + 0.1) si calculeaza puterea clusterului pentru aceste doua tensiuni de alimentare. Daca puterile in stanga si in dreapta sunt egale, acel punct e maxim. Daca nu, se deduce panta si se continua cautarea inspre maxim. 
