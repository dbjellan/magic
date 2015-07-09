%{
    #include    <stdio.h>

    #include    "magic.h"
    #include    "ast.h"

    int yylex(void);
    void yyerror(char *);   


    extern int readInputForLexer(char* buffer,int *numBytesRead,int maxBytesToRead);
    ast_node* root;
%}
%code requires { #define YYSTYPE struct ast_node* }
%token INT
%token IDENT
%token STRING
%token FLOAT
%token IF ELSE RETURN FUNCTION END DOT ASSIGN NEWLINE

%%
M       :   S                   { root  =  make_module($1);}

S       :   S S                 { $$ = make_statements($1, $2);}
        |   exp NEWLINE            { $$ = $1;}
        |   lval ASSIGN exp NEWLINE  { $$ = make_assign($1, $3);}
        |   FUNCTION IDENT '(' varlist ')' S END    { $$ = make_func($2, $4, $6);}
        ;

varlist :   IDENT               {make_identifier($1);}
        |   varlist     ','     IDENT {make_varlist($1, $3);}

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
        ;

lval    :   IDENT               { $$ = make_lval_identifier($1);}
        |   lval DOT IDENT      { $$ = make_lval_access($1, $3);}
        ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}