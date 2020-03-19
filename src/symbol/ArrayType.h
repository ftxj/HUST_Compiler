#ifndef __ArrayType_H__
#define __ArrayType_H__
#include "../symbol/SymbolType.h"
#include <string>
class Node;
class ArrayType : public SymbolType {
	protected:
		SymbolType* elemType;						// array base type
		int numElems; 								// array size
	public:
		ArrayType(SymbolType* eType) : SymbolType("array"), elemType(eType), numElems(-1) {}
		ArrayType(SymbolType* eType, Node* node) : SymbolType("array", node), elemType(eType), numElems(-1) {}
		ArrayType(SymbolType* eType, Node* node, int nums) : SymbolType("array", node), elemType(eType), numElems(nums) {}
	public:
		SymbolType* getElmType() {
			return elemType;
		}
		bool IsEquivalentTo(SymbolType* type) {
			if(dynamic_cast<ArrayType*>(type) == nullptr) {
				return false;
			}
			ArrayType* atp = dynamic_cast<ArrayType*>(type);
			if(!elemType->IsEquivalentTo(atp->elemType)) {
				return false;
			}
			return true;
		}
		std::string getName() {
		    return elemType->getName() + "[]";
		}
		int getArraySize() {
			return numElems;
		}
		int getTypeIndex() {
			return -1;
		}

		std::string getTableName() {
			return elemType->getTableName() + "[]";
		}
		
		friend class SemanticType;
};
#endif