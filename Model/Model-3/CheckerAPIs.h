
#ifndef M_CHECKER
#define M_CHECKER

#include <cstdio>
#include <iostream>
#include <map>
#include <stack>

/* Signal related value */

#define BB_NUM 200
#define nullptr NULL

extern unsigned int sig_queue[BB_NUM*2];
extern const int size_sig_queue;
extern unsigned int current_size_sig_queue;

class BBInfo;

typedef std::map<unsigned int, BBInfo*> Pathtree;
typedef std::stack<unsigned> ReturnPointStack;


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

void add_basicblock(
	Pathtree* p_pathtree,
	unsigned int node_id,
	unsigned int numConnection,
	unsigned int next_node_id1,
	unsigned int next_node_id2);

Pathtree* generate_path_tree();
bool generate_return_point_stack();
unsigned int deque_sig_queue(unsigned int i);
void reset_sig_queue();
void checker_routine(unsigned int node_id);
bool if_has_connection_move(Pathtree* p_pathtree, unsigned int node_id, BBInfo** current_bb);
bool search_and_change_currentBB(unsigned int node_id, BBInfo** current_bb);

extern Pathtree* p_pathtree;
extern bool checker_init_flag;
extern ReturnPointStack* p_returnPointStack;

#endif
