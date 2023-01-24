#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <DHT.h>    // importa la Librerias DHT
#include <DHT_U.h>

//LEDS 
int lv1 =13;
int lv2 =12;
int lv3 =11;

int lr1 =10;
int lr2 =9;
int lr3 =8;
//Bomba en Pin7
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

int SensorPin = A0; /* Declaramos la entrada para lo que será la entrada analógica A0 la Nombraremos "SensorPin"*/
int Suelo = 0;
//DHT11
int SENSOR = 2;     // pin DATA de DHT11 a pin digital 2
int TEMPERATURA;
int HUMEDAD;
DHT dht(SENSOR, DHT11);

int speedw = 125;


void setup() {
  Serial.begin (9600);
  pinMode(7, OUTPUT); /* Declaramos Pin #7 como salida */
  digitalWrite (7, LOW);

  //LEDS
  pinMode(lv1, OUTPUT);
  pinMode(lv2, OUTPUT);
  pinMode(lv3, OUTPUT);
  pinMode(lr1, OUTPUT);
  pinMode(lr2, OUTPUT);
  pinMode(lr3, OUTPUT);
  // Inicializar el LCD
  lcd.setBacklightPin(3, POSITIVE); // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  dht.begin();      // inicializacion de sensor

  //Encender la luz de fondo.


  // Escribimos el Mensaje en el LCD.
  lcd.setCursor(0, 0);
  lcd.print("GROP-BOT");
  lcd.setCursor(1, 1);
  lcd.print("Elizabeth - Dario ");
  delay(500);
  lcd.clear ();
}

void loop() {

  lcd.clear ();
  int Suelo = analogRead(SensorPin);           //asignar los valores//
  Suelo = constrain (Suelo, 0, 1000);             /* Rango de medición */
  Suelo = map (Suelo, 0, 1000, 0, 100);      /*  valores porcentuales dentro del rango */

  //Serial.println  (Suelo);
  // Calculo del suelo
  if (Suelo <= 85) //* Agreagamos una condicion de funcionamiento en base a las lecturas*
  {
    Serial.print ("-Tierra mojada");
    Serial.println ("Bomba Apagada");
    digitalWrite(lv1, HIGH);
    digitalWrite(lv2, HIGH);
    digitalWrite(lv3, HIGH);
    digitalWrite(7, LOW); //Si se cumple la condicion la salida se desactiva, estado bajo *
    lgreen ();
  }
  else
  {
    Serial.print ("-Tierra Seca - ");
    Serial.println ("Bomba Activa");
    digitalWrite(lr1, HIGH);
    digitalWrite(lr2, HIGH);
    digitalWrite(lr3, HIGH);
    
    lcd.setCursor (0, 0);
    lcd.print ("Bomba Activa:");
    digitalWrite(7, speedw); // Si no se cumple la condicion la salida se activa, estado alto *
    delay (500);
    digitalWrite(7, LOW); // Si no se cumple la condicion la salida se activa, estado alto
    digitalWrite(lr1, LOW);
    digitalWrite(lr2, LOW);
    digitalWrite(lr3, LOW);
    delay (100);
    lcd.clear();
    delay (200);

  }
  TEMPE ();

  //Serial.print("Temperatura: ");  // escritura en monitor serial de los valores
  //Serial.print(TEMPERATURA);
  //Serial.print(" Humedad: ");
  //Serial.println(HUMEDAD);
  //delay(500);
  //Mostrar datos en Pantalla
  lcd.setCursor (0, 0);                                /* Posición inicial del texto*/
  lcd.print ("TEMP:");
  lcd.print(TEMPERATURA);                                     //Mostrar números finales//
  lcd.print("C");
  lcd.print (" HUM:");
  lcd.print (HUMEDAD);
  lcd.print ("%");

  lcd.setCursor (0, 1);
  lcd.print ("SUELO:");
  lcd.print (Suelo);
  lcd.print ("%");
  lcd.print ("  OK ;)");
  delay(1000);                                          //Espere segundos 0,1//
  lcd.clear();                                          //Limpie los caracteres adicionales//
  delay(100);
}



void TEMPE ()
{
  TEMPERATURA = dht.readTemperature();  // obtencion de valor de temperatura
  HUMEDAD = dht.readHumidity();   // obtencion de valor de humedad
}


void lred ()
{
  digitalWrite(lr1, HIGH);
  digitalWrite(lr2, HIGH);
  digitalWrite(lr3, HIGH);
  delay (100);
    
  digitalWrite(lr1, LOW);
  digitalWrite(lr2, LOW);
  digitalWrite(lr3, LOW);
  delay (100);
   
  }

void lgreen ()
{
  digitalWrite(lv1, HIGH);
  digitalWrite(lv2, HIGH);
  digitalWrite(lv3, HIGH);
  
  delay (200);  
  digitalWrite(lv1, LOW);
  digitalWrite(lv2, LOW);
  digitalWrite(lv3, LOW);
  
  delay (100);
}
