
#ifndef _RB_TREE_H_
#define _RB_TREE_H_
#include "common/common.h"

namespace util {

#define BLACK 0x0
#define RED 0x1

enum Mode
{
	LEFT = 1,
	RIGHT,
	PARENT
};

template <typename DataTreeNode>
class RbTreeNode
{

public:
	RbTreeNode();
	~RbTreeNode();
	RbTreeNode(const DataTreeNode &node);

	DataTreeNode* getTreeNodeData() const;

	void ChangeColor(int color);
	void ChangePtr(RbTreeNode *ptr, Mode mode);
	void ChangeData(DataTreeNode *data);

	int GetColor() const {return _Color;}
	bool IsRed(){return _Color==RED;}
	RbTreeNode *GetPtr(Mode mode) const {
		if(mode==LEFT){return _Left;}else if(mode == RIGHT){return _Right;}else{return _Parent;}
	}
	void SetTreeNodeData(DataTreeNode *data);

private:
	int _Color;
	RbTreeNode<DataTreeNode> *_Left;
	RbTreeNode<DataTreeNode> *_Right;
	RbTreeNode<DataTreeNode> *_Parent;
	DataTreeNode *_Data;
};

template <typename DataTreeNode>
class RbTree {

public:
	RbTree();
	~RbTree();

	DataTreeNode *RbTreeInsert(const DataTreeNode &node);
	void RbTreeDelete(DataTreeNode *node);

	DataTreeNode *getMinDataNode() const;

private:
	void _InitNil();
	RbTreeNode<DataTreeNode> & _NodeInit(RbTreeNode<DataTreeNode> &node);

