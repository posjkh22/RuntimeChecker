Pathtree* p_pathtree;

void chekcer_initializer(unsigned int node_id)
{
	p_pathtree = generate_path_tree();
	add_basicblock(p_pathtree, 10001, 2, 10002, 10003)
	add_basicblock(p_pathtree, 10002, 1, 10004, 0)
	add_basicblock(p_pathtree, 10003, 1, 10004, 0)
	add_basicblock(p_pathtree, 10004, 0, 0, 0)
	add_basicblock(p_pathtree, 20001, 2, 20002, 20003)
	add_basicblock(p_pathtree, 20002, 1, 10001, 0)
	add_basicblock(p_pathtree, 20003, 0, 0, 0)

	return;
}
