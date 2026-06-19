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

int i = 0,
	j = 0,
	soma = 0;

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

// TO DESTACANDO O **** INT MAIN **** PQ VIVO PERDENDO ELE DE VISTA TA BOM !!!! //

int main(){
    
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
    
    if(posPonto - posArroba - 1 < 5) {
        return 0;
    }

    if(strlen(c.chavePix) - posPonto - 1 < 5) {
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
	j = 10;
	int resto = 0,
	primeiroDigito = 0,
	segundoDigito = 0;
		
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
		printf("CPF Validado!");
		return 1;
	}
	else{
		printf("CPF Invalido!");
		return 0;
	}
}

// Funções Clientes

void cadastrarCliente ( Cliente c);
void cadastrarCliente( Cliente c) { 
    
    printf("\nNome..: ");
    fgets( c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';
    
    
    printf("CPF..: ");
    fgets( c.CPF, 50, stdin);
    c.CPF[strcspn(c.CPF, "\n")] = '\0';
    
    while(validarCPF(c) == 0) {
        printf("CPF INVALIDO! Tente novamente..: ");
        fgets( c.CPF, 50, stdin);
        c.CPF[strcspn(c.CPF, "\n")] = '\0';
    }
    
    printf("Telefone..: ");
    fgets( c.telefone, 15, stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';
    
    while(validarTelefone(c) == 0) {
        printf("TELEFONE INVALIDO! Tente novamente..: ");
        fgets( c.telefone, 15, stdin);
        c.telefone[strcspn(c.telefone, "\n")] = '\0';
    }
    
    printf("Data de Nascimento..: ");
    scanf("%d/%d/%d", &c.dataNascimento.dia, &c.dataNascimento.mes, &c.dataNascimento.ano);
    
    while(validarData(c.dataNascimento) == 0) {
        printf("DATA INVALIDA! Tente novamente..: ");
        scanf ("%d", &c.dataNascimento);
    }
    
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    printf("Numero do Cartao...: ");
    fgets( c.numeroCartao, 20, stdin);
    c.numeroCartao[strcspn(c.numeroCartao, "\n")] = '\0';
    
    while(validarCartao(c) == 0) {
        printf("NUMERO DO CARTAO INVALIDO! Tente novamente..: ");
        fgets( c.numeroCartao, 20, stdin);
        c.numeroCartao[strcspn(c.numeroCartao, "\n")] = '\0';
    }
    
    printf("Chave Pix...: ");
    fgets(c.chavePix, 30, stdin);
    c.chavePix[strcspn(c.chavePix, "\n")] = '\0';

    while(validarEmail(c) == 0) {
        printf("CHAVE PIX INVALIDA! Tente novamente..: ");
        fgets(c.chavePix, 30, stdin);
        c.chavePix[strcspn(c.chavePix, "\n")] = '\0';
    }
    
    printf("Cadastro realizado!!");
} // quando o telefone é digitado errado ele aparece a mensagem de erro 2 vezes e eu nn copnsigo arrumar aaaa


// Funções de Registro de Venda e Parcelas

int registroVenda();
int registroVenda{
    
    
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
}/******************************************************************************

Uma pequena empresa realiza vendas de produtos e serviços para diversos clientes. Atualmente, o controle financeiro é realizado manualmente, dificultando o acompanhamento dos recebimentos, das vendas parceladas e da situação financeira da empresa. Para melhorar esse processo, será desenvolvido um sistema de controle financeiro em Linguagem C (ANSI C). O sistema deverá permitir o cadastro de clientes, o registro de vendas, o acompanhamento das parcelas a receber e a geração de informações gerenciais para auxiliar na tomada de decisão.
O principal objetivo é controlar o fluxo de entrada de dinheiro na empresa, independentemente da forma de pagamento utilizada. A empresa realiza vendas somente para clientes cadastrados. Cada venda deverá possuir um valor total e uma forma de pagamento. Dependendo da forma de pagamento escolhida, o comportamento do sistema deverá variar:
Dinheiro (recebido imediatamente)
Pix (recebido imediatamente)
Cartão à Vista (recebido imediatamente, com taxa)
Cartão Parcelado (recebido dividido em parcelas mensais, com taxa)
O sistema deverá permitir que a empresa acompanhe:
quanto já recebeu;
quanto ainda tem a receber;
quais parcelas estão vencidas;
quais clientes possuem débitos pendentes;
qual o faturamento total da empresa.


*******************************************************************************/
#include <stdio.h>

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

int main()
{
    printf("Hello World");

    return 0;
}
