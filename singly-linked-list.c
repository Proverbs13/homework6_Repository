#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {// 연결리스트 구조체 Node
	int key;
	struct Node* link; //다음 노드를 가리킬 자기참고 구조체 포인터 link
} listNode; //별칭 listNode

typedef struct Head { //연결리스트 구조체 head, 내부 내용은 없음
	struct Node* first; //  Node를 가리킬 구조체 포인터first
}headNode; //별칭 headNode

/* 함수 리스트 */
headNode* initialize(headNode* h); //헤드노드 생성,동적메모리할당
int freeList(headNode* h); //헤드노드 동적메모리 해제
int insertFirst(headNode* h, int key); //연결리스트 처음위치 노드추가
int insertNode(headNode* h, int key);  //연결리스트 내 입력된 key보다 큰 값 앞에 노드추가
int insertLast(headNode* h, int key);  //연결리스트 마지막 위치에 노드추가
int deleteFirst(headNode* h); //연결리스트 첫 노드 삭제
int deleteNode(headNode* h, int key); //검색한 값이있는 노드 삭제
int deleteLast(headNode* h); // 마지막 노드 삭제
int invertList(headNode* h); // 연결리스트 거꾸로 뒤집기
void printList(headNode* h); // 연결리스트 출력

int main()
{
	printf("[----- [이찬] [2019038029] -----]\n");
	char command; //명령 입력받을 command
	int key; //리스트에 넣을 내용 key
	headNode* headnode=NULL; //head 구조체 포인터 headnode 
	headnode = initialize(headnode); //z 입력없이 바로 노드를 건들때 오류 방지
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

		switch(command) { //사용자의 입력에 따른 명령 실행
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

//헤드노드 동적메모리할당
headNode* initialize(headNode* h) {
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

//동적할당 해제 함수
int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	   headNode도 해제되어야 함. */
	listNode* p = h->first;//해제용 노드 구조체포인터 1  
	listNode* prev = NULL; //해제용 노드 구조체포인터 2 
	while(p != NULL) { //p자체가 NULL일때까지 반복
		prev = p;      //prev에 p값 저장
		p = p->link;   //가리키는 다음노드로 바꿔줌
		free(prev);    //저장해둔 prev위치 동적메모리 해제
	}
	free(h);  //헤드노드 메모리 해제
	return 0; //함수종료
}

//list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key) {  
	//내용 추가할 노드 생성후 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;       //입력한 값 노드에 넣어줌
	node->link = h->first; //노드는 원래 헤드가 가리키던노드 가리킴
	//비어있던 리스트일 경우 NULL가리킴 
	h->first = node;       //헤드는 노드를 가리킴
	return 0; //함수종료
}

// 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {
	//내용 추가할 노드 생성후 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;   //입력한 값 노드에 넣어줌
	node->link = NULL; //임시로 NULL 가리키도록 함/마지막 노드일 수도 있기때문에

	//첫 노드 생성일때
	if (h->first==NULL){
		h->first=node; //헤드노드가 노드를 가리키게하고
		return 0;      //함수종료
	}

	//추가할 노드의 값이 원래있던 노드들의 값보다 작거나 같을때
	listNode* searchN = h->first;  //검색용 리스트 구조체 포인터
	listNode* lastN = h->first;    //검색하며searchN 넘어갈때 이전 연결을 저장해놓을 구조체 포인터

	//searchN가 다음으로 넘어가면서 searchN 자제가 마지막(NULL)일때까지 반복
	while (searchN!=NULL){        
		if(key <=searchN->key){    // 넣는값이 원래있던 리스트 값보다 작을 때 노드삽입
			if(h->first==searchN){ // 리스트 첫노드값보다 넣는값이 작을때 = h->first = node가 되야할 때
				h->first = node;      //헤드노드 뒤,
				node->link = searchN; //찾은 노드 앞으로 node 연결
			}
			else{ //헤드다음위치는 아니지만 원래 리스트 노드들의 값보다는 작을 경우
				node->link = searchN; //찾아낸 값이 더 큰 노드 앞,
				lastN->link = node;   //저장되있던 이전노드 뒤로 node 연결
			}
			return 0;// 함수종료
		}
		lastN=searchN; //다음으로 넘어가기전 searchN의 연결경로 lastN에 저장
		searchN=searchN->link;	//searchN은 다음으로 넘어감
	}
	//추가할 노드의 값이 원래있던 모든 노드들의 값보다 클 때 마지막에 넣어줌
	lastN->link = node; //원래리스트의 마지막 연결을 node로 해줌
	return 0;
}

//list에 맨뒤에 key에 대한 노드하나를 추가 
int insertLast(headNode* h, int key) {
	//내용 추가할 노드 생성후 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;   //입력한 값 노드에 넣어줌
	node->link = NULL; //마지막 위치의 노드이므로 NULL 가리킴

	//첫 노드 생성일때
	if (h->first==NULL){
		h->first=node; //헤드노드가 노드를 가리키게하고
		return 0;      //함수종료
	}
	//아닐 때 = 리스트 마지막 위치까지 찾아서 추가할 노드 연결 
	listNode* n = h->first;  //검색용 리스트 구조체 포인터에 헤드가 가리키는 것 연결
	while(n->link != NULL) { //n의 다음 연결 = NULL 일때까지 반복,n이 마지막 노드일때 까지
		n = n->link; //다음 노드 가리킴
	}
	n->link = node;  //리스트 마지막 노드가 추가할 노드 가리키게 함
	return 0;        //함수종료
}

