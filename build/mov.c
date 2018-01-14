#include "movfuscator.c"
	/* this is the crudest hack here.  there was a recurring issue in which the
	 * compiler was trashing regs that it needed; haven't figured out if it's my
	 * bug or theirs.  issue arises when compiler tries to reuse dag nodes
	 * incorrectly.  we can modify the generator in src/gen.c to force mayrecalc
	 * to always return 0 to fix the issue.  or, to avoid modifying the lcc
	 * source, we can trick the compiler into not recognizing reusable
	 * components - lburg.c calls mayrecalc when it identifies INDIR(VREG)'s.
	 * by separating INDIR from VREG in the rules, we can prevent it from trying
	 * to recalculate anything. */
	//TODO: investigate this more
	//TODO: you may have luck disabling temporaries by setting tmask to 0
	//TODO: just patch this in lcc, we have to do that in other places anyway
/*
reg:  INDIRI1(VREGP)            "\n"
reg:  INDIRU1(VREGP)            "\n"
reg:  INDIRI4(VREGP)            "\n"
reg:  INDIRP4(VREGP)            "\n"
reg:  INDIRU4(VREGP)            "\n"
freg: INDIRF4(VREGP)            "\n"
*/
	/* these rules prevent an infinite loop in register spilling, by allowing a
	 * register spill to occur with fewer instructions than it otherwise would */
/*
generated at Sun Jan 14 20:28:00 2018
by $Id$
*/
static void _kids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);
static void _label(NODEPTR_TYPE);
static int _rule(void*, int);

#define _stmt_NT 1
#define _vr_NT 2
#define _reg_NT 3
#define _freg_NT 4
#define _freg8_NT 5
#define _cnst_NT 6
#define _saddr_NT 7
#define _memb_NT 8
#define _jaddr_NT 9

static char *_ntname[] = {
	0,
	"stmt",
	"vr",
	"reg",
	"freg",
	"freg8",
	"cnst",
	"saddr",
	"memb",
	"jaddr",
	0
};

struct _state {
	short cost[10];
	struct {
		unsigned int _stmt:7;
		unsigned int _vr:1;
		unsigned int _reg:7;
		unsigned int _freg:4;
		unsigned int _freg8:4;
		unsigned int _cnst:3;
		unsigned int _saddr:1;
		unsigned int _memb:1;
		unsigned int _jaddr:2;
	} rule;
};

static short _nts_0[] = { 0 };
static short _nts_1[] = { _vr_NT, 0 };
static short _nts_2[] = { _reg_NT, 0 };
static short _nts_3[] = { _freg_NT, 0 };
static short _nts_4[] = { _freg8_NT, 0 };
static short _nts_5[] = { _cnst_NT, 0 };
static short _nts_6[] = { _reg_NT, _reg_NT, 0 };
static short _nts_7[] = { _saddr_NT, _reg_NT, 0 };
static short _nts_8[] = { _saddr_NT, _freg_NT, 0 };
static short _nts_9[] = { _saddr_NT, _freg8_NT, 0 };
static short _nts_10[] = { _reg_NT, _memb_NT, 0 };
static short _nts_11[] = { _memb_NT, 0 };
static short _nts_12[] = { _jaddr_NT, 0 };
static short _nts_13[] = { _reg_NT, _freg_NT, 0 };
static short _nts_14[] = { _reg_NT, _freg8_NT, 0 };
static short _nts_15[] = { _freg_NT, _freg_NT, 0 };
static short _nts_16[] = { _freg8_NT, _freg8_NT, 0 };

static short *_nts[] = {
	0,	/* 0 */
	_nts_0,	/* 1 */
	_nts_1,	/* 2 */
	_nts_1,	/* 3 */
	_nts_1,	/* 4 */
	_nts_1,	/* 5 */
	_nts_1,	/* 6 */
	_nts_1,	/* 7 */
	_nts_1,	/* 8 */
	_nts_1,	/* 9 */
	_nts_1,	/* 10 */
	_nts_2,	/* 11 */
	_nts_2,	/* 12 */
	_nts_2,	/* 13 */
	_nts_2,	/* 14 */
	_nts_2,	/* 15 */
	_nts_2,	/* 16 */
	_nts_2,	/* 17 */
	_nts_3,	/* 18 */
	_nts_4,	/* 19 */
	_nts_0,	/* 20 */
	_nts_0,	/* 21 */
	_nts_0,	/* 22 */
	_nts_0,	/* 23 */
	_nts_0,	/* 24 */
	_nts_0,	/* 25 */
	_nts_0,	/* 26 */
	_nts_2,	/* 27 */
	_nts_3,	/* 28 */
	_nts_4,	/* 29 */
	_nts_2,	/* 30 */
	_nts_2,	/* 31 */
	_nts_2,	/* 32 */
	_nts_2,	/* 33 */
	_nts_2,	/* 34 */
	_nts_2,	/* 35 */
	_nts_2,	/* 36 */
	_nts_0,	/* 37 */
	_nts_0,	/* 38 */
	_nts_0,	/* 39 */
	_nts_5,	/* 40 */
	_nts_2,	/* 41 */
	_nts_2,	/* 42 */
	_nts_2,	/* 43 */
	_nts_2,	/* 44 */
	_nts_2,	/* 45 */
	_nts_2,	/* 46 */
	_nts_2,	/* 47 */
	_nts_6,	/* 48 */
	_nts_6,	/* 49 */
	_nts_6,	/* 50 */
	_nts_6,	/* 51 */
	_nts_6,	/* 52 */
	_nts_6,	/* 53 */
	_nts_6,	/* 54 */
	_nts_6,	/* 55 */
	_nts_6,	/* 56 */
	_nts_6,	/* 57 */
	_nts_6,	/* 58 */
	_nts_6,	/* 59 */
	_nts_2,	/* 60 */
	_nts_2,	/* 61 */
	_nts_2,	/* 62 */
	_nts_6,	/* 63 */
	_nts_6,	/* 64 */
	_nts_6,	/* 65 */
	_nts_6,	/* 66 */
	_nts_6,	/* 67 */
	_nts_6,	/* 68 */
	_nts_6,	/* 69 */
	_nts_6,	/* 70 */
	_nts_6,	/* 71 */
	_nts_6,	/* 72 */
	_nts_2,	/* 73 */
	_nts_2,	/* 74 */
	_nts_2,	/* 75 */
	_nts_2,	/* 76 */
	_nts_2,	/* 77 */
	_nts_2,	/* 78 */
	_nts_2,	/* 79 */
	_nts_2,	/* 80 */
	_nts_2,	/* 81 */
	_nts_2,	/* 82 */
	_nts_2,	/* 83 */
	_nts_2,	/* 84 */
	_nts_2,	/* 85 */
	_nts_2,	/* 86 */
	_nts_0,	/* 87 */
	_nts_7,	/* 88 */
	_nts_7,	/* 89 */
	_nts_7,	/* 90 */
	_nts_7,	/* 91 */
	_nts_7,	/* 92 */
	_nts_7,	/* 93 */
	_nts_7,	/* 94 */
	_nts_8,	/* 95 */
	_nts_9,	/* 96 */
	_nts_6,	/* 97 */
	_nts_6,	/* 98 */
	_nts_6,	/* 99 */
	_nts_6,	/* 100 */
	_nts_6,	/* 101 */
	_nts_6,	/* 102 */
	_nts_6,	/* 103 */
	_nts_2,	/* 104 */
	_nts_2,	/* 105 */
	_nts_2,	/* 106 */
	_nts_2,	/* 107 */
	_nts_10,	/* 108 */
	_nts_11,	/* 109 */
	_nts_0,	/* 110 */
	_nts_2,	/* 111 */
	_nts_0,	/* 112 */
	_nts_12,	/* 113 */
	_nts_6,	/* 114 */
	_nts_6,	/* 115 */
	_nts_6,	/* 116 */
	_nts_6,	/* 117 */
	_nts_6,	/* 118 */
	_nts_6,	/* 119 */
	_nts_6,	/* 120 */
	_nts_6,	/* 121 */
	_nts_6,	/* 122 */
	_nts_6,	/* 123 */
	_nts_6,	/* 124 */
	_nts_6,	/* 125 */
	_nts_12,	/* 126 */
	_nts_12,	/* 127 */
	_nts_12,	/* 128 */
	_nts_12,	/* 129 */
	_nts_2,	/* 130 */
	_nts_2,	/* 131 */
	_nts_2,	/* 132 */
	_nts_3,	/* 133 */
	_nts_4,	/* 134 */
	_nts_2,	/* 135 */
	_nts_2,	/* 136 */
	_nts_13,	/* 137 */
	_nts_14,	/* 138 */
	_nts_3,	/* 139 */
	_nts_4,	/* 140 */
	_nts_3,	/* 141 */
	_nts_4,	/* 142 */
	_nts_15,	/* 143 */
	_nts_15,	/* 144 */
	_nts_15,	/* 145 */
	_nts_15,	/* 146 */
	_nts_16,	/* 147 */
	_nts_16,	/* 148 */
	_nts_16,	/* 149 */
	_nts_16,	/* 150 */
	_nts_3,	/* 151 */
	_nts_4,	/* 152 */
	_nts_3,	/* 153 */
	_nts_4,	/* 154 */
	_nts_3,	/* 155 */
	_nts_4,	/* 156 */
	_nts_2,	/* 157 */
	_nts_2,	/* 158 */
	_nts_15,	/* 159 */
	_nts_15,	/* 160 */
	_nts_15,	/* 161 */
	_nts_15,	/* 162 */
	_nts_15,	/* 163 */
	_nts_15,	/* 164 */
	_nts_16,	/* 165 */
	_nts_16,	/* 166 */
	_nts_16,	/* 167 */
	_nts_16,	/* 168 */
	_nts_16,	/* 169 */
	_nts_16,	/* 170 */
	_nts_12,	/* 171 */
	_nts_12,	/* 172 */
	_nts_12,	/* 173 */
	_nts_12,	/* 174 */
};

