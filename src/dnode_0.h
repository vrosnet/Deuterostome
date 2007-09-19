/*=================== D machine Rev3.0: dnode_0.c =====================

  Include module for dnode.c: operator and error lists of dnode.
*/

/*--- LL */
L op_loadlib(void);
L op_nextlib(void);
L op_getplugindir(void);

/*--- threads */
L op_makethreads(void);
L op_threads(void);

B *sysop[] =
{
      "lock",        (B*) op_lock,
	  "serialize",   (B*) op_serialize,
#if ENABLE_THREADS
	  "threads",     (B*) op_threads,
	  "makethreads", (B*) op_makethreads,
#endif //ENABLE_THREADS

/*-- hi */
      "hi",            (B*) op_syshi,
      "libnum",        (B*) op_syslibnum,
       
/*-- load library */
      "loadlib",       (B*) op_loadlib,
      "nextlib",       (B*) op_nextlib,
      
/*-- dnode specific */
      "toconsole",      (B *)op_toconsole,
      "tostderr",       (B *)op_tostderr,
      "setconsole",     (B *)op_setconsole,
      "console",        (B *)op_console,
      "error",          (B *)op_error,
      "errormessage",   (B *)op_errormessage,
      "abort",          (B *)op_abort,
      "halt",           (B *)op_halt,
      "continue",       (B *)op_continue,
      "vmresize",       (B *)op_vmresize,
	  "killsockets",    (B *)op_killsockets,
      "getmyport",      (B *)op_getmyport,

/*-- network */
      "connect",        (B *)op_connect,
      "disconnect",     (B *)op_disconnect,
      "send",           (B *)op_send,
      "getsocket",      (B *)op_getsocket,
      "getmyname",      (B *)op_getmyname,

/*-- X windows */
	  "Xwindows",       (B *)op_Xwindows,
	  "Xwindows_",      (B *)op_Xwindows_,
      "Xconnect",       (B *)op_Xconnect,
      "Xdisplayname",   (B *)op_Xdisplayname,
      "Xdisconnect",    (B *)op_Xdisconnect,
      "screensize",     (B *)op_screensize,
      "makewindow",     (B *)op_makewindow,
      "deletewindow",   (B *)op_deletewindow,
      "mapwindow",      (B *)op_mapwindow,
      "resizewindow",   (B *)op_resizewindow,
      "Xsync",          (B *)op_Xsync,
      "mapcolor",       (B *)op_mapcolor,
      "drawline",       (B *)op_drawline,
      "drawsymbols",    (B *)op_drawsymbols,
      "fillrectangle",  (B *)op_fillrectangle,
      "drawtext",       (B *)op_drawtext,
      "makewindowtop",  (B *)op_makewindowtop,
      "setinputfocus",  (B *)op_setinputfocus,

/*-- operand stack */
      "pop",            (B *)op_pop,
      "exch",           (B *)op_exch,
      "dup",            (B *)op_dup,
      "copy",           (B *)op_copy,
      "index",          (B *)op_index,
      "roll",           (B *)op_roll,
      "clear",          (B *)op_clear,
      "count",          (B *)op_count,
      "cleartomark",    (B *)op_cleartomark,
      "counttomark",    (B *)op_counttomark,
/*-- dictionary, array, list */
      "currentdict",    (B *)op_currentdict,
      "]",              (B *)op_closelist, 
      "dict",           (B *)op_dict,
      "cleardict",      (B *)op_cleardict,
      "array",          (B *)op_array,
      "list",           (B *)op_list,
      "used",           (B *)op_used,
      "length",         (B *)op_length, 
      "begin",          (B *)op_begin,
      "end",            (B *)op_end,
      "def",            (B *)op_def,
      "name",           (B *)op_name,
      "find",           (B *)op_find,
      "get",            (B *)op_get,
      "put",            (B *)op_put,
      "known",          (B *)op_known,
      "getinterval",    (B *)op_getinterval,
      "countdictstack", (B *)op_countdictstack,
      "dictstack",      (B *)op_dictstack,
/*-- VM and miscellaneous */
      "save",           (B *)op_save,
      "capsave",        (B *)op_capsave,
      "restore",        (B *)op_restore,
			"setcleanup",     (B *)op_setcleanup,
      "vmstatus",       (B *)op_vmstatus,
      "bind",           (B *)op_bind,
      "null",           (B *)op_null,
/*-- control */
      "start",          (B *)op_start,
      "exec",           (B *)op_exec,
      "if",             (B *)op_if,
      "ifelse",         (B *)op_ifelse,
      "for",            (B *)op_for,
      "repeat",         (B *)op_repeat,
      "loop",           (B *)op_loop,
      "forall",         (B *)op_forall,
      "exit",           (B *)op_exit,
      "stop",           (B *)op_stop,
      "stopped",        (B *)op_stopped,
      "countexecstack", (B *)op_countexecstack,
      "execstack",      (B *)op_execstack,
/*-- math */
      "checkFPU",       (B *)op_checkFPU,
      "neg",            (B *)op_neg,
      "abs",            (B *)op_abs,
      "thearc",         (B *)op_thearc, 
      "add",            (B *)op_add,
      "mod",            (B *)op_mod,
      "sub",            (B *)op_sub,
      "mul",            (B *)op_mul,
      "div",            (B *)op_div,
      "sqrt",           (B *)op_sqrt,
      "exp",            (B *)op_exp,
      "ln",             (B *)op_ln,
      "lg",             (B *)op_lg,
      "pwr",            (B *)op_pwr,
      "cos",            (B *)op_cos,
      "sin",            (B *)op_sin,
      "tan",            (B *)op_tan,
      "atan",           (B *)op_atan,
      "floor",          (B *)op_floor,
      "ceil",           (B *)op_ceil,
      "asin",           (B *)op_asin,
      "acos",           (B *)op_acos,
/*-- relational, boolean, bitwise */ 
      "eq",             (B *)op_eq,
      "ne",             (B *)op_ne,
      "ge",             (B *)op_ge,
      "gt",             (B *)op_gt,
      "le",             (B *)op_le,
      "lt",             (B *)op_lt,
      "and",            (B *)op_and,
      "not",            (B *)op_not,
      "or",             (B *)op_or,
      "xor",            (B *)op_xor,
      "bitshift",       (B *)op_bitshift,
/*-- conversion, string, attribute, class ,type */
      "class",          (B *)op_class,
      "type",           (B *)op_type,
      "readonly",       (B *)op_readonly,
      "active",         (B *)op_active,
      "tilde",          (B *)op_tilde,
      "mkread",         (B *)op_mkread,
      "mkact",          (B *)op_mkact,
      "mkpass",         (B *)op_mkpass,
      "ctype",          (B *)op_ctype,
      "parcel",         (B *)op_parcel,
      "text",           (B *)op_text,
      "number",         (B *)op_number,
      "token",          (B *)op_token,
      "search",         (B *)op_search,
      "anchorsearch",   (B *)op_anchorsearch,
/*-- time/date and file access */
      "gettime",        (B *)op_gettime,
      "localtime",      (B *)op_localtime,
      "getwdir",        (B *)op_getwdir,
      "setwdir",        (B *)op_setwdir,
      "readfile",       (B *)op_readfile,
      "writefile",      (B *)op_writefile,
      "findfiles",      (B *)op_findfiles,
	  "findfile",       (B *)op_findfile,
      "readboxfile",    (B *)op_readboxfile,
      "writeboxfile",   (B *)op_writeboxfile,
      "tosystem",       (B *)op_tosystem,
			"fromsystem",     (B *)op_fromsystem,
      "transcribe",     (B *)op_transcribe,
/*-- more ... */
      "fax",            (B *)op_fax,
      "merge",          (B *)op_merge,
      "nextobject",     (B *)op_nextobject,
      "interpolate",    (B *)op_interpolate,
      "integrateOH",    (B *)op_integrateOH,
      "extrema",        (B *)op_extrema,
      "solvetridiag",   (B *)op_solvetridiag,
      "integrateOHv",   (B *)op_integrateOHv,
      "tile",           (B *)op_tile,
      "ramp",           (B *)op_ramp,
      "extract",        (B *)op_extract,
      "dilute",         (B *)op_dilute,
      "ran1",           (B *)op_ran1,
      "solve_bandmat",  (B *)op_solve_bandmat,
      "complexFFT",     (B *)op_complexFFT,
      "realFFT",        (B *)op_realFFT,
      "sineFFT",        (B *)op_sineFFT,
      "decompLU",       (B *)op_decompLU,
      "backsubLU",      (B *)op_backsubLU,
      "integrateRS",    (B *)op_integrateRS,
      "bandLU",         (B *)op_bandLU,
      "bandBS",         (B *)op_bandBS,
      "invertLU",       (B *)op_invertLU,
      "matmul",         (B *)op_matmul,
      "mattranspose",   (B *)op_mattranspose,
      "dilute_add",     (B *)op_dilute_add,
      "matvecmul",      (B *)op_matvecmul,
      "getstartupdir",  (B *)op_getstartupdir,
      "getconfdir",     (B *)op_getconfdir,
      "gethomedir",     (B *)op_gethomedir,
			"getplugindir",   (B *)op_getplugindir,
      "",               (B *)0L, 
 };     
   
   
