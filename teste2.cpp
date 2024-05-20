#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef struct Node {
    int iPayLoad;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

// (1.a) Funções para lista circular duplamente encadeada

// Lista duplamente encadeada
Node* createNode(int);
void displayList(Node**);
void addElementList(Node**, int iPayLoad);
void deleteList(Node**);

// Lista circular duplamente encadeada 
void displayCicle(Node*);
void addElementCicle(Node**, int);
Node* createCiclebyArray(int*, int);
int avance(Node*);
int retroceda(Node*);

// (1.b) Funções para remover e deletar elementos da lista circular
void removeNodebyID(Node**, int);
void deleteCicle(Node**);


// (1.c) Função para intercalar duas listas circulares
Node* intercallCicles(Node*, Node*);


// (2) Função para verificar se uma lista encadeada possui um loop
bool thereCicle(Node**);


// (3) Função para criar uma lista circular representando um Ouroboros
Node* Ouroboros(int, int);


int main() {

    // Questão 1
    
    cout << "Exercício 1 - Framework e Playlist" << endl;
    // Criando uma Lista Cíclica por um Array
    int arr1[6] = {42, 13, 26, 90, 42, 37};
    Node* cicle1 = createCiclebyArray(arr1, 6);
    cout << "Ciclo 1: "; displayCicle(cicle1);
    
    // Retornar ID e avançar a Lista
    cout << "ID (Ciclo 1): " << avance(cicle1) << endl;
    cout << "Ciclo 1 - Após Avançar: "; displayCicle(cicle1);

    // Retornar ID e retroceder a Lista    
    cout << "ID (Ciclo 1): " << retroceda(cicle1) << endl;
    cout << "Ciclo 1 - Após Retroceder: "; displayCicle(cicle1);
    
    // Removendo nó
    cout << "Removendo Nó com ID 13: "; removeNodebyID(&cicle1, 13);
    // Intercalando Listas
    int arr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Node* cicle2 = createCiclebyArray(arr2, 10);
    cout << "Ciclo 2: "; displayCicle(cicle2);
    Node* cicle3 = intercallCicles(cicle1, cicle2);
    cout << "Ciclo 3: "; displayCicle(cicle3);

    // Deletando os Ciclos Originais
    deleteCicle(&cicle1);
    deleteCicle(&cicle2);
    
    cout << "========================" << endl;
    
    // Questão 2
    
    cout << "Exercício 2 - Are we in the loop?" << endl;

    // Criando Lista
    Node* list1 = createNode(0);
    for (int i = 1; i < 10; i++) {
        addElementList(&list1, i);
    }
    cout << "Lista 1: "; displayList(&list1);
    
    // Criando um Loop na Lista
    Node* current1;
    for (current1 = list1; current1->ptrNext != nullptr; current1 = current1->ptrNext);
    current1->ptrNext = list1;
    list1->ptrPrev = current1;
    
    // Verificando se há Loop
    cout << "Ciclo na Lista 1 (1 - Existe, 0 - Não existe): " << thereCicle(&list1) << endl;
    
    // Verificando se há Loop numa Lista sem Loop
    Node* list2 = createNode(0);
    for (int i = 1; i < 9; i++) {
        addElementList(&list2, i);
    }
    cout << "Lista 2: "; displayList(&list2);
    
    cout << "Ciclo na Lista 2 (1 - Existe, 0 - Não existe): " << thereCicle(&list2) << endl;
    
    // Verificando se há Loop numa Lista com Loop iniciando no meio
    // Criando a lista
    Node* list3 = createNode(0);
    for (int i = 1; i < 10; i++) {
        addElementList(&list3, i);
    }
    
    cout << "Lista 3: "; displayList(&list3);
    
    // Construindo o loop a partir da 3ª posição (valor 3)
    Node* current3;
    for (current3 = list3; current3->ptrNext != nullptr; current3 = current3->ptrNext);
    current3->ptrNext = list3->ptrNext->ptrNext;
    
    cout << "Ciclo na Lista 3 (1 - Existe, 0 - Não existe): " << thereCicle(&list3) << endl;
    
    cout << "========================" << endl;
    // Questão 3
    
    cout << "Exercício 3 - Helping an Ouroboros" << endl;
    
    // Validando Ouroboros Final = 320 -> (1, 2, 3)
    Node* cicle4 = Ouroboros(320, 3);
    cout << "OUROBOROS para (320, 3): "; displayCicle(cicle4);
    deleteCicle(&cicle4);
    
    // Validando Ouroboros Final = 12 -> (1, 1, 1)
    Node* cicle5 = Ouroboros(12, 3);
    cout << "OUROBOROS para (12, 3): "; displayCicle(cicle5);
    deleteCicle(&cicle5);
    
    // Validando Ouroboros Final = 1024 -> (3, 3, 3)
    Node* cicle6 = Ouroboros(1024, 3);
    cout << "OUROBOROS para (1024, 3): "; displayCicle(cicle6);
    deleteCicle(&cicle6);
    
    // Validando Ouroboros Final = 2048 -> (4, 4, 4)
    Node* cicle7 = Ouroboros(2048, 3);
    cout << "OUROBOROS para (2048, 3): "; displayCicle(cicle7);
    deleteCicle(&cicle7);
    
    cout << "========================" << endl;
    
    // Deletando os Ciclos
    //deleteCicle(&cicle1);
    //deleteCicle(&cicle2);
    deleteCicle(&cicle3);
    deleteCicle(&cicle4);
    deleteCicle(&cicle5);
    deleteCicle(&cicle6);
    deleteCicle(&cicle7);
    
    deleteList(&list1);
    deleteList(&list2);
    deleteList(&list3);
        
    return 0;
}

