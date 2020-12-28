import random
numlist=list()
while len(numlist)<40:
    num=random.randint(1,999)
    numlist.append(num)

count=1
f=open('./data.txt','w+')
for num in numlist:
    n=str(num)
    if count==10:
        f.write(n+'\n')
        count=1
    else:
        f.write(n+' ')
        count+=1
f.close()