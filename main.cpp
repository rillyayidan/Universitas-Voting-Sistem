#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <conio.h>

using namespace std;

struct Pemilih {
    string nama;
    int umur;
    string gender;
    string Password;
    string Pilihan;
    string Rektor;
    string wakilRektor;
};

struct Kandidat {
    string nama;
    int jumlahVote;
};

stack<string> stackVote;
// menu utama
void menuUtama() {
    cout << "========== Pemungutan Suara ==========" << endl;
    cout << "1. Daftar Pemilih" << endl;
    cout << "2. Voting" << endl;
    cout << "3. Data Pemilih dan Pilihannya" << endl;
    cout << "4. Perolehan Suara" << endl;
    cout << "5. Batalkan Voting Terakhir" << endl;
    cout << "6. Keluar" << endl;
    cout << "=======================================" << endl;
    cout << "Masukkan pilihan Anda (1-6): ";
}

// sub-menu voting
void menuVoting() {
    cout << "========== Pilihan Voting ==========" << endl;
    cout << "1. Voting Rektor" << endl;
    cout << "2. Voting Wakil Rektor" << endl;
    cout << "3. Keluar" << endl;
    cout << "=====================================" << endl;
    cout << "Masukkan pilihan Anda (1-3): ";
}

// mendaftarkan pemilih
void daftarPemilih(vector<Pemilih>& pemilih) {
    string nama, gender, password;
    int umur;
	
    cout << "Nama: ";
    getline(cin, nama);

    if (nama.empty()) {
        cout << "Nama tidak boleh kosong." << endl;
        return;
    }

    cout << "Umur: ";
    cin >> umur;
    cin.ignore();

    cout << "Jenis Kelamin (L/P): ";
    getline(cin, gender);
    
    if (gender.empty()) {
        cout << "Jenis Kelamin tidak boleh kosong." << endl;
        return;
    }
    
    if (gender == "L" || gender == "l") {
        gender = "Laki-Laki";
    } else if (gender == "P" || gender == "p") {
        gender = "Perempuan";
    } else {
        cout << "Jenis Kelamin tidak valid." << endl;
        return;
    }

    cout << "Password: ";
    getline(cin, password);
    
    if (password.empty()) {
        cout << "Password tidak boleh kosong." << endl;
        return;
    }

    Pemilih pemilihBaru;
    pemilihBaru.nama = nama;
    pemilihBaru.umur = umur;
    pemilihBaru.gender = gender;
    pemilihBaru.Password = password;
    pemilihBaru.Pilihan = "";

    pemilih.push_back(pemilihBaru);

    ofstream file("data.txt", ios::app);  // Menggunakan mode ios::app agar data ditambahkan ke dalam file yang sudah ada
    if (file.is_open()) {
        file << "Nama: " << pemilihBaru.nama << endl;
        file << "Umur: " << pemilihBaru.umur << endl;
        file << "Jenis Kelamin: " << pemilihBaru.gender << endl;
        file << "Pilihan Rektor: " << pemilihBaru.Rektor << endl;
        file << "Pilihan Wakil Rektor: " << pemilihBaru.wakilRektor << endl;
        file << "---------------------------------------" << endl;
        file.close();
        cout << "Pemilih berhasil terdaftar dan data pemilih telah disimpan ke dalam file 'data.txt'." << endl;
    } else {
        cout << "Gagal membuka file 'data.txt'." << endl;
    }
}

