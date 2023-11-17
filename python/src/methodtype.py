from types import MethodType

class Student:
    pass
def SetName(self, name):
    self.name = name
def SetSno(self, sno)
    self.sno = sno

if __name__=='__main__':
    stu1 = Student()
    stu2 = Student()
    '''
        在为对象绑定方法时，需要使用types模块中的MethodType方法，其第一个参数是要绑定的函数名，第二个
    参数是绑定的对象名。
        当为一个对象绑定方法后，只能通过该对象调用该方法，其他未绑定该方法的对象不能调用。
        当为一个类绑定方法后，则该类中的所有实例对象都有该方法。
    '''
    stu1.SetName=MethodType(SetName, stu1)  #为stu1对象绑定SetName方法
    Student.SetSno=SetSno   #为Student类绑定SetSno方法
    stu1.SetName("xiaoming")
    stu1.SetSno("1234")
    stu2.SetSno("4567")
