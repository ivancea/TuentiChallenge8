import sys
from itertools import count
from fractions import gcd

def err(str):
    print(str, file=sys.stderr)

def testValue(doorIntervals, doorOffsets, value):
    for i in range(0, len(doorIntervals)):
        if (value + i + doorOffsets[i])%doorIntervals[i] != 0:
            return False

    return True

def solve(doorIntervals, doorOffsets):
    currentInterval = doorIntervals[0]
    currentOffset = doorOffsets[0]

    for i in range(1, len(doorIntervals)):
        if (currentOffset - doorOffsets[i] - i) % gcd(currentInterval, doorIntervals[i]) != 0:
            return "NEVER"
            
        # current = solve(current, [i])


    return currentInterval - currentOffset

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
        
        result = solve(doorIntervals, doorOffsets)

        if result != "NEVER":
            if not testValue(doorIntervals, doorOffsets):
                err("INVALID VALUE")

        err("Case #" + str(currentCase) + ": " + str(result))
        print("Case #" + str(currentCase) + ": " + str(result))


main()