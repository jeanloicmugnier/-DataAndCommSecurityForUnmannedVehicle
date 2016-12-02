from Tkinter import * 
import serial

# Initialisation des variables necessaires
arduino = serial.Serial('/dev/ttyUSB0', 115200)
arduino.timeout = 1.5

# Definition des fonctions
def alert():
    showinfo("alerte", "Bravo!")

def record(btn, str):
	if(btn.cget("relief")=="raised"):
		btn.config(relief = "sunken")
		arduino.write("rec "+str)
	else :
		btn.config(relief="raised")
		arduino.write("srec "+str)

def sendCommand(str):
	arduino.write(str)

# Initialisation de la fenetre
fenetre = Tk()
fenetre.wm_title("Rover controller")

# Menus
menubar = Menu(fenetre)
menu1 = Menu(menubar, tearoff=0)
menu1.add_command(label="Initialiser", command=alert)
menu1.add_command(label="Autre menu", command=alert)
menu1.add_separator()
menu1.add_command(label="Quitter", command=fenetre.quit)
menubar.add_cascade(label="Communication", menu=menu1)
menu2 = Menu(menubar, tearoff=0)
menu2.add_command(label="Couper", command=alert)
menu2.add_command(label="Copier", command=alert)
menu2.add_command(label="Coller", command=alert)
menubar.add_cascade(label="Menu", menu=menu2)
menu3 = Menu(menubar, tearoff=0)
menu3.add_command(label="Tutoriel", command=alert)
menubar.add_cascade(label="Aide", menu=menu3)
fenetre.config(menu=menubar)

# Frame de texte
l = LabelFrame(fenetre, text="Informations", padx=20, pady=20)
l.grid(row=1, column=1, columnspan=7)
texte = Label(l, text="Texte a l'interieur de la frame", height = 30, width = 120).grid(row=1, column=2)

# Autre(s) texte(s) & Espacement des ensembles de boutons
Label(fenetre, text="          ").grid(row=3, column=4)
Label(fenetre, text="Capture de donnees").grid(row=2, column=1)
Label(fenetre, text="Controle du rover").grid(row=2, column=5)

# Placement des boutons
btn_pressure = Button(fenetre, text ='Pression').grid(row=3, column=1, sticky=N+E+W+S)
btn_pressure(command=record(btn_pressure, "pressure"))
btn_tst = Button(fenetre, text ='Autre...', command=record(self, "tst")).grid(row=4, column=1, sticky=N+E+W+S)
btn_vitmota = Button(fenetre, text ='Vitesse moteur A', command=record(self, "vitmota")).grid(row=3, column=2, sticky=N+E+W+S)
btn_vitmotb = Button(fenetre, text ='Vitesse moteur B', command=record(self, "vitmotb")).grid(row=4, column=2, sticky=N+E+W+S)
btn_fw = Button(fenetre, text ='Avancer', command=sendCommand("a")).grid(row=3, column=6, sticky=N+E+W+S)
btn_left = Button(fenetre, text ='Gauche', command=sendCommand("g")).grid(row=4, column=5, sticky=N+E+W+S)
btn_right = Button(fenetre, text ='Droite', command=sendCommand("d")).grid(row=4, column=7, sticky=N+E+W+S)
btn_bw = Button(fenetre, text ='Reculer', command=sendCommand("r")).grid(row=5, column=6, sticky=N+E+W+S)
btn_stop = Button(fenetre, text ='Stop', command=sendCommand("s")).grid(row=4, column=6, sticky=N+E+W+S)

# Loop principal
fenetre.mainloop()