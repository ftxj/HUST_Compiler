#ifndef __LOCALSCOPE_H__
#define __LOCALSCOPE_H__
#include "../symbol/Scope.h"
/** A scope object typically associated with {...} code blocks */
class LocalScope : public Scope {
	public:
		LocalScope(Scope* parent) : Scope(parent){}
};
#endif