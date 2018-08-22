import time
import random
import numpy as np
import sys
import time
from multiprocessing import Process, Lock, Array

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

processes = []

#funcion a paralelizar

def matMult(mf, mc, size, C_arr, l):
    temp = 0
    for j in range(size):
        temp += A[mf][j] * B[j][mc]

    l.acquire()
    C_arr[(mf * size) + mc] = temp
    l.release()
    #print C[mf][mc]

#main nuevo
def main():
    file = open('datos.txt','w')

    lock = Lock()

    #Matriz A
    global A
    #A.resize((p,p))
    A = np.random.rand(s,s)
    #print A

    #Matriz B
    global B
    #B.resize((p,p))
    B = np.random.rand(s,s)
    #print B

    C_array = Array('d', range(s*s))

    #timestamp inicial
    ts_i = time.time()

    for f in range(s):
        for c in range(s):
            #tr = threading.Thread(target=matMult, args=(f,c,p,))
            pr = Process(target=matMult, args=(f,c,s,C_array,Lock()))
            processes.append(pr)
            pr.start()

    for pr in processes:
        pr.join()

    #timestamp final
    ts_f = time.time()
    #print C_array[:]

    ts = str("%f" % (ts_f - ts_i))
    print "Size:",s,"; Time:", ts
    file.write(ts + '\n')

    file.close()

main()
