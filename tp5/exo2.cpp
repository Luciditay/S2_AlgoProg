#include "lib/mainwindow.h"
#include <QApplication>
#include <QString>
#include <time.h>
#include <stdio.h>
#include <string>
#include <math.h>

#include "lib/tp5.h"

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int hash(string key)
{
    int a = 3;
    int keyHash = 0;

    for(int i=0; i<key.size(); i++)
    {
        keyHash+= (int) key.at(i) * pow(a, i);
    }

    return keyHash;
}

struct BinarySearchTree : public BinaryTree
{

    string key;
    int key_hash;

    int value;

    BinarySearchTree* left;
    BinarySearchTree* right;

    virtual ~BinarySearchTree() {}
    virtual void setValue(QVariant value) override {this->value = value.toInt();};
    virtual QString toString() const override
        {return QString("%1:\n%2").arg(QString::fromStdString(key)).arg(value);}
    const Node* leftChild() const override {return left;};
    const Node* rightChild() const override {return right;};

    BinarySearchTree(string key, int value)
    {
        this->key = key;
        this->value = value;
        this->key_hash = hash(key);

        this->left = this->right = nullptr;
    }

    void insertNode(BinarySearchTree* node)
    {
        if(!this->left)
        {
            this->left = node;
        }
        else
        {
            this->right = node;
        }
    }

    void insertNode(string key, int value)
    {
        this->insertNode(new BinarySearchTree(key, value));
    }
};

struct Map
{
    Map() {
        this->root = nullptr;
    }

    void insert(string key, int value)
    {
        if (!this->root)
            this->root = new BinarySearchTree(key, value);
        else
            this->root->insertNode(key, value);
    }

    int get(string key)
    {
        int value = 0;

        int hashKey = hash(key);
        BinarySearchTree* tmpTree = this->root;

        while(tmpTree!=NULL)
        {
            if (tmpTree->key == key)
            {
                return value = tmpTree->value;
            }
            else if (tmpTree->key_hash > hashKey )
            {
                tmpTree = tmpTree->left;
            }
            else
            {
                tmpTree = tmpTree->right;
            }
        }
        return 0;
    }

    BinarySearchTree* root;
};


int main(int argc, char *argv[])
{
	Map map;
    map.insert("Laurinne", 9);
    map.insert("Luc", 5);
    map.insert("Alois", 14);
    map.insert("Paul", 10);
    map.insert("Bojack", 15);
    map.insert("Mr.PeanutB", 20);

    QApplication a(argc, argv);
    MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow(map.root);
    w->show();


    printf("map[\"Laurinne\"]=%d\n", map.get("Laurinne"));
    printf("map[\"Paul\"]=%d\n", map.get("Paul"));
    w->resize(750,750);
    return a.exec();
}
