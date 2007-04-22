program
begin
var flag=1,i,num
write("enter number : ")
read(num)
for i = 2 to num / 2 
if(  num % i = 0)
flag = 0
endif
endfor
if( flag = 1)
write("number prime")
else
write("number not prime")
endif
end.
