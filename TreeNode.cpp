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
#include <iostream>
using namespace std;

//Cria o nó da árvore, aloca a memória e armazena seu grau
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    //copia o grau e o minimo numero de filhos da arvore
    t = t1;
    leaf = leaf1;

    //Aloca memoria para o maior numero possivel de chaves e filhos
    keys = new int[2 * t - 1];
    C = new BTreeNode * [2 * t];

    // Inicia o numero de chaves em 0
    n = 0;
}

// Função que retorna a posição da chave maior igual ao K
int BTreeNode::BuscaChave(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

// Função para a remoção de chave
void BTreeNode::remove(int k)
{
    int idx = BuscaChave(k);

    // verifica se a chave a ser removida está presente no nó
    if (idx < n && keys[idx] == k)
    {


        if (leaf)
            removefolha(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {


        if (leaf)
        {
            cout << "a chave " << k << " não existe na arvore \n";
            return;
        }

        // A chave a ser removida está presente na subárvore
        // A"flag" indica se a chave está presente na subárvore com o ultimo filho do nó
        bool flag = ((idx == n) ? true : false);

        // Se a chave tiver menos que t chaves onde ela supostamente deveria existir, preenche o filho
        if (C[idx]->n < t)
            Preencher(idx);

        // Se o ultimo filho tiver sido juntado, ele deve ter sido juntado com o filho anterior 
        // e então recursa no filho (idx-1)th. 
        //Caso contrario, recursa no filho (idx)th que agora tem pelo menos t chaves. 
        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

// Função para remover chave da folha a partir de um index 
void BTreeNode::removefolha(int idx)
{


    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    // reduz o numero de chaves na folha
    n--;

    return;
}

// Função para remover chave de não folha
void BTreeNode::removeFromNonLeaf(int idx)
{

    int k = keys[idx];


    if (C[idx]->n >= t)
    {
        int pred = getpredecessor(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }


    else if (C[idx + 1]->n >= t)
    {
        int succ = getsucessor(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    }


    else
    {
        juntar(idx);
        C[idx]->remove(k);
    }
    return;
}

// Função para identificar o predecessesor da chave
int BTreeNode::getpredecessor(int idx)
{
    // percorra a folha para a direita
    BTreeNode* cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    // pega a ultima chave dela
    return cur->keys[cur->n - 1];
}

int BTreeNode::getsucessor(int idx)
{

    // percorra a folha para a esquerda
    BTreeNode* cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Retorne a primeira chave da folha
    return cur->keys[0];
}

// Função para preencher o node quando ele fica com t-1 chaves
void BTreeNode::Preencher(int idx)
{


    if (idx != 0 && C[idx - 1]->n >= t)
        borrowLeftChild(idx);


    else if (idx != n && C[idx + 1]->n >= t)
        borrowRightChild(idx);

    //Merge com a proxima Child node
    else
    {
        if (idx != n)
            juntar(idx);
        else
            juntar(idx - 1);
    }
    return;
}

// Função para pegar uma chave emprestada do no filho anterior
void BTreeNode::borrowLeftChild(int idx)
{

    BTreeNode* child = C[idx];
    BTreeNode* sibling = C[idx - 1];


    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];


    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];


    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// Função para pegar uma chave emprestada do proximo nó filho

void BTreeNode::borrowRightChild(int idx)
{

    BTreeNode* child = C[idx];
    BTreeNode* irmao = C[idx + 1];


    child->keys[(child->n)] = keys[idx];


    if (!(child->leaf))
        child->C[(child->n) + 1] = irmao->C[0];


    keys[idx] = irmao->keys[0];


    for (int i = 1; i < irmao->n; ++i)
        irmao->keys[i - 1] = irmao->keys[i];


    if (!irmao->leaf)
    {
        for (int i = 1; i <= irmao->n; ++i)
            irmao->C[i - 1] = irmao->C[i];
    }


    child->n += 1;
    irmao->n -= 1;

    return;
}

// função para juntar nós
void BTreeNode::juntar(int idx)
{
    BTreeNode* child = C[idx];
    BTreeNode* irmao = C[idx + 1];

    child->keys[t - 1] = keys[idx];

    // copia as chaves
    for (int i = 0; i < irmao->n; ++i)
        child->keys[i + t] = irmao->keys[i];

    // copia os ponteiros
    if (!child->leaf)
    {
        for (int i = 0; i <= irmao->n; ++i)
            child->C[i + t] = irmao->C[i];
    }

    // Move as chaves
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    // atualiza o numero de chaves
    child->n += irmao->n + 1;
    n--;

    delete(irmao);
    return;
}

//função para inserir quando o nó não esta vazio
void BTreeNode::insertNonFull(int k)
{

    int i = n - 1;

    // verifica se é leaf
    if (leaf == true)
    {

        // 1. acha a localização em que a nova chava sera inserida
        // 2. move as outras chaves do nó, para frente
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insere chave na posição encontrada
        keys[i + 1] = k;
        n = n + 1;
    }
    else //leaf?
    {
        // encontra o nó filho em que a chave sera inserida
        while (i >= 0 && keys[i] > k)
            i--;

        // esta cheio?
        if (C[i + 1]->n == 2 * t - 1)
        {
            // se estiver, divide
            splitChild(i + 1, C[i + 1]);

            // depois da divisão, escolha qual dos dois irá pra uma nova chave raiz
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// função para dividir o nó filho só pode ser chamada quando o mesmo estiver cheio
void BTreeNode::splitChild(int i, BTreeNode* y)
{
    //Cria um novo nó que ira armazenar a chave de y
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copia as chaves de z até y
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copia a ultima filha de t para z até y
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    // Reduz o numeor de chaves
    y->n = t - 1;


    // cria espaço para novo filho
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // linka o node com o novo filho
    C[i + 1] = z;

    //seleciona a chave de y que será movida
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // copia a chave do meio de y para este nó
    keys[i] = y->keys[t - 1];

    // aumenta o key count de n
    n = n + 1;
}

// Função tranverserinorder
void BTreeNode::traverseInOrder()
{
    // Existem n chaves e n+1 filhos, comece a travessar pelas chaves n e primeiro filho n
    int i;
    for (i = 0; i < n; i++)
    {
        // se isso não for uma folha. antes de printar a chave, atravesse a subarvore que tem o filho como raiz
        if (leaf == false)
            C[i]->traverseInOrder();
        cout << " " << keys[i];
    }

    // printe a subarvore em que sua raiz é o ultimo filho
    if (leaf == false)
        C[i]->traverseInOrder();
}

// Função para buscar chave na subarvore
BTreeNode* BTreeNode::Busca(int k)
{
    // encontre a primeira chave igual ou maior que k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // Se o resultado for == k, retorne k
    if (keys[i] == k)
        return this;

    // se a chave for uma folha, retorne que é folha
    if (leaf == true)
        return NULL;

    // vá até o filho apropriado
    return C[i]->Busca(k);
}