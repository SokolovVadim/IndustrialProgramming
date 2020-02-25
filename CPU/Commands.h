#pragma once

enum Commands
{
 cmd_pushi = 1,
 cmd_pushd,
 cmd_pushr,
 cmd_pushri,
 cmd_pushrd,
 cmd_begin,
 cmd_pop,
 cmd_popr,
 cmd_back,
 cmd_size,
 cmd_resize,
 cmd_clear,
 cmd_jmp,
 cmd_jxx,
 cmd_ja,
 cmd_end,
 cmd_add,
 cmd_in,
 cmd_out,
 cmd_mul,
 cmd_sub,
 cmd_div,
 cmd_cmp,
 cmd_and,
 cmd_or,
 cmd_not,
 cmd_xor,
 cmd_call,
 cmd_ret,
 cmd_label,
 cmd_fsqrt,
 cmd_VS = 39
};

enum Types
{
	nullarg = 0,
	onearg,
	twoarg,
	threearg,
	fourarg,
	regarg,
	pusharg,
	pushrarg,
	labelarg,
	endarg,
	jmparg,
	callarg,
	sizenull = 0,
	sizec,
	sizei = sizeof(int),
	sized = sizeof(double)
};