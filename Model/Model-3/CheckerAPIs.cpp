
#include "CheckerAPIs.h"

using namespace std;

//////////////////////////////////////////////////////////////////////

/* 						checker_initializer 						*/

//////////////////////////////////////////////////////////////////////

#define BB_NUM 200

Pathtree* p_pathtree = nullptr;
bool checker_init_flag = true;
ReturnPointStack* p_returnPointStack = nullptr;


bool generate_return_point_stack()
{
	
	p_returnPointStack = new ReturnPointStack;
	return true;
}

void add_basicblock(
	Pathtree* p_pathtree,
	unsigned int node_id,
	unsigned int numConnection,
	unsigned int next_node_id1,
	unsigned int next_node_id2)
{
	BBInfo* p_bb = new BBInfo(node_id, numConnection, next_node_id1, next_node_id2);
	p_pathtree->insert(std::make_pair(node_id, p_bb));
}

//////////////////////////////////////////////////////////////////////

/* 								checker		 						*/

//////////////////////////////////////////////////////////////////////

extern "C" void checker()
{

	for(unsigned int i=0; i< current_size_sig_queue; i++)
	{
		unsigned int node_id = deque_sig_queue(i);
		checker_routine(node_id);
	}
	
	reset_sig_queue();
}

void reset_sig_queue()
{
	current_size_sig_queue = 0;
}


unsigned int deque_sig_queue(unsigned int deque_pointer)
{
	int return_node_id;
	return_node_id = sig_queue[deque_pointer];
	
	return return_node_id;
}


void checker_routine(unsigned int node_id)
{
	static bool initial_checker_routine = true;
	static BBInfo* current_bb;

	if(initial_checker_routine == true)
	{
		current_bb = p_pathtree->find(0x00000001)->second;
		initial_checker_routine = false;
	}


	if(if_has_connection_move(p_pathtree, node_id, &current_bb) == true)
	{
		return;
	}
	else
	{
		current_bb = p_pathtree->find(0x00000001)->second;
		reset_sig_queue();
		cout << " [RESET][ERROR] <<<<<<<< Undefined Path >>>>>>>>>>" << endl;
		// SWI_RESET;
		return;
	}
}


bool if_has_connection_move(Pathtree* p_pathtree, unsigned int node_id, BBInfo** current_bb)
{

	if((*current_bb)->numConnection == 0)
	{
		unsigned int returnPoint = p_returnPointStack->top();
		p_returnPointStack->pop();
		std::cout << " [Stack POP] ReturnPoint: ";
		std::cout << std::hex << returnPoint << std::endl << std::dec;
		
		
		BBInfo* t_bb = (*current_bb);
		search_and_change_currentBB(returnPoint, current_bb);

	}

	else if((*current_bb)->numConnection == 3)
	{
		if((*current_bb)->nextNode[0] != node_id)
		{
			return false;
		}
		else
		{
			p_returnPointStack->push((*current_bb)->nextNode[1]);
			std::cout << " [Stack PUSH] retunPoint: ";
			std::cout << std::hex << (*current_bb)->nextNode[1] << std::dec << std::endl;
			search_and_change_currentBB(node_id, current_bb);
		}
	}

	else if((*current_bb)->numConnection == 1)
	{
		if((*current_bb)->nextNode[0] != node_id)
		{
			return false;
		}
		else
		{
			search_and_change_currentBB(node_id, current_bb);
		}
	}
	
	else if((*current_bb)->numConnection == 2)
	{
		if((*current_bb)->nextNode[0] != node_id)
		{
			if((*current_bb)->nextNode[1] != node_id)
			{
				return false;
			}
			
			else
			{
				search_and_change_currentBB(node_id, current_bb);
			}
		}

		else
		{
			search_and_change_currentBB(node_id, current_bb);
		}
	}

	else
	{
		// SWI_MONITOR_ERROR
		return false;
	}
	return true;

}

bool search_and_change_currentBB(unsigned int node_id, BBInfo** current_bb)
{

	BBInfo* next_bb = p_pathtree->find(node_id)->second;	
	printf(" Move: %x to %x \n", (*current_bb)->node_id, next_bb->node_id);
	*current_bb = next_bb;


	if((*current_bb)->numConnection == -1)
	{
		BBInfo* t_bb = (*current_bb);
		(*current_bb) = p_pathtree->find(0x00000001)->second;
		
		printf(" Move: %x to %x \n", 
				t_bb->node_id, (*current_bb)->node_id);

		cout << " #####################" << endl; 	
		cout << " [RESET] Program Reset" << endl;
	  	cout << " #####################" << endl << endl; 	
		
		delete p_returnPointStack;
		p_returnPointStack = new ReturnPointStack;
	}

	return true;
}


