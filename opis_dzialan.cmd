#define ROTATE_SPEED 30
/*
* Przykładowy zestaw poleceń
*/


Begin_Parallel_Actions
Move Samolot 0.2 24
Rotate Samolot -3 OX 360
Rotate Samolot.smiglo 30 OY 3600

Rotate Blok1 20 OZ 2400
Rotate Blok1 20 OY 2400
Rotate Blok2 20 OX 2400
Rotate Blok3 30 OX 3600
Rotate Blok4 -20 OX 2400
Rotate Blok5 -30 OX 3600
End_Parallel_Actions


Begin_Parallel_Actions
Move Samolot 0.2 5
Rotate Samolot -10 OZ 30
Rotate Samolot.smiglo 30 OY 750
End_Parallel_Actions
