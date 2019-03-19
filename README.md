# Decode-captcha-images-C-Language

Pislari Vadim -> Facultatea Automatica si Calculatoare -> Universitatea Politehnica Bucuresti

                                                 (Romanian language)
                                               -------DESCRIERE-------

O imagine BMP are urmatoarea structura:
signature – 2 octeti - literele 'B' si 'M' in ASCII;
file size – 4 octeti – dimensiunea intregului fisier;
reserved – 4 octeti – nefolosit;
offset – 4 octeti – offsetul de la inceputul fisierului pana la inceputului bitmap-ului, adica al matricii de pixeli.
size – 4 octeti – dimensiunea Info Header-ului;
width – 4 octeti – latimea matricii de pixeli;
height – 4 octeti – inaltimea matricii de pixeli ;
planes – 2 octeti – setat la valoarea fixa 1;
bit count – 2 octeti – numarul de biti per pixel. 
compression – 4 octeti – tipul de compresie. 
image size – 4 octeti – se refera la dimensiunea matricii de pixeli, inclusiv padding-ul adaugat;
x pixels per meter – 4 octeti – se refera la rezolutia de printare.
y pixels per meter – la fel ca mai sus;
colors used – numarul de culori din paleta de culori. 
colors important – numarul de culori importante. 

1.Schimbarea culorii tuturor cifrelor din imagine. 
Se primeste o imagine si un numar intreg intre 0 si 255, care va reprezenta noua culoare a imaginii.
Cu exceptia matricei de pixeli, toate celelalte valori din imaginea initiala raman neschimbate;

2.Recunoasterea cifrelor din imagine.
Numarul format are cifrele ordonate de la stanga la dreapta.
Cifrele pot incepe oriunde in imagine (atata timp cat nu depasesc dimensiunea imaginii).
Cifrele nu se intersecteaza si oricare doua cifre sunt separare de cel putin o linie sau o coloana;
Nu exista 2 cifre care sa inceapa pe aceeasi coloana.

3.Eliminarea unor cifre din imagine.
Programul primeste o lista de cifre si le elimina din imagine daca acestea se regasesc. Dupa eliminarea unei cifre toate celelalte cifrele ce se afla la dreapta ei sunt mutate spre stanga in felul urmator:
-Prima cifra de dupa o cifra eliminata ia locul cifrei eliminate;
-Urmatoarea cifra ia locul cifrei recent mutate;

4. Schimbarea culorii in functie de localizarea "luminitelor de Craciun". 
Sunt adaugate cateva puncte random pe imagine. Aceste puncte au marime fixa de un pixel si raza de actiune 7. Punctele reprezinta beculete de craciun, beculete ce lumineaza cifrele din captcha. Culoarea fiecarui pixel ce apartine unei cifre se schimba in functie de culoarea initiala si culorile beculetelor in a caror raza se afla. Pentru calcularea noii culori se foloseste o medie aritmetica asupra fiecare valori din RGB.
