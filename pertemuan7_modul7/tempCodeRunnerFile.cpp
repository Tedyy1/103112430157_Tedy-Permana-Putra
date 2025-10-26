#include <iostream>
#include <string>
using namespace std;

struct Queue {
    static const int MAX = 10;
    string data[MAX];
    int front, rear;
};

void createQueue(Queue &Q) {
    Q.front = -1;
    Q.rear = -1;
}

bool isEmpty(Queue Q) {
    return (Q.front == -1);
}

bool isFull(Queue Q) {
    return (Q.rear == Queue::MAX - 1);
}

void enqueue(Queue &Q, string value) {
    if (isFull(Q)) {
        cout << "Queue penuh.\n";
    } else {
        if (isEmpty(Q)) {
            Q.front = 0;
        }
        Q.rear++;
        Q.data[Q.rear] = value;
        cout << value << " dimasukkan ke queue.\n";
    }
}

void dequeue(Queue &Q, string &value) {
    if (isEmpty(Q)) {
        cout << "Queue kosong.\n";
    } else {
        value = Q.data[Q.front];
        cout << value << " dikeluarkan dari queue.\n";
        if (Q.front == Q.rear) {
            Q.front = Q.rear = -1; 
        } else {
            Q.front++;
        }
    }
}

void tampilQueue(Queue Q) {
    cout << "\nIsi Queue:\n";
    if (isEmpty(Q)) {
        cout << "Queue kosong.\n";
    } else {
        for (int i = Q.front; i <= Q.rear; i++) {
            cout << Q.data[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    Queue Q;
    createQueue(Q);

    enqueue(Q, "Andi");
    enqueue(Q, "Budi");
    enqueue(Q, "Citra");

    tampilQueue(Q);

    string keluar;
    dequeue(Q, keluar);

    tampilQueue(Q);

    return 0;
}
