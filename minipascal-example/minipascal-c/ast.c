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
  nd->type = e_null_node;
  nd->val.str = NULL;
  nd->son = NULL;
  nd->parent = NULL;
  nd->next = NULL;

  return RET_SUCCESS;
}

// AST抽象语法树初始化
void init_ast()
{
  init_node(&ast_root);
}
