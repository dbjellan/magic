#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "grammar.y"
    #include    <stdio.h>
    int yylex(void);
    void yyerror(char *);   

    #include    "magic.h"
    #include    "vm.h"

    m_state* state = NULL
#line 28 "y.tab.c"

#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define INT 257
#define IDENT 258
#define STRING 259
#define FLOAT 260
#define IF 261
#define ELSE 262
#define RETURN 263
#define FUNCTION 264
#define END 265
#define DOT 266
#define ASSIGN 267
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    1,    1,    4,    4,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    5,    5,    3,    3,
};
static const short yylen[] = {                            2,
    1,    2,    2,    4,    7,    1,    3,    1,    4,    1,
    1,    3,    3,    3,    3,    3,    1,    3,    1,    3,
};
static const short yydefred[] = {                         0,
   10,    0,   11,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   16,    0,    0,    0,
    0,   20,    0,   18,    9,    0,    0,    4,    0,    0,
    0,    5,
};
static const short yydgoto[] = {                          6,
   15,    8,    9,   25,   10,
};
static const short yysindex[] = {                       -35,
    0,  -36,    0, -252,  -27,    0,  -35,   10, -238, -256,
  -27,  -22,  -36,  -26,  -35,    0,  -27,  -27,  -27,  -27,
 -234,  -27, -228,  -20,  -33,  -27,    0,  -20,  -20,  -20,
  -20,    0,   16,    0,    0,  -27,  -32,    0,  -20,  -35,
  -38,    0,
};
static const short yyrindex[] = {                         0,
    0,  -10,    0,    0,    0,    0,   34,    0,    0,    4,
    0,    0,   -3,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,   25,    0,    0,    0,   21,   26,   40,
   44,    0,    0,    0,    0,    0,    0,    0,   27,    0,
    0,    0,
};
static const short yygindex[] = {                         0,
    3,   72,    0,   30,    0,
};
#define YYTABLESIZE 266
static const short yytable[] = {                         17,
    2,    5,    7,   11,    5,   12,   17,   35,   40,   23,
   36,   36,    5,    8,   27,   19,   17,   26,   18,   16,
   20,   19,   17,   32,   18,   38,   20,   21,   22,   34,
   12,   17,   17,    1,   17,   13,   17,   17,   17,   17,
   17,   17,   41,   17,    8,    8,    8,    8,    8,   14,
    8,   19,   17,   15,   18,   37,   20,   19,   17,    0,
   18,   12,   20,    0,   12,    6,   13,    7,    6,   13,
    7,    0,    0,    0,    0,    0,   14,    0,    0,    0,
   14,    0,   24,   14,   15,    0,    0,   15,   28,   29,
   30,   31,    0,   33,    0,    0,    0,   24,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   39,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    1,    2,
    3,    1,    2,    3,    0,    4,   42,    0,    4,    1,
   13,    3,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   17,   19,    0,    0,    0,
    0,    0,   17,    0,    0,    2,
};
static const short yycheck[] = {                         10,
    0,   40,    0,   40,   40,  258,   10,   41,   41,  266,
   44,   44,   40,   10,   41,   42,   43,   40,   45,   10,
   47,   42,   43,  258,   45,   10,   47,  266,  267,  258,
   10,   42,   43,    0,   45,   10,   47,   41,   42,   43,
   44,   45,   40,   47,   41,   42,   43,   44,   45,   10,
   47,   42,   43,   10,   45,   26,   47,   42,   43,   -1,
   45,   41,   47,   -1,   44,   41,   41,   41,   44,   44,
   44,   -1,   -1,   -1,   -1,   -1,    5,   -1,   -1,   -1,
   41,   -1,   11,   44,   41,   -1,   -1,   44,   17,   18,
   19,   20,   -1,   22,   -1,   -1,   -1,   26,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   36,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  257,  258,  259,   -1,  264,  265,   -1,  264,  257,
  258,  259,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  266,  267,   -1,   -1,   -1,
   -1,   -1,  266,   -1,   -1,  265,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 267
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"INT","IDENT","STRING","FLOAT","IF","ELSE","RETURN","FUNCTION","END","DOT",
"ASSIGN","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : M",
"M : S",
"S : S S",
"S : exp '\\n'",
"S : lval ASSIGN exp '\\n'",
"S : FUNCTION IDENT '(' arglist ')' S END",
"arglist : exp",
"arglist : arglist ',' exp",
"exp : rval",
"exp : IDENT '(' arglist ')'",
"exp : INT",
"exp : STRING",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp '*' exp",
"exp : exp '/' exp",
"exp : '(' exp ')'",
"rval : IDENT",
"rval : rval DOT IDENT",
"lval : IDENT",
"lval : lval DOT IDENT",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 48 "grammar.y"

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
    yyparse();
    return 0;
}
#line 258 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 19 "grammar.y"
	{ root  =   yystack.l_mark[0]}
break;
case 2:
#line 21 "grammar.y"
	{ yyval = make_statments(yystack.l_mark[-1], yystack.l_mark[0])}
break;
case 3:
#line 22 "grammar.y"
	{ yyval = yystack.l_mark[-1];}
break;
case 4:
#line 23 "grammar.y"
	{ yyval = make_assign(yystack.l_mark[-3], yystack.l_mark[-1])}
break;
case 5:
#line 24 "grammar.y"
	{ yyval make_func(yystack.l_mark[-5], yystack.l_mark[-3], yystack.l_mark[-1])}
break;
case 7:
#line 28 "grammar.y"
	{   make_arglist(yystack.l_mark[-2], yystack.l_mark[0]);}
break;
case 9:
#line 32 "grammar.y"
	{ yyval = make_function_call(yystack.l_mark[-3], yystack.l_mark[-1]);}
break;
case 10:
#line 33 "grammar.y"
	{ yyval = make_int_lit(yystack.l_mark[0]);}
break;
case 11:
#line 34 "grammar.y"
	{ yyval = make_string_lit(yystack.l_mark[0]);}
break;
case 12:
#line 35 "grammar.y"
	{ yyval = make_add(yystack.l_mark[-2], yystack.l_mark[0]);}
break;
case 13:
#line 36 "grammar.y"
	{ yyval = make_sub(yystack.l_mark[-2], yystack.l_mark[0]);}
break;
case 14:
#line 37 "grammar.y"
	{ yyval = make_mult(yystack.l_mark[-2], yystack.l_mark[0]);}
break;
case 15:
#line 38 "grammar.y"
	{ yyval = make_div(yystack.l_mark[-2], yystack.l_mark[0]);}
break;
case 16:
#line 39 "grammar.y"
	{ yyval = yystack.l_mark[-1];}
break;
case 17:
#line 42 "grammar.y"
	{ yyval = make_identifier(yystack.l_mark[0]);}
break;
case 18:
#line 43 "grammar.y"
	{ yyval = make_field(yystack.l_mark[-2], yystack.l_mark[0]);}
break;
case 19:
#line 44 "grammar.y"
	{ yyval = make_lval_identifier(yystack.l_mark[0]);}
break;
case 20:
#line 45 "grammar.y"
	{ yyval = make_lval_access(yystack.l_mark[-2], yystack.l_mark[0]);}
break;
#line 532 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
