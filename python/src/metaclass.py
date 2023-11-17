'''
    因为type是用于创建Student类的类，所以type是一个metaclass。如果将下述代码清单改为第一行改为" class Student(metaclass=type):"，
则程序运行后会得到同样的结果，其中metaclass是关键字参数，默认值为type

'''
class Student:
    pass
stu=Student()
print('stu所属的类是 ', stu.__class__)  #使用__class__属性获取所属的类, 结果为<class '__main__.Student'>
print('Student所属的类是 ', Student.__class__) #结果为 <class 'type'>


'''
    如果在metaclass中定义__call__方法，则可以改变类的实例化过程。单例模式(指的是在程序运行时确保某个类最多只有一个实例对象)有多种
实现方法，这里介绍一种通过重写元类的__init__和__call__实现单例模式的方法，具体实现如下所示：
    下面的wb2和wb1实际上是同一个对象(即实现了单例模式)
'''
class MyMetaclass(type): #以type作为父类创建子类MyMetaclass
    def __new__(cls, *args, **kwargs):
        print('MyMetaclass __new__')
        return super().__new__(cls, *args, **kwargs)    #调用父类(即type)的__new__方法创建cls类对象并返回
    def __init__(self, *args, **kwargs):
        print('MyMetaclass __init__')
        self._instance=None
        return super().__init__(*args, **kwargs) #调用父类(即type)的__init__方法
    def __call__(self, *args, **kwargs):
        print('MyMetaclass __call__')
        if self._instance is None:
            self._instance = super().__call__(*args, **kwargs)
        return self._instance

class WebData(metaclass=MyMetaclass): #以MyMetaclass作为元类定义WebData, 此时会自动执行MyMetaclass中的__new__方法
    def __new__(cls, *args, **kwargs):
        print('WebData __new__')
        return super().__new__(cls)
    def __init__(self):
        print('WebData __init__')
    def __call__(self, timeout):
        print('WebData __call__')
        self.timeout=timeout

if __name__=='__main__':
    wb1=WebData()
    wb2=WebData()
    wb1(60) #等价于wb1.__call__(60)
    print(wb1.timeout)
    wb1.timeout=30
    print(wb1.timeout)
    wb2.timeout=15
    print(wb1.timeout, wb2.timeout)
