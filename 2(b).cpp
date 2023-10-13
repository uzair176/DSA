#include <iostream>
#include <conio.h>
using namespace std; 


class NodeDoubly {
	public:
    int data;
    NodeDoubly* next;
    NodeDoubly* prev;
    
    NodeDoubly(int data)
    {
    	this->next=NULL;
    	this->data=data;
    	this->prev=NULL;
    	
	}
};
void seek(NodeDoubly* head) {
    int targetData;
    std::cout << "Enter the value you want to seek: ";
    std::cin >> targetData;

    NodeDoubly* current = head;
    bool found = false;

    while (current != NULL) {
        if (current->data == targetData) {
            found = true;
            std::cout << "Value " << targetData << " found in the list." << std::endl;
            return;
        }
        current = current->next;
    }

    if (!found) {
        std::cout << "Value " << targetData << " not found in the list." << std::endl;
    }
}


void reverseAndPrint(NodeDoubly* &head) {
    if (head == NULL) {
        std::cout << "List is empty. Nothing to reverse and print." << std::endl;
        return;
    }

    NodeDoubly* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    std::cout << "Reversed List:" << std::endl;

    while (current != NULL) {
        std::cout << (current->next ? "<-" : "") << current->data << " -> ";
        current = current->prev;
    }

    std::cout << "NULL" << std::endl;
}

void deleteSpecificDataNode(NodeDoubly*& head) {
    int targetData;
    std::cout << "Enter the value you want to delete: ";
    std::cin >> targetData;

    if (head == NULL) {
        std::cout << "List is empty. Cannot delete from an empty list." << std::endl;
        return;
    }

    if (head->data == targetData) {
        NodeDoubly* temp = head;
        head = head->next;

        if (head != NULL) {
            head->prev = NULL;
        }

        delete temp;
        return;
    }

    NodeDoubly* current = head;

    while (current != NULL) {
        if (current->data == targetData) {
            current->prev->next = current->next;

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            delete current;
            return;
        }

        current = current->next;
    }

    std::cout << "Value " << targetData << " not found in the list." << std::endl;
}


void deleteAtEnd(NodeDoubly*& head) {
    if (head == NULL) {
        std::cout << "List is empty. Cannot delete from an empty list." << std::endl;
        return;
    }

    if (head->next == NULL) {
        // If there's only one node in the list, delete it and set head to NULL.
        delete head;
        head = NULL;
        return;
    }

    NodeDoubly* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    delete current->next;
    current->next = NULL;
}

void deleteAtHead(NodeDoubly*& head) {
    if (head == NULL) {
        std::cout << "List is empty. Cannot delete from an empty list." << std::endl;
        return;
    }

    NodeDoubly* temp = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    delete temp;
}

void insertAtSpecificDataNode(NodeDoubly*& head, int dataToInsert) {
    int dataAfter;
    std::cout << "Enter the value after which you want to insert: ";
    std::cin >> dataAfter;

    NodeDoubly* new_node = new NodeDoubly(dataToInsert);
    NodeDoubly* current = head;

    while (current != NULL) {
        if (current->data == dataAfter) {
            new_node->prev = current;
            new_node->next = current->next;

            if (current->next != NULL) {
                current->next->prev = new_node;
            }

            current->next = new_node;
            return;
        }

        current = current->next;
    }
}


void insertAtEnd(NodeDoubly*& head, int data) {
    NodeDoubly* new_node = new NodeDoubly(data);
    NodeDoubly* current = head;

    if (head == NULL) {
        head = new_node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

void Display(NodeDoubly* head) {
    NodeDoubly* current = head;

    while (current != NULL) {
        std::cout << (current->prev ? "<-" : "") << current->data << " -> ";
        current = current->next;
    }

    std::cout << "NULL" << std::endl;
}

void insertAtHead(NodeDoubly*& head, int data) {
    NodeDoubly* new_node = new NodeDoubly(data);
    if (head ==NULL) {
        head = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

int main() {
    
    int operation;
    NodeDoubly*            singlyList=NULL;
    NodeDoubly* dhead = NULL; // head of singly linked list
    
        do {
            cout << "\n\nWhich operation you want to perform:" << endl;
            cout << "1: Insertion" << endl;
            cout << "2: Deletion" << endl;
            cout << "3: Display" << endl;
            cout << "4: Reverse" << endl;
            cout << "5: Seek" << endl;
            cout << "6: Back to Previous Menu" << endl;
            cout << "Enter your choice: ";
            cin >> operation;

            if (operation == 6) {
                break;  // exit
            }

            // Handle Insertion
            if (operation == 1) {
                int insertionOption;

                do {
                    cout << "\n\nInsertion Options:" << endl;
                    cout << "1: Insert at the beginning" << endl;
                    cout << "2: Insert at the end" << endl;
                    cout << "3: Insert at a specific data node" << endl;
                    cout << "4: Back to Previous Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> insertionOption;

                    if (insertionOption == 4) {
                        break;  // Return to the previous menu
                    }
                    
                    	switch (insertionOption) {
                        case 1:
                            {   int data;
                            cout<<"Enter the Value to insert:";
                            cin>>data;
							    insertAtHead(dhead,data);
							    cout<<"inserted successfully!\n";
							    Display(dhead);
							    char c;
							    cout<<"Press any key to continue...";
							    getch();
                            	break;
							}
                        case 2:
                            {   int data;
                            cout<<"Enter the Value to insert:";
                            cin>>data;
							    insertAtEnd(dhead,data);
							    cout<<"inserted successfully!\n";
							    Display(dhead);
							    char c;
							    cout<<"Press any key to continue...";
							    getch();
                            	break;
							}
                        case 3:
                            { int data;
                            cout<<"Enter the Value to insert:";
                            cin>>data;
							insertAtSpecificDataNode(dhead,data);
							    Display(dhead);
							    char c;
							    cout<<"\nPress any key to continue...";
							    getch();
                            	break;
							}
                        default:
                            {
                            	cout << "Invalid option. Please try again." << endl;
                            	break;
							}
                    }
					
					
			

                } while (true);
            } 
			if (operation == 2) {
                int deletionOption;

                do {
                    cout << "\n\nDeletion Options:" << endl;
                    cout << "1: Delete at the beginning" << endl;
                    cout << "2: Delete at the end" << endl;
                    cout << "3: Delete at a specific data node" << endl;
                    cout << "4: Back to Previous Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> deletionOption;

                    if (deletionOption == 4) {
                        break;  // Return to the previous menu
                    }
                    
                    	switch (deletionOption) {
                        case 1:
                            {   
							    deleteAtHead(dhead);
							    Display(dhead);
							    char c;
							    cout<<"Press any key to continue...";
							    getch();
                            	break;
							}
                        case 2:
                            {   
							    deleteAtEnd(dhead);
							    Display(dhead);
							    char c;
							    cout<<"Press any key to continue...";
							    getch();
                            	break;
							}
                        case 3:
                            { deleteSpecificDataNode(dhead);
							    Display(dhead);
							    char c;
							    cout<<"\nPress any key to continue...";
							    getch();
                            	break;
							}
                        default:
                            {
                            	cout << "Invalid option. Please try again." << endl;
                            	break;
							}
                    }
				
					
			

                } while (true);
            } 
        if(operation==3)
        {
        	Display(dhead);
		}
		if(operation==4)
		{
			reverseAndPrint(dhead);
		}
        if(operation==5)  
		{
			seek(dhead);
		 } 
        } while (true);
   
    return 0;
}
