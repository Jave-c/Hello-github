#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct TREENODE
{
	int data;
	struct TREENODE* lchild;
	struct TREENODE* rchild;
}treenode;
//构建一颗搜索树，用来为下面构建做铺垫
int search(treenode* T,int vale,treenode* parent,treenode** pos)//指针parent用于下面创造树的函数，而pos用于插入时的传入，因为传入是改变的所以运用的是二维指针
{
	if (T == NULL)//其实我想过放最下面，但实际要先判断是否这一节点为空才能有下方判断
	{
		*pos = T;
		return 0;
	}
    if(T->data==vale)
	{
		*pos = T;//其实无意义，只是上下对称，逻辑合理，但是拓展有用
		return 1;
	}
	//不相等递归至树尾，
	else if(T->data>vale)
	{
		return search(T->lchild, vale, T, pos);
	}
	else
	{
		return search(T->rchild, vale, T, pos);
	}
}
void creat(treenode* T, int e, treenode** pos)
{
	int result = search(T, e, NULL, pos);
	if (result == 0)
	{
		treenode* addnode = (treenode*)malloc(sizeof(treenode));
		addnode->data = e;
		addnode->lchild = NULL;
		addnode->rchild = NULL;
		if ((*pos)->data > e)//!!!见证二重指针的魅力，这个时候就不能用T了
		{
			(*pos)->lchild = addnode;
			return;
		}
		else
		{
			(*pos)->rchild = addnode;
			return;
		}
	}
	else if(result==1)
	{
		char O;
		printf("已存在该值，是否需要继续添加，是则输入Y，退出按任意键");
		scanf("%c", &O);
		if (O == 'Y')
		{
			int e_1;
			scanf("%d", &e_1);
			creat(T, e_1, pos);
			return;
		}
		else
		{
			return;
		}
	}
}
void delet_2(treenode** T)
{
	if ((*T)->lchild == NULL && (*T)->rchild == NULL)
	{
		free((*T));
		*T = NULL;
		return;
	}
	else if ((*T)->lchild != NULL && (*T)->rchild != NULL)
	{
		treenode* move = (*T)->lchild;
		treenode** parent = T;
		parent=&(*parent)->lchild;
		while (move->rchild != NULL)
		{
			move = move->rchild;
		}
		(*T)->data = move->data;
		while ((*parent)->rchild != NULL)
		{
			parent = &(*parent)->rchild;//想要移动二重指针，就要改变二重指针本来的地址，而不是存储的地址，否则地址没动而值改变了
		}
		if (move->lchild != NULL)
		{
			treenode* temp_1 = *parent;
			*parent = temp_1->lchild;
			free(temp_1);
			return;
		}
		else
		{
			*parent = NULL;
			free(move);
		}
	}
	else if ((*T)->lchild != NULL && (*T)->rchild == NULL)
	{
		treenode* temp = *T;
		*T = temp->lchild;//!!!这里体现了二重指针的霸道直接相当于链表中的->next->next
		free(temp);
		return;
	}
	else
	{
		treenode* temp = *T;
		*T = temp->rchild;
		free(temp);
		return;
	}
}
void delete_1(treenode** T, int vale)
{
	if (*T == NULL)
	{
		printf("树中无目标数");
		return;
	}
	if ((*T)->data < vale)
	{
		return delete_1(&(*T)->rchild, vale);
	}
	else if((*T)->data>vale)
	{
		return delete_1(&(*T)->lchild, vale);
	}
	else
	{
		delet_2(T);
	}
}
int main()
{

}