
#ifndef _AST_H_
#define _AST_H_

#define RET_SUCCESS		0
#define RET_ERROR		-1

enum node_type
{
	e_null_node,
	e_program, e_sub_prog, e_var_def, e_type_int, e_type_real,
	e_varlist, e_compstat, e_if_then_stat, e_bool_exp,
	e_exp, e_if_then_else_stat, e_assign_stat, e_while_stat,
	e_math_op, e_relation_op, e_statement
};

struct node_val
{
	char *str;
};

struct node
{
	enum node_type type;
	struct node_val val;
	struct node *son;/*记录本节点的第一个子节点。
	                   其余子节点通过对该字节点
	                   的next链进行扫描来获得。*/
	struct node *parent;
	struct node *next;/*记录本节点的下一个兄弟节点。
	                   本节点的parent节点的son_list
	                   指向整个兄弟链的第一个元素。*/
};

int init_node(struct node *nd);
int add_son_node(struct node *parent, struct node *son);
int add_brother_node(struct node *last, struct node *new_brother);
int set_node_val_str(struct node *nd, char *str);
int get_son_node(struct node *parent, struct node **result);
int get_next_brother_node(struct node *cur_nd, struct node **result);
int new_node(struct node **result);

void init_ast();

extern struct node ast_root;

#endif
