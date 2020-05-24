#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

/*
 * 请在本文件中编写有关抽象语法树创建、添加节点、图形输出语法树的接口函数
 */

/* 整个AST的根节点。该节点不允许有兄弟节点，即root.next==NULL */
struct node ast_root;

/***************************************
  init_node函数负责对nd节点进行初始化
****************************************/
int init_node(struct node *nd)
{
  if (nd == NULL) return NULL_NODE_POINTER;
  nd->type = e_null_node;
  nd->val.str = NULL;
  nd->son = NULL;
  nd->parent = NULL;
  nd->next = NULL;

  return INIT_NODE_SUCCESS;
}

// AST抽象语法树初始化
void init_ast()
{
  init_node(&ast_root);
}

// add son_node into parent node.
int add_son_node(struct node *parent, struct node *son){
  if (parent == NULL && son == NULL) return NULL_NODE_POINTER;
  // add son_node if parent has no son
  if (parent && parent->son == NULL){
    parent->son = son;
    son->parent = parent;
  }else{
    struct node *tmp_node=parent->son;
    // parent has son, so add new son into its sibling.
    while(tmp_node->next)
    {
        tmp_node=tmp_node->next;
    }
    tmp_node->next = son;
    son->parent = parent;
    tmp_node->next = son;
  }
  return ADD_SON_NODE_SUCCESS;
}


int add_brother_node(struct node *last, struct node *new_brother){
  if (last == NULL && new_brother == NULL) return NULL_NODE_POINTER;
  struct node *tmp_parent=NULL;
  if (last->parent){ // add brother node if last's parent exist
    last->next = new_brother;
    new_brother->parent = last->parent;
  }else{
    return ADD_BROTHER_TO_NODE_WITHOUT_PARENT;
  }
  return ADD_BROTHER_NODE_SUCCESS;
}

int set_node_val_str(struct node *nd, char *str){
  if (!nd || !str) return NULL_NODE_POINTER;
  if (nd->val.str){ // free the origin str if it exist
    free(nd->val.str);
  }
  nd->val.str = (char*) malloc(strlen(str)+1);
  strcpy(nd->val.str, str);
  return SET_NODE_VAL_STR_SUCCESS;
}

// store the son node into result
int get_son_node(struct node *parent, struct node **result){
  if (!parent || !result) return NULL_NODE_POINTER;
  *result = parent->son;
  return GET_SON_NODE_SUCCESS;
}

int get_next_brother_node(struct node *cur_nd, struct node **result){
  if (!cur_nd || !result) return NULL_NODE_POINTER;
  *result = cur_nd->next;
  return GET_NEXT_BROTHER_NODE_SUCCESS;
}

// init a new node
int new_node(struct node **result){
  if(!result) return NULL_NODE_POINTER;
  *result = (struct node*)malloc(sizeof(struct node));
  if (init_node(*result) == INIT_NODE_SUCCESS){
    return NEW_NODE_SUCCESS;
  }else{
    return MEMORY_ALLOC_ERROR;
  }
}

// malloc and init a new node
void complete_init_node(struct node **cur, char *Name){
  new_node(cur);
	init_node(*cur);
	set_node_val_str(*cur, Name);
}

// draw the ast tree begin with level
void draw_ast(struct node *cur, int level){
  printf("%4d", level);
	int i;
	for (i = 0; i < level; i++) {
		printf("|\t");
	}

	printf("%s \n", cur->val.str);
  // draw the next level of tree if the son exist
	if (cur->son) {
		draw_ast(cur->son, level + 1);
	}
  // draw the sibling node.
	if (cur->next) {
		draw_ast(cur->next, level);
	}

}