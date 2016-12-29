#ifndef _CORE_RED_BLACK_TREE_INLINE_
#define _CORE_RED_BLACK_TREE_INLINE_

#define CS_RED_BLACK_TREE_NODE_TEMPLATE	template<typename KeyT, typename ValueT>
#define CS_RED_BLACK_TREE_NODE_QUAL		CsReadBlackTreeNode<KeyT, ValueT>
#define CS_RED_BLACK_TREE_TEMPLATE		template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
#define CS_RED_BLACK_TREE_QUAL			CsReadBlackTree<KeyT, ValueT, CompareT, NodeT>

CS_RED_BLACK_TREE_NODE_TEMPLATE
inline CS_RED_BLACK_TREE_NODE_QUAL::CsReadBlackTreeNode(
	const KeyT &key,
	const ValueT &value,
	CS_RED_BLACK_TREE_NODE_QUAL *parent,
	CS_RED_BLACK_TREE_NODE_QUAL *left,
	CS_RED_BLACK_TREE_NODE_QUAL *right,
	cs_small color)
	: CsBinaryTreeNodeT<CS_RED_BLACK_TREE_NODE_QUAL>(parent, left, right)
	, CsKeyValueNodeT<KeyT, ValueT>(key, value)
	, m_nColor(color)
{

}

CS_RED_BLACK_TREE_TEMPLATE
inline CS_RED_BLACK_TREE_QUAL::~CsReadBlackTree()
{

}

CS_RED_BLACK_TREE_TEMPLATE
inline NodeT *CS_RED_BLACK_TREE_QUAL::Insert(const KeyT &key, const ValueT &value, cs_bool *realInsert)
{
	NodeT *insert_point = NULL; // 插入位置的双亲节点
	NodeT *node = m_pRoot;
	while (node)
	{
		insert_point = node;
		cs_int ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			if (realInsert)
			{
				*realInsert = false;
			}
			insert_point->m_tValue = value;
			return insert_point;
		}
	}

	// 新增插入节点
	NodeT* insert_node = new NodeT(key, value);
	if (!insert_point)
	{
		//插入的是一颗空树
		m_pRoot = insert_node;
		insert_node->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
	}
	else
	{
		// 找到具体的插入位置
		cs_int ret = m_fCompare(key, insert_point->m_tKey);
		if (ret < 0)
		{
			insert_point->m_pLeft = insert_node;
		}
		else if (ret > 0)
		{
			insert_point->m_pRight = insert_node;
		}
		else
		{
			// 处理数据相同的情况
		}
		insert_node->m_pParent = insert_point;

		// 插入修复
		InsertFixUp(insert_node);
	}

	if (realInsert)
	{
		*realInsert = true;
	}
	return insert_node;
}

