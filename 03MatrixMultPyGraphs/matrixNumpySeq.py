import time
import threading
import random
import numpy as np
import sys
import time

#Numero de pruebas
pruebas = int(sys.argv[1])

threads = []

def main():
    file = open('datos.txt','w')

    for p in xrange(100, pruebas + 1, 100):

        #Matriz A
        A = np.random.rand(p,p)
        #print A

        #Matriz B
        B = np.random.rand(p,p)
        #print B

        #Matriz C
        C = np.zeros((p,p))
        #print C

        #timestamp inicial
        ts_i = time.time()
        for f in range(p):
            for c in range(p):
                temp = 0
                for j in range(p):
                    temp += A[f][j] * B[j][c]
                C[f][c] = temp
        #timestamp final
        ts_f = time.time()
        #print C
        #print ts_f - ts_i
        ts = str("%f" % (ts_f - ts_i))
        print "Size:",p,"; Time:", ts
        file.write(ts + '\n')

    file.close()

main()
