#include <iostream>
#include <vector>

using namespace std;

template<class T>
struct Node{
	T value;
	Node<T>* left;
	Node<T>* right;

	Node(T _value){
		value = _value;
		left = NULL;
		right = NULL;
	}
};

template<class T>
class BST{
	private:
		Node<T>* root;
	public:
		BST(){
			root = NULL;
		}

		void insertHelper(Node<T>* &current, T value){
			if(current==NULL){ // We have reached bottom of the tree
				// Base case
				current = new Node<T>(value);
			}else{
				if(value<current->value){
					insertHelper(current->left, value); // going to the left
				}else if(value>current->value){
					insertHelper(current->right, value); // going to the right
				}
			}
		}

		void insert(T value){
			if(isEmpty()) root = new Node<T>(value);  // tree is empty
			else{
				// the tree is not empty
				insertHelper(root, value);
			}
		}

		bool hasHelper(Node<T>* current, T value){
			bool f = false;
			if(current!=NULL){
				if(current->value == value) return true; // match found
				else{
					if(value<current->value){ // search in the left side
						f = hasHelper(current->left, value);
					}else{ // search in the right side
						f = hasHelper(current->right, value);
					}
				}
			}
			return f;
		}

		bool has(T value){
			// return true if the value is in the tree, else return false
			return hasHelper(root, value);
		}

		bool isEmpty(){
			return (root==NULL);
		}

		void prefix(Node<T>* current){
			if(current!=NULL){
				cout<<current->value<<" ";
				prefix(current->left);
				prefix(current->right);
			}
		}

		void infix(Node<T>* current){
			if(current!=NULL){
				infix(current->left);
				cout<<current->value<<" ";
				infix(current->right);
			}
		}

		void postfix(Node<T>* current){
			if(current!=NULL){
				postfix(current->left);
				postfix(current->right);
				cout<<current->value<<" ";
			}
		}

		void display(int order=0){
			if(order==0) prefix(root);
			else if(order==1) infix(root);
			else if(order==2) postfix(root);
			cout<<endl;
		}

		bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		    //cout<<current->value<<endl;
            if (!current) return false;
            if (current->value == value) {

                //if(current)cout<<"ff"<<current->value<<endl;
                if (current->left == NULL || current->right == NULL) {

                    Node<T>* temp = current->left;
                    if (current->right) temp = current->right;


                    if (parent) {

                        if (parent->left == current) {
                            parent->left = temp;

                        } else {
                            parent->right = temp;
                        }
                    } else {
                        root = temp;
                    }


                } else {
                    Node<T>* validSubs = current->right;
                    while (validSubs->left) {
                        validSubs = validSubs->left;
                    }
                    T temp = current->value;
                    current->value = validSubs->value;
                    validSubs->value = temp;
                    return deleteValueHelper(current, current->right, temp);
                }
                //if(current)cout<<"ff"<<current->value<<endl;
                delete current;
                //cout<<parent->left->value<<endl;
                return true;
            }
            if(current->value > value)
                return deleteValueHelper(current, current->left, value);
            return deleteValueHelper(current, current->right, value);
       }


       bool deleteValue(T value) {
            Node<T>* parent=NULL;
            return deleteValueHelper(parent, root, value);
       }
};


int main(){
	BST<int> firstTree; // We are creating the binary tree, it is empty
	//BST<string> tree2;
	//BST<double> tree3;
	//BST<char> tree4;
	//BST<Student> tree5;
	//BST<List<int>> tree6;
	//List<BST<int>> tree7;
	int nums[] = {10, 7, 5, 6, 12, 11, 15};
	int c = 7;

	for(int i=0;i<c;i++){
		firstTree.insert(nums[i]);
	}

	firstTree.display(1);
	firstTree.deleteValue(15);
    firstTree.display(1);
    firstTree.deleteValue(5);
    firstTree.display(1);
    firstTree.deleteValue(10);
    firstTree.display(1);
    firstTree.deleteValue(7);
    firstTree.display(1);
	cout<<firstTree.has(999999)<<endl;

	return 0;
}
