/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++

   Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

// Take the name prefix into account.
#define yylex   vrml1lex

#include "vrml1-parser.hh"

/* User implementation prologue.  */
#line 38 "./vrml1-parser.yy"

#include "Driver.hh"


/* Line 317 of lalr1.cc.  */
#line 48 "./vrml1-parser.cc"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG							\
  for (bool yydebugcond_ = yydebug_; yydebugcond_; yydebugcond_ = false)	\
    (*yycdebug_)

/* Enable debugging if requested.  */
#if YYDEBUG

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab

namespace vrml1
{
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  vrml1_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  vrml1_parser::vrml1_parser (vrml1::Driver& driver_yyarg)
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
      driver (driver_yyarg)
  {
  }

  vrml1_parser::~vrml1_parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  vrml1_parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
        case 145: /* "\"float\"" */
#line 192 "./vrml1-parser.yy"
	{ debug_stream () << (yyvaluep->fval); };
#line 178 "./vrml1-parser.cc"
	break;
      case 146: /* "\"integer\"" */
#line 192 "./vrml1-parser.yy"
	{ debug_stream () << (yyvaluep->ival); };
#line 183 "./vrml1-parser.cc"
	break;
      case 147: /* "\"string\"" */
#line 192 "./vrml1-parser.yy"
	{ debug_stream () << (yyvaluep->sval); };
#line 188 "./vrml1-parser.cc"
	break;
       default:
	  break;
      }
  }


  void
  vrml1_parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif /* ! YYDEBUG */

  void
  vrml1_parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 147: /* "\"string\"" */
#line 191 "./vrml1-parser.yy"
	{ delete (yyvaluep->sval); };
#line 223 "./vrml1-parser.cc"
	break;

	default:
	  break;
      }
  }

  void
  vrml1_parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

  std::ostream&
  vrml1_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  vrml1_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  vrml1_parser::debug_level_type
  vrml1_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  vrml1_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }


  int
  vrml1_parser::parse ()
  {
    /// Look-ahead and look-ahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the look-ahead.
    semantic_type yylval;
    /// Location of the look-ahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    #line 22 "./vrml1-parser.yy"
{
	// Initialize the initial location.
	yylloc.begin.filename = yylloc.end.filename = &driver.file;
}
  /* Line 547 of yacc.c.  */
#line 305 "./vrml1-parser.cc"
    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;
    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without look-ahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a look-ahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc, driver);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Accept?  */
    if (yyn == yyfinal_)
      goto yyacceptlab;

    /* Shift the look-ahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted unless it is eof.  */
    if (yychar != yyeof_)
      yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:
#line 196 "./vrml1-parser.yy"
    { driver.pushVRMLDoc(); ;}
    break;

  case 5:
#line 203 "./vrml1-parser.yy"
    { driver.pushNodeSeparator(); ;}
    break;

  case 9:
#line 211 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("renderCulling"); ;}
    break;

  case 10:
#line 214 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 11:
#line 215 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 12:
#line 216 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 17:
#line 227 "./vrml1-parser.yy"
    { if (!driver.pushDEF()) { YYERROR; }  ;}
    break;

  case 19:
#line 231 "./vrml1-parser.yy"
    { if (!driver.pushUSE()) { YYERROR; }  ;}
    break;

  case 55:
#line 273 "./vrml1-parser.yy"
    { driver.pushNodeSwitch(); ;}
    break;

  case 59:
#line 282 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("whichChild"); ;}
    break;

  case 60:
#line 287 "./vrml1-parser.yy"
    { driver.pushNodeCube(); ;}
    break;

  case 65:
#line 298 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("width"); ;}
    break;

  case 66:
#line 299 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("height"); ;}
    break;

  case 67:
#line 300 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("depth"); ;}
    break;

  case 68:
#line 305 "./vrml1-parser.yy"
    { driver.pushNodeCone(); ;}
    break;

  case 73:
#line 316 "./vrml1-parser.yy"
    { driver.pushAttributeSFBitmask("parts"); ;}
    break;

  case 74:
#line 317 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("bottomRadius"); ;}
    break;

  case 75:
#line 318 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("height"); ;}
    break;

  case 80:
#line 329 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 81:
#line 330 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 82:
#line 331 "./vrml1-parser.yy"
    { driver.pushInteger(0x03); ;}
    break;

  case 83:
#line 336 "./vrml1-parser.yy"
    {  driver.pushNodeSphere(); ;}
    break;

  case 85:
#line 340 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("radius"); ;}
    break;

  case 86:
#line 345 "./vrml1-parser.yy"
    { driver.pushNodeCylinder(); ;}
    break;

  case 91:
#line 356 "./vrml1-parser.yy"
    { driver.pushAttributeSFBitmask("parts"); ;}
    break;

  case 92:
#line 357 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("radius"); ;}
    break;

  case 93:
#line 358 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("height"); ;}
    break;

  case 98:
#line 369 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 99:
#line 370 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 100:
#line 371 "./vrml1-parser.yy"
    { driver.pushInteger(0x04); ;}
    break;

  case 101:
#line 372 "./vrml1-parser.yy"
    { driver.pushInteger(0x07); ;}
    break;

  case 102:
#line 377 "./vrml1-parser.yy"
    { driver.pushNodeMaterial(); ;}
    break;

  case 107:
#line 388 "./vrml1-parser.yy"
    { driver.pushAttributeMFColor("ambientColor"); ;}
    break;

  case 108:
#line 389 "./vrml1-parser.yy"
    { driver.pushAttributeMFColor("diffuseColor"); ;}
    break;

  case 109:
#line 390 "./vrml1-parser.yy"
    { driver.pushAttributeMFColor("specularColor"); ;}
    break;

  case 110:
#line 391 "./vrml1-parser.yy"
    { driver.pushAttributeMFColor("emissiveColor"); ;}
    break;

  case 111:
#line 392 "./vrml1-parser.yy"
    { driver.pushAttributeMFFloat("shininess"); ;}
    break;

  case 112:
#line 393 "./vrml1-parser.yy"
    { driver.pushAttributeMFFloat("transparency"); ;}
    break;

  case 113:
#line 398 "./vrml1-parser.yy"
    { driver.pushNodeMaterialBinding(); ;}
    break;

  case 115:
#line 402 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("value"); ;}
    break;

  case 116:
#line 405 "./vrml1-parser.yy"
    { driver.pushInteger(0); ;}
    break;

  case 117:
#line 406 "./vrml1-parser.yy"
    { driver.pushInteger(1); ;}
    break;

  case 118:
#line 407 "./vrml1-parser.yy"
    { driver.pushInteger(2); ;}
    break;

  case 119:
#line 408 "./vrml1-parser.yy"
    { driver.pushInteger(3); ;}
    break;

  case 120:
#line 409 "./vrml1-parser.yy"
    { driver.pushInteger(4); ;}
    break;

  case 121:
#line 410 "./vrml1-parser.yy"
    { driver.pushInteger(5); ;}
    break;

  case 122:
#line 411 "./vrml1-parser.yy"
    { driver.pushInteger(6); ;}
    break;

  case 123:
#line 412 "./vrml1-parser.yy"
    { driver.pushInteger(7); ;}
    break;

  case 124:
#line 417 "./vrml1-parser.yy"
    { driver.pushNodeTranslation(); ;}
    break;

  case 126:
#line 421 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("translation"); ;}
    break;

  case 127:
#line 426 "./vrml1-parser.yy"
    { driver.pushNodeRotation(); ;}
    break;

  case 129:
#line 430 "./vrml1-parser.yy"
    { driver.pushAttributeSFRotation("rotation"); ;}
    break;

  case 130:
#line 435 "./vrml1-parser.yy"
    { driver.pushNodeScale(); ;}
    break;

  case 132:
#line 438 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("scaleFactor"); ;}
    break;

  case 133:
#line 443 "./vrml1-parser.yy"
    { driver.pushNodeMatrixTransform(); ;}
    break;

  case 135:
#line 447 "./vrml1-parser.yy"
    { driver.pushAttributeSFMatrix("matrix"); ;}
    break;

  case 136:
#line 452 "./vrml1-parser.yy"
    { driver.pushNodeTransform(); ;}
    break;

  case 141:
#line 463 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("translation"); ;}
    break;

  case 142:
#line 464 "./vrml1-parser.yy"
    { driver.pushAttributeSFRotation("rotation"); ;}
    break;

  case 143:
#line 465 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("scaleFactor"); ;}
    break;

  case 144:
#line 466 "./vrml1-parser.yy"
    { driver.pushAttributeSFRotation("scaleOrientation"); ;}
    break;

  case 145:
#line 467 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("center"); ;}
    break;

  case 146:
#line 472 "./vrml1-parser.yy"
    { driver.pushNodeOrthographicCamera(); ;}
    break;

  case 151:
#line 483 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("position"); ;}
    break;

  case 152:
#line 484 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("orientation"); ;}
    break;

  case 153:
#line 485 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("focalDistance"); ;}
    break;

  case 154:
#line 490 "./vrml1-parser.yy"
    { driver.pushNodePerspectiveCamera(); ;}
    break;

  case 159:
#line 501 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("position"); ;}
    break;

  case 160:
#line 502 "./vrml1-parser.yy"
    { driver.pushAttributeSFRotation("orientation"); ;}
    break;

  case 161:
#line 503 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("focalDistance"); ;}
    break;

  case 162:
#line 504 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("heightAngle"); ;}
    break;

  case 163:
#line 509 "./vrml1-parser.yy"
    { driver.pushNodePointLight(); ;}
    break;

  case 168:
#line 519 "./vrml1-parser.yy"
    { driver.pushAttributeSFBool("on"); ;}
    break;

  case 169:
#line 520 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("intensity"); ;}
    break;

  case 170:
#line 521 "./vrml1-parser.yy"
    { driver.pushAttributeSFColor("color"); ;}
    break;

  case 171:
#line 522 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("location"); ;}
    break;

  case 172:
#line 527 "./vrml1-parser.yy"
    { driver.pushNodeSpotLight(); ;}
    break;

  case 177:
#line 538 "./vrml1-parser.yy"
    { driver.pushAttributeSFBool("on"); ;}
    break;

  case 178:
#line 539 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("intensity"); ;}
    break;

  case 179:
#line 540 "./vrml1-parser.yy"
    { driver.pushAttributeSFColor("color"); ;}
    break;

  case 180:
#line 541 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("location"); ;}
    break;

  case 181:
#line 542 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("direction"); ;}
    break;

  case 182:
#line 543 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("dropOffRate"); ;}
    break;

  case 183:
#line 544 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("cutOffAngle"); ;}
    break;

  case 184:
#line 549 "./vrml1-parser.yy"
    { driver.pushNodeDirectionalLight(); ;}
    break;

  case 189:
#line 560 "./vrml1-parser.yy"
    { driver.pushAttributeSFBool("on"); ;}
    break;

  case 190:
#line 561 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("intensity"); ;}
    break;

  case 191:
#line 562 "./vrml1-parser.yy"
    { driver.pushAttributeSFColor("color"); ;}
    break;

  case 192:
#line 563 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("direction"); ;}
    break;

  case 193:
#line 568 "./vrml1-parser.yy"
    { driver.pushNodeTexture2Transform(); ;}
    break;

  case 198:
#line 579 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec2f("translation"); ;}
    break;

  case 199:
#line 580 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("rotation"); ;}
    break;

  case 200:
#line 581 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec2f("scaleFactor"); ;}
    break;

  case 201:
#line 582 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec2f("center"); ;}
    break;

  case 202:
#line 587 "./vrml1-parser.yy"
    { driver.pushNodeShapeHints(); ;}
    break;

  case 207:
#line 598 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("vertexOrdering"); ;}
    break;

  case 208:
#line 599 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("shapeType"); ;}
    break;

  case 209:
#line 600 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("faceType"); ;}
    break;

  case 210:
#line 601 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("creaseAngle"); ;}
    break;

  case 211:
