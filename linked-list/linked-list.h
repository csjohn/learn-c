typedef struct linkedListNode {
  char data[40];
  struct linkedListNode *next;
} linkedListNode;

linkedListNode* createLinkedListNode(char *data);

void deleteLinkedListNode(linkedListNode** head, int index);

void insertLinkedListNode(linkedListNode** head, linkedListNode* newNode, int index);

void appendLinkedListNode(linkedListNode** head, linkedListNode* newNode);

void displayLinkedList(linkedListNode* head);
