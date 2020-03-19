#ifndef __H_ast_type__
#define __H_ast_type__
#include "ast.h"
#include <string>
class SymbolType;
class AstType : public Node {
	protected:
		std::string typeName;
	public:
		static AstType *intType, *doubleType, *boolType, *voidType,
			*nullType, *stringType, *errorType;
		AstType(yyltype loc);
		AstType(std::string str);
		virtual std::string getName();
		friend ostream& operator<<(ostream& out, AstType *t) { t->PrintToStream(out); return out; }
		virtual bool IsEquivalentTo(AstType *other);
		virtual void PrintToStream(ostream& out);
		SymbolType* Generate();
		friend class SemanticType;
		friend class Generate;

		std::string GetPrintNameForNode() { return "Type"; }
    	void PrintChildren(int indentLevel);
};

class AstNamedType : public AstType {
	protected:
		Identifier * id;
	public:
		AstNamedType(Identifier *i);
		std::string getName();
		void PrintToStream(ostream& out);
		bool IsEquivalentTo(AstType *other);
		friend class SemanticDecl;
		friend class SemanticType;
		friend class SemanticExpr;
		friend class Generate;

		std::string GetPrintNameForNode() { return "NamedType"; }
    	void PrintChildren(int indentLevel);
};

class AstArrayType : public AstType {
	protected:
		AstType * elemType;
	public:
		AstArrayType(yyltype loc, AstType *elemType);
		std::string getName();
		void PrintToStream(ostream& out);
		bool IsEquivalentTo(AstType *other);
		friend class SemanticType;
		friend class Generate;
		friend class SemanticDecl;
		std::string GetPrintNameForNode() { return "ArrayType"; }
    	void PrintChildren(int indentLevel);
};
#endif