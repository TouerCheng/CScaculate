fuwiqi:
	gcc -o fuwuqi func.c fuwuqi.c -lpthread -g
	gcc -o kehuduan func.c kehuduan.c -lpthread -g
kehuduan:func.o kehuduan.o
	gcc -o kehuduan func.c kehuduan.c -lpthread
	make clean
.PHONY:clean
clean:
	rm -f *.o
