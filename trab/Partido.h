#ifndef Partido_h
#define Partido_h
#include "Candidato.h"

#include <string>
#include<list>

using namespace std;

class Partido {
    private:
        int num_partido;
        int votos_legenda;
        string nome;
        string sigla;
        int votosNominais_partido;
        int votosTotais;

      

    public:
      //lista de candidatos
        list<Candidato> candidatosDoPartido;
        Partido();
        Partido(int num_partido, int votos_legenda, string nome, string sigla);
        ~Partido();
        int getNumPartido();
        int getVotosLegenda();
        string getNome();
        string getSigla();
        int getVotosNominais();
        int getVotosTotais();
        int getQtdEleitos();
        void setNumPartido(int num_partido);
        void setVotosLegenda(int votos_legenda);
        void setNome(string nome);
        void setSigla(string sigla);
        void setVotosNominais(int votosNominais_partido);
        void setVotosTotais(int votosTotais);
        void addCandidato(Candidato candidato);
        void removeCandidato(Candidato candidato);
        void removeCandidato(int numero);
        Candidato getCandidato(int numero);
        list<Candidato> getCandidatos();
        void setCandidatos(list<Candidato> candidatos);
        void print();
};


#endif