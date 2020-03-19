/* File: tac.cc
 * ------------
 * Implementation of Location class and Instruction class/subclasses.
 */
	
#include "../generate/tac.h"
#include "../generate/mips.h"
#include "../tools/utility.h"
#include "../generate/codegen.h"
#include <string>

CodeGenerator* TAC::generator = new CodeGenerator();

Location::Location(Segment s, int o, std::string name) :
	variableName(name), segment(s), offset(o){
		//	cout << "Location name = " << name << ", offset = " << offset << endl;		
}

void Instruction::Print() {
	std::cout << "\t" << printed << "\n";
}

void Instruction::Emit(Mips *mips) {
	if(printed.empty())
		mips->Emit("# %s", printed.data());	 // emit TAC as comment into assembly
	EmitSpecific(mips);
} 

LoadConstant::LoadConstant(Location *d, int v)
	: dst(d), val(v) {
	Assert(dst != NULL);
	printed = string_format("%s = %d", dst->GetName().data(), val);
}

void LoadConstant::EmitSpecific(Mips *mips) {
	mips->EmitLoadConstant(dst, val);
}

LoadStringConstant::LoadStringConstant(Location *d, std::string s)
	: dst(d) {
	Assert(dst != NULL && !s.empty());
	std::string quote = (s == "\"") ? "" : "\"";
	str = s;
	quote = (str.length() > 50) ? "...\"" : "";
	printed = string_format("%s = %s", dst->GetName().data(), s.data());
	//printed = string_format("%s = %.50s%s", dst->GetName(), str, quote);
}

void LoadStringConstant::EmitSpecific(Mips *mips) {
	mips->EmitLoadStringConstant(dst, str);
}
		 
LoadLabel::LoadLabel(Location *d, std::string l)
	: dst(d), label(l) {
	Assert(dst != NULL && !label.empty());
	printed = string_format("%s = %s", dst->GetName().data(), label.data());
}

void LoadLabel::EmitSpecific(Mips *mips) {
	mips->EmitLoadLabel(dst, label);
}


Assign::Assign(Location *d, Location *s)
	: dst(d), src(s) {
	Assert(dst != NULL && src != NULL);
	printed = string_format("%s = %s", dst->GetName().data(), src->GetName().data());
}

void Assign::EmitSpecific(Mips *mips) {
	mips->EmitCopy(dst, src);
}

Load::Load(Location *d, Location *s, int off)
	: dst(d), src(s), offset(off) {
	Assert(dst != NULL && src != NULL);
	if (offset) 
		printed = string_format("%s = *(%s + %d)", dst->GetName().data(), src->GetName().data(), offset);
	else
		printed = string_format("%s = *(%s)", dst->GetName().data(), src->GetName().data());
}

void Load::EmitSpecific(Mips *mips) {
	mips->EmitLoad(dst, src, offset);
}

Store::Store(Location *d, Location *s, int off)
	: dst(d), src(s), offset(off) {
	Assert(dst != NULL && src != NULL);
	if (offset)
		printed = string_format("*(%s + %d) = %s", dst->GetName().data(), offset, src->GetName().data());
	else
		printed = string_format("*(%s) = %s", dst->GetName().data(), src->GetName().data());
}
void Store::EmitSpecific(Mips *mips) {
	mips->EmitStore(dst, src, offset);
}
 
std::string BinaryOp::opName[BinaryOp::NumOps] = {"+", "-", "*", "/", "%", "==", "<", "&&", "||"};

BinaryOp::OpCode BinaryOp::OpCodeForName(const std::string name) {
	for (int i = 0; i < NumOps; i++) 
		if (!opName[i].empty() && opName[i] ==  name)
			return (OpCode)i;
	Failure("Unrecognized Tac operator: '%s'\n", name);
	return Add; // can't get here, but compiler doesn't know that
}

