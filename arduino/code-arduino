// Libraries
 
#include <DHT.h>
 
#include <LiquidCrystal.h>
 
// Définition des pins pour l'écran LCD
 
#define rs A0
 
#define en A1
 
#define d4 6
 
#define d5 5
 
#define d6 4
 
#define d7 3
 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
// Définition du capteur DHT
 
#define data 2
 
DHT dht(data, DHT11);
 
unsigned long previousMillis = 0;  // Stocke le dernier temps de mise à jour
 
const long interval = 2000;        // Intervalle de 10 secondes (10000 ms)
 
float lastTemp = 0.0;  // Dernière température lue
 
float lastHum = 0.0;   // Dernière humidité lue
 
void setup() {
 
  dht.begin();          // Initialisation du capteur
 
  Serial.begin(9600);   // Initialisation de la communication série
 
  lcd.begin(16, 2);     // Initialisation de l'écran LCD
 
}
 
void loop() {
 
  unsigned long currentMillis = millis();  // Récupère le temps écoulé
 
  // Vérifie si 10 secondes se sont écoulées
 
  if (currentMillis - previousMillis >= interval) {
 
    previousMillis = currentMillis;  // Sauvegarde le temps actuel
 
    // Lire l'humidité et la température
 
    float h = dht.readHumidity();
 
    float t = dht.readTemperature();
 
    // Vérifier que les lectures sont valides
 
    if (!isnan(t) && !isnan(h)) {
 
      lastTemp = t;
 
      lastHum = h;
 
      // Affichage sur le port série
 
      Serial.print("DATA:");
 
      Serial.print(lastTemp);
 
      Serial.print(",");
 
      Serial.println(lastHum);
 
    } else {
 
      Serial.println("Erreur lecture capteur !");
 
    }
 
    // Mise à jour de l'affichage LCD
 
    lcd.clear();  // Efface l'écran LCD avant d'afficher les nouvelles données
 
    lcd.setCursor(0, 0);
 
    lcd.print("Temp : | Hum :  ");
 
    lcd.setCursor(0, 1);
 
    lcd.print(lastTemp); lcd.print("*C | ");
 
    lcd.print(lastHum); lcd.print("%   ");
 
  }
 
}
 
 