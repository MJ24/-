#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
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

#pragma region ����
// ͨ�ã��������start��end��Ԫ������
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

// �Ƴ�������ĳֵ��Ԫ�أ����������鳤�ȣ�������ԭ����˳��ɱ�
int removeElemInArray(vector<int> &nums, int val)
{
	// rightָ�����������һ��Ԫ�ص���һλ
	int right = nums.size();
	for (int i = 0; i < right; i++)
	{
		if (nums[i] == val)
		{
			nums[i] = nums[--right];
			--i; //�Ӻ����ڹ������¿ӵ���ҲҪͬ���Ƚ�һ��
		}
	}
	return right;
}

// �ҳ������к�Ϊ0�����������β�±꣬�ҳ�һ�������鼴��
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
// �ö��umap[0] = 0ʹ��ÿ��ѭ����һ���ж�currSum�Ƿ�Ϊ0
vector<int> subarraySumPro(vector<int> nums)
{
	int currSum = 0;
	unordered_map<int, int> umap;
	umap[0] = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		currSum += nums[i];
		if (umap.find(currSum) != umap.end())
			return vector<int>{umap[currSum], i};//ԭ��Ϊumap[currSum]+1
		else
			umap[currSum] = i + 1;//ԭ��Ϊumap[currSum] = i
	}
	return vector<int>{0, 0};
}

// ����ת�����������黹ԭ
void recoverRotatedSortedArray(int arr[], int length)
{
	if (length < 2) return;
	//���ҵ�����������ƻ���
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

#pragma region �ַ���
// ͨ�ã���str��start��end��˳������
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

// ��srcStr���ҵ���һ�γ��ֵ�subStr��λ��
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

// ���δ����⣬ʱ�临�Ӷ�o(n)���ռ临�Ӷ�o(1)
bool isChangeWord(string s, string t)
{
	int size = s.size();
	if (t.size() != size) return false;

	int charArr[256] = { 0 }; //��Ϊ256�ǳ������Կռ临�ӶȻ���o(1)

	for (int i = 0; i != size; ++i)
	{
		++charArr[s.at(i)];
		--charArr[t.at(i)];
	}

	for (int i = 0; i != 256; ++i)
		if (charArr[i]) return false;

	return true;
}

// �ж�A�ǲ��ǰ���B�������ַ���B�е��ظ��ַ�ҲҪ��A�����ٳ�����ô���,����B�ж��Ǵ�д��ĸ
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

// ����൥�ʰ��ձ��δʷ�����������ڱ��δʵ�Ϊһ��
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

// ��str�����index���ַ��Ƶ�ǰ����
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

// ��s�е��ʵ�˳�����򣬶����ʱ�������
string reverseWordsInStr(string &s)
{
	int size = s.size();
	if (!size) return s;
	reverseStr(s, 0, size - 1);

	// start������Ϊ0����Ϊindex��0��ʼ
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
	//�������һ���ַ����ǿո�ʱ���һ�����ʻ�û��ת
	if (!isspace(s.at(size - 1)))
	{
		reverseStr(s, start, size - 1);
	}
	return s;
}

// �ж�str�Ƿ�Ϊ�����ַ�������"A man, a plan, a canal: Panama"
bool isPalindromeStr(string &str)
{
	int start = 0, end = str.size() - 1;
	while (start < end)
	{
		if (!isalnum(str.at(start)))
		{
			++start;
			continue; //�ǵ�Ҫ����ѭ������
		}
		if (!isalnum(str.at(end)))
		{
			--end;
			continue;
		}
		// ��ͬ��ֱ�++ --���м�����Ƚ�
		if (tolower(str.at(start++)) != tolower(str.at(end--)))
			return false;
	}
	return true;
}

// ������Ӵ�
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
		// Ѱ����iΪ���ĵ��������ȵ�������Ӵ�
		int l = i, r = i;
		while (l >= 0 && r < len&&s.at(l) == s.at(r))
		{
			--l;
			++r;
		}
		if (r - l - 1 > subLen) //���������ѭ����l��r���Ѿ���������һ��
		{
			subStart = l + 1;
			subLen = r - l - 1;
		}
		// Ѱ����iΪ���ĵ�ż�����ȵ�������Ӵ�
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

// �ַ���ͨ���ƥ��
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

#pragma region ��̬�滮
// ������������ӡ��ά����
void printMatrix(const vector<vector<int> > &dp)
{
	for (auto row : dp)
	{
		for (auto num : row)
			cout << num << "\t";
		cout << endl;
	}
}
// ��̨��
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

	int res = steps[n - 1]; //ע��������n-1
	delete[] steps;
	return res;
}

