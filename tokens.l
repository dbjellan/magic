%{
    #include <stdlib.h>

    #include "y.tab.h"
    #include "magic.h"

    void yyerror(char *);

    int nchar, nword;
    int linenum = 0;

    #define YYSTYPE struct ast_node*
    extern YYSTYPE yylval;

    extern int readInputForLexer(char* buffer,size_t *numBytesRead,int maxBytesToRead);
    #undef YY_INPUT
    #define YY_INPUT(b,r,s) readInputForLexer(b,&r,s)
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
                                    yylval = (struct ast_node*)yytext;
                                    return IDENT;

                                }

{digit}+                        {   
                                    yylval = (struct ast_node*)yytext;
                                    return INT;
                                }

{digit}+\.{digit}*             {
                                    yylval = (struct ast_node*)yytext;
                                    return FLOAT;
                                }

\"[^\"]*\"                    {
                                    yylval = (struct ast_node*)yytext;
                                    return STRING;
                                }

[-+()*]                         return *yytext;

"\n"                            {
                                    linenum++;
                                    return NEWLINE;
                                }


[ \t]   ;

"#".*   ;

.                               yyerror("invalid token");

%%

int yywrap(void) {
    return 1;
}