static char *_templates[] = {
/* 0 */	0,
/* 1 */	"",	/* vr: VREGP */
/* 2 */	"\n",	/* reg: INDIRI1(vr) */
/* 3 */	"\n",	/* reg: INDIRU1(vr) */
/* 4 */	"\n",	/* reg: INDIRI2(vr) */
/* 5 */	"\n",	/* reg: INDIRU2(vr) */
/* 6 */	"\n",	/* reg: INDIRI4(vr) */
/* 7 */	"\n",	/* reg: INDIRU4(vr) */
/* 8 */	"\n",	/* reg: INDIRP4(vr) */
/* 9 */	"\n",	/* freg: INDIRF4(vr) */
/* 10 */	"\n",	/* freg8: INDIRF8(vr) */
/* 11 */	"# emit2\n",	/* stmt: ASGNI1(VREGP,reg) */
/* 12 */	"# emit2\n",	/* stmt: ASGNU1(VREGP,reg) */
/* 13 */	"# emit2\n",	/* stmt: ASGNI2(VREGP,reg) */
/* 14 */	"# emit2\n",	/* stmt: ASGNU2(VREGP,reg) */
/* 15 */	"# emit2\n",	/* stmt: ASGNI4(VREGP,reg) */
/* 16 */	"# emit2\n",	/* stmt: ASGNU4(VREGP,reg) */
/* 17 */	"# emit2\n",	/* stmt: ASGNP4(VREGP,reg) */
/* 18 */	"# emit2\n",	/* stmt: ASGNF4(VREGP,freg) */
/* 19 */	"# emit2\n",	/* stmt: ASGNF8(VREGP,freg8) */
/* 20 */	"$%a",	/* cnst: CNSTI1 */
/* 21 */	"$%a",	/* cnst: CNSTU1 */
/* 22 */	"$%a",	/* cnst: CNSTI4 */
/* 23 */	"$%a",	/* cnst: CNSTU4 */
/* 24 */	"$%a",	/* cnst: CNSTP4 */
/* 25 */	"$%a",	/* cnst: CNSTI2 */
/* 26 */	"$%a",	/* cnst: CNSTU2 */
/* 27 */	"",	/* stmt: reg */
/* 28 */	"",	/* stmt: freg */
/* 29 */	"",	/* stmt: freg8 */
/* 30 */	"# emit2\n",	/* reg: INDIRI1(reg) */
/* 31 */	"# emit2\n",	/* reg: INDIRU1(reg) */
/* 32 */	"# emit2\n",	/* reg: INDIRI2(reg) */
/* 33 */	"# emit2\n",	/* reg: INDIRU2(reg) */
/* 34 */	"# emit2\n",	/* reg: INDIRI4(reg) */
/* 35 */	"# emit2\n",	/* reg: INDIRU4(reg) */
/* 36 */	"# emit2\n",	/* reg: INDIRP4(reg) */
/* 37 */	"# emit2\n",	/* reg: ADDRGP4 */
/* 38 */	"# emit2\n",	/* reg: ADDRLP4 */
/* 39 */	"# emit2\n",	/* reg: ADDRFP4 */
/* 40 */	"movl %0, %c\n",	/* reg: cnst */
/* 41 */	"# emit2\n",	/* reg: LOADI1(reg) */
/* 42 */	"# emit2\n",	/* reg: LOADI2(reg) */
/* 43 */	"# emit2\n",	/* reg: LOADI4(reg) */
/* 44 */	"# emit2\n",	/* reg: LOADU1(reg) */
/* 45 */	"# emit2\n",	/* reg: LOADU2(reg) */
/* 46 */	"# emit2\n",	/* reg: LOADU4(reg) */
/* 47 */	"# emit2\n",	/* reg: LOADP4(reg) */
/* 48 */	"# emit2\n",	/* reg: ADDI4(reg,reg) */
/* 49 */	"# emit2\n",	/* reg: ADDP4(reg,reg) */
/* 50 */	"# emit2\n",	/* reg: ADDU4(reg,reg) */
/* 51 */	"# emit2\n",	/* reg: SUBI4(reg,reg) */
/* 52 */	"# emit2\n",	/* reg: SUBP4(reg,reg) */
/* 53 */	"# emit2\n",	/* reg: SUBU4(reg,reg) */
/* 54 */	"# emit2\n",	/* reg: BANDI4(reg,reg) */
/* 55 */	"# emit2\n",	/* reg: BANDU4(reg,reg) */
/* 56 */	"# emit2\n",	/* reg: BORI4(reg,reg) */
/* 57 */	"# emit2\n",	/* reg: BORU4(reg,reg) */
/* 58 */	"# emit2\n",	/* reg: BXORI4(reg,reg) */
/* 59 */	"# emit2\n",	/* reg: BXORU4(reg,reg) */
/* 60 */	"# emit2\n",	/* reg: BCOMI4(reg) */
/* 61 */	"# emit2\n",	/* reg: BCOMU4(reg) */
/* 62 */	"# emit2\n",	/* reg: NEGI4(reg) */
/* 63 */	"# emit2\n",	/* reg: LSHI4(reg,reg) */
/* 64 */	"# emit2\n",	/* reg: LSHU4(reg,reg) */
/* 65 */	"# emit2\n",	/* reg: RSHI4(reg,reg) */
/* 66 */	"# emit2\n",	/* reg: RSHU4(reg,reg) */
/* 67 */	"# emit2\n",	/* reg: MULI4(reg,reg) */
/* 68 */	"# emit2\n",	/* reg: MULU4(reg,reg) */
/* 69 */	"# emit2\n",	/* reg: DIVU4(reg,reg) */
/* 70 */	"# emit2\n",	/* reg: DIVI4(reg,reg) */
/* 71 */	"# emit2\n",	/* reg: MODU4(reg,reg) */
/* 72 */	"# emit2\n",	/* reg: MODI4(reg,reg) */
/* 73 */	"movl %0,%c\n",	/* reg: CVPU4(reg) */
/* 74 */	"movl %0,%c\n",	/* reg: CVUP4(reg) */
/* 75 */	"# emit2\n",	/* reg: CVII1(reg) */
/* 76 */	"# emit2\n",	/* reg: CVUU1(reg) */
/* 77 */	"# emit2\n",	/* reg: CVIU1(reg) */
/* 78 */	"# emit2\n",	/* reg: CVUI1(reg) */
/* 79 */	"# emit2\n",	/* reg: CVII2(reg) */
/* 80 */	"# emit2\n",	/* reg: CVIU2(reg) */
/* 81 */	"# emit2\n",	/* reg: CVUI2(reg) */
/* 82 */	"# emit2\n",	/* reg: CVUU2(reg) */
/* 83 */	"# emit2\n",	/* reg: CVII4(reg) */
/* 84 */	"# emit2\n",	/* reg: CVIU4(reg) */
/* 85 */	"# emit2\n",	/* reg: CVUI4(reg) */
/* 86 */	"# emit2\n",	/* reg: CVUU4(reg) */
/* 87 */	"%a",	/* saddr: ADDRLP4 */
/* 88 */	"# emit2\n",	/* stmt: ASGNI1(saddr,reg) */
/* 89 */	"# emit2\n",	/* stmt: ASGNU1(saddr,reg) */
/* 90 */	"# emit2\n",	/* stmt: ASGNI2(saddr,reg) */
/* 91 */	"# emit2\n",	/* stmt: ASGNU2(saddr,reg) */
/* 92 */	"# emit2\n",	/* stmt: ASGNI4(saddr,reg) */
/* 93 */	"# emit2\n",	/* stmt: ASGNU4(saddr,reg) */
/* 94 */	"# emit2\n",	/* stmt: ASGNP4(saddr,reg) */
/* 95 */	"# emit2\n",	/* stmt: ASGNF4(saddr,freg) */
/* 96 */	"# emit2\n",	/* stmt: ASGNF8(saddr,freg8) */
/* 97 */	"# emit2\n",	/* stmt: ASGNI1(reg,reg) */
/* 98 */	"# emit2\n",	/* stmt: ASGNU1(reg,reg) */
/* 99 */	"# emit2\n",	/* stmt: ASGNI2(reg,reg) */
/* 100 */	"# emit2\n",	/* stmt: ASGNU2(reg,reg) */
/* 101 */	"# emit2\n",	/* stmt: ASGNI4(reg,reg) */
/* 102 */	"# emit2\n",	/* stmt: ASGNU4(reg,reg) */
/* 103 */	"# emit2\n",	/* stmt: ASGNP4(reg,reg) */
/* 104 */	"# emit2\n",	/* stmt: ARGI4(reg) */
/* 105 */	"# emit2\n",	/* stmt: ARGU4(reg) */
/* 106 */	"# emit2\n",	/* stmt: ARGP4(reg) */
/* 107 */	"# emit2\n",	/* memb: INDIRB(reg) */
/* 108 */	"# emit2\n",	/* stmt: ASGNB(reg,memb) */
/* 109 */	"# emit2\n",	/* stmt: ARGB(memb) */
/* 110 */	"%a",	/* jaddr: ADDRGP4 */
/* 111 */	"%0",	/* jaddr: reg */
/* 112 */	"# emit2\n",	/* stmt: LABELV */
/* 113 */	"# emit2\n",	/* stmt: JUMPV(jaddr) */
/* 114 */	"# emit2\n",	/* stmt: EQI4(reg,reg) */
/* 115 */	"# emit2\n",	/* stmt: GEI4(reg,reg) */
/* 116 */	"# emit2\n",	/* stmt: GTI4(reg,reg) */
/* 117 */	"# emit2\n",	/* stmt: LEI4(reg,reg) */
/* 118 */	"# emit2\n",	/* stmt: LTI4(reg,reg) */
/* 119 */	"# emit2\n",	/* stmt: NEI4(reg,reg) */
/* 120 */	"# emit2\n",	/* stmt: EQU4(reg,reg) */
/* 121 */	"# emit2\n",	/* stmt: GEU4(reg,reg) */
/* 122 */	"# emit2\n",	/* stmt: GTU4(reg,reg) */
/* 123 */	"# emit2\n",	/* stmt: LEU4(reg,reg) */
/* 124 */	"# emit2\n",	/* stmt: LTU4(reg,reg) */
/* 125 */	"# emit2\n",	/* stmt: NEU4(reg,reg) */
/* 126 */	"# emit2\n",	/* reg: CALLI4(jaddr) */
/* 127 */	"# emit2\n",	/* reg: CALLU4(jaddr) */
/* 128 */	"# emit2\n",	/* reg: CALLP4(jaddr) */
/* 129 */	"# emit2\n",	/* stmt: CALLV(jaddr) */
/* 130 */	"# emit2\n",	/* stmt: RETI4(reg) */
/* 131 */	"# emit2\n",	/* stmt: RETU4(reg) */
/* 132 */	"# emit2\n",	/* stmt: RETP4(reg) */
/* 133 */	"# emit2\n",	/* stmt: RETF4(freg) */
/* 134 */	"# emit2\n",	/* stmt: RETF8(freg8) */
/* 135 */	"# emit2\n",	/* freg: INDIRF4(reg) */
/* 136 */	"# emit2\n",	/* freg8: INDIRF8(reg) */
/* 137 */	"# emit2\n",	/* stmt: ASGNF4(reg,freg) */
/* 138 */	"# emit2\n",	/* stmt: ASGNF8(reg,freg8) */
/* 139 */	"# emit2\n",	/* stmt: ARGF4(freg) */
/* 140 */	"# emit2\n",	/* stmt: ARGF8(freg8) */
/* 141 */	"# emit2\n",	/* freg: NEGF4(freg) */
/* 142 */	"# emit2\n",	/* freg8: NEGF8(freg8) */
/* 143 */	"# emit2\n",	/* freg: ADDF4(freg,freg) */
/* 144 */	"# emit2\n",	/* freg: DIVF4(freg,freg) */
/* 145 */	"# emit2\n",	/* freg: MULF4(freg,freg) */
/* 146 */	"# emit2\n",	/* freg: SUBF4(freg,freg) */
/* 147 */	"# emit2\n",	/* freg8: ADDF8(freg8,freg8) */
/* 148 */	"# emit2\n",	/* freg8: DIVF8(freg8,freg8) */
/* 149 */	"# emit2\n",	/* freg8: MULF8(freg8,freg8) */
/* 150 */	"# emit2\n",	/* freg8: SUBF8(freg8,freg8) */
/* 151 */	"# emit2\n",	/* freg: CVFF4(freg) */
/* 152 */	"# emit2\n",	/* freg: CVFF4(freg8) */
/* 153 */	"# emit2\n",	/* freg8: CVFF8(freg) */
/* 154 */	"# emit2\n",	/* freg8: CVFF8(freg8) */
/* 155 */	"# emit2\n",	/* reg: CVFI4(freg) */
/* 156 */	"# emit2\n",	/* reg: CVFI4(freg8) */
/* 157 */	"# emit2\n",	/* freg: CVIF4(reg) */
/* 158 */	"# emit2\n",	/* freg8: CVIF8(reg) */
/* 159 */	"# emit2\n",	/* stmt: EQF4(freg,freg) */
/* 160 */	"# emit2\n",	/* stmt: GEF4(freg,freg) */
/* 161 */	"# emit2\n",	/* stmt: GTF4(freg,freg) */
/* 162 */	"# emit2\n",	/* stmt: LEF4(freg,freg) */
/* 163 */	"# emit2\n",	/* stmt: LTF4(freg,freg) */
/* 164 */	"# emit2\n",	/* stmt: NEF4(freg,freg) */
/* 165 */	"# emit2\n",	/* stmt: EQF8(freg8,freg8) */
/* 166 */	"# emit2\n",	/* stmt: GEF8(freg8,freg8) */
/* 167 */	"# emit2\n",	/* stmt: GTF8(freg8,freg8) */
/* 168 */	"# emit2\n",	/* stmt: LEF8(freg8,freg8) */
/* 169 */	"# emit2\n",	/* stmt: LTF8(freg8,freg8) */
/* 170 */	"# emit2\n",	/* stmt: NEF8(freg8,freg8) */
/* 171 */	"# emit2\n",	/* freg: CALLF4(jaddr) */
/* 172 */	"# emit2\n",	/* freg8: CALLF8(jaddr) */
/* 173 */	"# emit2\n",	/* stmt: CALLF4(jaddr) */
/* 174 */	"# emit2\n",	/* stmt: CALLF8(jaddr) */
};

