#include "bruxo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratamentos.h"

int max_bruxos = 5;
int qtd_bruxos = 2;
st_bruxo *bruxo = NULL;

//Inicialiar o array de bruxos
int inicializarBruxos(){
	
	bruxo = (st_bruxo*) malloc(max_bruxos*sizeof(st_bruxo));
	
	if(bruxo == NULL){
		return 0;
	}
	bruxo[0].codigo = 1;
	strcpy(bruxo[0].nome, "Daniel");
	strcpy(bruxo[0].especialidade, "Cirurgiao");
	
	bruxo[1].codigo = 22;
	strcpy(bruxo[1].nome, "Ze");
	strcpy(bruxo[1].especialidade, "Seila");
	
	return 1;
}

//Encerrar o array de bruxos
int EncerraBruxos(){
	free(bruxo);
	return 1;
}

//Salvar um novo bruxo no array e aumentar o tamanho do array se necessário
int salvarBruxo(st_bruxo novo){	
	if(qtd_bruxos==max_bruxos){
		max_bruxos += 5;
		st_bruxo* temp_bruxo;
		temp_bruxo = (st_bruxo*) realloc(bruxo, max_bruxos*sizeof(st_bruxo));
		if(temp_bruxo == NULL){
			max_bruxos -= 5;
			return 0;
		}
		bruxo = temp_bruxo;
	}
	bruxo[qtd_bruxos] = novo;
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
	st_bruxo* b = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(b==NULL){
		return NULL;
	}
	*b = bruxo[indice];
	return b;	
}

//Retorna um bruxo de acordo com o codigo
st_bruxo* obterBruxoPeloCodigo(int codigo){
	int i;
	st_bruxo* b = (st_bruxo*) malloc(sizeof(st_bruxo));
	if(b == NULL){
		return NULL;
	}
	for(i=0; i<qtd_bruxos; i++){
		if(bruxo[i].codigo == codigo){
			*b = bruxo[i];
			return b;
		}
	}
	return NULL;
}

//Altera o conteúdo da struct de um Bruxo
int atualizarBruxo(st_bruxo b){
	int i;
	for(i=0; i<qtd_bruxos; i++){
		if(bruxo[i].codigo == b.codigo){
			bruxo[i] = b;
			return 1;
		}
	}
	return 0;
}


//Apagar bruxo pelo codigo (puxa o ultimo para a posição do que será apagado, e apaga o ultimo)
int apagarBruxoPeloCodigo(int codigo){
	if(qtd_bruxos <= (0.4*max_bruxos)){
		int temp;
		if(qtd_bruxos%5 == 0){
			temp = qtd_bruxos+5;
		}
		else{
			temp = qtd_bruxos;
			while(temp%5 != 0){
				temp++;
			}
		}
		st_bruxo* temp_bruxo;
		temp_bruxo = (st_bruxo*) realloc(bruxo, temp*sizeof(st_bruxo));
		if(temp_bruxo  == NULL){
			return 0;
		}
		max_bruxos = temp;
		bruxo = temp_bruxo;
	}
	int i;
	for(i=0; i<qtd_bruxos; i++){
		if(bruxo[i].codigo == codigo){
			if(verificaBruxo(codigo)){
				return 0;
			}
			bruxo[i] = bruxo[qtd_bruxos-1];
			qtd_bruxos--;
			return 1;
		}
	}
	return 0;
}

//Apagar bruxo pelo nome (faz o mesmo da anterior, mas busca o bruxo pelo nome como parametro)
int apagarBruxoPeloNome(char* nome){
	if(qtd_bruxos <= (0.4*max_bruxos)){
		int temp;
		if(qtd_bruxos%5 == 0){
			temp = qtd_bruxos+5;
		}
		else{
			temp = qtd_bruxos;
			while(temp%5 != 0){
				temp++;
			}
		}
		st_bruxo* temp_bruxo;
		temp_bruxo = (st_bruxo*) realloc(bruxo, temp*sizeof(st_bruxo));
		if(temp_bruxo  == NULL){
			return 0;
		}
		max_bruxos = temp;
		bruxo = temp_bruxo;
	}
	int i;
	for(i=0;i<qtd_bruxos;i++){
		if(strcmp(nome, bruxo[i].nome)==0){
			if(verificaBruxo(bruxo[i].codigo)){
				return 0;
			}
			bruxo[i] = bruxo[qtd_bruxos-1];
			qtd_bruxos--;
			return 1;
		}
	}
	return 0;
}

