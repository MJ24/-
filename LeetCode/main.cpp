#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
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

#pragma region 数组
// 通用，将数组从start到end的元素逆序
void reverseArr(int arr[], int start, int end)
{
	while (start < end)
	{
		arr[start] ^= arr[end];
		arr[end] ^= arr[start];
		arr[start] ^= arr[end];
		++start;
		--end;
	}
}

// 移除数组中某值的元素，返回新数组长度，数组中原数据顺序可变
int removeElemInArray(vector<int> &nums, int val)
{
	// right指向新数组最后一个元素的下一位
	int right = nums.size();
	for (int i = 0; i < right; i++)
	{
		if (nums[i] == val)
		{
			nums[i] = nums[--right];
			--i; //从后面挖过来填新坑的数也要同样比较一次
		}
	}
	return right;
}

// 找出数组中和为0的子数组的首尾下标，找出一个子数组即可
vector<int> subarraySum(vector<int> &nums)
{
	int currSum = 0;
	unordered_map<int, int> umap;
	for (int i = 0; i < nums.size(); i++)
	{
		currSum += nums[i];
		if (currSum == 0)
			return vector<int>{0, i};
		if (umap.find(currSum) != umap.end())
			return vector<int>{umap[currSum] + 1, i};
		else
			umap[currSum] = i;
	}
	return vector<int>{0, 0};
}
// 用多加umap[0] = 0使得每次循环少一个判断currSum是否为0
vector<int> subarraySumPro(vector<int> nums)
{
	int currSum = 0;
	unordered_map<int, int> umap;
	umap[0] = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		currSum += nums[i];
		if (umap.find(currSum) != umap.end())
			return vector<int>{umap[currSum], i};//原来为umap[currSum]+1
		else
			umap[currSum] = i + 1;//原来为umap[currSum] = i
	}
	return vector<int>{0, 0};
}

// 将旋转过的有序数组还原
void recoverRotatedSortedArray(int arr[], int length)
{
	if (length < 2) return;
	//先找到数组有序的破坏点
	int recPoint = 0;
	while (recPoint < length - 1 && arr[recPoint] <= arr[recPoint + 1])
		recPoint++;
	if (recPoint < length - 1)
	{
		reverseArr(arr, 0, recPoint);
		reverseArr(arr, recPoint + 1, length - 1);
		reverseArr(arr, 0, length - 1);
	}
}
#pragma endregion

#pragma region 字符串
// 通用，将str从start到end的顺序逆序
void reverseStr(string &str, int start, int end)
{
	while (start < end)
	{
		char tmp = str.at(start);
		str.at(start) = str.at(end);
		str.at(end) = tmp;
		++start;
		--end;
	}
}

// 从srcStr中找到第一次出现的subStr的位置
int strFind(string srcStr, string subStr)
{
	int m = srcStr.size(), n = subStr.size();
	if (!n) return 0;
	for (int i = 0; i != m - n + 1; ++i)
	{
		int j = 0;
		for (; j != n; ++j)
			if (srcStr.at(i + j) != subStr.at(j)) break;
		if (j == n) return i;
	}
	return -1;
}

// 变形词问题，时间复杂度o(n)，空间复杂度o(1)
bool isChangeWord(string s, string t)
{
	int size = s.size();
	if (t.size() != size) return false;

	int charArr[256] = { 0 }; //因为256是常数所以空间复杂度还是o(1)

	for (int i = 0; i != size; ++i)
	{
		++charArr[s.at(i)];
		--charArr[t.at(i)];
	}

	for (int i = 0; i != 256; ++i)
		if (charArr[i]) return false;

	return true;
}

// 判断A是不是包含B的所有字符，B中的重复字符也要在A中至少出现那么多次,假设B中都是大写字母
bool isAContainsB(string A, string B)
{
	int m = A.size(), n = B.size();
	if (m < n) return false;

	int charArr[26] = { 0 };

	for (int i = 0; i != n; ++i)
		++charArr[A.at(i) - 'A'];

	for (int i = 0; i != m; ++i)
	{
		--charArr[B.at(i) - 'A'];
		if (charArr[B.at(i) - 'A'] < 0) return false;
	}
	return true;
}

// 将许多单词按照变形词分组输出，属于变形词的为一组
void groupChangeWords(const vector<string> &strs)
{
	unordered_map<string, vector<string>> umap;
	for (string str : strs)
	{
		string tmp = str;
		sort(tmp.begin(), tmp.end());
		umap[tmp].push_back(str);
	}

	for (auto strsPair : umap)
	{
		for (string str : strsPair.second)
			cout << str << " ";
		cout << endl;
	}
}

