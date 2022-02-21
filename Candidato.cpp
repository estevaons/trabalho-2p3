#include "Candidato.h"
#include <string>
#include <time.h>
#include <iostream>

using namespace std;

Candidato::Candidato(int numero, int votos_nominais, string situacao, string nome, string nome_urna, string sexo, time_t dataNascimento, string destino_voto, int num_partido){
    this->numero = numero;
    this->votos_nominais = votos_nominais;
    this->situacao = situacao;
    this->nome = nome;
    this->nome_urna = nome_urna;
    this->sexo = sexo;
    this->dataNascimento = dataNascimento;
    this->destino_voto = destino_voto;
    this->num_partido = num_partido;
}
//destrutor
Candidato::~Candidato(){}

//getNumero
int Candidato::getNumero(){
    return this->numero;
}
//getVotosNominais
int Candidato::getVotosNominais(){
    return this->votos_nominais;
}
//getSituacao
string Candidato::getSituacao(){
    return this->situacao;
}
//getNome
string Candidato::getNome(){
    return this->nome;
}
//getNomeUrna
string Candidato::getNomeUrna(){
    return this->nome_urna;
}
//getSexo
string Candidato::getSexo(){
    return this->sexo;
}
//getDataNascimento
time_t Candidato::getDataNascimento(){
    return this->dataNascimento;
}
//getDestinoVoto
string Candidato::getDestinoVoto(){
    return this->destino_voto;
}
//getNumPartido
int Candidato::getNumPartido(){
    return this->num_partido;
}
//getIdade
int Candidato::getIdade(){
    return this->idade;
}
//getRank
int Candidato::getRank(){
    return this->rank;
}
//setNumero
void Candidato::setNumero(int numero){
    this->numero = numero;
}
//setVotosNominais
void Candidato::setVotosNominais(int votos_nominais){
    this->votos_nominais = votos_nominais;
}
//setSituacao
void Candidato::setSituacao(string situacao){
    this->situacao = situacao;
}
//setNome
void Candidato::setNome(string nome){
    this->nome = nome;
}
//setNomeUrna
void Candidato::setNomeUrna(string nome_urna){
    this->nome_urna = nome_urna;
}
//setSexo
void Candidato::setSexo(string sexo){
    this->sexo = sexo;
}
//setDataNascimento
void Candidato::setDataNascimento(time_t dataNascimento){
    this->dataNascimento = dataNascimento;
}
//setDestinoVoto
void Candidato::setDestinoVoto(string destino_voto){
    this->destino_voto = destino_voto;
}
//setNumPartido
void Candidato::setNumPartido(int num_partido){
    this->num_partido = num_partido;
}
//setIdade
void Candidato::setIdade(int idade){
    this->idade = idade;
}
//setRank
void Candidato::setRank(int rank){
    this->rank = rank;
}
//print
void Candidato::print(){
    cout << "Numero: " << this->numero << endl;
    cout << "Votos Nominais: " << this->votos_nominais << endl;
    cout << "Situacao: " << this->situacao << endl;
    cout << "Nome: " << this->nome << endl;
    cout << "Nome Urna: " << this->nome_urna << endl;
    cout << "Sexo: " << this->sexo << endl;
    cout << "Data Nascimento: " << this->dataNascimento << endl;
    cout << "Destino Voto: " << this->destino_voto << endl;
    cout << "Numero Partido: " << this->num_partido << endl;
    cout << "Idade: " << this->idade << endl;
    cout << "Rank: " << this->rank << endl;
}