#line 604 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 212:
#line 605 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 213:
#line 606 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 214:
#line 609 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 215:
#line 610 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 216:
#line 613 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 217:
#line 614 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 218:
#line 619 "./vrml1-parser.yy"
    { driver.pushNodeNormalBinding(); ;}
    break;

  case 220:
#line 623 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("value"); ;}
    break;

  case 221:
#line 626 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 222:
#line 627 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 223:
#line 628 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 224:
#line 629 "./vrml1-parser.yy"
    { driver.pushInteger(0x03); ;}
    break;

  case 225:
#line 630 "./vrml1-parser.yy"
    { driver.pushInteger(0x04); ;}
    break;

  case 226:
#line 631 "./vrml1-parser.yy"
    { driver.pushInteger(0x05); ;}
    break;

  case 227:
#line 632 "./vrml1-parser.yy"
    { driver.pushInteger(0x06); ;}
    break;

  case 228:
#line 633 "./vrml1-parser.yy"
    { driver.pushInteger(0x07); ;}
    break;

  case 229:
#line 638 "./vrml1-parser.yy"
    { driver.pushNodeFontStyle(); ;}
    break;

  case 234:
#line 649 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("size"); ;}
    break;

  case 235:
#line 650 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("family"); ;}
    break;

  case 236:
#line 651 "./vrml1-parser.yy"
    { driver.pushAttributeSFBitmask("style"); ;}
    break;

  case 241:
#line 662 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 242:
#line 663 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 243:
#line 664 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 244:
#line 667 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 245:
#line 668 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 246:
#line 669 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 247:
#line 674 "./vrml1-parser.yy"
    { driver.pushNodeLOD(); ;}
    break;

  case 252:
#line 685 "./vrml1-parser.yy"
    { driver.pushAttributeMFFloat("range"); ;}
    break;

  case 253:
#line 686 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("center"); ;}
    break;

  case 254:
#line 691 "./vrml1-parser.yy"
    { driver.pushNodeNormal(); ;}
    break;

  case 255:
#line 694 "./vrml1-parser.yy"
    { driver.pushAttributeMFVec3f("vector"); ;}
    break;

  case 256:
#line 699 "./vrml1-parser.yy"
    { driver.pushNodeCoordinate3(); ;}
    break;

  case 257:
#line 702 "./vrml1-parser.yy"
    { driver.pushAttributeMFVec3f("point"); ;}
    break;

  case 258:
#line 707 "./vrml1-parser.yy"
    { driver.pushNodeTextureCoordinate2(); ;}
    break;

  case 259:
#line 710 "./vrml1-parser.yy"
    { driver.pushAttributeMFVec2f("point"); ;}
    break;

  case 260:
#line 715 "./vrml1-parser.yy"
    { driver.pushNodePointSet(); ;}
    break;

  case 264:
#line 725 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("startIndex"); ;}
    break;

  case 265:
#line 726 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("numPoints"); ;}
    break;

  case 266:
#line 731 "./vrml1-parser.yy"
    { driver.pushNodeIndexedLineSet(); ;}
    break;

  case 270:
#line 741 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("coordIndex"); ;}
    break;

  case 271:
#line 742 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("coordIndex"); ;}
    break;

  case 272:
#line 743 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("normalIndex"); ;}
    break;

  case 273:
#line 744 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("textureCoordIndex"); ;}
    break;

  case 274:
#line 749 "./vrml1-parser.yy"
    { driver.pushNodeIndexedFaceSet(); ;}
    break;

  case 278:
#line 759 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("coordIndex"); ;}
    break;

  case 279:
#line 760 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("materialIndex"); ;}
    break;

  case 280:
#line 761 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("normalIndex"); ;}
    break;

  case 281:
#line 762 "./vrml1-parser.yy"
    { driver.pushAttributeMFLong("textureCoordIndex"); ;}
    break;

  case 282:
#line 768 "./vrml1-parser.yy"
    { driver.pushNodeTexture2(); ;}
    break;

  case 286:
#line 778 "./vrml1-parser.yy"
    { driver.pushAttributeSFString("filename"); ;}
    break;

  case 287:
#line 779 "./vrml1-parser.yy"
    { driver.pushAttributeSFImage("image"); ;}
    break;

  case 288:
#line 780 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("wrapS"); ;}
    break;

  case 289:
#line 781 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("wrapT"); ;}
    break;

  case 290:
#line 784 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 291:
#line 785 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 292:
#line 790 "./vrml1-parser.yy"
    { driver.pushNodeWWWInline(); ;}
    break;

  case 296:
#line 800 "./vrml1-parser.yy"
    { driver.pushAttributeSFString("name"); ;}
    break;

  case 297:
#line 801 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("bboxSize"); ;}
    break;

  case 298:
#line 802 "./vrml1-parser.yy"
    { driver.pushAttributeSFVec3f("bboxCenter"); ;}
    break;

  case 299:
#line 807 "./vrml1-parser.yy"
    { driver.pushNodeWWWAnchor(); ;}
    break;

  case 303:
#line 817 "./vrml1-parser.yy"
    { driver.pushAttributeSFString("name"); ;}
    break;

  case 304:
#line 818 "./vrml1-parser.yy"
    { driver.pushAttributeSFString("description"); ;}
    break;

  case 305:
#line 819 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("map"); ;}
    break;

  case 306:
#line 822 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 307:
#line 823 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 308:
#line 828 "./vrml1-parser.yy"
    { driver.pushNodeAsciiText(); ;}
    break;

  case 312:
#line 838 "./vrml1-parser.yy"
    { driver.pushAttributeSFString("string"); ;}
    break;

  case 313:
#line 839 "./vrml1-parser.yy"
    { driver.pushAttributeSFFloat("spacing"); ;}
    break;

  case 314:
#line 840 "./vrml1-parser.yy"
    { driver.pushAttributeSFLong("justification"); ;}
    break;

  case 315:
#line 841 "./vrml1-parser.yy"
    { driver.pushAttributeMFFloat("width"); ;}
    break;

  case 316:
#line 844 "./vrml1-parser.yy"
    { driver.pushInteger(0x00); ;}
    break;

  case 317:
#line 845 "./vrml1-parser.yy"
    { driver.pushInteger(0x01); ;}
    break;

  case 318:
#line 846 "./vrml1-parser.yy"
    { driver.pushInteger(0x02); ;}
    break;

  case 319:
#line 854 "./vrml1-parser.yy"
    { driver.StackDown(); ;}
    break;

  case 320:
#line 857 "./vrml1-parser.yy"
    { driver.StackUp(); ;}
    break;

  case 321:
#line 862 "./vrml1-parser.yy"
    { driver.pushBool(false); ;}
    break;

  case 322:
#line 863 "./vrml1-parser.yy"
    { driver.pushBool(true); ;}
    break;

  case 323:
#line 864 "./vrml1-parser.yy"
    { driver.pushBool(false); ;}
    break;

  case 324:
#line 865 "./vrml1-parser.yy"
    { driver.pushBool(true); ;}
    break;

  case 325:
#line 868 "./vrml1-parser.yy"
    { driver.pushInteger(0); ;}
    break;

  case 326:
#line 869 "./vrml1-parser.yy"
    { driver.pushInteger(1); ;}
    break;

  case 327:
#line 870 "./vrml1-parser.yy"
    { driver.pushInteger((yysemantic_stack_[(1) - (1)].ival)); ;}
    break;

  case 333:
#line 882 "./vrml1-parser.yy"
    { driver.pushFloat((yysemantic_stack_[(1) - (1)].fval)); ;}
    break;

  case 334:
#line 883 "./vrml1-parser.yy"
    { driver.pushFloat((yysemantic_stack_[(1) - (1)].ival)); ;}
    break;

  case 335:
#line 884 "./vrml1-parser.yy"
    { driver.pushFloat(0.0); ;}
    break;

  case 336:
#line 885 "./vrml1-parser.yy"
    { driver.pushFloat(1.0); ;}
    break;

  case 362:
#line 941 "./vrml1-parser.yy"
    { driver.pushString(*(yysemantic_stack_[(1) - (1)].sval)); ;}
    break;

  case 371:
#line 960 "./vrml1-parser.yy"
    { driver.pushString(*(yysemantic_stack_[(1) - (1)].sval)); ;}
    break;

  case 373:
#line 964 "./vrml1-parser.yy"
    { driver.pushString("Separator"); ;}
    break;

  case 374:
#line 965 "./vrml1-parser.yy"
    { driver.pushString("{"); ;}
    break;

  case 375:
#line 966 "./vrml1-parser.yy"
    { driver.pushString("}"); ;}
    break;

  case 376:
#line 967 "./vrml1-parser.yy"
    { driver.pushString("Cube"); ;}
    break;

  case 377:
#line 968 "./vrml1-parser.yy"
    { driver.pushString("width"); ;}
    break;

  case 378:
#line 969 "./vrml1-parser.yy"
    { driver.pushString("height"); ;}
    break;

  case 379:
#line 970 "./vrml1-parser.yy"
    { driver.pushString("depth"); ;}
    break;

  case 380:
#line 971 "./vrml1-parser.yy"
    { driver.pushString("SIDES"); ;}
    break;

  case 381:
#line 972 "./vrml1-parser.yy"
    { driver.pushString("parts"); ;}
    break;

  case 382:
#line 973 "./vrml1-parser.yy"
    { driver.pushString("bottomRadius"); ;}
    break;

  case 383:
#line 974 "./vrml1-parser.yy"
    { driver.pushString("BOTTOM"); ;}
    break;

  case 384:
#line 975 "./vrml1-parser.yy"
    { driver.pushString("Cone"); ;}
    break;

  case 385:
#line 976 "./vrml1-parser.yy"
    { driver.pushString("ALL"); ;}
    break;

  case 386:
#line 977 "./vrml1-parser.yy"
    { driver.pushString("Sphere"); ;}
    break;

  case 387:
#line 978 "./vrml1-parser.yy"
    { driver.pushString("radius"); ;}
    break;

  case 388:
#line 979 "./vrml1-parser.yy"
    { driver.pushString("Cylinder"); ;}
    break;

  case 389:
#line 980 "./vrml1-parser.yy"
    { driver.pushString("TOP"); ;}
    break;

  case 390:
#line 981 "./vrml1-parser.yy"
    { driver.pushString("DirectionalLight"); ;}
    break;

  case 391:
#line 982 "./vrml1-parser.yy"
    { driver.pushString("intensity"); ;}
    break;

  case 392:
#line 983 "./vrml1-parser.yy"
    { driver.pushString("color"); ;}
    break;

  case 393:
#line 984 "./vrml1-parser.yy"
    { driver.pushString("on"); ;}
    break;

  case 394:
#line 985 "./vrml1-parser.yy"
    { driver.pushString("direction"); ;}
    break;

  case 395:
#line 986 "./vrml1-parser.yy"
    { driver.pushString("FALSE"); ;}
    break;

  case 396:
#line 987 "./vrml1-parser.yy"
    { driver.pushString("TRUE"); ;}
    break;

  case 397:
#line 988 "./vrml1-parser.yy"
    { driver.pushString("transparency"); ;}
    break;

  case 398:
#line 989 "./vrml1-parser.yy"
    { driver.pushString("Material"); ;}
    break;

  case 399:
#line 990 "./vrml1-parser.yy"
    { driver.pushString("emissiveColor"); ;}
    break;

  case 400:
#line 991 "./vrml1-parser.yy"
    { driver.pushString("ambientColor"); ;}
    break;

  case 401:
#line 992 "./vrml1-parser.yy"
    { driver.pushString("specularColor"); ;}
    break;

  case 402:
#line 993 "./vrml1-parser.yy"
    { driver.pushString("shininess"); ;}
    break;

  case 403:
#line 994 "./vrml1-parser.yy"
    { driver.pushString("diffuseColor"); ;}
    break;

  case 404:
#line 995 "./vrml1-parser.yy"
    { driver.pushString("OVERALL"); ;}
    break;

  case 405:
