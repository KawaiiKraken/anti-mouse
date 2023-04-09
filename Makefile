compile:
	gcc -o intercept -l xdo -Wall intercept.c
	gcc -o movemouse -l xdo -Wall movemouse.c

clean:
	rm /bin/intercept
	rm /bin/movemouse

install:
	gcc -o movemouse -l xdo -Wall movemouse.c
	mv movemouse /bin/movemouse
	sudo chmod 755 /bin/movemouse
	#
	gcc -o intercept -l xdo -Wall intercept.c
	mv intercept /bin/intercept 
	sudo chmod 755 /bin/intercept
