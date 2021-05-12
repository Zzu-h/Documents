Answer
class FourCal:
    def __init__(self, first, second):
        self.first = first
        self.second = second
    def setdata(self, first, second):
        self.first = first
        self.second = second
    def add(self):
        result = 0
        try:
            result = self.first + self.second
            if(result > 128 or result < -127):
                raise OverflowError
        except OverflowError:
            print("값이 너무 크거나 작습니다")
            return 0
        else:
            return result

    def mul(self):
        result = 0
        try:
            result = self.first * self.second
            if(result > 128 or result < -127):
                raise OverflowError
        except OverflowError:
            print("값이 너무 크거나 작습니다")
            return 0            
        else:
            return result
    def div(self):
        result = 0
        try:
            result = self.first / self.second
            if(result > 128 or result < -127):
                raise OverflowError
        except OverflowError:
            print("값이 너무 크거나 작습니다")
        except ZeroDivisionError:
            print("0으로 나눌 수 없습니다")
        finally:
            return result


a = FourCal(126,4)
print(a.add())

b = FourCal(4,0)
print(b.div())

c = FourCal(4,2)
print(c.div())

'''
1. 아래의 메인문을 만족하는 'bank' 클래스를 생성하시오
    a. 'bank'는 회원 수와 총 현금보유량을 관리하여야 한다.
    b. 각 회원은 가입할때 입금을 할 수 있어야 한다.
    c. 각 회원은 입금과 출금을 할 수 있어야 한다.
    d. 출금을 할 때 잔액보다 많이 출금하려 하면 출금이 되지 않아야 한다.
    e. 'bank'는 자신의 회원수와 현금보유량을 확인하는 'printbank'메서드를 보유하여야 한다.

a님 가입을 환영합니다. 잔액은 500원입니다.
a님 500원 입금되었습니다. 잔액은 1000원입니다.
a님 잔액이 모자랍니다.

b님 가입을 환영합니다. 잔액은 1000원입니다.
b님 1500원 입금되었습니다. 잔액은 2500원입니다.
b님 500원 출금되었습니다. 잔액은 2000원 입니다.

c님 가입을 환영합니다. 잔액은 0원입니다.

-------------------------
Bank 유저수 : 3
Bank 현금보유량 : 3000
-------------------------
'''
class Bank():
    userCount = 0
    bankMoney = 0

    def __init__(self, name, s_money=0):
        self.name = name
        self.money = s_money
        Bank.userCount += 1
        Bank.bankMoney += s_money
        print('{}님 가입을 환영합니다. 잔액은 {}원입니다.'.format(self.name, self.money))

    def saving(self, s_money):
        self.money += s_money
        Bank.bankMoney += s_money
        print("{}님 {}원 입금되었습니다. 잔액은 {}원입니다.".format(self.name, s_money, self.money))
    def withdrawal(self, w_money):
        if self.money < w_money:
            print("{}님 잔액이 모자랍니다.".format(self.name))
        else:
            self.money -= w_money
            Bank.bankMoney -= w_money
            print("{}님 {}원 출금되었습니다. 잔액은 {}원입니다.".format(self.name, w_money, self.money))
    def printbank():
        print(
            '''
            -------------------------
            Bank 유저수 : {}
            Bank 현금보유량 : {}
            -------------------------
            '''.format(Bank.userCount, Bank.bankMoney)
            )

if __name__ == "__main__":
    a = Bank('a', 500)
    a.saving(500)
    a.withdrawal(1500)
    print()

    b = Bank('b', 1000)
    b.saving(1500)
    b.withdrawal(500)
    print()

    c = Bank('c')
    print()

    Bank.printbank()

