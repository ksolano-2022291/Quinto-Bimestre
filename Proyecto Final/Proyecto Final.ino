/*
 * Fundación Kinal
 * Centro educativo técnico laboral Kinal
 * Electrónica
 * Grado: Quinto
 * Sección: "A"
 * Curso: Taller de Electronica y computacion I
 * Nombre: Kevin Audiel Solano Torres
 * Carnet:2022291
 * Proyecto: Proyecto final de año, Multimetro.
*/

#define RES A0
#define sensorVolt A1      

unsigned int raw_sensor = 0;
int Vol();
int txt();
int medicionR();
int Divisor;
char opcion;
String msg;
bool MT = true;
float sensibilidad=0.185;
float Vt=0;
float volt_sens = 0;
float vcc=5;
float R1=0;
float R2=10000;


void setup() 
{
Serial.begin(9600);
pinMode(sensorVolt, INPUT);    
}

void loop()
{
if (Serial.available())
{
opcion = Serial.read(); 
}

switch(opcion)
{
case 'A':
 if(MT){
 
  txt();
 MT=false;
break;

case 'V':
Vol();
break; 

case 'R':
medicionR();
Serial.println("Ohmios:");
break;
  
case 'C':
float Idc=calculoCorriente(100);
Serial.print("corriente: ");
Serial.println(Idc, 3);
delay(100);
break;
}
}
}
int medicionR()
{
Divisor=analogRead(RES);
if(Divisor)
{
Vt=analogRead(RES);
Vt=Vt*5/1023;
R1=(R2*5/Vt)-(R2);
Serial.println(R1);
delay(2000);
{
}
    
}else 
{
Serial.println("No Tiene Resistencia");
delay(500);
return 0;
}
}

int txt()
{
Serial.println("¿Qué Desea Medir?");
}

int Vol()
{
raw_sensor = analogRead(sensorVolt);      //Leo el valor medido por el pin analogico
volt_sens = fmap(raw_sensor,0,1023,0.0,25.0);   //Linealizo el valor leido y lo convierto 
Serial.print("Voltios: ");
Serial.println(volt_sens);
delay(1000);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
return (x-in_min)*(out_max - out_min)/(in_max - in_min) + out_min;
}

float calculoCorriente(int numeroMuestras)
{
float leerAcs712 = 0;
float intensidad = 0;
for(int i=0; i<numeroMuestras; i++)
{
leerAcs712 = analogRead(A3)*(5.02/1023.0);
intensidad=intensidad+(leerAcs712 - 2.5)/sensibilidad;
}
return(intensidad/numeroMuestras);
}
