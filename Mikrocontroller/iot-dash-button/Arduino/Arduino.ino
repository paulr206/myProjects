#define ENCODER_DO_NOT_USE_INTERRUPTS
#include "rgb_lcd.h"
#include <ESP8266WiFi.h>
#include <Encoder.h>
#include <Wire.h>
#include <string.h>
#include <string>

rgb_lcd lcd;
Encoder myEnc(12, 14);

enum actions {
  userRequestedArticles,
  manufacturerAddedArticles,
  manufacturerRequestedPayOff
};


enum menues {
  selectUser,
  payOff_or_addArticle,
  payOff,
  addArticle,
  selectNumberOfArticles
};
enum users { customer, manufacturer };

bool pressed = false;
int activeMenu = selectUser;
int selectedUser = customer;
int selectedArticle = 0; // ausgewählter Artikel
int menuStepSize = 4;
int holdTime = 3000;
int sumOfArticles = 1; // Anzahl Artikel auswahl
int payOffMoney = 0;
int menuSelectionPayOffOrAddArticle = addArticle; // payOff_or_addArticle
const int LAST_ARTICLE = 5;
const int FIRST_ARTICLE = 0;
const int BACK_BUTTON = LAST_ARTICLE;
long position; // wird in setup() initialisiert
char *message = "";
char *articles[] = {"Apfel", "Birnen", "Kirsche",
                    "Honig", "Ei", "zurueck"}; // Liste der Artikel

// Serveradresse
char *serverIP = "172.16.18.155"; // Ip-adresse über cmd-Command ipconfig auslesen
const uint16_t serverPort = 8910;

// const char* ssid = "iPhone von Paul";    // ssid (Name WLAN)
// const char* wifiPw = "hotspotPaul2";  // Passwort WLAN
//const char* ssid = "FRITZ!BoxTR";    // ssid (Name WLAN)
//const char* wifiPw = "01031959TR";  // Passwort WLAN
//const char *ssid = "FRITZ!Box 7530 JR";      // ssid (Name WLAN) Marvin
//const char *wifiPw = "42424968210568278054"; // Passwort WLAN
// const char* ssid = "OnePlus 9";    // ssid Marvin
// const char* wifiPw = "z3ehhs97";  // Passwort WLAN
const char *ssid = "hackathonUCB";      // ssid (Name WLAN)
const char *wifiPw = "JpUXfsltubuu3131"; // Passwort WLAN


void setup() {

  lcd.begin(16, 2);
  /*
  lcd.clear();
  // lcd.setCursor(Spalte, Zeile)
  lcd.setCursor(0, 0);
  lcd.print("Default");
  */
  Serial.begin(115200);
  Wire.begin(); // ---- Initialisiere den I2C-Bus
  if (Wire.status() != I2C_OK)
    Serial.println("Something wrong with I2C");

  // Cursorposition initial auslesen
  position = myEnc.read();

  // WLAN initialisieren
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPw);
  printLine1("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Wifi connected with IP: ");
  Serial.println(WiFi.localIP());
  printLine1("Connected!");
}

