class Complex:
    def __init__(self, real=0, image=0):
        self.real = real
        self.image = image
    @classmethod # 内置的类方法装饰器
    def add1(cls, c1, c2):
        print(cls)  # <class '__main__'.Complex>
        c = Complex()
        c.real = c1.real + c2.real
        c.image = c1.image + c2.image
        return c
    @staticmethod # 内置的静态方法装饰器
    def add2(c1, c2):
        c = Complex()
        c.real = c1.real + c2.real
        c.image = c1.image + c2.image
        return c       

if __name__=='__main__':
    c1 = Complex(1, 2.5)
    c2 = Complex(2.2, 3.1)
    c_class = Complex.add1(c1, c2) # 调用时类方法的第一个参数cls会隐式接收类本身，这里的cls也是约定俗成的名字
    c_static = Complex.add2(c1, c2)
    print('c1+c2的结果为%.2f + %.2fi'%(c_class.real, c_class.image))
    print('c1+c2的结果为%.2f + %.2fi'%(c_static.real, c_static.image))