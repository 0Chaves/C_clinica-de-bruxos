typedef struct
{
	int codigo;
	char nome[30];
	int idade;
	float altura;
} st_paciente;

int inicializarPacientes();
int EncerraPacientes();
int salvarPaciente(st_paciente novo_paciente);
int QuantidadePacientes();
st_paciente* obterPacientePeloIndice(int indice);
st_paciente* obterPacientePeloCodigo(int codigo);
int atualizarPaciente(st_paciente c);
int apagarPacientePeloCodigo(int codigo);
int apagarPacientePeloNome(char* nome);
