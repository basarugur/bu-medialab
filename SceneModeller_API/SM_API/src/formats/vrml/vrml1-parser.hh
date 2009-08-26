/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison LALR(1) parsers in C++

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

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H

#include <string>
#include <iostream>
#include "stack.hh"

namespace vrml1
{
  class position;
  class location;
}

/* First part of user declarations.  */
#line 7 "./vrml1-parser.yy"

#include <string>


namespace vrml1 {
	class Driver;
}


/* Line 35 of lalr1.cc.  */
#line 63 "./vrml1-parser.hh"

#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
do {							\
  if (N)						\
    {							\
      (Current).begin = (Rhs)[1].begin;			\
      (Current).end   = (Rhs)[N].end;			\
    }							\
  else							\
    {							\
      (Current).begin = (Current).end = (Rhs)[0].end;	\
    }							\
} while (false)
#endif

namespace vrml1
{

  /// A Bison parser.
  class vrml1_parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
#line 32 "./vrml1-parser.yy"
{
	int ival;
	float fval;
	std::string *sval;
}
/* Line 35 of lalr1.cc.  */
#line 121 "./vrml1-parser.hh"
	;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
   enum yytokentype {
     END = 0,
     KW_Separator = 258,
     KW_BRACKETOPEN = 259,
     KW_BRACKETCLOSE = 260,
     KW_Cube = 261,
     KW_width = 262,
     KW_height = 263,
     KW_depth = 264,
     KW_SIDES = 265,
     KW_parts = 266,
     KW_bottomRadius = 267,
     KW_BOTTOM = 268,
     KW_Cone = 269,
     KW_ALL = 270,
     KW_Sphere = 271,
     KW_radius = 272,
     KW_Cylinder = 273,
     KW_TOP = 274,
     KW_DirectionalLight = 275,
     KW_intensity = 276,
     KW_color = 277,
     KW_on = 278,
     KW_direction = 279,
     KW_FALSE = 280,
     KW_TRUE = 281,
     KW_transparency = 282,
     KW_Material = 283,
     KW_emissiveColor = 284,
     KW_ambientColor = 285,
     KW_specularColor = 286,
     KW_shininess = 287,
     KW_diffuseColor = 288,
     KW_OVERALL = 289,
     KW_MaterialBinding = 290,
     KW_PER_FACE = 291,
     KW_value = 292,
     KW_PER_VERTEX_INDEXED = 293,
     KW_PER_PART = 294,
     KW_PER_FACE_INDEXED = 295,
     KW_DEFAULT = 296,
     KW_PER_PART_INDEXED = 297,
     KW_PER_VERTEX = 298,
     KW_Translation = 299,
     KW_translation = 300,
     KW_Rotation = 301,
     KW_rotation = 302,
     KW_Scale = 303,
     KW_scaleFactor = 304,
     KW_MatrixTransform = 305,
     KW_matrix = 306,
     KW_scaleOrientation = 307,
     KW_Transform = 308,
     KW_center = 309,
     KW_OrthographicCamera = 310,
     KW_position = 311,
     KW_orientation = 312,
     KW_focalDistance = 313,
     KW_heightAngle = 314,
     KW_PerspectiveCamera = 315,
     KW_PointLight = 316,
     KW_SpotLight = 317,
     KW_cutOffAngle = 318,
     KW_dropOffRate = 319,
     KW_location = 320,
     KW_Texture2Transform = 321,
     KW_creaseAngle = 322,
     KW_CLOCKWISE = 323,
     KW_CONVEX = 324,
     KW_vertexOrdering = 325,
     KW_SOLID = 326,
     KW_COUNTERCLOCKWISE = 327,
     KW_shapeType = 328,
     KW_UNKNOWN_FACE_TYPE = 329,
     KW_UNKNOWN_ORDERING = 330,
     KW_faceType = 331,
     KW_UNKNOWN_SHAPE_TYPE = 332,
     KW_ShapeHints = 333,
     KW_NormalBinding = 334,
     KW_SANS = 335,
     KW_TYPEWRITER = 336,
     KW_LOD = 337,
     KW_style = 338,
     KW_SERIF = 339,
     KW_size = 340,
     KW_range = 341,
     KW_family = 342,
     KW_FontStyle = 343,
     KW_ITALIC = 344,
     KW_NONE = 345,
     KW_BOLD = 346,
     KW_LEFTPARENTHESIS = 347,
     KW_RIGHTPARENTHESIS = 348,
     KW_BAR = 349,
     KW_COMMA = 350,
     KW_SQUAREDBRACKETOPEN = 351,
     KW_SQUAREDBRACKETCLOSE = 352,
     KW_vector = 353,
     KW_Normal = 354,
     KW_point = 355,
     KW_Coordinate3 = 356,
     KW_TextureCoordinate2 = 357,
     KW_startIndex = 358,
     KW_numPoints = 359,
     KW_PointSet = 360,
     KW_textureCoordIndex = 361,
     KW_normalIndex = 362,
     KW_coordIndex = 363,
     KW_IndexedLineSet = 364,
     KW_materialIndex = 365,
     KW_IndexedFaceSet = 366,
     KW_renderCulling = 367,
     KW_OFF = 368,
     KW_AUTO = 369,
     KW_ON = 370,
     KW_whichChild = 371,
     KW_Switch = 372,
     KW_filename = 373,
     KW_wrapT = 374,
     KW_CLAMP = 375,
     KW_Texture2 = 376,
     KW_image = 377,
     KW_REPEAT = 378,
     KW_wrapS = 379,
     KW_WWWInline = 380,
     KW_bboxCenter = 381,
     KW_bboxSize = 382,
     KW_name = 383,
     KW_map = 384,
     KW_POINT = 385,
     KW_description = 386,
     KW_WWWAnchor = 387,
     KW_justification = 388,
     KW_CENTER = 389,
     KW_spacing = 390,
     KW_string = 391,
     KW_RIGHT = 392,
     KW_AsciiText = 393,
     KW_LEFT = 394,
     KW_ZERO = 395,
     KW_ONE = 396,
     KW_DEF = 397,
     KW_USE = 398,
     KW_VRML_ID = 399,
     TYPE_FLOAT = 400,
     TYPE_INTEGER = 401,
     TYPE_STRING = 402
   };

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    vrml1_parser (vrml1::Driver& driver_yyarg);
    virtual ~vrml1_parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the look-ahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if YYDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
#endif /* ! YYDEBUG */


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const short int yypact_ninf_;

    /// For a state, default rule to reduce.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned short int yydefact_[];

    static const short int yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const unsigned short int yytable_[];
    static const signed char yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned short int yystos_[];

    /// For a rule, its LHS.
    static const unsigned short int yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[];

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif

#if YYERROR_VERBOSE
    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    virtual std::string yytnamerr_ (const char *n);
#endif

#if YYDEBUG
    /// A type to store symbol numbers and -1.
    typedef short int rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned short int yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned short int yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;


    /* User arguments.  */
    vrml1::Driver& driver;
  };
}


#endif /* ! defined PARSER_HEADER_H */
