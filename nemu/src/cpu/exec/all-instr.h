#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/push.h"
#include "data-mov/pop.h"
#include "data-mov/movext.h"
#include "data-mov/cltd.h"
#include "data-mov/leave.h"

#include "arith/cmp.h"
#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/sub.h"
#include "arith/add.h"
#include "arith/adc.h"
#include "arith/sbb.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/test.h"
#include "logic/setcc.h"

#include "control/call.h"
#include "control/ret.h"
#include "control/jcc.h"
#include "control/jmp.h"

#include "string/rep.h"
#include "string/movs.h"
#include "string/lods.h"
#include "string/scas.h"
#include "string/stos.h"

#include "misc/misc.h"

#include "special/special.h"
/* Jcc (Condition Jump) Declarations */
// 8-bit versions (0x70 - 0x7F)
make_helper(jo_si_b);  make_helper(jno_si_b);
make_helper(jb_si_b);  make_helper(jae_si_b);
make_helper(je_si_b);  make_helper(jne_si_b);
make_helper(jbe_si_b); make_helper(ja_si_b);
make_helper(js_si_b);  make_helper(jns_si_b);
make_helper(jp_si_b);  make_helper(jnp_si_b);
make_helper(jl_si_b);  make_helper(jge_si_b);
make_helper(jle_si_b); make_helper(jg_si_b);

// Aliases for 8-bit
make_helper(jz_si_b);
make_helper(jnz_si_b);

// 16/32-bit versions (0x0F 8x)
make_helper_v(jo_si);  make_helper_v(jno_si);
make_helper_v(jb_si);  make_helper_v(jae_si);
make_helper_v(je_si);  make_helper_v(jne_si);
make_helper_v(jbe_si); make_helper_v(ja_si);
make_helper_v(js_si);  make_helper_v(jns_si);
make_helper_v(jp_si);  make_helper_v(jnp_si);
make_helper_v(jl_si);  make_helper_v(jge_si);
make_helper_v(jle_si); make_helper_v(jg_si);

// Aliases for 16/32-bit
make_helper_v(jz_si);
make_helper_v(jnz_si);

/* System Instructions (Stub declarations for PA3 compilation) */
// 为了解决 lgdt, mov_cr2rm 等报错，暂时在这里声明它们
// 如果你还没有实现 system.c，稍后会报 undefined reference，但至少能过编译阶段
make_helper(lgdt);
make_helper(mov_cr2rm);
make_helper(mov_rm2cr);
make_helper(mov_rm2sreg);