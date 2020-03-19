#ifndef _H_mips
#define _H_mips
#include "../generate/tac.h"
#include "../tools/utility.h"
#include <list>
#include <string>
#include <memory>
class Location;
class Mips {
  private:
    typedef enum {zero, at, v0, v1, a0, a1, a2, a3,
			t0, t1, t2, t3, t4, t5, t6, t7,
			s0, s1, s2, s3, s4, s5, s6, s7,
			t8, t9, k0, k1, gp, sp, fp, ra, NumRegs } Register;
    
    struct RegContents {
        bool isDirty;
        Location *var;
        std::string name;
        bool isGeneralPurpose;
    } regs[NumRegs];

    Register lastUsed;
    
    typedef enum { ForRead, ForWrite } Reason;

    Register GetRegister(Location *var, Reason reason, Register avoid1, Register avoid2);
    Register GetRegister(Location *var, Register avoid1 = zero);
    Register GetRegisterForWrite(Location *var, Register avoid1 = zero, Register avoid2 = zero);
    bool FindRegisterWithContents(Location *var, Register& reg);
    Register SelectRegisterToSpill(Register avoid1, Register avoid2);
    void SpillRegister(Register reg);
    void SpillAllDirtyRegisters();
    void SpillForEndFunction();

    void EmitCallInstr(Location *dst, std::string fn, bool isL);
    
    static std::string mipsName[BinaryOp::NumOps];
    static std::string NameForTac(BinaryOp::OpCode code);

 public:
    Mips();

    //static void Emit(const char *fmt, ...);

    template<typename ... Args>
    static void Emit(const std::string format, Args ... args ) {
        //stdOutput("Emit");
        size_t size = std::snprintf(nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        std::unique_ptr<char[]> buf(new char[size]); 
        std::snprintf(buf.get(), size, format.c_str(), args ... );
        std::string res = std::string(buf.get(), buf.get() + size - 1);
        if (res[res.length() - 1] != ':') 
		    std::cout << "\t"; // don't tab in labels
	    if (res[0] != '#') 
		    std::cout << "	";	 // outdent comments a little
        std::cout << res;
	    if (res[res.length() - 1] != '\n') 
            std::cout << "\n"; // end with a newline
    }

    void EmitLoadConstant(Location *dst, int val);
    void EmitLoadStringConstant(Location *dst,std::string str);
    void EmitLoadLabel(Location *dst, std::string label);

    void EmitLoad(Location *dst, Location *reference, int offset);
    void EmitStore(Location *reference, Location *value, int offset);
    void EmitCopy(Location *dst, Location *src);
    
    void EmitBinaryOp(BinaryOp::OpCode code, Location *dst, 
			    Location *op1, Location *op2);

    void EmitLabel(std::string label);
    void EmitGoto(std::string label);
    void EmitIfZ(Location *test, std::string label);
    void EmitReturn(Location *returnVal);
    
    void EmitBeginFunction(int frameSize);
    void EmitEndFunction();

    void EmitParam(Location *arg);
    void EmitLCall(Location *result, std::string label);
    void EmitACall(Location *result, Location *fnAddr);
    void EmitPopParams(int bytes);
    void EmitVTable(std::string label, std::list<std::string> *methodLabels);

    void EmitPreamble();
    void EmitBuildInCall();
};
#endif