#line 996 "./vrml1-parser.yy"
    { driver.pushString("MaterialBinding"); ;}
    break;

  case 406:
#line 997 "./vrml1-parser.yy"
    { driver.pushString("PER_FACE"); ;}
    break;

  case 407:
#line 998 "./vrml1-parser.yy"
    { driver.pushString("value"); ;}
    break;

  case 408:
#line 999 "./vrml1-parser.yy"
    { driver.pushString("PER_VERTEX_INDEXED"); ;}
    break;

  case 409:
#line 1000 "./vrml1-parser.yy"
    { driver.pushString("PER_PART"); ;}
    break;

  case 410:
#line 1001 "./vrml1-parser.yy"
    { driver.pushString("PER_FACE_INDEXED"); ;}
    break;

  case 411:
#line 1002 "./vrml1-parser.yy"
    { driver.pushString("DEFAULT"); ;}
    break;

  case 412:
#line 1003 "./vrml1-parser.yy"
    { driver.pushString("PER_PART_INDEXED"); ;}
    break;

  case 413:
#line 1004 "./vrml1-parser.yy"
    { driver.pushString("PER_VERTEX"); ;}
    break;

  case 414:
#line 1005 "./vrml1-parser.yy"
    { driver.pushString("Translation"); ;}
    break;

  case 415:
#line 1006 "./vrml1-parser.yy"
    { driver.pushString("translation"); ;}
    break;

  case 416:
#line 1007 "./vrml1-parser.yy"
    { driver.pushString("Rotation"); ;}
    break;

  case 417:
#line 1008 "./vrml1-parser.yy"
    { driver.pushString("rotation"); ;}
    break;

  case 418:
#line 1009 "./vrml1-parser.yy"
    { driver.pushString("Scale"); ;}
    break;

  case 419:
#line 1010 "./vrml1-parser.yy"
    { driver.pushString("scaleFactor"); ;}
    break;

  case 420:
#line 1011 "./vrml1-parser.yy"
    { driver.pushString("MatrixTransform"); ;}
    break;

  case 421:
#line 1012 "./vrml1-parser.yy"
    { driver.pushString("matrix"); ;}
    break;

  case 422:
#line 1013 "./vrml1-parser.yy"
    { driver.pushString("scaleOrientation"); ;}
    break;

  case 423:
#line 1014 "./vrml1-parser.yy"
    { driver.pushString("Transform"); ;}
    break;

  case 424:
#line 1015 "./vrml1-parser.yy"
    { driver.pushString("center"); ;}
    break;

  case 425:
#line 1016 "./vrml1-parser.yy"
    { driver.pushString("OrthographicCamera"); ;}
    break;

  case 426:
#line 1017 "./vrml1-parser.yy"
    { driver.pushString("position"); ;}
    break;

  case 427:
#line 1018 "./vrml1-parser.yy"
    { driver.pushString("orientation"); ;}
    break;

  case 428:
#line 1019 "./vrml1-parser.yy"
    { driver.pushString("focalDistance"); ;}
    break;

  case 429:
#line 1020 "./vrml1-parser.yy"
    { driver.pushString("heightAngle"); ;}
    break;

  case 430:
#line 1021 "./vrml1-parser.yy"
    { driver.pushString("PerspectiveCamera"); ;}
    break;

  case 431:
#line 1022 "./vrml1-parser.yy"
    { driver.pushString("PointLight"); ;}
    break;

  case 432:
#line 1023 "./vrml1-parser.yy"
    { driver.pushString("SpotLight"); ;}
    break;

  case 433:
#line 1024 "./vrml1-parser.yy"
    { driver.pushString("cutOffAngle"); ;}
    break;

  case 434:
#line 1025 "./vrml1-parser.yy"
    { driver.pushString("dropOffRate"); ;}
    break;

  case 435:
#line 1026 "./vrml1-parser.yy"
    { driver.pushString("location"); ;}
    break;

  case 436:
#line 1027 "./vrml1-parser.yy"
    { driver.pushString("Texture2Transform"); ;}
    break;

  case 437:
#line 1028 "./vrml1-parser.yy"
    { driver.pushString("creaseAngle"); ;}
    break;

  case 438:
#line 1029 "./vrml1-parser.yy"
    { driver.pushString("CLOCKWISE"); ;}
    break;

  case 439:
#line 1030 "./vrml1-parser.yy"
    { driver.pushString("CONVEX"); ;}
    break;

  case 440:
#line 1031 "./vrml1-parser.yy"
    { driver.pushString("vertexOrdering"); ;}
    break;

  case 441:
#line 1032 "./vrml1-parser.yy"
    { driver.pushString("SOLID"); ;}
    break;

  case 442:
#line 1033 "./vrml1-parser.yy"
    { driver.pushString("COUNTERCLOCKWISE"); ;}
    break;

  case 443:
#line 1034 "./vrml1-parser.yy"
    { driver.pushString("shapeType"); ;}
    break;

  case 444:
#line 1035 "./vrml1-parser.yy"
    { driver.pushString("UNKNOWN_FACE_TYPE"); ;}
    break;

  case 445:
#line 1036 "./vrml1-parser.yy"
    { driver.pushString("UNKNOWN_ORDERING"); ;}
    break;

  case 446:
#line 1037 "./vrml1-parser.yy"
    { driver.pushString("faceType"); ;}
    break;

  case 447:
#line 1038 "./vrml1-parser.yy"
    { driver.pushString("UNKNOWN_SHAPE_TYPE"); ;}
    break;

  case 448:
#line 1039 "./vrml1-parser.yy"
    { driver.pushString("ShapeHints"); ;}
    break;

  case 449:
#line 1040 "./vrml1-parser.yy"
    { driver.pushString("NormalBindings"); ;}
    break;

  case 450:
#line 1041 "./vrml1-parser.yy"
    { driver.pushString("SANS"); ;}
    break;

  case 451:
#line 1042 "./vrml1-parser.yy"
    { driver.pushString("FontStyle"); ;}
    break;

  case 452:
#line 1043 "./vrml1-parser.yy"
    { driver.pushString("TYPEWRITER"); ;}
    break;

  case 453:
#line 1044 "./vrml1-parser.yy"
    { driver.pushString("LOD"); ;}
    break;

  case 454:
#line 1045 "./vrml1-parser.yy"
    { driver.pushString("style"); ;}
    break;

  case 455:
#line 1046 "./vrml1-parser.yy"
    { driver.pushString("SERIF"); ;}
    break;

  case 456:
#line 1047 "./vrml1-parser.yy"
    { driver.pushString("size"); ;}
    break;

  case 457:
#line 1048 "./vrml1-parser.yy"
    { driver.pushString("range"); ;}
    break;

  case 458:
#line 1049 "./vrml1-parser.yy"
    { driver.pushString("family"); ;}
    break;

  case 459:
#line 1050 "./vrml1-parser.yy"
    { driver.pushString("ITALIC"); ;}
    break;

  case 460:
#line 1051 "./vrml1-parser.yy"
    { driver.pushString("NONE"); ;}
    break;

  case 461:
#line 1052 "./vrml1-parser.yy"
    { driver.pushString("BOLD"); ;}
    break;

  case 462:
#line 1053 "./vrml1-parser.yy"
    { driver.pushString("("); ;}
    break;

  case 463:
#line 1054 "./vrml1-parser.yy"
    { driver.pushString(")"); ;}
    break;

  case 464:
#line 1055 "./vrml1-parser.yy"
    { driver.pushString("|"); ;}
    break;

  case 465:
#line 1056 "./vrml1-parser.yy"
    { driver.pushString("COMMA"); ;}
    break;

  case 466:
#line 1057 "./vrml1-parser.yy"
    { driver.pushString("["); ;}
    break;

  case 467:
#line 1058 "./vrml1-parser.yy"
    { driver.pushString("]"); ;}
    break;

  case 468:
#line 1059 "./vrml1-parser.yy"
    { driver.pushString("vector"); ;}
    break;

  case 469:
#line 1060 "./vrml1-parser.yy"
    { driver.pushString("Normal"); ;}
    break;

  case 470:
#line 1061 "./vrml1-parser.yy"
    { driver.pushString("point"); ;}
    break;

  case 471:
#line 1062 "./vrml1-parser.yy"
    { driver.pushString("Coordinate3"); ;}
    break;

  case 472:
#line 1063 "./vrml1-parser.yy"
    { driver.pushString("TextrueCoordinate2"); ;}
    break;

  case 473:
#line 1064 "./vrml1-parser.yy"
    { driver.pushString("startIndex"); ;}
    break;

  case 474:
#line 1065 "./vrml1-parser.yy"
    { driver.pushString("numPoints"); ;}
    break;

  case 475:
#line 1066 "./vrml1-parser.yy"
    { driver.pushString("PointSet"); ;}
    break;

  case 476:
#line 1067 "./vrml1-parser.yy"
    { driver.pushString("textureCoordIndex"); ;}
    break;

  case 477:
#line 1068 "./vrml1-parser.yy"
    { driver.pushString("normalIndex"); ;}
    break;

  case 478:
#line 1069 "./vrml1-parser.yy"
    { driver.pushString("coordIndex"); ;}
    break;

  case 479:
#line 1070 "./vrml1-parser.yy"
    { driver.pushString("IndexedLineSet"); ;}
    break;

  case 480:
#line 1071 "./vrml1-parser.yy"
    { driver.pushString("materialIndex"); ;}
    break;

  case 481:
#line 1072 "./vrml1-parser.yy"
    { driver.pushString("IndexedFaceSet"); ;}
    break;

  case 482:
#line 1073 "./vrml1-parser.yy"
    { driver.pushString("renderCulling"); ;}
    break;

  case 483:
#line 1074 "./vrml1-parser.yy"
    { driver.pushString("OFF"); ;}
    break;

  case 484:
#line 1075 "./vrml1-parser.yy"
    { driver.pushString("AUTO"); ;}
    break;

  case 485:
#line 1076 "./vrml1-parser.yy"
    { driver.pushString("ON"); ;}
    break;

  case 486:
#line 1077 "./vrml1-parser.yy"
    { driver.pushString("whichChild"); ;}
    break;

  case 487:
#line 1078 "./vrml1-parser.yy"
    { driver.pushString("Switch"); ;}
    break;

  case 488:
#line 1079 "./vrml1-parser.yy"
    { driver.pushString("filename"); ;}
    break;

  case 489:
#line 1080 "./vrml1-parser.yy"
    { driver.pushString("wrapT"); ;}
    break;

  case 490:
#line 1081 "./vrml1-parser.yy"
    { driver.pushString("CLAMP"); ;}
    break;

  case 491:
#line 1082 "./vrml1-parser.yy"
    { driver.pushString("Texture2"); ;}
    break;

  case 492:
#line 1083 "./vrml1-parser.yy"
    { driver.pushString("image"); ;}
    break;

  case 493:
#line 1084 "./vrml1-parser.yy"
    { driver.pushString("REPEAT"); ;}
    break;

  case 494:
#line 1085 "./vrml1-parser.yy"
    { driver.pushString("wrapS"); ;}
    break;

  case 495:
#line 1086 "./vrml1-parser.yy"
    { driver.pushString("WWWInline"); ;}
    break;

  case 496:
#line 1087 "./vrml1-parser.yy"
    { driver.pushString("bboxCenter"); ;}
    break;

  case 497:
#line 1088 "./vrml1-parser.yy"
    { driver.pushString("bboxSize"); ;}
    break;

  case 498:
#line 1089 "./vrml1-parser.yy"
    { driver.pushString("name"); ;}
    break;

  case 499:
#line 1090 "./vrml1-parser.yy"
    { driver.pushString("map"); ;}
    break;

  case 500:
#line 1091 "./vrml1-parser.yy"
    { driver.pushString("POINT"); ;}
    break;

  case 501:
#line 1092 "./vrml1-parser.yy"
    { driver.pushString("description"); ;}
    break;

  case 502:
