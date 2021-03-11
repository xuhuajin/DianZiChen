from PyQt5Ui.main_win import Ui_Form
from PyQt5.Qt import QWidget,pyqtSignal,QThread,QStandardItemModel,QHeaderView,QAbstractItemView,QStandardItem,QApplication,Qt
from communication.serial_communication import UserCommunication

class MyQWidget(QWidget):
    win_close = pyqtSignal(bool) #窗口关闭信号
    def __init__(self,*args,**kwargs):
        super(MyQWidget, self).__init__(*args,**kwargs)

    def closeEvent(self,e):
        '''
        重写窗口关闭事件
        :param e:
        :return:
        '''
        self.win_close.emit(True) #发送窗口关闭信号

class Mythread(QThread):
    ZL_Data = pyqtSignal(int)  #自定义信号 注意pyqtSignal一定要实例到__init__前面
    def __init__(self):
        super(Mythread, self).__init__()
        self.threadstartflag = True #线程开始
        self.timecount = 0

    def run(self):
        """
        线程运行
        :return:
        """
        if self.threadstartflag:
            while self.threadstartflag:
                data = UserCommunication.Get_ZhongLiang()
                if data!=None:
                    self.ZL_Data.emit(data)

    def close(self):
        """
        关闭线程，关闭串口
        :return:
        """
        self.threadstartflag=False
        UserCommunication.Close_Serial()


class Main_Win(MyQWidget,Ui_Form):
    def __init__(self,*args,**kwargs):
        super(Main_Win, self).__init__(*args,**kwargs)
        self.num = 1 #表格编号
        self.HeJiMoney = 0 #合计金额
        self.data=[]
        self.setupUi(self)
        self.startTimer(100,Qt.PreciseTimer)
        self.win_close.connect(self.close_win)
        self.set_tableView()

    def threadstartslot(self):
        """
        开始线程
        :return:
        """
        self.work = Mythread()
        self.work.ZL_Data.connect(self.Set_ZLLcd)
        self.work.start()  # 开启线程

    def Set_ZLLcd(self, int):
        """
        自定义信号ZL_Data的槽函数，用于显示称重重量
        :param int: 称重重量值
        :return: None
        """
        self.Zhongliang.display(int)


    def timerEvent(self, a0: 'QTimerEvent') -> None:
        """
        定时器事件，用于刷新界面，显示金额信息
        :param a0:
        :return:
        """
        self.je = self.doubleSpinBox_2.value() *self.Zhongliang.value()
        self.JinE.display(round(self.je,1))


    def close_win(self,bool):
        """
        窗口关闭槽函数
        :param bool:
        :return:
        """
        self.work.close()

    def set_tableView(self):
        """
        设置表格格式
        :return:
        """
        # 设置数据层次结构，4行4列
        self.model = QStandardItemModel(0, 4)
        # 设置水平方向四个头标签文本内容
        self.model.setHorizontalHeaderLabels(['编号', '重量(g)', '单价(元/g)', '金额(元)'])
        self.tableView.setModel(self.model)
        # 水平方向标签拓展剩下的窗口部分，填满表格
        self.tableView.horizontalHeader().setStretchLastSection(True)
        self.tableView.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)# 水平方向，表格大小拓展到适当的尺寸
        # self.tableView.setRowHeight(0,60) #设置行高
        self.tableView.setShowGrid(False) #不显示网格
        # self.tableView.setEnabled(False)
        self.tableView.setSelectionBehavior(QAbstractItemView.SelectRows) #设置点击选择一整行
        self.tableView.verticalHeader().hide() #隐藏行头
        self.tableView.setEditTriggers(QAbstractItemView.NoEditTriggers) #单元格不可编辑

    def OKBtn_click(self):
        val =[]
        self.model.removeRow(self.num-1)
        self.HeJiMoney = self.HeJiMoney+self.je
        val.append(QStandardItem("%d"%self.num))
        val.append(QStandardItem("%d"%self.Zhongliang.value()))
        val.append(QStandardItem("%.2f"%self.doubleSpinBox_2.value()))
        val.append(QStandardItem("%.1f"%self.je))
        self.data.append(val)
        self.model.appendRow(val)
        self.model.item(self.num-1, 0).setTextAlignment(Qt.AlignCenter)
        self.model.item(self.num-1, 1).setTextAlignment(Qt.AlignCenter)
        self.model.item(self.num-1, 2).setTextAlignment(Qt.AlignCenter)
        self.model.item(self.num-1, 3).setTextAlignment(Qt.AlignCenter)
        self.model.setItem(self.num,3,QStandardItem("合计:%.1f"%self.HeJiMoney))
        self.model.item(self.num,3).setTextAlignment(Qt.AlignCenter)
        self.tableView.scrollToBottom() #滚动到最底部
        self.num += 1

    def JieZhangBtn_click(self):
        for r in range(self.num-1):
            self.model.removeRow(0)
        self.HeJiMoney=0
        self.data.clear()
        self.num = 1;

    def XiuGaiBtn_click(self):
        if len(self.data)!=0: #判断是否还有数据
            self.HeJiMoney -= float(self.data[-1][3].text())
            self.data.pop()
            if self.HeJiMoney < 0:
                self.HeJiMoney = 0
            self.model.removeRow(self.num-2) #删除最后一次数据
            self.model.removeRow(self.num-1) #删除合计金额行
            self.model.setItem(self.num-2, 3, QStandardItem("合计:%.1f" % self.HeJiMoney))
            self.model.item(self.num-2, 3).setTextAlignment(Qt.AlignCenter)
            self.num -=1
            if self.num<1:
                self.num=1


    def QuPiBtn_click(self):
        UserCommunication.Write_Data("QP1")



if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    Form = Main_Win()
    Form.show()
    sys.exit(app.exec_())
