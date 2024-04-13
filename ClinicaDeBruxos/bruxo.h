typedef struct
{
	int codigo;
	char nome[30];
	char especialidade[20];	
} st_bruxo;

int inicializarBruxos();
int EncerraBruxos();
int salvarBruxo(st_bruxo novo);
int QuantidadeBruxos();
st_bruxo* obterBruxoPeloIndice(int indice);
st_bruxo* obterBruxoPeloCodigo(int codigo);
int atualizarBruxo(st_bruxo b);
int apagarBruxoPeloCodigo(int codigo);
int apagarBruxoPeloNome(char* nome);
