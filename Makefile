main.o: Main.cpp
	g++ Main.cpp Candidato.cpp Partido.cpp Partido.h Candidato.h

clean:
	rm *.o