#include "../generate/mips.h"
#include "../tools/utility.h"
#include <stdarg.h>
#include <string.h>

Mips::Register Mips::GetRegister(Location *var, Reason reason, Register avoid1, Register avoid2) {
	//stdOutput("Emit GetRegister");
	Register reg;
	if (!FindRegisterWithContents(var, reg)) {
		if (!FindRegisterWithContents(nullptr, reg)) { 
			reg = SelectRegisterToSpill(avoid1, avoid2);
			SpillRegister(reg);
		}
		regs[reg].var = var;
		if (reason == ForRead) {				// load current value
			Assert(var->GetOffset() % 4 == 0); 	// all variables are 4 bytes
			std::string offsetFromWhere = var->GetSegment() == fpRelative? regs[fp].name : regs[gp].name;
			Emit("lw %s, %d(%s)\t# load %s from %s%+d into %s", regs[reg].name.data(),
			var->GetOffset(), offsetFromWhere.data(), var->GetName().data(),
			offsetFromWhere.data(), var->GetOffset(), regs[reg].name.data());
			regs[reg].isDirty = false;
		}
	}
	if (reason == ForWrite)
		regs[reg].isDirty = true;
	return reg;
}

Mips::Register Mips::GetRegister(Location *var, Register avoid1) {
	//stdOutput("Emit GetRegister");
	return GetRegister(var, ForRead, avoid1, zero);
}

Mips::Register Mips::GetRegisterForWrite(Location *var, Register avoid1, Register avoid2) {
	//stdOutput("Emit GetRegister");
	return GetRegister(var, ForWrite, avoid1, avoid2);
}

static bool LocationsAreSame(Location *var1, Location *var2) {
	//stdOutput("Emit location same");
	 return (var1 == var2 || (var1 && var2 
		&& var1->GetName() == var2->GetName()
		&& var1->GetSegment() == var2->GetSegment()
		&& var1->GetOffset() == var2->GetOffset()));
}

bool Mips::FindRegisterWithContents(Location *var, Register& reg) {
	//stdOutput("Emit find reg with con");
	for (reg = zero; reg < NumRegs; reg = Register(reg + 1))
		if (regs[reg].isGeneralPurpose && LocationsAreSame(var, regs[reg].var))
			return true;
	return false;
}

Mips::Register Mips::SelectRegisterToSpill(Register avoid1, Register avoid2) {
	//stdOutput("Emit select to spill");
	// first hunt for a non-dirty one, since no work to spill
	for (Register i = zero; i < NumRegs; i = (Register)(i + 1)) {
		if (i != avoid1 && i != avoid2 && regs[i].isGeneralPurpose && !regs[i].isDirty)
			return i;
	}
	do { // otherwise just pick the next usuable register
		lastUsed = (Register)((lastUsed + 1) % NumRegs);
	} while (lastUsed == avoid1 || lastUsed == avoid2 || !regs[lastUsed].isGeneralPurpose);
	return lastUsed;
}

void Mips::SpillRegister(Register reg) {
	//stdOutput("Emit spell re");
	Location *var = regs[reg].var;
	if (var && regs[reg].isDirty) {
		std::string offsetFromWhere = var->GetSegment() == fpRelative? regs[fp].name : regs[gp].name;
		Assert(var->GetOffset() % 4 == 0); // all variables are 4 bytes in size
		Emit("sw %s, %d(%s)\t# spill %s from %s to %s%+d", regs[reg].name.data(),
		 var->GetOffset(), offsetFromWhere.data(), var->GetName().data(), regs[reg].name.data(),
		 offsetFromWhere.data(),var->GetOffset());
	}
	regs[reg].var = nullptr;
}

void Mips::SpillAllDirtyRegisters() {
	//stdOutput("Emit spill dirty");
	Register i;
	for (i = zero; i < NumRegs; i = Register(i+1)) 
		if (regs[i].var && regs[i].isDirty) break;
	if (i != NumRegs) {
		// none are dirty, don't print message to avoid confusion
		Emit("# (save modified registers before flow of control change)");
	}
	for (i = zero; i < NumRegs; i = Register(i + 1)) {
		SpillRegister(i);
	}
}


