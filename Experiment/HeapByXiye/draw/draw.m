data=xlsread('C:\Users\81228\Desktop\HeapByXiye\draw\data2.xlsx');
[m,n]=size(data);
x=data(:,1);
y=data(:,2);
for i=1:m
    k(i)=log2(x(i));
end
plot(k,y,'-o');
title('N=1000时，t随log2k的变化曲线')
xlabel('log2k');
ylabel('t/s');