#line 1093 "./vrml1-parser.yy"
    { driver.pushString("WWWAnchor"); ;}
    break;

  case 503:
#line 1094 "./vrml1-parser.yy"
    { driver.pushString("justification"); ;}
    break;

  case 504:
#line 1095 "./vrml1-parser.yy"
    { driver.pushString("CENTER"); ;}
    break;

  case 505:
#line 1096 "./vrml1-parser.yy"
    { driver.pushString("spacing"); ;}
    break;

  case 506:
#line 1097 "./vrml1-parser.yy"
    { driver.pushString("string"); ;}
    break;

  case 507:
#line 1098 "./vrml1-parser.yy"
    { driver.pushString("RIGHT"); ;}
    break;

  case 508:
#line 1099 "./vrml1-parser.yy"
    { driver.pushString("AsciiText"); ;}
    break;

  case 509:
#line 1100 "./vrml1-parser.yy"
    { driver.pushString("LEFT"); ;}
    break;

  case 510:
#line 1101 "./vrml1-parser.yy"
    { driver.pushString("ZERO"); ;}
    break;

  case 511:
#line 1102 "./vrml1-parser.yy"
    { driver.pushString("ONE"); ;}
    break;

  case 512:
#line 1103 "./vrml1-parser.yy"
    { driver.pushString("DEF"); ;}
    break;

  case 513:
#line 1104 "./vrml1-parser.yy"
    { driver.pushString("USE"); ;}
    break;

  case 514:
#line 1105 "./vrml1-parser.yy"
    { driver.pushString("VRML_ID"); ;}
    break;


    /* Line 675 of lalr1.cc.  */
