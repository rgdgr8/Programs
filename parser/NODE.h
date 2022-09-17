#ifndef NODE_H
#define __main__ 128
#define __if__ 129
#define __else__ 130
#define __for__ 131
#define __id__ 132
#define __intlit__ 133
#define __charlit__ 134
#define __eq__ 135
#define __type__ 136
#define __int__ 137
#define __char__ 138
#define __stringlit__ 139
#define __AUGMENTED_START__ 256
#define __PROGRAM__ 257
#define __HEAD__ 258
#define __ARGS__ 259
#define __BODY__ 260
#define __TYPE__ 261
#define __V__ 262
#define __STMT__ 263
#define __DECL__ 264
#define __IF__ 265
#define __SIMPLE__ 266
#define __FOR__ 267
#define __FOR_HEAD__ 268
#define __SIMPLES__ 269
#define __EXP__ 270
#define __FORSTMTS__ 271
#define __D__ 272
#define __BR__ 273
#define __DBR__ 274
#define __DBR2__ 275
#define __BV__ 276
#define __BV2__ 277
#define __A__ 278
#define __R__ 279
#define __T__ 280
#define __F__ 281
#define __POW__ 282
#define __IF_CL__ 283
typedef struct
{
	int sym;
	union
	{
		struct
		{
		} main_node;
		struct
		{
		} if_node;
		struct
		{
		} else_node;
		struct
		{
		} for_node;
		struct
		{
			char name[20];
		} id_node;
		struct
		{
			int value;
		} intlit_node;
		struct
		{
		} charlit_node;
		struct
		{
		} stringlit_node;
		struct
		{
		} eq_node;
		struct
		{
			int basetype;
			int dim;
		} type_node;
		struct
		{
		} int_node;
		struct
		{
		} char_node;
		struct
		{
		} PROGRAM_node;
		struct
		{
		} HEAD_node;
		struct
		{
		} ARGS_node;
		struct
		{
		} BODY_node;
		struct
		{
		} TYPE_node;
		struct
		{
		} V_node;
		struct
		{
		} STMT_node;
		struct
		{
		} DECL_node;
		struct
		{
		} IF_node;
		struct
		{
		} SIMPLE_node;
		struct
		{
		} FOR_node;
		struct
		{
		} FOR_HEAD_node;
		struct
		{
		} SIMPLES_node;
		struct
		{
		} EXP_node;
		struct
		{
		} FORSTMTS_node;
		struct
		{
		} D_node;
		struct
		{
		} BR_node;
		struct
		{
		} DBR_node;
		struct
		{
		} DBR2_node;
		struct
		{
		} BV_node;
		struct
		{
		} BV2_node;
		struct
		{
		} A_node;
		struct
		{
		} R_node;
		struct
		{
		} T_node;
		struct
		{
		} F_node;
		struct
		{
		} POW_node;
		struct
		{
		} IF_CL_node;
	} info;
} node;
extern const char *spec_ter_mapping[];
extern const char *nonter_mapping[];
#ifdef NODE_H_DEFINE_HERE
const char *spec_ter_mapping[] = {
	"main",
	"if",
	"else",
	"for",
	"id",
	"intlit",
	"charlit",
	"eq",
	"type",
	"int",
	"char",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
};
const char *nonter_mapping[] = {
	"AUGMENTED_START",
	"PROGRAM",
	"HEAD",
	"ARGS",
	"BODY",
	"TYPE",
	"V",
	"STMT",
	"DECL",
	"IF",
	"SIMPLE",
	"FOR",
	"FOR_HEAD",
	"SIMPLES",
	"EXP",
	"FORSTMTS",
	"D",
	"BR",
	"DBR",
	"DBR2",
	"BV",
	"BV2",
	"A",
	"R",
	"T",
	"F",
	"POW",
	"IF_CL",
};
#endif
#endif
#define NODE_H
