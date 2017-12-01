#include <iostream>
#include <stack>

using namespace std;
template<class T>

class btree_node {
private:
	T _value;
	btree_node<T>* _left;
	btree_node<T>* _right;
	btree_node<T>* _up;
public:
	btree_node() {
		_value = _left = _right = _up = NULL;
	}
	btree_node(const T& value) {
		_left = _right = _up = NULL;
		_value = value;
	}
	btree_node(const T& value, btree_node<T> *left, btree_node<T> *right) {
		_left = left;
		_right = right;
		_value = value;
		left->up = this;
		right->up = this;
	}
	~btree_node() {
		/*
		 if(_left)
		 delete _left;
		 if(_right)
		 delete _right;
		 */
	}
	T value() const {
		return _value;
	}
	;
	btree_node<T>* left() const{
		return _left;
	}
	btree_node<T>* right() const{
		return _right;
	}
	btree_node<T>* up() {
		return _up;
	}
	void set_left(btree_node<T>* left) {
		_left = left;
	}
	void set_right(btree_node<T>* right) {
		_right = right;
	}
	bool is_leaf() {
		return (_left == NULL) && (_right == NULL);
	}
	btree_node<T>& operator=(const btree_node<T>& node) {
		_value = node.value();
		_left = node.left();
		_right = node.right();
	}
};

template<class T>
class btree {
private:
	btree_node<T>* _root;
public:

	btree() {
		_root = NULL;
	}
	btree(btree_node<T>* root) {
		_root = root;
	}
	~btree() {
		/*
		 if(_root!=NULL)
		 delete _root;
		 */
	}
	bool is_empty() const {
		return _root == NULL;
	}

	btree_node<T>* root() {
		return _root;
	}
	btree_node<T>* up(btree_node<T> *cur) {
	}
	btree_node<T>* left(btree_node<T> *cur) {
		return cur->left();
	}
	btree_node<T>* right(btree_node<T> *cur) {
		return cur->right();
	}

	void create_tree(const T& value, btree<T>& left, btree<T>& right) {
		_root->set_value(value);
		_root->set_left(left.root());
		_root->set_right(right.root());
	}
	void set(btree_node<T> *cur, btree_node<T> *node) {
		if (cur->value() < node->value()) {
			if (right(cur) == NULL) {
				cur->set_right(node);
			} else {
				set(right(cur), node);
			}
		} else {
			if (left(cur) == NULL) {
				cur->set_left(node);
			} else {
				set(left(cur), node);
			}
		}
	}
	btree_node<T>* find_up(btree_node<T>* root, btree_node<T> *node) {
		if (root == node) {
			return NULL;
		} else {
			if (root->left() == node || root->right() == node) {
				return root;
			} else {
				int val = node->value();
				if (root->value() < val) {
					return find_up(root->left(), node);
				} else {
					return find_up(root->right(), node);
				}
			}
		}
	}
	string prefix() {
		return prefix(_root);
	}
	string prefix(btree_node<T> *root) {
		string res;
		if (root != NULL) {
			cout << root->value();
			cout << " ";
			res = root->value();
			res += " ";
			if (root->left() != NULL) {
				res += prefix(root->left());
			}
			if (root->right() != NULL) {
				res += prefix(root->right());
			}
		}
		return res;
	}
	string infix() {
		return infix(_root);
	}
	string infix(btree_node<T> *root) {
		string res;
		if (root != NULL) {
			if (root->left() != NULL) {
				res += infix(root->left());
			}
			res += root->value();
			res += " ";
			cout << root->value() << " ";
			if (root->right() != NULL) {
				res += infix(root->right());
			}
		}
		return res;
	}
	string postfix(btree_node<T> *root) {
		string res;
		if (root != NULL) {
			if (root->left() != NULL) {
				res += postfix(root->left());
			}
			if (root->right() != NULL) {
				res += postfix(root->right());
			}
			res += root->value();
			res += " ";
			cout << root->value() << " ";
		}
		return res;
	}
	string postfix() {
		return postfix(_root);
	}
	void level(btree_node<T> *root);
	void delete_btree(btree_node<T> *root) {
	}
	btree_node<T> *min() {
		return min(_root);
	}
	btree_node<T> *min(btree_node<T> *cur) {
		if (cur->left() == NULL)
			return cur;
		else
			return min(cur->left());
	}
};

int main() {
	/*
	 btree_node<char> root('a');
	 btree_node<char> b('b');
	 btree_node<char> c('c');
	 btree_node<char> d('d');
	 btree_node<char> e('e');
	 btree_node<char> f('f');
	 btree_node<char> g('g');
	 btree_node<char> h('h');
	 btree_node<char> i('i');
	 root.set_left(&b);
	 b.set_left(&d);
	 b.set_right(&e);
	 e.set_left(&g);
	 root.set_right(&c);
	 c.set_right(&f);
	 f.set_left(&h);
	 f.set_right(&i);

	 btree<char> tree(&root);
	 cout << tree.prefix();
	 cout << endl;
	 cout << tree.infix();
	 cout << endl;
	 cout << tree.postfix();
	 */

	btree_node<int> a(50);
	btree_node<int> b(10);
	btree_node<int> c(100);
	btree_node<int> d(1000);
	btree_node<int> e(10000);
	btree<int> tree(&a);
	tree.set(&a, &b);
	tree.set(&a, &c);
	tree.set(&a, &d);
	tree.set(&a, &e);

	tree.prefix();
	cout << endl;
	tree.infix();
	cout << endl;
	tree.postfix();
	cout << endl;
	cout << tree.min()->value() << endl;

	return 0;
}