static char _isinstruction[] = {
/* 0 */	0,
/* 1 */	0,	/*  */
/* 2 */	1,	/* \n */
/* 3 */	1,	/* \n */
/* 4 */	1,	/* \n */
/* 5 */	1,	/* \n */
/* 6 */	1,	/* \n */
/* 7 */	1,	/* \n */
/* 8 */	1,	/* \n */
/* 9 */	1,	/* \n */
/* 10 */	1,	/* \n */
/* 11 */	1,	/* # emit2\n */
/* 12 */	1,	/* # emit2\n */
/* 13 */	1,	/* # emit2\n */
/* 14 */	1,	/* # emit2\n */
/* 15 */	1,	/* # emit2\n */
/* 16 */	1,	/* # emit2\n */
/* 17 */	1,	/* # emit2\n */
/* 18 */	1,	/* # emit2\n */
/* 19 */	1,	/* # emit2\n */
/* 20 */	0,	/* $%a */
/* 21 */	0,	/* $%a */
/* 22 */	0,	/* $%a */
/* 23 */	0,	/* $%a */
/* 24 */	0,	/* $%a */
/* 25 */	0,	/* $%a */
/* 26 */	0,	/* $%a */
/* 27 */	0,	/*  */
/* 28 */	0,	/*  */
/* 29 */	0,	/*  */
/* 30 */	1,	/* # emit2\n */
/* 31 */	1,	/* # emit2\n */
/* 32 */	1,	/* # emit2\n */
/* 33 */	1,	/* # emit2\n */
/* 34 */	1,	/* # emit2\n */
/* 35 */	1,	/* # emit2\n */
/* 36 */	1,	/* # emit2\n */
/* 37 */	1,	/* # emit2\n */
/* 38 */	1,	/* # emit2\n */
/* 39 */	1,	/* # emit2\n */
/* 40 */	1,	/* movl %0, %c\n */
/* 41 */	1,	/* # emit2\n */
/* 42 */	1,	/* # emit2\n */
/* 43 */	1,	/* # emit2\n */
/* 44 */	1,	/* # emit2\n */
/* 45 */	1,	/* # emit2\n */
/* 46 */	1,	/* # emit2\n */
/* 47 */	1,	/* # emit2\n */
/* 48 */	1,	/* # emit2\n */
/* 49 */	1,	/* # emit2\n */
/* 50 */	1,	/* # emit2\n */
/* 51 */	1,	/* # emit2\n */
/* 52 */	1,	/* # emit2\n */
/* 53 */	1,	/* # emit2\n */
/* 54 */	1,	/* # emit2\n */
/* 55 */	1,	/* # emit2\n */
/* 56 */	1,	/* # emit2\n */
/* 57 */	1,	/* # emit2\n */
/* 58 */	1,	/* # emit2\n */
/* 59 */	1,	/* # emit2\n */
/* 60 */	1,	/* # emit2\n */
/* 61 */	1,	/* # emit2\n */
/* 62 */	1,	/* # emit2\n */
/* 63 */	1,	/* # emit2\n */
/* 64 */	1,	/* # emit2\n */
/* 65 */	1,	/* # emit2\n */
/* 66 */	1,	/* # emit2\n */
/* 67 */	1,	/* # emit2\n */
/* 68 */	1,	/* # emit2\n */
/* 69 */	1,	/* # emit2\n */
/* 70 */	1,	/* # emit2\n */
/* 71 */	1,	/* # emit2\n */
/* 72 */	1,	/* # emit2\n */
/* 73 */	1,	/* movl %0,%c\n */
/* 74 */	1,	/* movl %0,%c\n */
/* 75 */	1,	/* # emit2\n */
/* 76 */	1,	/* # emit2\n */
/* 77 */	1,	/* # emit2\n */
/* 78 */	1,	/* # emit2\n */
/* 79 */	1,	/* # emit2\n */
/* 80 */	1,	/* # emit2\n */
/* 81 */	1,	/* # emit2\n */
/* 82 */	1,	/* # emit2\n */
/* 83 */	1,	/* # emit2\n */
/* 84 */	1,	/* # emit2\n */
/* 85 */	1,	/* # emit2\n */
/* 86 */	1,	/* # emit2\n */
/* 87 */	0,	/* %a */
/* 88 */	1,	/* # emit2\n */
/* 89 */	1,	/* # emit2\n */
/* 90 */	1,	/* # emit2\n */
/* 91 */	1,	/* # emit2\n */
/* 92 */	1,	/* # emit2\n */
/* 93 */	1,	/* # emit2\n */
/* 94 */	1,	/* # emit2\n */
/* 95 */	1,	/* # emit2\n */
/* 96 */	1,	/* # emit2\n */
/* 97 */	1,	/* # emit2\n */
/* 98 */	1,	/* # emit2\n */
/* 99 */	1,	/* # emit2\n */
/* 100 */	1,	/* # emit2\n */
/* 101 */	1,	/* # emit2\n */
/* 102 */	1,	/* # emit2\n */
/* 103 */	1,	/* # emit2\n */
/* 104 */	1,	/* # emit2\n */
/* 105 */	1,	/* # emit2\n */
/* 106 */	1,	/* # emit2\n */
/* 107 */	1,	/* # emit2\n */
/* 108 */	1,	/* # emit2\n */
/* 109 */	1,	/* # emit2\n */
/* 110 */	0,	/* %a */
/* 111 */	0,	/* %0 */
/* 112 */	1,	/* # emit2\n */
/* 113 */	1,	/* # emit2\n */
/* 114 */	1,	/* # emit2\n */
/* 115 */	1,	/* # emit2\n */
/* 116 */	1,	/* # emit2\n */
/* 117 */	1,	/* # emit2\n */
/* 118 */	1,	/* # emit2\n */
/* 119 */	1,	/* # emit2\n */
/* 120 */	1,	/* # emit2\n */
/* 121 */	1,	/* # emit2\n */
/* 122 */	1,	/* # emit2\n */
/* 123 */	1,	/* # emit2\n */
/* 124 */	1,	/* # emit2\n */
/* 125 */	1,	/* # emit2\n */
/* 126 */	1,	/* # emit2\n */
/* 127 */	1,	/* # emit2\n */
/* 128 */	1,	/* # emit2\n */
/* 129 */	1,	/* # emit2\n */
/* 130 */	1,	/* # emit2\n */
/* 131 */	1,	/* # emit2\n */
/* 132 */	1,	/* # emit2\n */
/* 133 */	1,	/* # emit2\n */
/* 134 */	1,	/* # emit2\n */
/* 135 */	1,	/* # emit2\n */
/* 136 */	1,	/* # emit2\n */
/* 137 */	1,	/* # emit2\n */
/* 138 */	1,	/* # emit2\n */
/* 139 */	1,	/* # emit2\n */
/* 140 */	1,	/* # emit2\n */
/* 141 */	1,	/* # emit2\n */
/* 142 */	1,	/* # emit2\n */
/* 143 */	1,	/* # emit2\n */
/* 144 */	1,	/* # emit2\n */
/* 145 */	1,	/* # emit2\n */
/* 146 */	1,	/* # emit2\n */
/* 147 */	1,	/* # emit2\n */
/* 148 */	1,	/* # emit2\n */
/* 149 */	1,	/* # emit2\n */
/* 150 */	1,	/* # emit2\n */
/* 151 */	1,	/* # emit2\n */
/* 152 */	1,	/* # emit2\n */
/* 153 */	1,	/* # emit2\n */
/* 154 */	1,	/* # emit2\n */
/* 155 */	1,	/* # emit2\n */
/* 156 */	1,	/* # emit2\n */
/* 157 */	1,	/* # emit2\n */
/* 158 */	1,	/* # emit2\n */
/* 159 */	1,	/* # emit2\n */
/* 160 */	1,	/* # emit2\n */
/* 161 */	1,	/* # emit2\n */
/* 162 */	1,	/* # emit2\n */
/* 163 */	1,	/* # emit2\n */
/* 164 */	1,	/* # emit2\n */
/* 165 */	1,	/* # emit2\n */
/* 166 */	1,	/* # emit2\n */
/* 167 */	1,	/* # emit2\n */
/* 168 */	1,	/* # emit2\n */
/* 169 */	1,	/* # emit2\n */
/* 170 */	1,	/* # emit2\n */
/* 171 */	1,	/* # emit2\n */
/* 172 */	1,	/* # emit2\n */
/* 173 */	1,	/* # emit2\n */
/* 174 */	1,	/* # emit2\n */
};