/*========================== Error Table =================================

This has been expanded in order to accommodate external operator errors.
'errm' and 'errc' now are arrays of pointers rather than arrays of messages
or codes. Each pointer denotes an array of messages or codes; the first
pointer belongs to the basic dnode operator set.
*/

L syserrc[] =
{
    TIMER,CORR_OBJ,VM_OVF, LOST_CONN,
    OPDS_OVF, EXECS_OVF, DICTS_OVF, SAVE_OVF,
    OPDS_UNF, EXECS_UNF, DICTS_UNF, SAVE_UNF,
    INV_EXT, INV_STOP, EXECS_COR, INV_REST, 
    BAD_TOK, BAD_ASC, ARR_CLO, CLA_ARR, PRO_CLO,
    OPD_CLA, OPD_TYP, OPD_ERR, RNG_CHK, OPD_ATR, UNDF, DICT_ATR,
    DICT_OVF, DICT_USED, UNDF_VAL, DIR_NOSUCH,
    CORR_OP, BADBOX, BAD_MSG, NOSYSTEM, INV_MSG, NOT_HOST, BAD_FMT,
    LIB_LOAD, LIB_EXPORT, LIB_LINK, LIB_ADD, LIB_LOADED, LIB_OVF, LIB_MERGE,
    LIB_INIT,
    NO_XWINDOWS, X_ERR, X_BADFONT, X_BADHOST,
	VMR_ERR, VMR_STATE, ILL_OPAQUE, FOLD_OPAQUE, NOPLUGINS,
		MEM_OVF, BAD_ARR, SBOX_SET,
    0L,
};

