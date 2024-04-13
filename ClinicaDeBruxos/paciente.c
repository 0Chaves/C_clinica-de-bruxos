#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tratamentos.h"

int max_pacientes = 5;
int qtd_pacientes = 2;
st_paciente *paciente = NULL;

//Inicialiar o array de pacientes
int inicializarPacientes(){
	
	paciente = (st_paciente*) malloc(max_pacientes*sizeof(st_paciente));
	
	if(paciente == NULL){
		return 0;
	}
	
	paciente[0].codigo = 1;
	strcpy(paciente[0].nome, "PG");
	paciente[0].idade = 15;
	paciente[0].altura = 4.15;
	
	paciente[1].codigo = 22;
	strcpy(paciente[1].nome, "Jubileu");
	paciente[1].idade = 222;
	paciente[1].altura = 155.15;
	
	
	return 1;
}

//Encerrar o array de pacientes
int EncerraPacientes(){
	free(paciente);
	return 1;
}

//Salvar um novo paciente no array e aumentar o tamanho do array se necessário
int salvarPaciente(st_paciente novo_paciente){	
	if(qtd_pacientes==max_pacientes){
		max_pacientes += 5;
		st_paciente* temp_paciente;
		temp_paciente = (st_paciente*) realloc(paciente, max_pacientes*sizeof(st_paciente));
		if(temp_paciente == NULL){
			max_pacientes -= 5;
			return 0;
		}
		paciente = temp_paciente;
	}
	paciente[qtd_pacientes] = novo_paciente;
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
	st_paciente* c = (st_paciente*) malloc(sizeof(st_paciente));
	if(c==NULL){
		return NULL;
	}
	*c = paciente[indice];
	return c;	
}

//Retorna um paciente de acordo com o codigo
st_paciente* obterPacientePeloCodigo(int codigo){
	int i;
	st_paciente* c = (st_paciente*) malloc(sizeof(st_paciente));
	if(c == NULL){
		return NULL;
	}
	for(i=0; i<qtd_pacientes; i++){
		if(paciente[i].codigo == codigo){
			*c = paciente[i];
			return c;
		}
	}
	return NULL;
}

//Altera o conteúdo da struct de um paciente
int atualizarPaciente(st_paciente c){
	int i;
	for(i=0; i<qtd_pacientes; i++){
		if(paciente[i].codigo == c.codigo){
			paciente[i] = c;
			return 1;
		}
	}
	return 0;
}


//Apagar paciente pelo codigo (puxa o ultimo para a posição do que será apagado, e apaga o ultimo)
int apagarPacientePeloCodigo(int codigo){
	if(qtd_pacientes <= (0.4*max_pacientes)){
		int temp;
		if(qtd_pacientes%5 == 0){
			temp = qtd_pacientes+5;
		}
		else{
			temp = qtd_pacientes;
			while(temp%5 != 0){
				temp++;
			}
		}
		st_paciente* temp_paciente;
		temp_paciente = (st_paciente*) realloc(paciente, temp*sizeof(st_paciente));
		if(temp_paciente == NULL){
			return 0;
		}
		max_pacientes = temp;
		paciente = temp_paciente;
	}
	
	int i;
	for(i=0; i<qtd_pacientes; i++){
		if(paciente[i].codigo == codigo){
			if(verificaPaciente(codigo)){
				return 0;
			}
			paciente[i] = paciente[qtd_pacientes-1];
			qtd_pacientes--;
			return 1;
		}
	}
	return 0;
}

//Apagar paciente pelo nome (faz o mesmo da anterior, mas busca o paciente pelo nome como parametro)
int apagarPacientePeloNome(char* nome){
	if(qtd_pacientes <= (0.4*max_pacientes)){
		int temp;
		if(qtd_pacientes%5 == 0){
			temp = qtd_pacientes+5;
		}
		else{
			temp = qtd_pacientes;
			while(temp%5 != 0){
				temp++;
			}
		}
		st_paciente* temp_paciente;
		temp_paciente = (st_paciente*) realloc(paciente, temp*sizeof(st_paciente));
		if(temp_paciente == NULL){
			return 0;
		}
		max_pacientes = temp;
		paciente = temp_paciente;
	}
	int i;
	for(i=0;i<qtd_pacientes;i++){
		if(strcmp(nome, paciente[i].nome)==0){
			if(verificaPaciente(paciente[i].codigo)){
				return 0;
			}
			paciente[i] = paciente[qtd_pacientes-1];
			qtd_pacientes--;
			return 1;
		}
	}
	return 0;
}

