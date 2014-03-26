/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 271 "_config_reader_parser.y"

#ifndef IN_PEACH_CONFIG_READER_PARSER_C
    #error This file must be inclued by peach_config_reader_parser.c
#endif
#line 15 "_config_reader_parser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    peach_config_reader_parserTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is peach_config_reader_parserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    peach_config_reader_parserARG_SDECL     A static variable declaration for the %extra_argument
**    peach_config_reader_parserARG_PDECL     A parameter declaration for the %extra_argument
**    peach_config_reader_parserARG_STORE     Code to store %extra_argument into yypParser
**    peach_config_reader_parserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 19
#define YYACTIONTYPE unsigned char
#define peach_config_reader_parserTOKENTYPE  peach_config_reader_parser_token_data_t * 
typedef union {
  peach_config_reader_parserTOKENTYPE yy0;
  peach_list_t * yy6;
  peach_config_reader_parser_node_t * yy11;
  peach_string_list_t * yy16;
  int yy37;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define peach_config_reader_parserARG_SDECL  peach_config_reader_parser_node_t ** config_tree ;
#define peach_config_reader_parserARG_PDECL , peach_config_reader_parser_node_t ** config_tree 
#define peach_config_reader_parserARG_FETCH  peach_config_reader_parser_node_t ** config_tree  = yypParser->config_tree 
#define peach_config_reader_parserARG_STORE yypParser->config_tree  = config_tree 
#define YYNSTATE 38
#define YYNRULE 17
#define YYERRORSYMBOL 11
#define YYERRSYMDT yy37
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor;

/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    31,   24,   14,   13,   35,    3,   56,   31,   31,   14,
 /*    10 */    14,   27,    7,    6,    4,   23,   11,    1,   27,    5,
 /*    20 */    23,   38,    2,   16,   21,   10,   22,   35,   15,   22,
 /*    30 */    25,   19,   12,   26,   27,   35,   35,    8,   34,   37,
 /*    40 */    22,   28,   17,   10,   22,   10,   18,   10,   29,    8,
 /*    50 */    30,    9,   32,   33,   20,   36,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    11,   11,   13,   13,    6,   16,   17,   11,   11,   13,
 /*    10 */    13,    7,   16,   16,    1,    2,    5,    4,    7,    1,
 /*    20 */     2,    0,    4,   15,   12,    3,   12,    6,   14,   12,
 /*    30 */     8,   14,    5,    7,    7,    6,    6,    6,    9,    9,
 /*    40 */    12,   10,   14,    3,   12,    3,   14,    3,    8,    6,
 /*    50 */     8,    6,    8,   10,   15,    6,
};
#define YY_SHIFT_USE_DFLT (-3)
#define YY_SHIFT_MAX 23
static const signed char yy_shift_ofst[] = {
 /*     0 */    -2,   -2,   -2,   21,   11,   27,   29,   30,    4,    4,
 /*    10 */     4,   45,   45,   13,   18,   22,   31,   40,   42,   44,
 /*    20 */    43,   26,   26,   49,
};
#define YY_REDUCE_USE_DFLT (-12)
#define YY_REDUCE_MAX 12
static const signed char yy_reduce_ofst[] = {
 /*     0 */   -11,   -4,   -3,  -10,   14,   17,  -10,  -10,   28,   32,
 /*    10 */    12,    8,   39,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */    55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
 /*    10 */    55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
 /*    20 */    55,   50,   49,   55,   43,   44,   54,   53,   45,   52,
 /*    30 */    51,   39,   40,   41,   42,   47,   48,   46,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  peach_config_reader_parserARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void peach_config_reader_parserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "EQUAL",         "DOT",           "COLON",       
  "BRACKETL",      "SQUAREBRACKETL",  "PATH",          "TEXT",        
  "SEMICOLON",     "BRACKETR",      "SQUAREBRACKETR",  "error",       
  "string",        "path",          "values",        "pairs",       
  "node",          "start",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "start ::= node",
 /*   1 */ "node ::= error",
 /*   2 */ "node ::= path EQUAL values SEMICOLON",
 /*   3 */ "node ::= path EQUAL SQUAREBRACKETL pairs SQUAREBRACKETR",
 /*   4 */ "node ::= path BRACKETL node BRACKETR",
 /*   5 */ "node ::= node error",
 /*   6 */ "node ::= node path EQUAL values SEMICOLON",
 /*   7 */ "node ::= node path EQUAL SQUAREBRACKETL pairs SQUAREBRACKETR",
 /*   8 */ "node ::= node path BRACKETL node BRACKETR",
 /*   9 */ "path ::= PATH",
 /*  10 */ "path ::= path DOT PATH",
 /*  11 */ "values ::= string",
 /*  12 */ "values ::= values COLON string",
 /*  13 */ "pairs ::= PATH values SEMICOLON",
 /*  14 */ "pairs ::= pairs PATH values SEMICOLON",
 /*  15 */ "string ::= TEXT",
 /*  16 */ "string ::= string TEXT",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to peach_config_reader_parser and peach_config_reader_parserFree.
*/
void *peach_config_reader_parserAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  peach_config_reader_parserARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
      /* TERMINAL Destructor */
    case 1: /* EQUAL */
    case 2: /* DOT */
    case 3: /* COLON */
    case 4: /* BRACKETL */
    case 5: /* SQUAREBRACKETL */
    case 6: /* PATH */
    case 7: /* TEXT */
    case 8: /* SEMICOLON */
    case 9: /* BRACKETR */
    case 10: /* SQUAREBRACKETR */
{
#line 33 "_config_reader_parser.y"

    if ((yypminor->yy0) != 0) {
        if ((yypminor->yy0)->string != 0)
            free((yypminor->yy0)->string);

        free((yypminor->yy0));
    }

#line 396 "_config_reader_parser.c"
}
      break;
    case 12: /* string */
    case 13: /* path */
{
#line 44 "_config_reader_parser.y"

    peach_string_list_destroy((yypminor->yy16));

#line 406 "_config_reader_parser.c"
}
      break;
    case 14: /* values */
{
#line 56 "_config_reader_parser.y"

    peach_list_destroy((yypminor->yy6), (peach_list_clean_t)free);

#line 415 "_config_reader_parser.c"
}
      break;
    case 15: /* pairs */
{
#line 62 "_config_reader_parser.y"

    peach_config_reader_parser_node_destroy((yypminor->yy11));

#line 424 "_config_reader_parser.c"
}
      break;
    case 16: /* node */
{
#line 68 "_config_reader_parser.y"

    if ((yypminor->yy11) != 0)
        peach_config_reader_parser_node_destroy((yypminor->yy11));

#line 434 "_config_reader_parser.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
  peach_config_reader_parserARG_STORE;
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from peach_config_reader_parserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void peach_config_reader_parserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int peach_config_reader_parserStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      int iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( j>=0 && j<YY_SZ_ACTTAB && yy_lookahead[j]==YYWILDCARD ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_MAX ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_MAX );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_SZ_ACTTAB );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   peach_config_reader_parserARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   peach_config_reader_parserARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 17, 1 },
  { 16, 1 },
  { 16, 4 },
  { 16, 5 },
  { 16, 4 },
  { 16, 2 },
  { 16, 5 },
  { 16, 6 },
  { 16, 5 },
  { 13, 1 },
  { 13, 3 },
  { 14, 1 },
  { 14, 3 },
  { 15, 3 },
  { 15, 4 },
  { 12, 1 },
  { 12, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  peach_config_reader_parserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* start ::= node */
#line 140 "_config_reader_parser.y"
{
    *config_tree = yymsp[0].minor.yy11;
}
#line 739 "_config_reader_parser.c"
        break;
      case 1: /* node ::= error */
#line 145 "_config_reader_parser.y"
{
    yygotominor.yy11 = 0;
}
#line 746 "_config_reader_parser.c"
        break;
      case 2: /* node ::= path EQUAL values SEMICOLON */
#line 150 "_config_reader_parser.y"
{
    yygotominor.yy11 = peach_config_reader_parser_node_add_child(0, 
                peach_string_list_merge(yymsp[-3].minor.yy16, 1),
                peach_config_reader_parser_node_values_pairs_add(0, 0, yymsp[-1].minor.yy6));
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,8,&yymsp[0].minor);
}
#line 757 "_config_reader_parser.c"
        break;
      case 3: /* node ::= path EQUAL SQUAREBRACKETL pairs SQUAREBRACKETR */
