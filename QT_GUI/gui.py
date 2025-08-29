import sys
import socket
from PyQt5.QtWidgets import QApplication, QWidget, QSlider, QVBoxLayout
from PyQt5.QtCore import Qt

class Slider(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):

        layout = QVBoxLayout()
        self.setLayout(layout)

        self.slider1 = QSlider(Qt.Orientation.Horizontal) 
        layout.addWidget(self.slider1)

        self.slider1.setRange(0, 100)
        self.slider1.valueChanged.connect(self.sendSliderInfo)

    def sendSliderInfo(self): 

        value1 = self.slider1.value() 
        message = f"LED{value1}"   

        tcpsockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
        serveraddr = ("127.0.0.1", 8080) 

        tcpsockfd.connect(serveraddr)
        tcpsockfd.send(message.encode())
        tcpsockfd.close()

def main():
    app = QApplication(sys.argv)
    window = Slider()
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()

