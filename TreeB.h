//Eric Felipeli César Dias Pereira - 41911296
//Domingos Soares do Carmo Neto - 32032889
//
//referencias
//https://www.youtube.com/watch?v=aZjYr87r1b8
//https://www.youtube.com/watch?v=hMGhs63sCO0
//https://www.programiz.com/dsa/b-tree
//https://www.tutorialspoint.com/cplusplus-program-to-implement-b-tree
//https://www.programiz.com/dsa/tree-traversal
//https://www.tutorialspoint.com/cplusplus-program-to-perform-preorder-recursive-traversal-of-a-given-binary-tree

#ifndef __TREEB_H__
#define __TREEB_H__

#include "TreeNode.h"

// Nó da Btree
class BTree
{
    BTreeNode* root; // Ponteiro para a raiz do nó
    int t;  // grau mínimo
public:

    // Construtor (Inicializa a árvore vazia)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void traverseInOrder()
    {
        if (root != NULL) root->traverseInOrder();
    }

    // Função para procurar uma chave na árvore
    BTreeNode* search(int k)
    {
        return (root == NULL) ? NULL : root->Busca(k);
    }

    // Função principal que insere uma nova chave na B-Tree
    void insert(int k);

    // Função principal que remove uma chave na B-Tree
    void remove(int k);

};
#endif