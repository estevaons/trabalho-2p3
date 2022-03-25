#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <list>
#include "Candidato.h"
#include "Partido.h"
#include "Relatorios.h"
#include "LeitorCSV.h"
#include <math.h>
#include <time.h>
#include <iomanip>
#include<locale>
#include<locale.h>
#include <clocale>
#include<sstream>


#include<stdio.h>
#include<stdlib.h>

using namespace std;


int main()
{   
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int contador = 0;
    list<Candidato> candidatos = list<Candidato>();

    /* Faz a leitura do candidatos.csv */

    list<vector<string>> csv_contents;
   
    LeitorCSV leitor = LeitorCSV();
    csv_contents = leitor.LerCSV("candidatos.csv");
    for (auto& row : csv_contents) {
        if(contador == 0){
            contador++;
            continue;
        }

        /* Retira o espaço vazio no final do nome caso houver */
        if(row[4][row[4].length()-1] == ' '){
            row[4].erase(row[4].length()-1);
        }

        /* Cria um boolean para a variavel destinoVoto recebida pelo csv */
        bool destinoVoto;
        if(row[7] =="Válido"){
            destinoVoto = true;
        }else{
            destinoVoto = false;
        }

        /* Cria um candidato e o adiciona na lista de candidatos*/
        Candidato candidato(stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], row[5],row[6], destinoVoto, stoi(row[8]));
        
        if(candidato.getDestinoVoto() == false){
            continue;
        }
        candidatos.push_back(candidato);
    }
  
    contador = 0;
    list<Partido> partidos = list<Partido>();

    
    //list de vetores
    list<vector<string>> csv_contents_2 = leitor.LerCSV("partidos.csv");

    for (auto& row : csv_contents_2) {
        if(contador == 0){
            contador++;
            continue;
        }
        Partido partido (stoi(row[0]),stoi(row[1]),row[2],row[3]);
        partidos.push_back(partido);
    }

    Relatorios relatorios = Relatorios();

    //ordenar candidatos pelo numero de votos e por idade
    candidatos.sort([](Candidato& a, Candidato& b){
        if(a.getVotosNominais() == b.getVotosNominais()){
            return a.getDataNascimento() > b.getDataNascimento();
        }
        return a.getVotosNominais() > b.getVotosNominais();
    });

   // setando o rank de cada candidato de acordo com seu numero de votos
    int rank = 1;
    for(auto& candidato : candidatos){
        candidato.setRank(rank);
        rank++;
    }

    map<int, Partido> partidos_map;

    for(auto& partido : partidos){
        partidos_map.insert(pair<int, Partido>(partido.getNumPartido(), partido));
    }

    //crindo lista de candidatos eleitos
    list<Candidato> candidatosEleitos = list<Candidato>();
    for(auto& candidato : candidatos){
        if(candidato.getSituacao() == "Eleito"){
            if(candidato.getDestinoVoto() == true){
                candidatosEleitos.push_back(candidato);
            }
        }
    }

/* Calculando os relatorios */
    int numeroEleitos = relatorios.calculaRelatorioUm(candidatos);

    relatorios.calculaRelatorioDois(candidatosEleitos, partidos_map);

    relatorios.calculaRelatorioTres(candidatos, partidos_map, numeroEleitos);

    relatorios.calculaRelatorioQuatro(candidatos, partidos_map, numeroEleitos);

    relatorios.calculaRelatorioCinco(candidatos,candidatosEleitos, partidos_map, numeroEleitos);

    relatorios.calculaRelatorioSeis(partidos, candidatos);

    relatorios.calculaRelatorioSete(partidos, candidatos);

    relatorios.calculaRelatorioOito(partidos, candidatos);

    relatorios.calculaRelatorioNove(candidatosEleitos);

    relatorios.calculaRelatorioDez(candidatosEleitos);

    relatorios.calculaRelatorioOnze(candidatos,partidos);


    exit(EXIT_SUCCESS);
}