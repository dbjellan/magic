%{
    #include    <stdio.h>
    int yylex(void);
    void yyerror(char *);   

    #include    "magic.h"
    #include    "vm.h"

    m_state* state = NULL
%}

%token INT
%token IDENT
%token STRING
%token IF ELSE RETURN FUNCTION END DOT

%%
M       :   S                   { state = new_magic_state();}

S       :   S S
        |   exp '\n'            { }
        |   lval ':=' exp '\n'  { }
        |   FUNCTION IDENT '(' arglist ')' S END
        ;

arglist :   exp
        |   arlist     ','     exp
        
exp     :   IDENT '(' arglist ')'
        |   INT                 { $$ = $1;}
        |   STRING
        |   IDENT               { $$ = get_identifier(state, $1);}
        |   exp     '+'     exp { $$ = $1 + $3;}
        |   exp     '-'     exp { $$ = $1 - $3;}
        |   exp     '*'     exp { $$ = $1 * $3;}
        |   exp     '/'     exp { $$ = $1 / $3;}
        |   '(' exp ')'         { $$ = $2;}
        ;

lval    :   IDENT               { $$ = get_lvalue(state, $1);} ;
        |   lval DOT IDENT      { $$ = get_field($1, $3);}

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
    yyparse();
    return 0;
}