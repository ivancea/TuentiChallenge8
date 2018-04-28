from sympy.solvers.diophantine import diop_solve
from sympy import symbols

def getNextInterval(intervalX, offsetX, indexX, intervalY, offsetY, indexY):
    x,y = symbols("x, y", integer=True)
    t = diop_solve(intervalX*x - intervalY*y - (offsetX + indexX - offsetY - indexY))
    
    s, = t[0].free_symbols
    k = t[0].subs({s: 0})

    k = k%intervalY

    n = intervalX*k - offsetX

    newInterval = intervalX * intervalY
    newOffset = newInterval - n

    return newInterval, newOffset

def main():
    intervalX = 7
    offsetX = 2
    indexX = 0

    intervalY = 9
    offsetY = 3
    indexY = 1

    print(getNextInterval(intervalX, offsetX, indexX, intervalY, offsetY, indexY))


main()


'''

7*-8 = -56
9*-6 = -54

-56-2 = -58
-54-4 = -58

n = -58











'''