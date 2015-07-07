%{
    #include <stdlib.h>
    void yyerror(char *);
    #include "y.tab.h"

    int nchar, nword, nline;

    #define YYSTYPE struct magic_object*
    extern YYSTYPE yylval;
%}

digit   [0-9]
letter  [A-Za-z]
pm      "+"|"-"

%%

{letter}({letter}|{digit})*     {   
                                    yylval = yytext;
                                    return IDENT;

                                }

{digit}+                        {   
                                    yylval = atoi(yytext);
                                    return INT;
                                }

"'"[^"'"]*"'"                    {
                                    yylval = yytext;
                                    return STRING;
                                }

[-+()*\n]                       return *yytext;

:=                              ECHO;

[ \t]   ;

"#".*   ;

.                               yyerror("invalid token");

%%

int yywrap(void) {
    return 1;
}