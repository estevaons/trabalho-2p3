#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include<list>
#include "Candidato.h"
#include "Partido.h"

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
        Candidato candidato(stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], row[5], stoi(row[6]), row[7], stoi(row[8]));
        candidatos.push_back(candidato);
    }
    //imprimir lista de candidatos
    for(auto& candidato : candidatos){
        cout << candidato.getNumero() << " " << candidato.getVotosNominais() << " " << candidato.getSituacao() << " " << candidato.getNome() << " " << candidato.getNomeUrna() << " " << candidato.getSexo() << " " << candidato.getDataNascimento() << " " << candidato.getDestinoVoto() << " " << candidato.getNumPartido() << endl;
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
    //imprimir lista de partidos
    for(auto& partido : partidos){
        cout << partido.getNumPartido() << " " << partido.getVotosLegenda() << " " << partido.getNome() << " " << partido.getSigla() << endl;
    }



    exit(EXIT_SUCCESS);
}