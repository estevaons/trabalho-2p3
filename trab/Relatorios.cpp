#include "Relatorios.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <iomanip>  
#include<stdio.h>

using namespace std;

/* Criando o primeiro relatório */
int Relatorios::calculaRelatorioUm(list<Candidato> candidatos){
    int numeroEleitos = 0;
    for(auto& candidato : candidatos){
        /* Verificando se o candidato foi eleito e possui o destinoVoto válido */
        if(candidato.getSituacao() == "Eleito"){
            if(candidato.getDestinoVoto()){
                numeroEleitos++;
            }
        }
    }
    cout << "Número de vagas: " << numeroEleitos << endl;
    return numeroEleitos;
}

/* Criando o segundo relatório */
void Relatorios::calculaRelatorioDois(list <Candidato> candidatosEleitos, map <int, Partido> partidos_map){
    
    //   Ordernando candidatos eleitos pelo numero de votos e por idade
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

/* Criando o terceiro relatório */

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

/* Criando o quarto relatório */

void Relatorios::calculaRelatorioQuatro(list <Candidato> candidatos, map <int, Partido> partidos_map, int numeroEleitos){
    cout<<"\nTeriam sido eleitos se a votação fosse majoritária, e não foram eleitos:"<<endl;
    cout<<"(com sua posição no ranking de mais votados)"<<endl;

    int cont2 = 0;

    for(auto& candidato: candidatos){
        if(cont2 < numeroEleitos){
            cont2++;
            /* Verifica quem dos mais votados não foram eleitos dentro do número de vagas */
            if(candidato.getSituacao() == "Não eleito" || candidato.getSituacao() == "Suplente"){
                printf("%d - %s / %s (%s, %d votos)\n",cont2,candidato.getNome().c_str(),candidato.getNomeUrna().c_str(),partidos_map.at(candidato.getNumPartido()).getSigla().c_str(),candidato.getVotosNominais());
            }
        }
    }
}

/* Criando o quinto relatório */

void Relatorios::calculaRelatorioCinco(list <Candidato> candidatos,list <Candidato> candidatosEleitos, map <int, Partido> partidos_map, int numeroEleitos){
    
    int menorVotos;
           
    int cont3 = 0;
    /* Verificando quantos votos teve o candidato menos votado dentro do numero de vagas ( e que seria eleito caso a votaçao fosse majoritaria)*/
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
        /* Caso o candidato tenha menos votos que o resultado que achamos: */
        if(candidato.getVotosNominais() < menorVotos){
            printf("%d - %s / %s (%s, %d votos)\n",candidato.getRank(),candidato.getNome().c_str(),candidato.getNomeUrna().c_str(),partidos_map.at(candidato.getNumPartido()).getSigla().c_str(),candidato.getVotosNominais());
        }
    }
}

/* Criando o sexto relatório */

