Beste allemaal,

## Practicum 3

Het 3e practicum staat online, op yOUlearn in de cursusstructuur, en in de GitHub repo van FramboOS.
Jullie gaan een pong screensaver bouwen die gebruik maakt van een losse update en render taak.
De synchronisatie tussen deze twee taken gebeurt mbv zelfgeschreven spinlocks.
Voor deze opdracht heb je langer de tijd dan de vorige twee, tot en met 9 januari, aangezien de kerst er tussen zit.

Nog wat tips van ons:

* Maak goed gebruik van de `uart_log_...` functies uit `include/hardware/uart.h` wanneer je tegen problemen aan loopt.
* Vergeet niet antwoord te geven op de niet-programmeer vragen uit.
  Wanneer je dit niet doet, beoordelen wij je practicum met een "onvoldaan" en, net als met tentamens, krijg je maar 3 pogingen voor elk practicum om het in te leveren.
* Stel vragen in de cursusstructuur aan je tutor of stel algemene vragen op het discussieforum van yOUlearn.

## Versie Qemu en WSL

Het was even puzzelen, maar ondanks dat wij eerder dachten dat je prima uit de voeten kunt met Qemu versie 5, blijkt dit toch *niet* het geval!
Je hebt *echt* versie 6 of hoger nodig, en emuleren van FramboOS op de machine `raspi2` (zonder de `b`) werkt *niet* naar behoren.
(Dit naar aanleiding van studenten die dit op yOUlearn hebben aangegeven, dank daarvoor!)

Dat betekent dat je, wanneer je WSL onder Windows draait, er *echt* voor moet zorgen dat je WSL versie 2 draait,
je hele Ubuntu installatie *moet* updaten naar versie 22.04,
en vervolgens Qemu *moet* updaten naar versie 6.
Deze instructies staan in de README van FramboOS, daar kun je ze nog steeds vinden.
Met klem: doe dit!

## Bereikbaarheid

Gedurende de feestdagen zijn wij minder bereikbaar dan anders.
Tot en met 1 januari lezen wij allemaal geen mail en kijken niet op yOUlearn.
De week er op gaan wij weer langzaam aan het werk, de een iets eerder dan de andere.
Houd hier rekening mee bij het maken van het practicum.

Wij wensen jullie allemaal fijne feestdagen en een mooie jaarwisseling toe!
Team BS
