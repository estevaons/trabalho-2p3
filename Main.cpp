#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <string>
#include <list>
#include "Candidato.h"
#include "Partido.h"
#include <math.h>
#include <time.h>
#include <iomanip>
#include<locale.h>

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
    setlocale(LC_ALL, "Portuguese");
    

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
        Candidato candidato(stoi(row[0]), stoi(row[1]), row[2], row[3], row[4], row[5],row[6], row[7], stoi(row[8]));
        if(candidato.getDestinoVoto() != "Válido"){
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
    cout<<"\nVereadores eleitos:"<<endl;
    int cont =0;
    for(auto& candidato : candidatosEleitos){
        cont ++;
        // cout << candidato.getNumero() << " " << candidato.getVotosNominais() << " " << candidato.getSituacao() << " " << candidato.getNome() << " " << candidato.getNomeUrna() << " " << candidato.getSexo() << " " << candidato.getDataNascimento() << " " << candidato.getDestinoVoto() << " " << candidato.getNumPartido() << endl;
        cout << cont<<" - "<<candidato.getNome()<<" / "<<candidato.getNomeUrna()<<" ("<<partidos_map.at(candidato.getNumPartido()).getSigla()<<", "<<candidato.getVotosNominais()<<" votos)"<< endl;
    }

 


    // 3.imprimir candidatos mais votados dentro do numero de vagas

    cout <<"\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    cont = 0;
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
               cout<<candidato.getRank()<<" - " << candidato.getNome() <<" / "<< candidato.getNomeUrna()<<" (" <<partidos_map.at(candidato.getNumPartido()).getSigla()<<", " <<candidato.getVotosNominais()<<" votos)"<< endl;
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
            cout << candidato.getRank() << " - " << candidato.getNome() << " / " << candidato.getNomeUrna() << " (" << partidos_map.at(candidato.getNumPartido()).getSigla() << ", " << candidato.getVotosNominais() << " votos)" << endl;
        }
    }

     // 6.Votos totalizados por partido e número de candidatos eleitos;

     
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

        //7. Votos de legenda (com a porcentagem destes votos frente ao total de votos no partido)

          //ordernar partidos por votos de legenda
        partidos.sort([](Partido& a, Partido& b){
            if(a.getVotosLegenda() == b.getVotosLegenda()){
                if(a.getVotosNominais() == b.getVotosNominais()){
                    return a.getNumPartido() < b.getNumPartido();
                }
                return a.getNumPartido() < b.getNumPartido();
            }
            return a.getVotosLegenda() > b.getVotosLegenda();
        });

        cout << "\nVotação dos partidos (apenas votos de legenda):" << endl;
        cont = 0;

        for(auto& partido: partidos){
            if(partido.getVotosLegenda() != 0){
                float porcentagem = (float)partido.getVotosLegenda() / (float)partido.getVotosTotais() * 100;
                //duas casas decimais

                cont++;
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosLegenda() << " votos de legenda (" << fixed << setprecision(2) << porcentagem << "% do total do partido)" << endl;
            }else{
                cont++;
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << partido.getVotosLegenda() << " voto de legenda (proporção não calculada, 0 voto no partido)" << endl;
                continue;
            }
        }

           //      8.8. Primeiro e último colocados de cada partido (com nome da urna, número do candidato e total de votos
        // nominais). Partidos que não possuírem candidatos com um número positivo de votos válidos devem ser
        // ignorados;

        cout << "\nPrimeiro e último colocados de cada partido:" << endl;
    
        for(auto& partido: partidos){
            partido.candidatosDoPartido.sort([](Candidato& a, Candidato& b){
                if(a.getVotosNominais() == b.getVotosNominais()){
                    return a.getDataNascimento() < b.getDataNascimento();
                   
                }
                return b.getVotosNominais() > a.getVotosNominais();
            });
        }

        // ordenando os partidos por votos nominais e por numero
        partidos.sort([](Partido& a, Partido& b){
            if(a.getVotosNominais() == b.getVotosNominais()){
                return a.getNumPartido() < b.getNumPartido();
            }
            return b.candidatosDoPartido.back().getVotosNominais() < a.candidatosDoPartido.back().getVotosNominais();
        });


        
        cont = 1;
        for(auto& partido: partidos){
            if(partido.getVotosLegenda() == 0 || partido.candidatosDoPartido.size() == 0){
                continue;
            }
            Candidato maisVotado = partido.candidatosDoPartido.back();
            Candidato menosVotado = partido.candidatosDoPartido.front();

            if(maisVotado.getVotosNominais() > 1 && menosVotado.getVotosNominais() > 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << maisVotado.getNomeUrna() << " (" << maisVotado.getNumero() << ", " << maisVotado.getVotosNominais() << " votos) / " << menosVotado.getNomeUrna() << " (" << menosVotado.getNumero() << ", " << menosVotado.getVotosNominais() << " votos)" << endl;
            }

            if(maisVotado.getVotosNominais() > 1 && menosVotado.getVotosNominais() <= 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << maisVotado.getNomeUrna() << " (" << maisVotado.getNumero() << ", " << maisVotado.getVotosNominais() << " votos) / " << menosVotado.getNomeUrna() << " (" << menosVotado.getNumero() << ", " << menosVotado.getVotosNominais() << " voto)" << endl;
            }

            if(maisVotado.getVotosNominais() <= 1 && menosVotado.getVotosNominais() > 1){
                cout << cont << " - " << partido.getSigla() << " - " << partido.getNumPartido() << ", " << maisVotado.getNomeUrna() << " (" << maisVotado.getNumero() << ", " << maisVotado.getVotosNominais() << " voto) / " << menosVotado.getNomeUrna() << " (" << menosVotado.getNumero() << ", " << menosVotado.getVotosNominais() << " votos)" << endl;
            }
            cont++;
        }

        // 9. Distribuição de eleitos por faixa etária, considerando a idade do candidato no dia da eleição;


        int menorQue30 = 0;
        int entre30e40 = 0;
        int entre40e50 = 0;
        int entre50e60 = 0;
        int maiorQue60 = 0;

        for(Candidato candidato : candidatosEleitos){
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            int dia = 15;
            int mes = 11;
            int ano = 2020;
            string data = to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);

            if(candidato.getIdade(data) < 30){
                menorQue30++;
            }
            if(30 <= candidato.getIdade(data) && candidato.getIdade(data) < 40){
                entre30e40++;
            }
            if(40 <= candidato.getIdade(data) && candidato.getIdade(data) < 50){
                entre40e50++;
            }
            if(50 <= candidato.getIdade(data) && candidato.getIdade(data) < 60){
                entre50e60++;
            }
            if(candidato.getIdade(data) >= 60){
                maiorQue60++;
            }
        }

        float porcentagemMenorQue30 = (float)menorQue30 / (float)candidatosEleitos.size() * 100;
        float porcentagemEntre30e40 = (float)entre30e40 / (float)candidatosEleitos.size() * 100;
        float porcentagemEntre40e50 = (float)entre40e50 / (float)candidatosEleitos.size() * 100;
        float porcentagemEntre50e60 = (float)entre50e60 / (float)candidatosEleitos.size() * 100;
        float porcentagemMaiorQue60 = (float)maiorQue60 / (float)candidatosEleitos.size() * 100;
    








        cout << "Eleitos, por faixa etária (na data da eleição):" << endl;
        cout << "      Idade < 30: " << menorQue30 << " (" << fixed << setprecision(2) << porcentagemMenorQue30 << "%)" << endl;
        cout << "30 <= Idade < 40: " << entre30e40 << " (" << fixed << setprecision(2) << porcentagemEntre30e40 << "%)" << endl;
        cout << "40 <= Idade < 50: " << entre40e50 << " (" << fixed << setprecision(2) << porcentagemEntre40e50 << "%)" << endl;
        cout << "50 <= Idade < 60: " << entre50e60 << " (" << fixed << setprecision(2) << porcentagemEntre50e60 << "%)" << endl;
        cout << "60 <= Idade     : " << maiorQue60 << " (" << fixed << setprecision(2) << porcentagemMaiorQue60 << "%)" << endl;



        //10. Distribuição de eleitos por sexo;

        int homens = 0;
        int mulheres = 0;

        for(Candidato candidato : candidatosEleitos){
            if(candidato.getSexo() == "M"){
                homens++;
            }
            if(candidato.getSexo() == "F"){
                mulheres++;
            }
        }

        //imprimir resultados
        float porcentagemHomens = (float)homens / candidatosEleitos.size() * 100;
        float porcentagemMulheres = (float)mulheres / candidatosEleitos.size() * 100;

        cout << "Eleitos, por sexo:" << endl;
        cout << "Feminino:  " << mulheres << " (" << fixed << setprecision(2) << porcentagemMulheres << "%)" << endl;
        cout << "Masculino: " << homens << " (" << fixed << setprecision(2) << porcentagemHomens << "%)" << endl;



        // 11. total de votos válidos

        int totalVotosValidos = 0;
        int totalVotosNominais = 0;
        int totalVotosLegenda = 0;

        for(Candidato candidato : candidatos){
            if(candidato.getDestinoVoto() == "Válido"){
                totalVotosNominais += candidato.getVotosNominais();
            }
        }
        for(Partido partido : partidos){
            totalVotosLegenda += partido.getVotosLegenda();
        }

        totalVotosValidos = totalVotosNominais + totalVotosLegenda;

        float porcentagemNominais = (float)totalVotosNominais / totalVotosValidos * 100;
        float porcentagemLegenda = (float)totalVotosLegenda / totalVotosValidos * 100;

        cout << "Total de votos válidos:    " << totalVotosValidos << endl;
        cout << "Total de votos nominais:   " << totalVotosNominais << " (" << fixed << setprecision(2) << porcentagemNominais << "%)" << endl;
        cout << "Total de votos de legenda: " << totalVotosLegenda << " (" << fixed << setprecision(2) << porcentagemLegenda << "%)" << endl;


    exit(EXIT_SUCCESS);
}