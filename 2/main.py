def main():
    total = int(input())

    for i in range(1, total+1):
        base = len(input())

        max = 0
        min = base**(base-1)

        for n in range(1, base):
            max += n * base**n

        for n in range(2, base):
            min += n * base**(base-n-1)

        print("Case #" + str(i) + ": " + str(max - min))


main()

'''
Base 5

4*5^4 + 3*5^3 + 2*5^2 + 1*5

1*5^4 + 0*5^3 + 2*5^2 + 3*5 + 4
1*4^3 + 2*4^1 + 3*4^0
'''