/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "WXTBison.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAXSTR 20
#define MAXMEMBER 100

#define INTTYPE  0
#define REALTYPE 1

extern int yylex();
extern FILE* yyin;
extern char str1[20];

int FillType(int first,int type);
int Merge(int,int);
void BackPatch(int,int);
int GEN(char*,int,int,int);
void OutputQ(void);
int yyparse();
void OutputIList(void);
int yyerror(char*);
int Entry(char*);
int VarCount=0;//变量个数
FILE* fp;
int NXQ=0;  /* used to indicate the number of next Quater*/



struct QUATERLIST{char op[6];int arg1,arg2,result;} QuaterList[MAXMEMBER];//四元式
struct VARLIST{char name[20];int type;int addr;} VarList[MAXMEMBER];//符号表


#line 102 "WXTBison.tab.c" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "WXTBison.tab.h".  */
#ifndef YY_YY_WXTBISON_TAB_H_INCLUDED
# define YY_YY_WXTBISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Iden = 300,
    IntNo = 301,
    RealNo = 302,
    Program = 400,
    Begin = 401,
    End = 402,
    Var = 403,
    Integer = 404,
    Real = 405,
    While = 406,
    If = 407,
    Else = 408,
    For = 409,
    To = 410,
    LE = 500,
    GE = 501,
    NE = 502,
    UMINUS = 504
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 37 "WXTBison.y" /* yacc.c:355  */

 int Iv;
 int CH;
 int NO;
 struct { int TC,FC;} _BExpr;
 struct { int AC,BC,CC,CH;} _FExpr; //For的属性：AC传递TC，BC传递1，CC传递变量i，CH传递退出链FC
 struct { int QUAD,CH;} _WBD; //while
 struct { int QUAD,CH,D,N;} _FD; //For
 struct { int type,place;/*union{int Iv;float Rv;} Value;*/} _Expr;
 char _Rop[5];
 int First;
 char str[20];

#line 177 "WXTBison.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_WXTBISON_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 192 "WXTBison.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   143

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   504

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,     2,     2,    30,    21,     2,
      35,    36,    28,    26,    33,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    32,
      23,    25,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     5,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      17,    18,    19,     2,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   109,   113,   119,   122,   123,   125,   126,
     128,   129,   130,   131,   133,   137,   140,   141,   144,   145,
     146,   147,   150,   155,   156,   158,   178,   180,   182,   184,
     186,   188,   190,   194,   199,   228,   258,   287,   316,   327,
     331,   338,   343,   346,   353,   352,   355,   355,   357,   359,
     361,   366,   371,   377,   378,   379,   380,   381,   382
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Iden", "IntNo", "RealNo", "Program",
  "Begin", "End", "Var", "Integer", "Real", "While", "If", "Else", "For",
  "To", "LE", "GE", "NE", "'|'", "'&'", "'!'", "'<'", "'>'", "'='", "'+'",
  "'-'", "'*'", "'/'", "'%'", "UMINUS", "';'", "','", "':'", "'('", "')'",
  "$accept", "ProgDef", "SubProg", "VarDef", "VarDefList", "Type",
  "VarList", "Asignment", "StateLists", "StateList", "Statement",
  "AsignState", "Asign_Varable", "I_T_E", "I_T", "Wd", "W", "Fd", "FExpr",
  "ComplexState", "Expr", "BoolExpr", "$@1", "$@2", "Varable", "Const",
  "RelationOp", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   503,   300,   301,   302,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   500,   501,   502,
     124,    38,    33,    60,    62,    61,    43,    45,    42,    47,
      37,   504,    59,    44,    58,    40,    41
};
# endif

#define YYPACT_NINF -55

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-55)))