static char *_string[] = {
/* 0 */	0,
/* 1 */	"vr: VREGP",
/* 2 */	"reg: INDIRI1(vr)",
/* 3 */	"reg: INDIRU1(vr)",
/* 4 */	"reg: INDIRI2(vr)",
/* 5 */	"reg: INDIRU2(vr)",
/* 6 */	"reg: INDIRI4(vr)",
/* 7 */	"reg: INDIRU4(vr)",
/* 8 */	"reg: INDIRP4(vr)",
/* 9 */	"freg: INDIRF4(vr)",
/* 10 */	"freg8: INDIRF8(vr)",
/* 11 */	"stmt: ASGNI1(VREGP,reg)",
/* 12 */	"stmt: ASGNU1(VREGP,reg)",
/* 13 */	"stmt: ASGNI2(VREGP,reg)",
/* 14 */	"stmt: ASGNU2(VREGP,reg)",
/* 15 */	"stmt: ASGNI4(VREGP,reg)",
/* 16 */	"stmt: ASGNU4(VREGP,reg)",
/* 17 */	"stmt: ASGNP4(VREGP,reg)",
/* 18 */	"stmt: ASGNF4(VREGP,freg)",
/* 19 */	"stmt: ASGNF8(VREGP,freg8)",
/* 20 */	"cnst: CNSTI1",
/* 21 */	"cnst: CNSTU1",
/* 22 */	"cnst: CNSTI4",
/* 23 */	"cnst: CNSTU4",
/* 24 */	"cnst: CNSTP4",
/* 25 */	"cnst: CNSTI2",
/* 26 */	"cnst: CNSTU2",
/* 27 */	"stmt: reg",
/* 28 */	"stmt: freg",
/* 29 */	"stmt: freg8",
/* 30 */	"reg: INDIRI1(reg)",
/* 31 */	"reg: INDIRU1(reg)",
/* 32 */	"reg: INDIRI2(reg)",
/* 33 */	"reg: INDIRU2(reg)",
/* 34 */	"reg: INDIRI4(reg)",
/* 35 */	"reg: INDIRU4(reg)",
/* 36 */	"reg: INDIRP4(reg)",
/* 37 */	"reg: ADDRGP4",
/* 38 */	"reg: ADDRLP4",
/* 39 */	"reg: ADDRFP4",
/* 40 */	"reg: cnst",
/* 41 */	"reg: LOADI1(reg)",
/* 42 */	"reg: LOADI2(reg)",
/* 43 */	"reg: LOADI4(reg)",
/* 44 */	"reg: LOADU1(reg)",
/* 45 */	"reg: LOADU2(reg)",
/* 46 */	"reg: LOADU4(reg)",
/* 47 */	"reg: LOADP4(reg)",
/* 48 */	"reg: ADDI4(reg,reg)",
/* 49 */	"reg: ADDP4(reg,reg)",
/* 50 */	"reg: ADDU4(reg,reg)",
/* 51 */	"reg: SUBI4(reg,reg)",
/* 52 */	"reg: SUBP4(reg,reg)",
/* 53 */	"reg: SUBU4(reg,reg)",
/* 54 */	"reg: BANDI4(reg,reg)",
/* 55 */	"reg: BANDU4(reg,reg)",
/* 56 */	"reg: BORI4(reg,reg)",
/* 57 */	"reg: BORU4(reg,reg)",
/* 58 */	"reg: BXORI4(reg,reg)",
/* 59 */	"reg: BXORU4(reg,reg)",
/* 60 */	"reg: BCOMI4(reg)",
/* 61 */	"reg: BCOMU4(reg)",
/* 62 */	"reg: NEGI4(reg)",
/* 63 */	"reg: LSHI4(reg,reg)",
/* 64 */	"reg: LSHU4(reg,reg)",
/* 65 */	"reg: RSHI4(reg,reg)",
/* 66 */	"reg: RSHU4(reg,reg)",
/* 67 */	"reg: MULI4(reg,reg)",
/* 68 */	"reg: MULU4(reg,reg)",
/* 69 */	"reg: DIVU4(reg,reg)",
/* 70 */	"reg: DIVI4(reg,reg)",
/* 71 */	"reg: MODU4(reg,reg)",
/* 72 */	"reg: MODI4(reg,reg)",
/* 73 */	"reg: CVPU4(reg)",
/* 74 */	"reg: CVUP4(reg)",
/* 75 */	"reg: CVII1(reg)",
/* 76 */	"reg: CVUU1(reg)",
/* 77 */	"reg: CVIU1(reg)",
/* 78 */	"reg: CVUI1(reg)",
/* 79 */	"reg: CVII2(reg)",
/* 80 */	"reg: CVIU2(reg)",
/* 81 */	"reg: CVUI2(reg)",
/* 82 */	"reg: CVUU2(reg)",
/* 83 */	"reg: CVII4(reg)",
/* 84 */	"reg: CVIU4(reg)",
/* 85 */	"reg: CVUI4(reg)",
/* 86 */	"reg: CVUU4(reg)",
/* 87 */	"saddr: ADDRLP4",
/* 88 */	"stmt: ASGNI1(saddr,reg)",
/* 89 */	"stmt: ASGNU1(saddr,reg)",
/* 90 */	"stmt: ASGNI2(saddr,reg)",
/* 91 */	"stmt: ASGNU2(saddr,reg)",
/* 92 */	"stmt: ASGNI4(saddr,reg)",
/* 93 */	"stmt: ASGNU4(saddr,reg)",
/* 94 */	"stmt: ASGNP4(saddr,reg)",
/* 95 */	"stmt: ASGNF4(saddr,freg)",
/* 96 */	"stmt: ASGNF8(saddr,freg8)",
/* 97 */	"stmt: ASGNI1(reg,reg)",
/* 98 */	"stmt: ASGNU1(reg,reg)",
/* 99 */	"stmt: ASGNI2(reg,reg)",
/* 100 */	"stmt: ASGNU2(reg,reg)",
/* 101 */	"stmt: ASGNI4(reg,reg)",
/* 102 */	"stmt: ASGNU4(reg,reg)",
/* 103 */	"stmt: ASGNP4(reg,reg)",
/* 104 */	"stmt: ARGI4(reg)",
/* 105 */	"stmt: ARGU4(reg)",
/* 106 */	"stmt: ARGP4(reg)",
/* 107 */	"memb: INDIRB(reg)",
/* 108 */	"stmt: ASGNB(reg,memb)",
/* 109 */	"stmt: ARGB(memb)",
/* 110 */	"jaddr: ADDRGP4",
/* 111 */	"jaddr: reg",
/* 112 */	"stmt: LABELV",
/* 113 */	"stmt: JUMPV(jaddr)",
/* 114 */	"stmt: EQI4(reg,reg)",
/* 115 */	"stmt: GEI4(reg,reg)",
/* 116 */	"stmt: GTI4(reg,reg)",
/* 117 */	"stmt: LEI4(reg,reg)",
/* 118 */	"stmt: LTI4(reg,reg)",
/* 119 */	"stmt: NEI4(reg,reg)",
/* 120 */	"stmt: EQU4(reg,reg)",
/* 121 */	"stmt: GEU4(reg,reg)",
/* 122 */	"stmt: GTU4(reg,reg)",
/* 123 */	"stmt: LEU4(reg,reg)",
/* 124 */	"stmt: LTU4(reg,reg)",
/* 125 */	"stmt: NEU4(reg,reg)",
/* 126 */	"reg: CALLI4(jaddr)",
/* 127 */	"reg: CALLU4(jaddr)",
/* 128 */	"reg: CALLP4(jaddr)",
/* 129 */	"stmt: CALLV(jaddr)",
/* 130 */	"stmt: RETI4(reg)",
/* 131 */	"stmt: RETU4(reg)",
/* 132 */	"stmt: RETP4(reg)",
/* 133 */	"stmt: RETF4(freg)",
/* 134 */	"stmt: RETF8(freg8)",
/* 135 */	"freg: INDIRF4(reg)",
/* 136 */	"freg8: INDIRF8(reg)",
/* 137 */	"stmt: ASGNF4(reg,freg)",
/* 138 */	"stmt: ASGNF8(reg,freg8)",
/* 139 */	"stmt: ARGF4(freg)",
/* 140 */	"stmt: ARGF8(freg8)",
/* 141 */	"freg: NEGF4(freg)",
/* 142 */	"freg8: NEGF8(freg8)",
/* 143 */	"freg: ADDF4(freg,freg)",
/* 144 */	"freg: DIVF4(freg,freg)",
/* 145 */	"freg: MULF4(freg,freg)",
/* 146 */	"freg: SUBF4(freg,freg)",
/* 147 */	"freg8: ADDF8(freg8,freg8)",
/* 148 */	"freg8: DIVF8(freg8,freg8)",
/* 149 */	"freg8: MULF8(freg8,freg8)",
/* 150 */	"freg8: SUBF8(freg8,freg8)",
/* 151 */	"freg: CVFF4(freg)",
/* 152 */	"freg: CVFF4(freg8)",
/* 153 */	"freg8: CVFF8(freg)",
/* 154 */	"freg8: CVFF8(freg8)",
/* 155 */	"reg: CVFI4(freg)",
/* 156 */	"reg: CVFI4(freg8)",
/* 157 */	"freg: CVIF4(reg)",
/* 158 */	"freg8: CVIF8(reg)",
/* 159 */	"stmt: EQF4(freg,freg)",
/* 160 */	"stmt: GEF4(freg,freg)",
/* 161 */	"stmt: GTF4(freg,freg)",
/* 162 */	"stmt: LEF4(freg,freg)",
/* 163 */	"stmt: LTF4(freg,freg)",
/* 164 */	"stmt: NEF4(freg,freg)",
/* 165 */	"stmt: EQF8(freg8,freg8)",
/* 166 */	"stmt: GEF8(freg8,freg8)",
/* 167 */	"stmt: GTF8(freg8,freg8)",
/* 168 */	"stmt: LEF8(freg8,freg8)",
/* 169 */	"stmt: LTF8(freg8,freg8)",
/* 170 */	"stmt: NEF8(freg8,freg8)",
/* 171 */	"freg: CALLF4(jaddr)",
/* 172 */	"freg8: CALLF8(jaddr)",
/* 173 */	"stmt: CALLF4(jaddr)",
/* 174 */	"stmt: CALLF8(jaddr)",
};

