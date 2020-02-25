#pragma once
CMD_DEF(push,   cmd_pushd,  pusharg,     sized,    command)
CMD_DEF(push,   cmd_pushi,  pusharg,     sizei,    command)
CMD_DEF(popr,   cmd_popr,   regarg,      sizec,    command)// pop ax into stk
//CMD_DEF(pushr,  cmd_pushr,  pushrarg,    sizec,    command)// push ax 12.32
CMD_DEF(pushr,  cmd_pushr,  regarg,      sizec,    command)//push ax from stk
CMD_DEF(pop,    cmd_pop,    nullarg,     sizenull, command)// pop
CMD_DEF(ret,    cmd_ret,    nullarg,     sizenull, command)// return
CMD_DEF(add,    cmd_add,    nullarg,     sizenull, command)
CMD_DEF(fsqrt,  cmd_fsqrt,  nullarg,     sizenull, command)
CMD_DEF(mul,    cmd_mul,    nullarg,     sizenull, command)
CMD_DEF(sub,    cmd_sub,    nullarg,     sizenull, command)
CMD_DEF(div,    cmd_div,    nullarg,     sizenull, command)
CMD_DEF(back,   cmd_back,   nullarg,     sizenull, command)
CMD_DEF(clear,  cmd_clear,  nullarg,     sizenull, command)
CMD_DEF(size,   cmd_size,   nullarg,     sizenull, command)
CMD_DEF(jmp,    cmd_jmp,    jmparg,      sizenull, command)
CMD_DEF(end,    cmd_end,    endarg,      sizenull, command)
CMD_DEF(begin,  cmd_begin,  twoarg,      sizei,    command)// begin VS 1
CMD_DEF(resize, cmd_resize, onearg,      sizei,    command)
//CMD_DEF(call,   cmd_call,   callarg,     sizei,    command)// 
CMD_DEF(call,   cmd_call,   jmparg,      sizei,    command)
CMD_DEF(jxx,    cmd_jxx,    jmparg,      sizei,    command)
CMD_DEF(:,      cmd_label,  labelarg,    sizei,    command)// labels


//EMIT1(num, binbuff, newcounter, char);

//CMD_DEF ( pushr,  cmd_pushr,  2)
//CMD_DEF ( popr,   cmd_popr,   1)
//CMD_DEF ( begin,  cmd_begin,  2)
//CMD_DEF2( pop,    cmd_pop,    0)
//CMD_DEF2( back,   cmd_back,   0)
//CMD_DEF2( fsqrt,  cmd_fsqrt,  0)
//CMD_DEF2( size,   cmd_size,   0)
//CMD_DEF2( clear,  cmd_clear,  0)
//CMD_DEF2( add,    cmd_add,    0)
//CMD_DEF2( mul,    cmd_mul,    0)
//CMD_DEF2( sub,    cmd_sub,    0)
//CMD_DEF2( div,    cmd_div,    0)
//CMD_DEF ( resize, cmd_resize, 1)
//CMD_DEF ( jmp,    cmd_jmp,    1)
//CMD_DEF ( jxx,    cmd_jxx,    1)
//CMD_DEF ( ja,     cmd_ja,     1)
//CMD_DEF2( end,    cmd_end,    0)



//char code[...] = {};
//int addr = 0;
//
//...
//
//code[addr++] = CMD_PUSH;
//EMIT(code, addr, float, 3.14f);


//#define EMIT(code, addr, type, value)    \
//	{                                    \
//	*(type*)((code) + (addr)) = (value); \
//	(addr) += sizeof(type);              \
//	}