void Mips::SpillForEndFunction() {
	//stdOutput("Emit spill func");
	for (Register i = zero; i < NumRegs; i = Register(i + 1)) {
		if (regs[i].isGeneralPurpose && regs[i].var) {
			if (regs[i].var->GetSegment() == gpRelative)
				SpillRegister(i);
			else	// all stack variables can just be tossed at end func
				regs[i].var = nullptr;
		}
	}
}

void Mips::EmitLoadConstant(Location *dst, int val) {
	//stdOutput("Emit load con");
	Register reg = GetRegisterForWrite(dst);
	//Todo
	Emit("li %s, %d\t\t# load constant value %d into %s", regs[reg].name.data(),
	 val, val, regs[reg].name.data());
}

void Mips::EmitLoadStringConstant(Location *dst, std::string str) {
	//stdOutput("Emit load const");
	static int strNum = 1;
	std::string label = "_string" + std::to_string(strNum++);
	Emit(".data\t\t\t# create string constant marked with label");
	Emit("%s: .asciiz %s", label.data(), str.data());
	Emit(".text");
	EmitLoadLabel(dst, label);
}


void Mips::EmitLoadLabel(Location *dst, std::string label) {
	//stdOutput("Emit load lable");
	Register reg = GetRegisterForWrite(dst);
	Emit("la %s, %s\t# load label", 
		regs[reg].name.data(), label.data());
}


void Mips::EmitCopy(Location *dst, Location *src) {
	//stdOutput("Emit copy");
	Register rSrc = GetRegister(src), rDst = GetRegisterForWrite(dst, rSrc);
	Emit("move %s, %s\t\t# copy value", 
		regs[rDst].name.data(), regs[rSrc].name.data());
}


void Mips::EmitLoad(Location *dst, Location *reference, int offset) {
	//stdOutput("Emit load");
	Register rSrc = GetRegister(reference);
	Register rDst = GetRegisterForWrite(dst, rSrc);
	Emit("lw %s, %d(%s) \t# load with offset", 
		regs[rDst].name.data(), offset, regs[rSrc].name.data());
}


void Mips::EmitStore(Location *reference, Location *value, int offset) {
	//stdOutput("Emit store");
	Register rVal = GetRegister(value), rRef = GetRegister(reference, rVal);
	Emit("sw %s, %d(%s) \t# store with offset", 
		regs[rVal].name.data(), offset, regs[rRef].name.data());
}


void Mips::EmitBinaryOp(BinaryOp::OpCode code, Location *dst, Location *op1, Location *op2) {
	//stdOutput("Emit op");
	Register rLeft = GetRegister(op1);
	Register rRight = GetRegister(op2, rLeft);
	Register rDst = GetRegisterForWrite(dst, rLeft, rRight);
	Emit("%s %s, %s, %s\t", NameForTac(code).data(), regs[rDst].name.data(), 
		regs[rLeft].name.data(), regs[rRight].name.data());
}


void Mips::EmitLabel(std::string label) { 
	//stdOutput("Emit ..label");
	SpillAllDirtyRegisters();
	Emit("%s:", label.data());
}


void Mips::EmitGoto(std::string label) {
	//stdOutput("Emit goto");
	SpillAllDirtyRegisters();
	Emit("b %s\t\t# unconditional branch", label.data());
}

void Mips::EmitIfZ(Location *test, std::string label) { 
	//stdOutput("Emit ifz");
	Register testReg = GetRegister(test);
	SpillAllDirtyRegisters();
	Emit("beqz %s, %s\t# branch if %s is zero ", 
		regs[testReg].name.data(), label.data(), test->GetName().data());
}
void Mips::EmitParam(Location *arg) { 
	//stdOutput("Emit para");
	Emit("subu $sp, $sp, 4\t# decrement sp to make space for param");
	Register reg = GetRegister(arg);
	Emit("sw %s, 4($sp)\t# copy param value to stack", regs[reg].name.data());
}

