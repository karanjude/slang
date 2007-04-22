/* 
   program to find whther a 
   number is palindrom or not 
*/
program
var num,i,j
begin
read(num)
write(num)   write("\n")
i = num
while i > 0
j = (j * 10 ) + i % 10
write(j)
i = i / 10
endwhile
write("\n")
write(num) write("\t") write(j)
if j = num
write("palindrome")
else
write("not palindrome")
endif
end.
	


 	

