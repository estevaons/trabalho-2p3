main.o: Main.cpp
	g++ Main.cpp Candidato.cpp Partido.cpp Partido.h Candidato.h
	./a.out

clean:
	rm *.o