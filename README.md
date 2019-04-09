Stasjon 1: Få roboten til å kjøre mot lyset
På denne stasjon skal du få roboten til å kjøre mot lyset. Foran på roboten kan du se to lysfølsomme motstande, som kan brukes til å sense hvor mye lys som er tilstede. Disse to skal du bruke til å navigere roboten. Det forventes ikke at du kan lage alle øvelserne selv, men det vil være mentorer tilstede som kan hjelpe med disse.
Al kode er markeret med grøn tekst som du kan kopiere ind i dit program, dersom du ikke vil skrive det selv 😊
På dette link finder du en færdig versjon af koden du skal lave, og du kan hente hjelp her dersom du trenger det. Det vil i hver oppgave også være henvisninger til bestemte linjer kode i denne fil.
Dersom du allerede har gjennemført noen af øvelserne på en tidligere stasjon trenger du ikke å lage disse igjen, men du kan bruke koden fra tidligere. Husk derfor å lagre dit program når du er ferdig.
Bliver du ferdig med øvelserne før tid, kan du enten velge å fortsette med de foreslåtte øvelser eller å lage dit eget program.
Opgaver:
1.	Start med å åpne et tomt Arduino program.
2.	Først skal vi få roboten til å kjøre frem. For å bruke de fire motorer på roboten må vi tilføje disse fem linjer i starten af programmet:

#include <UCMotor.h>
UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);

Nå kan du styre hver enkelt motor ved å give den en retning og en hastighed. Hvis du for eksempel vil få venstre motor foran til å kjøre frem må du skrive dette i din loop funksjon:
leftMotor1.run(0x01); 			(“0x02” vil få motoren til å kjøre baglæns)
leftMotor1.setSpeed(200);		(farten sættes her til 200)

3.	For å skabe mere overblik i programmet, kan du lave funksjoner, som indeholder kode. Nu skal du lave en funksjon der får roboten til å kjøre frem (som du gjorde i forrige opgave). Et eksempel på en funksjon er dette:

void minFunksjon() {
    // mellem disse to “{ }” skal du skrive alt det kode, som din funksjon skal udføre.
}

Du kjører din funktion ved å skrive funksjonens navn:
	
void loop() {
minFunksjon();
}

4.	Lav nu funksjoner der får roboten til å:		(SE LINJE 69-100 I FERDIG VERSJON)
a.	Kjøre til venstre
b.	Kjøre til højre
c.	Stoppe
Husk at du må bruke «delay()» mellem hver funksjon du kjører. Dette får programmet til å vente med å kjøre videre i programmet. Hvis du for eksempel vil kjøre frem i to sekunder, må du skrive:
funksjon_frem();
delay(2000);
funksjon_stop();

5.	Nå er du klar til å hente data fra de to lyssensorer. For å bruke disse må du sætte begge sensorer til å være input. Først skal du tilføje disse to linjer før din setup funksjon: 	(SE LINJE 10-11 I FERDIG VERSJON)

const int LIGHT_PIN_RIGHT = A5;
const int LIGHT_PIN_LEFT = A4;
	Og disse tre linjer må du sette ind i din setup funksjon (LINJE 17-20 I FERDIG VERSJON):
Serial.begin(9600);
pinMode(LIGHT_PIN_RIGHT, INPUT);
pinMode(LIGHT_PIN_LEFT, INPUT);
Du kan hente data fra de to sensorer ved å skrive «analogRead(pin)». Disse data kan gemmes som to forskjellige variabler. Du kan printe de to variabler ved å bruke Serial.print(). Se eksemplet herunder:
void loop() {
	int Light_right = analogRead(LIGHT_PIN_RIGHT);
int Light_left = analogRead(LIGHT_PIN_LEFT);

Serial.print("Right sensor: "); Serial.println(Light_right);
Serial.print("Left sensor: "); Serial.println(Light_left);
Serial.println("");

delay(500);
}
	Prøv å kopiere koden herover og lys med din telefon på de to sensorer.
6.	De to lyssensorer kan måle litt forskjellige verdier, selvom der i virkeligheden er like mye lys som rammer begge sensorer. Vi må derfor nulstille sensorerne efter omgivelserne. Dette gør vi ved å lave 100 målinger og finde gennemsnittet af disse. Dette gennemsnit må vi trække fra hver fremtidig måling (du trenger ikke å forstå dette helt, men du kan bare kopiere koden ind i dit program). 
For å gjøre dette må du tilføje disse to linjer før din setup funksjon:

unsigned int offset_right = 0;
unsigned int offset_left = 0;

Og disse linjer må du indsætte i din setup funksjon:

for (int i=0; i<100; i++){
      offset_right += analogRead(LIGHT_PIN_RIGHT);
      offset_left += analogRead(LIGHT_PIN_LEFT);
      delay(20);
}
offset_right = offset_right/100;
offset_left = offset_left/100;
Nu kan du prøve å hente data fra sensorerne igjen, hvor du trækker gennemsnitsmålingen fra hver nye måling (du kan kopiere koden herunder):
void loop() {
int Light_right = analogRead(LIGHT_PIN_RIGHT)-offset_right;
int Light_left = analogRead(LIGHT_PIN_LEFT)-offset_left;

Serial.print("Right sensor: "); Serial.println(Light_right);
Serial.print("Left sensor: "); Serial.println(Light_left);
Serial.println("");

delay(500);
}

7.	For å styre roboten mot lyset må vi bruke data fra begge sensorer.  Vi skal ut fra disse data bestemme hvilken af disse fire muligheter den skal vælge:
a.	Stop: hvis der ikke er tilstrækkeligt lys på noen af sensorerne
b.	Kjør ret frem: hvis der er like mye lys på begge sensorer
c.	Kjør til højre: hvis der er mest lys på sensoren til højre
d.	Kjør til venstre: hvis der er mest lys på sensoren til venstre

For å sammenligne de to værdier findes differensen mellem dem og gemmes som en variabel «diff»:

int diff = Light_right-Light_left;

Hvis verdien af “diff” er positiv er der mest lys på højre sensor. Hvis verdien er negativ er der mest lys på venstre sensor. Nu skal du ved bruk af if/else statements velge hvilke af de fire funksjoner som skal kjøres. Hvis forskjellen på de to sensor-verdier er mindre end 10 skal den kjøre ret frem, og hvis ingen af sensor-verdierne er større end 10 må den stoppe (HINT: SE LINJE 41-59 I KODEN FOR HJELP). 
8.	Tag en måling af lyset 20 gange i sekundet ved å bruke ”delay(50)”. 
Du er nå klar til å teste dit ferdige program. Find et mørkt rum og lys med din telefon foran roboten. Husk å lade roboten være tændt i cirka tre sekunder før du tænder for lyset, så den kan nulstille sensorerne.
9.	Har du mere tid kan du få roboten til å stoppe hvis der kommer en forhindring. For å bruke afstandssensoren må du tilføje disse linjer før din setup funksjon:

#include <Ultrasonic.h>
Ultrasonic ultrasonic(A2, A3);
	Afstanden kan nu gemmes som variablen ”dist” ved at bruge denne linje kode i dit program:
		  int  dist = ultrasonic.distanceRead();
Du kan nu tilføje en if-statement der får roboten til å stoppe hvis afstanden eksempelvis er mindre end 40 (enheden er i centimeter).
