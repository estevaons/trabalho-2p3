#include "Relatorios.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <iomanip>  

using namespace std;


int Relatorios::calculaRelatorioUm(list<Candidato> candidatos){
    int numeroEleitos = 0;
    for(auto& candidato : candidatos){
        if(candidato.getSituacao() == "Eleito"){
            if(candidato.getDestinoVoto() == "Válido"){
                numeroEleitos++;
            }
        }
    }
    cout << "Número de vagas: " << numeroEleitos << endl;
    return numeroEleitos;
}


void Relatorios::calculaRelatorioDois(list <Candidato> candidatosEleitos, map <int, Partido> partidos_map){
    
    //   ordernar candidatos eleitos pelo numero de votos e por idade
    candidatosEleitos.sort([](Candidato& a, Candidato& b){
        if(a.getVotosNominais() == b.getVotosNominais()){
            return a.getDataNascimento() < b.getDataNascimento();
        }
        return a.getVotosNominais() > b.getVotosNominais();
    });


    cout<<"\nVereadores eleitos:"<<endl;
    int cont =0;
    for(auto& candidato : candidatosEleitos){
        cont ++;
        // cout << candidato.getNumero() << " " << candidato.getVotosNominais() << " " << candidato.getSituacao() << " " << candidato.getNome() << " " << candidato.getNomeUrna() << " " << candidato.getSexo() << " " << candidato.getDataNascimento() << " " << candidato.getDestinoVoto() << " " << candidato.getNumPartido() << endl;
        cout << cont<<" - "<<candidato.getNome()<<" / "<<candidato.getNomeUrna()<<" ("<<partidos_map.at(candidato.getNumPartido()).getSigla()<<", "<<candidato.getVotosNominais()<<" votos)"<< endl;
    }
}

void Relatorios::calculaRelatorioTres(list <Candidato> candidatos, map <int, Partido> partidos_map, int numeroEleitos){
    int cont =0;
    cout <<"\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    cont = 0;
    for(auto& candidato: candidatos){
        if(cont < numeroEleitos){
            cont ++;
            cout << cont<<" - "<<candidato.getNome()<<" / "<<candidato.getNomeUrna()<<" ("<<partidos_map.at(candidato.getNumPartido()).getSigla()<<", "<<candidato.getVotosNominais()<<" votos)"<< endl;
        }
    }
}

void Relatorios::calculaRelatorioQuatro(list <Candidato> candidatos, map <int, Partido> partidos_map, int numeroEleitos){
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
}

void Relatorios::calculaRelatorioCinco(list <Candidato> candidatos,list <Candidato> candidatosEleitos, map <int, Partido> partidos_map, int numeroEleitos){
    
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
}

void Relatorios::calculaRelatorioSeis(list <Partido> partidos, list<Candidato> candidatos){

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
        int cont = 0;

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

}

void Relatorios::calculaRelatorioSete(list <Partido> partidos, list<Candidato> candidatos){
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
    int cont = 0;

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
}

void Relatorios::calculaRelatorioOito(list <Partido> partidos, list<Candidato> candidatos){
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


        
        int cont = 1;
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
}

void Relatorios::calculaRelatorioNove(list <Candidato> candidatosEleitos){

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









    cout << "\nEleitos, por faixa etária (na data da eleição):" << endl;
    cout << "      Idade < 30: " << menorQue30 << " (" << fixed << setprecision(2) << porcentagemMenorQue30 << "%)" << endl;
    cout << "30 <= Idade < 40: " << entre30e40 << " (" << fixed << setprecision(2) << porcentagemEntre30e40 << "%)" << endl;
    cout << "40 <= Idade < 50: " << entre40e50 << " (" << fixed << setprecision(2) << porcentagemEntre40e50 << "%)" << endl;
    cout << "50 <= Idade < 60: " << entre50e60 << " (" << fixed << setprecision(2) << porcentagemEntre50e60 << "%)" << endl;
    cout << "60 <= Idade     : " << maiorQue60 << " (" << fixed << setprecision(2) << porcentagemMaiorQue60 << "%)" << endl;


}

void Relatorios::calculaRelatorioDez(list <Candidato> candidatosEleitos){
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
}

void Relatorios::calculaRelatorioOnze(list <Candidato> candidatos, list <Partido> partidos){
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

}
