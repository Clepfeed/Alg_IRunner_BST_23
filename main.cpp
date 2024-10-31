#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

ofstream fout("out.txt");

class Node {
public:
    Node* left = nullptr;
    Node* right = nullptr;
    Node* mother = nullptr;
    int num;
    int placeInLeafsArr;
    int leftChildren = 0; // Cчитаем сколько детей слева
    int rightChildren = 0; // Считаем сколько детей справа
    unordered_set<int> leftWays;
    unordered_set<int> rightWays;
    int floor = 0;

    Node(int n);
    Node(int n, Node* mother);
    void out()
    {
        cout << num << "\n";
    }
};
vector<Node*> leafs;
Node::Node(int n)
{
    placeInLeafsArr = leafs.size();
    leafs.push_back(this);
    num = n;
}
Node::Node(int n, Node* mother)
{
    if (mother->placeInLeafsArr != -1)
    {
        placeInLeafsArr = mother->placeInLeafsArr;
        mother->placeInLeafsArr = -1;
        leafs[placeInLeafsArr] = this;
    }
    else
    {
        placeInLeafsArr = leafs.size();
        leafs.push_back(this);
        num = n;
    }
    num = n;
    this->mother = mother;
    this->floor = mother->floor++;
}

class BST {
    Node* root = nullptr;

    void deleteTree(Node* node)
    {
        if (node != nullptr)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void addNode(int n, Node*& node, Node*& motherNode)
    {
        if (node == nullptr) node = new Node(n, motherNode);
        else if (node->num > n) addNode(n, node->left, node);
        else if (node->num < n) addNode(n, node->right, node);
    }

    void showTreeLeftPre(Node* node)
    {
        if (node != nullptr)
        {
            node->out();
            showTreeLeftPre(node->left);
            showTreeLeftPre(node->right);
        }
    }
    void deleteNode(int n, Node*& node)
    {
        if (node == nullptr) return;

        if (node->num == n)
        {
            Node* temp = nullptr; // новая вершина

            if (node->left == nullptr && node->right == nullptr) // если нету детей
            {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) // если правая дочерняя
            {
                temp = node->right;
                if (node != root) temp->mother = node->mother;
                delete node;
                node = temp;
            }
            else if (node->right == nullptr) // если левая дочерняя
            {
                temp = node->left;
                if (node != root) temp->mother = node->mother;
                delete node;
                node = temp;
            }
            else // если две дочерние
            {
                temp = node->right;
                while (temp->left != nullptr)
                {
                    temp = temp->left;
                }
                node->num = temp->num;
                deleteNode(temp->num, node->right);
            }
        }
        else
        {
            if (n > node->num)
            {
                deleteNode(n, node->right);
            }
            else
            {
                deleteNode(n, node->left);
            }
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST()
    {
        deleteTree(root);
    }

    void addNode(int n)
    {
        if (root == nullptr) root = new Node(n);
        else if (root->num > n) addNode(n, root->left, root);
        else if (root->num < n) addNode(n, root->right, root);
    }

    void showTreeLeftPre()
    {
        showTreeLeftPre(root);
    }
    void deleteNode(int n)
    {
        deleteNode(n, root);
    }
};


int main()
{
	ifstream fin("in.txt");
    BST tree;
	int lenth;
	fin >> lenth;
    int t;
    while (fin >> t)
    {
        tree.addNode(t);
    }
    tree.showTreeLeftPre();
    


	fout.close();
	return 0;
}