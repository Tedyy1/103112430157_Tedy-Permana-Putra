#include <iostream>
#include <string>
using namespace std;

struct Akun {
    string username;
    string password;
};

struct ElmList {
    Akun info;
    ElmList *prev;
    ElmList *next;
};

typedef ElmList* address;

struct List {
    address first;
    address last;
};

void createList(List &L) {
    L.first = NULL;
    L.last = NULL;
}

address createNewElm(Akun akun) {
    address p = new ElmList;
    if (p != NULL) {
        p->info = akun;
        p->prev = NULL;
        p->next = NULL;
    }
    return p;
}

void insertLast(address p, List &L) {
    if (L.first == NULL) { 
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}

address findAkun(string username, List L) {
    address p = L.first;
    while (p != NULL) {
        if (p->info.username == username)
            return p;
        p = p->next;
    }
    return NULL;
}

void signUp(Akun akun, List &L) {
    if (findAkun(akun.username, L) != NULL) {
        cout << "Account has been registered." << endl;
    } else {
        address p = createNewElm(akun);
        insertLast(p, L);
        cout << "Account registered successfully." << endl;
    }
}

void deleteFirst(List &L, address &p) {
    if (L.first == NULL) {
        p = NULL;
        return;
    }

    p = L.first;
    if (L.first == L.last) { 
        L.first = NULL;
        L.last = NULL;
    } else {
        L.first = p->next;
        L.first->prev = NULL;
        p->next = NULL;
    }
}

void deleteAfter(address q, address &p) {
    if (q == NULL || q->next == NULL) {
        p = NULL;
        return;
    }

    p = q->next;
    q->next = p->next;
    if (p->next != NULL) {
        p->next->prev = q;
    }
    p->next = NULL;
    p->prev = NULL;
}

void deleteLast(List &L, address &p) {
    if (L.last == NULL) {
        p = NULL;
        return;
    }

    p = L.last;
    if (L.first == L.last) {
        L.first = NULL;
        L.last = NULL;
    } else {
        L.last = p->prev;
        L.last->next = NULL;
        p->prev = NULL;
    }
}

void removeAkun(string username, List &L) {
    address target = findAkun(username, L);
    if (target == NULL) {
        cout << "Account not found." << endl;
        return;
    }

    address p;
    if (target == L.first) {
        deleteFirst(L, p);
    } else if (target == L.last) {
        deleteLast(L, p);
    } else {
        deleteAfter(target->prev, p);
    }

    cout << "Account deleted: " << username << endl;
    delete p;
}

void showAll(List L) {
    address p = L.first;
    cout << "\n=== LIST AKUN ===\n";
    while (p != NULL) {
        cout << "Username: " << p->info.username
             << ", Password: " << p->info.password << endl;
        p = p->next;
    }
    cout << "==================\n";
}

int main() {
    List L;
    createList(L);

    Akun a1 = {"user1", "password"};
    Akun a2 = {"userAbc", "123abc"};
    Akun a3 = {"xyz", "001pqr"};

    signUp(a1, L);
    signUp(a2, L);
    signUp(a3, L);
    signUp(a2, L);

    showAll(L);

    removeAkun("userAbc", L);
    showAll(L);

    return 0;
}