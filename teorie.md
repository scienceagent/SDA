# 15.02.2024 Seminar SDA

Sunt analist de date pentru un magazin online care vinde o gama variata de produse magazinul a înregistrat toate tranzacțiile de vânzare din ultimul an într-un tabel excel și dorește să obțină o perspectivă mai clară asupra performanței de vânzări pentru a putea lua decizii informate privind stocurile de produse și strategiile de marketing.

## Date disponibile

Ai la dispoziție un fișier de tip .csv care conține următoarele coloane de date pentru fiecare tranzacție:

1. data_vânzării
2. id_produs
3. nume_produs
4. categorie_produs
5. subgategorie_produs
6. pret_unitar
7. cantitate_vîndută
8. țara_de_vânzare
9. orașul_de_vânzare

## Sarcina

Trebuie să creez un tablou dinamic (malloc), care să răsundă la următoarele intrebări de afaceri (BQ):

1. Care este venitul total generat în fiecare luna a anului
2. Care sunt primele 5 produse, cele mai bine vândute în dependentă de venitul generat
3. Cum se distribuie vânzările pe categorii de produse
4. Care sunt orașele cu cele mai mari vânzări pentru fiecare țară
5. Ce tendințe se observă în vânzările lunare pentru diferite subgategorii de produse (calculăm trend-ul) - generăm un tabel, verificăm cu cât au crescut vânzările față de luna precendentă, avem 2 rănduri per categorie relativ/absolut

## Pașii care trebuie de urmat

1. Creează o funcție de importare a datelor dintr-un fișier de tip .csv și inițializează un tablou dinamic de structuri, care să corespundă cu conținutul fișierului
2. Implementează funcții de grupare a elementelor din tablou în depedentă de diferite criterii(lună, an categorie, subgategorie, etc.)
3. Prevede câmpuri adiționale în strucura de date pentru a le utiliza la determinare parametrilor adiționali ca venit total, etc.
4. Folosește funcțiile de grupare pentru a segmenta (grupa) datele pentru a izola doar informațiile relevante pentru fiecare întrebare (BQ)
5. Creează tabele dinamice corelate rezultatelor calculelor efectuate pentru fiecare BQ pentru a ilustra în consolă răspunsurile și tendințele importante

## Rezultat așteptat

Se așteaptă un program care are meniu poate importa orice fișier de tip .csv cu datele necesare și oferă opțiuni pentru a răspunde la fiecare BQ

## Notă

1. Aplicația să fie capabilă să exporte rezultatele într-un raport textul
2. Aplicația permite generarea de grafice pe baza datelor calculate (librăria raylib)
