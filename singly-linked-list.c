#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {// ���Ḯ��Ʈ ����ü Node
	int key;
	struct Node* link; //���� ��带 ����ų �ڱ����� ����ü ������ link
} listNode; //��Ī listNode

typedef struct Head { //���Ḯ��Ʈ ����ü head, ���� ������ ����
	struct Node* first; //  Node�� ����ų ����ü ������first
}headNode; //��Ī headNode

/* �Լ� ����Ʈ */
headNode* initialize(headNode* h); //����� ����,�����޸��Ҵ�
int freeList(headNode* h); //����� �����޸� ����
int insertFirst(headNode* h, int key); //���Ḯ��Ʈ ó����ġ ����߰�
int insertNode(headNode* h, int key);  //���Ḯ��Ʈ �� �Էµ� key���� ū �� �տ� ����߰�
int insertLast(headNode* h, int key);  //���Ḯ��Ʈ ������ ��ġ�� ����߰�
int deleteFirst(headNode* h); //���Ḯ��Ʈ ù ��� ����
int deleteNode(headNode* h, int key); //�˻��� �����ִ� ��� ����
int deleteLast(headNode* h); // ������ ��� ����
int invertList(headNode* h); // ���Ḯ��Ʈ �Ųٷ� ������
void printList(headNode* h); // ���Ḯ��Ʈ ���

int main()
{
	printf("[----- [����] [2019038029] -----]\n");
	char command; //��� �Է¹��� command
	int key; //����Ʈ�� ���� ���� key
	headNode* headnode=NULL; //head ����ü ������ headnode 
	headnode = initialize(headnode); //z �Է¾��� �ٷ� ��带 �ǵ鶧 ���� ����
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) { //������� �Է¿� ���� ��� ����
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

//����� �����޸��Ҵ�
headNode* initialize(headNode* h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

//�����Ҵ� ���� �Լ�
int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	   headNode�� �����Ǿ�� ��. */
	listNode* p = h->first;//������ ��� ����ü������ 1  
	listNode* prev = NULL; //������ ��� ����ü������ 2 
	while(p != NULL) { //p��ü�� NULL�϶����� �ݺ�
		prev = p;      //prev�� p�� ����
		p = p->link;   //����Ű�� �������� �ٲ���
		free(prev);    //�����ص� prev��ġ �����޸� ����
	}
	free(h);  //����� �޸� ����
	return 0; //�Լ�����
}

//list ó���� key�� ���� ����ϳ��� �߰�
int insertFirst(headNode* h, int key) {  
	//���� �߰��� ��� ������ �����Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;       //�Է��� �� ��忡 �־���
	node->link = h->first; //���� ���� ��尡 ����Ű����� ����Ŵ
	//����ִ� ����Ʈ�� ��� NULL����Ŵ 
	h->first = node;       //���� ��带 ����Ŵ
	return 0; //�Լ�����
}

// ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(headNode* h, int key) {
	//���� �߰��� ��� ������ �����Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;   //�Է��� �� ��忡 �־���
	node->link = NULL; //�ӽ÷� NULL ����Ű���� ��/������ ����� ���� �ֱ⶧����

	//ù ��� �����϶�
	if (h->first==NULL){
		h->first=node; //����尡 ��带 ����Ű���ϰ�
		return 0;      //�Լ�����
	}

	//�߰��� ����� ���� �����ִ� ������ ������ �۰ų� ������
	listNode* searchN = h->first;  //�˻��� ����Ʈ ����ü ������
	listNode* lastN = h->first;    //�˻��ϸ�searchN �Ѿ�� ���� ������ �����س��� ����ü ������

	//searchN�� �������� �Ѿ�鼭 searchN ������ ������(NULL)�϶����� �ݺ�
	while (searchN!=NULL){        
		if(key <=searchN->key){    // �ִ°��� �����ִ� ����Ʈ ������ ���� �� ������
			if(h->first==searchN){ // ����Ʈ ù��尪���� �ִ°��� ������ = h->first = node�� �Ǿ��� ��
				h->first = node;      //����� ��,
				node->link = searchN; //ã�� ��� ������ node ����
			}
			else{ //��������ġ�� �ƴ����� ���� ����Ʈ ������ �����ٴ� ���� ���
				node->link = searchN; //ã�Ƴ� ���� �� ū ��� ��,
				lastN->link = node;   //������ִ� ������� �ڷ� node ����
			}
			return 0;// �Լ�����
		}
		lastN=searchN; //�������� �Ѿ���� searchN�� ������ lastN�� ����
		searchN=searchN->link;	//searchN�� �������� �Ѿ
	}
	//�߰��� ����� ���� �����ִ� ��� ������ ������ Ŭ �� �������� �־���
	lastN->link = node; //��������Ʈ�� ������ ������ node�� ����
	return 0;
}

//list�� �ǵڿ� key�� ���� ����ϳ��� �߰� 
int insertLast(headNode* h, int key) {
	//���� �߰��� ��� ������ �����Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;   //�Է��� �� ��忡 �־���
	node->link = NULL; //������ ��ġ�� ����̹Ƿ� NULL ����Ŵ

	//ù ��� �����϶�
	if (h->first==NULL){
		h->first=node; //����尡 ��带 ����Ű���ϰ�
		return 0;      //�Լ�����
	}
	//�ƴ� �� = ����Ʈ ������ ��ġ���� ã�Ƽ� �߰��� ��� ���� 
	listNode* n = h->first;  //�˻��� ����Ʈ ����ü �����Ϳ� ��尡 ����Ű�� �� ����
	while(n->link != NULL) { //n�� ���� ���� = NULL �϶����� �ݺ�,n�� ������ ����϶� ����
		n = n->link; //���� ��� ����Ŵ
	}
	n->link = node;  //����Ʈ ������ ��尡 �߰��� ��� ����Ű�� ��
	return 0;        //�Լ�����
}

