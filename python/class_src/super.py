class Person:
    def __init__(self, name):
        print('Peron constructor! ')
        self.name=name
class Student(Person):
    def __init__(self, sno, name):
        print('Student constructor! ')
        super().__init__(name)  #调用父类的构造方法,super(Student, self).__init(name)
        self.sno=sno
class Postgraduate(Student):
    def __init__(self, sno, name, tutor):   #其中的self对应新创建的对象
        print('Postgraduate constructor! ')
        '''
        相当于super(Postgraduate, self).__init(sno, name) 通过super()返回Postgraduate的父类Student类的的代理对象,
        该代理对象中的self就是新创建的Postgraduate类对象中的self。因此, 通过super().__init__(sno, name) 执行Student类
        的构造方法时,第9行的self.sno=sno实际上就是为新创建的Postgraduate类对象中的sno属性赋为形参sno的值。
        
        在执行到第8行时，通过super返回Student的父类Person类的代理对象，该代理对象中的self就是Student对象中的self，也就是
        新创建的Postgraduate类对象中的self。因此通过super().__init__(name)执行Person类的构造方法时，第4行的self.name=name
        实际上就是为新创建的Postgraduate类对象的name属性赋为形参name的值。
        '''
        super().__init__(sno, name) 
        self.tutor=tutor

if __name__=='__main__':
    pg=Postgraduate('18100', 'xiaoming', 'xiaozhang')
    print('学号: %s, 姓名: %s, 导师: %s'%(pg.sno, pg.name, pg.tutor))
