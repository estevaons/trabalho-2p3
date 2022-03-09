main.o: Main.cpp
	g++ Main.cpp Candidato.cpp Partido.cpp Relatorios.cpp Partido.h Candidato.h Relatorios.h
	./a.out

clean:
	rm *.o