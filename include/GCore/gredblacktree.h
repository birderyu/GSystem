/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gredblacktree.h
** @brief	该文件包含了红黑树的定义及实现
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-08-17
** @version	1.0
** @see		GBinaryTreeNode
** @see		GBinaryTree
** @see		GBinarySortTree
** @see		GBinarySortTreeNode
**
****************************************************************************/

#ifndef _CORE_RED_BLACK_TREE_H_
#define _CORE_RED_BLACK_TREE_H_

#include "gbinarysorttree.h"

#define G_RED_BLACK_TREE_NODE_RED		0
#define G_RED_BLACK_TREE_NODE_BLACK		1

namespace gsystem { // gsystem

template<typename KeyT, typename ValueT>
struct GRedBlackTreeNode 
	: public GBinaryTreeNodeT<GRedBlackTreeNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GRedBlackTreeNode<KeyT, ValueT>>
{
	gsmall m_nColor;

	GRedBlackTreeNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GRedBlackTreeNode<KeyT, ValueT> *parent = GNULL,
		GRedBlackTreeNode<KeyT, ValueT> *left = GNULL,
		GRedBlackTreeNode<KeyT, ValueT> *right = GNULL,
		gsmall color = G_RED_BLACK_TREE_NODE_RED);

	GRedBlackTreeNode(
		const KeyT &key, ValueT &&value,
		GRedBlackTreeNode<KeyT, ValueT> *parent = GNULL,
		GRedBlackTreeNode<KeyT, ValueT> *left = GNULL,
		GRedBlackTreeNode<KeyT, ValueT> *right = GNULL,
		gsmall color = G_RED_BLACK_TREE_NODE_RED);
};

/****************************************************************************
**
** gredblacktree.h
**
** @class		GRedBlackTree
** @brief		红黑树
** @module		GCore
**
** 满足以下五个性质的二叉排序树，被称为红黑树：
** 1）每个结点要么是红的，要么是黑的；
** 2）根结点是黑的；
** 3）空结点（NULL）是黑的；
** 4）如果一个结点是红的，那么它的俩个儿子都是黑的；
** 5）对每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点。
**
** @see GRedBlackTreeNode
** @see GBinaryTreeNodeT<NodeT>
** @see GKeyValueNodeT<KeyT, ValueT>
**
****************************************************************************/
template<typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT>,
	typename NodeT = GRedBlackTreeNode<KeyT, ValueT> >
class GRedBlackTree 
	: public GBinarySortTree<KeyT, ValueT, CompareT, NodeT>
{
public:
	virtual ~GRedBlackTree();

	/// 插入一个数据
	virtual NodeT *Insert(const KeyT &key, const ValueT &value, gbool *realInsert = GNULL);
	virtual NodeT *Insert(const KeyT &key, ValueT &&value, gbool *realInsert = GNULL);

	/// 删除一个数据
	virtual gvoid Delete(const KeyT &key, gbool *realDelete = GNULL);
	virtual gvoid Delete(NodeT *node, gbool *realDelete = GNULL);

protected:
	// 插入修复
	gvoid InsertFixUp(NodeT *);
	// 删除修复
	gvoid DeleteFixUp(NodeT *);
	// 左旋
	gvoid RotateLeft(NodeT *);
	// 右旋
	gvoid RotateRight(NodeT *);
};

} // namespace gsystem

#include "gredblacktree.inl"

#undef G_RED_BLACK_TREE_NODE_BLACK
#undef G_RED_BLACK_TREE_NODE_RED

#endif // _CORE_RED_BLACK_TREE_H_