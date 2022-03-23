#ifndef Relatorios_h
#define Relatorios_h

#include "Candidato.h"
#include "Partido.h"

#include <string>
#include <list>
#include <map>
using namespace std;

class Relatorios {
    public:
        int calculaRelatorioUm(list<Candidato> candidatos);
        void calculaRelatorioDois(list <Candidato> candidatosEleitos, map <int, Partido> partidos_map);
        void calculaRelatorioTres(list <Candidato> candidatos, map <int, Partido> partidos_map, int numeroEleitos);
        void calculaRelatorioQuatro(list <Candidato> candidatos, map <int, Partido> partidos_map, int numeroEleitos);
        void calculaRelatorioCinco(list <Candidato> candidatos,list <Candidato> candidatosEleitos, map <int, Partido> partidos_map, int numeroEleitos);
        void calculaRelatorioSeis(list <Partido> partidos, list<Candidato> candidatos);
        void calculaRelatorioSete(list <Partido> partidos, list<Candidato> candidatos);
        void calculaRelatorioOito(list <Partido> partidos, list<Candidato> candidatos);
        void calculaRelatorioNove(list <Candidato> candidatosEleitos);
        void calculaRelatorioDez(list <Candidato> candidatosEleitos);
        void calculaRelatorioOnze(list <Candidato> candidatos, list <Partido> partidos);       
};


#endif