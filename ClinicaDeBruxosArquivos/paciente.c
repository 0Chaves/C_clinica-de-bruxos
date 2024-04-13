#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratamentos.h"

int qtd_pacientes = 0;
FILE *arquivoPacientes;

//Abre o arquivo de pacientes
int inicializarPacientes(){
	if((arquivoPacientes = fopen("pacientes.bin", "r+b")) == NULL){
		arquivoPacientes = fopen("pacientes.bin", "w+b");
		
	}
	if(arquivoPacientes == NULL){
		return 0;
	}
	
	fseek(arquivoPacientes, 0, SEEK_END);
	qtd_pacientes = ftell(arquivoPacientes)/sizeof(st_paciente);
	return 1;
}

//Fecha o arquivo de pacientes
int EncerraPacientes(){
	fclose(arquivoPacientes);
	return 1;
}

//Salvar um novo paciente no arquivo
int salvarPaciente(st_paciente novo){
	st_paciente *temp_paciente;
	temp_paciente = (st_paciente*) malloc(sizeof(st_paciente));
	if(temp_paciente == NULL){
			return 0;
		}
	*temp_paciente = novo;
	fseek(arquivoPacientes, 0, SEEK_END);
	fwrite(temp_paciente, sizeof(st_paciente), 1, arquivoPacientes);
	free(temp_paciente);
	qtd_pacientes++;
	return 1;
}

//Retornar a quantidade de pacientes
int QuantidadePacientes(){
	return qtd_pacientes;
}

//Retorna um paciente de acordo com o indice
st_paciente* obterPacientePeloIndice(int indice){
	if(indice<0 || indice>=qtd_pacientes){
		return NULL;
	}
	st_paciente* paciente = (st_paciente*) malloc(sizeof(st_paciente));
	if(paciente==NULL){
		return NULL;
	}
	fseek(arquivoPacientes, indice*sizeof(st_paciente), SEEK_SET);
	fread(paciente, sizeof(st_paciente), 1, arquivoPacientes);
	return paciente;
}

//Retorna um paciente de acordo com o codigo
st_paciente* obterPacientePeloCodigo(int codigo){
	int i;
	st_paciente *paciente = (st_paciente*) malloc(sizeof(st_paciente));
	if(paciente == NULL){
		return NULL;
	}
	rewind(arquivoPacientes);
	for(i=0; i<qtd_pacientes; i++){
		fread(paciente, sizeof(st_paciente), 1, arquivoPacientes);
		if(paciente->codigo == codigo){
			return paciente;
		}
	}
	free(paciente);
	return NULL;
}

//Altera o conteúdo da struct de um Paciente
int atualizarPaciente(st_paciente paciente_novo){
	int i;
	st_paciente *temp = (st_paciente*) malloc(sizeof(st_paciente));
	if(temp == NULL){
		return 0;
	}
	rewind(arquivoPacientes);
	for(i=0; i<qtd_pacientes; i++){
		fread(temp, sizeof(st_paciente), 1, arquivoPacientes);
		if(temp->codigo == paciente_novo.codigo){
			*temp = paciente_novo;
			fseek(arquivoPacientes, -1*sizeof(st_paciente), SEEK_CUR);
			fwrite(temp, sizeof(st_paciente), 1, arquivoPacientes);
			free(temp);
			return 1;
		}
	}
	free(temp);
	return 0;
}


//Apagar paciente pelo codigo (cria um novo arquivo, copiando todos os dados exceto aquele que possuir o codigo a ser deletado)
int apagarPacientePeloCodigo(int codigo){
	if(verificaPaciente(codigo)){
		return 0;
	}	
	st_paciente *temp = (st_paciente*) malloc(sizeof(st_paciente));
	if(temp == NULL){
		return 0;
	}
	FILE *novo_arquivo;
	novo_arquivo = fopen("temp.bin", "w+b");
	if(novo_arquivo == NULL){
		free(temp);
		return 0;
	}
	rewind(arquivoPacientes);
	int i;
	for(i=0; i<qtd_pacientes; i++){
		fread(temp, sizeof(st_paciente), 1, arquivoPacientes);
		if(temp->codigo != codigo){
			fwrite(temp, sizeof(st_paciente), 1, novo_arquivo);
		}
	}
	fclose(arquivoPacientes);
	if(remove("pacientes.bin")){
		return 0;
	}
	fclose(novo_arquivo);
	if(rename("temp.bin", "pacientes.bin")){
		return 0;
	}
	free(temp);
	inicializarPacientes();
	return 1;
}

//Apagar paciente pelo nome (faz o mesmo da anterior, mas busca o paciente pelo nome como parametro)
int apagarPacientePeloNome(char* nome){
	st_paciente *temp = (st_paciente*) malloc(sizeof(st_paciente));
	if(temp == NULL){
		return 0;
	}
	rewind(arquivoPacientes);
	for(int i=0; i<qtd_pacientes; i++){
		fread(temp, sizeof(st_paciente), 1, arquivoPacientes);
		if(verificaPaciente(temp->codigo) && strcmp(temp->nome, nome) == 0){
			free(temp);
			return 0;
		}
	}
	FILE *novo_arquivo;
	novo_arquivo = fopen("temp.bin", "w+b");
	if(novo_arquivo == NULL){
		free(temp);
		return 0;
	}
	rewind(arquivoPacientes);
	for(int i=0; i<qtd_pacientes; i++){
		fread(temp, sizeof(st_paciente), 1, arquivoPacientes);
		if(strcmp(temp->nome, nome) != 0){
			fwrite(temp, sizeof(st_paciente), 1, novo_arquivo);
		}
	}
	fclose(arquivoPacientes);
	if(remove("pacientes.bin")){
		return 0;
	}
	fclose(novo_arquivo);
	if(rename("temp.bin", "pacientes.bin")){
		return 0;
	}
	free(temp);
	inicializarPacientes();
	return 1;
}

