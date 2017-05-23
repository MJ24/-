#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

#pragma region 树的辅助函数
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
// 按输入创建一棵二叉搜索树
TreeNode* createTree()
{
	TreeNode* root = 0;
	for (int n; cin >> n;)
	{
		TreeNode** parent = &root;
		TreeNode* cur = root;
		while (cur)
		{
			if (n < cur->val)
			{
				parent = &cur->left;
				cur = cur->left;
			}
			else
			{
				parent = &cur->right;
				cur = cur->right;
			}
		}
		*parent = new TreeNode(n);
	}
	return root;
}
void output_impl(TreeNode* n, bool left, string const& indent)
{
	if (n->right)
	{
		output_impl(n->right, false, indent + (left ? "|     " : "      "));
	}
	cout << indent;
	cout << (left ? '\\' : '/');
	cout << "-----";
	cout << n->val << endl;
	if (n->left)
	{
		output_impl(n->left, true, indent + (left ? "      " : "|     "));
	}
}
void printTree(TreeNode* root)
{
	if (!root)
		return;
	if (root->right)
		output_impl(root->right, false, "");
	cout << root->val << endl;
	if (root->left)
		output_impl(root->left, true, "");
}
#pragma endregion

#pragma region 数字处理
//拿石头游戏，桌上有若干石头，每次拿1-3颗，拿到最后一颗的赢
//分析下来，剩4颗，8颗，12等4的倍数颗时赢不了，其他情况都可以让对方赢不了
bool canWinNim(int n) {
	return (n % 4) == 0 ? false : true;
}
//给出一个非负数，将它所有数字相加，加出来的数再数字相加，直到加出来的数是0到9
int addDigits(int num) {
	if (num == 0)
	{
		return 0;
	}
	else
	{
		int i = num % 9;
		return i == 0 ? 9 : i;
	}
}
//找出数组中唯二出现过奇数次的数，其他都出现偶数次。
void printTwoOddNum(const vector<int> &vec)
{
	// 求出e=x^y
	int e = 0;
	for (auto n : vec)
		e ^= n;
	// 找到e中不为0的最低位k的位数
	int k = 0;
	while (!(e & (int)pow(2, k)))
		++k;
	// 求出其中一个数x
	int x = 0;
	for (auto n : vec)
	{
		if (n & (int)pow(2, k))
			x ^= n;
	}
	cout << "两个数分别为：" << x << "," << (x^e) << endl;
}
#pragma endregion

#pragma region 栈相关
// 进制转换，将十进制数num转成dec进制，如十进制1348为八进制2504
void decimalConvert(const int &oringeNum, const int &dec)
{
	int num = oringeNum;
	stack<int> stk;
	queue<int> que;
	while (num)
	{
		stk.push(num%dec);
		que.push(num%dec);
		num = num / dec;
	}
	ostringstream oss; // 如果用string来接受int的拼接是不行的
	while (!stk.empty())
	{
		oss << stk.top();
		stk.pop();
	}
	int res = 0, i = 0;
	while (!que.empty())
	{
		res += que.front() * pow(10, i);
		++i;
		que.pop();
	}
	cout << oringeNum << "的" << dec << "进制为："
		<< oss.str() << "/" << stoi(oss.str()) << "/" << res << endl;
}

