#include <iostream>
#include <string>
using namespace std;

struct User {
    int id;
    string nama;
    float temperature;
    float humidity;
    int airquality;
    bool smoke;
    float noise;
    float monitoringscore;
    User* next;
};

// Variabel global head dan cur untuk linked list
User* head = NULL;
User* cur  = NULL;

// Function hitungScore : menghitung monitoring score berdasarkan jumlah sensor ideal
float hitungScore(User* cur) {
    int ideal = 0;

    // Cek tiap sensor apakah nilainya masuk range ideal
    if (cur->temperature >= 20 && cur->temperature <= 27) ideal++;
    if (cur->humidity >= 40 && cur->humidity <= 60) ideal++;
    if (cur->airquality >= 0 && cur->airquality <= 50) ideal++;
    if (cur->smoke == 0) ideal++;
    if (cur->noise >= 30 && cur->noise <= 55) ideal++;

    return (ideal / 5.0) * 100;
}

// Function cekIdDuplikat yaitu traversal linked list untuk cek apakah ID sudah ada
bool cekIdDuplikat(int id) {
    User* temp = head;
    while (temp != NULL) {
        if (temp->id == id) return true;
        temp = temp->next;
    }
    return false;
}

// Function cekWilayah yaitu dengan ambil 3 digit pertama ID lalu cocokkan dengan kode wilayah kelompok
bool cekWilayah(int id) {
    int prefix = id;
    while (prefix >= 1000) prefix /= 10;

    
    return (prefix == 015 || prefix == 030 || prefix == 142 || prefix == 110);
}

// ======================= Requirement 1 (Naufal) =======================//
// Function tambahUser untuk input data pelanggan baru, validasi, lalu masukkan ke linked list.
void tambahUser() {

    // Alokasi memori untuk node baru
    User* baru = new User;

    cout << "Masukkan User ID : ";
    cin >> baru->id;

    // Cek ID duplikat dan kode wilayah sebelum lanjut input
    if (cekIdDuplikat(baru->id)) {
        cout << "Error: User ID sudah ada di sistem\n";
        delete baru;
        return;
    }
    if (!cekWilayah(baru->id)) {
        cout << "Error: ID harus diawali kode wilayah yang valid\n";
        delete baru;
        return;
    }

    cout << "Masukkan Nama Pelanggan : ";
    cin >> baru->nama;

    cout << "Masukkan Temperature (-10 sampai 50) : ";
    cin >> baru->temperature;
    if (baru->temperature < -10 || baru->temperature > 50) {
        cout << "Error: Temperature di luar range\n";
        delete baru;
        return;
    }

    cout << "Masukkan Humidity (0 sampai 100) : ";
    cin >> baru->humidity;
    if (baru->humidity < 0 || baru->humidity > 100) {
        cout << "Error: Humidity di luar range\n";
        delete baru;
        return;
    }

    cout << "Masukkan Air Quality (0 sampai 500) : ";
    cin >> baru->airquality;
    if (baru->airquality < 0 || baru->airquality > 500) {
        cout << "Error: Air Quality di luar range\n";
        delete baru;
        return;
    }

    cout << "Masukkan Smoke (0 atau 1) : ";
    cin >> baru->smoke;
    if (baru->smoke != 0 && baru->smoke != 1) {
        cout << "Error: Smoke hanya boleh 0 atau 1\n";
        delete baru;
        return;
    }

    cout << "Masukkan Noise (0 sampai 120) : ";
    cin >> baru->noise;
    if (baru->noise < 0 || baru->noise > 120) {
        cout << "Error: Noise di luar range\n";
        delete baru;
        return;
    }

    // Hitung monitoring score otomatis setelah semua sensor diinput
    baru->monitoringscore = hitungScore(baru);
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = baru;
    }

    cout << "\nBerhasil menambahkan pelanggan baru\n";
    cout << "User ID          : " << baru->id << endl;
    cout << "Nama Pelanggan   : " << baru->nama << endl;
    cout << "Monitoring Score : " << baru->monitoringscore << "%" << endl;
}

