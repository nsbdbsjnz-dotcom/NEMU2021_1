#include "cpu/exec/arith/add.h"
#include "cpu/exec/arith/adc.h"
#include "cpu/exec/arith/sub.h"
#include "cpu/exec/arith/sbb.h"
#include "cpu/exec/arith/cmp.h"
#include "cpu/exec/arith/inc.h"
#include "cpu/exec/arith/dec.h"
#include "cpu/exec/arith/neg.h"
#include "cpu/exec/arith/mul.h"
#include "cpu/exec/arith/imul.h"
#include "cpu/exec/arith/div.h"
#include "cpu/exec/arith/idiv.h"

#include "cpu/exec/logic/and.h"
#include "cpu/exec/logic/or.h"
#include "cpu/exec/logic/not.h"
#include "cpu/exec/logic/xor.h"
#include "cpu/exec/logic/shl.h"
#include "cpu/exec/logic/shr.h"
#include "cpu/exec/logic/shrd.h"
#include "cpu/exec/logic/sar.h"
#include "cpu/exec/logic/setcc.h"
#include "cpu/exec/logic/test.h"

#include "cpu/exec/string/rep.h"
#include "cpu/exec/string/movs.h"
#include "cpu/exec/string/lods.h"
#include "cpu/exec/string/stos.h"
#include "cpu/exec/string/scas.h"

#include "cpu/exec/control/call.h"
#include "cpu/exec/control/jmp.h"
#include "cpu/exec/control/ret.h"
#include "cpu/exec/control/jcc.h" // 确保这一行在

#include "cpu/exec/data-mov/mov.h"
#include "cpu/exec/data-mov/xchg.h"
#include "cpu/exec/data-mov/push.h"
#include "cpu/exec/data-mov/pop.h"
#include "cpu/exec/data-mov/leave.h"
#include "cpu/exec/data-mov/cltd.h"
#include "cpu/exec/data-mov/movext.h"

#include "cpu/exec/misc/misc.h"
#include "cpu/exec/special/special.h"
#include "cpu/exec/prefix/prefix.h"

#include "cpu/exec/helper.h"

/* 临时声明系统指令，防止 exec.c 报错 */
make_helper(lgdt);
make_helper(lidt);
make_helper(mov_r2cr);
make_helper(mov_cr2r);
make_helper(mov_rm2sreg);
make_helper(mov_cr2rm);
make_helper(mov_rm2cr);