%{
    #include    <stdio.h>

    #include    "magic.h"
    #include    "ast.h"

    int yylex(void);
    void yyerror(char *);   


    extern int readInputForLexer(char* buffer,size_t *numBytesRead,int maxBytesToRead);
    ast_node* root;
%}
%code requires { #define YYSTYPE struct ast_node* }
%token INT
%token IDENT
%token STRING
%token FLOAT
%token IF ELSE RETURN FUNCTION END DOT ASSIGN NEWLINE

%%
M       :   S                   { root  =  make_internal_node(AST_MODULE, 1, $1);}

S       :   S S                 { $$ = make_internal_node(AST_STATEMENTS, 2, $1, $2);}
        |   exp NEWLINE            { $$ = $1;}
        |   lval ASSIGN exp NEWLINE                 { $$ = make_internal_node(AST_ASSIGN, 2, $1, $3);}
        |   FUNCTION IDENT '(' varlist ')' S END    { $$ = make_internal_node(AST_FUNC, 3, $2, $4, $6);}
        ;

varlist :   IDENT                                   {make_identifier($1);}
        |   varlist     ','     varlist               {make_internal_node(AST_VARLIST, 2, $1, $3);}

arglist :   exp
        |   arglist     ','     exp {   make_internal_node(AST_ARGLIST, 2, $1, $3);}
        ;
        
exp     :   rval  
        |   IDENT '(' arglist ')'   { $$ = make_function_call($1, $3);}
        |   INT                 { $$ = make_int_lit($1);}
        |   FLOAT               { $$ = make_float_lit($1);}
        |   STRING              { $$ = make_string_lit($1);}
        |   exp     '+'     exp { $$ = make_internal_node(AST_ADD, 2, $1, $3);}
        |   exp     '-'     exp { $$ = make_internal_node(AST_SUB, 2, $1, $3);}
        |   exp     '*'     exp { $$ = make_internal_node(AST_MULT, 2, $1, $3);}
        |   exp     '/'     exp { $$ = make_internal_node(AST_DIV, 2, $1, $3);}
        |   '(' exp ')'         { $$ = $2;}
        ;

rval    :   IDENT               { $$ = make_identifier($1);}
        |   rval    DOT rval   { $$ = make_internal_node(AST_ACCESS, 2, $1, $3);}
        ;

lval    :   IDENT               { $$ = make_lval_identifier($1);}
        |   lval    DOT lval      { $$ = make_internal_node(AST_LVAL_ACCESS, 2, $1, $3);}
        ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error on line: %s\n", s);
}