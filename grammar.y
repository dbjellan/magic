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
%token FLOAT
%token IF ELSE RETURN FUNCTION END DOT ASSIGN

%%
M       :   S                   { root  =   $1}

S       :   S S                 { $$ = make_statments($1, $2)}
        |   exp '\n'            { $$ = $1;}
        |   lval ASSIGN exp '\n'  { $$ = make_assign($1, $3)}
        |   FUNCTION IDENT '(' arglist ')' S END    { $$ make_func($2, $4, $6)}
        ;

arglist :   exp
        |   arglist     ','     exp {   make_arglist($1, $3);}
        ;
        
exp     :   rval  
        |   IDENT '(' arglist ')'   { $$ = make_function_call($1, $3);}
        |   INT                 { $$ = make_int_lit($1);}
        |   STRING              { $$ = make_string_lit($1);}
        |   exp     '+'     exp { $$ = make_add($1, $3);}
        |   exp     '-'     exp { $$ = make_sub($1, $3);}
        |   exp     '*'     exp { $$ = make_mult($1, $3);}
        |   exp     '/'     exp { $$ = make_div($1, $3);}
        |   '(' exp ')'         { $$ = $2;}
        ;

rval    :   IDENT               { $$ = make_identifier($1);}
        |   rval    DOT IDENT   { $$ = make_field($1, $3);}
lval    :   IDENT               { $$ = make_lval_identifier($1);} ;
        |   lval DOT IDENT      { $$ = make_lval_access($1, $3);}

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
    yyparse();
    return 0;
}