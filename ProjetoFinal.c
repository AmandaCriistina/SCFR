/******************************************************************************

Alunos: Amanda Correa e Giovanni Marin
Turma: C11
Data de Início: 15/06/2026

Uma pequena empresa realiza vendas de produtos e serviços para diversos clientes. Atualmente, o controle financeiro é realizado manualmente, dificultando o acompanhamento dos recebimentos, das vendas parceladas e da situação financeira da empresa. Para melhorar esse processo, será desenvolvido um sistema de controle financeiro em Linguagem C (ANSI C). O sistema deverá permitir o cadastro de clientes, o registro de vendas, o acompanhamento das parcelas a receber e a geração de informações gerenciais para auxiliar na tomada de decisão.
O principal objetivo é controlar o fluxo de entrada de dinheiro na empresa, independentemente da forma de pagamento utilizada. A empresa realiza vendas somente para clientes cadastrados. Cada venda deverá possuir um valor total e uma forma de pagamento. Dependendo da forma de pagamento escolhida, o comportamento do sistema deverá variar:
Dinheiro (recebido imediatamente)
quais clientes possuem débitos pendentes;
qual o faturamento total da empresa.


*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// STRUCTS

typedef struct Data {
		int dia;
		int mes;
		int ano;
} Data;

typedef struct Cliente {
    char nome[50];
    char CPF[50];
    char telefone[15];
    Data dataNascimento;
    char numeroCartao[20];
    char chavePix[30];
} Cliente;

typedef struct Vendas {
    Cliente cliente[50];
    float valorTotalVenda;
    int formaPagamento;
    int qtdeParcelas;
    Data dataVenda;
    char observacao[50];
} Vendas;

typedef struct Parcela {
    int idParcela;
    int idVenda;
    int numeroDaParcela;
    float valorDaParcela;
    Data dataVencimento;
    Data dataRecebimento;
    char situacaoDaParcela;
} Parcela;

// VARIAVEIS GLOBAIS
int i = 0,
	j = 0,
	soma = 0;
	
Cliente cliente[50];
int qtdClientes = 0;
    
// Funções de Validação do Cadastro de Clientes

int validarData ( Data dt );
int validarData ( Data dt ){
    if (dt.dia>=1 && dt.dia<=30) {
        if (dt.mes>=1 && dt.mes<=12) {
            if (dt.ano>=1900 && dt.ano<=2026) {
                return 1;
            }
        }
    }
    return 0;
}

int validarTelefone ( Cliente c );
int validarTelefone ( Cliente c ){
    int tamanho = strlen(c.telefone);
    if (c.telefone[0] == '0' ) { 
        if (tamanho == 11 || tamanho == 12) {
            return 1;
        }
    }
    return 0;
}

int validarEmail ( Cliente c );
int validarEmail ( Cliente c) {
    int arroba = 0;
    int posArroba = -1;
    int posPonto = -1;
    
    for ( i = 0; i < strlen(c.chavePix); i++) {
        if( c.chavePix[i] == '@' ) {
            arroba++;
            posArroba = i;
        }
        
        if ( c.chavePix[i] == '.' ) {
            posPonto = i;
        }
    }
    
    if ( arroba != 1) {
        return 0;
    }

    if(posArroba < 2) {
        return 0;
    }

    if(posPonto == -1) {
        return 0;
    }
    
    if(posPonto - posArroba - 1 < 2) {
        return 0;
    }

    if(strlen(c.chavePix) - posPonto - 1 < 2) {
        return 0;
    }

    return 1;
}

int validarCartao ( Cliente c );
int validarCartao ( Cliente c ){
    int tamanho = strlen(c.numeroCartao);
    int numero = 0;
    int soma = 0;
    int dobrar = 0;
    
    for(i =  tamanho - 1; i>=0; i--){
        numero = c.numeroCartao[i] - '0';
        
        if (dobrar == 1) { 
            numero = numero *2;
            
            if (numero > 9) {
                numero = numero -9;
            }
        }
        
     soma = soma + numero;
     
        if (dobrar == 0) { 
            dobrar = 1;
        } else {
            dobrar = 0;
        }
    }
    
    if (soma % 10 == 0) {
        return 1;
    }
    else {
        return 0; 
    }
}

int validarCPF(Cliente c);
int validarCPF(Cliente c){
	int j = 10;
	int soma = 0;
	
	int resto = 0,
	    primeiroDigito = 0,
	    segundoDigito = 0;
		
	for(i = 0; i < 20; i++){
		if(c.CPF[i] == '\0'){
			printf("CPF Invalido!");
			break;
		}
		
		if(c.CPF[i] == '.' || c.CPF[i] == '-' ){
			continue;
		    
		}
			
		soma += (c.CPF[i] - '0')*j;
		j--;
			
		if(j < 2){
			break;
		}

	}
	
	resto = (soma * 10) % 11;
	if(resto > 10){
		primeiroDigito = 0;
	} else{
		primeiroDigito = resto;
	}
	
	j = 11,
	soma = 0;
	
	for(i = 0; i < 20; i++){
		if(c.CPF[i] == '\0'){
			printf("CPF Invalido!");
			break;
		}
		if(c.CPF[i] == '.' || c.CPF[i] == '-' ){
			continue;}
			
		soma += (c.CPF[i] - '0')*j;
		j--;
			
		if(j < 2){
			break;
		}
	}
	resto = (soma * 10) % 11;
	if(resto > 10){
		segundoDigito = 0;
	} else{
		segundoDigito = resto;
	}
	
	if((c.CPF[strcspn(c.CPF, "\n") - 1] - '0' == segundoDigito) && (c.CPF[strcspn(c.CPF, "\n") - 2] - '0' == primeiroDigito)){
		//printf("CPF Validado!");
		return 1;
	}
	else{
		//printf("CPF Invalido!");
		return 0;
	}
}

// Funções de Clientes

void cadastrarCliente ( Cliente c);
void cadastrarCliente(Cliente c) {

    printf("\nNome..: ");
    fgets(c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("CPF..: ");
    fgets(c.CPF, 50, stdin);
    c.CPF[strcspn(c.CPF, "\n")] = '\0';

    while (validarCPF(c) == 0) {
        printf("CPF INVALIDO! Tente novamente..: ");
        fgets(c.CPF, 50, stdin);
        c.CPF[strcspn(c.CPF, "\n")] = '\0';
    }

    printf("Telefone..: ");
    fgets(c.telefone, 15, stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    while (validarTelefone(c) == 0) {
        printf("TELEFONE INVALIDO! Tente novamente..: ");
        fgets(c.telefone, 15, stdin);
        c.telefone[strcspn(c.telefone, "\n")] = '\0';
    }

    printf("Data de Nascimento..: ");
    scanf("%d/%d/%d", &c.dataNascimento.dia, &c.dataNascimento.mes, &c.dataNascimento.ano);
    getchar();

    while (validarData(c.dataNascimento) == 0) {
        printf("DATA INVALIDA! Tente novamente..: ");
        scanf("%d/%d/%d", &c.dataNascimento.dia, &c.dataNascimento.mes, &c.dataNascimento.ano);
        getchar();
    }

    printf("Numero do Cartao...: ");
    fgets(c.numeroCartao, 20, stdin);
    c.numeroCartao[strcspn(c.numeroCartao, "\n")] = '\0';

    while (validarCartao(c) == 0) {
        printf("NUMERO DO CARTAO INVALIDO! Tente novamente..: ");
        fgets(c.numeroCartao, 20, stdin);
        c.numeroCartao[strcspn(c.numeroCartao, "\n")] = '\0';
    }

    printf("Chave Pix...: ");
    fgets(c.chavePix, 30, stdin);
    c.chavePix[strcspn(c.chavePix, "\n")] = '\0';

    while (validarEmail(c) == 0) {
        printf("CHAVE PIX INVALIDA! Tente novamente..: ");
        fgets(c.chavePix, 30, stdin);
        c.chavePix[strcspn(c.chavePix, "\n")] = '\0';
    }
    
    printf("\n Cadastro Completo!!\n");
    
}

void exibirCliente(Cliente c);
void exibirCliente(Cliente c) {
    printf("\nNome: %s", c.nome);
    printf("\nCPF: %s", c.CPF);
    printf("\nTelefone: %s", c.telefone);
    printf("\nData de Nascimento: %02d/%02d/%04d", c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano);
    printf("\nCartao: %s", c.numeroCartao);
    printf("\nChave Pix: %s", c.chavePix);
}

// BUSCA DE CLIENTES


void buscarPorNome ();
void buscarPorNome () {
    char nome[50];
    i = 0;
    
    printf("Digite o nome..: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].nome, nome) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    
    printf("\nCliente nao encontrado!\n");
    
}

void buscarPorCPF ();
void buscarPorCPF () {
    char CPF[50];
    i = 0;
    
    printf("Digite o CPF..: ");
    fgets(CPF, 50, stdin);
    CPF[strcspn(CPF, "\n")] = '\0';
    
    for ( i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].CPF, CPF) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    
    printf("\nCliente nao encontrado!\n");
    
}

void buscarPorTelefone ();
void buscarPorTelefone () {
    char telefone[15];
    i = 0;
    
    printf("Digite o telefone..: ");
    fgets(telefone, 15, stdin);
    telefone[strcspn(telefone, "\n")] == '\0';
    
    for (i = 0; i < qtdClientes; i++) {
        if (strcmp(cliente[i].telefone, telefone) == 0) {
            exibirCliente(cliente[i]);
            return;
        }
    }
    
    printf("\nCliente nao encontrado!\n");
    
}

void menuBuscarCliente ();
void menuBuscarCliente () {
    int menu = 0;
    
    printf("=============================================================\n");
	printf("                       BUSCA DE CLIENTES\n");
	printf("=============================================================\n");
	printf("Escolha uma das opcoes abaixo:\n");
	printf("-------------------------------------------------------------\n");
	printf("1 - Buscar cliente por Nome");
	printf("2 - Buscar cliente por CPF");
	printf("3 - Buscar cliente por Telefone");
	printf("-------------------------------------------------------------\n");
	printf("Opcao: ");
	scanf("%d",&menu);
	getchar();
    
    switch(menu) {
        case 1:
        buscarPorNome();
        break;
        
        case 2:
        buscarPorCPF();
        break;
        
        case 3:
        buscarPorTelefone();
        break;
        
        default:
        printf("Opcao Invalida!");
    }
}

// Funções de Registro de Venda e Parcelas

int registroVenda();
int registroVenda() {
    return 0;
}

int CalcularParcela();
int CalcularParcela() {
	Parcela p;
	float ValorMes = 0;
	printf("Qual seria o valor total?");
	scanf("%f", &p.valorDaParcela);
	printf("Quantas parcelas?");
	scanf("%d", &p.numeroDaParcela);
	
	ValorMes = p.valorDaParcela / p.numeroDaParcela;
	printf("%.2f", ValorMes);

    return 0;
}

void exibirParcela(Parcela p);
void exibirParcela(Parcela p) {
	printf("        Dados da Parcela   \n");
	printf("ID da Parcela      ->  %10d\n", p.idParcela);
	printf("ID da Venda        ->  %10d\n", p.idVenda);
	printf("Numero da Parcela  ->  %10d\n", p.numeroDaParcela);
	printf("Valor da Parcela   ->  R$ %7.2f\n", p.valorDaParcela);
	printf("Data de Vencimento ->  %02d/%02d/%d\n", p.dataVencimento.dia ,p.dataVencimento.mes, p.dataVencimento.ano);
	printf("Data de Recebimento -> %02d/%02d/%d\n", p.dataRecebimento.dia ,p.dataRecebimento.mes, p.dataRecebimento.ano);
	printf("\nSituacao da Parcela: %c\n", p.situacaoDaParcela);
	
}	


// TO DESTACANDO O **** INT MAIN **** PQ VIVO PERDENDO ELE DE VISTA TA BOM !!!! //

int main(){
    
    int menu = 0;
    
    
    printf("=============================================================\n");
	printf("                     PAINEL DE COMPRA E VENDAS\n");
	printf("=============================================================\n");
	printf("Desenvolvido por Amanda e Giovanni\n");
	printf("-------------------------------------------------------------\n");
	printf("Escolha uma das opcoes abaixo:\n");
	printf("-------------------------------------------------------------\n");
	printf("1 - Cadastrar Cliente\n");
	printf("2 - Registrar Venda\n");
	printf("3 - Consultar Clientes\n");
	printf("4 - Consultar Parcelas\n");
	printf("5 - Parcelas Vencidas\n");
	printf("6 - Clientes Inadimplentes\n");
	printf("7 - Faturamento Total\n");
	printf("8 - Valor a Receber\n");
	printf("9 - Valor Recebido\n");
	printf("0 - Sair\n");
	printf("-------------------------------------------------------------\n");
	printf("Opcao: ");
	scanf("%d",&menu);
	getchar();
	
    switch(menu){
		case 1:
		    cadastrarCliente(cliente[qtdClientes]);
		    qtdClientes++;
			break;
			
		case 2:
			break;
			
		case 3:
		    menuBuscarCliente();
			break;
			
		case 4:
			break;
			
		default:
			break;
			
		}
		
		return 0;
}
