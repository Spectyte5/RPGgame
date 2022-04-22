#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>
#include "Header.h"



    //Add new element at the end of the list
    void LinkedList::push_back(int newElement) {
        Node* newNode = new Node();
        newNode->data = newElement;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            newNode->next = head;
        }
        else {
            Node* temp = head;
            while (temp->next != head)
                temp = temp->next;
            temp->next = newNode;
            newNode->next = head;
        }
    }

    //Delete first node of the list
    void LinkedList::pop_front() {
        if (head != NULL) {
            if (head->next == head) {
                head = NULL;
            }
            else {
                Node* temp = head;
                Node* firstNode = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                head = head->next;
                temp->next = head;
                free(firstNode);
            }
        }
    }

    //display the content of the list
    void LinkedList::PrintList() {
        
        Node* temp = head;
        int node_cnt = 1;

        if (temp != NULL) {
            std::cout << "\nCurrent session history of battles: " <<std::endl;
            while (1) {

                std::cout << node_cnt << "." ;

                if (temp->data == 2) {
                    std::cout << " ESCAPE" << std::endl;
                }

                else if (temp->data == 1) {
                    std::cout << " WIN" << std::endl;
                }

                else {
                    std::cout << " LOSE" << std::endl;
                }
                node_cnt++;
                temp = temp->next;

                if (temp == head)
                    break;
            }
        }
    }