// Ӳ�Ҵ���������������ֵ��Ӳ�Ҵ�������arr�У������aim��ֵ��Ǯ�ж��������
int changeCoins(int S[], int m, int n)
{
	// ���nΪ0�����ҵ���һ������
	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
	// û��Ӳ�ҿ����ˣ�Ҳ����0
	if (m <= 0)
		return 0;
	// ��������ĵݹ麯��
	return changeCoins(S, m - 1, n) + changeCoins(S, m, n - S[m - 1]);
}
int changeCoinsDP(int S[], int m, int n)
{
	int i, j, x, y;

	// ͨ�����¶��ϵķ�ʽ���������Ҫn+1��
	// ������������n=0
	vector<vector<int> > table(n + 1, vector<int>(m));
	//int table[n + 1][m];

	// ��ʼ��n=0����� (�ο�����ĵݹ����)
	for (i = 0; i < m; i++)
		table[0][i] = 1;

	for (i = 1; i < n + 1; i++)
	{
		for (j = 0; j < m; j++)
		{
			// ���� S[j] �ķ�����
			x = (i - S[j] >= 0) ? table[i - S[j]][j] : 0;

			// ������ S[j] �ķ�����
			y = (j >= 1) ? table[i][j - 1] : 0;

			table[i][j] = x + y;
		}
	}
	return table[n][m - 1];
}
int changeCoinsProDP(int S[], int m, int n)
{
	vector<int> table(m, 0);
	//��ʼ���������
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

	// ��ʼ����һ��index=0�����
	for (int j = 0; j < aim + 1; j++)
		dp[0][j] = j%arr[0] == 0 ? 1 : 0;
	// ��ʼ����һ��aim=0�����
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

// ��������Ͻǵ����½ǵ���̴�Ȱ·������
int getMatrixMinLen(const vector<vector<int> > &matrix)
{
	int rows = matrix.size();
	int cols = matrix[0].size();

	vector<vector<int> >dp(rows, vector<int>(cols));
	dp[0][0] = matrix[0][0];

	// ��ʼ����һ��
	for (int i = 1; i < cols; i++)
		dp[0][i] = dp[0][i - 1] + matrix[0][i];
	// ��ʼ����һ��
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

//�����������
int LISubSeq(int arr[], int len)
{
	int lisLen = 1;
	//dp[i]��ʾ��arr[i]��β��lcs�ĳ���
	vector<int> dp(len, 1);
	for (int i = 1; i != len; ++i)
	{
		//dp[i]������j��[0~i-1]��arr[j]<arr[i]�����У�dp[j]����+1
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

// ����������� eg:LCSubseq("1A2C3D4B56","B1D23CA45B6A")=6;
int LCSubseq(const string &str1, const string &str2)
{
	int m = str1.size(), n = str2.size();
	if (!m || !n) return 0;

	vector<vector<int> > dp(m, vector<int>(n));
	//��ʼ����һ��
	int i = 0;
	//�ҵ���str1�е�һ������str2[0]��i��i֮ǰ��dpֵΪ0
	for (; i != m; ++i)
	{
		if (str1.at(i) == str2[0])
			break;
		dp[i][0] = 0;
	}
	//i�����Ժ��dpֵΪ1
	for (; i != m; ++i)
		dp[i][0] = 1;

	//��ʼ����һ��
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
// Ϊdp������һ��һ�з���ͳһ�����һ�к͵�һ�У����ܴ���str1��str2Ϊ��
int LCSubseqPro(const string &str1, const string &str2)
{
	int len1 = str1.size(), len2 = str2.size();

	vector<vector<int> > dp(len1 + 1, vector<int>(len2 + 1, 0));
	// �ӵڶ��еڶ��п�ʼ����һ�к͵�һ��Ϊ��ʼֵȫ0
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
			// ע��Ƚϵ���str1[i - 1]��str2[j - 1]
			dp[i][j] = str1.at(i - 1) == str2.at(j - 1) ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
	}

	//printMatrix(dp);
	return dp[len1][len2];
}
// ������Ӵ�, ͬ��dp�����ӵ�һ�е�һ��ȫ0����ͳһ����
int LCSubStr(const string &str1, const string &str2)
{
	int len1 = str1.size(), len2 = str2.size();
	int lcs = 0;
	vector<vector<int> > dp(len1 + 1, vector<int>(len2 + 1));
	// �ӵڶ��еڶ��п�ʼ����һ�к͵�һ��Ϊ��ʼֵȫ0
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			// ע��Ƚϵ���str1[i - 1]��str2[j - 1]
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