// Lista duplamente encadeada

Node* createNode(int iPayLoad) {
    Node* node = (Node*) malloc(sizeof(Node));
    
    if (node != nullptr) {
        node->iPayLoad = iPayLoad;
        node->ptrPrev = nullptr;
        node->ptrNext = nullptr;
    }
    return node;
}

void displayList(Node** head) {
    if (*head == nullptr) {
        cout << "Lista Vazia" << endl;
        return;
    }
    
    Node* current;
    for (current = *head; current->ptrNext != nullptr; current = current->ptrNext) {
        cout << current->iPayLoad << " ";
    }
    cout << current->iPayLoad << endl;
}

void addElementList(Node** head, int iPayLoad) {
    Node* temp = createNode(iPayLoad);
        
    if (*head == nullptr) {
        *head = temp;
    } else {
        Node* current;
        for (current = *head; current->ptrNext != nullptr; current = current->ptrNext);
        current->ptrNext = temp;
        temp->ptrPrev = current;
    }
}

// Algoritmo de Froyd (Tartaruga e Lebre)
bool thereCicle(Node** head) {
    Node* slow = *head;
    Node* fast = *head;
    
    while (fast != nullptr && fast->ptrNext != nullptr) {
        slow = slow->ptrNext;
        fast = fast->ptrNext->ptrNext;
        
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

void deleteList(Node** head) {
    Node* current = *head;
    Node* next;
    
    while (current != nullptr) {
        next = current->ptrNext;
        free(current);
        current = next;
    }
    
    *head = nullptr;
}

// Lista circular duplamente encadeada 

void displayCicle(Node* head) {
    if (head == nullptr) {
        cout << "Lista Vazia" << endl;
        return;
    }
    
    Node* current = head;
    do {
        cout << current->iPayLoad << " ";
        current = current->ptrNext;
    } while (current != head);
    cout << endl;
}

void addElementCicle(Node** head, int iPayLoad) {
    Node* temp = createNode(iPayLoad);
    
    if (*head == nullptr) {
        *head = temp;
        temp->ptrNext = temp;
        temp->ptrPrev = temp;
    } else {
        Node* tail = (*head)->ptrPrev;
        temp->ptrPrev = tail;
        temp->ptrNext = *head;
        tail->ptrNext = temp;
        (*head)->ptrPrev = temp;
    }
}

Node* createCiclebyArray(int* arr, int n) {
    Node* head = nullptr;
    for (int i = 0; i < n; i++) {
        addElementCicle(&head, arr[i]);
    }
    return head;
}

int avance(Node* head) {
    if (head == nullptr) {
        return -1;
    }
    int id = head->iPayLoad;
    head = head->ptrNext;
    return id;
}

int retroceda(Node* head) {
    if (head == nullptr) {
        return -1;
    }
    int id = head->iPayLoad;
    head = head->ptrPrev;
    return id;
}

void removeNodebyID(Node** head, int id) {
    if (head == nullptr || *head == nullptr) {
        return;
    }
    
    Node* current = *head;
    do {
        if (current->iPayLoad == id) {
            if (current->ptrNext == current) {
                free(current);
                *head = nullptr;
                return;
            }
            current->ptrPrev->ptrNext = current->ptrNext;
            current->ptrNext->ptrPrev = current->ptrPrev;
            
            if (current == *head) {
                *head = current->ptrNext;
            }
            free(current);
            return;
        }
        current = current->ptrNext;
    } while (current != *head);
}

void deleteCicle(Node** head) {
    if (head == nullptr || *head == nullptr) {
        return;
    }
    
    Node* current = *head;
    Node* next;
    
    do {
        next = current->ptrNext;
        free(current);
        current = next;
    } while (current != *head);
    
    *head = nullptr;
}

Node* intercallCicles(Node* head1, Node* head2) {
    if (head1 == nullptr && head2 == nullptr) {
        return createNode(0); // Retorna uma lista circular vazia
    }
    
    if (head1 == nullptr) {
        return head2;
    }
    
    if (head2 == nullptr) {
        return head1;
    }

    Node* result = nullptr;
    Node* current1 = head1;
    Node* current2 = head2;

    do {
        addElementCicle(&result, current1->iPayLoad);
        current1 = current1->ptrNext;
        if (current2 != head2) {
            addElementCicle(&result, current2->iPayLoad);
            current2 = current2->ptrNext;
        }
    } while (current1 != head1 || current2 != head2);

    return result;
}


Node* Ouroboros(int number, int digits) {
    Node* cicle = nullptr;
    int value = abs(number); // Garante que o número seja tratado como positivo
    
    for (int i = 0; i < digits; i++) {
        int digit = value % 10;
        value /= 10;
        value = digit * pow(10, digits - 1) + value / 10;
        addElementCicle(&cicle, value);
    }
    return cicle;
}
 
 