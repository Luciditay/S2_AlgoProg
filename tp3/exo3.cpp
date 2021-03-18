#include "lib/mainwindow.h"
#include "lib/tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

struct BinarySearchTree : public BinaryTree
{
	BinarySearchTree(int value=0) : BinaryTree(value) {}
	virtual ~BinarySearchTree() {}

	void insertNumber(int value) {
        /*
         * check where the new value must be inserted;
         * if there is no child in this emplacement
         * create a new node here else ask the child
         * to insert the value
         */

        if (this->value > value)
        {
            if (this->right==nullptr)
            {
                this->right=createNode(value);
            }
            else
            {
                this->right->insertNumber(value);
            }
        }
        else

        {
            if (this->left==nullptr)
            {
                this->left=createNode(value);
            }
            else
            {
                this->left->insertNumber(value);
            }
        }

	}

   uint height() const	{
        // should return the maximum height between left child and
        // right child +1 for itself. If there is no child, return
        // just 1

       int l=1, r=1;

        if (this->left==nullptr && this->right==nullptr)
            return 1;
        else
        {
            if (this->left!=nullptr)
            {
                l+=this->left->height();
            }
            if (this->right!=nullptr)
            {
                r+=this->right->height();
            }
        }

        if (l>r)
            return l;
        return r;
    }

	uint nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        if (this->left==nullptr && this->right==nullptr)
        {
            return 1;
        }
        else if (this->left==nullptr) // <=> right n'est pas nul
        {return 1 + (this->right->nodesCount());
        }
        else if (this->right==nullptr)
        {
            return 1 + (this->left->nodesCount());
        }
        else
            return 1 + this->right->nodesCount() + this->left->nodesCount();
    }

	bool isLeaf() const {
         if (this->left==nullptr && this->right==nullptr)
         {
            return true;
         }
         return false;
	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        if (this->isLeaf())
        {
            leaves[leavesCount]=this;
            leavesCount++;
        }
        if (this->right!=nullptr)
            this->right->allLeaves(leaves, leavesCount);
        if (this->left!=nullptr)
            this->left->allLeaves(leaves, leavesCount);
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        if (this->left!=nullptr)
        {
           this->left->inorderTravel(nodes, nodesCount);
        }
        nodes[nodesCount]=this;
        nodesCount++;

        if (this->right!=nullptr)
        {
           this->right->inorderTravel(nodes, nodesCount);
        }

	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {

        nodes[nodesCount]=this;
        nodesCount++;

        if (this->left!=nullptr)
        {
           this->left->preorderTravel(nodes, nodesCount);
        }

        if (this->right!=nullptr)
        {
           this->right->preorderTravel(nodes, nodesCount);
        }

	}

	void postorderTravel(Node* nodes[], uint& nodesCount) {
        if (this->left!=nullptr)
        {
          this->left->postorderTravel(nodes, nodesCount);
        }

        if (this->right!=nullptr)
        {
          this->right->postorderTravel(nodes, nodesCount);
        }
        nodes[nodesCount]=this;
        nodesCount++;
    }

    Node* find(int value) { // Ne marche pas mais je ne sais pas trop pourquoi ..... (avec ou sans les cast en Node*)
        if (this->value==value)
            return this;
        else if(value > this->value && this->right!=nullptr)
            return (this->right->find(value));
        else if (value<this->value && this->left!=nullptr)
            return (this->left->find(value));

        return nullptr;

    }
};

Node* createNode(int value) {
	return new BinarySearchTree(value);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
	BinarySearchTree bst;
	w = new BinarySearchTreeWindow(bst);
	w->show();

	return a.exec();
}
