import math
import sys
import time

def truncateFloat(value):
    return "%.2f" % value

# Linearly searching downwards from number/2
def findLargestDivisorLinear(number):
    
    print("Doing linear search downwards")

    startTime = time.time()

    i = math.ceil(number/2)
    numbersDone = 0
    while (i > 2):
        if (number % i == 0):
            elapsedTime = time.time() - startTime
            print("Elapsed time: " + str(truncateFloat(elapsedTime)) + " seconds")
            return i
        i -= 1
        numbersDone += 1
        currentTime = time.time()
        passedTime = currentTime-startTime
        percentageDone = numbersDone / (number/2)*100
        averageTime = passedTime/numbersDone
        expectedTime = averageTime*i
        if (i % 1000000 == 0):
            print(str(truncateFloat(percentageDone)) + "%. All possible values checked in: " + str(truncateFloat(expectedTime)) + " seconds")
    return 1

if __name__ == "__main__":

    if (len(sys.argv) > 2):
        print("You can submit only one number to be checked. You gave " + str(len(sys.argv)-1))
        sys.exit(1)
    try:
        test = int(sys.argv[1])
    except ValueError:
        print("Must give a valid number to be checked. You have " + sys.argv[1])
        sys.exit(1)
    largest = findLargestDivisorLinear(int(sys.argv[1]))
    print("Largest was: " + str(largest))