CS_RED_BLACK_TREE_TEMPLATE
inline cs_void CS_RED_BLACK_TREE_QUAL::Delete(const KeyT &key, cs_bool *realDelete)
{
	NodeT* delete_point = Find(key);
	if (!delete_point)
	{
		if (realDelete)
		{
			*realDelete = false;
		}
		return;
	}
	if (delete_point->m_pLeft && delete_point->m_pRight)
	{
		// 找到节点，且该节点有左右两个孩子
		NodeT *successor = delete_point->m_pRight->First();
		SwitchNode(delete_point, successor);
	}

	NodeT *delete_point_child = NULL;
	if (!delete_point->m_pLeft)
	{
		delete_point_child = delete_point->m_pRight;
	}
	else if (!delete_point->m_pRight)
	{
		delete_point_child = delete_point->m_pLeft;
	}

	NodeT *delete_point_parent = delete_point->m_pParent;
	if (delete_point_child)
	{
		delete_point_child->m_pParent = delete_point_parent;
	}

	if (!delete_point_parent)
	{
		m_pRoot = delete_point_child;
	}
	else
	{
		if (delete_point == delete_point_parent->m_pLeft)
		{
			delete_point_parent->m_pLeft = delete_point_child;
		}
		else
		{
			delete_point_parent->m_pRight = delete_point_child;
		}
	}

	if (delete_point->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
	{
		if (delete_point_child && delete_point_child != m_pRoot)
		{
			DeleteFixUp(delete_point_child);
		}
	}

	if (realDelete)
	{
		*realDelete = true;
	}
	delete delete_point;
}

CS_RED_BLACK_TREE_TEMPLATE
inline cs_void CS_RED_BLACK_TREE_QUAL::InsertFixUp(NodeT *node)
{
	while (node->m_pParent &&
		node->m_pParent->m_nColor == CS_RED_BLACK_TREE_NODE_RED)
	{
		if (node->m_pParent == node->m_pParent->m_pParent->m_pLeft)
		{
			NodeT *uncle = node->m_pParent->m_pParent->m_pRight;
			if (!uncle || uncle->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
			{
				if (node == node->m_pParent->m_pRight)
				{
					node = node->m_pParent;
					RotateLeft(node);
				}
				else
				{
					node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					node->m_pParent->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
					RotateRight(node->m_pParent->m_pParent);
				}
			}
			else if (uncle->m_nColor == CS_RED_BLACK_TREE_NODE_RED)
			{
				node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
				uncle->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
				node->m_pParent->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
				node = node->m_pParent->m_pParent;
			}
		}
		else
		{
			NodeT *uncle = node->m_pParent->m_pParent->m_pLeft;
			if (!uncle || uncle->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
			{
				if (node == node->m_pParent->m_pLeft)
				{
					node = node->m_pParent;
					RotateRight(node);
				}
				else
				{
					node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					node->m_pParent->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
					RotateLeft(node->m_pParent->m_pParent);
				}
			}
			else if (uncle->m_nColor == CS_RED_BLACK_TREE_NODE_RED)
			{
				node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
				uncle->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
				uncle->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
				node = node->m_pParent->m_pParent;
			}
		}
	}
	m_pRoot->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
}

CS_RED_BLACK_TREE_TEMPLATE
inline cs_void CS_RED_BLACK_TREE_QUAL::DeleteFixUp(NodeT *node)
{
	while (node != m_pRoot && node->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
	{
		if (node == node->m_pParent->m_pLeft)
		{
			NodeT *brother = node->m_pParent->m_pRight;
			if (brother->m_nColor == CS_RED_BLACK_TREE_NODE_RED)
			{
				brother->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
				node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
				RotateLeft(node->m_pParent);
			}
			else
			{
				if (brother->m_pLeft->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK
					&& brother->m_pRight->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
					node = node->m_pParent;
				}
				else if (brother->m_pRight->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
					brother->m_pLeft->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					RotateRight(brother);
				}
				else if (brother->m_pRight->m_nColor == CS_RED_BLACK_TREE_NODE_RED)
				{
					brother->m_nColor = node->m_pParent->m_nColor;
					node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					brother->m_pRight->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					RotateLeft(node->m_pParent);
					node = m_pRoot;
				}
			}
		}
		else
		{
			NodeT *brother = node->m_pParent->m_pLeft;
			if (brother->m_nColor == CS_RED_BLACK_TREE_NODE_RED)
			{
				brother->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
				node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
				RotateRight(node->m_pParent);
			}
			else
			{
				if (brother->m_pLeft->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK
					&& brother->m_pRight->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
					node = node->m_pParent;
				}
				else if (brother->m_pLeft->m_nColor == CS_RED_BLACK_TREE_NODE_BLACK)
				{
					brother->m_nColor = CS_RED_BLACK_TREE_NODE_RED;
					brother->m_pRight->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					RotateLeft(brother);
				}
				else if (brother->m_pLeft->m_nColor == CS_RED_BLACK_TREE_NODE_RED)
				{
					brother->m_nColor = node->m_pParent->m_nColor;
					node->m_pParent->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					brother->m_pLeft->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;
					RotateRight(node->m_pParent);
					node = m_pRoot;
				}
			}
		}
	}
	//最后将node置为根结点，
	node->m_nColor = CS_RED_BLACK_TREE_NODE_BLACK;    //并改为黑色。
}

CS_RED_BLACK_TREE_TEMPLATE
inline cs_void CS_RED_BLACK_TREE_QUAL::RotateLeft(NodeT *node)
{
	if (!node || !node->m_pRight)
	{
		return;
	}
	NodeT *lower_right = node->m_pRight;
	lower_right->m_pParent = node->m_pParent;
	node->m_pRight = lower_right->m_pLeft;
	if (lower_right->m_pLeft)
	{
		lower_right->m_pLeft->m_pParent = node;
	}
	if (!node->m_pParent)
	{
		// node为根节点
		m_pRoot = lower_right;
	}
	else
	{
		if (node == node->m_pParent->m_pLeft)
		{
			node->m_pParent->m_pLeft = lower_right;
		}
		else
		{
			node->m_pParent->m_pRight = lower_right;
		}
	}
	node->m_pParent = lower_right;
	lower_right->m_pLeft = node;
}

CS_RED_BLACK_TREE_TEMPLATE
inline cs_void CS_RED_BLACK_TREE_QUAL::RotateRight(NodeT *node)
{
	if (!node || !node->m_pLeft)
	{
		return;
	}
	NodeT *lower_left = node->m_pLeft;
	node->m_pLeft = lower_left->m_pRight;
	lower_left->m_pParent = node->m_pParent;
	if (lower_left->m_pRight)
	{
		lower_left->m_pRight->m_pParent = node;
	}
	if (!node->m_pParent)
	{
		// node为根节点
		m_pRoot = lower_left;
	}
	else
	{
		if (node == node->m_pParent->m_pRight)
		{
			node->m_pParent->m_pRight = lower_left;
		}
		else
		{
			node->m_pParent->m_pLeft = lower_left;
		}
	}
	node->m_pParent = lower_left;
	lower_left->m_pRight = node;
}

#undef CS_RED_BLACK_TREE_QUAL
#undef CS_RED_BLACK_TREE_TEMPLATE	
#undef CS_RED_BLACK_TREE_NODE_QUAL	
#undef CS_RED_BLACK_TREE_NODE_TEMPLATE

#endif // _CORE_RED_BLACK_TREE_INLINE_