void Mips::EmitCallInstr(Location *result, std::string fn, bool isLabel) {
	//stdOutput("Emit call");
	SpillAllDirtyRegisters();
	Emit("%s %-15s\t# jump to function", isLabel? "jal": "jalr", fn.data());
	if (result != nullptr) {
		Register r1 = GetRegisterForWrite(result);
		Emit("move %s, %s\t\t# copy function return value from $v0", 
			regs[r1].name.data(), regs[v0].name.data());
	}
}

void Mips::EmitLCall(Location *dst, std::string label) {
	//stdOutput("Emit call_1");
	EmitCallInstr(dst, label, true);
}

void Mips::EmitACall(Location *dst, Location *fn) {
	//stdOutput("Emit acall");
	EmitCallInstr(dst, regs[GetRegister(fn)].name, false);
}


void Mips::EmitPopParams(int bytes) {
	//stdOutput("Emit pop");
	if (bytes != 0)
		Emit("add $sp, $sp, %d\t# pop params off stack", bytes);
}


void Mips::EmitReturn(Location *returnVal) { 
	//stdOutput("Emit return ");
	if (returnVal != nullptr) 
		Emit("move $v0, %s\t\t# assign return value into $v0", regs[GetRegister(returnVal)].name.data());
	SpillForEndFunction();
	Emit("move $sp, $fp\t\t# pop callee frame off stack");
	Emit("lw $ra, -4($fp)\t# restore saved ra");
	Emit("lw $fp, 0($fp)\t# restore saved fp");
	Emit("jr $ra\t\t# return from function");
}

void Mips::EmitBeginFunction(int stackFrameSize) {
	//stdOutput("Emit begin");
	Assert(stackFrameSize >= 0);
	Emit("subu $sp, $sp, 8\t# decrement sp to make space to save ra, fp");
	Emit("sw $fp, 8($sp)\t# save fp");
	Emit("sw $ra, 4($sp)\t# save ra");
	Emit("addiu $fp, $sp, 8\t# set up new fp");
	if (stackFrameSize != 0) {
		Emit("subu $sp, $sp, %d\t# decrement sp to make space for locals/temps", stackFrameSize);
	}
}

void Mips::EmitEndFunction() { 
	//stdOutput("Emit endfunc");
	Emit("# (below handles reaching end of fn body with no explicit return)");
	EmitReturn(nullptr);
}

void Mips::EmitVTable(std::string label, std::list<std::string> *methodLabels) {
	//stdOutput("Emit vtable");
	Emit(".data");
	Emit(".align 2");
	Emit("%s:\t\t# label for class %s vtable", label.data(), label.data());
	for (auto iter : *methodLabels)
		Emit(".word %s\n", iter.data());
	Emit(".text");
}

void Mips::EmitPreamble() {
	//stdOutput("Emit emit pre");
	Emit("# standard Decaf preamble ");
	Emit(".text");
	Emit(".align 2");
	Emit(".globl main");
}

