import sys
import math
from multiprocessing import Process, connection, Event


def print_factors(event, large_number):
    large_number = int(large_number)
    if large_number % 2 == 0:
        print("{:d}={:d}*{:d}".format(large_number, int(large_number/2), 2))
        event.set()
    maxFactor = int(math.sqrt(large_number))
    maxFactor = maxFactor if maxFactor % 2 != 0 else maxFactor+1
    for i in range(3, maxFactor, 2):
        if event.is_set():
            break
        if large_number % i == 0:
            print("{:d}={:d}*{:d}".format(large_number, int(large_number/i), i))
            event.set()


def print_factors_reverse(event, large_number):
    large_number = int(large_number)
    if large_number % 2 == 0:
        print("{:d}={:d}*{:d}".format(large_number, int(large_number/2), 2))
        event.set()
    maxFactor = int(math.sqrt(large_number))
    maxFactor = maxFactor if maxFactor % 2 != 0 else maxFactor+1
    for i in range(maxFactor, 3, -2):
        if event.is_set():
            break
        if large_number % i == 0:
            print("{:d}={:d}*{:d}".format(large_number, int(large_number/i), i))
            event.set()


def callback(task, otherTask):
    print(task.result())
    otherTask.cancel()


def main(large_number):
    event = Event()
    # Create two processes for each function
    process1 = Process(target=print_factors, args=(event, large_number,))
    process2 = Process(target=print_factors_reverse,
                       args=(event, large_number,))
    # Start both processes
    process1.start()
    process2.start()

    # event.wait()

    process1.join()
    process2.join()


if __name__ == "__main__":
    with open(sys.argv[1], 'r') as f:
        for line in f:
            main(line.strip())