// 根据中缀表达式求后缀表达式
string getPostExp(const string &exp)
{
	string postExp;
	string operators = "+-*/()";
	stack<char> stk;
	for (auto c : exp)
	{
		// c是操作数，直接写入后缀表达式
		if (operators.find(c) == string::npos)
			postExp += c;
		// c是优先级可能比栈顶小的运算符即+-
		else if (c == '+' || c == '-')
		{
			while (true)
			{
				if (stk.empty() || stk.top() == '(') //比c优先级低
				{
					stk.push(c);
					break;
				}
				else //栈顶为+-*/都比c优先级高，输出并弹出栈顶直到栈顶比c低
				{
					postExp += stk.top();
					stk.pop();
				}
			}
		}
		else if (c == '*' || c == '/')
		{
			while (true)
			{
				if (stk.empty())
				{
					stk.push(c);
					break;
				}
				else
				{
					char stkTop = stk.top();
					// 比c优先级高，输出并弹出栈顶直到栈顶比c低
					if (stkTop == '*' || stkTop == '/')
					{
						postExp += stk.top();
						stk.pop();
					}
					else //为+-或(比c优先级低
					{
						stk.push(c);
						break;
					}
				}
			}
		}
		else if (c == '(')
			stk.push(c);
		else // c==')'
		{
			char stkTop = stk.top();
			while (stkTop != '(')
			{
				postExp += stkTop;
				stk.pop();
				stkTop = stk.top();
			}
			stk.pop();
		}
	}
	while (!stk.empty())
	{
		postExp += stk.top();
		stk.pop();
	}
	return postExp;
}
// 根据后缀表达式求值，假设表达式运算数和符号以空格分割
double getPostExpVal(const string &exp)
{
	istringstream iss(exp);
	stack<double> stk;
	string item;
	string operators = "+-*/";
	while (iss >> item)
	{
		if (operators.find(item) == string::npos) //是运算数,直接入栈
			stk.push(stod(item));
		else //是运算符则拿出栈顶的两个运算数运算，并将结果再压栈
		{
			//运算顺序别搞错
			double next = stk.top(); stk.pop();
			double pre = stk.top(); stk.pop();
			if (item == "+")
				stk.push(pre + next);
			else if (item == "-")
				stk.push(pre - next);
			else if (item == "*")
				stk.push(pre * next);
			else
				stk.push(pre / next);
		}
	}
	return stk.top();
}

//验证括号是否匹配,如"()[]{}("返回false，"()[]{}"返回true
bool isValidExp(const string &exp)
{
	stack<char> stk;
	for (size_t i = 0; i < exp.size(); i++)
	{
		switch (exp.at(i))
		{
		case '(':
		case '[':
		case '{':
			stk.push(exp.at(i));
			break;
		case ')':
			if (stk.empty() || stk.top() != '(')
				return false;
			stk.pop(); //栈顶为'('
			break;
		case ']':
			if (stk.empty() || stk.top() != '[')
				return false;
			stk.pop(); //栈顶为'['
			break;
		case '}':
			if (stk.empty() || stk.top() != '{')
				return false;
			stk.pop(); //栈顶为'{'
			break;
		}
	}
	return stk.empty();
}
void testStack()
{
	cout << "a*b+(c-d/e)*f 的后缀表达式为：" << getPostExp("a*b+(c-d/e)*f") << endl;
	cout << "2*(9+6/3-5)+4 的后缀表达式为：" << getPostExp("2*(9+6/3-5)+4")
		<< " 它的值为：" << getPostExpVal("2 9 6 3 / + 5 - * 4 +") << endl;
	decimalConvert(1348, 8);
	cout << "(()[]{}的匹配结果为：" << isValidExp("(()[]{}") << endl;
	cout << "()[]{}(的匹配结果为：" << isValidExp("()[]{}(") << endl;
	cout << "()[{}的匹配结果为：" << isValidExp("()[{}") << endl;
	cout << "([{}])的匹配结果为：" << isValidExp("([{}])") << endl;
}
#pragma endregion

#pragma region 树相关
// 递归求一个二叉树的最大深度
int getTreeDepth(TreeNode* root) {
	if (!root)
		return 0;
	int lDep = getTreeDepth(root->left);
	int rDep = getTreeDepth(root->right);
	return lDep > rDep ? lDep + 1 : rDep + 1;
}
// 非递归用层序遍历思想求深度
int getTreeDepthPro(TreeNode* root)
{
	if (root == NULL)
		return 0;
	queue<TreeNode *> q;
	q.push(root);
	int res = 0;
	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0; i < size; ++i)
		{
			TreeNode *tmp = q.front();
			q.pop();
			if (tmp->left)
				q.push(tmp->left);
			if (tmp->right)
				q.push(tmp->right);
		}
		res++;
	}
	return res;
}
bool isBalanceTree(TreeNode* root)
{
	if (!root)
		return true;
	int lh = 0, rh = 0;
	if (isBalanceTree(root->left))
		lh = getTreeDepth(root->left);
	else
		return false;
	if (isBalanceTree(root->right))
		rh = getTreeDepth(root->right);
	else
		return false;
	return abs(lh - rh) < 2;
}

