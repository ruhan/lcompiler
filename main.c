/*******************************************************************************
 * Arquivo principal que executa todas as outras funcoes do compilador.
 *
 * @author: Julio Cesar <julio.cesar@2xt.com.br> - 350705
 *          Ruhan Bidart <ruhan@2xt.com.br> - 347152
 * @since:  18/02/2010
 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <ext/cmockery/cmockery.h>

#include <config.h>
#include <lexer/symboltable.h>



#ifdef LCOMPILER_TESTS
int test_maria(void) {
    return 1;
}

void test_one(void **state) {
    assert_int_equal(test_maria(), 2);
}

// Testa a insercao e recuperacao de chaves sequencias na hashtable da tabela
// de simbolos
int test_populate_symboltable_proc(){
    symboltable_init();

    symboltable_print();

    // insere os itens
    register int x;
    for (x = 0; x < 100; x += 1) {
        char *lex = malloc(sizeof(char) * 9);

        sprintf(lex, "teste%d", x);
        symboltable_insert((char) x, lex);

        free(lex);
    }

    // Recupera os mesmos items
    // Repare que este loop e percorrido 50 vezes a mais qque as insercoes
    // anteriores: testando tambem a inexistencia de um item
    for (x = 0; x < 100; x += 1) {
        char *lex = malloc(sizeof(char) * 20);
        sprintf(lex, "teste%d", x);

        struct symbol *symb = (struct symbol *) symboltable_search(lex);
        if (symb && strcmp(lex, symb->lexeme) == 0) {
            printf("Lexema %s vale sobre o token %d\n", symb->lexeme, symb->token);
        } else {
            printf("Lexema %s nao encontrado\n", lex);
            return 1;
        }

        free(lex);
    }
    symboltable_print();
    symboltable_destroy();
    return 0;
}

void test_populate_symboltable(void **state) {
    assert_int_equal(test_populate_symboltable_proc(), 0);
}
#endif


int main(int argc, char* argv[])
{
    #ifdef LCOMPILER_TESTS
    const UnitTest tests[] = {
        unit_test(test_populate_symboltable),
    };
    return run_tests(tests);
    #else
        return 0;
    #endif
}