#define YYTABLE_NINF -33

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      16,     1,    24,   -16,   -55,    44,   106,    -3,   -55,     4,
     -55,   106,   -55,    25,    29,   -55,   106,     3,   -55,   -55,
      34,   106,   106,   106,    40,   106,   -55,   -55,   -55,   -55,
      -3,    36,    47,    62,    12,    51,    36,   -55,   -55,   -55,
      59,   -55,    71,   -55,    51,   -55,    47,   -55,    65,    36,
     106,   -55,   -55,   -55,    51,    10,    51,    78,   -15,   -55,
     -55,    81,    80,    10,   -55,    -2,    73,   -55,    65,    15,
     -55,    10,   -55,    64,     5,   -55,   -55,   -55,   -55,   -55,
     -55,    10,    10,    10,    10,    10,    10,   -55,   -55,   -55,
      51,   -55,   101,   -55,    10,   -55,    96,   -55,   -55,    82,
      82,   -55,   -55,   -55,   101,    51,    51,    46,   101,    99,
     -55,    10,   107,    10,   102
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     2,     0,
      50,     0,    30,     0,     0,    24,     0,     0,    16,    18,
       0,     0,     0,     0,     0,     0,    23,    26,     8,     9,
       5,     0,     7,     0,     0,     0,     0,    17,     4,    15,
       0,    19,    20,    21,     0,    22,     6,    12,    13,     0,
       0,    33,    51,    52,     0,     0,     0,     0,     0,    41,
      42,     0,     0,     0,    27,     0,     0,    10,    11,     0,
      48,     0,    40,     0,     0,    58,    56,    57,    53,    54,
      55,     0,     0,     0,     0,     0,     0,    46,    44,    28,
       0,    31,    25,    29,     0,     3,     0,    39,    49,    34,
      35,    36,    37,    38,    43,     0,     0,     0,    14,    47,
      45,     0,     0,     0,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -55,   112,   -55,   -55,   109,    91,   -55,    -8,
      49,   105,   -55,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -54,   -44,   -55,   -55,    27,    30,   -55
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     8,    15,    30,    31,    32,    47,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    62,    26,
      57,    58,   106,   105,    59,    60,    86
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      65,    72,    73,    34,     3,    87,    88,    28,    29,    92,
      70,    38,    74,    10,    52,    53,     5,    96,    87,    88,
      51,    89,     1,    95,     4,    87,    88,    99,   100,   101,
     102,   103,   104,    27,    93,    39,    33,    55,    27,    10,
     108,    98,    69,    27,    39,    71,   107,    39,    27,    27,
      27,     6,    27,     7,    10,    52,    53,   112,    48,    99,
      35,   109,   110,    27,    36,    37,    87,    88,    40,    50,
      41,    42,    43,    54,    45,    44,    68,    27,    55,   111,
      49,    75,    76,    77,    63,    64,    56,    78,    79,    80,
      81,    82,    83,    84,    85,    75,    76,    77,    94,    66,
      97,    78,    79,    80,    81,    82,    83,    84,    85,    10,
      83,    84,    85,    11,    90,     7,    91,     9,    12,    13,
      88,    14,    81,    82,    83,    84,    85,    81,    82,    83,
      84,    85,    97,   113,    82,    83,    84,    85,   -32,    46,
      67,    61,     0,   114
};

static const yytype_int8 yycheck[] =
{
      44,    55,    56,    11,     3,    20,    21,    10,    11,    63,
      54,     8,    56,     3,     4,     5,    32,    71,    20,    21,
       8,    36,     6,     8,     0,    20,    21,    81,    82,    83,
      84,    85,    86,     6,    36,    32,    32,    27,    11,     3,
      94,    36,    50,    16,    32,    35,    90,    32,    21,    22,
      23,     7,    25,     9,     3,     4,     5,   111,    31,   113,
      35,   105,   106,    36,    35,    16,    20,    21,    34,     7,
      21,    22,    23,    22,    25,    35,    49,    50,    27,    33,
      33,    17,    18,    19,    25,    14,    35,    23,    24,    25,
      26,    27,    28,    29,    30,    17,    18,    19,    25,    34,
      36,    23,    24,    25,    26,    27,    28,    29,    30,     3,
      28,    29,    30,     7,    33,     9,    36,     5,    12,    13,
      21,    15,    26,    27,    28,    29,    30,    26,    27,    28,
      29,    30,    36,    26,    27,    28,    29,    30,    36,    30,
      49,    36,    -1,   113
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    38,     3,     0,    32,     7,     9,    39,    40,
       3,     7,    12,    13,    15,    40,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    56,    61,    10,    11,
      41,    42,    43,    32,    46,    35,    35,    47,     8,    32,
      34,    47,    47,    47,    35,    47,    43,    44,    61,    33,
       7,     8,     4,     5,    22,    27,    35,    57,    58,    61,
      62,    48,    55,    25,    14,    58,    34,    44,    61,    46,
      58,    35,    57,    57,    58,    17,    18,    19,    23,    24,
      25,    26,    27,    28,    29,    30,    63,    20,    21,    36,
      33,    36,    57,    36,    25,     8,    57,    36,    36,    57,
      57,    57,    57,    57,    57,    60,    59,    58,    57,    58,
      58,    33,    57,    26,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    41,    41,    42,    42,
      43,    43,    43,    43,    44,    45,    46,    46,    47,    47,
      47,    47,    47,    47,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    58,    59,    58,    60,    58,    58,    58,
      61,    62,    62,    63,    63,    63,    63,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     5,     3,     2,     2,     1,     1,     1,
       3,     3,     2,     2,     4,     2,     1,     2,     1,     2,
       2,     2,     2,     1,     1,     4,     1,     3,     4,     4,
       1,     4,     7,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     3,     0,     4,     0,     4,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=0;printf("\nCompile successfully!\n");}
