/*******************************************************************************
 * Implementa o analisador lexico do compilador.
 *
 * @author: Julio Cesar <julio.cesar@2xt.com.br> - 350705
 *          Ruhan Bidart <ruhan@2xt.com.br> - 347152
 * @since:  18/02/2010
 *******************************************************************************/
// Estrutura de um registro lexico que o analisador retorna
struct lexical_reg {
    char *lexeme;
    char token;
    char type;
    char position;
};
