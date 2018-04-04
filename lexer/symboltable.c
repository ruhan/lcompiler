/*******************************************************************************
 * Implementa as funções da tabela de símbolos, preenchida pelo analisador
 * léxico, e usada por todo o compilador.
 *
 * @author: Julio Cesar <julio.cesar@2xt.com.br> - 350705
 *          Ruhan Bidart <ruhan@2xt.com.br> - 347152
 * @since:  18/02/2010
 *******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <config.h>
#include <lexer/symboltable.h>

// Usado para popular a tabela de simbolos com as palavras reservadas da
// linguagem
extern char symboltable_initial_tokens[LCOMPILER_SYMBOLTABLE_INITIAL_LENGTH][7] = {
    "true", "final", "int", "byte", "string", "while", "if", "else",
    "and", "or", "not", "==", "=", "(", ")", "<", ">", "<>", ">=",
    "<=", ",", "+", "-", "*", "/", ";", "begin", "end", "readln",
    "write", "false", "boolean", "writeln"
};

/**
 * Funcao de espalhamento para a hash. Esta e a mesma funcao utilizada pelo
 * berkeley db e pela gawk e tem sua e sua performance e garantida pois
 * fora testada exaustivamente.
 */
static unsigned int sdbm(char *str)
{
    // TODO: conferir valores muto grandes que esta função está retornando
    // (considerar usar este resultado % tamanho da hsh)
    unsigned long hash = 0;
    int c;

    // O numero 65599 e utilizado como constante magica
    // Ao evitar uma multiplicacao utilizando os deslocamentos
    // ganhamos em performance.
    while ((c = *str++))
        hash = c + ((hash << 6) + (hash << 16) - hash);

    return hash;
}

// true se as strings forem iguais (utilizado internamente pela Hash table para
// detectar colissoes, e coisas do tipo)
static unsigned int teste_chaves_iguais(char *v, char *v1){
    return (strcmp(v, v1)  == 0);
}



// Inicializa os valores dos tokens da linguagem L na tabela de simbolos
void symboltable_init(void)
{
    if(LCOMPILER_DEBUG){
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("POPULANDO TABELA DE SIMBOLOS\n");
    }

    symboltable = create_hashtable(LCOMPILER_SYMBOLTABLE_MINSIZE,
                                   sdbm,
                                   teste_chaves_iguais);

    register int x=0;
    for(x=0; x<LCOMPILER_SYMBOLTABLE_INITIAL_LENGTH; x++){
        struct symbol *symb = symboltable_insert((char) x,
                                                 symboltable_initial_tokens[x]);

        if(LCOMPILER_DEBUG){
            printf("* Inserido '%s' com o token %d \n",
                                   symboltable_initial_tokens[x], symb->token);
        }
    }
}


// Insercao na tabela de simbolos
struct symbol *symboltable_insert(char token, char *lexeme)
{
    struct symbol *symb = (struct symbol *) malloc(sizeof(struct symbol));
    symb->token = token;

    // Criamos uma string equivalente ao lexema indicado e fazemos a inserção
    // com este elemento
    char *lex = malloc(sizeof(char) * strlen(lexeme));
    strcpy(lex, lexeme);
    symb->lexeme = lex;

    int inserted = hashtable_insert(symboltable, lex, symb);

    if (inserted) return symb;
    else return NULL;
}


// Pesquisa na tabela de simbolos
struct symbol *symboltable_search(char *lexeme)
{
    return (struct symbol *) hashtable_search(symboltable, lexeme);
}


// Exibe na tela o conteudo de todos o símbolos contidos na tabela de simbolos
void symboltable_print(void)
{
    if(LCOMPILER_DEBUG){
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("VISUALIZANDO CONTEUDO DA TABELA DE SIMBOLOS\n");
    }

    if (hashtable_count(symboltable) > 0) {
        struct hashtable_itr *itr = hashtable_iterator(symboltable);
        char *k;
        struct symbol *v;

        do {
            k = hashtable_iterator_key(itr);
            v = hashtable_iterator_value(itr);

            if(LCOMPILER_DEBUG){
                printf("LEXEMA %-15s  TOKEN %d \n", k, v->lexeme, v->token);
            }

        } while (hashtable_iterator_advance(itr));
        free(itr);
    }
}


// Libera o conteudo usado pela tabela de simbolos
void symboltable_destroy(void)
{
    hashtable_destroy(symboltable, 1);
}
