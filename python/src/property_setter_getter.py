'''
    通过@property装饰器使得学生成绩的取值范围限定在0~100之间，通过该装饰器将方法转为属性，这样的话就可以像属性一样调用了。
    直接使用@property就可以定义一个用于获取属性值的方法(即getter)，如果要定义一个设置属性值的方法(setter)，则需要使用
名字格式为"@属性名.setter"的装饰器。
    如果一个属性只有用于获取属性值的getter方法，而没有用于设置属性值的setter方法，则该属性是一个只读属性，只允许读取该属性
的值，而不能设置该属性的值。例如下面的age就是一个只读属性。
    对于有getter/setter方法的属性，只要对该属性赋值，就会执行setter方法，只要读取该属性的值就会执行getter方法。例如下面
的代码中当给stu.score赋值时，都会自动执行18~23行代码，当读取stu.age时，会自动执行24-26行代码，当读取stu.score时自动执行15-17行代码
    在类的setter和getter方法中使用self访问属性时，需要在属性名前加上下划线，否则系统会因不断递归调用而报错。例如下面代码中第17行
和23行访问score属性时，都是用self_score(score前有一个下划线)。
'''
import datetime

class Student:
    @property 
    def score(self): #定义一个用于获取score属性的方法
        return self._score
    @score.setter
    def score(self, score): #用score.setter定义一个用于设置score属性的方法
        if score<0 or score>100:
            print('成绩必须在0~100之间')
        else:
            self._score=score
    @property
    def age(self): #定义一个用于获取age属性的方法
        return datetime.datetime.now().year-self.birthyear
    
if __name__=='__main__':
    stu=Student()
    stu.score=80    #调用上述使用装饰器score.setter定义的方法
    stu.birthyear=2000
    print('年龄 %d, 成绩 %d'%(stu.age, stu.score))  #像属性一样使用
    #stu.age=19 #取消前面注释会报错，因为其为只读的
    stu.score=105
    print('年龄 %d, 成绩 %d'%(stu.age, stu.score))