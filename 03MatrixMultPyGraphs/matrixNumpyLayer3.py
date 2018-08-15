import time
import threading
import random
import numpy as np
import sys
import time

#Numero de pruebas
pruebas = int(sys.argv[1])

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

def matMult(mf, mc, size):
    temp = 0
    for j in range(size):
        temp += A[mf][j] * B[j][mc]
    C[mf][mc] = temp
    #print C[mf][mc]

#main nuevo
def main():
    file = open('datos.txt','w')

    for p in xrange(100, pruebas + 1, 100):

        #Matriz A
        global A
        A.resize((p,p))
        A = np.random.rand(p,p)
        #print A

        #Matriz B
        global B
        B.resize((p,p))
        B = np.random.rand(p,p)
        #print B

        #Matriz C
        global C
        C.resize((p,p))
        C = np.zeros((p,p))
        #print C

        #timestamp inicial
        ts_i = time.time()

        for f in range(p):
            for c in range(p):
                tr = threading.Thread(target=matMult, args=(f,c,p,))
                threads.append(tr)
                tr.start()

        for tr in threads:
            tr.join()

        #timestamp final
        ts_f = time.time()
        #print C

        ts = str("%f" % (ts_f - ts_i))
        print "Size:",p,"; Time:", ts
        file.write(ts + '\n')

    file.close()

main()
