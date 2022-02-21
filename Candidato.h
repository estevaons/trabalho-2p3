#ifndef Candidato_h
#define Candidato_h

#include <string>
#include <time.h>
using namespace std;


class Candidato {
    private:
        int numero;
        int votos_nominais;
        string situacao;
        string nome;
        string nome_urna;
        string sexo;
        time_t dataNascimento;
        string destino_voto;
        int num_partido;
        int idade;
        int rank;
    public:
        Candidato();
        Candidato(int numero, int votos_nominais, string situacao, string nome, string nome_urna, string sexo, time_t dataNascimento, string destino_voto, int num_partido);
        ~Candidato();
        int getNumero();
        int getVotosNominais();
        string getSituacao();
        string getNome();
        string getNomeUrna();
        string getSexo();
        time_t getDataNascimento();
        string getDestinoVoto();
        int getNumPartido();
        int getIdade();
        int getRank();
        void setNumero(int numero);
        void setVotosNominais(int votos_nominais);
        void setSituacao(string situacao);
        void setNome(string nome);
        void setNomeUrna(string nome_urna);
        void setSexo(string sexo);
        void setDataNascimento(time_t dataNascimento);
        void setDestinoVoto(string destino_voto);
        void setNumPartido(int num_partido);
        void setIdade(int idade);
        void setRank(int rank);
        void print();
};

#endif