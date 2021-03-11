from PyQt5Ui.login_win import Ui_Form
from PyQt5.Qt import QWidget,pyqtSignal,Qt
from serial.tools import list_ports
from communication.serial_communication import UserCommunication


class Login_Win(QWidget,Ui_Form):
    window_jump_signal = pyqtSignal()
    def __init__(self,*args,**kwargs):
        super(Login_Win, self).__init__(*args,**kwargs)
        self.setupUi(self)
        self.time = self.startTimer(100, Qt.PreciseTimer)

    def timerEvent(self, a0: 'QTimerEvent') -> None:
        """
        实时获取串口列表
        :param a0:
        :return:
        """
        self.comboBox.clear()
        self.port_list = list(list_ports.comports())
        if len(self.port_list)!=0:
            for i,com in enumerate(self.port_list):
                self.comboBox.insertItem(i,com[0])

    def LianJIe_Serial(self):
        """
        连接串口
        :return:
        """
        port = self.comboBox.itemText(0)
        reda=UserCommunication.Open_Serial(port,115200,1)
        if reda:
            self.window_jump_signal.emit()
        else:
            self.label_2.setText("串口[%s]打开失败!"%port)


if __name__ == "__main__":
    import sys
    import qdarkgraystyle
    app = QApplication(sys.argv)
    Form =Login_Win()
    with open("darkly.qss","r") as f:
        qss=f.read()
        app.setStyleSheet(qss)
    Form.show()
    sys.exit(app.exec_())