#line 1353 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 110 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1].CH),NXQ);
		 GEN("Stop",0,0,0);
	    }
#line 1361 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 114 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1].CH),NXQ);
		 GEN("Stop",0,0,0);
	    }
#line 1369 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 120 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=0;}
#line 1375 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 122 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=0;}
#line 1381 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 123 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=0;}
#line 1387 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 125 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.Iv)=INTTYPE;}
#line 1393 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 126 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.Iv)=REALTYPE;}
#line 1399 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 128 "WXTBison.y" /* yacc.c:1646  */
    {FillType((yyvsp[0].CH),(yyvsp[-2].First));}
#line 1405 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 129 "WXTBison.y" /* yacc.c:1646  */
    {FillType((yyvsp[0].NO),(yyvsp[-2].First));}
#line 1411 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 130 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.First)=(yyvsp[-1].Iv) ;FillType((yyvsp[0].CH),(yyval.First));}
#line 1417 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.First)=(yyvsp[-1].Iv) ;FillType((yyvsp[0].NO),(yyval.First));}
#line 1423 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 134 "WXTBison.y" /* yacc.c:1646  */
    {
			   GEN(":=",(yyvsp[0]._Expr).place,0,(yyvsp[-3].NO));}
#line 1430 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 138 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1].CH),NXQ);(yyval.CH)=0;}
#line 1436 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 140 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=(yyvsp[0].CH);}
#line 1442 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 142 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=(yyvsp[0].CH);}
#line 1448 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 144 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=0;}
#line 1454 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 145 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=Merge((yyvsp[-1].CH),(yyvsp[0].CH));}
#line 1460 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 146 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=Merge((yyvsp[-1].CH),(yyvsp[0].CH));}
#line 1466 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 147 "WXTBison.y" /* yacc.c:1646  */
    { GEN("j",0,0,(yyvsp[-1]._WBD).QUAD);
		  BackPatch((yyvsp[0].CH),(yyvsp[-1]._WBD).QUAD);
		  (yyval.CH)=(yyvsp[-1]._WBD).CH;}
#line 1474 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 151 "WXTBison.y" /* yacc.c:1646  */
    {
		GEN("I+",(yyvsp[-1]._FD).D,(yyvsp[-1]._FD).N,(yyvsp[-1]._FD).D);
		GEN("j",0,0,(yyvsp[-1]._FD).QUAD);
		(yyval.CH)=(yyvsp[-1]._FD).CH;}
#line 1483 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 155 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=(yyvsp[0].CH);}
#line 1489 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 156 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=0;}
#line 1495 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 160 "WXTBison.y" /* yacc.c:1646  */
    {
			 if(VarList[(yyvsp[-3].NO)].type==(yyvsp[0]._Expr).type)
			   GEN(":=",(yyvsp[0]._Expr).place,0,(yyvsp[-3].NO));
			 else if((yyvsp[0]._Expr).type==INTTYPE)
			 {
			   int T=NewTemp();
			   GEN("I->R",(yyvsp[0]._Expr).place,0,T);
			   GEN(":=",T,0,(yyvsp[-3].NO));
			 }
			else
			{
			 int T=NewTemp();
			 GEN("R->I",(yyvsp[0]._Expr).place,0,T);
			 GEN(":=",T,0,(yyvsp[-3].NO));
			}
			(yyval.CH)=(yyvsp[-3].NO);
	      }
