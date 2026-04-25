from turtle import *


left(90)

k = 15
tracer(0)

for i in range(4):
    forward(10 * k)
    right(90)

up()

for x in range(-100, 100):
    for y in range(-100, 100):
        dot(3)
        goto(x * k,y * k) #Поле от -100 до 100  с коеф (точки расставляем)

update()



done()