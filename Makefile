all: raspiiclock

raspiiclock:	main.o common.o screen.o clock_digits.o clock_digial.o backg_fire.o backg_matrix.o backg_obj3d.o backg_plasma.o backg_snow.o backg_starfield3d.o backg_starfield

# többi is

common.o:	inc/common.h
			gcc -c -o common.o inc/common.h

screen.o:	inc/screen.h
			gcc -c -o screen.o inc/screen.h

clock_digits.o:	inc/clock_digits.h
				gcc -c -o clock_digits.o inc/clock_digits.h

clock_digial.o:	inc/clock_digial.cpp
				gcc -c -o clock_digial.o inc/clock_digial.cpp


backg_fire.o: 	inc/backg_fire.cpp
				gcc -c -o backg_fire.o 	inc/backg_fire.cpp

backg_matrix.o: inc/backg_matrix.cpp
				gcc -c -o backg_matrix.o inc/backg_matrix.cpp

backg_obj3d.o:	inc/backg_obj3d.cpp
				gcc -c -o backg_obj3d.o	inc/backg_obj3d.cpp

backg_plasma.o: inc/backg_plasma.cpp
				gcc -c -o backg_plasma.o inc/backg_plasma.cpp

backg_snow.o: 	nc/backg_snow.cpp
				gcc -c -o backg_snow.o 	nc/backg_snow.cpp

backg_starfield3d.o: 	inc/backg_starfield3d.cpp
				gcc -c -o backg_starfield3d.o 	inc/backg_starfield3d.cpp

backg_starfield.o: 		inc/backg_starfield.cpp
				gcc -c -o backg_starfield.o 		inc/backg_starfield.cpp

main.o:		main.cpp
			gcc -c -o main.o main.cpp

clean:
	@rm -rf *.o
	@rm -rf server

