/*******************************************************************************
 * Interface para as funções de leitura de arquivo do compilador.
 *
 * @author: Julio Cesar <julio.cesar@2xt.com.br> - 350705
 *          Ruhan Bidart <ruhan@2xt.com.br> - 347152
 * @since:  18/02/2010
 *******************************************************************************/

/*
* Codigo ASCII de cada caractere especial permitido no compilador, (letras e
* numeros nao sao caracteres especiais). A cada caractere lido, o teste de
* validade de caractere deve ser feito, e caso um caractere invalido for
* encontrado, o programa deverá ser interrompido.
*
* Caracteres validos:
* Letras:
*   maicusculas: {x | x >= 65 E X <= 90}
*   minusculas: {x | x >= 97 E x <= 122}
*   numeros: {x | x >= 48 E x <= 57}
*   quebra de linha: {x | x = 10}
*   retorno de carro: {x | x = 13}
*/
char valid_especial_characters[] = {
    ' ', '_', '.', ',', ';', ':', '(', ')', '[', ']', '{', '}', '+', '-', '"',
    '\'', '/', '\\', '|', '!', '?', '>', '<', '='
};
