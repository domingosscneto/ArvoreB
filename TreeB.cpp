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

#include "Treeb.h"
#include <sstream>
#include <iostream>
using namespace std;


// a função principl que insere o nó na arvore b
void BTree::insert(int k)
{
    // se a arvore estiver vazia
    if (root == nullptr)
    {
        // aloca memoria pra raiz
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // inserir chave
        root->n = 1;  // atualiza o numero de chaves na root
    }
    else // se a arvore não estiver vazia
    {
        // se a raiz esta cheia, a arvore cresce em altura "Bottom Up"
        if (root->n == 2 * t - 1)
        {
            // aloca memoria para novo nó
            BTreeNode* s = new BTreeNode(t, false);

            // faz a raiz filha da nova raiz
            s->C[0] = root;

            // separa a raiz pai e manda uma chave para a nova raiz filha
            s->splitChild(0, root);

            // a nova raiz tem duas filhas, decida em qual filha a chave sera inserida
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // trocar raiz
            root = s;
        }
        else  //se a raiz não estiver vazia, chame para inserir
            root->insertNonFull(k);
    }
}


void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    // chama a remoção pra raiz
    root->remove(k);

    // Se o node estiver vazio, faça de seu primeiro filho a raiz. Se tiver um filho, defina a raiz como nullptr
    if (root->n == 0)
    {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->C[0];

        // libera a raiz antiga
        delete tmp;
    }
    return;
}