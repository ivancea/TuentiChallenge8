import sys
from fractions import gcd
from sympy.solvers.diophantine import diop_solve
from sympy import symbols

def err(str):
    print(str, file=sys.stderr)

def testValue(doorIntervals, doorOffsets, value):
    for i in range(0, len(doorIntervals)):
        if (value + i + doorOffsets[i])%doorIntervals[i] != 0:
            return False

    return True

def getNextInterval(intervalX, offsetX, intervalY, offsetY):
    x,y = symbols("x, y", integer=True)

    t = diop_solve(intervalX*x - intervalY*y - (offsetX - offsetY))
    
    s, = t[0].free_symbols
    k = t[0].subs({s: 0})

    k = k%intervalY

    n = intervalX*k - offsetX

    newInterval = intervalX * intervalY
    newOffset = newInterval - n

    return newInterval, newOffset

def solve(doorIntervals, doorOffsets):
    currentInterval = doorIntervals[0]
    currentOffset = doorOffsets[0]

    for i in range(1, len(doorIntervals)):
        if (currentOffset - doorOffsets[i] - i) % gcd(currentInterval, doorIntervals[i]) != 0:
            return "NEVER"
            
        currentInterval, currentOffset = getNextInterval(currentInterval, currentOffset, doorIntervals[i], doorOffsets[i] + i)
    
    return currentInterval - currentOffset

def isPossible(doorIntervals, doorOffsets):
    for i in range(0, len(doorIntervals)):
        for j in range(i+1, len(doorIntervals)):
            if (doorOffsets[i] + i - doorOffsets[j] - j) % gcd(doorIntervals[i], doorIntervals[j]) != 0:
                return False

    return True

def main():
    caseCount = int(input())

    for currentCase in range(1, caseCount + 1):
        doorCount = int(input())

        doorIntervals = []
        doorOffsets = []

        for currentDoor in range(0, doorCount):
            interval, offset = map(int, input().split())

            doorIntervals.append(interval)
            doorOffsets.append(offset)

            if currentCase == 8:
                err(str(interval) + " " + str(offset))
        
        originalIntervals = list(doorIntervals)
        originalOffsets = list(doorOffsets)

        for i in range(0, len(doorIntervals)):
            for j in range(i+1, len(doorIntervals)):
                g = gcd(doorIntervals[i], doorIntervals[j])
                doorIntervals[j] //= g

        if not isPossible(originalIntervals, originalOffsets):
            result = "NEVER"
        else:
            result = solve(doorIntervals, doorOffsets)

            if not testValue(doorIntervals, doorOffsets, result):
                err("INVALID VALUE")

        err("Case #" + str(currentCase) + ": " + str(result))
        print("Case #" + str(currentCase) + ": " + str(result))


main()