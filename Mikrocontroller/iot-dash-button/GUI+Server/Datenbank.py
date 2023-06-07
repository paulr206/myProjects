import tkinter.messagebox
from tokenize import String
from unittest import result
import mysql.connector
from tkinter import *

# Funktion zum Erstellen der Datenbank
#mycursor.execute("CREATE DATABASE lebensmittelautomat")

# Funktion zum Erstellen der article und balance Tabelle
#mycursor.execute("CREATE TABLE articles (id INT, name VARCHAR(30), stock Int, price Int, PRIMARY KEY(id));")
#mycursor.execute("CREATE TABLE balance (balance INT);")

# Erstellen der Datensätze
sql = "INSERT INTO articles (id, name, stock, price) VALUES (%s, %s, %s, %s)"
sql0 = "INSERT INTO balance (balance) VALUES (100);"
val0 = (0, "Äpfel", 0, 1)
val1 = (1, "Birnen", 0, 2)
val2 = (2, "Kirschen", 0, 1)
val3 = (3, "Honig", 0, 4)
val4 = (4, "Eier", 0, 2)
#mycursor.execute(sql, val0)
#mycursor.execute(sql, val1)
#mycursor.execute(sql, val2)
#mycursor.execute(sql, val3)
#mycursor.execute(sql, val4)
# mycursor.execute(sql0)
# mydb.commit()

# Funktion zum Anzeigen aller Bestände


def showAllData(mycursor):
   mycursor.execute("SELECT * FROM articles;")
   result = mycursor.fetchall()
   for _ in result:
      print(_)

# Funktion zum Aktualisieren aller Bestände


def updateStock(db, mycursor, articleId, newStock):
   sql = "UPDATE articles SET stock = " + str(newStock) + " WHERE id = " + str(articleId) + ";"
   mycursor.execute(sql)
   db.commit()

# Funktion zum Anzeigen der Informationen eines bestimmten Artikels


def showDataOfArticle(mycursor, articleId):
   sql = "SELECT * FROM articles WHERE id = " + str(articleId) + ";"
   mycursor.execute(sql)
   result = mycursor.fetchall()
   for _ in result:
      print(_)

# Srtikelbestand abrufen


def getArticleStock(mycursor, articleId):
   sql = "SELECT stock FROM articles WHERE id = " + str(articleId) + ";"
   mycursor.execute(sql)
   result = mycursor.fetchone()
   print("getArticleStock: Artikel " + str(articleId) + ": " + str(result[0]))
   return result[0]

# Artikelpreis abrufen


def getArticlePrice(mycursor, articleId):
   sql = "SELECT price FROM articles WHERE id =" + str(articleId) + ";"
   mycursor.execute(sql)
   result = mycursor.fetchone()
   print(result[0])
   return result[0]

# Bestand erhöhen


def addStock(db, mycursor, articleId, count):
   # vorherigen Bestand abfragen
   oldStock = getArticleStock(mycursor, articleId)
   # Bestand aufaddiert aktualisieren
   newCount = int(oldStock) + int(count)
   updateStock(db, mycursor, articleId, newCount)

# Kontostand abrufen


def getBalance(db, mycursor):
   sql = "SELECT balance FROM balance"
   mycursor.execute(sql)
   result = mycursor.fetchone()
   return result[0]

# Kontostand erhöhen


def raiseBalance(db, mycursor, amount):
   oldB = getBalance(db, mycursor)
   sum = int(oldB) + int(amount)
   updateBalance(db, mycursor, sum)
   print("Guthaben wurde von " + str(oldB) + " auf " + str(sum) + " erhöht.")

# Kontostand verringern


def lowerBalance(db, mycursor, amount):
   oldB = getBalance(db, mycursor)
   sum = oldB - amount
   sql = "UPDATE balance set balance = " + str(sum)
   mycursor.execute(sql)
   db.commit()
   print("Guthaben wurde von " + str(oldB) + " auf " + str(sum) + "verringert.")


def updateBalance(db, mycursor, val):
   sql = "UPDATE balance SET balance = " + str(val) + ";"
   mycursor.execute(sql)
   db.commit()