//list의 첫번째 노드 삭제
int deleteFirst(headNode* h) {
	if (h->first == NULL) {      //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* p = h->first; //동적메모리 해제를 위한 구조체 포인터 p
	h->first = h->first->link; //첫번쨰 노드가 가리키던 것을 헤드노드가 가리키도록함
	free(p); //p가 가리키는 위치의 연결이 끊어진 대상 노드의 동적 메모리 해제
	return 0;
}

//list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) {      //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* searchN = h->first;  //검색용 리스트 구조체 포인터
	listNode* lastN = NULL;    //검색하며searchN 넘어갈때 이전 연결을 저장해놓을 구조체 포인터
	
	while(searchN!= NULL) { //넘어간 노드자체 = NULL 일때까지 반복-마지막노드도 검사해야됨
		if (key==searchN->key){  //입력한 키값이 찾은 노드의 키값인 경우
			//리스트의 첫번째 노드를 삭제할 경우
			if (searchN==h->first){ 
				h->first=searchN->link; //헤드노드는 삭제할 노드가 가리키던것을 가리킴
			}
			// 그외의 경우
			else{
				lastN->link=searchN->link; //삭제할 노드의 이전노드는 삭제할 노드가 가리키던것을 가리킴
			}
			free(searchN); //삭제할 노드(찾은 searchN) 동적 메모리 해제
			return 0;
		}
		lastN=searchN; //다음으로 넘어가기전 searchN의 연결경로 lastN에 저장
		searchN = searchN->link;      //searchN은 다음으로 넘어감
	} 
	// 찾는 key값을 가진 노드가 없을때 
	printf("Your key is not in the list\n"); //안내문 출력
	return 0; //함수종료
}

//list의 마지막 노드 삭제
int deleteLast(headNode* h) {
	if (h->first == NULL) {      //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* searchN = h->first;  //검색용 리스트 구조체 포인터
	listNode* lastN = h->first;    //검색하며searchN 넘어갈때 이전 연결을 저장해놓을 구조체 포인터
	
	if (searchN->link== NULL){ //리스트 노드가 하나밖에 없을 때(헤드노드 제외)
		h->first = NULL;       //헤드 노드는 NULL 가리킴
		free(searchN);		   //searchN이 가리키는 위치의 연결이 끊어진 대상 노드의 동적 메모리 해제
	}

	while(searchN->link!= NULL) { //searchN의 다음 연결 = NULL 일때까지 반복,searchN이 마지막 노드일때 까지
		lastN=searchN; //다음으로 넘어가기전 searchN의 연결경로 lastN에 저장
		searchN = searchN->link;      //searchN은 다음으로 넘어감
	} 
	free(searchN);    //이동한 마지막 노드 즉 searchN이 가리키는 위치 동적 메모리 해제
	lastN->link=NULL; // 저장되있던 그 전 노드를 마지막 노드로 처리
	return 0; //함수종료
}

//리스트의 링크를 역순으로 재 배치
int invertList(headNode* h) {
	if (h->first == NULL) {      //빈 리스트라 역순으로 바꿀 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	//구조체 포인터 3개 사용해 리스트 뒤집기
	listNode *lead  = h->first; //먼저 이동하는 구조체 포인터 
	listNode *middle = NULL; 
	listNode *trail = NULL;

	while(lead!=NULL){ //lead 노드자체가 = NULL 일때까지 반복 
		trail=middle;    //trail 이 middle로 이동 -> 첫루프에선 의미없음
		middle=lead;     //middle이 lead로 이동
		lead=lead->link; //lead는 다음으로 이동하고
		middle->link=trail;  //middle은 trail을 가리킴
	}
	//거꾸로 NULL을 향해 뒤집은 리스트에 헤드 노드 연결
	h->first=middle;
	return 0; //함수종료
}

//리스트 출력
void printList(headNode* h) {
	int i = 0; 
	listNode* p; //리스트를 이동하며 출력할용도의 리스트 포인터 p
	printf("\n---PRINT\n");
	if(h == NULL) { //리스트에 들어있는 것이 없으면
		printf("Nothing to print....\n");
		return; // 함수종료
	}
	p = h->first; //헤드가 가리키는 리스트 첫노드 주소 넣어줌

	while(p != NULL) { // 리스트가 마지막을 가리킬 때 까지
		printf("[ [%d]=%d ] ", i, p->key); //i번 리스트에 key값 출력
		p = p->link;  //다음 리스트로 이동
		i++;          //마지막 반복에서 한번 증가되고 반복문 종료됨
	}
	printf("  items = %d\n", i); //리스트의 노드 개수 출력
}