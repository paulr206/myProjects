from distutils.log import error
import socket
import mysql.connector
from Datenbank import getArticleStock, getArticlePrice, addStock, raiseBalance, lowerBalance, getBalance
# Server

mydb = mysql.connector.connect(
    host="localhost",
    username="testuser",
    password="passwort",
    database="lebensmittelautomat"
)

mycursor = mydb.cursor()

host = "0.0.0.0"      # IP adress of the Server
port = 8910             # Port used by the server

s = socket.socket()
s.bind((host, port))
s.listen(1)

while True:
   print("Server is running ...")
   client, addr = s.accept()
   print(f"Connected to {addr}")

   while True:
      print("Schleife beginnt")
      data = client.recv(1024)
      print(data)
      if data == b'\r\n':
         break
      
      ddata = data.decode()  # dekodierte Daten als String
      sdata = ddata.split()  # dekodierte Daten als Liste von Strings
      print(f"Received from client: {ddata}")  # Konsolenausgabe der Clientanfrage

      sdata[0] = int(sdata[0]) # Rolle
      sdata[1] = int(sdata[1]) # Artikel
      sdata[2] = int(sdata[2]) # Anzahl oder Geldbetrag
      sdata[3] = int(sdata[3]) # Aktion


      if (sdata[0] == 0):  # Kunde
         
         # Bestand des Artikel sdata[1]
         dbStock = getArticleStock(mycursor, sdata[1])
   
         # wenn Bestand in db größer als Anfrage -> ok
         if (dbStock >= sdata[2]):
            addStock(mydb, mycursor, sdata[1], sdata[2] * (-1))
            print("addStock ausgeführt")
            price = int(sdata[2]) * int(getArticlePrice(mycursor, sdata[1]))    # Summe gleich Anzahl mal Preis
            raiseBalance(mydb, mycursor, price)
            myString = "1 " + str(price)
            client.send(myString.encode())
            print("Kundenfall durchlaufen")
         # Fehlerfall! Bestand in db kleiner als Anfrage
         else:
            print("Bestand zu gering!")
            errorString = "0 " + str(0)
            errorString.encode()
            client.send(errorString)
            # sendto in python3
            # mystring = "0" + str(0)
            # byt = mystring.encode()
            # client.send(byt)

      elif (sdata[0] == 1):   # Produzent
         # wenn Aktion == "manufacturerAddedArticles"
         if (sdata[3] == 1):
            if (sdata[2] > 0):
               #Es werden Artikel hinzugefügt -> keine Negative Zahl oder 0
               addStock(mydb, mycursor, sdata[1], sdata[2])
               print("Artikel eingebucht!")
               myString = "1 0"
               client.send(myString.encode())
            else:
               # falsche Eingabe
               print("Artikel nicht eingebucht, weil Anzahl kleiner gleich 0!")
               myString = "0 0"
               client.send(myString.encode())
         # wenn Aktion == "manufacturerRequestedPayOff"
         elif (sdata[3] == 2):
            #buche Geld ab
            balance = getBalance(mydb, mycursor)
            #sdata[2] ist der Betrag! Guthaben größer als Anfrage?
            if(balance >= sdata[2]):
               print("Geld kann abgebucht werden")
               lowerBalance(mydb, mycursor, sdata[2])
               myString = "1 0"
               client.send(myString.encode())
            # Guthaben reicht  nicht aus
            else:
               myString = "0 0"
               client.send(myString.encode())

      print("Schleife beendet")

   #mydb.close()