// 求搜索二叉树中两个节点的最近祖先节点
TreeNode* lowestCommonAncestor(TreeNode *root, TreeNode* n1, TreeNode*n2)
{
	if (root->val < n1->val && root->val < n2->val)
		return lowestCommonAncestor(root->right, n1, n2);
	else if (root->val > n1->val && root->val > n2->val)
		return lowestCommonAncestor(root->left, n1, n2);
	else
		return root;
}
TreeNode* lowestCommonAncestorPro1(TreeNode *root, TreeNode* n1, TreeNode*n2)
{
	while (true)
	{
		if (root->val < n1->val && root->val < n2->val)
			root = root->right;
		else if (root->val > n1->val && root->val > n2->val)
			root = root->left;
		else
			return root;
	}
}
TreeNode* lowestCommonAncestorPro2(TreeNode *root, TreeNode* n1, TreeNode*n2)
{
	while ((root->val - n1->val)*(root->val - n2->val) > 0)
		root = (root->val > n1->val) ? root->left : root->right;
	return root;
}
// 求普通二叉树中两个节点的最近祖先节点
TreeNode* lowestCommonAncestor2(TreeNode *root, TreeNode* n1, TreeNode*n2)
{
	// 如果当前节点为NULL说明走到了叶节点都没有找到两个节点中的其中一个
	// 如果当前节点为n1,n2之中的一个，那么返回找到的这个
	if (root == nullptr || root == n1 || root == n2)
		return root;
	TreeNode *L = lowestCommonAncestor2(root->left, n1, n2);
	TreeNode *R = lowestCommonAncestor2(root->right, n1, n2);
	if (L&&R) // 如果当前节点左右节点都各找到一个，那么返回当前节点
		return root;
	return L ? L : R; // 只在1个子树中找到了一个，就返回它，另一个节点是它的子孙节点
}
// 测试LCA的各个函数
void testForLCA()
{
	TreeNode *node6 = new TreeNode(6); TreeNode *node3 = new TreeNode(3);
	TreeNode *node9 = new TreeNode(9); TreeNode *node1 = new TreeNode(1);
	TreeNode *node4 = new TreeNode(4); TreeNode *node7 = new TreeNode(7);
	TreeNode *node8 = new TreeNode(8);
	node6->left = node3; node6->right = node9;
	node3->left = node1; node3->right = node4;
	node9->left = node7; node7->right = node8;
	printTree(node6);
	cout << "4和8，4和1，9和8，4和6的LCA分别是：" << endl;
	cout << lowestCommonAncestor(node6, node4, node8)->val << " , ";
	cout << lowestCommonAncestor(node6, node4, node1)->val << " , ";
	cout << lowestCommonAncestor(node6, node9, node8)->val << " , ";
	cout << lowestCommonAncestor(node6, node4, node6)->val << endl;
	cout << lowestCommonAncestorPro1(node6, node4, node8)->val << " , ";
	cout << lowestCommonAncestorPro1(node6, node4, node1)->val << " , ";
	cout << lowestCommonAncestorPro1(node6, node9, node8)->val << " , ";
	cout << lowestCommonAncestorPro1(node6, node4, node6)->val << endl;
	cout << lowestCommonAncestorPro2(node6, node4, node8)->val << " , ";
	cout << lowestCommonAncestorPro2(node6, node4, node1)->val << " , ";
	cout << lowestCommonAncestorPro2(node6, node9, node8)->val << " , ";
	cout << lowestCommonAncestorPro2(node6, node4, node6)->val << endl;
	cout << lowestCommonAncestor2(node6, node4, node8)->val << " , ";
	cout << lowestCommonAncestor2(node6, node4, node1)->val << " , ";
	cout << lowestCommonAncestor2(node6, node9, node8)->val << " , ";
	cout << lowestCommonAncestor2(node6, node4, node6)->val << endl;
}
// 求整棵树节点间的最大距离
int getTreeMaxDistance(TreeNode *root)
{
	if (root == nullptr)
		return 0;
	else if (root->left == nullptr && root->right == nullptr)
		return 0;
	int dl = getTreeMaxDistance(root->left);
	int dr = getTreeMaxDistance(root->right);
	int dlr = getTreeDepth(root->left) + getTreeDepth(root->right);
	if (dl > dr)
		return dl > dlr ? dl : dlr;
	else
		return dr > dlr ? dr : dlr;
}
#pragma endregion

int main()
{
	system("pause");
	return 0;
}