	RbTreeNode<DataTreeNode> * _BlanceInsertTree(RbTreeNode<DataTreeNode> *node);
	RbTreeNode<DataTreeNode> * _BlanceDeleteTree(RbTreeNode<DataTreeNode> *node,RbTreeNode<DataTreeNode> *parent);
	RbTreeNode<DataTreeNode> * _LeftRotate(RbTreeNode<DataTreeNode> *node);
	RbTreeNode<DataTreeNode> * _RightRotate(RbTreeNode<DataTreeNode> *node);
	RbTreeNode<DataTreeNode> * _GetMinLeftTree(RbTreeNode<DataTreeNode> *node);
	RbTreeNode<DataTreeNode> * _SearchTree(DataTreeNode *node);
	RbTreeNode<DataTreeNode> * _TreeSubSequence(RbTreeNode<DataTreeNode> *node);
	RbTreeNode<DataTreeNode>* _getInsertPos(const RbTreeNode<DataTreeNode> &node);
	RbTreeNode<DataTreeNode>* _InsertNode(RbTreeNode<DataTreeNode> &node);
	RbTreeNode<DataTreeNode>* _DeleteNode(RbTreeNode<DataTreeNode> *node);
	RbTreeNode<DataTreeNode> &_GetNilNode();

private:
	RbTreeNode<DataTreeNode> _NIL;
	RbTreeNode<DataTreeNode> *_Root;


};

template <typename DataTreeNode>
RbTreeNode<DataTreeNode>::RbTreeNode(const DataTreeNode &node)
{
	DataTreeNode *_node = new DataTreeNode(node);
	_Data = _node;
	_Color = RED;
	_Left = _Right = _Parent = NULL;
}

template <typename DataTreeNode>
RbTreeNode<DataTreeNode>::RbTreeNode()
{	
	_Left = _Right = _Parent = NULL;
	_Data = NULL;
	_Color = RED;
}


template <typename DataTreeNode>
RbTreeNode<DataTreeNode>::~RbTreeNode()
{
	delete _Data;
}

template <typename DataTreeNode>
void RbTreeNode<DataTreeNode>::SetTreeNodeData(DataTreeNode *data)
{
	_Data = data;
}

template <typename DataTreeNode>
void RbTreeNode<DataTreeNode>::ChangeColor(int color)
{
	_Color = color;
}
template <typename DataTreeNode>
void RbTreeNode<DataTreeNode>::ChangePtr(RbTreeNode *node, Mode mode)
{
	if(mode == LEFT){
		_Left = node;
	}else if(mode == RIGHT){
		_Right = node;
	}else{
		_Parent = node;
	}
}

template <typename DataTreeNode>
DataTreeNode* RbTreeNode<DataTreeNode>::getTreeNodeData() const
{
	return _Data;
}

template <typename DataTreeNode> 
RbTree<DataTreeNode>::RbTree()
{
	_InitNil();
	_Root = &_NIL;
}

template <typename DataTreeNode>
RbTree<DataTreeNode>::~RbTree()
{

}

template <typename DataTreeNode>
void RbTree<DataTreeNode>::_InitNil()
{
	_NIL.ChangeColor(BLACK);
	_NIL.ChangePtr(&_NIL, LEFT);
	_NIL.ChangePtr(&_NIL, RIGHT);
	_NIL.ChangePtr(&_NIL, PARENT);
}

template <typename DataTreeNode>
DataTreeNode *RbTree<DataTreeNode>::RbTreeInsert(const DataTreeNode &node)
{
	RbTreeNode<DataTreeNode> *_node = new RbTreeNode<DataTreeNode>(node);
	_node->ChangePtr(&_NIL, LEFT);
	_node->ChangePtr(&_NIL, RIGHT);
	_node->ChangePtr(&_NIL, PARENT);

	RbTreeNode<DataTreeNode> *_node_ptr = _InsertNode(*_node);

	_node_ptr->ChangeColor(RED);
	_node_ptr->ChangePtr(&_NIL, LEFT);
	_node_ptr->ChangePtr(&_NIL, RIGHT);

	_BlanceInsertTree(_node_ptr);
	return _node_ptr->getTreeNodeData();
}

template <typename DataTreeNode>
void RbTree<DataTreeNode>::RbTreeDelete(DataTreeNode *node)
{
	RbTreeNode<DataTreeNode> *_node = _SearchTree(node);
	RbTreeNode<DataTreeNode> *_CurNode;
	if((_node->GetPtr(LEFT)==&_NIL)||(_node->GetPtr(RIGHT))==&_NIL)
	{
		_CurNode = _node;
	}else{
		_CurNode = _GetMinLeftTree(_node);
	}

	RbTreeNode<DataTreeNode> *_TmpNode;
	if(_CurNode->GetPtr(LEFT) != &_NIL){
		_TmpNode = _CurNode->GetPtr(LEFT);
	}else{
		_TmpNode = _CurNode->GetPtr(RIGHT);
	}

	_TmpNode->ChangePtr(_CurNode->GetPtr(PARENT),PARENT);
	if(_CurNode->GetPtr(PARENT) == &_NIL){
		_Root = _TmpNode;
	}else if(_CurNode == _CurNode->GetPtr(PARENT)->GetPtr(LEFT)){
		_CurNode->GetPtr(PARENT)->ChangePtr(_TmpNode,LEFT);
	}else{
		_CurNode->GetPtr(PARENT)->ChangePtr(_TmpNode,RIGHT);
	}

	if(_CurNode != _node)
	{
		_node->SetTreeNodeData(_CurNode->getTreeNodeData());
	}
	if(!_CurNode->IsRed()) {
		_BlanceDeleteTree(_TmpNode, _CurNode->GetPtr(PARENT));
	}
	delete _CurNode;
}



template <typename DataTreeNode>
RbTreeNode<DataTreeNode> *RbTree<DataTreeNode>::_BlanceDeleteTree(RbTreeNode<DataTreeNode> *node,RbTreeNode<DataTreeNode> *parent)
{
	RbTreeNode<DataTreeNode> * uncle= &_NIL;
	if (node->IsRed()){
		node->ChangeColor(BLACK);
	}else{
		while(!node->IsRed()&&node!=_Root){
				if (node==node->GetPtr(PARENT)->GetPtr(LEFT)){
		            uncle=node->GetPtr(PARENT)->GetPtr(RIGHT);

					if (uncle->GetColor()== RED){//case1：x的兄弟w是红色的
						uncle->ChangeColor(BLACK);
						node->GetPtr(PARENT)->ChangeColor(RED);
						_LeftRotate(node->GetPtr(PARENT));
						uncle=node->GetPtr(PARENT)->GetPtr(RIGHT);
					}else{
						if(!uncle->GetPtr(LEFT)->IsRed()&&!uncle->GetPtr(RIGHT)->IsRed()){//case2：X的兄弟节点W是黑色的，而且W的两个子节点都是黑色的。
		                    uncle->ChangeColor(RED);
		                    node = node->GetPtr(PARENT);//此时可以将X的一重黑色和W的黑色同时去掉，而转加给他们的父节点上，这是X就指向它的父节点了，因此此时父节点具有双重颜色了
						}else{
							if(!uncle->GetPtr(RIGHT)->IsRed()){//case3：X的兄弟节点W是黑色的，而且W的左子节点是红色的，右子节点是黑色的。
								uncle->GetPtr(LEFT)->ChangeColor(BLACK);
								uncle->ChangeColor(RED);
								_RightRotate(uncle);
								uncle=node->GetPtr(PARENT)->GetPtr(RIGHT);
							}
		                    uncle->ChangeColor(node->GetPtr(PARENT)->GetColor());//case4：X的兄弟节点W是黑色的，而且W的右子节点是红色的。
							node->GetPtr(PARENT)->ChangeColor(BLACK);
							uncle->GetPtr(RIGHT)->ChangeColor(BLACK);
							_LeftRotate(node->GetPtr(PARENT));
						}
					}
				} 
				else{
					uncle=node->GetPtr(PARENT)->GetPtr(LEFT);
					if (uncle->IsRed()){//case5：x的兄弟w是红色的
						uncle->ChangeColor(BLACK);
						node->GetPtr(PARENT)->ChangeColor(RED);
						_RightRotate(node->GetPtr(PARENT));
						uncle=node->GetPtr(PARENT)->GetPtr(LEFT);
					}else{
						if (!uncle->GetPtr(LEFT)->IsRed()&&!uncle->GetPtr(RIGHT)->IsRed()){//case6：X的兄弟节点W是黑色的，而且W的两个子节点都是黑色的。
							uncle->ChangeColor(RED);                                                                    //此时可以将X的一重黑色和W的黑色同时去掉，而转加给他们的父节点上，这是X就指向它的父节点了，因此此时父节点具有双重颜色了。
							node=node->GetPtr(PARENT);
						}else{
							if(!uncle->GetPtr(LEFT)->IsRed()){//case7：X的兄弟节点W是黑色的，而且W的左子节点是黑色的，右子节点是红色的。
								uncle->GetPtr(RIGHT)->ChangeColor(BLACK);
								uncle->ChangeColor(RED);
								_LeftRotate(uncle);
								uncle=node->GetPtr(PARENT)->GetPtr(LEFT);
							}
							uncle->ChangeColor(node->GetPtr(PARENT)->GetColor());
							//case8：X的兄弟节点W是黑色的，而且W的左子节点是红色的。
							node->GetPtr(PARENT)->ChangeColor(BLACK);
							uncle->GetPtr(LEFT)->ChangeColor(BLACK);
							_RightRotate(node->GetPtr(PARENT));
						}
					}
				}
			}
		}
	_Root->ChangeColor(BLACK);
	return _Root;
}

template <typename DataTreeNode>
RbTreeNode<DataTreeNode> *RbTree<DataTreeNode>::_BlanceInsertTree(RbTreeNode<DataTreeNode> *node)
{	
	RbTreeNode<DataTreeNode> *_tmp,*_node;
	_node = node;
	while(_node->GetPtr(PARENT)->IsRed())
	{
		if(_node->GetPtr(PARENT) == _node->GetPtr(PARENT)->GetPtr(PARENT)->GetPtr(LEFT)){
			_tmp = _node->GetPtr(PARENT)->GetPtr(PARENT)->GetPtr(RIGHT);
			if(_tmp->IsRed()){
				_node->GetPtr(PARENT)->ChangeColor(BLACK);
				_tmp->ChangeColor(BLACK);
				_node->GetPtr(PARENT)->GetPtr(PARENT)->ChangeColor(RED);
				_node = _node->GetPtr(PARENT)->GetPtr(PARENT);
			}else if(_node == _node->GetPtr(PARENT)->GetPtr(RIGHT))
			{
				_node = _node->GetPtr(PARENT);
				_LeftRotate(_node);
			}
			_node->GetPtr(PARENT)->ChangeColor(BLACK);
			_node->GetPtr(PARENT)->GetPtr(PARENT)->ChangeColor(RED);
			_RightRotate(_node);

		}else{
			_tmp = _node->GetPtr(PARENT)->GetPtr(PARENT)->GetPtr(LEFT);
			if(_tmp->IsRed()){
				_node->GetPtr(PARENT)->ChangeColor(BLACK);
				_tmp->ChangeColor(BLACK);
				_node->GetPtr(PARENT)->GetPtr(PARENT)->ChangeColor(RED);
				_node = _node->GetPtr(PARENT)->GetPtr(PARENT);
			}else if(_node == _node->GetPtr(PARENT)->GetPtr(LEFT))
			{
				_node = _node->GetPtr(PARENT);
				_RightRotate(_node);
			}
			_node->GetPtr(PARENT)->ChangeColor(BLACK);
			_node->GetPtr(PARENT)->GetPtr(PARENT)->ChangeColor(RED);
			_LeftRotate(_node);
		}
			
	}
	
	_Root->ChangeColor(BLACK);
	return _Root;

}

template <typename DataTreeNode>
RbTreeNode<DataTreeNode> *RbTree<DataTreeNode>::_getInsertPos(const RbTreeNode<DataTreeNode> &node)
{
	RbTreeNode<DataTreeNode> *_tempx, *_tempy;
	_tempx = _Root;
	_tempy = &_NIL;
	while (_tempx != &_NIL) {

		_tempy = _tempx;
		if(node.getTreeNodeData()<_tempx->getTreeNodeData())
		{
			_tempx = _tempx->GetPtr(LEFT);
		}else{
			_tempx = _tempx->GetPtr(RIGHT);
		}
	}
	return _tempy;
}

template <typename DataTreeNode>
RbTreeNode<DataTreeNode> *RbTree<DataTreeNode>::_InsertNode(RbTreeNode<DataTreeNode> &node)
{
	RbTreeNode<DataTreeNode> *_tempy = _getInsertPos(node);
	node.ChangePtr(_tempy, PARENT);

	if(_tempy == &_NIL)
		_Root = &node;
	else if(node.getTreeNodeData()<_tempy->getTreeNodeData())
		_tempy->ChangePtr(&node,LEFT);
	else
		_tempy->ChangePtr(&node, RIGHT);
	return &node;
}

template<typename DataTreeNode>
RbTreeNode<DataTreeNode> *RbTree<DataTreeNode>::_TreeSubSequence(RbTreeNode<DataTreeNode> *node)
{

	RbTreeNode<DataTreeNode> *_node;
	if(node->GetPtr(RIGHT) != NULL)
	{
		return _GetMinLeftTree(node->GetPtr(RIGHT));
	}
	_node = node->GetPtr(PARENT);
	while((_node != &_NIL)&&(node == _node->GetPtr(RIGHT)))
	{
		node = _node;
		_node = _node->GetPtr(PARENT);
	}
	return _node;

}

template <typename DataTreeNode>
RbTreeNode<DataTreeNode>* RbTree<DataTreeNode>::_LeftRotate(RbTreeNode<DataTreeNode> *nodeptr)
{

	RbTreeNode<DataTreeNode> *_tmp = nodeptr->GetPtr(RIGHT);
	nodeptr->ChangePtr(_tmp->GetPtr(LEFT),RIGHT);
	_tmp->GetPtr(LEFT)->ChangePtr(nodeptr,PARENT);
	_tmp->ChangePtr(nodeptr->GetPtr(PARENT),PARENT);
	if(nodeptr->GetPtr(PARENT) == &_NIL){
		_Root = _tmp;
	}else if(nodeptr->GetPtr(PARENT)->GetPtr(LEFT) == nodeptr){
		nodeptr->GetPtr(PARENT)->ChangePtr(_tmp, LEFT);
	}else{
		nodeptr->GetPtr(PARENT)->ChangePtr(_tmp, RIGHT);
	}

	_tmp->ChangePtr(nodeptr, LEFT);
	nodeptr->ChangePtr(_tmp, PARENT);
	return nodeptr;

}

template <typename DataTreeNode>
RbTreeNode<DataTreeNode>* RbTree<DataTreeNode>::_RightRotate(RbTreeNode<DataTreeNode> *nodeptr)
{

	RbTreeNode<DataTreeNode> *_tmp = nodeptr->GetPtr(LEFT);
	nodeptr->ChangePtr(_tmp->GetPtr(RIGHT),LEFT);
	_tmp->GetPtr(RIGHT)->ChangePtr(nodeptr,PARENT);
	_tmp->ChangePtr(nodeptr->GetPtr(PARENT),PARENT);
	if(nodeptr->GetPtr(PARENT) == &_NIL){
		_Root = _tmp;
	}else if(nodeptr->GetPtr(PARENT)->GetPtr(RIGHT) == nodeptr){
		nodeptr->GetPtr(PARENT)->ChangePtr(_tmp, RIGHT);
	}else{
		nodeptr->GetPtr(PARENT)->ChangePtr(_tmp, LEFT);
	}

	_tmp->ChangePtr(nodeptr, RIGHT);
	nodeptr->ChangePtr(_tmp, PARENT);
	return nodeptr;
}

template <typename DataTreeNode>
DataTreeNode *RbTree<DataTreeNode>::getMinDataNode() const
{
	RbTreeNode<DataTreeNode> *_minnode = _Root;

	while(_minnode->GetPtr(LEFT)!=&_NIL){
		_minnode = _minnode->GetPtr(LEFT);
	}
	return _minnode->getTreeNodeData();
}

template<typename DataTreeNode>
RbTreeNode<DataTreeNode> *RbTree<DataTreeNode>::_GetMinLeftTree(RbTreeNode<DataTreeNode> *node)
{
	RbTreeNode<DataTreeNode> *_node = node;
	while(_node->GetPtr(LEFT) != &_NIL)
	{
		_node = _node->GetPtr(LEFT);
	}
	return _node;
}

template<typename DataTreeNode>
RbTreeNode<DataTreeNode> *RbTree<DataTreeNode>::_SearchTree(DataTreeNode *datanode)
{
	RbTreeNode<DataTreeNode> *_node = _Root;
	while((_node != &_NIL)&&(_node->getTreeNodeData()!=datanode)){
		if(*datanode < *_node->getTreeNodeData()){
			_node = _node->GetPtr(LEFT);
		}else{
			_node = _node->GetPtr(RIGHT);
		}
	}
	return _node;
}

template <typename DataTreeNode>
RbTreeNode<DataTreeNode> & RbTree<DataTreeNode>::_NodeInit(RbTreeNode<DataTreeNode> &node)
{
	node.ChangePtr(&_NIL, LEFT);
	node.ChangePtr(&_NIL, RIGHT);
	node.ChangePtr(&_NIL, PARENT);
	return node;
}

}

#endif

