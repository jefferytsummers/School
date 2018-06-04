import sys

#Python script to output Lucas numbers as a sanity check.

orig_stdout = sys.stdout
f = open('trash.txt', 'w')
sys.stdout = f

r1    = 2
r2    = 1
r3    = 0
count = 100
one   = 1

acc = r1
print(2, '= ', format(acc, '08x'))
R   = acc
acc = r2
print(1, '= ', format(acc, '08x'))
r1  = acc
acc += R
print(3, '= ', format(acc, '08x'))
while(True):
    R = acc
    acc = r1
    acc += R
    print(acc, ' = ', format(acc, '08x'))
    r1 = acc
    acc = R
    r3 = acc
    acc = count
    R = acc
    acc = one
    acc = -acc
    acc += R
    if acc == 0:
        break
    count = acc
    acc = r3
    R = acc
    acc = r1
    acc += R
    print(acc, ' = ', format(acc, '08x'))
    r2 = acc
    acc = R
    r3 = acc
    acc = count
    R = acc
    acc = one
    acc = -acc
    acc += R
    if acc == 0:
        break
    count = acc
    acc = r2

sys.stdout = orig_stdout
f.close()
