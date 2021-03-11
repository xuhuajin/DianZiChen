import serial
import re
from PyQt5.Qt import QWidget
class UserCommunication(QWidget):

    @classmethod
    def Open_Serial(self,port,bps,timeout):
        """
        打开串口
        :return:
        """
        try:
            # 打开串口，并得到串口对象
            self.main_engine = serial.Serial(port,bps,timeout=timeout)
            # 判断是否打开成功
            if (self.main_engine.is_open):
                return True
            else:
                return False
        except:
            print("open-error\n")
            return False

    @classmethod
    def Close_Serial(self):
        """
        关闭串口
        :return:
        """
        try:
            self.main_engine.close()
            print("close_Serial")
        except:
            print("close-error\n")

    @classmethod
    def Read_Serial(self):
        """
        读取串口数据
        :return: 读取到的数据
        """
        try:
            data = self.main_engine.readline()
            return data
        except:
            print("Read_Error")

    @classmethod
    def Get_ZhongLiang(self):
        """
        获取称重重量信息
        :return:
        """
        try:
            Reciver_data = self.Read_Serial().decode("utf-8")
            self.zl = re.match("称重重量为：(.*?) g",Reciver_data,re.M | re.S)
            if self.zl:
                self.Val=int(self.zl.group(1))
                return self.Val
        except:
            print("GET_Error\n")

    @classmethod
    def Write_Data(self,data):
        self.main_engine.write(data.encode())
        # print(data.encode().decode("utf-8"))






if __name__ == '__main__':
    com = UserCommunication("COM3",115200,1)
    if(com.Open_Serial()):
        while True:
            # data = com.Read_Serial()
            # print(data.decode("utf-8"))
            com.Write_Data("12".encode())
            com.Get_ZhongLiang()
            print(com.Val)

