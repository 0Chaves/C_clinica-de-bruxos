#include "pocao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratamentos.h"

int qtd_pocoes = 0;
FILE *arquivoPocoes;

//Abre o arquivo de pocoes
int inicializarPocoes(){
	if((arquivoPocoes = fopen("pocoes.bin", "r+b")) == NULL){
		arquivoPocoes = fopen("pocoes.bin", "w+b");
		
	}
	if(arquivoPocoes == NULL){
		return 0;
	}
	
	fseek(arquivoPocoes, 0, SEEK_END);
	qtd_pocoes = ftell(arquivoPocoes)/sizeof(st_pocao);
	return 1;
}

//Fecha o arquivo de pocoes
int EncerraPocoes(){
	fclose(arquivoPocoes);
	return 1;
}

//Salvar um novo pocao no arquivo
int salvarPocao(st_pocao novo){
	st_pocao *temp_pocao;
	temp_pocao = (st_pocao*) malloc(sizeof(st_pocao));
	if(temp_pocao == NULL){
			return 0;
		}
	*temp_pocao = novo;
	fseek(arquivoPocoes, 0, SEEK_END);
	fwrite(temp_pocao, sizeof(st_pocao), 1, arquivoPocoes);
	free(temp_pocao);
	qtd_pocoes++;
	return 1;
}

//Retornar a quantidade de pocoes
int QuantidadePocoes(){
	return qtd_pocoes;
}

//Retorna um pocao de acordo com o indice
st_pocao* obterPocaoPeloIndice(int indice){
	if(indice<0 || indice>=qtd_pocoes){
		return NULL;
	}
	st_pocao* pocao = (st_pocao*) malloc(sizeof(st_pocao));
	if(pocao==NULL){
		return NULL;
	}
	fseek(arquivoPocoes, indice*sizeof(st_pocao), SEEK_SET);
	fread(pocao, sizeof(st_pocao), 1, arquivoPocoes);
	return pocao;
}

//Retorna um pocao de acordo com o codigo
st_pocao* obterPocaoPeloCodigo(int codigo){
	int i;
	st_pocao *pocao = (st_pocao*) malloc(sizeof(st_pocao));
	if(pocao == NULL){
		return NULL;
	}
	rewind(arquivoPocoes);
	for(i=0; i<qtd_pocoes; i++){
		fread(pocao, sizeof(st_pocao), 1, arquivoPocoes);
		if(pocao->codigo == codigo){
			return pocao;
		}
	}
	free(pocao);
	return NULL;
}

//Altera o conteúdo da struct de um Pocao
int atualizarPocao(st_pocao pocao_novo){
	int i;
	st_pocao *temp = (st_pocao*) malloc(sizeof(st_pocao));
	if(temp == NULL){
		return 0;
	}
	rewind(arquivoPocoes);
	for(i=0; i<qtd_pocoes; i++){
		fread(temp, sizeof(st_pocao), 1, arquivoPocoes);
		if(temp->codigo == pocao_novo.codigo){
			*temp = pocao_novo;
			fseek(arquivoPocoes, -1*sizeof(st_pocao), SEEK_CUR);
			fwrite(temp, sizeof(st_pocao), 1, arquivoPocoes);
			free(temp);
			return 1;
		}
	}
	free(temp);
	return 0;
}


//Apagar pocao pelo codigo (cria um novo arquivo, copiando todos os dados exceto aquele que possuir o codigo a ser deletado)
int apagarPocaoPeloCodigo(int codigo){
	if(verificaPocao(codigo)){
		return 0;
	}
	st_pocao *temp = (st_pocao*) malloc(sizeof(st_pocao));
	if(temp == NULL){
		return 0;
	}
	FILE *novo_arquivo;
	novo_arquivo = fopen("temp.bin", "w+b");
	if(novo_arquivo == NULL){
		free(temp);
		return 0;
	}
	rewind(arquivoPocoes);
	int i;
	for(i=0; i<qtd_pocoes; i++){
		fread(temp, sizeof(st_pocao), 1, arquivoPocoes);
		if(temp->codigo != codigo){
			fwrite(temp, sizeof(st_pocao), 1, novo_arquivo);
		}
	}
	fclose(arquivoPocoes);
	if(remove("pocoes.bin")){
		return 0;
	}
	fclose(novo_arquivo);
	if(rename("temp.bin", "pocoes.bin")){
		return 0;
	}
	free(temp);
	inicializarPocoes();
	return 1;
}

//Apagar pocao pelo nome (faz o mesmo da anterior, mas busca o pocao pelo nome como parametro)
int apagarPocaoPeloNome(char* nome){
	st_pocao *temp = (st_pocao*) malloc(sizeof(st_pocao));
	if(temp == NULL){
		return 0;
	}
	int i;
	rewind(arquivoPocoes);
	for(i=0; i<qtd_pocoes; i++){
		fread(temp, sizeof(st_pocao), 1, arquivoPocoes);
		if(verificaPocao(temp->codigo) && strcmp(temp->nome, nome) == 0){
			free(temp);
			return 0;
		}
	}
	FILE *novo_arquivo;
	novo_arquivo = fopen("temp.bin", "wb");
	if(novo_arquivo == NULL){
		free(temp);
		return 0;
	}
	rewind(arquivoPocoes);
	for(i=0; i<qtd_pocoes; i++){
		fread(temp, sizeof(st_pocao), 1, arquivoPocoes);
		if(strcmp(temp->nome, nome) != 0){
			fwrite(temp, sizeof(st_pocao), 1, novo_arquivo);
		}
	}
	fclose(arquivoPocoes);
	if(remove("pocoes.bin")){
		return 0;
	}
	fclose(novo_arquivo);
	if(rename("temp.bin", "pocoes.bin")){
		return 0;
	}
	free(temp);
	inicializarPocoes();
	return 1;
}

