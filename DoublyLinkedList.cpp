#include <iostream>

// lista circular ( o último aponta o primeiro ) -> monitoria
// lista duplamente encadeada ( o nó apota para o anterior e posterior )
// ordenação 
// busca 



using std::cout;
using std::cin;
using std::string;
using std::endl;

typedef struct Node 
{
    int iPayload; 
    Node* ptrNext;
    Node* ptrPrev;
} Node;

// a estrutura lista não precisa, apena o ponteiro para o inicio
// a estrutura vai ser um ponteiro

Node* createNode(int);
void insertFront(Node**, int); // node** - recebe o endereço do nó
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void displayList(Node*); //node* - endereço do head (recebe um nó)
void deleteNode(Node**, Node*);

void insertBefore(Node**,Node*, int); //fazer
Node* searchNodebyValue(Node*, int); //fazer
void deleteNodebyValue(Node*, int); //fazer

int main()
{
    Node* head = nullptr; 
    
    //Node* Lista1
    //Node* head1 = nullptr; 

    displayList(head);
    
    cout << "TESTANDO FUNÇÕES DE INSERÇÃO" << endl;

    insertFront(&head, 1);
    displayList(head);
    insertEnd(&head, 2);
    insertEnd(&head, 9);
    insertEnd(&head, 2);
    displayList(head);

    insertFront(&head, 66);
    displayList(head);

    insertAfter(head, 78);
    displayList(head);

    insertAfter(head->ptrNext, 202);
    displayList(head);
    cout << "---------++---------" << endl;
    
    
    cout << "FUNÇÃO insertBefore"<<endl;
    insertBefore(&head, head, 1010);
    displayList(head);
    cout << "---------++---------" << endl;
    
    cout << "FUNÇÃO deleteNode"<<endl;
    deleteNode(&head, head->ptrNext);
    displayList(head);
    cout << "---------++---------" << endl;
    cout<<endl;

    cout << "FUNÇÃO searchNodebyValue" << endl;
    Node* node1 = searchNodebyValue(head, 10100);
    Node* node2 = searchNodebyValue(head, 2);

    insertAfter(node1, 78);
    displayList(head);
    cout << "---------++---------" << endl;
    
    deleteNode(&head, node1);
    displayList(head);
    cout << "---------++---------" << endl;
    
    insertBefore(&head,node2, 500);
    displayList(head);
    
    cout << "---------++---------" << endl;

    deleteNodebyValue(node2,8) ;
    cout << "---------++---------" << endl;

    deleteNodebyValue(node2,2) ;
    displayList(head);
    cout << "---------++---------" << endl;

    return 0;
}


Node* createNode(int iValue)
{
    Node* temp = (Node*)malloc(sizeof(Node)); //transforma um void* ppara um Node*
    temp->iPayload = iValue;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}

void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: não é possível realizar displayList" << endl;
        return;
    }
    
    // se receber um nó do meio, rejeito (um modo)
    if (node->ptrPrev != nullptr)
    {
        cout << "O elemento está no meio ou fim da lista: não é possível realizar displayList" << endl;
        return;
    }
    
    Node* temp = node;

    cout << "Payload: ";
    
    while (temp != nullptr)
    {
        cout <<  temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}


void insertFront(Node** head, int iValue)
{
    Node* newNode = createNode(iValue);
    
    //newNode->ptrPrev = nullptr
    
    if (*head !=nullptr)
    {
        (*head)->ptrPrev = newNode; 
        newNode->ptrNext = (*head);
        (*head) = newNode;
        return;
    }
    (*head) = newNode;
}

void insertEnd(Node** head, int iValue)
{
    Node* newNode = createNode(iValue);
    //newNode->ptrNext = nullptr

    if(*head == nullptr) 
    {
        (*head) = newNode; 
        return;
    }
    
    Node* temp = (*head);
    while (temp->ptrNext != nullptr)
    {
        temp = temp->ptrNext;
    }
    
    newNode->ptrPrev = temp; // newnode aponta para o fim da lista
    temp->ptrNext = newNode; // antigo ultimo elemento aponta para o novo nó
}

void insertAfter(Node* ptrLocation, int iPayload) //um caso particula do insertEnd
{
    if(ptrLocation == nullptr) //Node* ptrLocation - aponta para um nó
    {
        cout << "Location é NULL" << endl;
        return;
    }
    Node* newNode = createNode(iPayload);
    // Corrigir nó a ser inserido
    newNode->ptrNext = ptrLocation->ptrNext;
    newNode->ptrPrev = ptrLocation;
    
    // Corrigir o ponto de inserção 
    ptrLocation->ptrNext = newNode;
    
    if (newNode->ptrNext != nullptr) 
    {
        newNode->ptrNext->ptrPrev = newNode;
    }
}

void insertBefore(Node** head, Node* ptrLocation, int iPayload)
{
    
    if(ptrLocation == nullptr) //Node* ptrLocation - aponta para um nó
    {
        cout << "Location é NULL" << endl;
        return;
    }
    Node* newNode = createNode(iPayload);
    // Corrigir nó a ser inserido
    
    newNode->ptrNext = ptrLocation;
    newNode->ptrPrev = ptrLocation->ptrPrev;
    
    // Corrigir o ponto de inserção 
    ptrLocation->ptrPrev = newNode;
    
    if (newNode->ptrPrev != nullptr) 
    {
        newNode->ptrPrev->ptrNext = newNode;
    }
    else 
    {
        *head = newNode; // SE O ENDEREÇO PASSADO FOR O PRIMEITO ELEMENTO
    }
    
}

Node* searchNodebyValue(Node* node, int iPayload) 
{
    Node* temp = node;
    while (temp != nullptr && temp->iPayload != iPayload)
    {
        temp = temp->ptrNext;
        if (temp == nullptr)
        {
            cout << "Valor não encontrado" << endl;
            break;
        }
    }
    return temp;
}

void deleteNode(Node** head, Node* ptrDelete)
{
    if(*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Não foi possível remover" << endl;
        return;
    }
   //caso o ptrDelete seja o primeiro elemento
    if (*head == ptrDelete)
   {
       (*head) = ptrDelete->ptrNext;
   }
   
   //se o ptrDelete não for o ultimo
   
    if (ptrDelete->ptrNext != nullptr ) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;
    
   //se o ptrDelete não for o primeiro
    if (ptrDelete->ptrPrev != nullptr ) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;

    free(ptrDelete);
}

void deleteNodebyValue(Node* node, int iPayload) 
{
    Node* temp = node;
    while (temp != nullptr && temp->iPayload != iPayload)
    {
        temp = temp->ptrNext;
        if (temp == nullptr)
        {
            cout << "Valor nao encontrado para ser deletado" << endl;
            return;
        }
    }
       

   //se o temp não for o ultimo
    if (temp->ptrNext != nullptr ) temp->ptrNext->ptrPrev = temp->ptrPrev;
    
   //se o temp não for o primeiro
    if (temp->ptrPrev != nullptr ) temp->ptrPrev->ptrNext = temp->ptrNext;

    free(temp);
}

// EXERCÍCIO 1: Elaborar o método void insertBefore(Node*, int)
// EXERCÍCIO 2: Elaborar o método void deleteNodebyValue(Node*, int) 
//receber um valor e remove o nó com o valor
// EXERCÍCIO 3: Elaborar o método Node* searchNodebyValue(Node*, int) 
