%{
    #include <stdlib.h>

    #include "y.tab.h"
    #include "magic.h"

    void yyerror(char *);

    int nchar, nword;
    int linenum = 0;

    #define YYSTYPE struct ast_node*
    extern YYSTYPE yylval;

    extern int readInputForLexer(char* buffer,int *numBytesRead,int maxBytesToRead);
    #undef YY_INPUT
    #define YY_INPUT(b,r,s) readInputForLexer(b,&r,s)

%}

digit   [0-9]
letter  [A-Za-z]
pm      "+"|"-"

%%
if                              return IF;
else                            return ELSE;
elseif                          return ELSEIF;
return                          return RETURN;
function                        return FUNCTION;
end                             return END;
in                              return IN;
for                             return FOR;
while                           return WHILE;
try     return TRY;
catch   return CATCH;
throw   return THROW;

\:\=                                return ASSIGN;
\:                                  return COLON;
\.                                  return DOT;

\{  return LBRAC;
\}  return RBRAC;
{letter}({letter}|{digit})*     {   
                                    char *text = (char *)malloc(yyleng+1);
                                    strcpy(text, yytext);
                                    yylval = (struct ast_node*)text;
                                    //printf("yylval: %s\n", (char *)text);
                                    return IDENT;

                                }

{digit}+                        {   
                                    char *text = (char *)malloc(yyleng+1);
                                    strcpy(text, yytext);
                                    yylval = (struct ast_node*)text;
                                    return INT;
                                }

{digit}+\.{digit}*             {
                                    char *text = (char *)malloc(yyleng+1);
                                    strcpy(text, yytext);
                                    yylval = (struct ast_node*)text;
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

\#.*   ;

.                               yyerror("invalid token");

%%

int yywrap(void) {
    return 1;
}