// 将str的最后index个字符移到前面来
string moveStr(string str, int index)
{
	int size = str.size();
	if (!size || index < 0) return str;
	index %= size;
	reverseStr(str, 0, size - 1);
	reverseStr(str, 0, index - 1);
	reverseStr(str, index, size - 1);
	return str;
}

// 把s中单词的顺序逆序，而单词本身不逆序
string reverseWordsInStr(string &s)
{
	int size = s.size();
	if (!size) return s;
	reverseStr(s, 0, size - 1);

	// start不能置为0，因为index从0开始
	int current = 0, start = -1;
	while (current < size)
	{
		if (!isspace(s.at(current)) && start == -1)
		{
			start = current;
		}
		if (isspace(s.at(current)) && start != -1)
		{
			reverseStr(s, start, current - 1);
			start = -1;
		}
		++current;
	}
	//处理当最后一个字符不是空格时最后一个单词还没反转
	if (!isspace(s.at(size - 1)))
	{
		reverseStr(s, start, size - 1);
	}
	return s;
}

// 判断str是否为回文字符串，如"A man, a plan, a canal: Panama"
bool isPalindromeStr(string &str)
{
	int start = 0, end = str.size() - 1;
	while (start < end)
	{
		if (!isalnum(str.at(start)))
		{
			++start;
			continue; //记得要跳出循环继续
		}
		if (!isalnum(str.at(end)))
		{
			--end;
			continue;
		}
		// 相同则分别++ --往中间继续比较
		if (tolower(str.at(start++)) != tolower(str.at(end--)))
			return false;
	}
	return true;
}

// 最长回文子串
bool isPalindromeSubStr(const string &str, int start, int end)
{
	if (start < 0) return false;
	while (start < end)
	{
		if (str.at(start++) != str.at(end--))
			return false;
	}
	return true;
}
string longestPalindrome(string s) {
	int len = s.size();
	if (len < 2) return s;
	int subStart = 0, subLen = 1;

	for (int i = 1; i < len; i++)
	{
		if (isPalindromeSubStr(s, i - subLen - 1, i))
		{
			subStart = i - subLen - 1;
			subLen += 2;
		}
		else if (isPalindromeSubStr(s, i - subLen, i))
		{
			subStart = i - subLen;
			++subLen;
		}
	}
	return s.substr(subStart, subLen);
}
string longestPalindrome2(string s) {
	int len = s.size();
	if (len < 2) return s;
	int subStart = 0, subLen = 1;

	for (int i = 0; i < len - subLen / 2; i++)
	{
		// 寻找以i为中心的奇数长度的最长回文子串
		int l = i, r = i;
		while (l >= 0 && r < len&&s.at(l) == s.at(r))
		{
			--l;
			++r;
		}
		if (r - l - 1 > subLen) //出了上面的循环后l和r都已经各多走了一步
		{
			subStart = l + 1;
			subLen = r - l - 1;
		}
		// 寻找以i为中心的偶数长度的最长回文子串
		l = i, r = i + 1;
		while (l >= 0 && r < len&&s.at(l) == s.at(r))
		{
			--l;
			++r;
		}
		if (r - l - 1 > subLen)
		{
			subStart = l + 1;
			subLen = r - l - 1;
		}
	}
	return s.substr(subStart, subLen);
}

// 字符串通配符匹配
bool isStrMatch(const char *s, const char *p) {
	const char* star = NULL;
	const char* ss = s;
	while (*s) {
		//advancing both pointers when (both characters match) or ('?' found in pattern)
		//note that *p will not advance beyond its length 
		if ((*p == '?') || (*p == *s)) { s++; p++; continue; }

		// * found in pattern, track index of *, only advancing pattern pointer 
		if (*p == '*') { star = p++; ss = s; continue; }

		//current characters didn't match, last pattern pointer was *, current pattern pointer is not *
		//only advancing pattern pointer
		if (star) { p = star + 1; s = ++ss; continue; }

		//current pattern pointer is not star, last patter pointer was not *
		//characters do not match
		return false;
	}

	//check for remaining characters in pattern
	while (*p == '*') { p++; }

	return !*p;
}
bool isStrMatch2(string s, string p) {
	int star = 0, ss = 0, i = 0, j = 0;
	while (s[i]) {
		if (p[j] == '?' || p[j] == s[i]) { j++; i++; continue; }
		if (p[j] == '*') { star = ++j; ss = i; continue; }
		if (star) { j = star; i = ++ss; continue; }
		return false;
	}
	while (p[j] == '*') j++;
	return !p[j];

}

