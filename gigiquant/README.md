Proiect PA – Analiză de piață

Acest proiect conține rezolvările pentru 4 taskuri din tema de Proiectarea Algoritmilor.  
Soluția este scrisă în C și este organizată modular, pe fișiere separate pentru fiecare task.

Despre proiect

Fiecare task folosește idei diferite:

Task 1 – calculul indicatorilor financiari:
  - randamente simple
  - medie
  - deviație standard
  - Sharpe Ratio

Task 2 – detectarea oportunităților de arbitraj între 3 piețe:
  - folosire de stive
  - folosire de coadă pentru păstrarea ordinii rezultatelor

Task 3 – identificarea perechilor de acțiuni:
  - transformarea evoluției în semnături de tip `U/D` (creștere/scădere)
  - compararea semnăturilor

Task 4 – model Markov pe intervale de preț:
  - stări definite prin intervale
  - probabilități reprezentate ca fracții ireductibile
  - actualizare iterativă a distribuției de probabilitate

Structuri de date folosite:

- listă simplu înlănțuită (Task 1)
- stivă (Task 2)
- coadă (Task 2)
- vectori (Task 3 și Task 4)
- fracții pentru păstrarea exactă a probabilităților (Task 4)

Structura fișierelor:

src/
    main.c
    list.c
    list.h
    task1.c
    task1.h
    task2.c
    task2.h
    task3.c
    task3.h
    task4.c
    task4.h

Rolul fișierelor: 
- main.c identifică automat taskul potrivit în funcție de formatul fișierului de input și apelează funcția corespunzătoare.
- list.c / list.h conțin implementarea listei simplu înlănțuite folosite la Task 1.
- task1.c / task1.h rezolvă Task 1.
- task2.c / task2.h rezolvă Task 2, folosind stive și coadă.
- task3.c / task3.h rezolvă Task 3.
- task4.c / task4.h rezolvă Task 4, folosind ideea de programare dinamică.

Compilare:

Din directorul proiectului: gcc src/main.c src/list.c src/task1.c src/task2.c src/task3.c src/task4.c -o src/test -lm

Testare:

Soluția a fost verificată folosind checkerul oferit pentru temă.
Pentru verificare se compilează proiectul și se rulează folosind fișierele de intrare și ieșire cerute de checker.

Rulare:

Programul primește două argumente: ./src/test input.txt output.txt
Exemplu: ./src/test in/data1.in out/data1.out

Observații:

- proiectul este organizat modular, astfel încât fiecare task să poată fi înțeles și testat separat.
- main.c nu rezolvă direct cerințele, ci doar alege taskul potrivit.
- pentru taskurile care lucrează cu numere reale, am avut grijă de formatul de afișare cerut de checker.

Posibile îmbunătățiri:

- mutarea unor funcții auxiliare într-un fișier separat;
- reducerea codului repetitiv dintre taskuri;
- refactorizare suplimentară pentru o organizare și mai clară;
- adăugarea unor teste locale automate.