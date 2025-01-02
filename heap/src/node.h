#ifndef NODE_H
#define NODE_H
struct node
{
  int key;

  node()
  {
    this->key = 0;
  }

  node(int key)
  {
    this->key = key;
  }
};

#endif