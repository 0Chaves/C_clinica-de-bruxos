#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "bruxo.h"
#include "pocao.h"
#include "paciente.h"
#include "tratamentos.h"

int main(int argc, char *argv[]) {
	if(inicializarBruxos()==0 || inicializarPocoes()==0 || inicializarPacientes()==0 || inicializarTratamentos()==0)
	{
		printf("Falha ao inicializar a memoria!");
		return 0;
	}
	
	int opcao_menu, opcao_submenu, opcao_tratamento, cod_bruxo, cod_pocao, cod_paciente, cod_tratamento;
	char nome[30];
	st_bruxo novo;
	st_pocao nova_pocao;
	st_paciente novo_paciente;
	st_tratamento novo_tratamento;
	do{
		opcao_menu = menu();
		if(validarOpcao(opcao_menu, 0, 4))
		{
			switch(opcao_menu)
			{
				case 1:{
					do{
						opcao_submenu = submenu();
						if(validarOpcao(opcao_submenu, 0, 4)){
							switch(opcao_submenu)
							{
								case 1:{
									printf("\n-------Lista de Bruxos-------\n");
									for(int i =0; i<QuantidadeBruxos(); i++){
										st_bruxo* b = obterBruxoPeloIndice(i);
										printf("Codigo: %d\n", b->codigo);
										printf("Nome: %s\n", b->nome);
										printf("Especialidade: %s\n\n", b->especialidade);
										free(b);
									}	
									break;
								}
								case 2:{
									printf("Digite o codigo: ");
									scanf("%d", &novo.codigo);
									printf("Digite o nome: ");
									scanf(" %s", novo.nome);
									printf("Digite a especialidade: ");
									scanf(" %s", novo.especialidade);
									if(salvarBruxo(novo)){
										printf("Bruxo salvo com sucesso.\n");
									}
									else{
										printf("Erro ao salvar Bruxo.\n");
									}
									break;
								}
								case 3:{
									printf("Digite o codigo do bruxo: ");
									scanf("%d", &cod_bruxo);
									st_bruxo* b = obterBruxoPeloCodigo(cod_bruxo);
									if(b != NULL){
										printf("Quer alterar o nome do bruxo? 1-Sim 2-Nao\n");
										scanf("%d", &opcao_submenu);
										if(opcao_submenu == 1){
											printf("Digite o novo nome: ");
											scanf(" %s", b->nome);
										}
										printf("Quer alterar a especialidade do bruxo? 1-Sim 2-Nao\n");
										scanf("%d", &opcao_submenu);
										if(opcao_submenu == 1){
											printf("Digite a nova especialidade: ");
											scanf(" %s", b->especialidade);	
										}
										novo = *b;
										if(atualizarBruxo(novo)){
											printf("Bruxo alterado com sucesso!\n");
										}
										else{
											printf("A alteração fracassou com sucesso!\n");
										}
									}
									else{
										printf("Codigo invalido!\n");
									}
									free(b);
									break;
								}
								case 4:{
									printf("Deseja apagar o bruxo por: \n");
									printf("1. Codigo\n");
									printf("2. Nome\n");
									scanf("%d", &opcao_submenu);
									if(validarOpcao (opcao_submenu, 1, 2)){
										switch(opcao_submenu){
											case 1:{
												printf("Digite o codigo do bruxo: ");
												scanf("%d", &cod_bruxo);
												if(apagarBruxoPeloCodigo(cod_bruxo)){
													printf("Bruxo apagado!\n");
												}
												else{
													printf("Erro ao apagar!\n");
												}
												break;
											}
											case 2:{
												printf("Digite o nome do bruxo: ");
												scanf(" %s", nome);
												if(apagarBruxoPeloNome(nome)){
													printf("Bruxo apagado!");
												}
												else{
													printf("Erro ao apagar!\n");
												}
												break;
											}
										}
									}
									break;
								}
								
							}	
						}
					}while(opcao_submenu != 0);
					break;
				}
				case 2:{
					do{
						opcao_submenu = submenu();
						if(validarOpcao(opcao_submenu, 0, 4)){
							switch(opcao_submenu)
							{
								case 1:{
									printf("\n-------Lista de Pacientes-------\n");
									for(int i =0; i<QuantidadePacientes(); i++){
										st_paciente* c = obterPacientePeloIndice(i);
										printf("Codigo: %d\n", c->codigo);
										printf("Nome: %s\n", c->nome);
										printf("Idade: %d\n", c->idade);
										printf("Altura: %.2f\n\n", c->altura);
										free(c);
									}
									break;
								}
								case 2:{
									printf("Digite o codigo: ");
									scanf("%d", &novo_paciente.codigo);
									printf("Digite o nome: ");
									scanf(" %s", novo_paciente.nome);
									printf("Digite a idade: ");
									scanf("%d", &novo_paciente.idade);
									printf("Digite a altura: ");
									scanf("%f", &novo_paciente.altura);
									if(salvarPaciente(novo_paciente)){
										printf("Paciente salvo com sucesso.\n");
									}
									else{
										printf("Erro ao salvar Paciente.\n");
									}
									break;
								}
								case 3:{
									printf("Digite o codigo do paciente: ");
									scanf("%d", &cod_paciente);
									//Perguntar se essa declaração gera problemas por estar no meio do codigo
									st_paciente* c = obterPacientePeloCodigo(cod_paciente);
									if(c != NULL){
										printf("Quer alterar o nome do paciente? 1-Sim 2-Nao\n");
										scanf("%d", &opcao_submenu);
										if(opcao_submenu == 1){
											printf("Digite o novo nome: ");
											scanf(" %s", c->nome);
										}
										printf("Quer alterar a idade do paciente? 1-Sim 2-Nao\n");
										scanf("%d", &opcao_submenu);
										if(opcao_submenu == 1){
											printf("Digite a nova idade: ");
											scanf("%d", &c->idade);	
										}
										printf("Quer alterar a altura do paciente? 1-Sim 2-Nao\n");
										scanf("%d", &opcao_submenu);
										if(opcao_submenu == 1){
											printf("Digite a nova altura: ");
											scanf("%f", &c->altura);	
										}
										novo_paciente = *c;
										if(atualizarPaciente(novo_paciente)){
											printf("Paciente alterado com sucesso!\n");
										}
										else{
											printf("A alteração fracassou com sucesso!\n");
										}
									}
									else{
										printf("Codigo invalido!\n");
									}
									free(c);
									break;
								}
								case 4:{
									printf("Deseja apagar o paciente por: \n");
									printf("1. Codigo\n");
									printf("2. Nome\n");
									scanf("%d", &opcao_submenu);
									if(validarOpcao (opcao_submenu, 1, 2)){
										switch(opcao_submenu){
											case 1:{
												printf("Digite o codigo do paciente: ");
												scanf("%d", &cod_paciente);
												if(apagarPacientePeloCodigo(cod_paciente)){
													printf("Paciente apagado!\n");
												}
												else{
													printf("Erro ao apagar!\n");
												}
												break;
											}
											case 2:{
												printf("Digite o nome do paciente: ");
												scanf(" %s", nome);
												if(apagarPacientePeloNome(nome)){
													printf("Paciente apagado!\n");
												}
												else{
													printf("Erro ao apagar!\n");
												}
												break;
											}
										}
									}
									break;
								}
							}													
						}	
					}while(opcao_submenu != 0);
					break;
				}
				case 3:{
					do{
						opcao_submenu = submenu();
						if(validarOpcao(opcao_submenu, 0, 4)){
							switch(opcao_submenu)
							{
								case 1:{
									printf("\n-------Lista de Pocoes-------\n");
									for(int i =0; i<QuantidadePocoes(); i++){
										st_pocao* p = obterPocaoPeloIndice(i);
										printf("Codigo: %d\n", p->codigo);
										printf("Nome: %s\n", p->nome);
										printf("Tipo: %c\n\n", p->tipo);
										free(p);
									}
									break;
								}
								case 2:{
									printf("Digite o codigo: ");
									scanf("%d", &nova_pocao.codigo);
									printf("Digite o nome: ");
									scanf(" %s", nova_pocao.nome);
									printf("Digite o tipo L ou C (liquido/comprimido): ");
									scanf(" %c", &nova_pocao.tipo);
									if(salvarPocao(nova_pocao)){
										printf("Pocao salva com sucesso.\n");
									}
									else{
										printf("Erro ao salvar Pocao.\n");
									}
									break;
								}
								case 3:{
									printf("Digite o codigo da pocao: ");
									scanf("%d", &cod_pocao);
									st_pocao* p = obterPocaoPeloCodigo(cod_pocao);
									if(p != NULL){
										printf("Quer alterar o nome da pocao? 1-Sim 2-Nao\n");
										scanf("%d", &opcao_submenu);
										if(opcao_submenu == 1){
											printf("Digite o novo nome: ");
											scanf(" %s", p->nome);
										}
										printf("Quer alterar o tipo? 1-Sim 2-Nao\n");
										scanf("%d", &opcao_submenu);
										if(opcao_submenu == 1){
											printf("Digite o novo tipo L ou C(Liquido/Comprimido): ");
											scanf(" %c", &p->tipo);	
										}
										nova_pocao = *p;
										if(atualizarPocao(nova_pocao)){
											printf("Pocao alterado com sucesso!\n");
										}
										else{
											printf("A alteração fracassou com sucesso!\n");
										}
									}
									else{
										printf("Codigo invalido!\n");
									}
									free(p);
									break;
								}
								case 4:{
									printf("Deseja apagar a pocao por: \n");
									printf("1. Codigo\n");
									printf("2. Nome\n");
									scanf("%d", &opcao_submenu);
									if(validarOpcao (opcao_submenu, 1, 2)){
										switch(opcao_submenu){
											case 1:{
												printf("Digite o codigo da pocao: ");
												scanf("%d", &cod_pocao);
												if(apagarPocaoPeloCodigo(cod_pocao)){
													printf("Pocao apagada!\n");
												}
												else{
													printf("Erro ao apagar!\n");
												}
												break;
											}
											case 2:{
												printf("Digite o nome da pocao: ");
												scanf(" %s", nome);
												if(apagarPocaoPeloNome(nome)){
													printf("Pocao apagada!\n");
												}
												else{
													printf("Erro ao apagar!\n");
												}
												break;
											}
										}
									}
									break;
								}
							}												
						}
					}while(opcao_submenu != 0);
					break;
				}
				case 4:{
					do{
						opcao_tratamento = submenu_tratamento();
						if(validarOpcao(opcao_tratamento, 0, 5)){
							switch(opcao_tratamento)
							{
								case 1:{
									printf("Digite o codigo do paciente: ");
									scanf("%d", &cod_paciente);
									st_paciente* checagem = obterPacientePeloCodigo(cod_paciente);
									if(checagem == NULL){
										printf("Erro\n");
										break;
									}
									if(verificaPaciente(cod_paciente)){
										printf("-------------\n");
										printf("Tratamentos do paciente: %s\n", checagem->nome);
										for(int i=0; i<quantidadeTratamentos(); i++){
											st_tratamento* t = obterTratamentoPeloIndice(i);
											st_bruxo* b = obterBruxoPeloCodigo(t->codigo_bruxo);
											st_paciente* c = obterPacientePeloCodigo(t->codigo_paciente);
											st_pocao* p = obterPocaoPeloCodigo(t->codigo_pocao);
											if(t == NULL || b == NULL || c == NULL || p == NULL){
												printf("Erro!!!!!\n");
												free(t);
												free(b);
												free(c);
												free(p);
												break;
											}
											if(t->codigo_paciente == cod_paciente){
												printf("\nTratamento %d:\n", i+1);
												printf("Codigo do tratamento: %d\n", t->codigo);
												printf("Bruxo: %s, %s\n", b->nome, b->especialidade);
												printf("Pocao: %s do tipo %c\n", p->nome, p->tipo);
												printf("Posologia: %d doses diarias por %d dias\n", t->doses, t->dias);
												
											}
											free(t);
											free(b);
											free(c);
											free(p);
										}
									}
									else{
										printf("O paciente nao possui um tratamento em andamento\n");
									}
									free(checagem);
									break;
								}
								case 2:{
									printf("Digite o codigo do bruxo: ");
									scanf("%d", &cod_bruxo);
									st_bruxo* checagem = obterBruxoPeloCodigo(cod_bruxo);
									if(checagem == NULL){
										printf("Erro\n");
										break;
									}
									if(verificaBruxo(cod_bruxo)){
										printf("-------------\n");
										printf("Tratamentos do bruxo: %s\n", checagem->nome);
										for(int i=0; i<quantidadeTratamentos(); i++){
											st_tratamento* t = obterTratamentoPeloIndice(i);
											st_bruxo* b = obterBruxoPeloCodigo(t->codigo_bruxo);
											st_paciente* c = obterPacientePeloCodigo(t->codigo_paciente);
											st_pocao* p = obterPocaoPeloCodigo(t->codigo_pocao);
											if(t == NULL || b == NULL || c == NULL || p == NULL){
												printf("Erro!!!!!\n");
												free(t);
												free(b);
												free(c);
												free(p);
												break;
											}
											if(t->codigo_bruxo == cod_bruxo){
												printf("\nTratamento %d:\n", i+1);
												printf("Codigo do tratamento: %d\n", t->codigo);
												printf("Paciente: %s, %d anos, %.2f metros\n", c->nome, c->idade, c->altura);
												printf("Pocao: %s do tipo %c\n", p->nome, p->tipo);
												printf("Posologia: %d doses diarias por %d dias\n", t->doses, t->dias);
												
											}
											free(t);
											free(b);
											free(c);
											free(p);
										}
									}
									else{
										printf("O bruxo nao esta cuidando de nenhum tratamento\n");
									}
									free(checagem);
									break;
								}
								case 3:{
									printf("\n-------Lista de Bruxos-------\n");
									for(int i =0; i<QuantidadeBruxos(); i++){
										st_bruxo* b = obterBruxoPeloIndice(i);
										printf("Codigo: %d\n", b->codigo);
										printf("Nome: %s\n", b->nome);
										printf("Especialidade: %s\n\n", b->especialidade);
										free(b);
									}
									printf("Digite o codigo do bruxo: ");
									scanf("%d", &cod_bruxo);
									st_bruxo* b = obterBruxoPeloCodigo(cod_bruxo);
									if(b == NULL){
										printf("Erro!");
										free(b);
										break;
									}
									novo_tratamento.codigo_bruxo = b->codigo;
									free(b);
									printf("\n-------Lista de Pacientes-------\n");
									for(int i =0; i<QuantidadePacientes(); i++){
										st_paciente* c = obterPacientePeloIndice(i);
										printf("Codigo: %d\n", c->codigo);
										printf("Nome: %s\n", c->nome);
										printf("Idade: %d\n", c->idade);
										printf("Altura: %.2f\n\n", c->altura);
										free(c);
									}
									printf("Digite o codigo do paciente: ");
									scanf("%d", &cod_paciente);
									st_paciente* c = obterPacientePeloCodigo(cod_paciente);
									if(c == NULL){
										printf("Erro!");
										free(c);
										break;
									}
									novo_tratamento.codigo_paciente = c->codigo;
									free(c);
									printf("\n-------Lista de Pocoes-------\n");
									for(int i =0; i<QuantidadePocoes(); i++){
										st_pocao* p = obterPocaoPeloIndice(i);
										printf("Codigo: %d\n", p->codigo);
										printf("Nome: %s\n", p->nome);
										printf("Tipo: %c\n\n", p->tipo);
										free(p);
									}
									printf("Digite o codigo da pocao: ");
									scanf("%d", &cod_pocao);
									st_pocao* p = obterPocaoPeloCodigo(cod_pocao);
									if(p == NULL){
										printf("Erro!");
										free(p);
										break;
									}
									novo_tratamento.codigo_pocao = p->codigo;
									free(p);
									
									printf("Digite a quantidade de dias do tratamento: ");
									scanf("%d", &novo_tratamento.dias);
									printf("Digite a quantidade de doses: ");
									scanf("%d", &novo_tratamento.doses);
									
									if(iniciarTratamento(novo_tratamento)){
										printf("Tratamento iniciado!\n");
									}
									else{
										printf("Erro ao iniciar tratamento!\n");
									}
									break;
								}
								case 4:{
									printf("Digite o codigo do tratamento para ampliar: ");
									scanf("%d", &cod_tratamento);
									st_tratamento* t = obterTratamentoPeloCodigo(cod_tratamento);
									if(t != NULL){
										printf("Digite a nova quantidade de dias: ");
										scanf("%d", &t->dias);
										printf("Digite a nova quantidade de doses: ");
										scanf("%d", &t->doses);
										novo_tratamento = *t;
										free(t);
										if(ampliarTratamento(novo_tratamento)){
											printf("Tratamento alterado\n");
										}
										else{
											printf("Erro ao alterar!\n");
										}
										break;
									}
									else{
										printf("Erro de alocacao de memoria!\n");
									}
									free(t);
									break;
								}
								case 5:{
									printf("Digite o codigo do tratamento para apagar: ");
									scanf("%d", &cod_tratamento);
									if(excluirTratamento(cod_tratamento)){
										printf("Tratamento exlcuído.\n");
									}
									else{
										printf("Falha ao exlcuir tratamento!\n");
									}
									break;
								}
							}		
						}		
					}while(opcao_tratamento != 0);
					break;
				}
			}	
		}
	}while(opcao_menu != 0);
	EncerraBruxos();
	EncerraPocoes();
	EncerraPacientes();
	EncerraTratamentos();
	return 0;
}