B* syserrm[] =
{
    "** Timeout",
    "** Corrupted object",
    "** VM overflow",
    "** Lost connection",
    "** Operand stack overflow",
    "** Execution stack overflow",
    "** Dictionary stack overflow",
    "** Save stack overflow",
    "** Operand stack underflow",
    "** Execution stack underflow",
    "** Dictionary stack underflow",
    "** Save stack underflow",
    "** Invalid exit",
    "** Invalid stop",
    "** Execution stack corrupted",
    "** Stack holds discardable object",
    "** Bad token",
    "** Bad ASCII character",
    "** Unmatched array closure",
    "** Illegal class in array",
    "** Unmatched procedure closure",
    "** Operand class",
    "** Operand type in ",
    "** Operand class or type",
    "** Range check",
    "** Operand attribute",
    "** Undefined name",
    "** Dictionary attribute",
    "** Dictionary overflow",
    "** Dictionary used",
    "** Undefined value",
    "** No such directory/volume",
    "** Corrupted operator array",
    "** File does not contain a box object",
    "** Bad message received on network",
    "** 'System' call to Linux failed",
    "** Invalid message format",
    "** Hostname not in 'hosts' file",
    "** Box not in native format",
    "** Unable to load dynamically linked shared library",
    "** Unable to find object in shared library",
    "** Library has not been loaded",
    "** Unable to add operation to library dictionary",
    "** Library already loaded",
    "** Overflow in malloc while loading library",
    "** Unable to merge library into sysdict",
    "** Unable to initialize loaded library",
    "** X windows unavailable",
    "** Error in X windows",
    "** Bad X windows font",
    "** Cannot connect to X server",
	"** Cannot allocate D memory",
	"** Memory already minimized",
	"** Opaque dict type mismatch",
	"** Illegal attempt to fold opaque object",
	"** Compiled without plugin support",
	"** Memory exhausted",
    "** dmnuminc debug error",
		"** Box already has a cleanup handler"
};

// original directory for vmresize
char* original_dir;
L serverport;
B hostname[256];
