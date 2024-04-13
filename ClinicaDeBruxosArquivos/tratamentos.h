typedef struct{
	int codigo;
	int codigo_bruxo;
	int codigo_paciente;
	int codigo_pocao;
	int dias;
	int doses;
} st_tratamento;

int inicializarTratamentos();

int EncerraTratamentos();

int iniciarTratamento(st_tratamento novo_tratamento);

int verificaBruxo(int cod_bruxo);
int verificaPaciente(int cod_paciente);
int verificaPocao(int cod_pocao);

int quantidadeTratamentos();

st_tratamento* obterTratamentoPeloIndice(int indice);
st_tratamento* obterTratamentoPeloCodigo(int codigo);

int ampliarTratamento(st_tratamento novo_tratamento);

int excluirTratamento(int codigo);
