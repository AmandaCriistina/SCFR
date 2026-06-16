/******************************************************************************

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
#include <string.h>
#include <stdlib.h>

typedef struct Data {
		int dia;
		int mes;
		int ano;
} Data;


typedef struct Cliente {
    char nome[50];
    int CPF[50];
    int telefone[15];
    Data dataNascimento;
    int numeroCartao[20];
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
