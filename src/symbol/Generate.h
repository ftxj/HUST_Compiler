#ifndef PROJECT_GENERATE_H
#define PROJECT_GENERATE_H
class Decl;
class VarDecl;
class ClassDecl;
class InterfaceDecl;
class FnDecl;
class Symbol;
class AstNamedType;
class AstArrayType;
class AstType;
class SymbolType;
class Generate {
	public:
		static Symbol* geneSymbol(Decl* decl);
		static Symbol* geneSymbol(VarDecl* decl);
		static Symbol* geneSymbol(ClassDecl* decl);
		static Symbol* geneSymbol(InterfaceDecl* decl);
		static Symbol* geneSymbol(FnDecl* decl);
		static SymbolType* geneType(AstArrayType* type);
		static SymbolType* geneType(AstNamedType* type);
		static SymbolType* geneType(AstType* type);
};
#endif