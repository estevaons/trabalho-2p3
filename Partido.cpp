#include "Partido.h"
#include <string>
#include<list>
#include <iostream>

using namespace std;

Partido::Partido(int num_partido, int votos_legenda, string nome, string sigla){
    this->num_partido = num_partido;
    this->votos_legenda = votos_legenda;
    this->nome = nome;
    this->sigla = sigla;
    this->votosNominais_partido = 0;
    this->votosTotais = 0;
    this->candidatosDoPartido = list<Candidato>();
}
//destrutor
Partido::~Partido(){}

//getNumPartido
int Partido::getNumPartido(){
    return this->num_partido;
}
//getVotosLegenda
int Partido::getVotosLegenda(){
    return this->votos_legenda;
}
//getNome
string Partido::getNome(){
    return this->nome;
}
//getSigla
string Partido::getSigla(){
    return this->sigla;
}
//getVotosNominais
int Partido::getVotosNominais(){
    return this->votosNominais_partido;
}
//getVotosTotais
int Partido::getVotosTotais(){
    return this->votosTotais;
}
//setNumPartido
void Partido::setNumPartido(int num_partido){
    this->num_partido = num_partido;
}
//setVotosLegenda
void Partido::setVotosLegenda(int votos_legenda){
    this->votos_legenda = votos_legenda;
}
//setNome
void Partido::setNome(string nome){
    this->nome = nome;
}
//setSigla
void Partido::setSigla(string sigla){
    this->sigla = sigla;
}
//setVotosNominais
void Partido::setVotosNominais(int votosNominais_partido){
    this->votosNominais_partido = votosNominais_partido;
}
//setVotosTotais
void Partido::setVotosTotais(int votosTotais){
    this->votosTotais = votosTotais;
}
//addCandidato
void Partido::addCandidato(Candidato candidato){
    this->candidatosDoPartido.push_back(candidato);
}
// removeCandidato
// void Partido::removeCandidato(Candidato candidato){
//     this->candidatosDoPartido.remove(candidato);
// }
// //removeCandidato
// void Partido::removeCandidato(int numero){
//     list<Candidato>::iterator it;
//     for(it = this->candidatosDoPartido.begin(); it != this->candidatosDoPartido.end(); it++){
//         if(it->getNumero() == numero){
//             this->candidatosDoPartido.erase(it);
//             break;
//         }
//     }
// }
// //getCandidato
// Candidato Partido::getCandidato(int numero){
//     list<Candidato>::iterator it;
//     for(it = this->candidatosDoPartido.begin(); it != this->candidatosDoPartido.end(); it++){
//         if(it->getNumero() == numero){
//             return *it;
//         }
//     }
// }
// //getCandidatos
// list<Candidato> Partido::getCandidatos(){
//     return this->candidatosDoPartido;
// }
// //setCandidatos
// void Partido::setCandidatos(list<Candidato> candidatos){
//     this->candidatosDoPartido = candidatos;
// }
// //print
// void Partido::print(){
//     cout << "Partido: " << this->num_partido << endl;
//     cout << "Votos Legenda: " << this->votos_legenda << endl;
//     cout << "Nome: " << this->nome << endl;
//     cout << "Sigla: " << this->sigla << endl;
//     cout << "Votos Nominais: " << this->votosNominais_partido << endl;
//     cout << "Votos Totais: " << this->votosTotais << endl;
//     cout << "Candidatos: " << endl;
//     list<Candidato>::iterator it;
//     for(it = this->candidatosDoPartido.begin(); it != this->candidatosDoPartido.end(); it++){
//         it->print();
//     }
// }