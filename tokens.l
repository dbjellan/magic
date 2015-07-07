%{
    #include <stdlib.h>
    void yyerror(char *);
    #include "y.tab.h"

    #include "magic.h"

    int nchar, nword;
    int linenum = 0;

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
                                    yylval = make_magic_object(atoi(yytext));
                                    return INT;
                                }

"'"[^"'"]*"'"                    {
                                    yylval = make_magic_object(yytext);
                                    return STRING;
                                }

"if"                            return IF;
"else"                          return ELSE;
"return"                        return RETURN;
"function"                      return FUNCTION;
"end"                           return END;

[-+()*]                         return *yytext;

"\n"                            {
                                    linenum++;
                                    ECHO;
                                }

:=                              ECHO;

[ \t]   ;

"#".*   ;

.                               yyerror("invalid token");

%%

int yywrap(void) {
    return 1;
}