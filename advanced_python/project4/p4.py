from time import time
from multiprocessing import Queue, Process
from sys import argv

def Compute(low, high, q):
    numOfPrimes = 0
    for num in range(low, high+1):
        if IsPrime(num):
            numOfPrimes += 1
    q.put(numOfPrimes)

def IsPrime(num):
    if num == 1 or num%2 == 0:
        return False
    for i in range(3,num//2,2):
        if num%i == 0:
            return False
    return True

def main():
    l_bound, u_bound = int(argv[1]), int(argv[2])
    numOfCores = int(argv[3])
    chunk = int((u_bound-l_bound)/numOfCores)

    q = Queue()
    processes = []
    for i in range(numOfCores):
        low  = l_bound if i == 0 else i*chunk + 1 + l_bound
        high = u_bound if i == numOfCores - 1 else (i + 1)*chunk + l_bound
        processes.append(Process(target = Compute, args = (low, high, q)))

    start = time()
    for process in processes:
        process.start()

    for process in processes:
        process.join()
    endTime = time() - start

    numOfPrimes = 0
    for process in processes:
        numOfPrimes += q.get()
    print('%d %12.4f' %(numOfPrimes, endTime))

main()
