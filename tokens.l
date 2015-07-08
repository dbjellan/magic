%{
    #include <stdlib.h>
    void yyerror(char *);
    #include "y.tab.h"

    #include "magic.h"

    int nchar, nword;
    int linenum = 0;

    #define YYSTYPE struct ast_node*
    extern YYSTYPE yylval;
%}

digit   [0-9]
letter  [A-Za-z]
pm      "+"|"-"

%%
if                              return IF;
else                            return ELSE;
return                          return RETURN;
function                        return FUNCTION;
end                             return END;

":="                            return ASSIGN;
"."                             return DOT;

{letter}({letter}|{digit})*     {   
                                    yylval = yytext;
                                    return IDENT;

                                }

{digit}+                        {   
                                    yylval = yytext
                                    return INT;
                                }

{digit}+"."{digit}*             {
                                    yylval = yytext
                                    return FLOAT
                                }

"'"[^"'"]*"'"                    {
                                    yylval = yytext;
                                    return STRING;
                                }

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