//list�� ù��° ��� ����
int deleteFirst(headNode* h) {
	if (h->first == NULL) {      //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* p = h->first; //�����޸� ������ ���� ����ü ������ p
	h->first = h->first->link; //ù���� ��尡 ����Ű�� ���� ����尡 ����Ű������
	free(p); //p�� ����Ű�� ��ġ�� ������ ������ ��� ����� ���� �޸� ����
	return 0;
}

//list���� key�� ���� ��� ����
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) {      //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* searchN = h->first;  //�˻��� ����Ʈ ����ü ������
	listNode* lastN = NULL;    //�˻��ϸ�searchN �Ѿ�� ���� ������ �����س��� ����ü ������
	
	while(searchN!= NULL) { //�Ѿ �����ü = NULL �϶����� �ݺ�-��������嵵 �˻��ؾߵ�
		if (key==searchN->key){  //�Է��� Ű���� ã�� ����� Ű���� ���
			//����Ʈ�� ù��° ��带 ������ ���
			if (searchN==h->first){ 
				h->first=searchN->link; //������ ������ ��尡 ����Ű������ ����Ŵ
			}
			// �׿��� ���
			else{
				lastN->link=searchN->link; //������ ����� �������� ������ ��尡 ����Ű������ ����Ŵ
			}
			free(searchN); //������ ���(ã�� searchN) ���� �޸� ����
			return 0;
		}
		lastN=searchN; //�������� �Ѿ���� searchN�� ������ lastN�� ����
		searchN = searchN->link;      //searchN�� �������� �Ѿ
	} 
	// ã�� key���� ���� ��尡 ������ 
	printf("Your key is not in the list\n"); //�ȳ��� ���
	return 0; //�Լ�����
}

//list�� ������ ��� ����
int deleteLast(headNode* h) {
	if (h->first == NULL) {      //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* searchN = h->first;  //�˻��� ����Ʈ ����ü ������
	listNode* lastN = h->first;    //�˻��ϸ�searchN �Ѿ�� ���� ������ �����س��� ����ü ������
	
	if (searchN->link== NULL){ //����Ʈ ��尡 �ϳ��ۿ� ���� ��(����� ����)
		h->first = NULL;       //��� ���� NULL ����Ŵ
		free(searchN);		   //searchN�� ����Ű�� ��ġ�� ������ ������ ��� ����� ���� �޸� ����
	}

	while(searchN->link!= NULL) { //searchN�� ���� ���� = NULL �϶����� �ݺ�,searchN�� ������ ����϶� ����
		lastN=searchN; //�������� �Ѿ���� searchN�� ������ lastN�� ����
		searchN = searchN->link;      //searchN�� �������� �Ѿ
	} 
	free(searchN);    //�̵��� ������ ��� �� searchN�� ����Ű�� ��ġ ���� �޸� ����
	lastN->link=NULL; // ������ִ� �� �� ��带 ������ ���� ó��
	return 0; //�Լ�����
}

//����Ʈ�� ��ũ�� �������� �� ��ġ
int invertList(headNode* h) {
	if (h->first == NULL) {      //�� ����Ʈ�� �������� �ٲ� ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	//����ü ������ 3�� ����� ����Ʈ ������
	listNode *lead  = h->first; //���� �̵��ϴ� ����ü ������ 
	listNode *middle = NULL; 
	listNode *trail = NULL;

	while(lead!=NULL){ //lead �����ü�� = NULL �϶����� �ݺ� 
		trail=middle;    //trail �� middle�� �̵� -> ù�������� �ǹ̾���
		middle=lead;     //middle�� lead�� �̵�
		lead=lead->link; //lead�� �������� �̵��ϰ�
		middle->link=trail;  //middle�� trail�� ����Ŵ
	}
	//�Ųٷ� NULL�� ���� ������ ����Ʈ�� ��� ��� ����
	h->first=middle;
	return 0; //�Լ�����
}

//����Ʈ ���
void printList(headNode* h) {
	int i = 0; 
	listNode* p; //����Ʈ�� �̵��ϸ� ����ҿ뵵�� ����Ʈ ������ p
	printf("\n---PRINT\n");
	if(h == NULL) { //����Ʈ�� ����ִ� ���� ������
		printf("Nothing to print....\n");
		return; // �Լ�����
	}
	p = h->first; //��尡 ����Ű�� ����Ʈ ù��� �ּ� �־���

	while(p != NULL) { // ����Ʈ�� �������� ����ų �� ����
		printf("[ [%d]=%d ] ", i, p->key); //i�� ����Ʈ�� key�� ���
		p = p->link;  //���� ����Ʈ�� �̵�
		i++;          //������ �ݺ����� �ѹ� �����ǰ� �ݺ��� �����
	}
	printf("  items = %d\n", i); //����Ʈ�� ��� ���� ���
}