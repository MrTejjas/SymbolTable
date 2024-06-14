all : Symbol_Table.o driver.o
	gcc Symbol_Table.o driver.o -o final.exe

Symbol_Table.o : Symbol_Table.c
	gcc -c Symbol_Table.c

driver.o : driver.c
	gcc -c driver.c

clean : 
	del *.o *.exe