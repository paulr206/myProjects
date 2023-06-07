from tkinter import *
import tkinter
from Datenbank import getArticleStock, updateStock
import mysql.connector


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
gui.geometry("600x400")

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


LoadStringVars()


def UpdateValue0():
   updateStock(0, int(E0.get()), mycursor, mydb)
   LoadStringVars()


def UpdateValue1():
   updateStock(1, int(E1.get()), mycursor, mydb)
   LoadStringVars()


def UpdateValue2():
   updateStock(2, int(E2.get()), mycursor, mydb)
   LoadStringVars()


def UpdateValue3():
   updateStock(3, int(E3.get()), mycursor, mydb)
   LoadStringVars()


def UpdateValue4():
   updateStock(4, int(E4.get()), mycursor, mydb)
   LoadStringVars()


# Erste Zeile
L0 = Label(gui, textvariable=string_var0, font=('Helevitica 15'))
L0.grid(row=0, column=0, padx=5, pady=5)
E0 = Entry(gui, bd=5)
E0.grid(row=0, column=1, padx=5, pady=5)
B0 = Button(text="Werte aktualisieren", command=UpdateValue0)
B0.grid(row=0, column=2, padx=5, pady=5)

# Zweite Zeile
L1 = Label(gui, textvariable=string_var1, font=('Helevitica 15'))
L1.grid(row=1, column=0, padx=5, pady=5)
E1 = Entry(gui, bd=5)
E1.grid(row=1, column=1, padx=5, pady=5)
B1 = Button(text="Werte aktualisieren", command=UpdateValue1)
B1.grid(row=1, column=2, padx=5, pady=5)

# Dritte Zeile
L2 = Label(gui, textvariable=string_var2, font=('Helevitica 15'))
L2.grid(row=2, column=0, padx=5, pady=5)
E2 = Entry(gui, bd=5)
E2.grid(row=2, column=1, padx=5, pady=5)
B2 = Button(text="Werte aktualisieren", command=UpdateValue2)
B2.grid(row=2, column=2, padx=5, pady=5)

# Vierte Zeile
L3 = Label(gui, textvariable=string_var3, font=('Helevitica 15'))
L3.grid(row=3, column=0, padx=5, pady=5)
E3 = Entry(gui, bd=5)
E3.grid(row=3, column=1, padx=5, pady=5)
B3 = Button(text="Werte aktualisieren", command=UpdateValue3)
B3.grid(row=3, column=2, padx=5, pady=5)

# Fünfte Zeile
L4 = Label(gui, textvariable=string_var4, font=('Helevitica 15'))
L4.grid(row=4, column=0, padx=5, pady=5)
E4 = Entry(gui, bd=5)
E4.grid(row=4, column=1, padx=5, pady=5)
B4 = Button(text="Werte aktualisieren", command=UpdateValue4)
B4.grid(row=4, column=2, padx=5, pady=5)

# Fenster anzeigen
gui.mainloop()