#line 2072 "./vrml1-parser.cc"
	default: break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse look-ahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    if (yyn == yyfinal_)
      goto yyacceptlab;

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the look-ahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		   &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyeof_ && yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  vrml1_parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const short int vrml1_parser::yypact_ninf_ = -588;
  const short int
  vrml1_parser::yypact_[] =
  {
       -82,    83,   138,    90,  -588,    83,  -588,  -588,   417,  -588,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    76,    90,    90,    90,    90,    90,    90,    -4,    90,
      90,    90,    90,    90,  -588,  -588,   724,   724,  -588,  -588,
    -588,  -588,   143,  1011,  -588,  1011,  1011,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
      58,  -588,  -588,  -588,  -588,   211,   129,   134,   189,   240,
     203,   125,   124,   123,   127,   218,    71,   219,   209,    92,
     109,    43,    79,   164,   -36,   170,  -588,    94,  -588,   150,
     142,   198,   201,    24,   131,   136,  -588,  -588,  -588,  -588,
     866,   -78,   162,   155,     9,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  1156,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,    58,    58,    58,    58,
     143,   211,  -588,    58,     4,    58,   143,   129,  -588,    58,
     143,    58,     3,    58,   143,   189,  -588,    58,    58,    13,
      58,   143,   240,  -588,   -72,   -70,   -70,   -70,   -72,   -70,
     143,   203,  -588,   141,   262,    58,   143,    58,   143,    58,
     143,    58,   143,    58,    58,    58,    58,    58,   143,    71,
    -588,    58,    58,    58,   143,   219,  -588,    58,    58,    58,
      58,   143,   209,  -588,    58,    58,    13,    58,   143,    92,
    -588,    58,    58,    13,    58,    58,    58,    58,   143,   109,
    -588,    58,    58,    58,    58,   143,    43,  -588,    58,   156,
      27,   -42,   143,    79,  -588,   171,   143,    58,   -72,   143,
     -36,  -588,   182,    58,   145,   143,   170,  -588,    58,  -588,
     158,  -588,   -61,   143,   -61,   143,   -38,   143,    19,    19,
     143,    24,  -588,   -40,   -40,   -40,   -40,   143,   131,  -588,
     -40,   -40,   -40,   -40,   143,   136,  -588,    19,  -588,   143,
    1011,   158,   -56,    19,   -56,   143,  -588,   -78,    58,    58,
     158,   143,   162,  -588,   158,   -75,   158,   143,   155,  -588,
     -72,   -85,    58,   158,   143,     9,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,   111,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,   148,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
      58,  -588,  -588,  -588,    58,  -588,  -588,    58,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,    58,  -588,  -588,
    -588,  -588,    58,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,    58,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,   224,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,    58,  -588,  -588,
    -588,  -588,  -588,    58,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,    19,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,    19,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,   228,   223,  -588,  -588,  -588,  -588,   231,   233,    58,
    -588,   197,    58,    58,  -588,   165,  -588,  -588,   207,  -588,
     221,  -588,   225,    19,  -588,   111,  -588,   148,  -588,    58,
    -588,    58,    58,  -588,   224,    58,  -588,    58,  -588,    19,
    -588,   179,  -588,  -588,  -588,  -588,    58,  -588,  -588,  -588,
    -588,  -588,   184,    58,  -588,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,  -588
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned short int
  vrml1_parser::yydefact_[] =
  {
         0,     0,     0,     0,     2,     3,     1,   319,     6,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   335,   336,     0,     0,   333,   334,
     362,    51,     0,     0,     8,    13,    14,    18,    52,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    45,    46,
      39,    40,    41,    42,    43,    44,    47,    48,    49,    50,
       0,   355,    53,   363,    54,    61,    69,    84,    87,   185,
     103,   114,   125,   128,   131,   134,   137,   147,   155,   164,
     173,   194,   203,   219,   248,   230,   357,     0,   365,     0,
       0,     0,     0,     0,     0,     0,    10,    12,    11,     9,
      56,     0,     0,     0,     0,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   400,   401,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,   450,   452,   453,   454,   455,   456,   457,   458,
     451,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   371,     0,   372,
      19,   320,     5,     7,    15,    16,     0,     0,     0,     0,
       0,    62,    63,     0,     0,     0,     0,    70,    71,     0,
       0,     0,     0,     0,     0,    88,    89,     0,     0,     0,
       0,     0,   186,   187,     0,     0,     0,     0,     0,     0,
       0,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,     0,     0,     0,     0,   148,   149,     0,     0,     0,
       0,     0,   156,   157,     0,     0,     0,     0,     0,   165,
     166,     0,     0,     0,     0,     0,     0,     0,     0,   174,
     175,     0,     0,     0,     0,     0,   195,   196,     0,     0,
       0,     0,     0,   204,   205,     0,     0,     0,     0,     0,
     249,   250,     0,     0,     0,     0,   231,   232,   359,   356,
     367,   364,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   261,   262,     0,     0,     0,     0,     0,   267,   268,
       0,     0,     0,     0,     0,   275,   276,     0,    58,     0,
       0,     0,     0,     0,     0,     0,   283,   284,     0,     0,
       0,     0,   293,   294,     0,     0,     0,     0,   300,   301,
       0,     0,     0,     0,     0,   309,   310,    17,   354,    65,
      66,    67,    60,    64,    75,    80,    81,    82,     0,    73,
      76,    74,    68,    72,    85,    83,    93,    94,     0,    91,
      92,    86,    90,   190,   191,   321,   322,   323,   324,   189,
       0,   192,   184,   188,     0,   337,   112,     0,   110,   107,
     109,   111,   108,   102,   106,   117,   120,   123,   118,   121,
     116,   119,   122,   115,   113,   126,   124,     0,   129,   127,
     132,   130,     0,   135,   133,   141,   142,   143,   144,   145,
     136,   140,   151,   152,   153,   146,   150,   159,   160,   161,
     162,   154,   158,   169,   170,   168,   171,   163,   167,   178,
     179,   177,   181,   183,   182,   180,   172,   176,     0,   198,
     199,   200,   201,   193,   197,   210,   212,   213,   211,   207,
     215,   214,   208,   217,   216,   209,   202,   206,   222,   225,
     228,   223,   226,   221,   224,   227,   220,   218,   253,   252,
     247,   251,   243,   241,   242,     0,   236,   237,   234,   245,
     246,   244,   235,   229,   233,   358,   366,     0,   349,   255,
     254,   257,   256,     0,   343,   259,   258,   325,   326,   327,
     264,   265,   260,   263,     0,   328,   273,   272,   270,   271,
     266,   269,   281,   280,   278,   279,   274,   277,    59,    55,
      57,   286,   291,   290,   289,     0,   287,   288,   282,   285,
     298,   297,   296,   292,   295,   303,   306,   307,   305,   304,
     299,   302,   315,   317,   318,   316,   314,   313,   312,   308,
     311,     0,    78,    98,   100,   101,    99,     0,    96,     0,
     339,     0,     0,     0,   342,     0,   239,   351,     0,   345,
       0,   330,     0,     0,    77,     0,    95,     0,   348,   341,
     338,     0,     0,   238,     0,   353,   350,   347,   344,   332,
     329,     0,    79,    97,   340,   360,     0,   240,   352,   346,
     331,   369,   368,     0,   370,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   361
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  vrml1_parser::yypgoto_[] =
  {
      -588,  -588,   326,   255,  -588,  -588,  -588,   -52,  -588,  -588,
      54,  -588,  -588,  -588,  -588,  -588,  -588,    42,  -588,  -588,
    -588,    40,  -588,  -357,    45,  -588,  -588,  -588,  -588,  -588,
      39,  -588,  -352,  -588,  -588,  -588,  -588,    28,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,    11,  -588,  -588,  -588,     6,  -588,  -588,  -588,
       0,  -588,  -588,  -588,   -11,  -588,  -588,  -588,   -14,  -588,
    -588,  -588,    44,  -588,  -588,  -588,   -17,  -588,  -588,  -588,
     -23,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
     -35,  -588,  -588,  -587,  -588,  -588,  -588,  -588,   -28,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,  -588,   -44,  -588,
    -588,  -588,   -50,  -588,  -588,  -588,   -51,  -588,  -588,   -68,
    -588,   -59,  -588,  -588,  -588,   -69,  -588,  -588,  -588,   -71,
    -588,  -588,  -588,  -588,   -79,  -588,   555,  -239,  -297,  -397,
    -228,  -588,    -8,  -311,  -588,  -364,  -588,  -588,  -304,   -25,
    -588,   -26,   -65,  -588,  -314,  -588,   -29,  -588,  -588,  -588,
    -588,   334,  -588
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  vrml1_parser::yydefgoto_[] =
  {
        -1,     2,     4,    51,    52,    53,   129,    54,    55,    56,
      57,    58,   429,   430,    59,   290,   291,   292,    60,   296,
     297,   298,   469,   671,   672,    61,   300,    62,   304,   305,
     306,   479,   677,   678,    63,   320,   321,   322,    64,   324,
     513,    65,   326,    66,   328,    67,   330,    68,   332,    69,
     338,   339,   340,    70,   344,   345,   346,    71,   351,   352,
     353,    72,   358,   359,   360,    73,   368,   369,   370,    74,
     311,   312,   313,    75,   375,   376,   377,    76,   382,   383,
     384,   569,   572,   575,    77,   386,   586,    78,   395,   396,
     397,   596,   685,   597,   602,    79,   389,   390,   391,    80,
     403,    81,   405,    82,   407,    83,   410,   411,   412,    84,
     417,   418,   419,    85,   424,   425,   426,    86,   435,   436,
     437,   644,    87,   441,   442,   443,    88,   447,   448,   449,
     658,    89,   454,   455,   456,   666,     8,   282,   489,   625,
     626,   692,   490,   496,   681,   559,   615,   690,   608,   609,
     688,    91,    92,   117,   518,   523,    93,    94,   119,   646,
     722,   278,   279
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char vrml1_parser::yytable_ninf_ = -1;
  const unsigned short int
  vrml1_parser::yytable_[] =
  {
        90,   283,   118,   284,   285,   116,   491,   501,   686,   561,
     562,   620,   621,   477,   465,   656,   450,   466,   387,   467,
     526,   515,   528,    90,   494,   520,   497,   573,   533,   525,
     638,   527,   574,   529,   538,   607,   645,   532,   485,   486,
     431,   432,   614,   537,   433,    90,   434,    90,    90,   663,
     388,   462,   664,   546,   665,   657,   624,   472,   613,   545,
     552,   475,     1,   555,   642,   481,   551,   643,    44,    45,
      44,    45,   492,    48,    49,    48,    49,   589,   428,    44,
      45,   503,   286,   588,    48,    49,     3,   516,   371,   519,
     372,   521,   373,   524,     7,   478,   468,   374,   570,   530,
     617,   618,    44,    45,   571,   535,   619,    48,    49,   126,
     127,   128,   541,   354,   355,   356,   333,   717,   334,   547,
     335,   465,    90,   336,   466,   337,   467,   408,   409,   556,
     361,   362,   363,   364,   650,   651,   563,   293,     6,   662,
     294,   295,   451,   576,   452,   453,   378,   587,   281,   379,
     590,   299,   380,   487,   488,   381,   603,   357,   673,   617,
     618,   674,   323,   675,   610,   619,   612,   676,   616,   325,
     327,   622,   365,   366,   367,   505,   329,   506,   630,   507,
     508,   509,   510,   511,   512,   636,   627,   628,   629,   398,
     639,   399,   632,   633,   634,   635,   648,   301,    44,    45,
     302,   385,   653,    48,    49,   578,   303,   579,   660,   580,
     581,   582,   583,   584,   585,   669,    44,    45,   287,   288,
     289,    48,    49,    50,   566,   599,   600,   691,   567,   601,
     314,   568,   315,   316,   317,   318,   319,   413,   414,   415,
     402,   416,   420,   421,   422,   400,   423,   401,   693,   689,
     498,   499,   500,   392,   502,   393,     5,   394,   703,   704,
       5,   307,   308,   309,   310,   347,   348,   349,   350,   331,
      90,   592,   593,   594,   595,   341,   342,   343,   458,   459,
     460,   461,   484,   444,   445,   464,   446,   471,   438,   439,
     440,   474,   699,   476,   700,   480,   711,   514,   404,   483,
      90,   406,   705,   687,   706,    50,   495,    90,    90,    90,
     495,    90,   720,   592,   593,   594,   707,   695,   708,   517,
     709,   694,   710,   522,   696,   721,   517,   697,   517,   544,
     724,     9,   457,   463,   517,   534,   550,   473,   712,   470,
     517,   539,   540,   719,   482,   713,   543,    90,   548,   504,
     531,   536,   542,   549,    90,   557,   493,   553,   554,   564,
     577,   604,   591,   558,   560,   558,   558,   623,   631,   649,
     565,   606,   605,   654,   637,   647,   670,   661,   640,   611,
     495,   280,     0,     0,     0,   598,     0,     0,     0,     0,
      90,     0,     0,     0,     0,     0,     0,     0,   558,     0,
       0,   718,   641,     0,     0,     0,     0,     0,     0,     0,
       0,   652,     0,     0,     0,   655,     0,   659,     0,     0,
       3,     0,    90,    10,   668,     0,     0,     0,     0,     0,
       0,    11,     0,    12,     0,    13,     0,    14,     0,     0,
       0,     0,   495,     0,   667,    15,     0,     0,     0,     0,
       0,     0,    16,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,    18,     0,    19,     0,    20,     0,     0,
      21,   116,    22,     0,     0,     0,     0,    23,    24,    25,
       0,     0,   679,    26,     0,     0,   680,     0,     0,    90,
       0,     0,     0,     0,     0,    27,    28,     0,     0,    29,
       0,     0,     0,     0,     0,    30,     0,     0,     0,   682,
       0,     0,     0,    31,   683,     0,    32,     0,    33,    34,
       0,     0,    35,     0,     0,     0,    36,     0,    37,    38,
       0,     0,     0,     0,    39,     0,     0,     0,    40,     0,
       0,     0,    41,     0,     0,     0,     0,     0,     0,    42,
     684,     0,     0,     0,     0,    43,     0,    44,    45,    46,
      47,     0,    48,    49,    50,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     0,   120,   121,   122,
     123,   124,   125,     0,   130,   131,   132,   133,   134,     0,
       0,     0,     0,     0,     0,   558,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   698,     0,     0,   701,   702,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   714,     0,   715,   716,     0,     0,     0,     0,   558,
       0,     0,     0,     0,     0,     0,     0,     0,   723,     0,
       0,     0,     0,     0,     0,   725,     0,   726,   727,   728,
     729,   730,   731,   732,   733,   734,   735,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,     3,
       0,   277,    10,     0,     0,     0,     0,     0,     0,     0,
      11,     0,    12,     0,    13,     0,    14,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,     0,     0,     0,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    18,     0,    19,     0,    20,     0,     0,    21,
       0,    22,     0,     0,     0,     0,    23,    24,    25,     0,
       0,     0,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,    28,     0,     0,    29,     0,
       0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,    32,     0,    33,    34,     0,
       0,    35,     0,     0,     0,    36,     0,    37,     0,     0,
       0,     0,   427,    39,     0,     0,     0,    40,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,    43,     0,    44,    45,    46,    47,
       0,    48,    49,    50,     3,     0,     0,    10,     0,     0,
       0,     0,     0,     0,     0,    11,     0,    12,     0,    13,
       0,    14,     0,     0,     0,     0,     0,     0,     0,    15,
       0,     0,     0,     0,     0,     0,    16,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,    18,     0,    19,
       0,    20,     0,     0,    21,     0,    22,     0,     0,     0,
       0,    23,    24,    25,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      28,     0,     0,    29,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
      32,     0,    33,    34,     0,     0,    35,     0,     0,     0,
      36,     0,    37,     0,     0,     0,     0,     0,    39,     0,
       0,     0,    40,     0,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,    43,
       0,    44,    45,    46,    47,     0,    48,    49,    50,     3,
       0,     0,    10,     0,     0,     0,     0,     0,     0,     0,
      11,     0,    12,     0,    13,     0,    14,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,     0,     0,     0,
       0,    16,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     0,    18,     0,    19,     0,    20,     0,     0,    21,
       0,    22,     0,     0,     0,     0,    23,    24,    25,     0,
       0,     0,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,    28,     0,     0,    29,     0,
       0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,    31,     0,     0,    32,     0,    33,    34,     0,
       0,    35,     0,     0,     0,    36,     0,    37,     0,     0,
       0,     0,     0,    39,     0,     0,     0,    40,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,    43,     0,    44,    45,     0,     0,
       0,    48,    49,    50
  };

  /* YYCHECK.  */
  const short int
  vrml1_parser::yycheck_[] =
  {
         8,    53,    31,    55,    56,    31,   310,   318,   595,   373,
     374,   408,   409,    10,    10,    90,     7,    13,    54,    15,
     334,   325,   336,    31,    96,   329,    96,    69,   342,   333,
     427,   335,    74,   337,   348,    96,   433,   341,    25,    26,
     118,   119,   406,   347,   122,    53,   124,    55,    56,   134,
      86,   290,   137,   357,   139,   130,    96,   296,    96,   356,
     364,   300,   144,   367,   120,   304,   363,   123,   140,   141,
     140,   141,   311,   145,   146,   145,   146,   388,   130,   140,
     141,   320,    90,   387,   145,   146,     3,   326,    45,   328,
      47,   330,    49,   332,     4,    92,    92,    54,    71,   338,
     140,   141,   140,   141,    77,   344,   146,   145,   146,   113,
     114,   115,   351,    21,    22,    23,    45,   704,    47,   358,
      49,    10,   130,    52,    13,    54,    15,   103,   104,   368,
      21,    22,    23,    24,   438,   439,   375,     8,     0,   450,
      11,    12,   133,   382,   135,   136,    67,   386,     5,    70,
     389,    17,    73,   140,   141,    76,   395,    65,    10,   140,
     141,    13,    37,    15,   403,   146,   405,    19,   407,    45,
      47,   410,    63,    64,    65,    34,    49,    36,   417,    38,
      39,    40,    41,    42,    43,   424,   414,   415,   416,    95,
     429,    97,   420,   421,   422,   423,   435,     8,   140,   141,
      11,    37,   441,   145,   146,    34,    17,    36,   447,    38,
      39,    40,    41,    42,    43,   454,   140,   141,     7,     8,
       9,   145,   146,   147,    68,    80,    81,   624,    72,    84,
      27,    75,    29,    30,    31,    32,    33,   106,   107,   108,
      98,   110,   106,   107,   108,    95,   110,    97,   645,   613,
     315,   316,   317,    83,   319,    85,     1,    87,    93,    94,
       5,    21,    22,    23,    24,    56,    57,    58,    59,    51,
     278,    89,    90,    91,    92,    56,    57,    58,   286,   287,
     288,   289,   308,   128,   129,   293,   131,   295,   126,   127,
     128,   299,    95,   301,    97,   303,   693,    35,   100,   307,
     308,   100,    95,   607,    97,   147,   314,   315,   316,   317,
     318,   319,   709,    89,    90,    91,    95,    94,    97,   327,
      95,    93,    97,   331,    93,   146,   334,    94,   336,   355,
     146,     5,   278,   291,   342,   343,   362,   297,   695,   294,
     348,   349,   350,   707,   305,   697,   354,   355,   359,   321,
     339,   345,   352,   361,   362,   369,   312,   365,   366,   376,
     383,   396,   390,   371,   372,   373,   374,   411,   418,   437,
     378,   400,   398,   442,   425,   434,   455,   448,   430,   404,
     388,    47,    -1,    -1,    -1,   393,    -1,    -1,    -1,    -1,
     398,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   406,    -1,
      -1,   705,   431,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   440,    -1,    -1,    -1,   444,    -1,   446,    -1,    -1,
       3,    -1,   430,     6,   453,    -1,    -1,    -1,    -1,    -1,
      -1,    14,    -1,    16,    -1,    18,    -1,    20,    -1,    -1,
      -1,    -1,   450,    -1,   452,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,
      53,   497,    55,    -1,    -1,    -1,    -1,    60,    61,    62,
      -1,    -1,   490,    66,    -1,    -1,   494,    -1,    -1,   497,
      -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,   517,
      -1,    -1,    -1,    96,   522,    -1,    99,    -1,   101,   102,
      -1,    -1,   105,    -1,    -1,    -1,   109,    -1,   111,   112,
      -1,    -1,    -1,    -1,   117,    -1,    -1,    -1,   121,    -1,
      -1,    -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,   132,
     558,    -1,    -1,    -1,    -1,   138,    -1,   140,   141,   142,
     143,    -1,   145,   146,   147,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,   613,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   679,    -1,    -1,   682,   683,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   699,    -1,   701,   702,    -1,    -1,    -1,    -1,   707,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   716,    -1,
      -1,    -1,    -1,    -1,    -1,   723,    -1,   725,   726,   727,
     728,   729,   730,   731,   732,   733,   734,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     3,
      -1,   147,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    16,    -1,    18,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,    53,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    99,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,    -1,   109,    -1,   111,    -1,    -1,
      -1,    -1,   116,   117,    -1,    -1,    -1,   121,    -1,    -1,
      -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,   132,    -1,
      -1,    -1,    -1,    -1,   138,    -1,   140,   141,   142,   143,
      -1,   145,   146,   147,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,    18,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    46,    -1,    48,
      -1,    50,    -1,    -1,    53,    -1,    55,    -1,    -1,    -1,
      -1,    60,    61,    62,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      79,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      99,    -1,   101,   102,    -1,    -1,   105,    -1,    -1,    -1,
     109,    -1,   111,    -1,    -1,    -1,    -1,    -1,   117,    -1,
      -1,    -1,   121,    -1,    -1,    -1,   125,    -1,    -1,    -1,
      -1,    -1,    -1,   132,    -1,    -1,    -1,    -1,    -1,   138,
      -1,   140,   141,   142,   143,    -1,   145,   146,   147,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    16,    -1,    18,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,    53,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    62,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    79,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    99,    -1,   101,   102,    -1,
      -1,   105,    -1,    -1,    -1,   109,    -1,   111,    -1,    -1,
      -1,    -1,    -1,   117,    -1,    -1,    -1,   121,    -1,    -1,
      -1,   125,    -1,    -1,    -1,    -1,    -1,    -1,   132,    -1,
      -1,    -1,    -1,    -1,   138,    -1,   140,   141,    -1,    -1,
      -1,   145,   146,   147
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned short int
  vrml1_parser::yystos_[] =
  {
         0,   144,   149,     3,   150,   151,     0,     4,   284,   150,
       6,    14,    16,    18,    20,    28,    35,    44,    46,    48,
      50,    53,    55,    60,    61,    62,    66,    78,    79,    82,
      88,    96,    99,   101,   102,   105,   109,   111,   112,   117,
     121,   125,   132,   138,   140,   141,   142,   143,   145,   146,
     147,   151,   152,   153,   155,   156,   157,   158,   159,   162,
     166,   173,   175,   182,   186,   189,   191,   193,   195,   197,
     201,   205,   209,   213,   217,   221,   225,   232,   235,   243,
     247,   249,   251,   253,   257,   261,   265,   270,   274,   279,
     290,   299,   300,   304,   305,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   299,   301,   304,   306,
     284,   284,   284,   284,   284,   284,   113,   114,   115,   154,
     284,   284,   284,   284,   284,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   147,   309,   310,
     309,     5,   285,   155,   155,   155,   290,     7,     8,     9,
     163,   164,   165,     8,    11,    12,   167,   168,   169,    17,
     174,     8,    11,    17,   176,   177,   178,    21,    22,    23,
      24,   218,   219,   220,    27,    29,    30,    31,    32,    33,
     183,   184,   185,    37,   187,    45,   190,    47,   192,    49,
     194,    51,   196,    45,    47,    49,    52,    54,   198,   199,
     200,    56,    57,    58,   202,   203,   204,    56,    57,    58,
      59,   206,   207,   208,    21,    22,    23,    65,   210,   211,
     212,    21,    22,    23,    24,    63,    64,    65,   214,   215,
     216,    45,    47,    49,    54,   222,   223,   224,    67,    70,
      73,    76,   226,   227,   228,    37,   233,    54,    86,   244,
     245,   246,    83,    85,    87,   236,   237,   238,    95,    97,
      95,    97,    98,   248,   100,   250,   100,   252,   103,   104,
     254,   255,   256,   106,   107,   108,   110,   258,   259,   260,
     106,   107,   108,   110,   262,   263,   264,   116,   155,   160,
     161,   118,   119,   122,   124,   266,   267,   268,   126,   127,
     128,   271,   272,   273,   128,   129,   131,   275,   276,   277,
       7,   133,   135,   136,   280,   281,   282,   158,   290,   290,
     290,   290,   285,   165,   290,    10,    13,    15,    92,   170,
     172,   290,   285,   169,   290,   285,   290,    10,    92,   179,
     290,   285,   178,   290,   299,    25,    26,   140,   141,   286,
     290,   296,   285,   220,    96,   290,   291,    96,   300,   300,
     300,   291,   300,   285,   185,    34,    36,    38,    39,    40,
      41,    42,    43,   188,    35,   296,   285,   290,   302,   285,
     296,   285,   290,   303,   285,   296,   302,   296,   302,   296,
     285,   200,   296,   302,   290,   285,   204,   296,   302,   290,
     290,   285,   208,   290,   299,   286,   296,   285,   212,   290,
     299,   286,   296,   290,   290,   296,   285,   216,   290,   293,
     290,   293,   293,   285,   224,   290,    68,    72,    75,   229,
      71,    77,   230,    69,    74,   231,   285,   228,    34,    36,
      38,    39,    40,    41,    42,    43,   234,   285,   296,   291,
     285,   246,    89,    90,    91,    92,   239,   241,   290,    80,
      81,    84,   242,   285,   238,   299,   304,    96,   296,   297,
     285,   297,   285,    96,   293,   294,   285,   140,   141,   146,
     287,   287,   285,   256,    96,   287,   288,   288,   288,   288,
     285,   260,   288,   288,   288,   288,   285,   264,   287,   285,
     155,   304,   120,   123,   269,   287,   307,   269,   285,   267,
     296,   296,   304,   285,   273,   304,    90,   130,   278,   304,
     285,   277,   291,   134,   137,   139,   283,   290,   304,   285,
     282,   171,   172,    10,    13,    15,    19,   180,   181,   290,
     290,   292,   290,   290,   290,   240,   241,   296,   298,   293,
     295,   287,   289,   287,    93,    94,    93,    94,   290,    95,
      97,   290,   290,    93,    94,    95,    97,    95,    97,    95,
      97,   287,   171,   180,   290,   290,   290,   241,   296,   293,
     287,   146,   308,   290,   146,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  vrml1_parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned short int
  vrml1_parser::yyr1_[] =
  {
         0,   148,   149,   150,   150,   151,   152,   152,   152,   153,
     154,   154,   154,   155,   155,   155,   155,   156,   156,   157,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   159,   160,   160,   160,   161,
     162,   163,   163,   164,   164,   165,   165,   165,   166,   167,
     167,   168,   168,   169,   169,   169,   170,   170,   171,   171,
     172,   172,   172,   173,   174,   174,   175,   176,   176,   177,
     177,   178,   178,   178,   179,   179,   180,   180,   181,   181,
     181,   181,   182,   183,   183,   184,   184,   185,   185,   185,
     185,   185,   185,   186,   187,   187,   188,   188,   188,   188,
     188,   188,   188,   188,   189,   190,   190,   191,   192,   192,
     193,   194,   194,   195,   196,   196,   197,   198,   198,   199,
     199,   200,   200,   200,   200,   200,   201,   202,   202,   203,
     203,   204,   204,   204,   205,   206,   206,   207,   207,   208,
     208,   208,   208,   209,   210,   210,   211,   211,   212,   212,
     212,   212,   213,   214,   214,   215,   215,   216,   216,   216,
     216,   216,   216,   216,   217,   218,   218,   219,   219,   220,
     220,   220,   220,   221,   222,   222,   223,   223,   224,   224,
     224,   224,   225,   226,   226,   227,   227,   228,   228,   228,
     228,   229,   229,   229,   230,   230,   231,   231,   232,   233,
     233,   234,   234,   234,   234,   234,   234,   234,   234,   235,
     236,   236,   237,   237,   238,   238,   238,   239,   239,   240,
     240,   241,   241,   241,   242,   242,   242,   243,   244,   244,
     245,   245,   246,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   255,   256,   256,   257,   258,   259,   259,
     260,   260,   260,   260,   261,   262,   263,   263,   264,   264,
     264,   264,   265,   266,   267,   267,   268,   268,   268,   268,
     269,   269,   270,   271,   272,   272,   273,   273,   273,   274,
     275,   276,   276,   277,   277,   277,   278,   278,   279,   280,
     281,   281,   282,   282,   282,   282,   283,   283,   283,   284,
     285,   286,   286,   286,   286,   287,   287,   287,   288,   288,
     289,   289,   289,   290,   290,   290,   290,   291,   291,   292,
     292,   292,   293,   294,   294,   295,   295,   295,   296,   297,
     297,   298,   298,   298,   299,   300,   300,   301,   301,   301,
     302,   303,   304,   305,   305,   306,   306,   306,   307,   308,
     308,   309,   309,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  vrml1_parser::yyr2_[] =
  {
         0,     2,     2,     1,     2,     4,     0,     2,     1,     2,
       1,     1,     1,     1,     1,     2,     2,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     0,     2,     1,     2,
       4,     0,     1,     1,     2,     2,     2,     2,     4,     0,
       1,     1,     2,     2,     2,     2,     1,     3,     1,     3,
       1,     1,     1,     4,     0,     2,     4,     0,     1,     1,
       2,     2,     2,     2,     1,     3,     1,     3,     1,     1,
       1,     1,     4,     0,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     4,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     0,     2,     4,     0,     2,
       4,     0,     2,     4,     0,     2,     4,     0,     1,     1,
       2,     2,     2,     2,     2,     2,     4,     0,     1,     1,
       2,     2,     2,     2,     4,     0,     1,     1,     2,     2,
       2,     2,     2,     4,     0,     1,     1,     2,     2,     2,
       2,     2,     4,     0,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     4,     0,     1,     1,     2,     2,
       2,     2,     2,     4,     0,     1,     1,     2,     2,     2,
       2,     2,     4,     0,     1,     1,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     4,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       0,     1,     1,     2,     2,     2,     2,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     4,     0,     1,
       1,     2,     2,     2,     4,     2,     4,     2,     4,     2,
       4,     1,     1,     2,     2,     2,     4,     1,     1,     2,
       2,     2,     2,     2,     4,     1,     1,     2,     2,     2,
       2,     2,     4,     1,     1,     2,     2,     2,     2,     2,
       1,     1,     4,     1,     1,     2,     2,     2,     2,     4,
       1,     1,     2,     2,     2,     2,     1,     1,     4,     1,
       1,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     2,     1,     1,     1,     1,     1,     3,     1,
       3,     2,     2,     1,     3,     1,     3,     2,     3,     1,
       3,     1,     3,     2,     3,     1,     3,     1,     3,     2,
       4,    16,     1,     1,     3,     1,     3,     2,     4,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const vrml1_parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "KW_Separator",
  "KW_BRACKETOPEN", "KW_BRACKETCLOSE", "KW_Cube", "KW_width", "KW_height",
  "KW_depth", "KW_SIDES", "KW_parts", "KW_bottomRadius", "KW_BOTTOM",
  "KW_Cone", "KW_ALL", "KW_Sphere", "KW_radius", "KW_Cylinder", "KW_TOP",
  "KW_DirectionalLight", "KW_intensity", "KW_color", "KW_on",
  "KW_direction", "KW_FALSE", "KW_TRUE", "KW_transparency", "KW_Material",
  "KW_emissiveColor", "KW_ambientColor", "KW_specularColor",
  "KW_shininess", "KW_diffuseColor", "KW_OVERALL", "KW_MaterialBinding",
  "KW_PER_FACE", "KW_value", "KW_PER_VERTEX_INDEXED", "KW_PER_PART",
  "KW_PER_FACE_INDEXED", "KW_DEFAULT", "KW_PER_PART_INDEXED",
  "KW_PER_VERTEX", "KW_Translation", "KW_translation", "KW_Rotation",
  "KW_rotation", "KW_Scale", "KW_scaleFactor", "KW_MatrixTransform",
  "KW_matrix", "KW_scaleOrientation", "KW_Transform", "KW_center",
  "KW_OrthographicCamera", "KW_position", "KW_orientation",
  "KW_focalDistance", "KW_heightAngle", "KW_PerspectiveCamera",
  "KW_PointLight", "KW_SpotLight", "KW_cutOffAngle", "KW_dropOffRate",
  "KW_location", "KW_Texture2Transform", "KW_creaseAngle", "KW_CLOCKWISE",
  "KW_CONVEX", "KW_vertexOrdering", "KW_SOLID", "KW_COUNTERCLOCKWISE",
  "KW_shapeType", "KW_UNKNOWN_FACE_TYPE", "KW_UNKNOWN_ORDERING",
  "KW_faceType", "KW_UNKNOWN_SHAPE_TYPE", "KW_ShapeHints",
  "KW_NormalBinding", "KW_SANS", "KW_TYPEWRITER", "KW_LOD", "KW_style",
  "KW_SERIF", "KW_size", "KW_range", "KW_family", "KW_FontStyle",
  "KW_ITALIC", "KW_NONE", "KW_BOLD", "KW_LEFTPARENTHESIS",
  "KW_RIGHTPARENTHESIS", "KW_BAR", "KW_COMMA", "KW_SQUAREDBRACKETOPEN",
  "KW_SQUAREDBRACKETCLOSE", "KW_vector", "KW_Normal", "KW_point",
  "KW_Coordinate3", "KW_TextureCoordinate2", "KW_startIndex",
  "KW_numPoints", "KW_PointSet", "KW_textureCoordIndex", "KW_normalIndex",
  "KW_coordIndex", "KW_IndexedLineSet", "KW_materialIndex",
  "KW_IndexedFaceSet", "KW_renderCulling", "KW_OFF", "KW_AUTO", "KW_ON",
  "KW_whichChild", "KW_Switch", "KW_filename", "KW_wrapT", "KW_CLAMP",
  "KW_Texture2", "KW_image", "KW_REPEAT", "KW_wrapS", "KW_WWWInline",
  "KW_bboxCenter", "KW_bboxSize", "KW_name", "KW_map", "KW_POINT",
  "KW_description", "KW_WWWAnchor", "KW_justification", "KW_CENTER",
  "KW_spacing", "KW_string", "KW_RIGHT", "KW_AsciiText", "KW_LEFT",
  "KW_ZERO", "KW_ONE", "KW_DEF", "KW_USE", "KW_VRML_ID", "\"float\"",
  "\"integer\"", "\"string\"", "$accept", "start", "Body", "Separator",
  "Separator_Body", "renderCulling", "renderCulling_Enums",
  "Separator_Childs", "Separator_DEF", "Separator_USE", "Separator_Tokens",
  "Switch", "Switch_Body", "whichChild", "Cube", "Cube_Body",
  "Cube_Attributes", "Cube_Attribute", "Cone", "Cone_Body",
  "Cone_Attributes", "Cone_Attribute", "Cone_Parts", "Cone_Part_Mask",
  "Cone_Part", "Sphere", "Sphere_Body", "Cylinder", "Cylinder_Body",
  "Cylinder_Attributes", "Cylinder_Attribute", "Cylinder_Parts",
  "Cylinder_Part_Mask", "Cylinder_Part", "Material", "Material_Body",
  "Material_Attributes", "Material_Attribute", "MaterialBinding",
  "MaterialBinding_Body", "MaterialBinding_value", "Translation",
  "Translation_Body", "Rotation", "Rotation_Body", "Scale", "Scale_Body",
  "MatrixTransform", "MatrixTransform_Body", "Transform", "Transform_Body",
  "Transform_Attributes", "Transform_Attribute", "OrthographicCamera",
  "OrthographicCamera_Body", "OrthographicCamera_Attributes",
  "OrthographicCamera_Attribute", "PerspectiveCamera",
  "PerspectiveCamera_Body", "PerspectiveCamera_Attributes",
  "PerspectiveCamera_Attribute", "PointLight", "PointLight_Body",
  "PointLight_Attributes", "PointLight_Attribute", "SpotLight",
  "SpotLight_Body", "SpotLight_Attributes", "SpotLight_Attribute",
  "DirectionalLight", "DirectionalLight_Body",
  "DirectionalLight_Attributes", "DirectionalLight_Attribute",
  "Texture2Transform", "Texture2Transform_Body",
  "Texture2Transform_Attributes", "Texture2Transform_Attribute",
  "ShapeHints", "ShapeHints_Body", "ShapeHints_Attributes",
  "ShapeHints_Attribute", "vertexOrdering_value", "shapeType_value",
  "faceType_value", "NormalBinding", "NormalBinding_Body",
  "NormalBinding_value", "FontStyle", "FontStyle_Body",
  "FontStyle_Attributes", "FontStyle_Attribute", "style_bitmask",
  "style_bits", "style_values", "family_value", "LOD", "LOD_Body",
  "LOD_Attributes", "LOD_Attribute", "Normal", "Normal_Body",
  "Coordinate3", "Coordinate3_Body", "TextureCoordinate2",
  "TextureCoordinate2_Body", "PointSet", "PointSet_Body",
  "PointSet_Arguments", "PointSet_Argument", "IndexedLineSet",
  "IndexedLineSet_Body", "IndexedLineSet_Arguments",
  "IndexedLineSet_Argument", "IndexedFaceSet", "IndexedFaceSet_Body",
  "IndexedFaceSet_Arguments", "IndexedFaceSet_Argument", "Texture2",
  "Texture2_Body", "Texture2_Arguments", "Texture2_Argument",
  "Texture2_wrap", "WWWInline", "WWWInline_Body", "WWWInline_Arguments",
  "WWWInline_Argument", "WWWAnchor", "WWWAnchor_Body",
  "WWWAnchor_Arguments", "WWWAnchor_Argument", "WWWAnchor_map",
  "AsciiText", "AsciiText_Body", "AsciiText_Arguments",
  "AsciiText_Argument", "AsciiText_justification", "BracketOpen",
  "BracketClose", "SFBool", "SFLong", "MFLong", "MFLongs", "SFFloat",
  "MFFloat", "MFFloats", "SFVec2f", "MFVec2f", "MFVec2fs", "SFVec3f",
  "MFVec3f", "MFVec3fs", "SFColor", "MFColor", "MFColors", "SFRotation",
  "SFMatrix", "SFString", "MFString", "MFStrings", "SFImage", "Image_Body",
  "Identifier", "Keywords", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const vrml1_parser::rhs_number_type
  vrml1_parser::yyrhs_[] =
  {
       149,     0,    -1,   144,   150,    -1,   151,    -1,   151,   150,
      -1,     3,   284,   152,   285,    -1,    -1,   153,   155,    -1,
     155,    -1,   112,   154,    -1,   113,    -1,   115,    -1,   114,
      -1,   156,    -1,   157,    -1,   156,   155,    -1,   157,   155,
      -1,   142,   309,   158,    -1,   158,    -1,   143,   309,    -1,
     162,    -1,   166,    -1,   173,    -1,   175,    -1,   182,    -1,
     186,    -1,   189,    -1,   191,    -1,   193,    -1,   195,    -1,
     197,    -1,   201,    -1,   205,    -1,   209,    -1,   213,    -1,
     217,    -1,   221,    -1,   225,    -1,   232,    -1,   247,    -1,
     249,    -1,   251,    -1,   253,    -1,   257,    -1,   261,    -1,
     235,    -1,   243,    -1,   265,    -1,   270,    -1,   274,    -1,
     279,    -1,   151,    -1,   159,    -1,   300,    -1,   305,    -1,
     117,   284,   160,   285,    -1,    -1,   161,   155,    -1,   155,
      -1,   116,   287,    -1,     6,   284,   163,   285,    -1,    -1,
     164,    -1,   165,    -1,   164,   165,    -1,     7,   290,    -1,
       8,   290,    -1,     9,   290,    -1,    14,   284,   167,   285,
      -1,    -1,   168,    -1,   169,    -1,   168,   169,    -1,    11,
     170,    -1,    12,   290,    -1,     8,   290,    -1,   172,    -1,
      92,   171,    93,    -1,   172,    -1,   172,    94,   171,    -1,
      10,    -1,    13,    -1,    15,    -1,    16,   284,   174,   285,
      -1,    -1,    17,   290,    -1,    18,   284,   176,   285,    -1,
      -1,   177,    -1,   178,    -1,   177,   178,    -1,    11,   179,
      -1,    17,   290,    -1,     8,   290,    -1,    10,    -1,    92,
     180,    93,    -1,   181,    -1,   181,    94,   180,    -1,    10,
      -1,    19,    -1,    13,    -1,    15,    -1,    28,   284,   183,
     285,    -1,    -1,   184,    -1,   185,    -1,   184,   185,    -1,
      30,   300,    -1,    33,   300,    -1,    31,   300,    -1,    29,
     300,    -1,    32,   291,    -1,    27,   291,    -1,    35,   284,
     187,    35,    -1,    -1,    37,   188,    -1,    41,    -1,    34,
      -1,    39,    -1,    42,    -1,    36,    -1,    40,    -1,    43,
      -1,    38,    -1,    44,   284,   190,   285,    -1,    -1,    45,
     296,    -1,    46,   284,   192,   285,    -1,    -1,    47,   302,
      -1,    48,   284,   194,   285,    -1,    -1,    49,   296,    -1,
      50,   284,   196,   285,    -1,    -1,    51,   303,    -1,    53,
     284,   198,   285,    -1,    -1,   199,    -1,   200,    -1,   199,
     200,    -1,    45,   296,    -1,    47,   302,    -1,    49,   296,
      -1,    52,   302,    -1,    54,   296,    -1,    55,   284,   202,
     285,    -1,    -1,   203,    -1,   204,    -1,   203,   204,    -1,
      56,   296,    -1,    57,   302,    -1,    58,   290,    -1,    60,
     284,   206,   285,    -1,    -1,   207,    -1,   208,    -1,   207,
     208,    -1,    56,   296,    -1,    57,   302,    -1,    58,   290,
      -1,    59,   290,    -1,    61,   284,   210,   285,    -1,    -1,
     211,    -1,   212,    -1,   211,   212,    -1,    23,   286,    -1,
      21,   290,    -1,    22,   299,    -1,    65,   296,    -1,    62,
     284,   214,   285,    -1,    -1,   215,    -1,   216,    -1,   215,
     216,    -1,    23,   286,    -1,    21,   290,    -1,    22,   299,
      -1,    65,   296,    -1,    24,   296,    -1,    64,   290,    -1,
      63,   290,    -1,    20,   284,   218,   285,    -1,    -1,   219,
      -1,   220,    -1,   219,   220,    -1,    23,   286,    -1,    21,
     290,    -1,    22,   299,    -1,    24,   296,    -1,    66,   284,
     222,   285,    -1,    -1,   223,    -1,   224,    -1,   223,   224,
      -1,    45,   293,    -1,    47,   290,    -1,    49,   293,    -1,
      54,   293,    -1,    78,   284,   226,   285,    -1,    -1,   227,
      -1,   228,    -1,   227,   228,    -1,    70,   229,    -1,    73,
     230,    -1,    76,   231,    -1,    67,   290,    -1,    75,    -1,
      68,    -1,    72,    -1,    77,    -1,    71,    -1,    74,    -1,
      69,    -1,    79,   284,   233,   285,    -1,    -1,    37,   234,
      -1,    41,    -1,    34,    -1,    39,    -1,    42,    -1,    36,
      -1,    40,    -1,    43,    -1,    38,    -1,    88,   284,   236,
     285,    -1,    -1,   237,    -1,   238,    -1,   237,   238,    -1,
      85,   290,    -1,    87,   242,    -1,    83,   239,    -1,   241,
      -1,    92,   240,    93,    -1,   241,    -1,   240,    94,   241,
      -1,    90,    -1,    91,    -1,    89,    -1,    84,    -1,    80,
      -1,    81,    -1,    82,   284,   244,   285,    -1,    -1,   245,
      -1,   246,    -1,   245,   246,    -1,    86,   291,    -1,    54,
     296,    -1,    99,   284,   248,   285,    -1,    98,   297,    -1,
     101,   284,   250,   285,    -1,   100,   297,    -1,   102,   284,
     252,   285,    -1,   100,   294,    -1,   105,   284,   254,   285,
      -1,   255,    -1,   256,    -1,   255,   256,    -1,   103,   287,
      -1,   104,   287,    -1,   109,   284,   258,   285,    -1,   259,
      -1,   260,    -1,   259,   260,    -1,   108,   288,    -1,   110,
     288,    -1,   107,   288,    -1,   106,   288,    -1,   111,   284,
     262,   285,    -1,   263,    -1,   264,    -1,   263,   264,    -1,
     108,   288,    -1,   110,   288,    -1,   107,   288,    -1,   106,
     288,    -1,   121,   284,   266,   285,    -1,   267,    -1,   268,
      -1,   268,   267,    -1,   118,   304,    -1,   122,   307,    -1,
     124,   269,    -1,   119,   269,    -1,   123,    -1,   120,    -1,
     125,   284,   271,   285,    -1,   272,    -1,   273,    -1,   272,
     273,    -1,   128,   304,    -1,   127,   296,    -1,   126,   296,
      -1,   132,   284,   275,   285,    -1,   276,    -1,   277,    -1,
     276,   277,    -1,   128,   304,    -1,   131,   304,    -1,   129,
     278,    -1,    90,    -1,   130,    -1,   138,   284,   280,   285,
      -1,   281,    -1,   282,    -1,   281,   282,    -1,   136,   304,
      -1,   135,   290,    -1,   133,   283,    -1,     7,   291,    -1,
     139,    -1,   134,    -1,   137,    -1,     4,    -1,     5,    -1,
      25,    -1,    26,    -1,   140,    -1,   141,    -1,   140,    -1,
     141,    -1,   146,    -1,   287,    -1,    96,   289,    97,    -1,
     287,    -1,   289,    95,   287,    -1,   289,    95,    -1,   145,
      -1,   146,    -1,   140,    -1,   141,    -1,   290,    -1,    96,
     292,    97,    -1,   290,    -1,   292,    95,   290,    -1,   292,
      95,    -1,   290,   290,    -1,   293,    -1,    96,   295,    97,
      -1,   293,    -1,   295,    95,   293,    -1,   295,    95,    -1,
     290,   290,   290,    -1,   296,    -1,    96,   298,    97,    -1,
     296,    -1,   298,    95,   296,    -1,   298,    95,    -1,   290,
     290,   290,    -1,   299,    -1,    96,   301,    97,    -1,   299,
      -1,   301,    95,   299,    -1,   301,    95,    -1,   290,   290,
     290,   290,    -1,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   290,   290,   290,    -1,
     147,    -1,   304,    -1,    96,   306,    97,    -1,   304,    -1,
     306,    95,   304,    -1,   306,    95,    -1,   287,   287,   287,
     308,    -1,   146,    -1,   308,   146,    -1,   147,    -1,   310,
      -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,     7,
      -1,     8,    -1,     9,    -1,    10,    -1,    11,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,    17,
      -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,    22,
      -1,    23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,
      -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,    32,
      -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,    37,
      -1,    38,    -1,    39,    -1,    40,    -1,    41,    -1,    42,
      -1,    43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,
      -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,    53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,
      -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,    62,
      -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,    67,
      -1,    68,    -1,    69,    -1,    70,    -1,    71,    -1,    72,
      -1,    73,    -1,    74,    -1,    75,    -1,    76,    -1,    77,
      -1,    78,    -1,    79,    -1,    80,    -1,    88,    -1,    81,
      -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,
      -1,    87,    -1,    89,    -1,    90,    -1,    91,    -1,    92,
      -1,    93,    -1,    94,    -1,    95,    -1,    96,    -1,    97,
      -1,    98,    -1,    99,    -1,   100,    -1,   101,    -1,   102,
      -1,   103,    -1,   104,    -1,   105,    -1,   106,    -1,   107,
      -1,   108,    -1,   109,    -1,   110,    -1,   111,    -1,   112,
      -1,   113,    -1,   114,    -1,   115,    -1,   116,    -1,   117,
      -1,   118,    -1,   119,    -1,   120,    -1,   121,    -1,   122,
      -1,   123,    -1,   124,    -1,   125,    -1,   126,    -1,   127,
      -1,   128,    -1,   129,    -1,   130,    -1,   131,    -1,   132,
      -1,   133,    -1,   134,    -1,   135,    -1,   136,    -1,   137,
      -1,   138,    -1,   139,    -1,   140,    -1,   141,    -1,   142,
      -1,   143,    -1,   144,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  vrml1_parser::yyprhs_[] =
  {
         0,     0,     3,     6,     8,    11,    16,    17,    20,    22,
      25,    27,    29,    31,    33,    35,    38,    41,    45,    47,
      50,    52,    54,    56,    58,    60,    62,    64,    66,    68,
      70,    72,    74,    76,    78,    80,    82,    84,    86,    88,
      90,    92,    94,    96,    98,   100,   102,   104,   106,   108,
     110,   112,   114,   116,   118,   120,   125,   126,   129,   131,
     134,   139,   140,   142,   144,   147,   150,   153,   156,   161,
     162,   164,   166,   169,   172,   175,   178,   180,   184,   186,
     190,   192,   194,   196,   201,   202,   205,   210,   211,   213,
     215,   218,   221,   224,   227,   229,   233,   235,   239,   241,
     243,   245,   247,   252,   253,   255,   257,   260,   263,   266,
     269,   272,   275,   278,   283,   284,   287,   289,   291,   293,
     295,   297,   299,   301,   303,   308,   309,   312,   317,   318,
     321,   326,   327,   330,   335,   336,   339,   344,   345,   347,
     349,   352,   355,   358,   361,   364,   367,   372,   373,   375,
     377,   380,   383,   386,   389,   394,   395,   397,   399,   402,
     405,   408,   411,   414,   419,   420,   422,   424,   427,   430,
     433,   436,   439,   444,   445,   447,   449,   452,   455,   458,
     461,   464,   467,   470,   473,   478,   479,   481,   483,   486,
     489,   492,   495,   498,   503,   504,   506,   508,   511,   514,
     517,   520,   523,   528,   529,   531,   533,   536,   539,   542,
     545,   548,   550,   552,   554,   556,   558,   560,   562,   567,
     568,   571,   573,   575,   577,   579,   581,   583,   585,   587,
     592,   593,   595,   597,   600,   603,   606,   609,   611,   615,
     617,   621,   623,   625,   627,   629,   631,   633,   638,   639,
     641,   643,   646,   649,   652,   657,   660,   665,   668,   673,
     676,   681,   683,   685,   688,   691,   694,   699,   701,   703,
     706,   709,   712,   715,   718,   723,   725,   727,   730,   733,
     736,   739,   742,   747,   749,   751,   754,   757,   760,   763,
     766,   768,   770,   775,   777,   779,   782,   785,   788,   791,
     796,   798,   800,   803,   806,   809,   812,   814,   816,   821,
     823,   825,   828,   831,   834,   837,   840,   842,   844,   846,
     848,   850,   852,   854,   856,   858,   860,   862,   864,   866,
     870,   872,   876,   879,   881,   883,   885,   887,   889,   893,
     895,   899,   902,   905,   907,   911,   913,   917,   920,   924,
     926,   930,   932,   936,   939,   943,   945,   949,   951,   955,
     958,   963,   980,   982,   984,   988,   990,   994,   997,  1002,
    1004,  1007,  1009,  1011,  1013,  1015,  1017,  1019,  1021,  1023,
    1025,  1027,  1029,  1031,  1033,  1035,  1037,  1039,  1041,  1043,
    1045,  1047,  1049,  1051,  1053,  1055,  1057,  1059,  1061,  1063,
    1065,  1067,  1069,  1071,  1073,  1075,  1077,  1079,  1081,  1083,
    1085,  1087,  1089,  1091,  1093,  1095,  1097,  1099,  1101,  1103,
    1105,  1107,  1109,  1111,  1113,  1115,  1117,  1119,  1121,  1123,
    1125,  1127,  1129,  1131,  1133,  1135,  1137,  1139,  1141,  1143,
    1145,  1147,  1149,  1151,  1153,  1155,  1157,  1159,  1161,  1163,
    1165,  1167,  1169,  1171,  1173,  1175,  1177,  1179,  1181,  1183,
    1185,  1187,  1189,  1191,  1193,  1195,  1197,  1199,  1201,  1203,
    1205,  1207,  1209,  1211,  1213,  1215,  1217,  1219,  1221,  1223,
    1225,  1227,  1229,  1231,  1233,  1235,  1237,  1239,  1241,  1243,
    1245,  1247,  1249,  1251,  1253,  1255,  1257,  1259,  1261,  1263,
    1265,  1267,  1269,  1271,  1273,  1275,  1277,  1279,  1281,  1283,
    1285,  1287,  1289,  1291,  1293
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  vrml1_parser::yyrline_[] =
  {
         0,   196,   196,   199,   200,   203,   206,   207,   208,   211,
     214,   215,   216,   221,   222,   223,   224,   227,   228,   231,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   273,   276,   277,   278,   282,
     287,   290,   291,   294,   295,   298,   299,   300,   305,   308,
     309,   312,   313,   316,   317,   318,   321,   322,   325,   326,
     329,   330,   331,   336,   339,   340,   345,   348,   349,   352,
     353,   356,   357,   358,   361,   362,   365,   366,   369,   370,
     371,   372,   377,   380,   381,   384,   385,   388,   389,   390,
     391,   392,   393,   398,   401,   402,   405,   406,   407,   408,
     409,   410,   411,   412,   417,   420,   421,   426,   429,   430,
     435,   437,   438,   443,   446,   447,   452,   455,   456,   459,
     460,   463,   464,   465,   466,   467,   472,   475,   476,   479,
     480,   483,   484,   485,   490,   493,   494,   497,   498,   501,
     502,   503,   504,   509,   511,   512,   515,   516,   519,   520,
     521,   522,   527,   530,   531,   534,   535,   538,   539,   540,
     541,   542,   543,   544,   549,   552,   553,   556,   557,   560,
     561,   562,   563,   568,   571,   572,   575,   576,   579,   580,
     581,   582,   587,   590,   591,   594,   595,   598,   599,   600,
     601,   604,   605,   606,   609,   610,   613,   614,   619,   622,
     623,   626,   627,   628,   629,   630,   631,   632,   633,   638,
     641,   642,   645,   646,   649,   650,   651,   654,   655,   658,
     659,   662,   663,   664,   667,   668,   669,   674,   677,   678,
     681,   682,   685,   686,   691,   694,   699,   702,   707,   710,
     715,   718,   721,   722,   725,   726,   731,   734,   737,   738,
     741,   742,   743,   744,   749,   752,   755,   756,   759,   760,
     761,   762,   768,   771,   774,   775,   778,   779,   780,   781,
     784,   785,   790,   793,   796,   797,   800,   801,   802,   807,
     810,   813,   814,   817,   818,   819,   822,   823,   828,   831,
     834,   835,   838,   839,   840,   841,   844,   845,   846,   854,
     857,   862,   863,   864,   865,   868,   869,   870,   873,   874,
     877,   878,   879,   882,   883,   884,   885,   888,   889,   892,
     893,   894,   897,   900,   901,   904,   905,   906,   910,   914,
     915,   918,   919,   920,   923,   926,   927,   930,   931,   932,
     935,   938,   941,   944,   945,   948,   949,   950,   953,   956,
     957,   960,   961,   964,   965,   966,   967,   968,   969,   970,
     971,   972,   973,   974,   975,   976,   977,   978,   979,   980,
     981,   982,   983,   984,   985,   986,   987,   988,   989,   990,
     991,   992,   993,   994,   995,   996,   997,   998,   999,  1000,
    1001,  1002,  1003,  1004,  1005,  1006,  1007,  1008,  1009,  1010,
    1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,
    1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,
    1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,
    1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,  1049,  1050,
    1051,  1052,  1053,  1054,  1055,  1056,  1057,  1058,  1059,  1060,
    1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,  1070,
    1071,  1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,  1080,
    1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,
    1091,  1092,  1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,
    1101,  1102,  1103,  1104,  1105
  };

  // Print the state stack on the debug stream.
  void
  vrml1_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  vrml1_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "), ";
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  vrml1_parser::token_number_type
  vrml1_parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int vrml1_parser::yyeof_ = 0;
  const int vrml1_parser::yylast_ = 1303;
  const int vrml1_parser::yynnts_ = 163;
  const int vrml1_parser::yyempty_ = -2;
  const int vrml1_parser::yyfinal_ = 6;
  const int vrml1_parser::yyterror_ = 1;
  const int vrml1_parser::yyerrcode_ = 256;
  const int vrml1_parser::yyntokens_ = 148;

  const unsigned int vrml1_parser::yyuser_token_number_max_ = 402;
  const vrml1_parser::token_number_type vrml1_parser::yyundef_token_ = 2;

} // namespace vrml1

#line 1108 "./vrml1-parser.yy"


void vrml1::vrml1_parser::error (const vrml1::vrml1_parser::location_type& l,
                               const std::string& m) {
	driver.error (l, m);
}