void loop() {
  // myEncoder liest die Position des Dreh-/Drückstellers ein
  long newPos = myEnc.read();
  if (digitalRead(2) == HIGH) {
    pressed = false;
  }

  // handle button pressed
  if (!pressed && digitalRead(2) == LOW) {
    pressed = true;

    // wenn das aktive Menü "selectUser" ist, dann wird unterschieden zwischen
    // Kunde und Produzent wenn Kunde dann soll das nächste Menü "add Article"
    // sein wenn Produzent dann soll "payOff_or_addArticle" kommen
    if (activeMenu == selectUser) {
      switch (selectedUser) {

      case customer:
        activeMenu = addArticle;
        print("Artikel waehlen", "Apfel");
        break;

      case manufacturer:
        activeMenu = payOff_or_addArticle;
        print("Waehlen", "addArtikel");
        break;
      }
    }
    // wenn im Menü addArticle ein Artikel ausgewählt wurde
    else if (activeMenu == addArticle) {
      // wenn ein Artikel ausgewählt und NICHT zurück
      if (selectedArticle != BACK_BUTTON) {
        activeMenu = selectNumberOfArticles;
        print(articles[selectedArticle], "Anzahl: 1");
      }
      // wenn zurück
      else {
        goBack();
      }
    } else if (activeMenu == payOff_or_addArticle) {
      if (menuSelectionPayOffOrAddArticle == addArticle) {
        activeMenu = addArticle;
        print("Artikel waehlen", "Apfel");
      } else if (menuSelectionPayOffOrAddArticle == payOff) {
        activeMenu = payOff;
        
        print("Betrag waehlen", "Euro   0");
      }
    } else if (activeMenu == payOff) {
      // normalerweise Rolle, Artikel, Anzahl, Aktion
      // ABER in dem Fall brauchen wir keinen Artikel und dessen Anzahl, sondern verwenden
      // die Anzahl als Geldbetrag, der ausgezahlt werden soll
      String serverMessage = send_message(selectedUser, 0, payOffMoney, manufacturerRequestedPayOff);
      int result = serverMessage.substring(0,1).toInt();
      // Server meldet OK
      if(result == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gezahlt werden");
        lcd.setCursor(0, 1);
        lcd.print("Euro ");
        lcd.setCursor(6,1);
        lcd.print(payOffMoney);
      }
      else {
        print("Betrag in Kasse", "reicht nicht aus");
      }
      delayAndReset();
    }

    else if (activeMenu == selectNumberOfArticles) {
      // wenn Produzent, dann füge Daten der Datenbank hinzu
      
      if (selectedUser == manufacturer) {
        // Anzahl Artikel Bestand ändern
        String serverMessage = send_message(selectedUser, selectedArticle, sumOfArticles, manufacturerAddedArticles);
        int result = serverMessage.substring(0,1).toInt();
        if(result == 1){
          // Server meldet OK!
          if (sumOfArticles > 1) {
            print("Artikel wurden", "eingebucht!");
          } 
          else {
            print("Artikel wurde", "eingebucht!");
          }
        }
        else {
          // Fehler
          print("Artikel nicht", "gebucht - ERROR");
        }
        delayAndReset();
      }
      
      else if (selectedUser == customer) {
        // Datenbank Bestand prüfen und Kasse ändern
        String serverMessage = send_message(selectedUser, selectedArticle, sumOfArticles, userRequestedArticles);
        int result = serverMessage.substring(0,1).toInt();
        int costs = serverMessage.substring(2,4).toInt();
        if (result == 1) {
          //Bestand passt -> alles in Ordnung
          printLine1("zu zahlen:");
          lcd.setCursor(0, 1);
          lcd.print("Euro ");
          lcd.setCursor(6, 1);
          lcd.print(costs);
          delayAndReset();
        }
        else {
          // Bestand zu gering
          print("Bestand nicht", "ausreichend!");
          delayAndReset();
        }
      }
    }
  }

  // handle rotation
  else if ((newPos / 4) != (position / 4)) {

    if (activeMenu == selectUser) {
      switch (selectedUser) {
      case customer:
        selectedUser = manufacturer;
        printLine1("Produzent");
        break;
      case manufacturer:
        selectedUser = customer;
        printLine1("Kunde");
        break;
      }
    } else if (activeMenu == addArticle) {
      nextArticle(&newPos);
      print("Artikel waehlen", articles[selectedArticle]);
    } else if (activeMenu == selectNumberOfArticles) {
      setArticleCount(&newPos);
      lcd.setCursor(8, 1);
      lcd.print(sumOfArticles);
    } else if (activeMenu == payOff_or_addArticle) {
      switch (menuSelectionPayOffOrAddArticle) {
      case payOff:
        menuSelectionPayOffOrAddArticle = addArticle;
        print("Waehlen", "addArtikel");
        break;
      case addArticle:
        menuSelectionPayOffOrAddArticle = payOff;
        print("Waehlen", "Ausbezahlen");
        break;
      }
    } else if (activeMenu == payOff) {
      setPayoffCount(&newPos);
      print("Betrag waehlen", "Euro   ");
      lcd.setCursor(7, 1);
      lcd.print(payOffMoney);
    }
  }
  position = newPos;
  delay(1);
}