static short _decode_stmt[] = {
	0,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	27,
	28,
	29,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	106,
	108,
	109,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	124,
	125,
	129,
	130,
	131,
	132,
	133,
	134,
	137,
	138,
	139,
	140,
	159,
	160,
	161,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	173,
	174,
};

static short _decode_vr[] = {
	0,
	1,
};

static short _decode_reg[] = {
	0,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	126,
	127,
	128,
	155,
	156,
};

static short _decode_freg[] = {
	0,
	9,
	135,
	141,
	143,
	144,
	145,
	146,
	151,
	152,
	157,
	171,
};

static short _decode_freg8[] = {
	0,
	10,
	136,
	142,
	147,
	148,
	149,
	150,
	153,
	154,
	158,
	172,
};

static short _decode_cnst[] = {
	0,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
};

static short _decode_saddr[] = {
	0,
	87,
};

static short _decode_memb[] = {
	0,
	107,
};

static short _decode_jaddr[] = {
	0,
	110,
	111,
};

static int _rule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 9)
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case _stmt_NT:	return _decode_stmt[((struct _state *)state)->rule._stmt];
	case _vr_NT:	return _decode_vr[((struct _state *)state)->rule._vr];
	case _reg_NT:	return _decode_reg[((struct _state *)state)->rule._reg];
	case _freg_NT:	return _decode_freg[((struct _state *)state)->rule._freg];
	case _freg8_NT:	return _decode_freg8[((struct _state *)state)->rule._freg8];
	case _cnst_NT:	return _decode_cnst[((struct _state *)state)->rule._cnst];
	case _saddr_NT:	return _decode_saddr[((struct _state *)state)->rule._saddr];
	case _memb_NT:	return _decode_memb[((struct _state *)state)->rule._memb];
	case _jaddr_NT:	return _decode_jaddr[((struct _state *)state)->rule._jaddr];
	default:
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
		return 0;
	}
}

static void _closure_reg(NODEPTR_TYPE, int);
static void _closure_freg(NODEPTR_TYPE, int);
static void _closure_freg8(NODEPTR_TYPE, int);
static void _closure_cnst(NODEPTR_TYPE, int);

static void _closure_reg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 1 < p->cost[_jaddr_NT]) {
		p->cost[_jaddr_NT] = c + 1;
		p->rule._jaddr = 2;
	}
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 10;
	}
}

static void _closure_freg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 11;
	}
}

static void _closure_freg8(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 12;
	}
}

static void _closure_cnst(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 0;
		p->rule._reg = 18;
		_closure_reg(a, c + 0);
	}
}

