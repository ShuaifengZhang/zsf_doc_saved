'''
__slots__中所做的动态扩展属性限制只对__slots__所在类的实例对象有效。
'''
class Person:
    __slots__ = ('name') #定义允许动态扩展的属性
'''如果子类中有__slots__的定义，则子类的实例对象可动态扩展的属性包括子类中通过__slots__定义的属性和其父类中通过__slots__定义的属性。'''
class Student(Person): 
    __slots__=('sno')
'''如果子类中没有__slots__定义，则子类的实例对象可以进行任意属性的动态扩展'''
class Postgraduate(Student): 
    pass

if __name__=='__main__'
    stu=Student()   
    stu.sno='12345' #为stu对象动态扩展属性sno
    stu.name='xiaoming' #为stu对象动态扩展属性name
    #stu.tutor='xiaohong' #取消前面的注释符会报错
    pg=Postgraduate()   
    pg.sno='45678'  #为pg对象动态扩展属性sno
    pg.name='xiaoqing'  #为pg对象动态扩展属性name
    pg.tutor='xiaohong' #为pg对象动态扩展属性tutor