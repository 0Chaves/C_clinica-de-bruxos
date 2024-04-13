#include "tratamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bruxo.h"
#include "pocao.h"
#include "paciente.h"

int qtd_tratamentos = 0;
FILE *arquivoTratamentos;


//Inicialiar o array de tratamentos
int inicializarTratamentos(){
	if((arquivoTratamentos = fopen("tratamentos.bin", "r+b")) == NULL){
		arquivoTratamentos = fopen("tratamentos.bin", "w+b");
	}
	if(arquivoTratamentos == NULL){
		return 0;
	}
	fseek(arquivoTratamentos, 0, SEEK_END);
	qtd_tratamentos = ftell(arquivoTratamentos)/sizeof(st_tratamento);
	return 1;
}

//Encerrar o array de tratamentos
int EncerraTratamentos(){
	fclose(arquivoTratamentos);
	return 1;
}


//Inserir um novo tratamento no array de tratamentos
int iniciarTratamento(st_tratamento novo_tratamento){
	st_tratamento *temp_tratamento = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp_tratamento == NULL){
		return 0;
	}
	*temp_tratamento = novo_tratamento;
	temp_tratamento->codigo = qtd_tratamentos;
	fseek(arquivoTratamentos, 0, SEEK_END);
	fwrite(temp_tratamento, sizeof(st_tratamento), 1, arquivoTratamentos);
	free(temp_tratamento);
	qtd_tratamentos++;
	return 1;
}



//Verificações de ocorrência no array de tratamentos
int verificaBruxo(int cod_bruxo){
	int i;
	st_tratamento *temp = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp == NULL){
		return 1;
		//pensar em outra forma de escrever esse return;
	}
	rewind(arquivoTratamentos);
	for(i=0; i<qtd_tratamentos;i++){
		fread(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
		if(temp->codigo_bruxo == cod_bruxo){
			free(temp);
			return 1;
		}
	}
	free(temp);
	return 0;
}

int verificaPaciente(int cod_paciente){
	int i;
	st_tratamento *temp = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp == NULL){
		return 1;
		//pensar em outra forma de escrever esse return;
	}
	rewind(arquivoTratamentos);
	for(i=0; i<qtd_tratamentos;i++){
		fread(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
		if(temp->codigo_paciente == cod_paciente){
			free(temp);
			return 1;
		}
	}
	free(temp);
	return 0;
}

int verificaPocao(int cod_pocao){
	int i;
	st_tratamento *temp = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp == NULL){
		return 1;
		//pensar em outra forma de escrever esse return;
	}
	rewind(arquivoTratamentos);
	for(i=0; i<qtd_tratamentos;i++){
		fread(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
		if(temp->codigo_pocao == cod_pocao){
			free(temp);
			return 1;
		}
	}
	free(temp);
	return 0;
}

//Retorna quantidade de tratamentos
int quantidadeTratamentos(){
	return qtd_tratamentos;
}

//Retorna um tratamento pelo indice do array
st_tratamento* obterTratamentoPeloIndice(int indice){
	st_tratamento* temp = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp == NULL){
		return NULL;
	}
	fseek(arquivoTratamentos, indice*sizeof(st_tratamento), SEEK_SET);
	fread(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
	return temp;
}

//Retorna um tratamento pelo código do tratamento
st_tratamento* obterTratamentoPeloCodigo(int codigo){
	int i;
	st_tratamento* temp = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp==NULL){
		return NULL;
	}
	rewind(arquivoTratamentos);
	for(i=0; i<qtd_tratamentos; i++){
		fread(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
		if(temp->codigo == codigo){
			return temp;
		}
	}
	free(temp);
	return NULL;
}

//Busca um tratamento pelo codigo e Altera seus outros valores
int ampliarTratamento(st_tratamento novo_tratamento){
	int i;
	st_tratamento *temp = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp == NULL){
		return 0;
	}
	rewind(arquivoTratamentos);
	for(i=0;i<qtd_tratamentos;i++){
		fread(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
		if(temp->codigo == novo_tratamento.codigo){
			*temp = novo_tratamento;
			fseek(arquivoTratamentos, -1*sizeof(st_tratamento), SEEK_CUR);
			fwrite(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
			free(temp);
			return 1;
		}
	}
	free(temp);
	return 0;
}

//Exclui um tratamento pelo codigo do tratamento
int excluirTratamento(int codigo){
	st_tratamento *temp = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(temp == NULL){
		return 0;
	}
	FILE *arquivo_temp = fopen("temp.bin", "wb");
	if(arquivo_temp == NULL){
		free(temp);
		return 0;
	}
	int i;
	rewind(arquivoTratamentos);
	for(i=0; i<qtd_tratamentos; i++){
		fread(temp, sizeof(st_tratamento), 1, arquivoTratamentos);
		if(temp->codigo != codigo){
			temp->codigo = i;
			fwrite(temp, sizeof(st_tratamento), 1, arquivo_temp);
		}
	}
	fclose(arquivoTratamentos);
	if(remove("tratamentos.bin")){
		return 0;
	}
	fclose(arquivo_temp);
	if(rename("temp.bin", "tratamentos.bin")){
		return 0;
	}
	free(temp);
	inicializarTratamentos();
	return 1;
}
