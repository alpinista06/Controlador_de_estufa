from PyQt4 import QtGui
import sys
import controlador_estufa
import serial
import random


'''Estrutura basica de um programa main do pyqt'''

class controlador(QtGui.QMainWindow, controlador_estufa.Ui_MainWindow):
    def __init__(self, parent=None):
        super(controlador, self).__init__(parent)
        self.setupUi(self)

        self.botao_regador.clicked.connect(self.regar)
        self.botao_ventilador.clicked.connect(self.ventilar)

        self.lcd_umidade.display(random.randint(1,101))
        self.lcd_temperatura.display(random.randint(1,40))

    def regar(self):
        print 'Estou regando'

    def ventilar(self):
        print 'Estou ventilando'

def main():
    app = QtGui.QApplication(sys.argv)
    form = controlador()
    form.show()
    app.exec_()

if __name__ == '__main__':
    main()
