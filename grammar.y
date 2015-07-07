%{
    #include    <stdio.h>
    int yylex(void);
    void yyerror(char *);   

    #include    "magic.h"
%}

%token INT
%token IDENT
%token STRING

%%
S       :   S S
        |   exp '\n'            { printf("%d\n", $1);}
        |   lval ':=' exp
        ;

exp     :   INT                 { $$ = $1;}
        |   STRING
        |   IDENT               { $$ = get_identifier($1);}
        |   exp     '+'     exp { $$ = $1 + $3;}
        |   exp     '-'     exp { $$ = $1 - $3;}
        |   exp     '*'     exp { $$ = $1 * $3;}
        |   exp     '/'     exp { $$ = $1 / $3;}
        |   '(' exp ')'         { $$ = $2;}
        ;

lval    :   IDENT;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
    yyparse();
    return 0;
}