// Funktion zum Auswählen des Abzuhebenden Geldes
void setPayoffCount(long *newpos) {
  // Nach rechts gedreht
  if (*newpos < position) {
      payOffMoney++;
  }
  // Nach links gedreht
  else if (payOffMoney > 0) {
    payOffMoney--;
  }
}

// Funktion zum Auswählen der Artikelanzahl
void setArticleCount(long *newpos) {
  // Nach rechts gedreht
  if (*newpos < position) {
    sumOfArticles++;
  }
  // Nach links gedreht
  else if (sumOfArticles > 0) {
    sumOfArticles--;
  }
}

void print(char *text1, char *text2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
}

void printLine1(char *text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
}

void printLine2(char *text) {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(text);
}

// Funktion zum Umschalten der Artikel
void nextArticle(long *newPos) {
  // wenn nach rechts gedreht
  if (*newPos > position) {
    // wenn Ende der Liste erreicht
    if (selectedArticle == LAST_ARTICLE) {
      // Kopf wieder auf ersten Artikel
      selectedArticle = 0;
    } else {
      // Kopf mittendrin
      selectedArticle++;
    }
  }
  // nach links gedreht
  else {
    // wenn Anfang der Liste erreicht
    if (selectedArticle == FIRST_ARTICLE) {
      selectedArticle = LAST_ARTICLE;
    } else {
      selectedArticle--;
    }
  }
}

void goBack() {
  switch (activeMenu) {
  case addArticle:
    // wenn Kunde dann wieder in selectUser Menü ansonsten kommt man von
    // payOff_or_addArticle Menü
    if (selectedUser == customer) {
      activeMenu = selectUser;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kunde");
    } else {
      activeMenu = payOff_or_addArticle;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Waehlen:");
      lcd.setCursor(0, 1);
      lcd.print("add Artikel");
    }
    break;
  }
}

int getPriceOf(int _selectedArticle) {
  // 3 = Honig
  if (_selectedArticle == 3) {
    return 5;
  } else {
    return 1;
  }
}

// Funktion, um Daten zurückzusetzen (wenn ein Vorgang beendet wurde und man
// wieder zum Startmenü kommt -> wählt man dann Kunde wird noch der alte Artikel
// und Anzahl angezeigt)
void resetData() {
  selectedArticle = 0;
  sumOfArticles = 1;
  activeMenu = selectUser;
  selectedUser = customer;
  menuSelectionPayOffOrAddArticle = addArticle;
}

// zurückkehren zum Startmenü, nachdem Vorgang abgeschlossen ist
void resetTheMachine() {
  resetData();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kunde");
}

void delayAndReset() {
  delay(2000);
  print("Vielen Dank", "fuer Ihren Kauf!");
  delay(2000);
  resetTheMachine();
}

// Sendmessage übergibt Rolle, Artikel und Anzahl, Aktion (was soll gemacht werden?)
String send_message(int role, int article, int count, int action) {
  WiFiClient client;

  if (!client.connect(serverIP, serverPort)) {
    Serial.print(serverPort);
    Serial.print(serverIP);
    Serial.println("connection failed");
    Serial.println("wait 1 sec...");
    delay(1000);
    return "";
  }

  String message = String(role) + " " + String(article) + " " + String(count) + " " + String(action);
  client.println(message);
  Serial.print("Sent: ");
  Serial.println(message);
  String response = client.readStringUntil('\r');
  Serial.print("Received: ");
  Serial.println(response);

  client.stop();
  return response;
}

int get_Guthaben() {
  WiFiClient client;

  if (!client.connect(serverIP, serverPort)) {
    Serial.print(serverPort);
    Serial.print(serverIP);
    Serial.println("connection failed");
    Serial.println("wait 1 sec...");
    delay(1000);
    return -1;
  }

  client.println(5);
  Serial.print("Sent: ");
  Serial.println(message);
  int response = client.readStringUntil('\r').toInt();
  Serial.print("Received: ");
  Serial.println(response);

  client.stop();
  return response;
}