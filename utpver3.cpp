#include <iostream>
using namespace std;

//buat node kaya biasa
class Node {
public:
    string nama;
    string wahana;
    Node* next;    //pionter yang menunjuk ke alamat node berikutnya

    Node(string n, string w) {    //constructor yg otomatis dijalankan saat node dibuat
        nama = n;
        wahana = w;
        next = nullptr;
    }
};

// class antrian pake sll
class Antrian {
private:
    Node* pHead;    //pointer yg nunjuk ke alamat node pertama

public:
    Antrian() {    //constructr 
        pHead = nullptr;
    }

    void append(string nama, string wahana) {
        Node* baru = new Node(nama, wahana);

        if (!pHead) {    //kalau pHead masih null
            pHead = baru;
            return;
        }

        Node* temp = pHead;
        while (temp->next) temp = temp->next;

        temp->next = baru;
    }

    void prepend(string nama, string wahana) {
        Node* baru = new Node(nama, wahana);
        baru->next = pHead;
        pHead = baru;
    }

    Node* deleteFront() {
        if (!pHead) return nullptr;

        Node* temp = pHead;
        pHead = pHead->next;
        return temp;    //alamatnya dikembalikan lalu nanti disimpan di pointer orang
    }

    void cancel(string nama) {
        if (!pHead) return;

        if (pHead->nama == nama) {
            Node* hapus = pHead;
            pHead = pHead->next;
            delete hapus;
            cout << nama << " batal antrian\n";
            return;
        }

        Node* temp = pHead;
        while (temp->next && temp->next->nama != nama) {
            temp = temp->next;
        }

        if (temp->next) {
            Node* hapus = temp->next;
            temp->next = hapus->next;
            delete hapus;
            cout << nama << " batal antrian\n";
        } else {
            cout << "Tidak ditemukan\n";
        }
    }

    void search(string nama) {
        Node* temp = pHead;
        int pos = 1;

        while (temp) {
            if (temp->nama == nama) {
                cout << nama << " ditemukan di posisi ke-" << pos
                     << " (wahana: " << temp->wahana << ")\n";
                return;
            }
            temp = temp->next;
            pos++;
        }

        cout << "Tidak ditemukan\n";
    }

    void display() {
        if (!pHead) {
            cout << "Antrian kosong\n";
            return;
        }

        Node* temp = pHead;
        cout << "Antrian:\n";
        while (temp) {
            cout << temp->nama << " (" << temp->wahana << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

//sistem log pake csll
class LogNode {
public:
    string data;
    LogNode* next;

    LogNode(string d) {
        data = d;
        next = nullptr;
    }
};

class Log {
private:
    LogNode* pHead;

public:
    Log() {
        pHead = nullptr;
    }

    void append(string data) {
        LogNode* baru = new LogNode(data);

        if (!pHead) {
            pHead = baru;
            baru->next = pHead;    // karna dia csll
            return;
        }

        LogNode* temp = pHead;
        while (temp->next != pHead) temp = temp->next;

        temp->next = baru;
        baru->next = pHead;
    }

    void display() {
        if (!pHead) {
            cout << "Log kosong\n";
            return;
        }

        LogNode* temp = pHead;
        cout << "Semua Log:\n";

        do {
            cout << "- " << temp->data << endl;
            temp = temp->next;
        } while (temp != pHead);    //pakai do while karna dia csll, agar semua node benar benar ditampilkan
    }

    void displayLast(int n) {
        if (!pHead) {
            cout << "Log kosong\n";
            return;
        }

        int count = 0;    //buat ngitung ada berapa node
        LogNode* temp = pHead;
        do {
            count++;
            temp = temp->next;
        } while (temp != pHead);

        int start = count - n;    //biar tau harus mulai di tampilkan dari mana
        if (start < 0) start = 0;    //antisipasi nilai n lebih besar dr jumlah node

        temp = pHead;    //reset dan pastiin posisi temp
        for (int i = 0; i < start; i++) {
            temp = temp->next;    //temp loncat ke posisi mulai yg dimau user
        }

        cout << "Log terakhir:\n";
        for (int i = start; i < count; i++) {
            cout << "- " << temp->data << endl;
            temp = temp->next;
        }
    }
};

//pilih wahana
string pilihWahana() {
    int pilih;
    cout << "Pilih Wahana:\n";
    cout << "1. RollerCoaster\n";
    cout << "2. Bianglala\n";
    cout << "3. KoraKora\n";
    cout << "Pilihan: ";
    cin >> pilih;

    if (pilih == 1) return "RollerCoaster";
    else if (pilih == 2) return "Bianglala";
    else if (pilih == 3) return "KoraKora";
    else return "Tidak diketahui";
}

// ================= MAIN =================
int main() {
    //buat object
    Antrian antrian;
    Log log;

    int pilih;
    string nama, wahana;

    do {    //pake do while karna harus muncul setidaknya sekali dulu
        cout << "\n=== TAMAN HIBURAN ===\n";
        cout << "1. Masuk Antrian Normal\n";
        cout << "2. Masuk Fast Track\n";
        cout << "3. Layani Pengunjung\n";
        cout << "4. Batal Antrian\n";
        cout << "5. Tampilkan Antrian\n";
        cout << "6. Cari Pengunjung\n";
        cout << "7. Tampilkan Semua Log\n";
        cout << "8. Tampilkan Log Terakhir\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
        case 1:
            cout << "Nama: ";
            cin >> nama;
            wahana = pilihWahana(); 
            antrian.append(nama, wahana);
            break;

        case 2:
            cout << "Nama: ";
            cin >> nama;
            wahana = pilihWahana(); 
            antrian.prepend(nama, wahana);
            break;

        case 3: {
            Node* orang = antrian.deleteFront();
            if (!orang) {
                cout << "Antrian kosong\n";
            } else {
                log.append(orang->nama + " naik " + orang->wahana);
                cout << orang->nama << " naik " << orang->wahana << endl;
                delete orang;    //karna datanya udah ga dibutuhkan
            }
            break;
        }

        case 4:
            cout << "Nama yang batal: ";
            cin >> nama;
            antrian.cancel(nama);
            break;

        case 5:
            antrian.display();
            break;

        case 6:
            cout << "Cari nama: ";
            cin >> nama;
            antrian.search(nama);
            break;

        case 7:
            log.display();
            break;

        case 8: {
            int n;
            cout << "Jumlah log terakhir: ";
            cin >> n;
            log.displayLast(n);
            break;
        }

        case 0:
            cout << "Program selesai\n";
            break;

        default:
            cout << "Pilihan tidak valid\n";
        }

    } while (pilih != 0);

    return 0;
}