#line 1517 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 178 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.NO)=(yyvsp[0].NO);}
#line 1523 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 180 "WXTBison.y" /* yacc.c:1646  */
    {int q=NXQ;GEN("j",0,0,0);BackPatch((yyvsp[-2].CH),NXQ);(yyval.CH)=Merge((yyvsp[-1].CH),q);}
#line 1529 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 182 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1]._BExpr).TC,NXQ);(yyval.CH)=(yyvsp[-1]._BExpr).FC;}
#line 1535 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 184 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1]._BExpr).TC,NXQ);(yyval._WBD).QUAD=(yyvsp[-3].CH);(yyval._WBD).CH=(yyvsp[-1]._BExpr).FC;}
#line 1541 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 186 "WXTBison.y" /* yacc.c:1646  */
    {(yyval.CH)=NXQ;}
#line 1547 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 188 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1]._FExpr).AC,NXQ);(yyval._FD).QUAD=(yyvsp[-1]._FExpr).AC;(yyval._FD).CH=(yyvsp[-1]._FExpr).CH;(yyval._FD).D=(yyvsp[-1]._FExpr).CC;(yyval._FD).N=(yyvsp[-1]._FExpr).BC;}
#line 1553 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 190 "WXTBison.y" /* yacc.c:1646  */
    {
			(yyval._FExpr).AC=(yyvsp[-4]._BExpr).TC;(yyval._FExpr).CH=(yyvsp[-4]._BExpr).FC;(yyval._FExpr).CC=(yyvsp[-6].CH);(yyval._FExpr).BC=(yyvsp[0]._Expr).place;
			}
#line 1561 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 195 "WXTBison.y" /* yacc.c:1646  */
    {
                  (yyval.CH)=(yyvsp[-1].CH);
 		}
