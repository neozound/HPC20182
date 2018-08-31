import time
import threading
import random
import numpy as np
import sys
import time

#Tamano de la matriz
s = int(sys.argv[1])

#Matrices como variables globales

#Matriz A
A = np.zeros((1,1))
#print A

#Matriz B
B = np.zeros((1,1))
#print B

#Matriz C
C = np.zeros((1,1))
#print C

threads = []

#funcion a paralelizar

def matMult(mf, size, lock):
    for mc in range(size):
        temp = 0
        for j in range(size):
            temp += A[mf][j] * B[j][mc]
        lock.acquire()
        C[mf][mc] = temp
        lock.release()

def main():
    file = open('datos.txt','w')

    l = threading.Lock()

    #Matriz A
    global A
    A = np.random.rand(s,s)
    #print A

    #Matriz B
    global B
    B = np.random.rand(s,s)
    #print B

    #Matriz C
    global C
    C = np.zeros((s,s))
    #print C

    #timestamp inicial
    ts_i = time.time()

    for f in range(s):
        #Aqui debe ir el hilo
        tr = threading.Thread(target=matMult, args=(f,s,l,))
        threads.append(tr)
        tr.start()

    for tr in threads:
        tr.join()

    #timestamp final
    ts_f = time.time()
    #print C

    ts = str("%f" % (ts_f - ts_i))
    print "Size:",s,"; Time:", ts
    file.write(ts + '\n')

    file.close()

main()
