#include "pocao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratamentos.h"

int max_pocoes = 5;
int qtd_pocoes = 2;
st_pocao *pocao = NULL;

//Inicialiar o array de poçoes
int inicializarPocoes(){

	pocao = (st_pocao*) malloc(max_pocoes*sizeof(st_pocao));
	
	if(pocao == NULL){
		return 0;
	}
	pocao[0].codigo = 1;
	strcpy(pocao[0].nome, "Paracetamol");
	pocao[0].tipo = 'c';
	
	pocao[1].codigo = 22;
	strcpy(pocao[1].nome, "Ibuprofeno");
	pocao[1].tipo = 'l';

	return 1;
}

//Encerrar o array de poçoes
int EncerraPocoes(){
	free(pocao);
	return 1;
}

//Salvar uma nova poçao no array e aumentar o tamanho do array se necessário
int salvarPocao(st_pocao nova_pocao){	
	if(qtd_pocoes==max_pocoes){
		max_pocoes += 5;
		st_pocao* temp_pocao;
		temp_pocao = (st_pocao*) realloc(pocao, max_pocoes*sizeof(st_pocao));
		if(temp_pocao == NULL){
			max_pocoes -=5;
			return 0;
		}
		pocao = temp_pocao;
	}
	pocao[qtd_pocoes] = nova_pocao;
	qtd_pocoes++;
	return 1;
}

//Retornar a quantidade de pocaos
int QuantidadePocoes(){
	return qtd_pocoes;
}

//Retorna um pocao de acordo com o indice
st_pocao* obterPocaoPeloIndice(int indice){
	if(indice<0 || indice>=qtd_pocoes){
		return NULL;
	}
	st_pocao* p = (st_pocao*) malloc(sizeof(st_pocao));
	if(p==NULL){
		return NULL;
	}
	*p = pocao[indice];
	return p;	
}

//Retorna um pocao de acordo com o codigo
st_pocao* obterPocaoPeloCodigo(int codigo){
	int i;
	st_pocao* p = (st_pocao*) malloc(sizeof(st_pocao));
	if(p == NULL){
		return NULL;
	}
	for(i=0; i<qtd_pocoes; i++){
		if(pocao[i].codigo == codigo){
			*p = pocao[i];
			return p;
		}
	}
	return NULL;
}

//Altera o conteúdo da struct de um pocao
int atualizarPocao(st_pocao p){
	int i;
	for(i=0; i<qtd_pocoes; i++){
		if(pocao[i].codigo == p.codigo){
			pocao[i] = p;
			return 1;
		}
	}
	return 0;
}


//Apagar pocao pelo codigo (puxa o ultimo para a posição do que será apagado, e apaga o ultimo)
int apagarPocaoPeloCodigo(int codigo){
	if(qtd_pocoes <= (0.4*max_pocoes)){
		int temp;
		if(qtd_pocoes%5 == 0){
			temp = qtd_pocoes+5;
		}
		else{
			temp = qtd_pocoes;
			while(temp%5 != 0){
				temp++;
			}
		}
		st_pocao* temp_pocao;
		temp_pocao = (st_pocao*) realloc(pocao, temp*sizeof(st_pocao));
		if(temp_pocao == NULL){
			return 0;
		}
		max_pocoes = temp;
		pocao = temp_pocao;
	}
	int i;
	for(i=0; i<qtd_pocoes; i++){
		if(pocao[i].codigo == codigo){
			if(verificaPocao(codigo)){
				return 0;
			}
			pocao[i] = pocao[qtd_pocoes-1];
			qtd_pocoes--;
			return 1;
		}
	}
	return 0;
}

//Apagar pocao pelo nome (faz o mesmo da anterior, mas busca o pocao pelo nome como parametro)
int apagarPocaoPeloNome(char* nome){
	if(qtd_pocoes <= (0.4*max_pocoes)){
		int temp;
		if(qtd_pocoes%5 == 0){
			temp = qtd_pocoes+5;
		}
		else{
			temp = qtd_pocoes;
			while(temp%5 != 0){
				temp++;
			}
		}
		st_pocao* temp_pocao;
		temp_pocao = (st_pocao*) realloc(pocao, temp*sizeof(st_pocao));
		if(temp_pocao == NULL){
			return 0;
		}
		max_pocoes = temp;
		pocao = temp_pocao;
	}
	int i;
	for(i=0;i<qtd_pocoes;i++){
		if(strcmp(nome, pocao[i].nome)==0){
			if(verificaPocao(pocao[i].codigo)){
				return 0;
			}
			pocao[i] = pocao[qtd_pocoes-1];
			qtd_pocoes--;
			return 1;
		}
	}
	return 0;
}



