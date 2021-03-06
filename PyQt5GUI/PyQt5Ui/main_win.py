# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main_win.ui'
#
# Created by: PyQt5 UI code generator 5.15.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.setEnabled(True)
        Form.resize(974, 600)
        Form.setMaximumSize(QtCore.QSize(974, 600))
        Form.setWindowOpacity(3.0)
        Form.setToolTipDuration(-1)
        self.widget = QtWidgets.QWidget(Form)
        self.widget.setEnabled(True)
        self.widget.setGeometry(QtCore.QRect(0, 0, 981, 301))
        self.widget.setObjectName("widget")
        self.label_2 = QtWidgets.QLabel(self.widget)
        self.label_2.setGeometry(QtCore.QRect(460, 40, 171, 71))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(20)
        self.label_2.setFont(font)
        self.label_2.setStyleSheet("label_2{\n"
"    background-color:rgb(255, 255, 127)\n"
"}")
        self.label_2.setObjectName("label_2")
        self.QuPi = QtWidgets.QPushButton(self.widget)
        self.QuPi.setGeometry(QtCore.QRect(670, 170, 93, 41))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(17)
        self.QuPi.setFont(font)
        self.QuPi.setStyleSheet("QPushButton:checked{\n"
"    background-color:rgb(255, 15, 127)\n"
"}")
        self.QuPi.setObjectName("QuPi")
        self.JieZhang = QtWidgets.QPushButton(self.widget)
        self.JieZhang.setGeometry(QtCore.QRect(830, 230, 93, 41))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(17)
        self.JieZhang.setFont(font)
        self.JieZhang.setObjectName("JieZhang")
        self.label = QtWidgets.QLabel(self.widget)
        self.label.setGeometry(QtCore.QRect(10, 40, 131, 71))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(20)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.JinE = QtWidgets.QLCDNumber(self.widget)
        self.JinE.setGeometry(QtCore.QRect(160, 170, 461, 101))
        self.JinE.setAutoFillBackground(False)
        self.JinE.setStyleSheet("")
        self.JinE.setFrameShape(QtWidgets.QFrame.Box)
        self.JinE.setFrameShadow(QtWidgets.QFrame.Plain)
        self.JinE.setLineWidth(5)
        self.JinE.setDigitCount(10)
        self.JinE.setMode(QtWidgets.QLCDNumber.Dec)
        self.JinE.setSegmentStyle(QtWidgets.QLCDNumber.Flat)
        self.JinE.setObjectName("JinE")
        self.label_3 = QtWidgets.QLabel(self.widget)
        self.label_3.setGeometry(QtCore.QRect(10, 180, 151, 71))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(21)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.XiuGai = QtWidgets.QPushButton(self.widget)
        self.XiuGai.setGeometry(QtCore.QRect(670, 230, 93, 41))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(17)
        self.XiuGai.setFont(font)
        self.XiuGai.setObjectName("XiuGai")
        self.ok = QtWidgets.QPushButton(self.widget)
        self.ok.setGeometry(QtCore.QRect(830, 170, 93, 41))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(17)
        self.ok.setFont(font)
        self.ok.setObjectName("ok")
        self.Zhongliang = QtWidgets.QLCDNumber(self.widget)
        self.Zhongliang.setGeometry(QtCore.QRect(160, 30, 271, 101))
        font = QtGui.QFont()
        font.setFamily("Adobe Devanagari")
        self.Zhongliang.setFont(font)
        self.Zhongliang.setLayoutDirection(QtCore.Qt.RightToLeft)
        self.Zhongliang.setAutoFillBackground(False)
        self.Zhongliang.setFrameShape(QtWidgets.QFrame.Panel)
        self.Zhongliang.setFrameShadow(QtWidgets.QFrame.Plain)
        self.Zhongliang.setLineWidth(5)
        self.Zhongliang.setSegmentStyle(QtWidgets.QLCDNumber.Flat)
        self.Zhongliang.setProperty("value", 0.0)
        self.Zhongliang.setObjectName("Zhongliang")
        self.doubleSpinBox_2 = QtWidgets.QDoubleSpinBox(self.widget)
        self.doubleSpinBox_2.setGeometry(QtCore.QRect(640, 30, 331, 91))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(34)
        font.setBold(True)
        font.setWeight(75)
        self.doubleSpinBox_2.setFont(font)
        self.doubleSpinBox_2.setObjectName("doubleSpinBox_2")
        self.tableView = QtWidgets.QTableView(Form)
        self.tableView.setGeometry(QtCore.QRect(-5, 301, 981, 301))
        self.tableView.setAlternatingRowColors(False)
        self.tableView.setShowGrid(True)
        self.tableView.setSortingEnabled(False)
        self.tableView.setObjectName("tableView")

        self.retranslateUi(Form)
        self.ok.clicked.connect(Form.OKBtn_click)
        self.JieZhang.clicked.connect(Form.JieZhangBtn_click)
        self.QuPi.clicked.connect(Form.QuPiBtn_click)
        self.XiuGai.clicked.connect(Form.XiuGaiBtn_click)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "电子秤"))
        self.label_2.setText(_translate("Form", "单价(元/g)："))
        self.QuPi.setText(_translate("Form", "去皮"))
        self.JieZhang.setText(_translate("Form", "结账"))
        self.label.setText(_translate("Form", "重量(g)："))
        self.label_3.setText(_translate("Form", "金额(元)："))
        self.XiuGai.setText(_translate("Form", "修改"))
        self.ok.setText(_translate("Form", "确认"))
        self.doubleSpinBox_2.setSuffix(_translate("Form", "元"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())
