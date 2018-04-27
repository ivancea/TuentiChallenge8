import sys
import itertools

def err(str):
    print(str, file=sys.stderr)

def testValue(doorIntervals, doorOffsets, value):
    for i in range(0, len(doorIntervals)):
        if (value + i + doorOffsets[i])%doorIntervals[i] != 0:
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
        
        result = "NEVER"

        for i in itertools.count():
            if testValue(doorIntervals, doorOffsets, i):
                result = i
                break


        err("Case #" + str(currentCase) + ": " + str(result))
        print("Case #" + str(currentCase) + ": " + str(result))


main()