BinaryOp::BinaryOp(OpCode c, Location *d, Location *o1, Location *o2)
	: code(c), dst(d), op1(o1), op2(o2) {
	Assert(dst != NULL && op1 != NULL && op2 != NULL);
	Assert(code >= 0 && code < NumOps);
	printed = string_format("%s = %s %s %s", dst->GetName().data(), op1->GetName().data(), 
		opName[code].data(), op2->GetName().data());
}

void BinaryOp::EmitSpecific(Mips *mips) {		
	mips->EmitBinaryOp(code, dst, op1, op2);
}


Label::Label(const std::string l) : label(l) {
	Assert(!label.empty());
	printed = "";
}
void Label::Print() {
	std::cout << label << ":\n";
}

void Label::EmitSpecific(Mips *mips) {
	mips->EmitLabel(label);
}

 
Goto::Goto(const std::string l) : label(l) {
	Assert(!l.empty());
	printed = string_format("Goto %s", label.data());
}

void Goto::EmitSpecific(Mips *mips) {		
	mips->EmitGoto(label);
}

IfZ::IfZ(Location *te, const std::string l) : test(te), label(l) {
	Assert(test != NULL && !l.empty());
	printed = string_format("IfZ %s Goto %s", test->GetName().data(), label.data());
}
void IfZ::EmitSpecific(Mips *mips) {		
	mips->EmitIfZ(test, label);
}

BeginFunc::BeginFunc() {
	printed = string_format("BeginFunc (unassigned)");
	frameSize = -555; // used as sentinel to recognized unassigned value
}

void BeginFunc::SetFrameSize(int numBytesForAllLocalsAndTemps) {
	frameSize = numBytesForAllLocalsAndTemps; 
	printed = string_format("BeginFunc %d", frameSize);
}
void BeginFunc::EmitSpecific(Mips *mips) {
	mips->EmitBeginFunction(frameSize);
}

EndFunc::EndFunc() : Instruction() {
	printed = string_format("EndFunc");
}

void EndFunc::EmitSpecific(Mips *mips) {
	mips->EmitEndFunction();
}
 
Return::Return(Location *v) : val(v) {
	printed = string_format("Return %s", val? val->GetName().data() : "");
}
void Return::EmitSpecific(Mips *mips) {		
	mips->EmitReturn(val);
}

PushParam::PushParam(Location *p)
	:	param(p) {
	Assert(param != NULL);
	printed = string_format("PushParam %s", param->GetName().data());
}
void PushParam::EmitSpecific(Mips *mips) {
	mips->EmitParam(param);
} 

PopParams::PopParams(int nb)
	:	numBytes(nb) {
	printed = string_format("PopParams %d", numBytes);
}
void PopParams::EmitSpecific(Mips *mips) {
	mips->EmitPopParams(numBytes);
} 

LCall::LCall(const std::string l, Location *d) : label(l), dst(d) {
	printed = string_format("%s%sLCall %s", dst? dst->GetName().data(): "", dst?" = ":"", label.data());
}
void LCall::EmitSpecific(Mips *mips) {
	mips->EmitLCall(dst, label);
}

ACall::ACall(Location *ma, Location *d)
	: dst(d), methodAddr(ma) {
	Assert(methodAddr != NULL);
	printed = string_format("%s%sACall %s", dst? dst->GetName().data(): "", dst?" = ":"",
			methodAddr->GetName().data());
}

void ACall::EmitSpecific(Mips *mips) {
	mips->EmitACall(dst, methodAddr);
} 


VTable::VTable(const std::string l, std::list<std::string> *m) : methodLabels(m), label(l) {
	Assert(methodLabels != NULL && !label.empty());
	printed = string_format("VTable for class %s", l.data());
}

void VTable::Print() {
	std::cout << "VTable " << label << " =\n";
	for (auto iter : *methodLabels) {
		std::cout << "\t" << iter << ",\n";
	}
	std::cout << "; \n";
}

void VTable::EmitSpecific(Mips *mips) {
	mips->EmitVTable(label, methodLabels);
}