static void _label(NODEPTR_TYPE a) {
	int c;
	struct _state *p;

	if (!a)
		fatal("_label", "Null tree\n", 0);
	STATE_LABEL(a) = p = allocate(sizeof *p, FUNC);
	p->rule._stmt = 0;
	p->cost[1] =
	p->cost[2] =
	p->cost[3] =
	p->cost[4] =
	p->cost[5] =
	p->cost[6] =
	p->cost[7] =
	p->cost[8] =
	p->cost[9] =
		0x7fff;
	switch (OP_LABEL(a)) {
	case 41: /* ARGB */
		_label(LEFT_CHILD(a));
		/* stmt: ARGB(memb) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_memb_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 33;
		}
		break;
	case 57: /* ASGNB */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: ASGNB(reg,memb) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_memb_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 32;
		}
		break;
	case 73: /* INDIRB */
		_label(LEFT_CHILD(a));
		/* memb: INDIRB(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_memb_NT]) {
			p->cost[_memb_NT] = c + 0;
			p->rule._memb = 1;
		}
		break;
	case 216: /* CALLV */
		_label(LEFT_CHILD(a));
		/* stmt: CALLV(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 48;
		}
		break;
	case 217: /* CALLB */
		break;
	case 248: /* RETV */
		break;
	case 584: /* JUMPV */
		_label(LEFT_CHILD(a));
		/* stmt: JUMPV(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 35;
		}
		break;
	case 600: /* LABELV */
		/* stmt: LABELV */
		if (0 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 0 + 0;
			p->rule._stmt = 34;
		}
		break;
	case 711: /* VREGP */
		/* vr: VREGP */
		if (0 + 0 < p->cost[_vr_NT]) {
			p->cost[_vr_NT] = 0 + 0;
			p->rule._vr = 1;
		}
		break;
	case 1045: /* CNSTI1 */
		/* cnst: CNSTI1 */
		if (0 + 0 < p->cost[_cnst_NT]) {
			p->cost[_cnst_NT] = 0 + 0;
			p->rule._cnst = 1;
			_closure_cnst(a, 0 + 0);
		}
		break;
	case 1046: /* CNSTU1 */
		/* cnst: CNSTU1 */
		if (0 + 0 < p->cost[_cnst_NT]) {
			p->cost[_cnst_NT] = 0 + 0;
			p->rule._cnst = 2;
			_closure_cnst(a, 0 + 0);
		}
		break;
	case 1077: /* ASGNI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI1(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 1;
			}
		}
		/* stmt: ASGNI1(saddr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 13;
		}
		/* stmt: ASGNI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 22;
		}
		break;
	case 1078: /* ASGNU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU1(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 2;
			}
		}
		/* stmt: ASGNU1(saddr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 14;
		}
		/* stmt: ASGNU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 23;
		}
		break;
	case 1093: /* INDIRI1 */
		_label(LEFT_CHILD(a));
		/* reg: INDIRI1(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 1;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 8;
			_closure_reg(a, c + 0);
		}
		break;
	case 1094: /* INDIRU1 */
		_label(LEFT_CHILD(a));
		/* reg: INDIRU1(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 2;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 9;
			_closure_reg(a, c + 0);
		}
		break;
	case 1157: /* CVII1 */
		_label(LEFT_CHILD(a));
		/* reg: CVII1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 53;
			_closure_reg(a, c + 0);
		}
		break;
	case 1158: /* CVIU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 55;
			_closure_reg(a, c + 0);
		}
		break;
	case 1205: /* CVUI1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 56;
			_closure_reg(a, c + 0);
		}
		break;
	case 1206: /* CVUU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 54;
			_closure_reg(a, c + 0);
		}
		break;
	case 1253: /* LOADI1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 19;
			_closure_reg(a, c + 0);
		}
		break;
	case 1254: /* LOADU1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 22;
			_closure_reg(a, c + 0);
		}
		break;
	case 2069: /* CNSTI2 */
		/* cnst: CNSTI2 */
		if (0 + 0 < p->cost[_cnst_NT]) {
			p->cost[_cnst_NT] = 0 + 0;
			p->rule._cnst = 6;
			_closure_cnst(a, 0 + 0);
		}
		break;
	case 2070: /* CNSTU2 */
		/* cnst: CNSTU2 */
		if (0 + 0 < p->cost[_cnst_NT]) {
			p->cost[_cnst_NT] = 0 + 0;
			p->rule._cnst = 7;
			_closure_cnst(a, 0 + 0);
		}
		break;
	case 2101: /* ASGNI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 3;
			}
		}
		/* stmt: ASGNI2(saddr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 15;
		}
		/* stmt: ASGNI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 24;
		}
		break;
	case 2102: /* ASGNU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 4;
			}
		}
		/* stmt: ASGNU2(saddr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 16;
		}
		/* stmt: ASGNU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 25;
		}
		break;
	case 2117: /* INDIRI2 */
		_label(LEFT_CHILD(a));
		/* reg: INDIRI2(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 3;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 10;
			_closure_reg(a, c + 0);
		}
		break;
	case 2118: /* INDIRU2 */
		_label(LEFT_CHILD(a));
		/* reg: INDIRU2(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 4;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 11;
			_closure_reg(a, c + 0);
		}
		break;
	case 2181: /* CVII2 */
		_label(LEFT_CHILD(a));
		/* reg: CVII2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 57;
			_closure_reg(a, c + 0);
		}
		break;
	case 2182: /* CVIU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 58;
			_closure_reg(a, c + 0);
		}
		break;
	case 2229: /* CVUI2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 59;
			_closure_reg(a, c + 0);
		}
		break;
	case 2230: /* CVUU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 60;
			_closure_reg(a, c + 0);
		}
		break;
	case 2277: /* LOADI2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 20;
			_closure_reg(a, c + 0);
		}
		break;
	case 2278: /* LOADU2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 23;
			_closure_reg(a, c + 0);
		}
		break;
	case 4113: /* CNSTF4 */
		break;
	case 4117: /* CNSTI4 */
		/* cnst: CNSTI4 */
		if (0 + 0 < p->cost[_cnst_NT]) {
			p->cost[_cnst_NT] = 0 + 0;
			p->rule._cnst = 3;
			_closure_cnst(a, 0 + 0);
		}
		break;
	case 4118: /* CNSTU4 */
		/* cnst: CNSTU4 */
		if (0 + 0 < p->cost[_cnst_NT]) {
			p->cost[_cnst_NT] = 0 + 0;
			p->rule._cnst = 4;
			_closure_cnst(a, 0 + 0);
		}
		break;
	case 4119: /* CNSTP4 */
		/* cnst: CNSTP4 */
		if (0 + 0 < p->cost[_cnst_NT]) {
			p->cost[_cnst_NT] = 0 + 0;
			p->rule._cnst = 5;
			_closure_cnst(a, 0 + 0);
		}
		break;
	case 4129: /* ARGF4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGF4(freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 56;
		}
		break;
	case 4133: /* ARGI4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 29;
		}
		break;
	case 4134: /* ARGU4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 30;
		}
		break;
	case 4135: /* ARGP4 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGP4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 31;
		}
		break;
	case 4145: /* ASGNF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNF4(VREGP,freg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 8;
			}
		}
		/* stmt: ASGNF4(saddr,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 20;
		}
		/* stmt: ASGNF4(reg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 54;
		}
		break;
	case 4149: /* ASGNI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 5;
			}
		}
		/* stmt: ASGNI4(saddr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 17;
		}
		/* stmt: ASGNI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 26;
		}
		break;
	case 4150: /* ASGNU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 6;
			}
		}
		/* stmt: ASGNU4(saddr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 18;
		}
		/* stmt: ASGNU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 27;
		}
		break;
	case 4151: /* ASGNP4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNP4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 7;
			}
		}
		/* stmt: ASGNP4(saddr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 19;
		}
		/* stmt: ASGNP4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 28;
		}
		break;
	case 4161: /* INDIRF4 */
		_label(LEFT_CHILD(a));
		/* freg: INDIRF4(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 1;
			_closure_freg(a, c + 0);
		}
		/* freg: INDIRF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 2;
			_closure_freg(a, c + 0);
		}
		break;
	case 4165: /* INDIRI4 */
		_label(LEFT_CHILD(a));
		/* reg: INDIRI4(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 5;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 12;
			_closure_reg(a, c + 0);
		}
		break;
	case 4166: /* INDIRU4 */
		_label(LEFT_CHILD(a));
		/* reg: INDIRU4(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 6;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 13;
			_closure_reg(a, c + 0);
		}
		break;
	case 4167: /* INDIRP4 */
		_label(LEFT_CHILD(a));
		/* reg: INDIRP4(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 7;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRP4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 14;
			_closure_reg(a, c + 0);
		}
		break;
	case 4209: /* CVFF4 */
		_label(LEFT_CHILD(a));
		/* freg: CVFF4(freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 8;
			_closure_freg(a, c + 0);
		}
		/* freg: CVFF4(freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 9;
			_closure_freg(a, c + 0);
		}
		break;
	case 4213: /* CVFI4 */
		_label(LEFT_CHILD(a));
		/* reg: CVFI4(freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 68;
			_closure_reg(a, c + 0);
		}
		/* reg: CVFI4(freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 69;
			_closure_reg(a, c + 0);
		}
		break;
	case 4225: /* CVIF4 */
		_label(LEFT_CHILD(a));
		/* freg: CVIF4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 10;
			_closure_freg(a, c + 0);
		}
		break;
	case 4229: /* CVII4 */
		_label(LEFT_CHILD(a));
		/* reg: CVII4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 61;
			_closure_reg(a, c + 0);
		}
		break;
	case 4230: /* CVIU4 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 62;
			_closure_reg(a, c + 0);
		}
		break;
	case 4246: /* CVPU4 */
		_label(LEFT_CHILD(a));
		/* reg: CVPU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 51;
			_closure_reg(a, c + 0);
		}
		break;
	case 4277: /* CVUI4 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 63;
			_closure_reg(a, c + 0);
		}
		break;
	case 4278: /* CVUU4 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 64;
			_closure_reg(a, c + 0);
		}
		break;
	case 4279: /* CVUP4 */
		_label(LEFT_CHILD(a));
		/* reg: CVUP4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 52;
			_closure_reg(a, c + 0);
		}
		break;
	case 4289: /* NEGF4 */
		_label(LEFT_CHILD(a));
		/* freg: NEGF4(freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 3;
			_closure_freg(a, c + 0);
		}
		break;
	case 4293: /* NEGI4 */
		_label(LEFT_CHILD(a));
		/* reg: NEGI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 40;
			_closure_reg(a, c + 0);
		}
		break;
	case 4305: /* CALLF4 */
		_label(LEFT_CHILD(a));
		/* freg: CALLF4(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 11;
			_closure_freg(a, c + 0);
		}
		/* stmt: CALLF4(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 70;
		}
		break;
	case 4309: /* CALLI4 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI4(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 65;
			_closure_reg(a, c + 0);
		}
		break;
	case 4310: /* CALLU4 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU4(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 66;
			_closure_reg(a, c + 0);
		}
		break;
	case 4311: /* CALLP4 */
		_label(LEFT_CHILD(a));
		/* reg: CALLP4(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 67;
			_closure_reg(a, c + 0);
		}
		break;
	case 4321: /* LOADF4 */
		break;
	case 4325: /* LOADI4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 21;
			_closure_reg(a, c + 0);
		}
		break;
	case 4326: /* LOADU4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 24;
			_closure_reg(a, c + 0);
		}
		break;
	case 4327: /* LOADP4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADP4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 25;
			_closure_reg(a, c + 0);
		}
		break;
	case 4337: /* RETF4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETF4(freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 52;
		}
		break;
	case 4341: /* RETI4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 49;
		}
		break;
	case 4342: /* RETU4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 50;
		}
		break;
	case 4343: /* RETP4 */
		_label(LEFT_CHILD(a));
		/* stmt: RETP4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 51;
		}
		break;
	case 4359: /* ADDRGP4 */
		/* reg: ADDRGP4 */
		if (0 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 0 + 0;
			p->rule._reg = 15;
			_closure_reg(a, 0 + 0);
		}
		/* jaddr: ADDRGP4 */
		if (0 + 0 < p->cost[_jaddr_NT]) {
			p->cost[_jaddr_NT] = 0 + 0;
			p->rule._jaddr = 1;
		}
		break;
	case 4375: /* ADDRFP4 */
		/* reg: ADDRFP4 */
		if (0 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 0 + 0;
			p->rule._reg = 17;
			_closure_reg(a, 0 + 0);
		}
		break;
	case 4391: /* ADDRLP4 */
		/* reg: ADDRLP4 */
		if (0 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 0 + 0;
			p->rule._reg = 16;
			_closure_reg(a, 0 + 0);
		}
		/* saddr: ADDRLP4 */
		if (0 + 0 < p->cost[_saddr_NT]) {
			p->cost[_saddr_NT] = 0 + 0;
			p->rule._saddr = 1;
		}
		break;
	case 4401: /* ADDF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg: ADDF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 4;
			_closure_freg(a, c + 0);
		}
		break;
	case 4405: /* ADDI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 26;
			_closure_reg(a, c + 0);
		}
		break;
	case 4406: /* ADDU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 28;
			_closure_reg(a, c + 0);
		}
		break;
	case 4407: /* ADDP4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDP4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 27;
			_closure_reg(a, c + 0);
		}
		break;
	case 4417: /* SUBF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg: SUBF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 7;
			_closure_freg(a, c + 0);
		}
		break;
	case 4421: /* SUBI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 29;
			_closure_reg(a, c + 0);
		}
		break;
	case 4422: /* SUBU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 31;
			_closure_reg(a, c + 0);
		}
		break;
	case 4423: /* SUBP4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBP4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 30;
			_closure_reg(a, c + 0);
		}
		break;
	case 4437: /* LSHI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 41;
			_closure_reg(a, c + 0);
		}
		break;
	case 4438: /* LSHU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 42;
			_closure_reg(a, c + 0);
		}
		break;
	case 4453: /* MODI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 50;
			_closure_reg(a, c + 0);
		}
		break;
	case 4454: /* MODU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 49;
			_closure_reg(a, c + 0);
		}
		break;
	case 4469: /* RSHI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 43;
			_closure_reg(a, c + 0);
		}
		break;
	case 4470: /* RSHU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 44;
			_closure_reg(a, c + 0);
		}
		break;
	case 4485: /* BANDI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 32;
			_closure_reg(a, c + 0);
		}
		break;
	case 4486: /* BANDU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 33;
			_closure_reg(a, c + 0);
		}
		break;
	case 4501: /* BCOMI4 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 38;
			_closure_reg(a, c + 0);
		}
		break;
	case 4502: /* BCOMU4 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 39;
			_closure_reg(a, c + 0);
		}
		break;
	case 4517: /* BORI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 34;
			_closure_reg(a, c + 0);
		}
		break;
	case 4518: /* BORU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 35;
			_closure_reg(a, c + 0);
		}
		break;
	case 4533: /* BXORI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 36;
			_closure_reg(a, c + 0);
		}
		break;
	case 4534: /* BXORU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 37;
			_closure_reg(a, c + 0);
		}
		break;
	case 4545: /* DIVF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg: DIVF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 5;
			_closure_freg(a, c + 0);
		}
		break;
	case 4549: /* DIVI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 48;
			_closure_reg(a, c + 0);
		}
		break;
	case 4550: /* DIVU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 47;
			_closure_reg(a, c + 0);
		}
		break;
	case 4561: /* MULF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg: MULF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_freg_NT]) {
			p->cost[_freg_NT] = c + 0;
			p->rule._freg = 6;
			_closure_freg(a, c + 0);
		}
		break;
	case 4565: /* MULI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 45;
			_closure_reg(a, c + 0);
		}
		break;
	case 4566: /* MULU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 46;
			_closure_reg(a, c + 0);
		}
		break;
	case 4577: /* EQF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 58;
		}
		break;
	case 4581: /* EQI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 36;
		}
		break;
	case 4582: /* EQU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 42;
		}
		break;
	case 4593: /* GEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 59;
		}
		break;
	case 4597: /* GEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 37;
		}
		break;
	case 4598: /* GEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 43;
		}
		break;
	case 4609: /* GTF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 60;
		}
		break;
	case 4613: /* GTI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 38;
		}
		break;
	case 4614: /* GTU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 44;
		}
		break;
	case 4625: /* LEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 61;
		}
		break;
	case 4629: /* LEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 39;
		}
		break;
	case 4630: /* LEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 45;
		}
		break;
	case 4641: /* LTF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 62;
		}
		break;
	case 4645: /* LTI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 40;
		}
		break;
	case 4646: /* LTU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 46;
		}
		break;
	case 4657: /* NEF4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEF4(freg,freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 63;
		}
		break;
	case 4661: /* NEI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 41;
		}
		break;
	case 4662: /* NEU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU4(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 47;
		}
		break;
	case 8209: /* CNSTF8 */
		break;
	case 8213: /* CNSTI8 */
		break;
	case 8214: /* CNSTU8 */
		break;
	case 8225: /* ARGF8 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGF8(freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 57;
		}
		break;
	case 8229: /* ARGI8 */
		break;
	case 8230: /* ARGU8 */
		break;
	case 8241: /* ASGNF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNF8(VREGP,freg8) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 9;
			}
		}
		/* stmt: ASGNF8(saddr,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_saddr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 21;
		}
		/* stmt: ASGNF8(reg,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 55;
		}
		break;
	case 8245: /* ASGNI8 */
		break;
	case 8246: /* ASGNU8 */
		break;
	case 8257: /* INDIRF8 */
		_label(LEFT_CHILD(a));
		/* freg8: INDIRF8(vr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_vr_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 1;
			_closure_freg8(a, c + 0);
		}
		/* freg8: INDIRF8(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 2;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8261: /* INDIRI8 */
		break;
	case 8262: /* INDIRU8 */
		break;
	case 8305: /* CVFF8 */
		_label(LEFT_CHILD(a));
		/* freg8: CVFF8(freg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 8;
			_closure_freg8(a, c + 0);
		}
		/* freg8: CVFF8(freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 9;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8309: /* CVFI8 */
		break;
	case 8321: /* CVIF8 */
		_label(LEFT_CHILD(a));
		/* freg8: CVIF8(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 10;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8325: /* CVII8 */
		break;
	case 8326: /* CVIU8 */
		break;
	case 8373: /* CVUI8 */
		break;
	case 8374: /* CVUU8 */
		break;
	case 8385: /* NEGF8 */
		_label(LEFT_CHILD(a));
		/* freg8: NEGF8(freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 3;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8389: /* NEGI8 */
		break;
	case 8401: /* CALLF8 */
		_label(LEFT_CHILD(a));
		/* freg8: CALLF8(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 11;
			_closure_freg8(a, c + 0);
		}
		/* stmt: CALLF8(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 71;
		}
		break;
	case 8405: /* CALLI8 */
		break;
	case 8406: /* CALLU8 */
		break;
	case 8417: /* LOADF8 */
		break;
	case 8433: /* RETF8 */
		_label(LEFT_CHILD(a));
		/* stmt: RETF8(freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 53;
		}
		break;
	case 8437: /* RETI8 */
		break;
	case 8438: /* RETU8 */
		break;
	case 8497: /* ADDF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg8: ADDF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 4;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8501: /* ADDI8 */
		break;
	case 8502: /* ADDU8 */
		break;
	case 8513: /* SUBF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg8: SUBF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 7;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8517: /* SUBI8 */
		break;
	case 8518: /* SUBU8 */
		break;
	case 8533: /* LSHI8 */
		break;
	case 8534: /* LSHU8 */
		break;
	case 8549: /* MODI8 */
		break;
	case 8550: /* MODU8 */
		break;
	case 8565: /* RSHI8 */
		break;
	case 8566: /* RSHU8 */
		break;
	case 8581: /* BANDI8 */
		break;
	case 8582: /* BANDU8 */
		break;
	case 8597: /* BCOMI8 */
		break;
	case 8598: /* BCOMU8 */
		break;
	case 8613: /* BORI8 */
		break;
	case 8614: /* BORU8 */
		break;
	case 8629: /* BXORI8 */
		break;
	case 8630: /* BXORU8 */
		break;
	case 8641: /* DIVF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg8: DIVF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 5;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8645: /* DIVI8 */
		break;
	case 8646: /* DIVU8 */
		break;
	case 8657: /* MULF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* freg8: MULF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_freg8_NT]) {
			p->cost[_freg8_NT] = c + 0;
			p->rule._freg8 = 6;
			_closure_freg8(a, c + 0);
		}
		break;
	case 8661: /* MULI8 */
		break;
	case 8662: /* MULU8 */
		break;
	case 8673: /* EQF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 64;
		}
		break;
	case 8677: /* EQI8 */
		break;
	case 8678: /* EQU8 */
		break;
	case 8689: /* GEF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 65;
		}
		break;
	case 8693: /* GEI8 */
		break;
	case 8694: /* GEU8 */
		break;
	case 8705: /* GTF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 66;
		}
		break;
	case 8709: /* GTI8 */
		break;
	case 8710: /* GTU8 */
		break;
	case 8721: /* LEF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 67;
		}
		break;
	case 8725: /* LEI8 */
		break;
	case 8726: /* LEU8 */
		break;
	case 8737: /* LTF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 68;
		}
		break;
	case 8741: /* LTI8 */
		break;
	case 8742: /* LTU8 */
		break;
	case 8753: /* NEF8 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEF8(freg8,freg8) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_freg8_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_freg8_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 69;
		}
		break;
	case 8757: /* NEI8 */
		break;
	case 8758: /* NEU8 */
		break;
	default:
		fatal("_label", "Bad terminal %d\n", OP_LABEL(a));
	}
}

