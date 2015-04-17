function CSI()
n=input('请输入点的数量:');
A=zeros(2,n);
for i=1:n
    A(1,i)=input('请输入x:\n');
    A(2,i)=input('请输入y:\n');
end
y1=input('请输入第一个点的一阶导值:');
y2=input('请输入最后一个点点的一阶导值:');
H=zeros(1,n-1);
U=zeros(1,n);
L=zeros(1,n);
F=zeros(1,n);
D=zeros(n,1);
M=zeros(n,1);
for i=1:n-1
    H(i)=A(1,i+1)-A(1,i);
    F(i)=(A(2,i+1)-A(2,i))/(A(1,i+1)-A(1,i));
end
for i=1:n
    if(i==1)
        D(i,1)=6*(F(i)-y1)/H(i);
    elseif(i==n)
        D(i,1)=6*(y2-F(i-1))/H(n-1);
    else
        D(i,1)=6*(F(i)-F(i-1))/(H(i-1)+H(i));
    end
end
L(1)=1;U(n)=1;
for i=2:n-1    
    L(i)=H(i)/(H(i-1)+H(i));
end
for i=2:n-1
    U(i)=H(i-1)/(H(i-1)+H(i));
end
B=2*eye(n);
for i=1:n-1
    B(i,i+1)=L(i);
    B(i+1,i)=U(i+1);
end
M=inv(B)*D;
s=0;
x=A(1,1):0.0001:A(1,n)-0.1;
for i=1:n-1
    s=s+(M(i).*(A(1,i+1)-x).^3/(6.*H(i))+M(i+1).*(x-A(1,i)).^3/(6.*H(i))+(A(2,i)-M(i).*H(i).^2/6)*((A(1,i+1)-x)./H(i))+(A(2,i+1)-M(i+1).*H(i).^2/6).*((x-A(1,i))./H(i))).*(x>=A(1,i)&x<A(1,i+1));
end
plot(x,s);

