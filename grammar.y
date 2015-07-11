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
%token IF ELSE ELSEIF IN FOR WHILE TRY CATCH THROW RETURN FUNCTION END DOT ASSIGN NEWLINE LBRAC RBRAC COLON

%%
M       :   S                   { root  =  make_internal_node(AST_MODULE, $1);}

S       :   S S                 { $$ = make_internal_node(AST_STATEMENTS, $1, $2);}
        |   IF exp COLON S END elseblock        {  $$ = make_internal_node(AST_IF_ELSE, $2, $4, $6);}
        |   IF exp COLON S END                  {  $$ = make_internal_node(AST_IF, $2, $4);}
        |   FOR lval IN exp COLON S END         {  $$ = make_internal_node(AST_FOR, $2, $4, $6);}
        |   WHILE exp COLON S END               {  $$ = make_internal_node(AST_WHILE, $2, $4); }
        |   TRY COLON S CATCH lval COLON S END              { $$ = make_internal_node(AST_TRY_CATCH, $3, $5, $7);}
        |   THROW exp  NEWLINE                  {   $$ = make_internal_node(AST_THROW, $2);} 
        |   exp NEWLINE            { $$ = $1;}
        |   lval ASSIGN exp NEWLINE                 { $$ = make_internal_node(AST_ASSIGN, $1, $3);}
        |   FUNCTION IDENT '(' varlist ')' S END    { $$ = make_internal_node(AST_FUNCTION, $2, $4, $6);}
        ;

elseblock   : ELSE COLON S END                        { $$ = make_internal_node(AST_ELSE, $3);}
            | ELSEIF COLON S END                      { $$ = make_internal_node(AST_ELSEIF, $3);}
            | ELSEIF COLON S END elseblock            { $$ = make_internal_node(AST_ELSEIF_ELSE, $3, $5);}
        ;

//wrong
varlist :
        |   %empty                                    { $$ = make_ast_node(0, AST_EMPVARLIST);}   
        |   varlist     ','     IDENT               { $$ = make_internal_node(AST_VARLIST, $1, make_identifier($3));}
        ;

arglist :   %empty                                         {$$ = make_ast_node(0, AST_EMPARGLIST);}
        |   arglist     ',' exp                            { $$ = make_internal_node(AST_ARGLIST, $1, $3);}
        ;
     
kvplist :   %empty                                      { $$ = make_ast_node(0, AST_EMPKVPLIST);}
        |   kvplist     ',' lval COLON exp              { $$ = make_internal_node(AST_KVPLIST, $1, $3, $5);}
        ;

exp     :   LBRAC arglist RBRAC     { $$ = make_internal_node(AST_LISTTABLE, $2);}
        |   LBRAC kvplist RBRAC     { $$ = make_internal_node(AST_TABLE, $2);}
        |   LBRAC RBRAC            { $$ = make_ast_node(0, AST_EMPTABLE);}
        |   rval
        |   rval '(' arglist ')'   { $$ = make_internal_node(AST_FUNCTION, $1, $3);}
        |   INT                 { $$ = make_int_lit($1);}
        |   FLOAT               { $$ = make_float_lit($1);}
        |   STRING              { $$ = make_string_lit($1);}
        |   exp     '+'     exp { $$ = make_internal_node(AST_ADD, $1, $3);}
        |   exp     '-'     exp { $$ = make_internal_node(AST_SUB, $1, $3);}
        |   exp     '*'     exp { $$ = make_internal_node(AST_MULT, $1, $3);}
        |   exp     '/'     exp { $$ = make_internal_node(AST_DIV, $1, $3);}
        |   '(' exp ')'         { $$ = $2;}
        ;

rval    :   IDENT               { $$ = make_identifier($1);}
        |   rval    DOT rval   { $$ = make_internal_node(AST_ACCESS, $1, $3);}
        ;

lval    :   IDENT               { $$ = make_lval_identifier($1);}
        |   lval    DOT lval      { $$ = make_internal_node(AST_LVAL_ACCESS, $1, $3);}
        ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error on line: %s\n", s);
}