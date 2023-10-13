#include <iostream>
using namespace std;

class Node
{
	public:
		int data;
		Node* next;
		Node(int data)
		{
			this->data=data;
			this->next=NULL;
		}
};
//Print using while loop
void print(Node* &head)
{
Node* temp=head;
   cout<<"  Linked List is:\n  ";
	while(temp!=NULL)
	{
		cout<<temp->data<<" ";
		temp=temp->next;
	}
	cout<<endl;	
	
Node* ptr=head;
   //cout<<"Linked List is:\n";
   cout<<"   ****head address:**** "<<&head<<endl;
   cout<<"----------------------------------------------------\n";
   cout<<"   head content:"<<head<<endl;
   cout<<"----------------------------------------------------\n";
   cout<<"   ****ptr address:**** "<<&ptr<<endl;
   cout<<"----------------------------------------------------\n";
   cout<<"   ptr content:"<<ptr<<endl;
   cout<<"----------------------------------------------------\n";
   cout<<"   ptr->data: "<<ptr->data<<endl;
   cout<<"----------------------------------------------------\n";
   ptr=ptr->next;
	while(ptr!=NULL)
	{
		cout<<"   ptr: "<<ptr<<endl;
		cout<<"   ptr->next: "<<ptr->next<<endl;
		cout<<"   ptr->data: "<<ptr->data<<endl;
		cout<<"----------------------------------------------------\n";
		ptr=ptr->next;
	}
}
int main()
{
	Node* head=NULL;
	Node* node1=new Node(1);
	head=node1;
	Node* node2=new Node(2);
	node1->next=node2;
	Node* node3=new Node(20);
	node2->next=node3;
	Node* node4=new Node(30);
	node3->next=node4;

	
	print(head);
}
