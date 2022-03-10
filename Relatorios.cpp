#include "Relatorios.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <iomanip>  
#include<stdio.h>

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
        printf("%d - %s / %s (%s, %d votos)\n",cont,candidato.getNome().c_str(),candidato.getNomeUrna().c_str(),partidos_map.at(candidato.getNumPartido()).getSigla().c_str(),candidato.getVotosNominais());
    }
}

void Relatorios::calculaRelatorioTres(list <Candidato> candidatos, map <int, Partido> partidos_map, int numeroEleitos){
    int cont =0;
    cout <<"\nCandidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    cont = 0;
    for(auto& candidato: candidatos){
        if(cont < numeroEleitos){
            cont ++;
            printf("%d - %s / %s (%s, %d votos)\n",cont,candidato.getNome().c_str(),candidato.getNomeUrna().c_str(),partidos_map.at(candidato.getNumPartido()).getSigla().c_str(),candidato.getVotosNominais());
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
                printf("%d - %s / %s (%s, %d votos)\n",cont2,candidato.getNome().c_str(),candidato.getNomeUrna().c_str(),partidos_map.at(candidato.getNumPartido()).getSigla().c_str(),candidato.getVotosNominais());
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
            printf("%d - %s / %s (%s, %d votos)\n",candidato.getRank(),candidato.getNome().c_str(),candidato.getNomeUrna().c_str(),partidos_map.at(candidato.getNumPartido()).getSigla().c_str(),candidato.getVotosNominais());
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
                printf("%d - %s - %d, %d votos (%d nominais e %d de legenda), %d candidatos eleitos\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosTotais(),partido.getVotosNominais(),partido.getVotosLegenda(),partido.getQtdEleitos());
            }

            if(partido.getVotosTotais() > 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() <= 1){
                printf("%d - %s - %d, %d votos (%d nominal e %d de legenda), %d candidato eleito\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosTotais(),partido.getVotosNominais(),partido.getVotosLegenda(),partido.getQtdEleitos());
            }

            if(partido.getVotosTotais() > 1 && partido.getVotosNominais() > 1 && partido.getQtdEleitos() <= 1){
                printf("%d - %s - %d, %d votos (%d nominais e %d de legenda), %d candidato eleito\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosTotais(),partido.getVotosNominais(),partido.getVotosLegenda(),partido.getQtdEleitos());
            }

            if(partido.getVotosTotais() > 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() > 1){
                printf("%d - %s - %d, %d votos (%d nominal e %d de legenda), %d candidatos eleitos\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosTotais(),partido.getVotosNominais(),partido.getVotosLegenda(),partido.getQtdEleitos());
            }
            if(partido.getVotosTotais() <= 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() <= 1){
                printf("%d - %s - %d, %d voto (%d nominal e %d de legenda), %d candidato eleito\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosTotais(),partido.getVotosNominais(),partido.getVotosLegenda(),partido.getQtdEleitos());
            }
            if(partido.getVotosTotais() <= 1 && partido.getVotosNominais() <= 1 && partido.getQtdEleitos() > 1){
                printf("%d - %s - %d, %d voto (%d nominal e %d de legenda), %d candidatos eleitos\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosTotais(),partido.getVotosNominais(),partido.getVotosLegenda(),partido.getQtdEleitos());
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
            return a.getVotosNominais() > b.getVotosNominais();
        }
        return a.getVotosLegenda() > b.getVotosLegenda();
    });

    cout << "\nVotação dos partidos (apenas votos de legenda):" << endl;
    int cont = 0;

    for(auto& partido: partidos){
        if(partido.getVotosLegenda() != 0){
            float porcentagem = (float)partido.getVotosLegenda() / (float)partido.getVotosTotais() * 100;
            cont++;
            printf("%d - %s - %d, %d votos de legenda (%0.2f%% do total do partido)\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosLegenda(),porcentagem);
        }else{
            cont++;
            printf("%d - %s - %d, %d voto de legenda (proporção não calculada, 0 voto no partido)\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),partido.getVotosLegenda());
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
               //ordernar pela data de nasciemnto se os votos forem iguais com proferencia para o mais velho
                if(a.getVotosNominais() == b.getVotosNominais()){
                    return a.getIdade("20/11/2500") < b.getIdade("20/11/2500");
                }
               

                return b.getVotosNominais() > a.getVotosNominais();
            });
        }


        // ordenando os partidos por votos nominais e por numero
        partidos.sort([](Partido& a, Partido& b){
            if(a.candidatosDoPartido.size() == 0 || b.candidatosDoPartido.size() == 0){
                return false;
            }

            if(a.candidatosDoPartido.back().getVotosNominais() == b.candidatosDoPartido.back().getVotosNominais()){
                
                return a.getNumPartido() < b.getNumPartido();
            }
            return a.candidatosDoPartido.back().getVotosNominais() > b.candidatosDoPartido.back().getVotosNominais();
        });


        
        int cont = 1;
        for(auto& partido: partidos){
            if(partido.getVotosLegenda() == 0 || partido.candidatosDoPartido.size() == 0){
                continue;
            }
            // printf("\nMais votado do partido %s : %s com %d votos.\n",partido.getSigla().c_str(),partido.candidatosDoPartido.back().getNomeUrna().c_str(),partido.candidatosDoPartido.back().getVotosNominais());
            Candidato maisVotado = partido.candidatosDoPartido.back();
            Candidato menosVotado = partido.candidatosDoPartido.front();

            if(maisVotado.getVotosNominais() > 1 && menosVotado.getVotosNominais() > 1){
                printf("%d - %s - %d, %s (%d, %d votos) / %s (%d, %d votos)\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),maisVotado.getNomeUrna().c_str(),maisVotado.getNumero(),maisVotado.getVotosNominais(),menosVotado.getNomeUrna().c_str(),menosVotado.getNumero(),menosVotado.getVotosNominais());
            }

            if(maisVotado.getVotosNominais() > 1 && menosVotado.getVotosNominais() <= 1){
                printf("%d - %s - %d, %s (%d, %d votos) / %s (%d, %d voto)\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),maisVotado.getNomeUrna().c_str(),maisVotado.getNumero(),maisVotado.getVotosNominais(),menosVotado.getNomeUrna().c_str(),menosVotado.getNumero(),menosVotado.getVotosNominais());
            }

            if(maisVotado.getVotosNominais() <= 1 && menosVotado.getVotosNominais() > 1){
                printf("%d - %s - %d, %s (%d, %d voto) / %s (%d, %d votos)\n",cont,partido.getSigla().c_str(),partido.getNumPartido(),maisVotado.getNomeUrna().c_str(),maisVotado.getNumero(),maisVotado.getVotosNominais(),menosVotado.getNomeUrna().c_str(),menosVotado.getNumero(),menosVotado.getVotosNominais());
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


    printf("\nEleitos, por faixa etária (na data da eleição):\n");
    printf("      Idade < 30: %d (%0.2f%%)\n",menorQue30,porcentagemMenorQue30);
    printf("30 <= Idade < 40: %d (%0.2f%%)\n",entre30e40,porcentagemEntre30e40);
    printf("40 <= Idade < 50: %d (%0.2f%%)\n",entre40e50,porcentagemEntre40e50);
    printf("50 <= Idade < 60: %d (%0.2f%%)\n",entre50e60,porcentagemEntre50e60);
    printf("60 <= Idade     : %d (%0.2f%%)\n",maiorQue60,porcentagemMaiorQue60);

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

    printf("\nEleitos, por sexo:\n");
    printf("Feminino:  %d (%.2f%%)\n", mulheres, porcentagemMulheres);
    printf("Masculino: %d (%.2f%%)\n", homens, porcentagemHomens);
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

    printf("\nTotal de votos válidos:    %d\n", totalVotosValidos);
    printf("Total de votos nominais:   %d (%0.2f%%)\n", totalVotosNominais, porcentagemNominais);
    printf("Total de votos de legenda: %d (%0.2f%%)\n\n", totalVotosLegenda, porcentagemLegenda);

}
