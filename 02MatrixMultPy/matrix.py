import time
import threading

s = 4
t = 0

#Matriz A
A = [1] * s
for i in range(s):
  A[i] = [1] * s
#print A

#Matriz B
B = [1] * s
for i in range(s):
  B[i] = [1] * s
#print B

#Matriz C
C = [0] * s
for i in range(s):
  C[i] = [0] * s
#print C

threads = []

#funcion a paralelizar

def matMult(mf, mc, size):
    temp = 0
    for j in range(size):
        temp += A[mf][j] * B[j][mc]
    C[mf][mc] = temp
    print C[mf][mc]

def main():
    for f in range(s):
        for c in range(s):
            tr = threading.Thread(target=matMult, args=(f,c,s,))
            threads.append(tr)
            tr.start()
            tr.join()

    print C


main()
