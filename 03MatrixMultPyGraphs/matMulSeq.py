import time
import threading
import random
import numpy as np
import sys
import time

#Numero de pruebas
s = int(sys.argv[1])

threads = []

def main():
    file = open('datos.txt','w')

    #Matriz A
    A = np.random.rand(s,s)
    #print A

    #Matriz B
    B = np.random.rand(s,s)
    #print B

    #Matriz C
    C = np.zeros((s,s))
    #print C

    #timestamp inicial
    ts_i = time.time()
    for f in range(s):
        for c in range(s):
            temp = 0
            for j in range(s):
                temp += A[f][j] * B[j][c]
            C[f][c] = temp
    #timestamp final
    ts_f = time.time()
    #print C
    #print ts_f - ts_i
    ts = str("%f" % (ts_f - ts_i))
    print "Size:",s,"; Time:", ts
    file.write(ts + '\n')

    file.close()

main()
