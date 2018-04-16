
#include "CompactBBSet.hpp"

CompactBBSet::CompactBBSet()
{
	p_CompactBBList = new CompactBBList;
}

bool CompactBBSet::generate(wrapper* w)
{
	for(auto iter1 = w->getwTask()->getwFuncList()->begin();
			iter1 != w->getwTask()->getwFuncList()->end();
			iter1++)
	{

		wFunction* Wf = *iter1;

		for(auto iter2 = Wf->getwBBList()->begin();
				iter2 != Wf->getwBBList()->end();
				iter2++)
		{

			wBasicBlock* currentWBB = *iter2;
			llvm::BasicBlock* currentBB = currentWBB->getBasicBlock();
			p_CompactBBList->push_back(currentBB);
		}
	}
	return true;
}

CompactBBList* CompactBBSet::getCompactBBList()
{
	return p_CompactBBList;
}

bool Debug_CompactBBListShow()
{

	return true;
}
