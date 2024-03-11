#include<iostream>
using namespace std;

struct linked {
	int data;
	struct linked* nextNode;
};


//링크드 리스트 클래스 생성 안에 함수들만 정의해놈
class linkedlist {
private:
	linked* head;
	linked* tail;
public:
	linkedlist() {
		head = NULL;
		tail = NULL;
	}

	//첫번째에 추가 함수 선언?
	void addFrintNode(int n);
	//마지막에 추가 함수
	void addNode(int n);
	//node 삽입 함수
	void insertNode(linked* prevNode, int n);
	//node에 삭제 함수
	void deleteNode(linked* prevNode);

	//첫번째 노드 가져오기
	linked* getHead() {
		return head;
	}

	//출력함수
	void display(linked* head);
};

//왜 함수를 어기써쓰는데 위에서 정의하지
// :: 기호이용해서 linkedlist클래스의 addFrintNode함수 여기서 정의한데
void linkedlist::addFrintNode(int n) {
	linked* temp = new linked; //머지 이건 - 동적할당 변수
	temp->data = n;//temp 데이터 n으로 설정
	
	//linkedlist가 비어있으면
	if (head == NULL) {
		// 첫 node는 temp
		head = temp;// 이러면 내가 추가함수(n)호출한 값 이 head즉 처음에되는듯
		// 마지막 node도? temp
		tail = temp;
	}
	//데이터 있는 경우
	else {
		//temp의 nextnode는 head
		temp->nextNode = head;//지금 해드를 새로만든 리스트의 연결노드에 박음
		//그리고 새로운 값을 head(리스트의 맨 처음)에 박음
		head = temp;
	}
}


//마지막의 node추가
void linkedlist::addNode(int n) {
	linked* temp = new linked;

	//새로운 리스트에 값 넣음(처음리스트(head)는아님)
	temp->data = n;
	//temp의 연결노드는 null
	temp->nextNode = NULL;

	//linkedlist가 비어있으면
	if (head == NULL) {
		//처음거 방금 우리값으로 만든거 삽입
		head = temp;
		//마지막도 temp느네? 아무것도 없으면 당연히 값넣야되서 else가 마지막삽입경우
		tail = temp;
	}
	//있으면
	else {
		//현재 마지막 node의 nextNode는 temp
		tail->nextNode = temp;
		//마지막 node는 temp
		tail = temp;
	}

}

//node삽입
void linkedlist::insertNode(linked* prevNode, int n) {
	linked* temp = new linked;
	//temp의 데이터는 n
	temp->data = n;
	
	//temp의 nextnode 저장
	// 삽입할 앞 node의 nextNode 를 temp의 nextNode에 저장
	temp->nextNode = prevNode->nextNode;
	//temp삽입
	//temp앞의 node의 nextNode를 temp로 저장
	prevNode->nextNode = temp;
}

//node삭제
void linkedlist::deleteNode(linked* prevNode) {
	//삭제할 node를 temp에 저장
	//삭제할 node의 1단계 전 node의 nextNode
	linked* temp = prevNode->nextNode;

	//삭제할 node를 제외
	//삭제할 node의 nextnode를 1단계 전 node의 nextNode에 저장
	prevNode->nextNode = temp->nextNode;
	
	//temp삭제
	delete temp;
}

//출력
void linkedlist::display(linked* head) {
	if (head == NULL) {
		cout << "\n";
	}
	else {
		cout << head->data << " ";
		display(head->nextNode);//재귀식으로 다음거 들어감 NULL까지
	}
	//cout << "endl";
}

int main() {

	//클래스 적용자? 생성
	linkedlist a;
	//1추가
	a.addNode(1);
	//2추가
	a.addNode(2);
	//3추가
	a.addNode(3);
	
	//display
	cout << "1,2,3을 linkedlist에 추가\n";
	a.display(a.getHead());//getHead내장함수?

	//0을 제일앞에 추가
	a.addFrintNode(0);

	//1을 네번쨰에 추가
	a.insertNode(a.getHead()->nextNode->nextNode, 1);
	cout << "0을 첫번쨰에 추가, 1을 네번쨰에 추가\n";
	a.display(a.getHead());

	//세번쨰 노드 삭제
	a.deleteNode(a.getHead()->nextNode);

	//display
	cout << "세번째 노드를 삭제\n";
	a.display(a.getHead());
	return 0;
}