void Mips::EmitBuildInCall() {
	Emit("_PrintInt:");
	Emit("subu $sp, $sp, 8");
	Emit("sw $fp, 8($sp)");
	Emit("sw $ra, 4($sp)");
	Emit("addiu $fp, $sp, 8");
	Emit("li   $v0, 1");
	Emit("lw   $a0, 4($fp)");
	Emit("syscall");
	Emit("move $sp, $fp");
	Emit("lw $ra, -4($fp)");
	Emit("lw $fp, 0($fp)");
	Emit("jr $ra");
									
	Emit("_PrintString:");
	Emit("subu $sp, $sp, 8");
	Emit("sw $fp, 8($sp)");
	Emit("sw $ra, 4($sp)");
	Emit("addiu $fp, $sp, 8");
	Emit("li   $v0, 4");
	Emit("lw $a0, 4($fp)");
	Emit("syscall");
	Emit("move $sp, $fp");
	Emit("lw $ra, -4($fp)");
	Emit("lw $fp, 0($fp)");
	Emit("jr $ra");
			
	Emit("_PrintBool:");
	Emit("subu $sp, $sp, 8");
	Emit("sw $fp, 8($sp)");
	Emit("sw $ra, 4($sp)");
	Emit("addiu $fp, $sp, 8");
	Emit("lw $t1, 4($fp)");
	Emit("blez $t1, fbr");
	Emit("li   $v0, 4		# system call for print_str");
	Emit("la   $a0, TRUE		# address of str to print");
	Emit("syscall			");
	Emit("b end");
	Emit("fbr:	li   $v0, 4		# system call for print_str");
	Emit("la   $a0, FALSE		# address of str to print");
	Emit("syscall");
	Emit("end:	move $sp, $fp");
	Emit("lw $ra, -4($fp)");
	Emit("lw $fp, 0($fp)");
	Emit("jr $ra");

	Emit("_Alloc:");
	Emit("subu $sp, $sp, 8");
	Emit("sw $fp, 8($sp)");
	Emit("sw $ra, 4($sp)");
	Emit("addiu $fp, $sp, 8");
	Emit("li   $v0, 9");
	Emit("lw $a0, 4($fp)");
	Emit("syscall");
	Emit("move $sp, $fp");
	Emit("lw $ra, -4($fp)");
	Emit("lw $fp, 0($fp) ");
	Emit("jr $ra");
	Emit("");

	Emit("_StringEqual:");
	Emit("subu $sp, $sp, 8      # decrement sp to make space to save ra, fp");
	Emit("sw $fp, 8($sp)        # save fp");
	Emit("sw $ra, 4($sp)        # save ra");
	Emit("addiu $fp, $sp, 8     # set up new fp");
	Emit("subu $sp, $sp, 4      # decrement sp to make space for locals/temps");
	Emit("");
	Emit("li $v0,0");
	Emit("");
	Emit("#Determine length string 1");
	Emit("lw $t0, 4($fp)       ");
	Emit("li $t3,0");
	Emit("bloop1: ");
	Emit("lb $t5, ($t0) ");
	Emit("beqz $t5, eloop1	");
	Emit("addi $t0, 1");
	Emit("addi $t3, 1");
	Emit("b bloop1");
	Emit("eloop1:");
	Emit("");
	Emit("#Determine length string 2");
	Emit("lw $t1, 8($fp)");
	Emit("li $t4,0");
	Emit("bloop2: ");
	Emit("lb $t5, ($t1) ");
	Emit("beqz $t5, eloop2	");
	Emit("addi $t1, 1");
	Emit("addi $t4, 1");
	Emit("b bloop2");
	Emit("eloop2:");
	Emit("bne $t3,$t4,end1       #Check String Lengths Same");
	Emit("");
	Emit("lw $t0, 4($fp)       ");
	Emit("lw $t1, 8($fp)");
	Emit("li $t3, 0     	");
	Emit("bloop3:	");
	Emit("lb $t5, ($t0) ");
	Emit("lb $t6, ($t1) ");
	Emit("bne $t5, $t6, end1");
	Emit("addi $t3, 1");
	Emit("addi $t0, 1");
	Emit("addi $t1, 1");
	Emit("bne $t3,$t4,bloop3");
	Emit("eloop3:	li $v0,1");
	Emit("end1:	move $sp, $fp         # pop callee frame off stack");
	Emit("lw $ra, -4($fp)       # restore saved ra");
	Emit("lw $fp, 0($fp)        # restore saved fp");
	Emit("jr $ra                # return from function");

	Emit("_Halt:");
	Emit("li $v0, 10");
	Emit("syscall");

	Emit("_ReadInteger:");
	Emit("sw $fp, 8($sp)        # save fp");
	Emit("sw $ra, 4($sp)        # save ra");
	Emit("addiu $fp, $sp, 8     # set up new fp");
	Emit("subu $sp, $sp, 4      # decrement sp to make space for locals/temps");
	Emit("li $v0, 5");
	Emit("syscall");
	Emit("move $sp, $fp         # pop callee frame off stack");
	Emit("lw $ra, -4($fp)       # restore saved ra");
	Emit("lw $fp, 0($fp)        # restore saved fp");
	Emit("jr $ra");
	Emit("");

	Emit("_ReadLine:");
	Emit("sw $fp, 8($sp)        # save fp");
	Emit("sw $ra, 4($sp)        # save ra");
	Emit("addiu $fp, $sp, 8     # set up new fp");
	Emit("subu $sp, $sp, 4      # decrement sp to make space for locals/temps");
	Emit("li $a1, 40");
	Emit("la $a0, SPACE");
	Emit("li $v0, 8");
	Emit("syscall");
	Emit("");
	Emit("la $t1, SPACE");
	Emit("bloop4: ");
	Emit("lb $t5, ($t1) ");
	Emit("beqz $t5, eloop4	");
	Emit("addi $t1, 1");
	Emit("b bloop4");
	Emit("eloop4:");
	Emit("addi $t1,-1");
	Emit("li $t6,0");
	Emit("sb $t6, ($t1)");
	Emit("");
	Emit("la $v0, SPACE");
	Emit("move $sp, $fp         # pop callee frame off stack");
	Emit("lw $ra, -4($fp)       # restore saved ra");
	Emit("lw $fp, 0($fp)        # restore saved fp");
	Emit("jr $ra");
	Emit("");
	Emit("");
	Emit(".data");

	Emit("TRUE:.asciiz \"true\"");

	Emit("FALSE:.asciiz \"false\"");

	Emit("SPACE:.asciiz \"Making Space For Inputed Values Is Fun.\"");
}

