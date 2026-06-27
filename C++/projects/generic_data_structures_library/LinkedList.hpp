#include <cstddef>
#include <stdexcept>

// TODO: Copy constructor, Copy assignment, Move constructor, Move assignment

template<typename T>
class LinkedList {
        public:
                LinkedList()
                        : head(nullptr)
                        , tail(nullptr)
                {}

                LinkedList(const LinkedList& source) {
                        Node* n  = new Node;
                        while(source) {
                                // write rest of copy constructor
                        }
                }

                ~LinkedList() {
                        while(!empty()) {
                                pop_front();
                        }
                }

                void push_back(T value) {
                        if(head == nullptr && tail == nullptr) {
                                Node* n = new Node;
                                n->data = value;
                                n->next = nullptr;
                                head = n;
                                tail = n;
                        }
                        else {
                                Node* n = new Node;
                                n->data = value;
                                n->next = nullptr;
                                tail->next = n;
                                tail = n;
                        }
                }

                void pop_front() {
                        if(head == nullptr && tail == nullptr) throw std::out_of_range("No elements to pop");
                        else {
                                if(head->next == nullptr) {
                                        Node* temp = head;
                                        head = nullptr;
                                        tail = nullptr;
                                        delete temp;
                                }
                                else {
                                        Node* temp = head;
                                        head = temp->next;
                                        delete temp;
                                }
                        }
                }

                T& front() {
                        return head->data;
                }

                const T& front() const {
                        return head->data;
                }

                size_t size() {
                        if(head == nullptr && tail == nullptr) return 0;
                        size_t count = 1;
                        Node* i = head;
                        while(i->next != nullptr) {
                                i = i->next;
                                count++;
                        }
                        return count;
                }

                bool empty() {
                        return head == nullptr && tail == nullptr;
                }

        private:
                struct Node {
                        T data;
                        Node* next;
                };
                Node* head;
                Node* tail;
};