// voting
void Voting(vector<Pemilih>& pemilih, vector<Kandidat>& kandidatRektor, vector<Kandidat>& kandidatWakilRektor) {
    string nama, password;

    cout << "Masukkan Nama: ";
    getline(cin, nama);

    cout << "Masukkan Password: ";
    getline(cin, password);

    for (Pemilih& p : pemilih) {
        if (p.nama == nama && p.Password == password) {
            if (p.Rektor != "" && p.wakilRektor != "") {
                cout << "Anda sudah melakukan voting sebelumnya." << endl;
                return;
            }
			
			do {
	            menuVoting();
	            int pilihan;
	            cin >> pilihan;
	            cin.ignore();
	
	            if (pilihan == 1) {
	                if (p.Rektor != "") {
	                    cout << "Anda sudah memilih Kandidat Rektor." << endl;
	                    return;
	                }
	
	                cout << "========== Kandidat Rektor ==========" << endl;
	                for (int i = 0; i < kandidatRektor.size(); i++) {
	                    cout << i + 1 << ". " << kandidatRektor[i].nama << endl;
	                }
	                cout << "=====================================" << endl;
	                cout << "Masukkan pilihan Anda: ";
	                int pilihanKandidat;
	                cin >> pilihanKandidat;
	                cin.ignore();
	
	                if (pilihanKandidat >= 1 && pilihanKandidat <= kandidatRektor.size()) {
	    				kandidatRektor[pilihanKandidat - 1].jumlahVote++;
	    				p.Rektor = kandidatRektor[pilihanKandidat - 1].nama;
	    				stackVote.push("Rektor");  // simpen voting rektor ke dalam stack
	    				system("cls");
					} else {
	    				cout << "Pilihan tidak valid." << endl;
	    				system("pause");
	    				system("cls");
					}
	
	
	            } else if (pilihan == 2) {
	                if (p.wakilRektor != "") {
	                    cout << "Anda sudah memilih Kandidat Wakil Rektor." << endl;
	                    return;
	                }
	
	                cout << "========== Kandidat Wakil Rektor ==========" << endl;
	                for (int i = 0; i < kandidatWakilRektor.size(); i++) {
	                    cout << i + 1 << ". " << kandidatWakilRektor[i].nama << endl;
	                }
	                cout << "===========================================" << endl;
	                cout << "Masukkan pilihan Anda: ";
	                int pilihanKandidat;
	                cin >> pilihanKandidat;
	                cin.ignore();
	
	                if (pilihanKandidat >= 1 && pilihanKandidat <= kandidatWakilRektor.size()) {
	    				kandidatWakilRektor[pilihanKandidat - 1].jumlahVote++;
	    				p.wakilRektor = kandidatWakilRektor[pilihanKandidat - 1].nama;
	    				stackVote.push("Wakil Rektor");  // simpen voting wakil rektor ke dalam stack
	    				system("cls");
					} else {
	   					cout << "Pilihan tidak valid." << endl;
	   					system("pause");
	    				system("cls");
					}
	
	            } else if (pilihan == 3) {
	                return;
	            } else {
	                cout << "Pilihan tidak valid." << endl;
	                return;
	            }
			} while (true);
			
            cout << "Terima Kasih Telah Voting!" << endl;
            return;
        }
    }

    cout << "Nama atau Password tidak ditemukan." << endl;
}

// Yang ini untuk hapus perolehan suara
void undoPerolehan(vector<Kandidat>& kandidat, const string& kandidatNama) {
    for (Kandidat& k : kandidat) {
        if (k.nama == kandidatNama) {
            k.jumlahVote--;
            break;
        }
    }
}

// Stack unvote
void batalVote(vector<Pemilih>& pemilih, vector<Kandidat>& kandidatRektor, vector<Kandidat>& kandidatWakilRektor) {
    if (stackVote.empty()) {
        cout << "Tidak ada operasi voting yang dapat dibatalkan." << endl;
        return;
    }

    string terakhirNgevote = stackVote.top();
    stackVote.pop();

    // Cari pemilih terakhir yang nge-vote
    for (int i = pemilih.size() - 1; i >= 0; i--) {
        Pemilih& p = pemilih[i];
        if (terakhirNgevote == "Rektor" && p.Rektor != "") {
            undoPerolehan(kandidatRektor, p.Rektor);  // panggil untuk cancel jumlah suara rektor
            p.Rektor = "";
            cout << "Operasi voting Rektor berhasil dibatalkan." << endl;
            return;
        } else if (terakhirNgevote == "Wakil Rektor" && p.wakilRektor != "") {
            undoPerolehan(kandidatWakilRektor, p.wakilRektor);  // panggil untuk cancel jumlah suara wakil rektor
            p.wakilRektor = "";
            cout << "Operasi voting Wakil Rektor berhasil dibatalkan." << endl;
            return;
        }
    }

    cout << "Operasi voting tidak ditemukan." << endl;

    cout << "Tekan Enter untuk kembali ke menu utama...";
    cin.ignore();
    cin.get();
    menuUtama();
}

