//Eric Felipeli C�sar Dias Pereira - 41911296
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
    int t;      // grau m�ximo (define o limite pro n�mero de chaves)
    BTreeNode** C; // Uma matrix de ponteiro para os filhos
    int n;     // N�mero atual de chaves
    bool leaf; // � verdadeiro(true) quando o node for uma folha(leaf). Caso contrario � falso

public:

    BTreeNode(int _t, bool _leaf);   // Construtor

    // Fun��o para atravessar todos os n�s da sub�rvore 
    void traverseInOrder();

    // Fun��o para pesquisar uma chave na sub�rvore
    BTreeNode* Busca(int k);   // retorna NULL se k n�o estiver presente

    // Fun��o que retorna o index da primeira chave que for maior ou igual a k
    int BuscaChave(int k);

    //Fun��o para inserir uma nova chave na sub�rvore desse n�. O n� n�o pode estar vazio quando essa fun��o for chamada.
    void insertNonFull(int k);

    //Fun��o para dividir filho y do n�. i � o index de y na matrix filha C[]. O filho y deve estar cheio quando essa fun��o for chamada.
    void splitChild(int i, BTreeNode* y);

    // Fun��o para remover uma chave k na sub�rvore.
    void remove(int k);

    // Fun��o para remover uma chave presente na posi��o idx no n� folha.
    void removefolha(int idx);

    // Fun��o para remover uma chave presente na posi��o idx no n� n�o folha.
    void removeFromNonLeaf(int idx);

    // Fun��o para pegar a chave anterior, quando a chave estiver presente na posi��o idx no n�.
    int getpredecessor(int idx);

    // Fun��o para pegar a chave posterior, quando a chave estiver presente na posi��o idx no n�.
    int getsucessor(int idx);

    // Fun��o para preencher o n� filho presente na posi��o idx na matrix C[], se esse filho possuir menos que t-1(grau maximo -1) chaves
    void Preencher(int idx);

    // Fun��o que pega emprestado uma chave de C[idx-1]-th 
    void borrowLeftChild(int idx);

    // Fun��o que pega emprestado uma chave de C[idx+1]-th 
    void borrowRightChild(int idx);

    // Fun��o para fundir o filho idx-th do n� com o filho (idx+1)th
    void juntar(int idx);

    // Transforma BTree "amiga" disso para conseguirmos acessar membros privados dessa classenas fun��es Btree
    friend class BTree;
};
#endif __TREENODE_H__