string countAndSay(int n)
{
	if (n == 1) return "1";
	string lastStr = countAndSay(n - 1) + '#';
	int count = 0;
	char c = lastStr[0];
	ostringstream res;
	for (int i = 0; i < lastStr.size(); i++)
	{
		if (lastStr.at(i) == c)
			++count;
		else
		{
			res << count << c;
			c = lastStr.at(i);
			count = 1;
		}
	}
	return res.str();
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

#pragma region 动态规划
// 辅助函数，打印二维矩阵
void printMatrix(const vector<vector<int> > &dp)
{
	for (auto row : dp)
	{
		for (auto num : row)
			cout << num << "\t";
		cout << endl;
	}
}
// 上台阶
int countSteps(int n)
{
	if (n < 1) return 0;
	if (n == 1 || n == 2) return n;
	return countSteps(n - 1) + countSteps(n - 2);
}
int countStepsDP(int n)
{
	if (n < 1) return 0;
	if (n == 1 || n == 2) return n;

	int *steps = new int[n] {1, 2};

	for (int i = 2; i != n; ++i)
		steps[i] = steps[i - 1] + steps[i - 2];

	int res = steps[n - 1]; //注意这里是n-1
	delete[] steps;
	return res;
}

// 硬币凑整，给定各种面值的硬币存在数组arr中，求组成aim价值的钱有多少种组合
int changeCoins(int S[], int m, int n)
{
	// 如果n为0，就找到了一个方案
	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	// 没有硬币可用了，也返回0
	if (m <= 0)
		return 0;
	// 按照上面的递归函数
	return changeCoins(S, m - 1, n) + changeCoins(S, m, n - S[m - 1]);
}
int changeCoinsDP(int S[], int m, int n)
{
	int i, j, x, y;

	// 通过自下而上的方式打表我们需要n+1行
	// 最基本的情况是n=0
	vector<vector<int> > table(n + 1, vector<int>(m));
	//int table[n + 1][m];

	// 初始化n=0的情况 (参考上面的递归程序)
	for (i = 0; i < m; i++)
		table[0][i] = 1;

	for (i = 1; i < n + 1; i++)
	{
		for (j = 0; j < m; j++)
		{
			// 包括 S[j] 的方案数
			x = (i - S[j] >= 0) ? table[i - S[j]][j] : 0;

			// 不包括 S[j] 的方案数
			y = (j >= 1) ? table[i][j - 1] : 0;

			table[i][j] = x + y;
		}
	}
	return table[n][m - 1];
}
int changeCoinsProDP(int S[], int m, int n)
{
	vector<int> table(m, 0);
	//初始化基本情况
	table[0] = 1;

	for (int i = 0; i < m; i++)
		for (int j = S[i]; j <= n; j++)
			table[j] += table[j - S[i]];

	return table[n];
}
int myChangeCoins(int arr[], int len, int index, int aim)
{
	int res = 0;
	if (index == len)
		res = aim == 0 ? 1 : 0;
	else
	{
		for (int i = 0; i*arr[index] <= aim; i++)
			res += myChangeCoins(arr, len, index + 1, aim - i*arr[index]);
	}
	return res;
}
int MyChangeCoinsDP(int arr[], int len, int aim)
{
	vector<vector<int> > dp(len, vector<int>(aim + 1));

	// 初始化第一行index=0的情况
	for (int j = 0; j < aim + 1; j++)
		dp[0][j] = j%arr[0] == 0 ? 1 : 0;
	// 初始化第一列aim=0的情况
	for (int i = 0; i < len; i++)
		dp[i][0] = 1;

	for (int i = 1; i < len; i++)
	{
		for (int j = 1; j < aim + 1; j++)
			dp[i][j] = dp[i - 1][j] + (j >= arr[i] ? dp[i][j - arr[i]] : 0);
	}
	return dp[len - 1][aim];
}
void testForchangeCoins()
{
	int arr[] = { 2, 5, 3, 6 };
	cout << changeCoins(arr, 4, 100) << "/" << changeCoinsDP(arr, 4, 100) << endl;
	cout << myChangeCoins(arr, 4, 0, 100) << "/" << MyChangeCoinsDP(arr, 4, 100) << endl;
}

// 求矩阵左上角到右下角的最短带劝路径长度
int getMatrixMinLen(const vector<vector<int> > &matrix)
{
	int rows = matrix.size();
	int cols = matrix[0].size();

	vector<vector<int> >dp(rows, vector<int>(cols));
	dp[0][0] = matrix[0][0];

	// 初始化第一行
	for (int i = 1; i < cols; i++)
		dp[0][i] = dp[0][i - 1] + matrix[0][i];
	// 初始化第一列
	for (int i = 1; i < rows; i++)
		dp[i][0] = dp[i - 1][0] + matrix[i][0];

	for (int i = 1; i < rows; i++)
	{
		for (int j = 1; j < cols; j++)
			dp[i][j] = matrix[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
	}

	return dp[rows - 1][cols - 1];
}
void testForMatrixMinLen()
{
	vector<vector<int> > matrix;
	matrix.push_back({ 1, 3, 5, 9 });
	matrix.push_back({ 8, 1, 3, 4 });
	matrix.push_back({ 5, 0, 6, 1 });
	matrix.push_back({ 8, 8, 4, 0 });
	getMatrixMinLen(matrix);
}

//最长递增子序列
int LISubSeq(int arr[], int len)
{
	int lisLen = 1;
	//dp[i]表示以arr[i]结尾的lcs的长度
	vector<int> dp(len, 1);
	for (int i = 1; i != len; ++i)
	{
		//dp[i]是所有j从[0~i-1]中arr[j]<arr[i]的数中，dp[j]最大的+1
		for (int j = 0; j < i; j++)
		{
			if (arr[j] <= arr[i] && dp[j] > dp[i] - 1)
				dp[i] = dp[j] + 1;
		}
		if (dp[i] > lisLen)
			lisLen = dp[i];
	}
	return lisLen;
}

// 最长公共子序列 eg:LCSubseq("1A2C3D4B56","B1D23CA45B6A")=6;
int LCSubseq(const string &str1, const string &str2)
{
	int m = str1.size(), n = str2.size();
	if (!m || !n) return 0;

	vector<vector<int> > dp(m, vector<int>(n));
	//初始化第一列
	int i = 0;
	//找到第str1中第一个等于str2[0]的i，i之前的dp值为0
	for (; i != m; ++i)
	{
		if (str1.at(i) == str2[0])
			break;
		dp[i][0] = 0;
	}
	//i及其以后的dp值为1
	for (; i != m; ++i)
		dp[i][0] = 1;

	//初始化第一行
	int j = 0;
	for (; j != n; ++j)
	{
		if (str2.at(j) == str1[0])
			break;
		dp[0][j] = 0;
	}
	for (; j != n; ++j)
		dp[0][j] = 1;

	for (int i = 1; i < m; i++)
	{
		for (int j = 1; j < n; j++)
			dp[i][j] = str1.at(i) == str2.at(j) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
	}

	//printMatrix(dp);
	return dp[m - 1][n - 1];
}
// 为dp矩阵多加一行一列方便统一处理第一行和第一列，还能处理str1或str2为空
int LCSubseqPro(const string &str1, const string &str2)
{
	int len1 = str1.size(), len2 = str2.size();

	vector<vector<int> > dp(len1 + 1, vector<int>(len2 + 1, 0));
	// 从第二行第二列开始，第一行和第一列为初始值全0
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
			// 注意比较的是str1[i - 1]和str2[j - 1]
			dp[i][j] = str1.at(i - 1) == str2.at(j - 1) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
	}

	//printMatrix(dp);
	return dp[len1][len2];
}
// 最长公共子串, 同上dp矩阵多加第一行第一列全0方便统一处理
int LCSubStr(const string &str1, const string &str2)
{
	int len1 = str1.size(), len2 = str2.size();
	int lcs = 0;
	vector<vector<int> > dp(len1 + 1, vector<int>(len2 + 1));
	// 从第二行第二列开始，第一行和第一列为初始值全0
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			// 注意比较的是str1[i - 1]和str2[j - 1]
			if (str1.at(i - 1) == str2.at(j - 1))
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				lcs = max(lcs, dp[i][j]);
			}
		}
	}
	//printMatrix(dp);
	return lcs;
}
#pragma endregion


int main()
{
	//cout << strFind("asdfasdf", "sd") << endl;
	//cout << isChangeWord("abcda", "bacdg") << endl;
	//groupChangeWords({ "dcs", "csd", "cd", "c", "dc", "a", "zb", "dc", "c", "sdfsf" });

	cout << "" << endl;
	system("pause");
	return 0;
}