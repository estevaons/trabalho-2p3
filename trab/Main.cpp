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


string readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

int main()
{   
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int contador = 0;
    list<Candidato> candidatos = list<Candidato>();
    string filename("candidatos.csv");
    string file_contents;


    //list de vetores
    list<vector<string>> csv_contents;
    file_contents = readFileIntoString(filename);
    istringstream iss(file_contents);
    string line;
    while (getline(iss, line)) {
        istringstream line_stream(line);
        string cell;
        vector<string> csv_row;

        while (getline(line_stream, cell, ',')) {
            csv_row.push_back(cell);
        }
        csv_contents.push_back(csv_row);
    }
    for (auto& row : csv_contents) {
        if(contador == 0){
            contador++;
            continue;
        }

        if(row[4][row[4].length()-1] == ' '){
            row[4].erase(row[4].length()-1);
        }

        bool destinoVoto;
        if(row[7] =="Válido"){
            destinoVoto = true;
        }else{
            destinoVoto = false;
        }

        Candidato candidato(stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], row[5],row[6], destinoVoto, stoi(row[8]));
        
        if(candidato.getDestinoVoto() == false){
            continue;
        }
        candidatos.push_back(candidato);
    }
  


    contador = 0;
    list<Partido> partidos = list<Partido>();
    string filename_2("partidos.csv");
    string file_contents_2;


    //list de vetores
    list<vector<string>> csv_contents_2;
    file_contents_2 = readFileIntoString(filename_2);
    istringstream iss_2(file_contents_2);
    string line_2;
    while (getline(iss_2, line_2)) {
        istringstream line_stream(line_2);
        string cell;
        vector<string> csv_row;

        while (getline(line_stream, cell, ',')) {
            csv_row.push_back(cell);
        }
        csv_contents_2.push_back(csv_row);
    }
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