#line 157 "_config_reader_parser.y"
{
    yygotominor.yy11 = peach_config_reader_parser_node_add_child(0, 
                peach_string_list_merge(yymsp[-4].minor.yy16, 1),
                yymsp[-1].minor.yy11);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,10,&yymsp[0].minor);
}
#line 769 "_config_reader_parser.c"
        break;
      case 4: /* node ::= path BRACKETL node BRACKETR */
#line 164 "_config_reader_parser.y"
{
    if (yymsp[-1].minor.yy11 != 0) {
        yymsp[-3].minor.yy16 = peach_string_list_push(yymsp[-3].minor.yy16, strdup("."));

        yygotominor.yy11 = peach_config_reader_parser_node_add_child(0, 
                    peach_string_list_merge(yymsp[-3].minor.yy16, 1), yymsp[-1].minor.yy11);
    } else {
        peach_string_list_destroy(yymsp[-3].minor.yy16);

        yygotominor.yy11 = 0;
    }
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
#line 787 "_config_reader_parser.c"
        break;
      case 5: /* node ::= node error */
#line 178 "_config_reader_parser.y"
{
    yygotominor.yy11 = yymsp[-1].minor.yy11;
}
#line 794 "_config_reader_parser.c"
        break;
      case 6: /* node ::= node path EQUAL values SEMICOLON */
#line 183 "_config_reader_parser.y"
{
    yygotominor.yy11 = peach_config_reader_parser_node_add_child(yymsp[-4].minor.yy11, 
                peach_string_list_merge(yymsp[-3].minor.yy16, 1), 
                peach_config_reader_parser_node_values_pairs_add(0, 0, yymsp[-1].minor.yy6));
  yy_destructor(yypParser,1,&yymsp[-2].minor);
  yy_destructor(yypParser,8,&yymsp[0].minor);
}
#line 805 "_config_reader_parser.c"
        break;
      case 7: /* node ::= node path EQUAL SQUAREBRACKETL pairs SQUAREBRACKETR */
#line 190 "_config_reader_parser.y"
{
    yygotominor.yy11 = peach_config_reader_parser_node_add_child(yymsp[-5].minor.yy11, 
                peach_string_list_merge(yymsp[-4].minor.yy16, 1), yymsp[-1].minor.yy11);
  yy_destructor(yypParser,1,&yymsp[-3].minor);
  yy_destructor(yypParser,5,&yymsp[-2].minor);
  yy_destructor(yypParser,10,&yymsp[0].minor);
}
#line 816 "_config_reader_parser.c"
        break;
      case 8: /* node ::= node path BRACKETL node BRACKETR */
#line 196 "_config_reader_parser.y"
{
    if (yymsp[-1].minor.yy11 != 0) {
        yymsp[-3].minor.yy16 = peach_string_list_push(yymsp[-3].minor.yy16, strdup("."));

        yygotominor.yy11 = peach_config_reader_parser_node_add_child(yymsp[-4].minor.yy11, 
                peach_string_list_merge(yymsp[-3].minor.yy16, 1), yymsp[-1].minor.yy11);
    } else {
        peach_string_list_destroy(yymsp[-3].minor.yy16);

        yygotominor.yy11 = yymsp[-4].minor.yy11;
    }
  yy_destructor(yypParser,4,&yymsp[-2].minor);
  yy_destructor(yypParser,9,&yymsp[0].minor);
}
#line 834 "_config_reader_parser.c"
        break;
      case 9: /* path ::= PATH */
#line 210 "_config_reader_parser.y"
{
    yygotominor.yy16 = peach_string_list_push(peach_string_list_create(),
                yymsp[0].minor.yy0->string);
    
    free(yymsp[0].minor.yy0);
}
#line 844 "_config_reader_parser.c"
        break;
      case 10: /* path ::= path DOT PATH */
#line 218 "_config_reader_parser.y"
{
    yymsp[-2].minor.yy16 = peach_string_list_push(yymsp[-2].minor.yy16, strdup("."));

    yygotominor.yy16 = peach_string_list_push(yymsp[-2].minor.yy16, yymsp[0].minor.yy0->string);

    free(yymsp[0].minor.yy0);
  yy_destructor(yypParser,2,&yymsp[-1].minor);
}
#line 856 "_config_reader_parser.c"
        break;
      case 11: /* values ::= string */
#line 227 "_config_reader_parser.y"
{
    yygotominor.yy6 = peach_list_init();
    peach_list_push_bottom(yygotominor.yy6, peach_string_list_merge(yymsp[0].minor.yy16, 1)); 
}
#line 864 "_config_reader_parser.c"
        break;
      case 12: /* values ::= values COLON string */
#line 233 "_config_reader_parser.y"
{
    peach_list_push_bottom(yymsp[-2].minor.yy6, peach_string_list_merge(yymsp[0].minor.yy16, 1));

    yygotominor.yy6 = yymsp[-2].minor.yy6;
  yy_destructor(yypParser,3,&yymsp[-1].minor);
}
#line 874 "_config_reader_parser.c"
        break;
      case 13: /* pairs ::= PATH values SEMICOLON */
#line 240 "_config_reader_parser.y"
{
    yygotominor.yy11 = peach_config_reader_parser_node_values_pairs_add(0, 
                yymsp[-2].minor.yy0->string, yymsp[-1].minor.yy6);

    free(yymsp[-2].minor.yy0);
  yy_destructor(yypParser,8,&yymsp[0].minor);
}
#line 885 "_config_reader_parser.c"
        break;
      case 14: /* pairs ::= pairs PATH values SEMICOLON */
#line 248 "_config_reader_parser.y"
{
    yygotominor.yy11 = peach_config_reader_parser_node_values_pairs_add(yymsp[-3].minor.yy11, 
                yymsp[-2].minor.yy0->string, yymsp[-1].minor.yy6);

    free(yymsp[-2].minor.yy0);
  yy_destructor(yypParser,8,&yymsp[0].minor);
}
#line 896 "_config_reader_parser.c"
        break;
      case 15: /* string ::= TEXT */
#line 256 "_config_reader_parser.y"
{
    yygotominor.yy16 = peach_string_list_push(peach_string_list_create(), yymsp[0].minor.yy0->string);

    free(yymsp[0].minor.yy0);
}
#line 905 "_config_reader_parser.c"
        break;
      case 16: /* string ::= string TEXT */
#line 263 "_config_reader_parser.y"
{
    yygotominor.yy16 = peach_string_list_push(yymsp[-1].minor.yy16, yymsp[0].minor.yy0->string);

    free(yymsp[0].minor.yy0);
}
#line 914 "_config_reader_parser.c"
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = yyact;
      yymsp->major = yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  peach_config_reader_parserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
#line 94 "_config_reader_parser.y"

    *config_tree = 0;
#line 964 "_config_reader_parser.c"
  peach_config_reader_parserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  peach_config_reader_parserARG_FETCH;
#define TOKEN (yyminor.yy0)
#define TOKEN_ID (yymajor)
#line 99 "_config_reader_parser.y"

    const char * token_type;

    switch (TOKEN_ID) {
    case PEACH_CONFIG_READER_PARSER_EQUAL:
        token_type = "'='";
        break;
    case PEACH_CONFIG_READER_PARSER_DOT:
        token_type = "'.'";
        break;
    case PEACH_CONFIG_READER_PARSER_COLON:
        token_type = "','";
        break;
    case PEACH_CONFIG_READER_PARSER_BRACKETL:
        token_type = "'{'";
        break;
    case PEACH_CONFIG_READER_PARSER_BRACKETR:
        token_type = "'}'";
        break;
    case PEACH_CONFIG_READER_PARSER_SQUAREBRACKETL:
        token_type = "'['";
        break;
    case PEACH_CONFIG_READER_PARSER_SQUAREBRACKETR:
        token_type = "']'";
        break;
    case PEACH_CONFIG_READER_PARSER_SEMICOLON:
        token_type = "';'";
        break;
    case PEACH_CONFIG_READER_PARSER_PATH:
        token_type = "variable";
        break;
    case PEACH_CONFIG_READER_PARSER_TEXT:
        token_type = "value";
        break;
    }

    peach_log_err("Configuration error: syntax error line:%llu column:%llu: "
                "unexpected %s.\n", TOKEN->line, TOKEN->column, token_type);
#line 1020 "_config_reader_parser.c"
  peach_config_reader_parserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  peach_config_reader_parserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  peach_config_reader_parserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "peach_config_reader_parserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void peach_config_reader_parser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  peach_config_reader_parserTOKENTYPE yyminor       /* The value for the token */
  peach_config_reader_parserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  peach_config_reader_parserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
