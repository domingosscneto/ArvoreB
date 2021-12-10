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
#include "TreeNode.h"
#include "TreeB.h"
#include<iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "pt_BR");
    BTree t(3); // Grau da árvore B = 3

    t.insert(15);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);
    t.insert(60);
    t.insert(70);
    t.insert(44);
    t.insert(28);

    cout << "Traverse in order da arvore com os inserts na Arvore B : \n";
    t.traverseInOrder();
    cout << endl;
    cout << endl;

    cout << "Tenta remover 10 para testar a função : \n";
    t.remove(10);
    cout << endl;

    cout << "20 removido : \n";
    t.remove(20);
    t.traverseInOrder();
    cout << endl;

    cout << "50 removido :\n";
    t.remove(50);
    t.traverseInOrder();
    cout << endl;

    cout << "28 removido :\n";
    t.remove(28);
    t.traverseInOrder();
    cout << endl;



}