#line 1569 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 200 "WXTBison.y" /* yacc.c:1646  */
    {
		 int T=NewTemp();
		 if((yyvsp[-2]._Expr).type== INTTYPE && (yyvsp[0]._Expr).type==INTTYPE)
		 {
		  GEN("I+",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=INTTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== REALTYPE && (yyvsp[0]._Expr).type==REALTYPE)
		 {
		  GEN("R+",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[-2]._Expr).place,0,U);
		  GEN("R+",U,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[0]._Expr).place,0,U);
		  GEN("R+",(yyvsp[0]._Expr).place,U,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 (yyval._Expr).place=T;
		}
#line 1602 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 229 "WXTBison.y" /* yacc.c:1646  */
    {
		 int T=NewTemp();
		 if((yyvsp[-2]._Expr).type== INTTYPE && (yyvsp[0]._Expr).type==INTTYPE)
		 {
		  GEN("I-",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=INTTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== REALTYPE && (yyvsp[0]._Expr).type==REALTYPE)
		 {
		  GEN("R-",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[-2]._Expr).place,0,U);
		  GEN("R-",U,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[0]._Expr).place,0,U);
		  GEN("R-",(yyvsp[0]._Expr).place,U,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 (yyval._Expr).place=T;
		}
#line 1635 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 259 "WXTBison.y" /* yacc.c:1646  */
    {
		 int T=NewTemp();
		 if((yyvsp[-2]._Expr).type== INTTYPE && (yyvsp[0]._Expr).type==INTTYPE)
		 {
		  GEN("I*",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=INTTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== REALTYPE && (yyvsp[0]._Expr).type==REALTYPE)
		 {
		  GEN("R*",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[-2]._Expr).place,0,U);
		  GEN("R*",U,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[0]._Expr).place,0,U);
		  GEN("R*",(yyvsp[0]._Expr).place,U,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 (yyval._Expr).place=T;
		}
#line 1668 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 288 "WXTBison.y" /* yacc.c:1646  */
    {
		 int T=NewTemp();
		 if((yyvsp[-2]._Expr).type== INTTYPE && (yyvsp[0]._Expr).type==INTTYPE)
		 {
		  GEN("I/",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=INTTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== REALTYPE && (yyvsp[0]._Expr).type==REALTYPE)
		 {
		  GEN("R/",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else if((yyvsp[-2]._Expr).type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[-2]._Expr).place,0,U);
		  GEN("R/",U,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",(yyvsp[0]._Expr).place,0,U);
		  GEN("R/",(yyvsp[0]._Expr).place,U,T);
		  VarList[T].type=(yyval._Expr).type=REALTYPE;
		 }
		 (yyval._Expr).place=T;
		}
#line 1701 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 317 "WXTBison.y" /* yacc.c:1646  */
    {
		 int T=NewTemp();
		 if((yyvsp[-2]._Expr).type== INTTYPE && (yyvsp[0]._Expr).type==INTTYPE)
		 {
		  GEN("I%",(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,T);
		  VarList[T].type=(yyval._Expr).type=INTTYPE;
		  (yyval._Expr).place=T;
                 }
		
		}
#line 1716 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 328 "WXTBison.y" /* yacc.c:1646  */
    {
		 (yyval._Expr)=(yyvsp[-1]._Expr);
		}
#line 1724 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 332 "WXTBison.y" /* yacc.c:1646  */
    {
		 int T=NewTemp();
		 (yyval._Expr)=(yyvsp[0]._Expr);
		 GEN("Minus",(yyvsp[0]._Expr).place,0,T);
		 (yyval._Expr).place=T;VarList[T].type=VarList[(yyvsp[0]._Expr).place].type;
		}
#line 1735 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 339 "WXTBison.y" /* yacc.c:1646  */
    {
		 (yyval._Expr).place=(yyvsp[0].NO);
		 (yyval._Expr).type=VarList[(yyvsp[0].NO)].type;
		}
#line 1744 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 344 "WXTBison.y" /* yacc.c:1646  */
    { (yyval._Expr)=(yyvsp[0]._Expr);}
#line 1750 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 347 "WXTBison.y" /* yacc.c:1646  */
    {
		 (yyval._BExpr).TC=NXQ;(yyval._BExpr).FC=NXQ+1;
		 GEN((yyvsp[-1]._Rop),(yyvsp[-2]._Expr).place,(yyvsp[0]._Expr).place,0);
		 GEN("j",0,0,0);
		}
#line 1760 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 353 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1]._BExpr).TC,NXQ);}
#line 1766 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 354 "WXTBison.y" /* yacc.c:1646  */
    {(yyval._BExpr).TC=(yyvsp[0]._BExpr).TC;(yyval._BExpr).FC=Merge((yyvsp[-3]._BExpr).FC,(yyvsp[0]._BExpr).FC);}
#line 1772 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 355 "WXTBison.y" /* yacc.c:1646  */
    {BackPatch((yyvsp[-1]._BExpr).FC,NXQ);}
#line 1778 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 356 "WXTBison.y" /* yacc.c:1646  */
    {(yyval._BExpr).FC=(yyvsp[0]._BExpr).FC;(yyval._BExpr).TC=Merge((yyvsp[-3]._BExpr).TC,(yyvsp[0]._BExpr).TC);}
#line 1784 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 358 "WXTBison.y" /* yacc.c:1646  */
    {(yyval._BExpr).TC=(yyvsp[0]._BExpr).FC;(yyval._BExpr).FC=(yyvsp[0]._BExpr).TC;}
#line 1790 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 359 "WXTBison.y" /* yacc.c:1646  */
    {(yyval._BExpr)=(yyvsp[-1]._BExpr);}
#line 1796 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 362 "WXTBison.y" /* yacc.c:1646  */
    { 
		    (yyval.NO)=Entry(str1);
	    	}
#line 1804 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 367 "WXTBison.y" /* yacc.c:1646  */
    { int i=Entry(str1);
		  (yyval._Expr).type=VarList[i].type=INTTYPE;
		  (yyval._Expr).place=i;
		}
#line 1813 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 372 "WXTBison.y" /* yacc.c:1646  */
    { int i=Entry(str1);
		  (yyval._Expr).type=VarList[i].type=REALTYPE;
		  (yyval._Expr).place=i;
		}
#line 1822 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 377 "WXTBison.y" /* yacc.c:1646  */
    {strcpy((yyval._Rop),"j<");}
#line 1828 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 378 "WXTBison.y" /* yacc.c:1646  */
    {strcpy((yyval._Rop),"j>");}
#line 1834 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 379 "WXTBison.y" /* yacc.c:1646  */
    {strcpy((yyval._Rop),"j=");}
#line 1840 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 380 "WXTBison.y" /* yacc.c:1646  */
    {strcpy((yyval._Rop),"j>=");}
#line 1846 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 381 "WXTBison.y" /* yacc.c:1646  */
    {strcpy((yyval._Rop),"j!=");}
#line 1852 "WXTBison.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 382 "WXTBison.y" /* yacc.c:1646  */
    {strcpy((yyval._Rop),"j<=");}
#line 1858 "WXTBison.tab.c" /* yacc.c:1646  */
    break;


#line 1862 "WXTBison.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 386 "WXTBison.y" /* yacc.c:1906  */

/*int yylex(void)
{ 
}
*/
void OutputQ(void) //输出四元式
{int i;
 for(i=0;i<NXQ;i++)
 {
  printf("(%3d) ( %5s, ",i,QuaterList[i].op);
  if(QuaterList[i].arg1)
	printf("%6s, ",VarList[QuaterList[i].arg1].name);
	else printf("      , ");
  if(QuaterList[i].arg2)
	printf("%6s, ",VarList[QuaterList[i].arg2].name);
	else printf("      , ");
  if((QuaterList[i].op[0]=='j')||(QuaterList[i].op[0]=='S')) 
		printf("%6d )\n",QuaterList[i].result);
   else if(QuaterList[i].result)
	printf("%6s )\n",VarList[QuaterList[i].result].name);
	else printf("-\t )\n");
 }
 return;
}



int yyerror(char *errstr)  
{
          printf(" %s\n",errstr);
          return 0;
}

int Entry(char *name) //将变量名填入符号表
{int i;
 for(i=1;i<=VarCount;i++) if(!strcmp(name,VarList[i].name)) return i;
 if(++VarCount>MAXMEMBER) {printf("Too many Variables!\n");exit(-1);}
 strcpy(VarList[VarCount].name,name);
 return VarCount;
}

int FillType(int first,int type)
{ int i;
  for(i=first;i<=VarCount;i++)
    VarList[i].type=type;
  return i-1;
}
int Merge(int p,int q)
{
 int r;
 if(!q) return p;
  else
  {
   r=q;
   while(QuaterList[r].result)
    r=QuaterList[r].result;
   QuaterList[r].result=p;
  }
 return q;
}
void BackPatch(int p,int t)
{
 int q=p;
 while(q)
 { int q1=QuaterList[q].result;
   QuaterList[q].result=t;
   q=q1;
 } 
 return;
}
int GEN(char* op,int a1,int a2,int re)
{
 strcpy(QuaterList[NXQ].op,op);
 QuaterList[NXQ].arg1=a1;
 QuaterList[NXQ].arg2=a2;
 QuaterList[NXQ].result=re;
 NXQ++;
 return NXQ;
}

int NewTemp()
{
 static int no=0;
 char Tname[10];
 sprintf(Tname,"_T%o",no++);
 return Entry(Tname);
}

void OutputIList(void)
{
 int i;
 printf(" No.\t name \t\t   type\n");
 for(i=1;i<=VarCount;i++)
  {
   printf("%4d\t%6s\t\t",i,VarList[i].name);
   if(VarList[i].type) printf(" REAL  \n");else printf(" INTEGER\n"); 
  }
 return;
}

int main(int argc, char *argv[])
{
 yyin=NULL;
 if(argc>1)
 {
  if((yyin=fopen(argv[1],"r"))==NULL)
  {printf("Can't open file %s\n",argv[1]);exit(0);}
  }
  yyin=fopen("Mini.txt","r");
	if(yyin==NULL){
	    printf("Can't open file Mini.txt\n");
		return -1;
	}
 yyparse();
 printf("\n");
 OutputQ();
 OutputIList();
 getchar();
 return;
}
