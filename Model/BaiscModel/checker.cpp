
#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

//////////////////////////////////

/* extern value */

#define BB_NUM 200

extern unsigned int sig_queue[BB_NUM*2];
extern const int size_sig_queue;
extern unsigned int current_size_sig_queue;




//////////////////////////////////

/* checker_initializer */

//////////////////////////////////

class BBInfo
{
public:
	BBInfo(
		unsigned int t_node_id,
		unsigned int t_numConnection,
		unsigned int t_nextNode1,
		unsigned int t_nextNode2)
		: node_id(t_node_id),
		numConnection(t_numConnection)
	{
		nextNode[0] = t_nextNode1;
		nextNode[1] = t_nextNode2;
	}

	unsigned int node_id;
	unsigned int numConnection;
	unsigned int nextNode[2];

};

typedef std::map<unsigned int, BBInfo*> Pathtree;

Pathtree* p_pathtree;

//////////////////////////////////

void add_basicblock(
	Pathtree* p_pathtree,
	unsigned int node_id,
	unsigned int numConnection,
	unsigned int next_node_id1,
	unsigned int next_node_id2);

Pathtree* generate_path_tree();
unsigned int deque_sig_queue(unsigned int i);
void reset_sig_queue();
void checker_routine(unsigned int node_id);
bool if_has_connection_move(Pathtree* p_pathtree, unsigned int node_id, BBInfo** current_bb);
bool search_and_change_currentBB(unsigned int node_id, BBInfo** current_bb);

//////////////////////////////////

bool checker_init_flag = true;

extern "C" void checker_initializer(unsigned int node_id)
{
	if(checker_init_flag != true)
	{
		return;
	}

	checker_init_flag = false;

	p_pathtree = generate_path_tree();
	add_basicblock(
			p_pathtree, 
			0x00010001, 1, 0x00010002, 0);
	add_basicblock(
			p_pathtree, 
			0x00010002, 2, 0x00010003, 0x00010004);
	add_basicblock(
			p_pathtree, 
			0x00010003, 1, 0x00020001, 0);
	add_basicblock(
			p_pathtree, 
			0x00010004, 1, 0x00010005, 0);
	add_basicblock(
			p_pathtree, 
			0x00020001, 1, 0x00020002, 0x00020003);
	add_basicblock(
			p_pathtree, 
			0x00020002, 1, 0x00020004, 0);
	add_basicblock(
			p_pathtree, 
			0x00020003, 1, 0x00020004, 0);
	add_basicblock(
			p_pathtree, 
			0x00020004, 1, 0x00010005, 0);
	add_basicblock(
			p_pathtree, 
			0x00010005, 0, 0, 0);


	return;
}

/*
BBInfo initBB;
initBB.node_id = 0x00000001;
initBB.numConnnection = 1;
initBB.nextNode[0] = 0x00010001;
initBB.nextNode[1] = 0;
*/

Pathtree* generate_path_tree()
{
	Pathtree* t_pathtree = new Pathtree;
	BBInfo* t_bb = new BBInfo(0x00000001, 1, 0x00010001, 0);
	t_pathtree->insert(std::make_pair(0x00000001, t_bb));
	
	return t_pathtree;
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


//////////////////////////////////

/* checker */

//////////////////////////////////



extern "C" void checker()
{
	for(unsigned int i=0; i< current_size_sig_queue; i++)
	{
		unsigned int node_id = deque_sig_queue(i);
		checker_routine(node_id);
	}
	
	//current_size_sig_queue = 0;
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

	//printf(" current_bb: %x\n", current_bb->node_id);

	if(if_has_connection_move(p_pathtree, node_id, &current_bb) == true)
	{
		//printf(" [CHECKER ROUTINE]: %x\n", current_bb->node_id);
		return;
	}
	else
	{
		current_bb = p_pathtree->find(0x00000001)->second;
		reset_sig_queue();
		cout << " [RESET] Undefined Path" << endl;
		// SWI_RESET;
		return;
	}
}


bool if_has_connection_move(Pathtree* p_pathtree, unsigned int node_id, BBInfo** current_bb)
{

	/*
	printf(" current_node_id: %x\n", (*current_bb)->node_id);
	cout << " numConnection: " << (*current_bb)->numConnection << endl;
	printf(" nextNode[0]: %x\n",(*current_bb)->nextNode[0]); 
	printf(" nextNode[1]: %x\n",(*current_bb)->nextNode[1]); 
	printf(" node_id: %x\n", node_id);
	*/

	if((*current_bb)->numConnection == 1)
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
				return true;
			}
		}

		else
		{
			search_and_change_currentBB(node_id, current_bb);
			return true;
		}
	}

	else if((*current_bb)->numConnection == 0)
	{

		cout << " [RESET] Program Reset" << endl;
		(*current_bb) = p_pathtree->find(0x00000001)->second;
		//reset_sig_queue();

		/* 0x00000001 to 0x00010001 */	
		if((*current_bb)->numConnection == 1)
		{
			printf(" node_id: %x\n", node_id);
			if((*current_bb)->nextNode[0] != node_id)
			{
				return false;
			}
			else
			{
				search_and_change_currentBB(node_id, current_bb);
				return true;
			}
		}
		else
		{
			// SWI_INIT_ERROR
			return false;
		}
		
	}

	else
	{
		// SWI_MONITOR_ERROR
		return false;
	}
}

bool search_and_change_currentBB(unsigned int node_id, BBInfo** current_bb)
{

	BBInfo* next_bb = p_pathtree->find(node_id)->second;	
	printf(" Move: %x to %x \n", (*current_bb)->node_id, next_bb->node_id);
	*current_bb = next_bb;
	return true;
}