std::string Mips::NameForTac(BinaryOp::OpCode code) {
	//stdOutput("Emit tac");
	Assert(code >=0 && code < BinaryOp::NumOps);
	std::string name = mipsName[code];
	Assert(!name.empty());
	return name;
}

Mips::Mips() {
	mipsName[BinaryOp::Add] = "add";
	mipsName[BinaryOp::Sub] = "sub";
	mipsName[BinaryOp::Mul] = "mul";
	mipsName[BinaryOp::Div] = "div";
	mipsName[BinaryOp::Mod] = "rem";
	mipsName[BinaryOp::Eq] = "seq";
	mipsName[BinaryOp::Less] = "slt";
	mipsName[BinaryOp::And] = "and";
	mipsName[BinaryOp::Or] = "or";
	regs[zero] = {false, nullptr, "$zero", false};
	regs[at] = {false, nullptr, "$at", false};
	regs[v0] = {false, nullptr, "$v0", false};
	regs[v1] = {false, nullptr, "$v1", false};
	regs[a0] = {false, nullptr, "$a0", false};
	regs[a1] = {false, nullptr, "$a1", false};
	regs[a2] = {false, nullptr, "$a2", false};
	regs[a3] = {false, nullptr, "$a3", false};
	regs[k0] = {false, nullptr, "$k0", false};
	regs[k1] = {false, nullptr, "$k1", false};
	regs[gp] = {false, nullptr, "$gp", false};
	regs[sp] = {false, nullptr, "$sp", false};
	regs[fp] = {false, nullptr, "$fp", false};
	regs[ra] = {false, nullptr, "$ra", false};
	regs[t0] = {false, nullptr, "$t0", true};
	regs[t1] = {false, nullptr, "$t1", true};
	regs[t2] = {false, nullptr, "$t2", true};
	regs[t3] = {false, nullptr, "$t3", true};
	regs[t4] = {false, nullptr, "$t4", true};
	regs[t5] = {false, nullptr, "$t5", true};
	regs[t6] = {false, nullptr, "$t6", true};
	regs[t7] = {false, nullptr, "$t7", true};
	regs[t8] = {false, nullptr, "$t8", true};
	regs[t9] = {false, nullptr, "$t9", true};
	regs[s0] = {false, nullptr, "$s0", true};
	regs[s1] = {false, nullptr, "$s1", true};
	regs[s2] = {false, nullptr, "$s2", true};
	regs[s3] = {false, nullptr, "$s3", true};
	regs[s4] = {false, nullptr, "$s4", true};
	regs[s5] = {false, nullptr, "$s5", true};
	regs[s6] = {false, nullptr, "$s6", true};
	regs[s7] = {false, nullptr, "$s7", true};
	lastUsed = zero;
}
std::string Mips::mipsName[BinaryOp::NumOps];