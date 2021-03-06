/*
 * =====================================================================================
 *
 *       Filename:  LinkedBinaryTree.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021年05月05日 21时29分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  RuiCao
 *   Organization:  Free
 *
 * =====================================================================================
 */
#include <iostream>
#include <memory>
#include <unordered_map>
#include <stack>
#include "Chain.h"
#include "LinkedBinaryTree.h"

using namespace std;

template<typename T>
void GenerateBinaryTree(vector<T> &input, BinaryTreeNode<T> **root, int input_size, int idx) {
    if (idx >= input_size) {
        return;
    }
    *root = new BinaryTreeNode<int>(input[idx], nullptr, nullptr);
    GenerateBinaryTree(input, &(*root)->left_child_, input_size, 2 * idx + 1);
    GenerateBinaryTree(input, &(*root)->right_child_, input_size, 2 * idx + 2);
}

template<typename T>
void GenerateChain(vector<T> &input, Chain<T> **listNode) {
    std::size_t sz = input.size();

    for (int i = 0; i < sz; ++i) {
        (*listNode)->insert(i, input[i]);
    }
}

template<typename T>
class Solution {
/* leet code:94 二叉树的中序遍历
 * 方法1: 递归
 * 定义inorder(root)表示当前遍历到root节点的答案，那么按照定义，
 * 我们只要递归调用inorder(root.left)来遍历root节点的左子树，
 * 然后将root节点的值加入答案，再递归调用inorder(root.right)
 * 来遍历root节点的右子树即可，递归终止的条件为碰到空节点。
 * */
private:
    void InOrder_94(BinaryTreeNode<T> *root, vector<T> &res) {
        if (root == nullptr) {
            return;
        }
        InOrder_94(root->left_child_, res);
        res.push_back(root->element_);
        InOrder_94(root->right_child_, res);
    }

public:
    vector<T> InorderTraversal_94_Recursion(BinaryTreeNode<T> *root) {
        vector<T> res{};
        InOrder_94(root, res);
        return res;
    }

    /* 方法*/
    vector<T> InorderTraversal_94_Stack(BinaryTreeNode<T> *root) {
        vector<T> res{};
        stack<BinaryTreeNode<T> *> stk;
        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left_child_;
            }
            root = stk.top();
            stk.pop();
            res.push_back(root->element_);
            root = root->right_child_;
        }
        return res;
    }

    /* 方法3: Morris 中序遍历
     * Morris遍历算法是另一种遍历二叉树的方法，
     * 它能将非递归的中序遍历空间复杂度降为O(1)。
     * Morris遍历算法整体步骤如下(假设当前遍历到的节点为x):
     * 1. 如果x无左孩子，先将x的值加入答案数组，再访问x的右孩子，即x=x.right
     * 2. 如果x有左孩子，则找到x左子树上最右的节点(即左子树中序遍历的最后一个节点，
     * x在中序遍历中的前驱节点），我们记为 predecessor。根据predecessor的右
     * 孩子是否为空，进行如下操作。
     *  - 如果predecessor的右孩子为空，则将其右孩子指向x，然后访问x的左孩子，即x=x.left。
     *  - 如果predecessor的右孩子不为空，则此时其右孩子指向x，说明我们已经遍历完x
     *    的左子树，我们将predecessor的右孩子置空，将x的值加入答案数组，然后访问x的
     *    右孩子，即x=x.right。
     * 3. 重复上述操作，直至访问完整棵树。
     * */
    vector<T> InorderTraversal_94_Morris(BinaryTreeNode<T> *root) {
        vector<T> res;
        BinaryTreeNode<T> *predecessor = nullptr;

        while (root != nullptr) {
            if (root->left_child_ != nullptr) {
                /* predecessor节点就是当前root结点向左走一步，
                 * 然后一直向右走至无法走为止 */
                predecessor = root->left_child_;
                while (predecessor->right_child_ != nullptr &&
                       predecessor->right_child_ != root) {
                    predecessor = predecessor->right_child_;
                }
                /* 让predecessor的右指针指向root，继续遍历左子树 */
                if (predecessor->right_child_ == nullptr) {
                    predecessor->right_child_ = root;
                    root = root->left_child_;
                } else {// 说明左子树已经访问完了，我们继续断开连接
                    res.push_back(root->element_);
                    predecessor->right_child_ == nullptr;
                    root = root->right_child_;
                }
            } else {// 如果没有左孩子，直接访问右孩子
                res.push_back(root->element_);
                root = root->right_child_;
            }
        }
        return res;
    }

public:
    bool check(BinaryTreeNode<T> *p, BinaryTreeNode<T> *q) {
        if (!p && !q)
            return true;

        if (!q || !p)
            return false;

        return p->element_ == q->element_ &&
               check(p->left_child_, q->right_child_) &&
               check(p->right_child_, q->left_child_);
    }

    bool IsSymmetric(LinkedBinaryTree<T> *root) {
        return check(root->root_, root->root_);
    }

