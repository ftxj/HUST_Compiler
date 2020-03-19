#ifndef __GENERATE_RW_H__
#define __GENERATE_RW_H__
class FieldAccess;
class ArrayAccess;
class Location;
class Scope;
class Expr;

class RW {
    public:
        static Location* read(Expr* , Scope* ); 
        static void store(Expr*, Scope* ,Location* ); 
        
        static Location* read(FieldAccess* , Scope* ); 
        static void store(FieldAccess*, Scope* ,Location*); 

        static Location* read(ArrayAccess* , Scope* ); 
        static void store(ArrayAccess*, Scope* ,Location*); 
};
#endif