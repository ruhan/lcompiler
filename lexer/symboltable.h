/*******************************************************************************
 * Define os elementos compartilhados pela tabela de simbolos.
 *
 * @author: Julio Cesar <julio.cesar@2xt.com.br> - 350705
 *          Ruhan Bidart <ruhan@2xt.com.br> - 347152
 * @since:  18/02/2010
 *******************************************************************************/
#include <ext/hashtable/hashtable.h>
#include <ext/hashtable/hashtable_itr.h>

#ifndef _LEXER_SYMBOLTABLE
#define _LEXER_SYMBOLTABLE

// Estrutura de um registro lexico na tabela de simbolos
struct symbol {
    char *lexeme;
    char token;
};

// Definicao da tabela de simbolos.
struct hashtable *symboltable;

// Inicializa os valores dos tokens da linguagem L na tabela de simbolos
void symboltable_init(void);

// Libera o conteudo usado pela tabela de simbolos
void symboltable_destroy(void);

// Insercao na tabela de simbolos
struct symbol *symboltable_insert(char token, char *lexeme);

// Pesquisa na tabela de simbolos
struct symbol *symboltable_search(char *lexeme);


// Imprime todos os tokens que atualmente estao na tabela de simbolos
void symboltable_print(void);


#endif
