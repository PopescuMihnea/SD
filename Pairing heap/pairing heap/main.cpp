#include <iostream>
#include <vector>
using namespace std;

class Node
{
    int inf;
    Node* left_child;
    Node* right_sibling;
    Node * prev;
public:
    Node(int x=0,Node* child=nullptr,Node* sibling=nullptr):inf(x),left_child(child),right_sibling(sibling),prev(nullptr)
    {
        //cout<<"Node\n";
    }
    Node (Node &n)
    {
        this->inf=n.inf;
        this->left_child=n.left_child;
        this->right_sibling=n.right_sibling;
    }
    ~Node()
    {
        //cout<<"~Node\n";
        delete this->left_child;
        delete this->right_sibling;
    }
    int get_inf() const;
    void set_left_child(Node *);
    Node * get_left_child() const;
    void set_right_sibling(Node *);
    Node * get_right_sibling() const;
    void set_prev(Node *);
    Node * get_prev() const;
    friend ostream & operator<<(ostream &,const Node&);
};

int Node::get_inf() const
{
    return this->inf;
}
void Node::set_left_child(Node *n)
{
    this->left_child=n;
}
Node * Node::get_left_child() const
{
    return this->left_child;
}
void Node::set_right_sibling(Node *n)
{
    this->right_sibling=n;
}
Node * Node::get_right_sibling() const
{
    return this->right_sibling;
}

void Node::set_prev(Node * n)
{
    this->prev=n;
}

Node * Node::get_prev() const
{
    return this->prev;
}

ostream & operator<<(ostream &out,const Node &n)
{
    out<<n.get_inf();
    return out;
}

class pairing_heap
{
    Node* root;
public:
    pairing_heap():root(nullptr)
    {

    }
    pairing_heap(int x):root(new Node(x))
    {
        //cout<<"pairing heap\n";
    }
    ~pairing_heap()
    {
        // cout<<"~pairing heap\n";
        delete root;
    }
    int get_min();
    Node * get_root() const;
    void merge(pairing_heap&);
    void insert(const int );
    void build(const vector<int>);
    void delete_min();
    void show_heap(Node *) const;
};

int pairing_heap::get_min()
{
    return this->root->get_inf();
}

Node * pairing_heap::get_root() const
{
    return this->root;
}

void pairing_heap::merge(pairing_heap & aux)
{
    if (this->root==nullptr)
        this->root=aux.root;
    else if (aux.root==nullptr)
        return;
    else if (this->root->get_inf()<aux.root->get_inf())
    {
        if (this->root->get_left_child()!=nullptr)
            this->root->get_left_child()->set_prev(aux.root);
        aux.root->set_right_sibling(this->root->get_left_child());
        this->root->set_left_child(aux.root);
    }
    else
    {
        if (aux.root->get_left_child()!=nullptr)
            aux.root->get_left_child()->set_prev(this->root);
        this->root->set_right_sibling(aux.root->get_left_child());
        aux.root->set_left_child(this->root);
        this->root=aux.root;
    }
    aux.root=nullptr;
}

void pairing_heap::insert(const int x)
{
    pairing_heap aux(x);
    this->merge(aux);
}

void pairing_heap::build(const vector<int> x)
{
    for (auto &i:x)
        this->insert(i);
}

void pairing_heap::delete_min()
{
    if (this->root==nullptr)
        return;
    Node *a=root->get_left_child(),*b=nullptr;
    root->set_left_child(nullptr);
    delete root;
    root=nullptr;
    Node * last_root=root;
    while (a!=nullptr)
    {
        Node *aux;
        b=a->get_right_sibling();
        if (b!=nullptr)
        {
            aux=b->get_right_sibling();
            cout<<*a<<" "<<*b<<"\n";
            if (a->get_inf()<b->get_inf())
            {
                if (last_root==nullptr)
                    this->root=a;
                else
                {
                    last_root->set_right_sibling(a);
                    a->set_prev(last_root);
                }
                last_root=a;
                b->set_right_sibling(a->get_left_child());
                if (a->get_left_child()!=nullptr)
                    a->get_left_child()->set_prev(b);
                a->set_left_child(b);
                b->set_prev(nullptr);
                a->set_right_sibling(nullptr);
            }
            else
            {
                if (last_root==nullptr)
                {
                    this->root=b;
                    b->set_prev(nullptr);
                }
                else
                {
                    last_root->set_right_sibling(b);
                    b->set_prev(last_root);
                }
                last_root=b;
                a->set_right_sibling(b->get_left_child());
                if (b->get_left_child()!=nullptr)
                    b->get_left_child()->set_prev(a);
                b->set_left_child(a);
                a->set_prev(nullptr);
                b->set_right_sibling(nullptr);
            }
        }
        else
        {
            if (last_root!=nullptr)
                last_root->set_right_sibling(a);
            a->set_prev(last_root);
            last_root=a;
            cout<<*a<<"\n";
            break;
        }
        a=aux;
    }
    if (last_root!=nullptr)
    {
        cout<<"\n\n\n";
    cout<<*last_root<<" ";
         a=last_root->get_prev();
    while (a!=nullptr)
    {
        Node *aux;
        aux=a->get_prev();
        cout<<*a<<" ";
     if (a->get_inf()<last_root->get_inf())
     {
         last_root->set_right_sibling(a->get_left_child());
         last_root->set_prev(nullptr);
         if (a->get_left_child()!=nullptr)
            a->get_left_child()->set_prev(last_root);
        a->set_left_child(last_root);
        a->set_right_sibling(nullptr);
        last_root=a;
     }
     else
     {
         a->set_right_sibling(last_root->get_left_child());
         a->set_prev(nullptr);
         if (last_root->get_left_child()!=nullptr)
            last_root->get_left_child()->set_prev(a);
        last_root->set_left_child(a);
     }
     a=aux;
    }
    root=last_root;
    }
}

void pairing_heap::show_heap(Node * n=nullptr) const
{
    if (n==nullptr)
    {
        n=this->root;
        cout<<"Radacina: ";
    }
    if (n!=nullptr)
    {
        cout<<*n<<"\n";
    if (n->get_prev()!=nullptr)
    {
        cout<<"Precedentul lui "<<*n<<" este: "<<n->get_prev()->get_inf()<<"\n";
    }
    if (n->get_right_sibling()!=nullptr)
    {
        cout<<"Fratele din dreapta al lui "<<*n<<" : ";
        show_heap(n->get_right_sibling());
    }
    if (n->get_left_child()!=nullptr)
    {
        cout<<"copilul din stanga al lui "<<*n<<" : ";
        show_heap(n->get_left_child());
    }
    }
    else
    {
        cout<<"null";
    }
}


int main()
{
    pairing_heap x;
    x.insert(3);
    x.insert(10);
    x.insert(11);
    x.delete_min();
    x.show_heap();
    x.delete_min();
    x.show_heap();
     x.delete_min();
     x.show_heap();
}
