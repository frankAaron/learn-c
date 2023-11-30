def eight_or_four(num):
    l = list(str(num))
    count8 = 0
    count4 = 0
    for i in range (11):
        if int(l[i]) == 8:
            count8 += 1
        if int(l[i]) == 4:
            count4 += 1
    if count8 > 0 and count4 > 0:
        return 0
    else:
        return 1

def con(num):
    l = list(str(num))
    for i in range (9):
        if l[i] == l[i+1] and l[i+1] == l[i+2]:
            return 1
    return 0

m,n=map(int,input().split())
count = 0
for i in range(m,n+1):
    if eight_or_four(i) and con(i):
        count += 1
print(count)        