#include "bruxo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratamentos.h"

int qtd_bruxos = 0;
FILE *arquivoBruxos;

//Abre o arquivo de bruxos
int inicializarBruxos(){
	if((arquivoBruxos = fopen("bruxos.bin", "r+b")) == NULL){
		arquivoBruxos = fopen("bruxos.bin", "w+b");
		
	}
	if(arquivoBruxos == NULL){
		return 0;
	}
	
	fseek(arquivoBruxos, 0, SEEK_END);
	qtd_bruxos = ftell(arquivoBruxos)/sizeof(st_bruxo);
	return 1;
}

//Fecha o arquivo de bruxos
int EncerraBruxos(){
	fclose(arquivoBruxos);
	return 1;
}

//Salvar um novo bruxo no arquivo
int salvarBruxo(st_bruxo novo){
	st_bruxo *temp_bruxo;
	temp_bruxo = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(temp_bruxo == NULL){
			return 0;
		}
	*temp_bruxo = novo;
	fseek(arquivoBruxos, 0, SEEK_END);
	fwrite(temp_bruxo, sizeof(st_bruxo), 1, arquivoBruxos);
	free(temp_bruxo);
	qtd_bruxos++;
	return 1;
}

//Retornar a quantidade de bruxos
int QuantidadeBruxos(){
	return qtd_bruxos;
}

//Retorna um bruxo de acordo com o indice
st_bruxo* obterBruxoPeloIndice(int indice){
	if(indice<0 || indice>=qtd_bruxos){
		return NULL;
	}
	st_bruxo* bruxo = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(bruxo==NULL){
		return NULL;
	}
	fseek(arquivoBruxos, indice*sizeof(st_bruxo), SEEK_SET);
	fread(bruxo, sizeof(st_bruxo), 1, arquivoBruxos);
	return bruxo;
}

//Retorna um bruxo de acordo com o codigo
st_bruxo* obterBruxoPeloCodigo(int codigo){
	int i;
	st_bruxo *bruxo = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(bruxo == NULL){
		return NULL;
	}
	rewind(arquivoBruxos);
	for(i=0; i<qtd_bruxos; i++){
		fread(bruxo, sizeof(st_bruxo), 1, arquivoBruxos);
		if(bruxo->codigo == codigo){
			return bruxo;
		}
	}
	free(bruxo);
	return NULL;
}

//Altera o conteúdo da struct de um Bruxo
int atualizarBruxo(st_bruxo bruxo_novo){
	int i;
	st_bruxo *temp = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(temp == NULL){
		return 0;
	}
	rewind(arquivoBruxos);
	for(i=0; i<qtd_bruxos; i++){
		fread(temp, sizeof(st_bruxo), 1, arquivoBruxos);
		if(temp->codigo == bruxo_novo.codigo){
			*temp = bruxo_novo;
			fseek(arquivoBruxos, -1*sizeof(st_bruxo), SEEK_CUR);
			fwrite(temp, sizeof(st_bruxo), 1, arquivoBruxos);
			free(temp);
			return 1;
		}
	}
	free(temp);
	return 0;
}


//Apagar bruxo pelo codigo (cria um novo arquivo, copiando todos os dados exceto aquele que possuir o codigo a ser deletado)
int apagarBruxoPeloCodigo(int codigo){
	if(verificaBruxo(codigo)){
		return 0;
	}
	st_bruxo *temp = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(temp == NULL){
		return 0;
	}
	FILE *novo_arquivo;
	novo_arquivo = fopen("temp.bin", "w+b");
	if(novo_arquivo == NULL){
		free(temp);
		return 0;
	}
	rewind(arquivoBruxos);
	int i;
	for(i=0; i<qtd_bruxos; i++){
		fread(temp, sizeof(st_bruxo), 1, arquivoBruxos);
		if(temp->codigo != codigo){
			fwrite(temp, sizeof(st_bruxo), 1, novo_arquivo);
		}
	}
	fclose(arquivoBruxos);
	if(remove("bruxos.bin")){
		return 0;
	}
	fclose(novo_arquivo);
	if(rename("temp.bin", "bruxos.bin")){
		return 0;
	}
	free(temp);
	inicializarBruxos();
	return 1;
}

//Apagar bruxo pelo nome (faz o mesmo da anterior, mas busca o bruxo pelo nome como parametro)
int apagarBruxoPeloNome(char* nome){
	st_bruxo *temp = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(temp == NULL){
		return 0;
	}
	int i;
	rewind(arquivoBruxos);
	for(i=0; i<qtd_bruxos; i++){
		fread(temp, sizeof(st_bruxo), 1, arquivoBruxos);
		if(verificaBruxo(temp->codigo) && strcmp(temp->nome, nome) == 0){
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
	rewind(arquivoBruxos);
	for(i=0; i<qtd_bruxos; i++){
		fread(temp, sizeof(st_bruxo), 1, arquivoBruxos);
		if(strcmp(temp->nome, nome) != 0){
			fwrite(temp, sizeof(st_bruxo), 1, novo_arquivo);
		}
	}
	fclose(arquivoBruxos);
	if(remove("bruxos.bin")){
		return 0;
	}
	fclose(novo_arquivo);
	if(rename("temp.bin", "bruxos.bin")){
		return 0;
	}
	free(temp);
	inicializarBruxos();
	return 1;
}

