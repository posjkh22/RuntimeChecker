#include "CheckerAPIs.h" 

Pathtree* generate_path_tree();
void add_basicblock(Pathtree* ,unsigned int, unsigned int, unsigned int, unsigned int);
extern Pathtree* p_pathtree;
extern bool checker_init_flag; 

extern "C" void checker_initializer(unsigned int node_id)
{
	
	if(checker_init_flag != true)
	{
		return;
	}

	checker_init_flag = false;

	generate_return_point_stack();
	p_pathtree = generate_path_tree();
	add_basicblock(p_pathtree, 0x10001, 2, 0x10002, 0x10003);
	add_basicblock(p_pathtree, 0x10002, 1, 0x10004, 0);
	add_basicblock(p_pathtree, 0x10003, 1, 0x10004, 0);
	add_basicblock(p_pathtree, 0x10004, 0, 0, 0);
	add_basicblock(p_pathtree, 0x20001, 2, 0x20002, 0x20003);
	add_basicblock(p_pathtree, 0x20002, 3, 0x10001, 0x20003);
	add_basicblock(p_pathtree, 0x20003, -1, 0, 0);


	return;
}