public:
    bool check1(BinaryTreeNode<T> *p, BinaryTreeNode<T> *q) {
        ArrayQueue<BinaryTreeNode<T> *> queue;
        queue.push(p);
        queue.push(q);

        while (!queue.empty()) {
            p = queue.front();
            queue.pop();
            q = queue.front();
            queue.pop();

            if (!p && !q) continue;
            if ((!q || !p) || (p->element_ != q->element_))
                return false;

            queue.push(p->left_child_);
            queue.push(q->right_child_);

            queue.push(p->right_child_);
            queue.push(q->left_child_);
        }
        return true;
    }

    bool IsSymmetric1(LinkedBinaryTree<T> *root) {
        return check1(root->root_, root->root_);
    }

public:
    int maxDepth_dfs(BinaryTreeNode<int> *root) {
        if (root == nullptr)
            return 0;
        return max(maxDepth_dfs(root->left_child_), maxDepth_dfs(root->right_child_)) + 1;
    }

    int maxDepth(LinkedBinaryTree<int> *root) {
        return maxDepth_dfs(root->root_);
    }

public:
    ChainNode<T> *getMedian(ChainNode<T> *left, ChainNode<T> *right) {
        ChainNode<T> *fast = left;
        ChainNode<T> *slow = left;

        while (fast != right && fast->next_ != right) {
            fast = fast->next_->next_;
            slow = slow->next_;
        }
        return slow;
    }

    BinaryTreeNode<T> *buildTree(ChainNode<T> *left, ChainNode<T> *right) {
        if (left == right)
            return nullptr;

        ChainNode<T> *mid = getMedian(left, right);
        auto *root = new BinaryTreeNode<T>(mid->element_);
        root->left_child_ = buildTree(left, mid);
        root->right_child_ = buildTree(mid->next_, right);
        return root;
    }

    BinaryTreeNode<T> *sortedListToBST_109(Chain<T> *root) {
        return buildTree(root->first_node_, nullptr);
    }

    /* 方法1的时间复杂度的瓶颈在于寻找中位数节点。由于构造出的二叉搜索树
     * 的中序遍历结果就是链表本身，因此我们可以将分治和中序遍历结合起来，
     * 减少时间复杂度
     * */
    int GetLength_109_2(Chain<T> *head) {
        ChainNode<T> *chainNode_tmp = head->first_node_;
        int ret = 0;
        for (; chainNode_tmp != nullptr; chainNode_tmp = chainNode_tmp->next_) {
            ++ret;
        }
        return ret;
    }

    BinaryTreeNode<T> *BuildTree_109_2(Chain<T> *&head, int left, int right) {
//        ChainNode<T> *node = head->first_node_;
        if (left > right) {
            return nullptr;
        }
        int mid = (left + right + 1) / 2;
        auto *root = new BinaryTreeNode<T>();
        root->left_child_ = BuildTree_109_2(head, left, mid - 1);
        root->element_ = head->first_node_->element_;
        head->first_node_ = head->first_node_->next_;
        root->right_child_ = BuildTree_109_2(head, mid + 1, right);
        return root;
    }

    LinkedBinaryTree<T> *SortedListToBST_109_2(Chain<T> *root) {
        int length = GetLength_109_2(root);
        BinaryTreeNode<T> *res_tmp = BuildTree_109_2(root, 0, length - 1);
        LinkedBinaryTree<T> *res = new LinkedBinaryTree<T>(res_tmp, length);
        return res;
    }

    /* Leetcode 105
     * 二叉树前序遍历的顺序为:
     * 1.先遍历根节点
     * 2.递归的遍历左子树
     * 3.递归的遍历右子
     * */
    unordered_map<int, int> index;

    BinaryTreeNode<int> *MyBuildTree(const vector<int> &preorder, const vector<int> &inorder,
                                     int preorder_left, int preorder_right,
                                     int inorder_left, int inorder_right) {
        if (preorder_left > preorder_right) {
            return nullptr;
        }
        /*前序遍历中的第一个节点就是根节点*/
        int preorder_root = preorder_left;
        /**/
        int inorder_root = index[preorder[preorder_root]];

        BinaryTreeNode<int> *root = new BinaryTreeNode<int>(preorder[preorder_root]);
        int size_left_subtree = inorder_root - inorder_left;
        root->left_child_ = MyBuildTree(preorder, inorder, preorder_left + 1,
                                        preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
        root->right_child_ = MyBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right,
                                         inorder_root + 1, inorder_right);
        return root;
    }

    BinaryTreeNode<int> *BuildTree_105(vector<int> &preorder, vector<int> &inorder) {
        int n = preorder.size();
        /* 构造哈希映射,帮助我们快速定位根节点 */
        for (int i = 0; i < n; ++i) {
            index[inorder[i]] = i;
        }
        return MyBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }

    BinaryTreeNode<int> *BuildTree_105_2(vector<int> &preorder, vector<int> &inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        auto *root = new BinaryTreeNode<int>(preorder[0]);
        stack<BinaryTreeNode<int> *> stk;
        stk.push(root);
        int inOrderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preOrderVal = preorder[i];
            BinaryTreeNode<int> *node = stk.top();
            if (node->element_ != inorder[inOrderIndex]) {
                node->left_child_ = new BinaryTreeNode<int>(preOrderVal);
                stk.push(node->left_child_);
            } else {
                while (!stk.empty() && stk.top()->element_ == inorder[inOrderIndex]) {
                    node = stk.top();
                    stk.pop();
                    ++inOrderIndex;
                }
                node->right_child_ = new BinaryTreeNode<int>(preOrderVal);
                stk.push(node->right_child_);
            }
        }
        return root;
    }

    /* LeetCode105:二叉搜索树的中序遍历是升序序列, 题目给定的数组是
     * 按照升序排序的有序数组, 因此可以保证数组是二叉搜
     * 索树的中序遍历序列. */
    BinaryTreeNode<int> *helper_1(vector<int> &nums, int left, int right) {
        if (left > right) return nullptr;
        /* 总是选择中间位置左边的数字作为根节点 */
        int mid = (left + right) / 2;
        BinaryTreeNode<int> *root = new BinaryTreeNode<int>(nums[mid]);
        root->left_child_ = helper_1(nums, left, mid - 1);
        root->right_child_ = helper_1(nums, mid + 1, right);
        return root;
    }

    BinaryTreeNode<int> *helper_2(vector<int> &nums, int left, int right) {
        if (left > right) return nullptr;
        /* 总是选择中间位置左边的数字作为根节点 */
        int mid = (left + right + 1) / 2;
        BinaryTreeNode<int> *root = new BinaryTreeNode<int>(nums[mid]);
        root->left_child_ = helper_2(nums, left, mid - 1);
        root->right_child_ = helper_2(nums, mid + 1, right);
        return root;
    }

    BinaryTreeNode<int> *SortedArrayToBST108_1(vector<int> &nums) {
        return helper_2(nums, 0, nums.size() - 1);
    }
};


