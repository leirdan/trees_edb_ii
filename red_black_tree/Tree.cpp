#include "Tree.hpp"

#include <iostream>

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    destroy_tree(root);
}

void Tree::insert(int key) {
    Node *z = new Node(key);
    Node *y = nullptr;
    Node *x = root;
    while (x != nullptr) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = nullptr;
    z->right = nullptr;
    z->color = true;
    insert_fixup(z);
}

void Tree::destroy_tree(Node *x) {
    if (x != nullptr) {
        destroy_tree(x->left);
        destroy_tree(x->right);
        delete x;
    }
}

void Tree::insert_fixup(Node *z) {
    while (z->parent != nullptr && z->parent->color == true) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y != nullptr && y->color == true) {
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = false;
                z->parent->parent->color = true;
                right_rotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y != nullptr && y->color == true) {
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = false;
                z->parent->parent->color = true;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->color = false;
}

void Tree::remove(int key) {
    Node *z = search(key);
    if (z == nullptr) {
        return;
    }
    Node *y = z;
    bool y_original_color = y->color;
    Node *x;
    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr) {
                x->parent = y;
            }
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == false) {
        remove_fixup(x);
    }
    delete z;
}

void Tree::remove_fixup(Node *x) {
    while (x != root && x->color == false) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == true) {
                w->color = false;
                x->parent->color = true;
                left_rotate(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || w->left->color == false) && (w->right == nullptr || w->right->color == false)) {
                w->color = true;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == false) {
                    if (w->left != nullptr) {
                        w->left->color = false;
                    }
                    w->color = true;
                    right_rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = false;
                if (w->right != nullptr) {
                    w->right->color = false;
                }
                left_rotate(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == true) {
                w->color = false;
                x->parent->color = true;
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if ((w->right == nullptr || w->right->color == false) && (w->left == nullptr || w->left->color == false)) {
                w->color = true;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == false) {
                    if (w->right != nullptr) {
                        w->right->color = false;
                    }
                    w->color = true;
                    left_rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = false;
                if (w->left != nullptr) {
                    w->left->color = false;
                }
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = false;
}

Node *Tree::search(int key) {
    Node *x = root;
    while (x != nullptr && x->key != key) {
        if (key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

void Tree::print() {
    print(root, 0);
}

void Tree::left_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Tree::right_rotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void Tree::transplant(Node *u, Node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

Node *Tree::minimum(Node *x) {
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

void Tree::print(Node *x, int level) {
    if (x != nullptr) {
        print(x->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "    ";
        }
        std::cout << x->key << std::endl;
        print(x->left, level + 1);
    }
}
