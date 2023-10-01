#include <iostream>

struct Node {
    int key;
    Node *left, *right;
};

Node* newNode(int key) {
    Node* node = new Node;
    node->key = key;
    node->left = node->right = nullptr;
    return node;
}

Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == nullptr) return root;

        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr)? root: rightRotate(root);
    }
    else {
        if (root->right == nullptr) return root;

        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == nullptr)? root: leftRotate(root);
    }
}

Node* insert(Node* root, int k) {
    if (root == nullptr) return newNode(k);

    root = splay(root, k);

    if (root->key == k) return root;

    Node* newnode = newNode(k);

    if (root->key > k) {
        newnode->right = root;
        newnode->left = root->left;
        root->left = nullptr;
    }
    else {
        newnode->left = root;
        newnode->right = root->right;
        root->right = nullptr;
    }

    return newnode;
}

Node* delete_key(Node* root, int key) {
    Node* temp;
    if (!root)
        return nullptr;

    root = splay(root, key);

    if (key != root->key)
        return root;

    if (!root->left) {
        temp = root;
        root = root->right;
    }
    else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }

    delete temp;
    return root;
}

void preOrder(Node* root) {
    if (root != nullptr) {
        std::cout<< root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node *root = newNode(100);
    root = insert(root, 50);
    root = insert(root, 200);
    root = insert(root, 40);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 25);

    std::cout << "Preorder traversal of the modified Splay tree is: \n";
    preOrder(root);

    root = delete_key(root, 40);
    std::cout << "\nPreorder traversal of the modified Splay tree is: \n";
    preOrder(root);

    return 0;
}
