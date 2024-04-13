#include "tratamentos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bruxo.h"
#include "pocao.h"
#include "paciente.h"

int max_tratamentos = 5;
int qtd_tratamentos = 0;
st_tratamento* tratamento = NULL;


//Inicialiar o array de tratamentos
int inicializarTratamentos(){
	
	tratamento = (st_tratamento*) malloc(max_tratamentos*sizeof(st_tratamento));
	
	if(tratamento == NULL){
		return 0;
	}
	
	return 1;
}

//Encerrar o array de tratamentos
int EncerraTratamentos(){
	free(tratamento);
	return 1;
}


//Inserir um novo tratamento no array de tratamentos
int iniciarTratamento(st_tratamento novo_tratamento){
	if(qtd_tratamentos==max_tratamentos){
		max_tratamentos += 5;
		st_tratamento* temp_tratamento;
		temp_tratamento = (st_tratamento*) realloc (tratamento, max_tratamentos*sizeof(st_tratamento));
		if(tratamento == NULL){
			max_tratamentos -= 5;
			return 0;
		}
		tratamento = temp_tratamento;
	}
	tratamento[qtd_tratamentos] = novo_tratamento;
	tratamento[qtd_tratamentos].codigo = qtd_tratamentos+1;
	qtd_tratamentos++;
	return 1;
}



//Verificações de ocorrência no array de tratamentos
int verificaBruxo(int cod_bruxo){
	int i;
	for(i=0; i<qtd_tratamentos;i++){
		if(tratamento[i].codigo_bruxo == cod_bruxo){
			return 1;
		}
	}
	return 0;
}

int verificaPaciente(int cod_paciente){
	int i;
	for(i=0; i<qtd_tratamentos;i++){
		if(tratamento[i].codigo_paciente == cod_paciente){
			return 1;
		}
	}
	return 0;
}

int verificaPocao(int cod_pocao){
	int i;
	for(i=0; i<qtd_tratamentos;i++){
		if(tratamento[i].codigo_pocao == cod_pocao){
			return 1;
		}
	}
	return 0;
}

//Retorna quantidade de tratamentos
int quantidadeTratamentos(){
	return qtd_tratamentos;
}

//Retorna um tratamento pelo indice do array
st_tratamento* obterTratamentoPeloIndice(int indice){
	st_tratamento* t = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(t == NULL){
		return NULL;
	}
	*t = tratamento[indice];
	return t;
}

//Retorna um tratamento pelo código do tratamento
st_tratamento* obterTratamentoPeloCodigo(int codigo){
	int i;
	st_tratamento* t = (st_tratamento*) malloc (sizeof(st_tratamento));
	if(t==NULL){
		return NULL;
	}
	for(i=0; i<qtd_tratamentos; i++){
		if(tratamento[i].codigo == codigo){
			*t = tratamento[i];
			return t;
		}
	}
	return NULL;
}

//Altera os valores de um tratamento sem alterar o codigo
int ampliarTratamento(st_tratamento novo_tratamento){
	int i;
	for(i=0;i<qtd_tratamentos;i++){
		if(novo_tratamento.codigo == tratamento[i].codigo){
			tratamento[i] = novo_tratamento;
			return 1;
		}
	}
	return 0;
}

//Exclui um tratamento pelo codigo do tratamento
int excluirTratamento(int codigo){
	if(qtd_tratamentos <= 0.4*max_tratamentos){
		int temp;
		if(qtd_tratamentos%5==0){
			temp = qtd_tratamentos+5;
		}
		else{
			temp = qtd_tratamentos;
			while(temp%5 != 0){
				temp++;
			}
		}
		st_tratamento* temp_tratamento;
		temp_tratamento = (st_tratamento*) realloc(tratamento, temp*sizeof(st_tratamento));
		if(temp_tratamento == NULL){
			return 0;
		}
		max_tratamentos = temp;
		tratamento = temp_tratamento;
	}
	int i;
	for(i=0; i<qtd_tratamentos; i++){
		if(tratamento[i].codigo == codigo){
			tratamento[i] = tratamento[qtd_tratamentos-1];
			qtd_tratamentos--;
		}
	}
}