// ======================= Requirement 2 & 3 (Thoriq) =======================//
// Mencari User
void cariUser(int idCari){
	cur = head;
	while(cur != NULL){
		
		// Cek apakah ID sama
		if(cur->id == idCari){
			
			cout<<"User ditemukan\n";
			cout<<"User ID :" << cur->id << endl;
			cout<<"Nama Pelanggan :" << cur->nama << endl;
			cout<<"Monitoring Score :" << cur->monitoringscore << endl;
			cout<<"Temperature :" << cur->temperature << endl;
			cout<<"Humidity :" << cur->humidity << endl;
			cout<<"Air Quality :" << cur->airquality << endl;
			cout<<"Smoke :" << cur->smoke << endl;
			cout<<"Noise :" << cur->noise << endl;
			
			return;
		}
		
		cur = cur->next;
	}
	cout<<"User tidak ditemukan\n";
}

// Mengupdate User
void updateUser(int idCari){
	cur = head;
	while(cur != NULL){
		
		// Cek apakah ID sama
		if(cur->id == idCari){
			
			cout<<"User found\n";
			cout<<"New Nama Pelanggan :";
			cin>>cur->nama;
			
			cout<<"New Temperature :";
			cin>>cur->temperature;
			
			cout<<"New Humidity :";
			cin>>cur->humidity;
			
			cout<<"New Air Quality :";
			cin>>cur->airquality;
			
			cout<<"New Smoke :";
			cin>>cur->smoke;
			
			cout<<"New Noise :";
			cin>>cur->noise;
			
			// Hitung ulang monitoring score otomatis dari sensor yang baru diupdate
			cur->monitoringscore = hitungScore(cur);
			cout<<"New Monitoring Score :" << cur->monitoringscore << "%" << endl;
			cout<<"Data berhasil diupdate\n";
			
			return;
		}
		
		cur = cur->next;
	}
	cout<<"User not found\n";
}

// ======================= Requirement 4 & 5 (Farras) =======================//
// Requirement 4: Hapus User
void hapusUser(int idHapus) {
    User* prev = NULL;
    cur = head;

    // Traversal linked list
    while (cur != NULL) {
        if (cur->id == idHapus) {
            if (prev == NULL) {
                head = cur->next;
            } else {
                prev->next = cur->next;
            }
            delete cur;
            cout << "User dengan ID " << idHapus << " berhasil dihapus dari sistem\n";
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "User not found\n";
}

// Bubble Sort untuk mengurutkan berdasarkan Monitoring Score (ascending)
void bubbleSort() {
    if (head == NULL) return;
    bool swapped;
    do {
        swapped = false;
        cur = head;
        while (cur->next != NULL) {
            if (cur->monitoringscore > cur->next->monitoringscore) {
                swap(cur->id, cur->next->id);
                swap(cur->nama, cur->next->nama);
                swap(cur->temperature, cur->next->temperature);
                swap(cur->humidity, cur->next->humidity);
                swap(cur->airquality, cur->next->airquality);
                swap(cur->smoke, cur->next->smoke);
                swap(cur->noise, cur->next->noise);
                swap(cur->monitoringscore, cur->next->monitoringscore);
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
}

// Requirement 5: Show Report
void showReport() {
    bubbleSort();

    cout << "LAPORAN MONITORING IOT\n";

    int total = 0;
    float sumScore = 0;

    cur = head;
    while (cur != NULL) {
        total++;
        sumScore += cur->monitoringscore;
        cout << "User ID : " << cur->id << endl;
        cout << "Nama Pelanggan : " << cur->nama << " Monitoring Score : " << cur->monitoringscore << "%" << endl;
        cout << "Temperature : " << cur->temperature << endl;
        cout << "Humidity : " << cur->humidity << endl;
        cout << "Air Quality : " << cur->airquality << endl;
        cout << "Smoke : " << cur->smoke << endl;
        cout << "Noise : " << cur->noise << endl;
        cout << "-----------------------------\n";
        cur = cur->next;
    }

    cout << "Total Pelanggan : " << total << endl;
    cout << "Rata-rata Score : " << (total ? sumScore / total : 0) << "%" << endl;
}



// ======================= MAIN =======================//
int main() {
    string cmd;
    while (true) {
        cout << "\nMasukkan perintah (Tambah/Cari/Update/Hapus/Show/Exit): ";
        cin >> cmd;
        if (cmd == "Tambah") tambahUser();
        else if (cmd == "Cari") { int id; cin >> id; cariUser(id); }
        else if (cmd == "Update") { int id; cin >> id; updateUser(id); }
        else if (cmd == "Hapus") { int id; cin >> id; hapusUser(id); }
        else if (cmd == "Show") showReport();
        else if (cmd == "Exit") break;
    }
    return 0;
}