// Searching
void Searching(const vector<Pemilih>& pemilih, const string& nama) {
    bool ditemukan = false;
    for (const Pemilih& p : pemilih) {
        if (p.nama == nama) {
            cout << "Nama: " << p.nama << endl;
            cout << "Umur: " << p.umur << endl;
            cout << "Jenis Kelamin: " << p.gender << endl;
            cout << "Pilihan Rektor: " << p.Rektor << endl;
            cout << "Pilihan Wakil Rektor: " << p.wakilRektor << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Pemilih dengan nama '" << nama << "' tidak ditemukan." << endl;
    }
}

void dataPemilih(const vector<Pemilih>& pemilih) {
	string password;
    cout << "Masukkan password: ";
    char ch;
    password = "";
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;

    system("cls");

    if (password != "admin") {
        cout << "Password salah. Akses ditolak." << endl;
        system("pause");
        return;
    }
    cout << "========== Daftar Pemilih dan Pilihannya ==========" << endl;
    int index = 1;
    for (const Pemilih& p : pemilih) {
        cout << index << ". Nama: " << p.nama << " Umur: " << p.umur << " Jenis Kelamin: " << p.gender << endl;
        cout << " Pilihan Rektor		: " << p.Rektor << endl;
        cout << " Pilihan Wakil Rektor	: " << p.wakilRektor << endl;
        index++;
    }
    cout << "==================================================" << endl;

    cout << "Apakah Anda ingin mencari data pemilih? (y/n): ";
    char pilihanCari;
    cin >> pilihanCari;
    cin.ignore();

    if (tolower(pilihanCari) == 'y') {
        cout << "Masukkan nama pemilih yang ingin dicari: ";
        string namaCari;
        getline(cin, namaCari);

        Searching(pemilih, namaCari);
    }

    cout << "Tekan 1 untuk kembali ke menu pilihan utama." << endl;
    int pilihan;
    cin >> pilihan;
    cin.ignore();
}

void jumlahSuara(const vector<Kandidat>& kandidatRektor, const vector<Kandidat>& kandidatWakilRektor) {
    cout << "========== Perolehan Suara Kandidat Rektor ==========" << endl;
    for (const Kandidat& k : kandidatRektor) {
        cout << k.nama << ": " << k.jumlahVote << " suara" << endl;
    }

    cout << "======= Perolehan Suara Kandidat Wakil Rektor =======" << endl;
    for (const Kandidat& k : kandidatWakilRektor) {
        cout << k.nama << ": " << k.jumlahVote << " suara" << endl;
    }
    cout << "=========================================================" << endl;

    cout << "Tekan 1 untuk kembali ke menu pilihan utama." << endl;
    int pilihan;
    cin >> pilihan;
    cin.ignore();
}

// Fungsi sorting
bool Sorting(const Pemilih& a, const Pemilih& b) {
    return a.nama < b.nama;
}

// OFStream
void simpanData(const vector<Pemilih>& pemilih, const vector<Kandidat>& kandidatRektor, const vector<Kandidat>& kandidatWakilRektor) {
    ofstream file("data.txt");
    if (file.is_open()) {
        // Simpan data pemilih
        for (const Pemilih& p : pemilih) {
            file << "Nama: " << p.nama << endl;
            file << "Umur: " << p.umur << endl;
            file << "Jenis Kelamin: " << p.gender << endl;
            file << "Pilihan Rektor: " << p.Rektor << endl;
            file << "Pilihan Wakil Rektor: " << p.wakilRektor << endl;
            file << "---------------------------------------" << endl;
        }

        // Simpan jumlah perolehan suara Rektor
        file << "========== Perolehan Suara Kandidat Rektor ==========" << endl;
        for (const Kandidat& k : kandidatRektor) {
            file << k.nama << ": " << k.jumlahVote << " suara" << endl;
        }

        // Simpan jumlah perolehan suara Wakil Rektor
        file << "======= Perolehan Suara Kandidat Wakil Rektor =======" << endl;
        for (const Kandidat& k : kandidatWakilRektor) {
            file << k.nama << ": " << k.jumlahVote << " suara" << endl;
        }

        file.close();
        cout << "Data pemilih, jumlah perolehan suara Rektor, dan jumlah perolehan suara Wakil Rektor berhasil disimpan ke dalam file 'data.txt'." << endl;
    } else {
        cout << "Gagal membuka file 'data.txt'." << endl;
    }
}


int main() {
    vector<Pemilih> pemilih;
    vector<Kandidat> kandidatRektor = {{"Reeve", 0}, {"Ray", 0}, {"Joko", 0}};
    vector<Kandidat> kandidatWakilRektor = {{"Lesty", 0}, {"Liswan", 0}};

    int pilihanUtama;

    do {
        menuUtama();
        while (!(cin >> pilihanUtama)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Masukkan pilihan Anda (1-6): ";
        }
        cin.ignore();

        switch (pilihanUtama) {
            case 1:
            	system("cls");
                daftarPemilih(pemilih);
                system("pause");
                system("cls");
                break;
            case 2:
            	system("cls");
                Voting(pemilih, kandidatRektor, kandidatWakilRektor);
                system("pause");
                system("cls");
                break;
            case 3:
            	system("cls");
                sort(pemilih.begin(), pemilih.end(), Sorting);
                dataPemilih(pemilih);
                system("cls");
                break;
            case 4:
            	system("cls");
                jumlahSuara(kandidatRektor, kandidatWakilRektor);
                system("cls");
                break;
            case 5:
            	system("cls");
    			batalVote(pemilih, kandidatRektor, kandidatWakilRektor);
    			simpanData(pemilih, kandidatRektor, kandidatWakilRektor);
    			system("pause");
                system("cls");
    			break;
            case 6:
                simpanData(pemilih, kandidatRektor, kandidatWakilRektor); // nyimpan data pemilih, jumlah perolehan suara rektor, dan Wakil Rektor ke dalam file "data.txt"
                cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!" << endl;
                system("pause");
                system("cls");
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                system("pause");
                system("cls");
                break;
        }
    } while (pilihanUtama != 6);

    return 0;
}