int main() {
    LinkedBinaryTree<int> a, x, y, z;
    y.makeTree(1, a, a);
    z.makeTree(2, a, a);
    x.makeTree(3, y, z);
    y.makeTree(4, x, a);
    cout << "Number of nodes = ";
    cout << y.size() << endl;
    cout << "height = ";
    cout << y.height() << endl;
    cout << "Pre-order sequence is ";
    y.preOrderOutput();
    cout << "In-order sequence is ";
    y.inOrderOutput();
    cout << "Post-order sequence is ";
    y.postOrderOutput();
    cout << "Level order sequence is ";
    y.levelOrderOutput();

    cout << "Right side view: ";
    vector<int> res = y.rightSideView();
    cout << "\n";
    vector<int> vec = vector<int>{1, 2, 2, 3, 4, 4, 3};
    BinaryTreeNode<int> *node;
    GenerateBinaryTree<int>(vec, &node, static_cast<int>(vec.size()), 0);
    LinkedBinaryTree<int> tr(node, vec.size());

    Solution<int> solution;
    /* Test LeetCode 94*/
    std::vector<int> res94{};
    res94 = solution.InorderTraversal_94_Morris(node);
//    res94 = solution.InorderTraversal_94_Stack(node);
    bool cmp_res = solution.IsSymmetric1(&tr);
    if (cmp_res)
        cout << "Is symmetric" << endl;
    else
        cout << "Is asymmetric" << endl;

    cout << "max depth is = " << solution.maxDepth(&tr) << endl;

    Chain<int> *list = new Chain<int>();
    GenerateChain(vec, &list);
    BinaryTreeNode<int> *newTree = solution.sortedListToBST_109(list);

    vector<int> preorder{3, 9, 8, 5, 4, 10, 20, 15, 7};        //{3, 9, 20, 15, 7};
    vector<int> inorder{4, 5, 8, 10, 9, 3, 15, 20, 7};         //{9, 3, 15, 20, 7};
    BinaryTreeNode<int> *res_105 = solution.BuildTree_105_2(preorder, inorder);

    vector<int> nums = {-10, -3, 0, 5, 9};
    BinaryTreeNode<int> *res_108_1 = solution.SortedArrayToBST108_1(nums);
    Chain<int> *list_new = new Chain<int>();
    GenerateChain(nums, &list_new);
    LinkedBinaryTree<int> *res_109_2 = solution.SortedListToBST_109_2(list_new);
    return 0;
}
