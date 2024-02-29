# Problemă: Optimizarea cozii de tipărire pentru N imprimante folosind liste simplu înlănțuite în limbajul C

## Context

O companie are N imprimante disponibile pentru tipărirea documentelor. Fiecare imprimantă poate tipări un rând dintr-un document într-un timp specific. Documentele sunt adesea compuse din mai multe rânduri. Scopul este de a gestiona eficient N imprimante astfel încât documentele să fie distribuite între imprimante în ordinea în care au fost puse în coadă, minimizând timpul total de așteptare pentru tipărire.

## Obiectiv

Implementați un sistem de gestionare a cozii de tipărire care să optimizeze distribuția documentelor între N imprimante, folosind liste simplu înlănțuite în C.

## Cerințe

1. Definiți o structură Document care să conțină cel puțin următoarele câmpuri:

   - Un identificator unic al documentului (de exemplu, un număr întreg)
   - Numele documentului
   - Numărul total de rânduri din document
   - Numărul de rânduri rămase de tipărit
   - Un pointer către următorul Document din listă

2. Definiți o structură Printer care să reprezinte o imprimantă și să conțină cel puțin următoarele:

   - Un identificator unic al imprimantei (de exemplu, un număr întreg)
   - Timpul necesar pentru tipărirea unui rând
   - Un pointer către documentul curent care se tipărește
   - Un pointer către următoarea Printer din listă

3. Implementați funcțiile necesare pentru a:

   - Inițializa lista de imprimante și a le atribui timpii de tipărire specifici
   - Adăuga un document nou în coada de tipărire
   - Distribui documentele din coadă către imprimante disponibile, astfel încât să minimizeze timpul total de așteptare (aceasta poate implica un algoritm care să ia în considerare timpul de tipărire al fiecărei imprimante și să aloce documentele în mod corespunzător)
   - Actualiza starea imprimantelor și a documentelor pe măsură ce rândurile sunt tipărite (aceasta poate implica simularea trecerii timpului și gestionarea rândurilor rămase de tipărit pentru fiecare document)
   - Afișa starea curentă a cozii de tipărire și a imprimantelor
   - Elibera memoria alocată pentru documente și imprimante atunci când nu mai sunt necesare

4. Scrieți o funcție main care demonstrează funcționalitatea sistemului de gestionare a cozii de tipărire. Inițializați sistemul cu un număr specific de imprimante și timpi de tipărire, adăugați o serie de documente în coadă și simulați procesul de tipărire.

## Bonus

- Implementați o funcție care să permită anularea unui document care este în așteptare în coadă sau care este în curs de tipărire.
- Adăugați o funcționalitate care să permită adăugarea sau scoaterea din funcțiune a imprimantelor în timp real (de exemplu, o imprimantă se defectează sau o nouă imprimantă este adăugată în sistem).

## Notă

Asigurați-vă că algoritmul de distribuție a documentelor între imprimante este eficient și că gestionați corect memoria pentru toate structurile de date folosite. De asemenea, trebuie să gestionați cazurile în care coada de tipărire este goală sau când toate imprimantele sunt ocupate.
