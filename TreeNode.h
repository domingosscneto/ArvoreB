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
#ifndef __TREENODE_H__
#define __TREENODE_H__

#include<string>

class BTreeNode
{
    int* keys;  // Lista de chaves
    int t;      // grau máximo (define o limite pro número de chaves)
    BTreeNode** C; // Uma matrix de ponteiro para os filhos
    int n;     // Número atual de chaves
    bool leaf; // É verdadeiro(true) quando o node for uma folha(leaf). Caso contrario é falso

public:

    BTreeNode(int _t, bool _leaf);   // Construtor

    // Função para atravessar todos os nós da subárvore 
    void traverseInOrder();

    // Função para pesquisar uma chave na subárvore
    BTreeNode* Busca(int k);   // retorna NULL se k não estiver presente

    // Função que retorna o index da primeira chave que for maior ou igual a k
    int BuscaChave(int k);

    //Função para inserir uma nova chave na subárvore desse nó. O nó não pode estar vazio quando essa função for chamada.
    void insertNonFull(int k);

    //Função para dividir filho y do nó. i é o index de y na matrix filha C[]. O filho y deve estar cheio quando essa função for chamada.
    void splitChild(int i, BTreeNode* y);

    // Função para remover uma chave k na subárvore.
    void remove(int k);

    // Função para remover uma chave presente na posição idx no nó folha.
    void removefolha(int idx);

    // Função para remover uma chave presente na posição idx no nó não folha.
    void removeFromNonLeaf(int idx);

    // Função para pegar a chave anterior, quando a chave estiver presente na posição idx no nó.
    int getpredecessor(int idx);

    // Função para pegar a chave posterior, quando a chave estiver presente na posição idx no nó.
    int getsucessor(int idx);

    // Função para preencher o nó filho presente na posição idx na matrix C[], se esse filho possuir menos que t-1(grau maximo -1) chaves
    void Preencher(int idx);

    // Função que pega emprestado uma chave de C[idx-1]-th 
    void borrowLeftChild(int idx);

    // Função que pega emprestado uma chave de C[idx+1]-th 
    void borrowRightChild(int idx);

    // Função para fundir o filho idx-th do nó com o filho (idx+1)th
    void juntar(int idx);

    // Transforma BTree "amiga" disso para conseguirmos acessar membros privados dessa classenas funções Btree
    friend class BTree;
};
#endif __TREENODE_H__