static void _kids(NODEPTR_TYPE p, int eruleno, NODEPTR_TYPE kids[]) {
	if (!p)
		fatal("_kids", "Null tree\n", 0);
	if (!kids)
		fatal("_kids", "Null kids\n", 0);
	switch (eruleno) {
	case 112: /* stmt: LABELV */
	case 110: /* jaddr: ADDRGP4 */
	case 87: /* saddr: ADDRLP4 */
	case 39: /* reg: ADDRFP4 */
	case 38: /* reg: ADDRLP4 */
	case 37: /* reg: ADDRGP4 */
	case 26: /* cnst: CNSTU2 */
	case 25: /* cnst: CNSTI2 */
	case 24: /* cnst: CNSTP4 */
	case 23: /* cnst: CNSTU4 */
	case 22: /* cnst: CNSTI4 */
	case 21: /* cnst: CNSTU1 */
	case 20: /* cnst: CNSTI1 */
	case 1: /* vr: VREGP */
		break;
	case 174: /* stmt: CALLF8(jaddr) */
	case 173: /* stmt: CALLF4(jaddr) */
	case 172: /* freg8: CALLF8(jaddr) */
	case 171: /* freg: CALLF4(jaddr) */
	case 158: /* freg8: CVIF8(reg) */
	case 157: /* freg: CVIF4(reg) */
	case 156: /* reg: CVFI4(freg8) */
	case 155: /* reg: CVFI4(freg) */
	case 154: /* freg8: CVFF8(freg8) */
	case 153: /* freg8: CVFF8(freg) */
	case 152: /* freg: CVFF4(freg8) */
	case 151: /* freg: CVFF4(freg) */
	case 142: /* freg8: NEGF8(freg8) */
	case 141: /* freg: NEGF4(freg) */
	case 140: /* stmt: ARGF8(freg8) */
	case 139: /* stmt: ARGF4(freg) */
	case 136: /* freg8: INDIRF8(reg) */
	case 135: /* freg: INDIRF4(reg) */
	case 134: /* stmt: RETF8(freg8) */
	case 133: /* stmt: RETF4(freg) */
	case 132: /* stmt: RETP4(reg) */
	case 131: /* stmt: RETU4(reg) */
	case 130: /* stmt: RETI4(reg) */
	case 129: /* stmt: CALLV(jaddr) */
	case 128: /* reg: CALLP4(jaddr) */
	case 127: /* reg: CALLU4(jaddr) */
	case 126: /* reg: CALLI4(jaddr) */
	case 113: /* stmt: JUMPV(jaddr) */
	case 109: /* stmt: ARGB(memb) */
	case 107: /* memb: INDIRB(reg) */
	case 106: /* stmt: ARGP4(reg) */
	case 105: /* stmt: ARGU4(reg) */
	case 104: /* stmt: ARGI4(reg) */
	case 86: /* reg: CVUU4(reg) */
	case 85: /* reg: CVUI4(reg) */
	case 84: /* reg: CVIU4(reg) */
	case 83: /* reg: CVII4(reg) */
	case 82: /* reg: CVUU2(reg) */
	case 81: /* reg: CVUI2(reg) */
	case 80: /* reg: CVIU2(reg) */
	case 79: /* reg: CVII2(reg) */
	case 78: /* reg: CVUI1(reg) */
	case 77: /* reg: CVIU1(reg) */
	case 76: /* reg: CVUU1(reg) */
	case 75: /* reg: CVII1(reg) */
	case 74: /* reg: CVUP4(reg) */
	case 73: /* reg: CVPU4(reg) */
	case 62: /* reg: NEGI4(reg) */
	case 61: /* reg: BCOMU4(reg) */
	case 60: /* reg: BCOMI4(reg) */
	case 47: /* reg: LOADP4(reg) */
	case 46: /* reg: LOADU4(reg) */
	case 45: /* reg: LOADU2(reg) */
	case 44: /* reg: LOADU1(reg) */
	case 43: /* reg: LOADI4(reg) */
	case 42: /* reg: LOADI2(reg) */
	case 41: /* reg: LOADI1(reg) */
	case 36: /* reg: INDIRP4(reg) */
	case 35: /* reg: INDIRU4(reg) */
	case 34: /* reg: INDIRI4(reg) */
	case 33: /* reg: INDIRU2(reg) */
	case 32: /* reg: INDIRI2(reg) */
	case 31: /* reg: INDIRU1(reg) */
	case 30: /* reg: INDIRI1(reg) */
	case 10: /* freg8: INDIRF8(vr) */
	case 9: /* freg: INDIRF4(vr) */
	case 8: /* reg: INDIRP4(vr) */
	case 7: /* reg: INDIRU4(vr) */
	case 6: /* reg: INDIRI4(vr) */
	case 5: /* reg: INDIRU2(vr) */
	case 4: /* reg: INDIRI2(vr) */
	case 3: /* reg: INDIRU1(vr) */
	case 2: /* reg: INDIRI1(vr) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 19: /* stmt: ASGNF8(VREGP,freg8) */
	case 18: /* stmt: ASGNF4(VREGP,freg) */
	case 17: /* stmt: ASGNP4(VREGP,reg) */
	case 16: /* stmt: ASGNU4(VREGP,reg) */
	case 15: /* stmt: ASGNI4(VREGP,reg) */
	case 14: /* stmt: ASGNU2(VREGP,reg) */
	case 13: /* stmt: ASGNI2(VREGP,reg) */
	case 12: /* stmt: ASGNU1(VREGP,reg) */
	case 11: /* stmt: ASGNI1(VREGP,reg) */
		kids[0] = RIGHT_CHILD(p);
		break;
	case 111: /* jaddr: reg */
	case 40: /* reg: cnst */
	case 29: /* stmt: freg8 */
	case 28: /* stmt: freg */
	case 27: /* stmt: reg */
		kids[0] = p;
		break;
	case 170: /* stmt: NEF8(freg8,freg8) */
	case 169: /* stmt: LTF8(freg8,freg8) */
	case 168: /* stmt: LEF8(freg8,freg8) */
	case 167: /* stmt: GTF8(freg8,freg8) */
	case 166: /* stmt: GEF8(freg8,freg8) */
	case 165: /* stmt: EQF8(freg8,freg8) */
	case 164: /* stmt: NEF4(freg,freg) */
	case 163: /* stmt: LTF4(freg,freg) */
	case 162: /* stmt: LEF4(freg,freg) */
	case 161: /* stmt: GTF4(freg,freg) */
	case 160: /* stmt: GEF4(freg,freg) */
	case 159: /* stmt: EQF4(freg,freg) */
	case 150: /* freg8: SUBF8(freg8,freg8) */
	case 149: /* freg8: MULF8(freg8,freg8) */
	case 148: /* freg8: DIVF8(freg8,freg8) */
	case 147: /* freg8: ADDF8(freg8,freg8) */
	case 146: /* freg: SUBF4(freg,freg) */
	case 145: /* freg: MULF4(freg,freg) */
	case 144: /* freg: DIVF4(freg,freg) */
	case 143: /* freg: ADDF4(freg,freg) */
	case 138: /* stmt: ASGNF8(reg,freg8) */
	case 137: /* stmt: ASGNF4(reg,freg) */
	case 125: /* stmt: NEU4(reg,reg) */
	case 124: /* stmt: LTU4(reg,reg) */
	case 123: /* stmt: LEU4(reg,reg) */
	case 122: /* stmt: GTU4(reg,reg) */
	case 121: /* stmt: GEU4(reg,reg) */
	case 120: /* stmt: EQU4(reg,reg) */
	case 119: /* stmt: NEI4(reg,reg) */
	case 118: /* stmt: LTI4(reg,reg) */
	case 117: /* stmt: LEI4(reg,reg) */
	case 116: /* stmt: GTI4(reg,reg) */
	case 115: /* stmt: GEI4(reg,reg) */
	case 114: /* stmt: EQI4(reg,reg) */
	case 108: /* stmt: ASGNB(reg,memb) */
	case 103: /* stmt: ASGNP4(reg,reg) */
	case 102: /* stmt: ASGNU4(reg,reg) */
	case 101: /* stmt: ASGNI4(reg,reg) */
	case 100: /* stmt: ASGNU2(reg,reg) */
	case 99: /* stmt: ASGNI2(reg,reg) */
	case 98: /* stmt: ASGNU1(reg,reg) */
	case 97: /* stmt: ASGNI1(reg,reg) */
	case 96: /* stmt: ASGNF8(saddr,freg8) */
	case 95: /* stmt: ASGNF4(saddr,freg) */
	case 94: /* stmt: ASGNP4(saddr,reg) */
	case 93: /* stmt: ASGNU4(saddr,reg) */
	case 92: /* stmt: ASGNI4(saddr,reg) */
	case 91: /* stmt: ASGNU2(saddr,reg) */
	case 90: /* stmt: ASGNI2(saddr,reg) */
	case 89: /* stmt: ASGNU1(saddr,reg) */
	case 88: /* stmt: ASGNI1(saddr,reg) */
	case 72: /* reg: MODI4(reg,reg) */
	case 71: /* reg: MODU4(reg,reg) */
	case 70: /* reg: DIVI4(reg,reg) */
	case 69: /* reg: DIVU4(reg,reg) */
	case 68: /* reg: MULU4(reg,reg) */
	case 67: /* reg: MULI4(reg,reg) */
	case 66: /* reg: RSHU4(reg,reg) */
	case 65: /* reg: RSHI4(reg,reg) */
	case 64: /* reg: LSHU4(reg,reg) */
	case 63: /* reg: LSHI4(reg,reg) */
	case 59: /* reg: BXORU4(reg,reg) */
	case 58: /* reg: BXORI4(reg,reg) */
	case 57: /* reg: BORU4(reg,reg) */
	case 56: /* reg: BORI4(reg,reg) */
	case 55: /* reg: BANDU4(reg,reg) */
	case 54: /* reg: BANDI4(reg,reg) */
	case 53: /* reg: SUBU4(reg,reg) */
	case 52: /* reg: SUBP4(reg,reg) */
	case 51: /* reg: SUBI4(reg,reg) */
	case 50: /* reg: ADDU4(reg,reg) */
	case 49: /* reg: ADDP4(reg,reg) */
	case 48: /* reg: ADDI4(reg,reg) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	default:
		fatal("_kids", "Bad rule number %d\n", eruleno);
	}
}

