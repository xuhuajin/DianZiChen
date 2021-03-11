from PyQt5.Qt import QApplication,QIcon
from main_win_pan import Main_Win
from login_win_pan import Login_Win
import sys


if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setWindowIcon(QIcon("C:/Users/Xuhuajin/Desktop/CHSY/resource/dzc.ico"))
    Form = Login_Win()
    Form.setWindowTitle("连接电子秤")
    with open("C:/Users/Xuhuajin/Desktop/CHSY/resource/darkly.qss","r") as f:
        qss=f.read()
        app.setStyleSheet(qss)
    # qss = qdarkgraystyle.load_stylesheet()
    # print(qss)
    # app.setStyleSheet(qss)
    Form.show()
    maininfac_window = Main_Win()
    def Window_Jump():
        """
        界面跳转
        :return:
        """
        Form.hide()
        maininfac_window.show()
        maininfac_window.threadstartslot()
    Form.window_jump_signal.connect(Window_Jump)
    sys.exit(app.exec_())

