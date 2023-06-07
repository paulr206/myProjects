from tkinter import *
import tkinter
from Datenbank import getArticleStock, updateStock, updateBalance, getBalance
import mysql.connector

from time import sleep, perf_counter
from threading import Thread


mydb = mysql.connector.connect(
    host="localhost",
    username="testuser",
    password="passwort",
    database="lebensmittelautomat"
)

mycursor = mydb.cursor()
articles = ["Äpfel", "Birnen", "Kirschen", "Honig", "Eier"]

# tkinter initialisieren
gui = Tk()

# Window titel festlegen
gui.title("Lebensmittelautomat")
gui.geometry("700x350")

# grid festlegen
gui.columnconfigure(0, weight=2)
gui.columnconfigure(1, weight=1)
gui.columnconfigure(2, weight=1)

# Stringvar Variablen anlegen
string_var0 = tkinter.StringVar()
string_var1 = tkinter.StringVar()
string_var2 = tkinter.StringVar()
string_var3 = tkinter.StringVar()
string_var4 = tkinter.StringVar()
string_var5 = tkinter.StringVar()


def LoadStringVars():
   global string_var0
   string_var0.set(articles[0] + " Bestand: " + str(getArticleStock(mycursor, 0)))
   global string_var1
   string_var1.set(articles[1] + " Bestand: " + str(getArticleStock(mycursor, 1)))
   global string_var2
   string_var2.set(articles[2] + " Bestand: " + str(getArticleStock(mycursor, 2)))
   global string_var3
   string_var3.set(articles[3] + " Bestand: " + str(getArticleStock(mycursor, 3)))
   global string_var4
   string_var4.set(articles[4] + " Bestand: " + str(getArticleStock(mycursor, 4)))
   global string_var5
   string_var5.set("Kontostand: " + str(getBalance(mydb, mycursor)))

def UpdateValue0():
   updateStock(mydb, mycursor, 0, int(E0.get()))
   LoadStringVars()
   E0.delete(0, 'end')


def UpdateValue1():
   updateStock(mydb, mycursor, 1, int(E1.get()))
   LoadStringVars()
   E1.delete(0, 'end')


def UpdateValue2():
   updateStock(mydb, mycursor, 2, int(E2.get()))
   LoadStringVars()
   E2.delete(0, 'end')


def UpdateValue3():
   updateStock(mydb, mycursor, 3, int(E3.get()))
   LoadStringVars()
   E3.delete(0, 'end')


def UpdateValue4():
   updateStock(mydb, mycursor, 4, int(E4.get()))
   LoadStringVars()
   E4.delete(0, 'end')


def UpdateBal():
   updateBalance(mydb, mycursor, int(E5.get()))
   LoadStringVars()
   E5.delete(0, 'end')

LoadStringVars()

# Erste Zeile
L0 = Label(gui, textvariable=string_var0, font=('Helevitica 15'))
L0.grid(row=0, column=0, padx=5, pady=10)
E0 = Entry(gui, bd=5, font=('Helevitica 15'))
E0.grid(row=0, column=1, padx=5, pady=5)
B0 = Button(text="Aktualisieren", command=UpdateValue0, font=('Helevitica 15'))
B0.grid(row=0, column=2, padx=5, pady=5)

# Zweite Zeile
L1 = Label(gui, textvariable=string_var1, font=('Helevitica 15'))
L1.grid(row=1, column=0, padx=5, pady=10)
E1 = Entry(gui, bd=5, font=('Helevitica 15'))
E1.grid(row=1, column=1, padx=5, pady=5)
B1 = Button(text="Aktualisieren", command=UpdateValue1, font=('Helevitica 15'))
B1.grid(row=1, column=2, padx=5, pady=5)

# Dritte Zeile
L2 = Label(gui, textvariable=string_var2, font=('Helevitica 15'))
L2.grid(row=2, column=0, padx=5, pady=10)
E2 = Entry(gui, bd=5, font=('Helevitica 15'))
E2.grid(row=2, column=1, padx=5, pady=5)
B2 = Button(text="Aktualisieren", command=UpdateValue2, font=('Helevitica 15'))
B2.grid(row=2, column=2, padx=5, pady=5)

# Vierte Zeile
L3 = Label(gui, textvariable=string_var3, font=('Helevitica 15'))
L3.grid(row=3, column=0, padx=5, pady=10)
E3 = Entry(gui, bd=5, font=('Helevitica 15'))
E3.grid(row=3, column=1, padx=5, pady=5)
B3 = Button(text="Aktualisieren", command=UpdateValue3, font=('Helevitica 15'))
B3.grid(row=3, column=2, padx=5, pady=5)

# Fünfte Zeile
L4 = Label(gui, textvariable=string_var4, font=('Helevitica 15'))
L4.grid(row=4, column=0, padx=5, pady=10)
E4 = Entry(gui, bd=5, font=('Helevitica 15'))
E4.grid(row=4, column=1, padx=5, pady=5)
B4 = Button(text="Aktualisieren", command=UpdateValue4, font=('Helevitica 15'))
B4.grid(row=4, column=2, padx=5, pady=5)

# sechsete Zeile
L5 = Label(gui, textvariable=string_var5, font=('Helevitica 15'))
L5.grid(row=5, column=0, padx=5, pady=10)
E5 = Entry(gui, bd=5, font=('Helevitica 15'))
E5.grid(row=5, column=1, padx=5, pady=5)
B5 = Button(text="Aktualisieren", command=UpdateBal, font=('Helevitica 15'))
B5.grid(row=5, column=2, padx=5, pady=5)


def updateGUI():
   while 1:
      LoadStringVars()
      print("Update")
      gui.update()
      sleep(5)



t1 = Thread(target=updateGUI)
t1.start()

# Fenster anzeigen
gui.mainloop()