void Relatorios::calculaRelatorioSeis(list <Partido> partidos, list<Candidato> candidatos){

        /* Preenchendo a lista de candidatos de cada partido verificando o número do partido de cada candidato */
        for(auto& partido: partidos){
            int votosPartido = 0;
            for(auto& candidato: candidatos){
                if(candidato.getDestinoVoto() ){
                    if(candidato.getNumPartido() == partido.getNumPartido()){
                        /* Calculando o numero total de votos nominais recebidos pelos candidatos do partido */
                        votosPartido += candidato.getVotosNominais();
                        partido.candidatosDoPartido.push_back(candidato);
                    }
                }
            }
            partido.setVotosNominais(votosPartido);
            /* Calculando o numero de votos totais do partido */
            partido.setVotosTotais(partido.getVotosNominais() + partido.getVotosLegenda());
        }

        //Ordena os partidos pelos votos totais e em caso de empate pelo número do partido
        partidos.sort([](Partido& a, Partido& b){
            if(a.getVotosTotais() == b.getVotosTotais()){
                return a.getNumPartido() < b.getNumPartido();
            }
            return a.getVotosTotais() > b.getVotosTotais();
        });

        cout << "\nVotação dos partidos e número de candidatos eleitos:" << endl;
        int cont = 0;

        for(auto& partido: partidos){
            cont++;
            /* Faz a verificação de singular e plural para o print */
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

/* Criando o sétimo relatório */

void Relatorios::calculaRelatorioSete(list <Partido> partidos, list<Candidato> candidatos){
        /* Preenchendo a lista de candidatos de cada partido verificando o número do partido de cada candidato */
        for(auto& partido: partidos){
            int votosPartido = 0;
            for(auto& candidato: candidatos){
                if(candidato.getDestinoVoto()){
                    if(candidato.getNumPartido() == partido.getNumPartido()){
                        votosPartido += candidato.getVotosNominais();
                        partido.candidatosDoPartido.push_back(candidato);
                    }
                }
            }
            partido.setVotosNominais(votosPartido);
            partido.setVotosTotais(partido.getVotosNominais() + partido.getVotosLegenda());
        }
        /* Ordenando os partidos pelos votos de legenda, caso iguais ordena por votos nominais, caso iguais ordena pelo numero do partido */
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
        /* Verifica se o partido possui algum voto de legenda */
        if(partido.getVotosLegenda() != 0){
            /* Calculando a porcentagem de votos de legenda */
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
        /* Preenchendo a lista de candidatos de cada partido verificando o número do partido de cada candidato */
       for(auto& partido: partidos){
            int votosPartido = 0;
            for(auto& candidato: candidatos){
                if(candidato.getDestinoVoto()){
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
               //Ordenando os candidatos de cada lista do partido pelos votos nominais, caso iguais ordena pelo mais velho
                if(a.getVotosNominais() == b.getVotosNominais()){
                    return a.getIdade("20/11/2022") < b.getIdade("20/11/2022");
                }
               

                return b.getVotosNominais() > a.getVotosNominais();
            });
        }


        // ordenando os partidos por votos nominais, caso iguais ordena pelo numero do partido
        partidos.sort([](Partido& a, Partido& b){
            if(a.candidatosDoPartido.back().getVotosNominais() == b.candidatosDoPartido.back().getVotosNominais()){
                
                return a.getNumPartido() < b.getNumPartido();
            }
            return a.candidatosDoPartido.back().getVotosNominais() > b.candidatosDoPartido.back().getVotosNominais();
        });


        
        int cont = 1;
        for(auto& partido: partidos){
            /* Verifica se o partido possui algum voto de legenda ou algum candidato valido */
            if(partido.getVotosLegenda() == 0 || partido.candidatosDoPartido.size() == 0){
                continue;
            }
            Candidato maisVotado = partido.candidatosDoPartido.back(); /* Pega o primeiro candidato da lista */
            Candidato menosVotado = partido.candidatosDoPartido.front(); /* Pega o ultimo candidato da lista */

            /* Verificando singular e plural */
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

/* Calculando o nono relatório */
void Relatorios::calculaRelatorioNove(list <Candidato> candidatosEleitos){

    int menorQue30 = 0;
    int entre30e40 = 0;
    int entre40e50 = 0;
    int entre50e60 = 0;
    int maiorQue60 = 0;

    for(Candidato candidato : candidatosEleitos){
        /* Cria um tipo data para fazer a comparação dos anos a fim de obter a idade de cada candidato */
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        int dia = 15;
        int mes = 11;
        int ano = 2020;
        string data = to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano);


        /* Calcula a quantidade de candidatos de cada idade desejada */
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
    /* Calculas as porcentagens da quantidade de candidatos com certa idade sobre o total de candidatos eleitos */

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

/* Calcula o décimo relatório */
void Relatorios::calculaRelatorioDez(list <Candidato> candidatosEleitos){
    int homens = 0;
    int mulheres = 0;

    /* Verifica quantos homens e quantas mulheres existem dentro da lista de candidatos eleitos */
    for(Candidato candidato : candidatosEleitos){
        if(candidato.getSexo() == "M"){
            homens++;
        }
        if(candidato.getSexo() == "F"){
            mulheres++;
        }
    }

    /* Calcula as porcentagens */
    float porcentagemHomens = (float)homens / candidatosEleitos.size() * 100;
    float porcentagemMulheres = (float)mulheres / candidatosEleitos.size() * 100;

    printf("\nEleitos, por sexo:\n");
    printf("Feminino:  %d (%.2f%%)\n", mulheres, porcentagemMulheres);
    printf("Masculino: %d (%.2f%%)\n", homens, porcentagemHomens);
}

/* Calcula o décimo primeiro relatório */
void Relatorios::calculaRelatorioOnze(list <Candidato> candidatos, list <Partido> partidos){
    int totalVotosValidos = 0;
    int totalVotosNominais = 0;
    int totalVotosLegenda = 0;

    /* Calcula o total de votos nominais recebidos por todos os candidatos */
    for(Candidato candidato : candidatos){
        if(candidato.getDestinoVoto() == true){
            totalVotosNominais += candidato.getVotosNominais();
        }
    }

    /* Calcula o total de votos de legenda recebidos por todos os partidos */
    for(Partido partido : partidos){
        totalVotosLegenda += partido.getVotosLegenda();
    }

    /* Calcula o total de votos validos */
    totalVotosValidos = totalVotosNominais + totalVotosLegenda;

    /* Calcula as porcentagens */
    float porcentagemNominais = (float)totalVotosNominais / totalVotosValidos * 100;
    float porcentagemLegenda = (float)totalVotosLegenda / totalVotosValidos * 100;

    printf("\nTotal de votos válidos:    %d\n", totalVotosValidos);
    printf("Total de votos nominais:   %d (%0.2f%%)\n", totalVotosNominais, porcentagemNominais);
    printf("Total de votos de legenda: %d (%0.2f%%)\n\n", totalVotosLegenda, porcentagemLegenda);

}
