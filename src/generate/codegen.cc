/* File: codegen.cc
 * ----------------
 * Implementation for the CodeGenerator class. The methods don't do anything
 * too fancy, mostly just create objects of the various Tac instruction
 * classes and append them to the list.
 */

#include "../generate/codegen.h"
#include "../tools/utility.h"
#include "../generate/tac.h"
#include "../generate/mips.h"
#include <string>

#include <iostream>
#define quote(x) #x

CodeGenerator::CodeGenerator() {
	code = new std::list<Instruction*>();
	nextLocalOffset = OffsetToFirstLocal; 
	nextParamOffset = OffsetToFirstParam; 
	nextGlobalOffset = OffsetToFirstGlobal; 
	currFunctionFrameSize = 0; 
	
	currSeg = gpRelative; 
	currParametersLocations = new map<std::string, Location*>;
	ReadWriteField = -1; 
}

std::string CodeGenerator::NewLabel() {
	static int nextLabelNum = 0;
	string temp = "_L" + std::to_string(nextLabelNum++);
	return temp;
}

Location* CodeGenerator::GenTempVar() {
	static int nextTempNum = 0;
	string temp = "_L" + std::to_string(nextTempNum++);
	Location *result = new Location(currSeg, nextLocalOffset, temp); 
	if (currSeg == fpRelative) {
		nextLocalOffset -= 4; 
		currFunctionFrameSize += VarSize; 
	} 
	else if (currSeg == gpRelative) {
		nextGlobalOffset += 4; 
	}
	Assert(result != nullptr);
	return result;
}

 
Location *CodeGenerator::GenLoadConstant(int value) {
	Location *result = GenTempVar();
	code->push_back(new LoadConstant(result, value));
	return result;
}

Location *CodeGenerator::GenLoadConstant(std::string s) {
	Location *result = GenTempVar();
	code->push_back(new LoadStringConstant(result, s));
	return result;
}

Location *CodeGenerator::GenLoadLabel(std::string label) {
	Location *result = GenTempVar();
	code->push_back(new LoadLabel(result, label));
	return result;
}

void CodeGenerator::GenAssign(Location *dst, Location *src) {
	code->push_back(new Assign(dst, src));
}

Location *CodeGenerator::GenLoad(Location *ref, int offset) {
	Location *result = GenTempVar();
	code->push_back(new Load(result, ref, offset));
	return result;
}

void CodeGenerator::GenStore(Location *dst,Location *src, int offset) {
	code->push_back(new Store(dst, src, offset));
}


Location *CodeGenerator::GenBinaryOp(std::string opName, Location *op1,
								 Location *op2) {
	Location *result = GenTempVar();
	code->push_back(new BinaryOp(BinaryOp::OpCodeForName(opName), result, op1, op2));
	return result;
}


void CodeGenerator::GenLabel(std::string label) {
	code->push_back(new Label(label));
}

void CodeGenerator::GenIfZ(Location *test, std::string label) {
	code->push_back(new IfZ(test, label));
}

void CodeGenerator::GenGoto(std::string label) {
	code->push_back(new Goto(label));
}

void CodeGenerator::GenReturn(Location *val) {
	code->push_back(new Return(val));
}

BeginFunc *CodeGenerator::GenBeginFunc() {
	BeginFunc *result = new BeginFunc;
	code->push_back(result);
	return result;
}

void CodeGenerator::GenEndFunc() {
	code->push_back(new EndFunc());
}

void CodeGenerator::GenPushParam(Location *param) {
	code->push_back(new PushParam(param));
}

void CodeGenerator::GenPopParams(int numBytesOfParams) {
	Assert(numBytesOfParams >= 0 && numBytesOfParams % VarSize == 0); // sanity check
	if (numBytesOfParams > 0)
		code->push_back(new PopParams(numBytesOfParams));
}

Location *CodeGenerator::GenLCall(std::string label, bool fnHasReturnValue) {
	Location *result = fnHasReturnValue ? GenTempVar() : nullptr;
	code->push_back(new LCall(label, result));
	return result;
}

Location *CodeGenerator::GenACall(Location *fnAddr, bool fnHasReturnValue) {
	Location *result = fnHasReturnValue ? GenTempVar() : nullptr;
	code->push_back(new ACall(fnAddr, result));
	return result;
}
 
 
static struct _builtin {
	std::string label;
	int numArgs;
	bool hasReturn;
} builtins[] = {
	{"_Alloc", 1, true},
	{"_ReadLine", 0, true},
	{"_ReadInteger", 0, true},
	{"_StringEqual", 2, true},
	{"_PrintInt", 1, false},
	{"_PrintString", 1, false},
	{"_PrintBool", 1, false},
	{"_Halt", 0, false}
};

Location *CodeGenerator::GenBuiltInCall(BuiltIn bn,Location *arg1, Location *arg2) {
	Assert(bn >= 0 && bn < NumBuiltIns);
	struct _builtin *b = &builtins[bn];
	Location *result = nullptr;

	if (b->hasReturn) result = GenTempVar();
								// verify appropriate number of non-nullptr arguments given
	Assert((b->numArgs == 0 && !arg1 && !arg2)
	|| (b->numArgs == 1 && arg1 && !arg2)
	|| (b->numArgs == 2 && arg1 && arg2));
	if (arg2) code->push_back(new PushParam(arg2));
	if (arg1) code->push_back(new PushParam(arg1));
	code->push_back(new LCall(b->label, result));
	GenPopParams(VarSize*b->numArgs);
	return result;
}


void CodeGenerator::GenVTable(std::string className, std::list<std::string> *methodLabels) {
	code->push_back(new VTable(className, methodLabels));
}


void CodeGenerator::DoFinalCodeGen() {
	for (auto iter : *code)
		iter->Print();
	Mips mips;
	mips.EmitPreamble();
	for (auto iter : *code) {
		iter->Emit(&mips);
	}
	mips.EmitBuildInCall();
}


