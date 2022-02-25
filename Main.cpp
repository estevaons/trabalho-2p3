#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <list>
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
    // for(auto& candidato : candidatos){
    //     cout << candidato.getNumero() << " " << candidato.getVotosNominais() << " " << candidato.getSituacao() << " " << candidato.getNome() << " " << candidato.getNomeUrna() << " " << candidato.getSexo() << " " << candidato.getDataNascimento() << " " << candidato.getDestinoVoto() << " " << candidato.getNumPartido() << endl;
    // }




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
    // for(auto& partido : partidos){
    //     cout << partido.getNumPartido() << " " << partido.getVotosLegenda() << " " << partido.getNome() << " " << partido.getSigla() << endl;
    // }


    //ordenar candidatos pelo numero de votos e por idade
    candidatos.sort([](Candidato& a, Candidato& b){
        if(a.getVotosNominais() == b.getVotosNominais()){
            return a.getDataNascimento() < b.getDataNascimento();
        }
        return a.getVotosNominais() > b.getVotosNominais();
    });
      // setando o rank de cada candidato de acordo com seu numero de votos
    int rank = 1;
    for(auto& candidato : candidatos){
        candidato.setRank(rank);
        rank++;
    }

    // 1.imprimir candidatos eleitos

    //criar mapa de partidos
    map<int, Partido> partidos_map;

    for(auto& partido : partidos){
        partidos_map.insert(pair<int, Partido>(partido.getNumPartido(), partido));
    }


    int numeroEleitos = 0;
    for(auto& candidato : candidatos){
        if(candidato.getSituacao() == "Eleito"){
            if(candidato.getDestinoVoto() == "Válido"){
                numeroEleitos++;
            }
        }
    }
    cout << "Número de vagas: " << numeroEleitos << endl;

    // 2. criar lista de candidatos eleitos
    list<Candidato> candidatosEleitos = list<Candidato>();
    for(auto& candidato : candidatos){
        if(candidato.getSituacao() == "Eleito"){
            if(candidato.getDestinoVoto() == "Válido"){
                candidatosEleitos.push_back(candidato);
            }
        }
    }

    //ordernar candidatos eleitos pelo numero de votos e por idade
    candidatosEleitos.sort([](Candidato& a, Candidato& b){
        if(a.getVotosNominais() == b.getVotosNominais()){
            return a.getDataNascimento() < b.getDataNascimento();
        }
        return a.getVotosNominais() > b.getVotosNominais();
    });

    //imprimir candidatos eleitos ordenados
    
    for(auto& candidato : candidatosEleitos){
        cout << candidato.getNumero() << " " << candidato.getVotosNominais() << " " << candidato.getSituacao() << " " << candidato.getNome() << " " << candidato.getNomeUrna() << " " << candidato.getSexo() << " " << candidato.getDataNascimento() << " " << candidato.getDestinoVoto() << " " << candidato.getNumPartido() << endl;
    }

 


    // 3.imprimir candidatos mais votados dentro do numero de vagas

    cout <<"\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    int cont = 0;
    for(auto& candidato: candidatos){
        if(cont < numeroEleitos){
            cont ++;
            cout << cont<<" - "<<candidato.getNome()<<" / "<<candidato.getNomeUrna()<<" ("<<partidos_map.at(candidato.getNumPartido()).getSigla()<<", "<<candidato.getVotosNominais()<<" votos)"<< endl;
        }
    }
  

    // 4. Candidatos não eleitos e que seriam eleitos se a votação fosse majoritária

    cout<<"\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:"<<endl;
    cout<<"(com sua posição no ranking de mais votados)"<<endl;

    int cont2 = 0;

    for(auto& candidato: candidatos){
        if(cont2 < numeroEleitos){
            cont2++;
            if(candidato.getSituacao() == "Não eleito" || candidato.getSituacao() == "Suplente"){
               cout<<candidato.getRank()<<" - " << candidato.getNome() <<" / "<< candidato.getNomeUrna()<<" (" <<partidos_map.at(candidato.getNumPartido()).getSigla()<<", " <<candidato.getVotosNominais()<<" votos )"<< endl;
            }
        }
    }


    // 5. Candidatos eleitos no sistema proporcional vigente, e que não seriam eleitos se a votação fosse
    // majoritária, isto é, pelo número de votos apenas que um candidato recebe diretamente;
    
    int menorVotos;
           
    int cont3 = 0;
    //percorrer lista de candidatos
    for(auto& candidato: candidatos){
        if(cont3 == numeroEleitos-1){
            menorVotos = candidato.getVotosNominais();
            break;
        }
        cont3 ++;
    }

    cout << "\nEleitos, que se beneficiaram do sistema proporcional:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;

    for(auto& candidato : candidatosEleitos){
        if(candidato.getVotosNominais() < menorVotos){
            cout << candidato.getRank() << " - " << candidato.getNome() << " / " << candidato.getNomeUrna() << " (" << partidos_map.at(candidato.getNumPartido()).getSigla() << ", " << candidato.getVotosNominais() << " votos )" << endl;
        }
    }

     // 6.Votos totalizados por partido e número de candidatos eleitos;

     
        // for(Partidos partido : partidos){  
        //     int votosPartido = 0;   
        //     for(Candidato candidato : candidatos){
        //         if(candidato.getDestino_voto().equals("Válido")){
        //             if(candidato.getNum_partido() == partido.getNum_partido()){                   
        //             votosPartido += candidato.getVotos_nominais();
        //             partido.candidatosDoPartido.add(candidato);
        //             }
        //         }           
        //     }
        //     partido.setVotosNominais_partido(votosPartido);       
        //     partido.setVotosTotais(partido.getVotosNominais_partido() + partido.getVotosLegenda());
       
        // }
        for(auto& partido: partidos){
            int votosPartido = 0;
            for(auto& candidato: candidatos){
                if(candidato.getDestinoVoto() == "Válido"){
                    if(candidato.getNumPartido() == partido.getNumPartido()){
                        votosPartido += candidato.getVotosNominais();
                        partido.candidatosDoPartido.push_back(candidato);
                    }
                }
            }
            partido.setVotosNominais(votosPartido);
            partido.setVotosTotais(partido.getVotosNominais() + partido.getVotosLegenda());
        }

        //ordena partido por votos e por numero
        partidos.sort([](Partido& a, Partido& b){
            if(a.getVotosTotais() == b.getVotosTotais()){
                return a.getNumPartido() < b.getNumPartido();
            }
            return a.getVotosTotais() > b.getVotosTotais();
        });

        //imprimir partidos ordenados
        cout << "\nVotação dos partidos e número de candidatos eleitos:" << endl;
        cont = 0;

        for(auto& partido: partidos){
            cont++;
            if(partido.getVotosTotais() > 1 && partido.getVotosNominais() > 1 && partido.getQtdEleitos() > 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosTotais() << " votos (" << partido.getVotosNominais() << " nominais e " << partido.getVotosLegenda() << " de legenda), " << partido.getQtdEleitos() << " candidatos eleitos" << endl;
            }

            if(partido.getVotosTotais() > 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() <= 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosTotais() << " votos (" << partido.getVotosNominais() << " nominal e " << partido.getVotosLegenda() << " de legenda), " << partido.getQtdEleitos() << " candidato eleito" << endl;
            }

            if(partido.getVotosTotais() > 1 && partido.getVotosNominais() > 1 && partido.getQtdEleitos() <= 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosTotais() << " votos (" << partido.getVotosNominais() << " nominais e " << partido.getVotosLegenda() << " de legenda), " << partido.getQtdEleitos() << " candidato eleito" << endl;
            }

            if(partido.getVotosTotais() > 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() > 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosTotais() << " votos (" << partido.getVotosNominais() << " nominal e " << partido.getVotosLegenda() << " de legenda), " << partido.getQtdEleitos() << " candidatos eleitos" << endl;
            }
            if(partido.getVotosTotais() <= 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() <= 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosTotais() << " voto (" << partido.getVotosNominais() << " nominal e " << partido.getVotosLegenda() << " de legenda), " << partido.getQtdEleitos() << " candidato eleito" << endl;
            }
            if(partido.getVotosTotais() <= 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() > 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosTotais() << " voto (" << partido.getVotosNominais() << " nominal e " << partido.getVotosLegenda() << " de legenda), " << partido.getQtdEleitos() << " candidatos eleitos" << endl;
            }
        }
      


    exit(EXIT_SUCCESS);
}