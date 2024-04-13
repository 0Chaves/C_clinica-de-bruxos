typedef struct
{
	int codigo;
	char nome[30];
	char tipo;
} st_pocao;

int inicializarPocoes();
int EncerraPocoes();
int salvarPocao(st_pocao nova_pocao);
int QuantidadePocoes();
st_pocao* obterPocaoPeloIndice(int indice);
st_pocao* obterPocaoPeloCodigo(int codigo);
int atualizarPocao(st_pocao p);
int apagarPocaoPeloCodigo(int codigo);
int apagarPocaoPeloNome(char* nome);
