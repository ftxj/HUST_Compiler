#ifndef __InternalType_H__
#define __InternalType_H__
#include "../symbol/SymbolType.h"
#include "../tools/utility.h"
#include <string>
class InternalType : public SymbolType {
	protected:
		int typeIndex;
	public:
		static InternalType *intType, *doubleType, *boolType, *voidType,
		*nullType, *stringType, *errorType, *arrayType, *classType;

		InternalType(std::string s) : SymbolType(s) {}
        InternalType(std::string s, Node* n) : SymbolType(s, n) {}

		bool IsEquivalentTo(SymbolType * t) {
			return t->getName() == getName();
		}

		std::string getName() {
			return SymbolType::name;
		}
		int getTypeIndex() {
			return typeIndex;
		}
		void setTypeIndex(int typeIndex) {
			this->typeIndex = typeIndex;
		}
};
#endif