#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

#pragma region ���ĸ�������
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
// �����봴��һ�ö���������
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

#pragma region ���ִ���
//��ʯͷ��Ϸ������������ʯͷ��ÿ����1-3�ţ��õ����һ�ŵ�Ӯ
//����������ʣ4�ţ�8�ţ�12��4�ı�����ʱӮ���ˣ���������������öԷ�Ӯ����
bool canWinNim(int n) {
	return (n % 4) == 0 ? false : true;
}
//����һ���Ǹ�������������������ӣ��ӳ���������������ӣ�ֱ���ӳ���������0��9
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
//�ҳ�������Ψ�����ֹ������ε���������������ż���Ρ�
void printTwoOddNum(const vector<int> &vec)
{
	// ���e=x^y
	int e = 0;
	for (auto n : vec)
		e ^= n;
	// �ҵ�e�в�Ϊ0�����λk��λ��
	int k = 0;
	while (!(e & (int)pow(2, k)))
		++k;
	// �������һ����x
	int x = 0;
	for (auto n : vec)
	{
		if (n & (int)pow(2, k))
			x ^= n;
	}
	cout << "�������ֱ�Ϊ��" << x << "," << (x^e) << endl;
}
#pragma endregion

#pragma region ջ���
// ����ת������ʮ������numת��dec���ƣ���ʮ����1348Ϊ�˽���2504
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
	ostringstream oss; // �����string������int��ƴ���ǲ��е�
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
	cout << oringeNum << "��" << dec << "����Ϊ��"
		<< oss.str() << "/" << stoi(oss.str()) << "/" << res << endl;
}

// ������׺���ʽ���׺���ʽ
string getPostExp(const string &exp)
{
	string postExp;
	string operators = "+-*/()";
	stack<char> stk;
	for (auto c : exp)
	{
		// c�ǲ�������ֱ��д���׺���ʽ
		if (operators.find(c) == string::npos)
			postExp += c;
		// c�����ȼ����ܱ�ջ��С���������+-
		else if (c == '+' || c == '-')
		{
			while (true)
			{
				if (stk.empty() || stk.top() == '(') //��c���ȼ���
				{
					stk.push(c);
					break;
				}
				else //ջ��Ϊ+-*/����c���ȼ��ߣ����������ջ��ֱ��ջ����c��
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
					// ��c���ȼ��ߣ����������ջ��ֱ��ջ����c��
					if (stkTop == '*' || stkTop == '/')
					{
						postExp += stk.top();
						stk.pop();
					}
					else //Ϊ+-��(��c���ȼ���
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
// ���ݺ�׺���ʽ��ֵ��������ʽ�������ͷ����Կո�ָ�
double getPostExpVal(const string &exp)
{
	istringstream iss(exp);
	stack<double> stk;
	string item;
	string operators = "+-*/";
	while (iss >> item)
	{
		if (operators.find(item) == string::npos) //��������,ֱ����ջ
			stk.push(stod(item));
		else //����������ó�ջ�����������������㣬���������ѹջ
		{
			//����˳�����
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

//��֤�����Ƿ�ƥ��,��"()[]{}("����false��"()[]{}"����true
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
			stk.pop(); //ջ��Ϊ'('
			break;
		case ']':
			if (stk.empty() || stk.top() != '[')
				return false;
			stk.pop(); //ջ��Ϊ'['
			break;
		case '}':
			if (stk.empty() || stk.top() != '{')
				return false;
			stk.pop(); //ջ��Ϊ'{'
			break;
		}
	}
	return stk.empty();
}
void testStack()
{
	cout << "a*b+(c-d/e)*f �ĺ�׺���ʽΪ��" << getPostExp("a*b+(c-d/e)*f") << endl;
	cout << "2*(9+6/3-5)+4 �ĺ�׺���ʽΪ��" << getPostExp("2*(9+6/3-5)+4")
		<< " ����ֵΪ��" << getPostExpVal("2 9 6 3 / + 5 - * 4 +") << endl;
	decimalConvert(1348, 8);
	cout << "(()[]{}��ƥ����Ϊ��" << isValidExp("(()[]{}") << endl;
	cout << "()[]{}(��ƥ����Ϊ��" << isValidExp("()[]{}(") << endl;
	cout << "()[{}��ƥ����Ϊ��" << isValidExp("()[{}") << endl;
	cout << "([{}])��ƥ����Ϊ��" << isValidExp("([{}])") << endl;
}
#pragma endregion

#pragma region �����
// �ݹ���һ����������������
int getTreeDepth(TreeNode* root) {
	if (!root)
		return 0;
	int lDep = getTreeDepth(root->left);
	int rDep = getTreeDepth(root->right);
	return lDep > rDep ? lDep + 1 : rDep + 1;
}
// �ǵݹ��ò������˼�������
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

// �������������������ڵ��������Ƚڵ�
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
// ����ͨ�������������ڵ��������Ƚڵ�
TreeNode* lowestCommonAncestor2(TreeNode *root, TreeNode* n1, TreeNode*n2)
{
	// �����ǰ�ڵ�ΪNULL˵���ߵ���Ҷ�ڵ㶼û���ҵ������ڵ��е�����һ��
	// �����ǰ�ڵ�Ϊn1,n2֮�е�һ������ô�����ҵ������
	if (root == nullptr || root == n1 || root == n2)
		return root;
	TreeNode *L = lowestCommonAncestor2(root->left, n1, n2);
	TreeNode *R = lowestCommonAncestor2(root->right, n1, n2);
	if (L&&R) // �����ǰ�ڵ����ҽڵ㶼���ҵ�һ������ô���ص�ǰ�ڵ�
		return root;
	return L ? L : R; // ֻ��1���������ҵ���һ�����ͷ���������һ���ڵ�����������ڵ�
}
// ����LCA�ĸ�������
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
	cout << "4��8��4��1��9��8��4��6��LCA�ֱ��ǣ�" << endl;
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
// ���������ڵ���������
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