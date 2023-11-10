// JUDUL: PROGRAM PENJUALAN ANEKA PROPERTI.
// 1. Gerry Hasrom         =   2209106094 ( KETUA )
// 2. Rheza Gerard Altama  =   2209106103
// 3. Azhar Nur Hakim      =   2209106113 

// ====================================================================================================================================
// 													DEKLARASI BERBAGAI HEADER YANG DIGUNAKAN
// ====================================================================================================================================
// Deklarasi header iostream untuk input dan output. Seperti menggunakan fungsi cin (untuk menerima input) dan cout (untuk mencetak keprogram)
#include <iostream>

// Deklarasi header string untuk menggunakan tipe data string dan untuk mengizinkan fitur manipulasi string
#include <string>

// Deklarasi header limits karena melibatkan berbagai tipe data didalamnya
#include <limits>

// Deklarasi header untuk menggunakan fungsi system cls
#include <cstdlib>

// Deklarasi header untuk menggunakan csv pada data login user
#include <fstream> 

// Deklarasi header sstream untuk operasi manipulasi string dan mengonversi antara tipe data
#include <sstream>

// Deklarasi header untuk bagian exit program, untuk membuat teks bergerak, animasi loading, warna font
#include <windows.h>

// Deklarasi header bantuan untuk waktu pada animasi loading
#include <ctime>

// Deklarasi header untuk jump searching nama properti
#include <bits/stdc++.h>

using namespace std;

// ====================================================================================================================================
//													STRUCT DAN VARIABEL YANG DIGUNAKAN
// ====================================================================================================================================
// Deklarasi struct untuk data properti yang ditawarkan menggunakan double linked list
struct Data_Properti_Admin { //Penyimpanan Double Linked List yang mengakses CRUD
	string nama_properti_admin; // Di input admin
	int id_properti_admin; // Id tidak boleh sama
	string jenis_properti_admin; // Di input admin
	int harga_properti_admin; // Di input admin 
	int total_pembayaran; // Di input admin 
	int harga_cicilan_perbulan;  // Di input admin 
	int uang_muka; // Di input admin 
	int posisi; // untuk input posisi
	Data_Properti_Admin* next; // Pointer next double linked list
	Data_Properti_Admin* prev; // Pointer prev double linked list
}; 

// Deklarasi struct untuk data pribadi dan properti yang dibeli user (Customer) untuk melakukan operasi stack
struct Data_Pembelian_User { //Penyimpanan Stack yang mengakses Push dan Pop
    string nama_user; // Untuk membantu konfirmasi nama
    string nama_properti_user; // Nama properti user dimasukkan ke daftar pesanan dari data admin
    int id_properti_user; // Id Properti dimasukkan ke daftar pesanan dari data admin
    string jenis_properti_user; // Jenis properti user dimasukkan ke daftar pesanan dari data admin
    int harga_properti_user; // Harga properti user dimasukkan ke daftar pesanan dari data admin
	int harga_cicilan_perbulan; // Harga Cicilan Perbulan dimasukkan ke daftar pesanan dari data admin
	int uang_muka; // Uang Muka dimasukkan ke daftar pesanan dari data admin
};

// Deklarasi node untuk struct data pembelian user
struct Node {
    Data_Pembelian_User data;
    Node* next;
};

// Deklarasi untuk membantu node stack pada pembelian user
struct Stack {
    Node* top;
};

// Untuk membuat node baru pada daftar pesanan user 
Node* newNode(Data_Pembelian_User newData) {
    Node* nodeBaru = new Node();
    nodeBaru->data = newData;
    nodeBaru->next = NULL;
    return nodeBaru;
}

// Deklarasi struct untuk nama pada riwayat pembelian untuk melakukan operasi queue
struct Data_Riwayat_Pembelian {
    string konfirmasi_nama; // Konfirmasi nama menggunakan queue, logikanya jika user lain beli properti melalui agensi lain atas nama
    						// agensi kita di real life, maka admin membutuhkan catatan riwayat pembelian properti dengan menginput namanya
};

// Deklarasi struct Node_nama untuk queue
struct Node_nama {
    Data_Riwayat_Pembelian data;
    Node_nama *next;
};

// Head dan Tail pada data properti admin untuk mendukung penggunaan double linked list
Data_Properti_Admin* head = NULL;
Data_Properti_Admin* tail = NULL;

// Num_properti untuk membantu penambahan di tengah
int num_properti = 0;
// Total_data_properti untuk menghitung total data untuk membantu penambahan di tengah
int total_data_properti = 0;

// Variabel global untuk daftar properti admin
Data_Properti_Admin* propertiList = NULL; 

// Username dan Password untuk login Admin, pada program bisa input 2x untuk menampilkan username dan password ini
string username = "admin"; // saat mendaftarkan akun admin bisa masukkan "Lupa" 2x untuk merestore dan menunjukkan username dan password admin ini
string password = "admin";

// Node untuk mengecek top pada stack
Node* TOP = NULL; 

// Node front dan rear pada queue riwayat nama
Node_nama *front = NULL;
Node_nama *rear = NULL;

// Prototype
void user(), menu_utama();
void display(Node* top);
Node_nama *newNode();
void menu_1b_admin_enqueue(Node_nama **front, Node_nama **rear);
void menu_4b_admin_dequeue(Node_nama **front);

// ====================================================================================================================================
//						 BAGIAN TAMBAHAN SELAIN ADMIN DAN USER, BERFUNGSI UNTUK MENDESAIN DAN MEMPERMUDAH PROGRAM
// ====================================================================================================================================

// void ketika admin atau user memilih menu exit
void exit_program(){
	int screenWidth = 80;  // lebar pergerakan teks
    string message = "Terima kasih telah berkunjung ;)"; // Pesan akhir program yang akan ditampilkan bergerak
    int messageLength = message.length(); 
    int position = 0; // dari posisi 0 ke 80 untuk pergerakannya

    // Untuk Gerakan ke kanan
    for (int moveRight = 0; moveRight < 3; moveRight++) {
        while (position < screenWidth - messageLength) {
            system("cls"); // Bersihkan layar (Windows)
   
            for (int i = 0; i < position; i++) {
                cout << " ";
            }

            cout << message << endl;

            Sleep(100); // Sleep selama 100ms (0.1 detik)
            position++;
        }

        // Untuk Gerakan ke kiri
        while (position > 0) {
            system("cls"); // Bersihkan layar (Windows)

            for (int i = 0; i < position; i++) {
                cout << " ";
            }
            cout << message << endl;

            Sleep(100); // Sleep selama 100ms (0.1 detik)
            position--;
        }
    }
}

// void untuk animasi loading saat masuk ke setiap menu yang ditentukan
void animasi_loading(){
	int lebar_layar = 51; // pergerakan spinner bergerak sebanyak 51 kali supaya akhiran spinner berbentuk | (untuk lebih keren)
    int animasi_loading_bar = 0; // dimulai dari posisi 0
    const char spinner[] = "/-\\|"; // Karakter spinner yang akan bergerak

    while (animasi_loading_bar <= lebar_layar) { // Untuk mengendalikan animasi Loading
        system("cls"); // Bersihkan layar (Windows)

        cout << "Loading: [";
        for (int i = 0; i < animasi_loading_bar; i++) { // Loop kedua yang akan mencetak spasi
            cout << "="; // Loading mencetak ini dari awal sampai batasnya
        }
        for (int i = animasi_loading_bar; i < lebar_layar; i++) {
            cout << " ";
        }

        cout << "] " << (animasi_loading_bar * 100 / lebar_layar) << "% " << spinner[animasi_loading_bar % 4]; // Animasi penutup loading bar

        animasi_loading_bar++;
        Sleep(10); // Sleep selama 50ms (0.05 detik) dan tanda "+" akan menyesuaikan dengan waktu ini
    }
}

// Fungsi untuk membersihkan output
void bersihkan() {
	system("cls");
}

// Fungsi untuk sebelum melanjutkan, tekan enter terlebih dahulu
void tekan_enter() {
	cin.get();
}

// Fungsi untuk membersihkan buffer dibeberapa kondisi 
void clear_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//===========================================================================================================================================
// 													BAGIAN ADMIN
//===========================================================================================================================================

// Berbagai Prototype
void menu_utama_admin(), menu_1_admin(), menu_1a_admin(), menu_1b_admin(), menu_2_admin(), menu_2a_admin(), menu_2b_admin(), 
menu_3_admin(), menu_4_admin(), menu_4a_admin(), menu_4b_admin();
void menu_2c_admin_display(Node_nama *front);

// Void ketika memilih menu login admin input username dan pass yang telah ditentukan
void admin(){
	string input_username;
	string input_password;
	int kesempatan_input = 1; // untuk menghitung kesempatan input
	int Maxkesempatan_input = 4; // ketika kesempatan input sampai 4x, ini digunakan untuk keluar dari void
	     	
	std::cout << "\033[1;31m"; // Untuk mencetak warna, menggunakan header #include <windows.h>
	std::cout << "\nSystem: "; // Teks yang dikenai warna 
	std::cout << "\033[0m"; // mengembalikan warna ke semula
	std::cout << "Login Admin Berhasil!\n" << std::endl; // pakai std::cout untuk menggunakan fungsi ini dan std::endl untuk menutupnya
	cout << "x====================================================x" << endl;
	std::cout << "|     	    	   |";
	std::cout << "\033[1;93m"; std::cout << " LOGIN ADMIN "; std::cout << "\033[0m"; std::cout << "|                   |" << std::endl;		
	cout << "x====================================================x" << endl;
	cout << "|                                                    |" << endl;
	cout << "|          Username Admin: _ _ _ _ _                 |" << endl;
	cout << "|          Password Admin: _ _ _ _ _                 |" << endl;
	cout << "|                                                    |" << endl;
	cout << "|                   Lupa user/pass? (input 'lupa')2x |" << endl; // Jika lupa user dan pass admin, input lupa 2x di setiap user dan passnya
	cout << "x====================================================x" << endl;
	
    while (kesempatan_input < Maxkesempatan_input) {
        cout << "\nMasukkan Username admin: ";
        cin >> input_username;

        cout << "Masukkan Password admin: ";
        cin >> input_password;
    
    // Untuk mencetak user dan pass admin jika input lupa 2x
    if (input_username == "lupa" && input_password == "lupa" || input_username == "lupa user pass" && input_password == "lupa user pass") {
			cout << "\nx====================================================x" << endl;
			cout << "|     	  	Restore Admin Account                |" << endl;
			cout << "x====================================================x" << endl;
			cout << "|                                                    |" << endl;
			cout << "|          Username Admin: " << username << "                     |" << endl;
			cout << "|          Password Admin: " << password << "                     |" << endl;
			cout << "|                                                    |" << endl;
			cout << "x====================================================x" << endl;
		
		// jika login admin berhasil	
        } else if (input_username == username && input_password == password) {
            std::cout << "\033[1;31m"; // cetak teks dengan warna
			std::cout << "\nSystem: ";
			std::cout << "\033[0m"; 									  // Teks bahasa inggris untuk lebih keren
			cout << "\n  Login admin berhasil!\n" << "  Hey Welcome." << " A bright day to start the day, admin.\n" << "  What do you want to do?" << endl;
			menu_utama_admin(); // setelah login masuk ke void menu utama admin 
			        
        } else { // jika login gagal akan menampilkan ini
        	cout << "\nLogin gagal. Coba lagi.\n";
            cout << "Anda sudah mencoba sebanyak: " << kesempatan_input << " kali." << endl;
            kesempatan_input++;
        }
    }

    std::cout << "\033[1;31m"; // cetak teks dengan warna
	std::cout << "\nSystem: ";
	std::cout << "\033[0m"; // kembalikan warna ke semula
	cout << "Kesempatan login admin anda sudah habis." << endl;
	
	std::cout << "\033[1;93m"; 
	std::cout << "System: ";
	std::cout << "\033[0m";
	cout << "Mendeteksi penyusup...  " << "\n        Program menendang anda kembali ke login admin/user." << endl; // untuk memberikan pesan supaya lebih keren
}

// void ketika berhasil login 
void menu_utama_admin() {
	int pilihan;
	bersihkan(); // void untuk bersihkan inputan sebelumnya (sudah dideklarasikan diawal)
	
	do {
		animasi_loading();
		std::cout << "\033[1;31m"; // cetak warna
        std::cout << "\nSystem : ";
        std::cout << "\033[0m"; // kembalikan warna
        std::cout << " Hey admin, where have you been, we need you now!" << std::endl;
        std::cout << "          Organize all these sales! ;] " << std::endl;
		
		cout << "\nx====================================================x" << endl;
		std::cout << "|     	    	   ";
		std::cout << "\033[95m"; std::cout << " MENU UTAMA ADMIN "; std::cout << "\033[0m"; 
		std::cout << "                |" << std::endl;
		cout << "x====================================================x" << endl;
		cout << "|                                                    |" << endl; 
	    cout << "|               1. Menu Tambahkan Data               |" << endl;
	    cout << "|               2. Menu Tampilkan Data               |" << endl;
	    cout << "|               3. Menu Edit Data Properti Admin     |" << endl;
	    cout << "|      	        4. Menu Hapus Data                   |" << endl;
	    cout << "|               5. Logout Akun Admin                 |" << endl;
	    cout << "|               6. Exit                              |" << endl;
	    cout << "|                                                    |" << endl;
	    cout << "x====================================================x" << endl;
	    cout << "\nSilahkan pilih menu utama admin [1-6]: "; // lengkap dengan error handling
	    
		if (!(cin >> pilihan)) {
            cin.clear(); // untuk mengatur ulang status, jika kesalahan pembacaan input, akan mengembalikan statusnya ke normal
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Untuk mengabaikan karakter yang tersisa dalam inputan sampai menemui karakter newline
            cout << "\nMenu hanya terdiri dari: \n" << "1. Menu Tambahkan Data \n" // pesan untuk membantu pemilihan menu 
			<< "2. Menu Tampilkan Data\n"
			<< "3. Menu Edit Data\n"
			<< "4. Menu Hapus Data\n"
			<< "5. Logout Akun Admin\n"
			<< "6. Exit\n"; 
			std::cout << "\033[1;31m"; // cetak teks dengan warna
			std::cout << "\nSystem: ";
			std::cout << "\033[0m"; // kembalikan ke awal
			std::cout << "Maaf Silahkan coba lagi\n" << std::endl; 
	        continue;
        }	
        
        switch(pilihan) {
        	case 1:
        		menu_1_admin(); // untuk masuk ke menu tambahkan data admin diawal, tengah, dan akhir
        		break;
        	case 2:
        		menu_2_admin(); // untuk masuk ke menu tampilkan data admin, data pesanan user, dan riwayat nama pembelian user
        		break;
			case 3:
				menu_3_admin(); // untuk edit data properti admin, jika tidak ada data akan langsung kembali tanpa memberikan pesan apapun
				break;
        	case 4:
				menu_4_admin(); // untuk masuk ke menu hapus data properti admin diawal, tengah, dan akhir
        		break;
        	case 5:
        		menu_utama(); // masuk kembali ke menu mau login admin / user
        		break;
        	case 6:
        		animasi_loading(); // animasi loading
            	exit_program(); // animasi exit
        		break;
			default:
			    cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl; // jika salah input menu
			    break;
			    	}
			    } while (pilihan != 6); // jika memasukkan pilihan menu bukan 1 sampai 6 akan terus melakukan looping
	}

// Fungsi membuat node baru dengan error handling dan looping
Node_nama *newNode() {
    Node_nama *nodeBaru = new Node_nama(); // deklarasi dari sebuah fungsi bernama newNode yang mengembalikan pointer ke objek Node_nama
    while (true) { 
        cout << "\nMasukkan Konfirmasi Nama: ";
        cin >> ws;  // Membersihkan whitespace dari input sebelum menggunakan getline
        getline(cin, nodeBaru->data.konfirmasi_nama); // membaca seluruh baris termasuk spasi

        // Cek apakah nama hanya mengandung huruf (menggunakan error handling hanya bisa input huruf besar atau kecil dari huruf A sampai Z
        if (nodeBaru->data.konfirmasi_nama.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos) { 
        	cout << "\nNama Berhasil dimasukkan!\n";
            break;  // Keluar dari loop jika nama valid 
        } else {
            cout << "Data hanya boleh huruf. Silakan masukkan kembali." << endl;
        }
    }
    return nodeBaru; // mengembalikan node baru
}

// void untuk memasukkan konfirmasi nama ke riwayat pembelian user 
void menu_1b_admin_enqueue(Node_nama **front, Node_nama **rear) {
    Node_nama *nodeBaru = newNode();  // Membuat node baru untuk menyimpan data

    if (*front == NULL) {
        // Jika antrian kosong, node baru menjadi elemen pertama
        *front = nodeBaru;
        *rear = nodeBaru;
    } else {
        // Jika antrian tidak kosong, cari elemen terakhir
        Node_nama *current = *front;
        while (current->next != NULL) {
            current = current->next;
        }
        // Sambungkan node baru ke elemen terakhir
        current->next = nodeBaru;
        *rear = nodeBaru;
    }
}

// void untuk menambahkan data properti admin dan data nama riwayat pembelian 
void menu_1_admin(){
	int pilihan;
	
	do {
		cout << "\nx====================================================x" << endl;
		std::cout << "|     	    	";
		std::cout << "\033[1;32m"; std::cout << " Menu Tambah Data Admin "; std::cout << "\033[0m"; 
		std::cout << "             |" << std::endl;
		cout << "x====================================================x" << endl;
		cout << "|                                                    |" << endl;
	    cout << "|       1. Tambahkan Data Properti Yang Dijual       |" << endl;
	    cout << "|       2. Enqueue Data Nama Riwayat Pembelian       |" << endl;
	    cout << "|       3. Back                                      |" << endl;
	    cout << "|                                                    |" << endl;
	    cout << "x====================================================x" << endl;
	    cout << "\nSilahkan pilih menu utama admin [1-3]: ";
	    
	    if (!(cin >> pilihan)) {
            cin.clear(); // untuk mengatur ulang status, jika kesalahan pembacaan input, akan mengembalikan statusnya ke normal
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Untuk mengabaikan karakter yang tersisa dalam inputan sampai menemui karakter newline
            cout << "\nMenu hanya terdiri dari: \n" << "1. Push Data Properti Yang Dijual \n"
			<< "2. Enqueue Data Nama Riwayat Pembelian" << endl;
			std::cout << "\033[1;31m";  // untuk cetak teks berwarna
			std::cout << "\nSystem: ";
			std::cout << "\033[0m"; // kembalikan warna asal
			std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
	        continue;
        }	
        
        switch(pilihan) {
        	case 1:
        		menu_1a_admin();
        		break;
        	case 2:
        		menu_1b_admin_enqueue(&front, &rear);
        		break;
        	case 3:
				break;
			default:
			    cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
			    break;
			    	}
			    } while (pilihan != 3);
	}

// void untuk menambahkan data properti di awal admin
void tambah_data_di_awal() {
    Data_Properti_Admin* new_data = new Data_Properti_Admin(); //  untuk membuat objek Data_Properti_Admin yang baru, dan variabel new_data akan menunjuk ke objek tersebut
	
	// input nama properti beserta error handling
    cout << "\nMasukkan nama properti: ";
    cin.ignore(); 
    do {
    	// error handling hanya boleh huruf, jika tidak akan terus looping sampai input benar
        getline(cin, new_data->nama_properti_admin); 
        if (new_data->nama_properti_admin.empty() || new_data->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
            cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan nama properti: ";
            cin.clear();
        }
    } while (new_data->nama_properti_admin.empty() || new_data->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);
	
	
	// input id properti beserta error handling
    cout << "\nMasukkan ID properti: ";
	int idPropertiInput;
	bool idSudahAda = false;
	
	do {
	    cin >> idPropertiInput;
	    idSudahAda = false; // Nolkan flag ini setiap kali pengguna memasukkan ID baru
		
		// error handling hanya boleh angka, dan tidak boleh 0, jika salah input akan terus looping sampai input benar
	    // Periksa apakah ID sudah ada dalam daftar
	    Data_Properti_Admin* current = head;
	    while (current != NULL) {
	        if (current->id_properti_admin == idPropertiInput) {
	            idSudahAda = true;
	            cout << "ID properti sudah ada. Masukkan ID properti yang berbeda: ";
	            break; // Keluar dari loop saat ID sudah ada
	        }
	        current = current->next;
	    }
	
	    if (cin.fail() || idPropertiInput <= 0) {
	        if (cin.fail()) {
	            cout << "Masukkan hanya boleh angka. Masukkan ID properti: ";
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        } else if (idPropertiInput <= 0) {
	            cout << "Masukkan angka lebih dari 0. Masukkan ID properti: ";
	        }
	    }
	
	    if (cin.peek() == '\n' && !idSudahAda) { // cek untuk inputannya apakah sudah ada? jika belum ketika enter akan looping kembali 
	        break;
	    }
	} while (cin.fail() || idPropertiInput <= 0 || idSudahAda);
	
	if (!cin.fail()) {
	    new_data->id_properti_admin = idPropertiInput;
	}
	
	// input jenis properti beserta error handling
    cout << "\nMasukkan jenis properti: ";
    cin.ignore();
    do {
        getline(cin, new_data->jenis_properti_admin);
        if (new_data->jenis_properti_admin.empty() || new_data->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
            cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan jenis properti: ";
            cin.clear();
        }
    } while (new_data->jenis_properti_admin.empty() || new_data->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);
	
	// input harga properti beserta error handling
    cout << "\nMasukkan harga properti: ";
    do {
        cin >> new_data->harga_properti_admin;
        if (cin.fail() || new_data->harga_properti_admin <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga properti: ";
            }
            if (cin.peek() == '\n') {  /// cek untuk inputannya apakah sudah ada? jika belum ketika enter akan looping kembali 
                cout << "Masukkan tidak boleh kosong. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->harga_properti_admin <= 0);
	
	// input harga cicilan perbulan beserta error handling
    cout << "\nMasukkan harga cicilan per bulan: ";
    do {
        cin >> new_data->harga_cicilan_perbulan;
        if (cin.fail() || new_data->harga_cicilan_perbulan <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga cicilan per bulan: ";
            }
            if (cin.peek() == '\n') {  // cek untuk inputannya apakah sudah ada? jika belum ketika enter akan looping kembali 
                cout << "Masukkan tidak boleh kosong. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->harga_cicilan_perbulan <= 0);
	
	// input uang muka beserta error handling
    cout << "\nMasukkan uang muka: ";
    do {
        cin >> new_data->uang_muka;
        if (cin.fail() || new_data->uang_muka <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan uang muka:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan uang muka: ";
            }
            if (cin.peek() == '\n') {  // cek untuk inputannya apakah sudah ada? jika belum ketika enter akan looping kembali 
                cout << "Masukkan tidak boleh kosong. Masukkan uang muka: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->uang_muka <= 0);

    if (head == NULL) {
        // Jika daftar kosong, inisialisasi head dan tail
        head = new_data;
        tail = new_data;
        new_data->next = NULL;
        new_data->prev = NULL;
    } else {
        // Sisipkan data baru di awal
        new_data->next = head;
        new_data->prev = NULL;
        head->prev = new_data;
        head = new_data;
    }
    
    num_properti++; // Tingkatkan 1 num properti 
    total_data_properti++; // Tingkatkan 1 total data

    cout << "\n|====================================================|" << endl;
    cout << "| Data properti berhasil ditambahkan di awal daftar! |" << endl;
    cout << "|====================================================|" << endl;
}

// void untuk menambahkan data properti di tengah admin
void tambah_data_di_tengah() {
    if (head == NULL) {
        cout << "Daftar kosong. Tambahkan data terlebih dahulu." << endl;
        return;
    }

    if (head->next == NULL) {
        cout << "Daftar tidak boleh hanya 1. Tambahkan data lain terlebih dahulu." << endl;
        return;
    }
    int posisi; // deklarasi header untuk memudahkan memasukkan posisi input
																				// maksud pesan dibawah jika data cuman 2, kemudian sampai posisi 2, inputan 2 dapat dilakukan selainnya tidak
    cout << "\nMasukkan posisi (Dari posisi 2 - posisi " << num_properti << " (Sebelum jika data tidak dua) dari total " << total_data_properti << " data: ";
    cin >> posisi;

    if (posisi < 2 || posisi > total_data_properti ) {
        cout << "Posisi tidak valid." << endl;
        return;
    }

    Data_Properti_Admin* new_data = new Data_Properti_Admin();

    cout << "\nMasukkan nama properti: ";
    cin.ignore();
    do {
        getline(cin, new_data->nama_properti_admin);
        if (new_data->nama_properti_admin.empty() || new_data->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
            cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan nama properti: ";
            cin.clear();
        }
    } while (new_data->nama_properti_admin.empty() || new_data->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);

    cout << "\nMasukkan ID properti: ";
	int idPropertiInput;
	bool idSudahAda = false;
	
	do {
	    cin >> idPropertiInput;
	    idSudahAda = false; // Nolkan flag ini setiap kali pengguna memasukkan ID baru
	
	    // Periksa apakah ID sudah ada dalam daftar
	    Data_Properti_Admin* current = head;
	    while (current != NULL) {
	        if (current->id_properti_admin == idPropertiInput) {
	            idSudahAda = true;
	            cout << "ID properti sudah ada. Masukkan ID properti yang berbeda: ";
	            break; // Keluar dari loop saat ID sudah ada
	        }
	        current = current->next;
	    }
	
	    if (cin.fail() || idPropertiInput <= 0) {
	        if (cin.fail()) {
	            cout << "Masukkan hanya boleh angka. Masukkan ID properti: ";
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        } else if (idPropertiInput <= 0) {
	            cout << "Masukkan angka lebih dari 0. Masukkan ID properti: ";
	        }
	    }
	
	    if (cin.peek() == '\n' && !idSudahAda) { 
	        break;
	    }
	} while (cin.fail() || idPropertiInput <= 0 || idSudahAda);
	
	if (!cin.fail()) {
	    new_data->id_properti_admin = idPropertiInput;
	}

    cout << "\nMasukkan jenis properti: ";
cin.ignore();
do {
    getline(cin, new_data->jenis_properti_admin);
    if (new_data->jenis_properti_admin.empty() || new_data->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
        cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan jenis properti: ";
        cin.clear();
    }
} while (new_data->jenis_properti_admin.empty() || new_data->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);


    cout << "\nMasukkan harga properti: ";
    do {
        cin >> new_data->harga_properti_admin;
        if (cin.fail() || new_data->harga_properti_admin <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga properti: ";
            }
            if (cin.peek() == '\n') { 
                cout << "Masukkan tidak boleh kosong. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->harga_properti_admin <= 0);

    cout << "\nMasukkan harga cicilan per bulan: ";
    do {
        cin >> new_data->harga_cicilan_perbulan;
        if (cin.fail() || new_data->harga_cicilan_perbulan <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga cicilan per bulan: ";
            }
            if (cin.peek() == '\n') {  
                cout << "Masukkan tidak boleh kosong. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->harga_cicilan_perbulan <= 0);

    cout << "\nMasukkan uang muka: ";
    do {
        cin >> new_data->uang_muka;
        if (cin.fail() || new_data->uang_muka <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan uang muka:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan uang muka: ";
            }
            if (cin.peek() == '\n') {  
                cout << "Masukkan tidak boleh kosong. Masukkan uang muka: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->uang_muka <= 0);

    Data_Properti_Admin* current = head;
    for (int i = 1; i < posisi - 1; ++i) {
        current = current->next;
    }
    new_data->next = current->next;
    new_data->prev = current;
    if (current->next != NULL) {
        current->next->prev = new_data;
    }
    current->next = new_data;
	
	total_data_properti++; // naikkan 1 total data properti
    num_properti++; // naikkan 1 num properti

    cout << "\n|====================================================|" << endl;
    cout << "| Data properti berhasil ditambahkan di tengah daftar! |" << endl;
    cout << "|====================================================|" << endl;
}

// void untuk menambahkan data properti di akhir pada admin
void tambah_data_di_akhir() {
    if (head == NULL) {
        cout << "Daftar kosong. Data properti tidak dapat ditambahkan di akhir." << endl;
        return;
    }

    Data_Properti_Admin* new_data = new Data_Properti_Admin();

    cout << "\nMasukkan nama properti: ";
    cin.ignore();
    do {
        getline(cin, new_data->nama_properti_admin);
        if (new_data->nama_properti_admin.empty() || new_data->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
            cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan nama properti: ";
            cin.clear();
        }
    } while (new_data->nama_properti_admin.empty() || new_data->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);

    cout << "\nMasukkan ID properti: ";
	int idPropertiInput;
	bool idSudahAda = false;
	
	do {
	    cin >> idPropertiInput;
	    idSudahAda = false; // Nolkan flag ini setiap kali pengguna memasukkan ID baru
	
	    // Periksa apakah ID sudah ada dalam daftar
	    Data_Properti_Admin* current = head;
	    while (current != NULL) {
	        if (current->id_properti_admin == idPropertiInput) {
	            idSudahAda = true;
	            cout << "ID properti sudah ada. Masukkan ID properti yang berbeda: ";
	            break; // Keluar dari loop saat ID sudah ada
	        }
	        current = current->next;
	    }
	
	    if (cin.fail() || idPropertiInput <= 0) {
	        if (cin.fail()) {
	            cout << "Masukkan hanya boleh angka. Masukkan ID properti: ";
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        } else if (idPropertiInput <= 0) {
	            cout << "Masukkan angka lebih dari 0. Masukkan ID properti: ";
	        }
	    }
	
	    if (cin.peek() == '\n' && !idSudahAda) { 
	        break;
	    }
	} while (cin.fail() || idPropertiInput <= 0 || idSudahAda);
	
	if (!cin.fail()) {
	    new_data->id_properti_admin = idPropertiInput;
	}

    cout << "\nMasukkan jenis properti: ";
    cin.ignore();
    do {
        getline(cin, new_data->jenis_properti_admin);
        if (new_data->jenis_properti_admin.empty() || new_data->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
            cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan jenis properti: ";
            cin.clear();
        }
    } while (new_data->jenis_properti_admin.empty() || new_data->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);

    cout << "\nMasukkan harga properti: ";
    do {
        cin >> new_data->harga_properti_admin;
        if (cin.fail() || new_data->harga_properti_admin <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga properti: ";
            }
            if (cin.peek() == '\n') { 
                cout << "Masukkan tidak boleh kosong. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->harga_properti_admin <= 0);

    cout << "\nMasukkan harga cicilan per bulan: ";
    do {
        cin >> new_data->harga_cicilan_perbulan;
        if (cin.fail() || new_data->harga_cicilan_perbulan <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga cicilan per bulan: ";
            }
            if (cin.peek() == '\n') {  
                cout << "Masukkan tidak boleh kosong. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->harga_cicilan_perbulan <= 0);

    cout << "\nMasukkan uang muka: ";
    do {
        cin >> new_data->uang_muka;
        if (cin.fail() || new_data->uang_muka <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan uang muka:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan uang muka: ";
            }
            if (cin.peek() == '\n') {  
                cout << "Masukkan tidak boleh kosong. Masukkan uang muka: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || new_data->uang_muka <= 0);

    new_data->next = NULL;

    if (head == NULL) {
        // Jika daftar kosong, data baru tidak ditambahkan
        cout << "Daftar kosong. Data properti tidak dapat ditambahkan di akhir." << endl;
        delete new_data;
        return;
    } else {
        // Data baru menjadi elemen tail
        new_data->prev = tail;
        tail->next = new_data;
        tail = new_data;
    }

    cout << "\n|====================================================|" << endl;
    cout << "| Data properti berhasil ditambahkan di akhir daftar! |" << endl;
    cout << "|====================================================|" << endl;

    num_properti++;
    total_data_properti++;
}

// void untuk menu tambah data admin mau dengan menambah diawal, tengah, atau akhir
void menu_1a_admin() {
    int pilihan;

    do {
        cout << "\nx=====================================================================x" << endl;
        std::cout << "|     	    	";
        std::cout << "\033[95m"; std::cout << " MENU TAMBAH DATA PENJUALAN ADMIN "; std::cout << "\033[0m"; 
        std::cout << "                    |" << std::endl;
        cout << "x=====================================================================x" << endl;
        cout << "|                                                                     |" << endl;
        cout << "|       1. Tambahkan Data Properti Yang Dijual di awal daftar         |" << endl;
        cout << "|       2. Tambahkan Data Properti Yang Dijual di tengah daftar       |" << endl;
        cout << "|       3. Tambahkan Data Properti Yang Dijual di akhir daftar        |" << endl;
        cout << "|       4. Back                                                       |" << endl;
        cout << "|                                                                     |" << endl;
        cout << "x=====================================================================x" << endl;
        cout << "\nSilahkan pilih menu utama admin [1-4]: ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\nMenu hanya terdiri dari: \n" << "1. Tambahkan Data Properti Yang Dijual di awal daftar \n"
            << "2. Tambahkan Data Properti Yang Dijual di tengah daftar\n" 
            << "3. Tambahkan Data Properti Yang Dijual di akhir daftar\n"
            << "4. Back";
            std::cout << "\033[1;31m"; 
            std::cout << "\nSystem: ";
            std::cout << "\033[0m"; 
            std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
            continue;
        }   
    
        switch (pilihan) {
            case 1:
                tambah_data_di_awal(); // masuk ke void tambah awal
                break;
            case 2: 
				tambah_data_di_tengah(); // masuk ke void tambah ditengah 
				break; 
			case 3: 
				tambah_data_di_akhir(); // masuk ke void tambah diakhir
				break;
            case 4:
                break;
            default:
                cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 4); // looping jika inputan bukan dari 1 hingga 4
}

// void untuk tampilkan data properti admin, data pesanan user, dan riwayat nama pembelian
void menu_2_admin(){
	int pilihan;

    do {
        cout << "\nx=====================================================================x" << endl;
        std::cout << "|     	            	";
        std::cout << "\033[0;33m"; std::cout << "    MENU TAMPILAN DATA   "; std::cout << "\033[0m"; 
        std::cout << "                     |" << std::endl;
        cout << "x=====================================================================x" << endl;
        cout << "|                                                                     |" << endl;
        cout << "|       1. Tampilkan Data Properti Yang Dijual                        |" << endl;
        cout << "|       2. Tampilkan Data Properti Yang Dibeli oleh user              |" << endl;
        cout << "|       3. Tampilkan riwayat pembelian user                           |" << endl;
        cout << "|       4. Back                                                       |" << endl;
        cout << "|                                                                     |" << endl;
        cout << "x=====================================================================x" << endl;
        cout << "\nSilahkan pilih menu utama admin [1-4]: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\nMenu hanya terdiri dari: \n" << "1.Tampilkan Data Properti Yang Dijual \n"
            << "2. Tampilkan Data Properti Yang Dibeli oleh user \n" 
            << "3. Tampilkan riwayat pembelian user\n"
            << "4. Back";
            std::cout << "\033[1;31m"; 
            std::cout << "\nSystem: ";
            std::cout << "\033[0m"; 
            std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
            continue;
        }   
    
        switch (pilihan) {
            case 1:
                menu_2a_admin(); // void untuk menampilkan semua data properti admin
                break;
            case 2: 
				display(TOP); // void untuk menampilkan data pesanan user menggunakan parameter top sesuai pada stack untuk mengambil semua datanya
				break;
			case 3: 
				cout << "\n====================================================" << endl;
   				cout << "|              RIWAYAT PEMBELIAN USER              |" << endl;
    			cout << "====================================================" << endl;
				menu_2c_admin_display(front); // void untuk menampilkan riwayat pembelian user, menggunakan parameter front sesuai queue
				break;
            case 4:
                break;
            default:
                cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 4);
	
}
	
// void untuk tempat menampilkan data properti admin
void menu_2a_admin() { 
    if (head == NULL) { // memeriksa apakah data nya kosong jika iya pesan akan tampil
        cout << "\nBelum ada data properti yang dimasukkan." << endl;
        return; // jika data ada lanjut ke bagian berikutnya menampilkan semua datanya
    }

    cout << "\n----------===============================---------";
    cout << "\n|========= PENJUALAN ANEKA PROPERTI =============|";
    cout << "\n----------===============================---------\n";

    Data_Properti_Admin* current = head; // Mendeklarasikan pointer current dan menginisialisasinya dengan elemen pertama (head) dalam daftar.
    int nomor_properti = 1;

    while (current != NULL) {
        cout << "|  Properti " << nomor_properti << ":" << endl;
        cout << "|  Nama Properti : " << current->nama_properti_admin << endl;
        cout << "|  ID Properti : " << current->id_properti_admin << endl;
        cout << "|  Jenis Properti : " << current->jenis_properti_admin << endl;
        cout << "|  Harga Properti : Rp." << current->harga_properti_admin << endl;
        cout << "|  Harga Cicilan Per Bulan : Rp." << current->harga_cicilan_perbulan << endl;
        cout << "|  Uang Muka : Rp." << current->uang_muka << endl;
        cout << "==================================================\n";

        current = current->next; // untuk menggeser pointer current ke elemen berikutnya dalam daftar 
        nomor_properti++; 
    }
}

// Void untuk menampilkan atau mendisplay data riwayat nama pembelian menggunakan parameter front
void menu_2c_admin_display(Node_nama *front) {
    if (front == NULL) { // jika queue kosong pesan akan tampil
        cout << "---------------------------------------" << endl;
        cout << "Tidak ada Data Yang dimasukkan!" << endl;
        cout << "----------------------------------------" << endl;
        return; // jika data adam lanjut menampilkan semua datanya
    }
    while (front != NULL) { //  untuk mengulang melalui seluruh antrian dan menampilkan nama pembelian dari setiap elemen antrian.
        cout << "|  " << front->data.konfirmasi_nama << endl;
        front = front->next; // untuk menggeser pointer front ke elemen berikutnya dalam antrian 
							 // sehingga bisa melanjutkan dengan data riwayat berikutnya
    }
    cout << "====================================================" << endl;
}

// void untuk mengedit data properti admin dan edit nya berdasarkan id properti yang dipilih
void menu_3_admin() {
	Data_Properti_Admin* new_data = new Data_Properti_Admin();
	
    // Periksa apakah daftar properti kosong, jika kosong akan kembali ke menu utama admin
    if (head == NULL) {
        cout << "Daftar properti masih kosong. Tambahkan data terlebih dahulu." << endl;
        return;
    }

    // Tampilkan daftar properti terlebih dahulu
    menu_2a_admin();

    int id_properti;
    cout << "Masukkan ID properti yang ingin diedit: ";
    cin >> id_properti;

    // Cari data properti berdasarkan ID
    Data_Properti_Admin* properti_terpilih = head;
    while (properti_terpilih != NULL) { // untuk mencari data properti berdasarkan ID yang diinginkan.
        if (properti_terpilih->id_properti_admin == id_properti) {
            break;
        }
        properti_terpilih = properti_terpilih->next;
    }

    // Jika properti tidak ditemukan, tampilkan pesan kesalahan
    if (properti_terpilih == NULL) { 
        cout << "ID properti tidak ditemukan." << endl;
        return;
    }

    // Tampilkan data properti yang akan diedit
    cout << "\n\n------------------=============================-------------------" << endl;
    cout << "==================    DATA YANG AKAN DIEDIT:   ================== " << endl;
    cout << "------------------=============================-------------------" << endl;
    cout << "|              Nama Properti: " << properti_terpilih->nama_properti_admin << endl;
    cout << "|  	       ID Properti: " << properti_terpilih->id_properti_admin << endl;
    cout << "|              Jenis Properti: " << properti_terpilih->jenis_properti_admin << endl;
    cout << "|              Harga Properti: " << properti_terpilih->harga_properti_admin << endl;
    cout << "|              Harga Cicilan Per Bulan: " << properti_terpilih->harga_cicilan_perbulan << endl;
    cout << "|              Uang Muka: " << properti_terpilih->uang_muka << endl;
	cout << "==================================================================" << endl;
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "==================================================================" << endl;
	
    // Data berdasarkan id ditemukan, dan mulai memasukkan perubahan data didalamnya lengkap dengan semua error handling
    cout << "\nMasukkan nama properti: ";
    cin.ignore();
    do {
        getline(cin, properti_terpilih->nama_properti_admin);
        if (properti_terpilih->nama_properti_admin.empty() || properti_terpilih->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
            cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan nama properti: ";
            cin.clear();
        }
    } while (properti_terpilih->nama_properti_admin.empty() || properti_terpilih->nama_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);

    cout << "\nMasukkan ID properti: ";
	int idPropertiInput;
	bool idSudahAda = false;
	
	do {
	    cin >> idPropertiInput;
	    idSudahAda = false; // Nolkan flag ini setiap kali pengguna memasukkan ID baru
	
	    // Periksa apakah ID sudah ada dalam daftar
	    Data_Properti_Admin* current = head;
	    while (current != NULL) {
	        if (current->id_properti_admin == idPropertiInput) {
	            idSudahAda = true;
	            cout << "ID properti sudah ada. Masukkan ID properti yang berbeda: ";
	            break; // Keluar dari loop saat ID sudah ada
	        }
	        current = current->next;
	    }
	
	    if (cin.fail() || idPropertiInput <= 0) {
	        if (cin.fail()) {
	            cout << "Masukkan hanya boleh angka. Masukkan ID properti: ";
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        } else if (idPropertiInput <= 0) {
	            cout << "Masukkan angka lebih dari 0. Masukkan ID properti: ";
	        }
	    }
	
	    if (cin.peek() == '\n' && !idSudahAda) { 
	        break;
	    }
	} while (cin.fail() || idPropertiInput <= 0 || idSudahAda);
	
	if (!cin.fail()) {
	    new_data->id_properti_admin = idPropertiInput;
	}

    cout << "\nMasukkan jenis properti: ";
    cin.ignore();
    do {
        getline(cin, properti_terpilih->jenis_properti_admin);
        if (properti_terpilih->jenis_properti_admin.empty() || properti_terpilih->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
            cout << "Masukkan hanya boleh huruf dan tidak boleh kosong. Masukkan jenis properti: ";
            cin.clear();
        }
    } while (properti_terpilih->jenis_properti_admin.empty() || properti_terpilih->jenis_properti_admin.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos);

    cout << "\nMasukkan harga properti: ";
    do {
        cin >> properti_terpilih->harga_properti_admin;
        if (cin.fail() || properti_terpilih->harga_properti_admin <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga properti: ";
            }
            if (cin.peek() == '\n') {  
                cout << "Masukkan tidak boleh kosong. Masukkan harga properti: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || properti_terpilih->harga_properti_admin <= 0);

    cout << "\nMasukkan harga cicilan per bulan: ";
    do {
        cin >> properti_terpilih->harga_cicilan_perbulan;
        if (cin.fail() || properti_terpilih->harga_cicilan_perbulan <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan harga cicilan per bulan: ";
            }
            if (cin.peek() == '\n') { 
                cout << "Masukkan tidak boleh kosong. Masukkan harga cicilan per bulan: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || properti_terpilih->harga_cicilan_perbulan <= 0);

    cout << "\nMasukkan uang muka: ";
    do {
        cin >> properti_terpilih->uang_muka;
        if (cin.fail() || properti_terpilih->uang_muka <= 0) {
            if (cin.fail()) {
                cout << "Masukkan hanya boleh angka. Masukkan uang muka:";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cout << "Masukkan angka lebih dari 0. Masukkan uang muka: ";
            }
            if (cin.peek() == '\n') {  
                cout << "Masukkan tidak boleh kosong. Masukkan uang muka: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } while (cin.fail() || properti_terpilih->uang_muka <= 0);

    cout << "\n|======================================================|" << endl;
    cout << "| Data properti berhasil diperbarui pada daftar!        |" << endl;
    cout << "|======================================================|" << endl;
}

// void untuk hapus data properti admin diawal
void hapus_data_di_awal() {
    // Periksa apakah daftar properti masih kosong
    if (head == NULL) { // untuk memeriksa apakah data nya kosong
        cout << "\nDaftar properti masih kosong. Tambahkan data properti terlebih dahulu." << endl;
        return;
    }

    Data_Properti_Admin* properti_terpilih = head; // untuk menginisialisasi pointernya dengan elemen pertama yaitu head
    head = head->next; // Memindahkan pointer head ke elemen berikutnya dalam daftar properti
					  // sehingga elemen yang sebelumnya menjadi elemen pertama sekarang tidak lagi ada dalam daftar.

    if (head != NULL) {
        head->prev = NULL;
    }

    delete properti_terpilih;
    total_data_properti--;
    num_properti--;

    cout << "\n|======================================================|" << endl;
    cout << "| Data properti berhasil dihapus pada awal daftar!     |" << endl;
    cout << "|======================================================|" << endl;
}

// void untuk hapus data properti admin ditengah
void hapus_data_di_tengah() {
    // Periksa apakah daftar properti masih kosong
    if (head == NULL) {
        cout << "\nDaftar properti masih kosong. Tambahkan data properti terlebih dahulu." << endl;
        return;
    }

    // Tampilkan daftar properti terlebih dahulu
    menu_2a_admin();

    // Periksa apakah ada cukup elemen yang dapat dihapus di tengah
    if (total_data_properti <= 2) {
        cout << "\nTidak cukup data untuk menghapus di tengah." << endl;
        return;
    }

    int posisi;
    cout << "Masukkan posisi (Dari posisi 2 - posisi (Sebelum jika data tidak 2) " << total_data_properti - 1 << " dari total " << total_data_properti << " data) untuk menghapus properti di tengah: ";
    cin >> posisi;

    if (posisi < 2 || posisi > total_data_properti) {
        cout << "Posisi tidak valid." << endl;
        return;
    }

    Data_Properti_Admin* properti_terpilih = head;
    Data_Properti_Admin* properti_sebelumnya = NULL;

    for (int i = 1; i < posisi; ++i) {
        properti_sebelumnya = properti_terpilih;
        properti_terpilih = properti_terpilih->next;
    }

    // Hapus data properti yang ditemukan
    if (properti_terpilih == head) {
        // Hapus data properti di awal
        head = properti_terpilih->next;
        if (head != NULL) {
            head->prev = NULL;
        }
    } else if (properti_terpilih == tail) {
        // Hapus data properti di akhir
        tail = properti_sebelumnya;
        tail->next = NULL;
    } else {
        // Hapus data properti selain di awal dan akhir
        properti_sebelumnya->next = properti_terpilih->next;
        properti_terpilih->next->prev = properti_sebelumnya;
    }

    delete properti_terpilih;
    total_data_properti--;
    num_properti--;

    // Memperbarui posisi setelah penghapusan
    Data_Properti_Admin* posisi_terbaru = head; // Mulai dari elemen pertama
    for (int i = 1; posisi_terbaru != NULL; ++i) {
        posisi_terbaru->posisi = i;
        posisi_terbaru = posisi_terbaru->next;
    }

    cout << "\n|======================================================|" << endl;
    cout << "| Data properti berhasil dihapus pada posisi tengah!  |" << endl;
    cout << "|======================================================|" << endl;
}

// void untuk hapus data properti admin di akhir
void hapus_data_di_akhir() {
    // Periksa apakah daftar properti masih kosong
    if (head == NULL) {
        cout << "\nDaftar properti masih kosong. Tambahkan data properti terlebih dahulu." << endl;
        return;
    }

    // Jika hanya ada satu data dalam daftar
    if (head->next == NULL) {
        cout << "\nData tidak dapat dihapus dari daftar karena hanya ada satu." << endl;
        return;
    }

    // Temukan data tail
    Data_Properti_Admin* data_tail = tail;

    // Update tail ke data sebelumnya
    tail = data_tail->prev;
    tail->next = NULL;

    // Hapus data tail
    delete data_tail;

    total_data_properti--;
    num_properti--;

    cout << "Data properti berhasil dihapus dari akhir daftar." << endl;
}

// void untuk hapus data properti admin dan hapus menggunakan operasi queue riwayat pembelian
void menu_4_admin(){
		int pilihan;

    do {
        cout << "\nx=====================================================================x" << endl;
        std::cout << "|     	        	";
        std::cout << "\033[0;32m"; std::cout << "  MENU HAPUS DATA ADMIN "; std::cout << "\033[0m"; 
        std::cout << "                      |" << std::endl;
        cout << "x=====================================================================x" << endl;
        cout << "|                                                                     |" << endl;
        cout << "|       1. Hapus Data Properti Yang Dijual                            |" << endl;
        cout << "|       2. Dequeue Riwayat Pembelian Customer                         |" << endl;
        cout << "|       3. Back                                                       |" << endl;
        cout << "|                                                                     |" << endl;
        cout << "x=====================================================================x" << endl;
        cout << "\nSilahkan pilih menu utama admin [1-3]: ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\n \n" << "1. Hapus Data Properti Yang Dijual  \n"
            << "2. Dequeue Riwayat Pembelian Customer \n" 
            << "3. Back \n";
            std::cout << "\033[1;31m"; 
            std::cout << "\nSystem: ";
            std::cout << "\033[0m"; 
            std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
            continue;
        }   
    
        switch (pilihan) {
            case 1:
                menu_4a_admin(); // masuk ke void mau hapus data properti admin dengan diawal, tengah, atau akhir
                break;
            case 2: 
				menu_4b_admin_dequeue(&front); // menggunakan parameter front untuk menghapus data pada queue sesuai prinsip fifo
				break;
			case 3: // kembali ke menu sebelumnya
				break;        
            default:
                cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 3); 
}

// void untuk hapus data properti admin diawal, tengah, dan akhir
void menu_4a_admin(){
    int pilihan;
    
    do {
        cout << "\nx=====================================================================x" << endl;
        std::cout << "|     	    	";
        std::cout << "\033[0;33m"; std::cout << "      MENU HAPUS PENJUALAN ADMIN "; std::cout << "\033[0m"; 
        std::cout << "                     |" << std::endl;
        cout << "x=====================================================================x" << endl;
        cout << "|                                                                     |" << endl;
        cout << "|       1. Hapus Data Properti Yang Dijual di awal daftar             |" << endl;
        cout << "|       2. Hapus Data Properti Yang Dijual di tengah daftar           |" << endl;
        cout << "|       3. Hapus Data Properti Yang Dijual di akhir daftar            |" << endl;
        cout << "|       4. Back                                                       |" << endl;
        cout << "|                                                                     |" << endl;
        cout << "x=====================================================================x" << endl;
        cout << "\nSilahkan pilih menu utama admin [1-4]: ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\nMenu hanya terdiri dari: \n" << "1. Hapus Data Properti Yang Dijual di awal daftar\n"
            << "2. Hapus Data Properti Yang Dijual di tengah daftar  \n" 
            << "3. Hapus Data Properti Yang Dijual di akhir daftar\n"
            << "4. Back";
            std::cout << "\033[1;31m"; // cetak teks dengan warna
            std::cout << "\nSystem: ";
            std::cout << "\033[0m";  // kembalikan warna ke awal
            std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
            continue;
        }   
    
        switch (pilihan) {
            case 1:
                hapus_data_di_awal();
                break;
            case 2: 
				hapus_data_di_tengah();
				break;
			case 3: 
				hapus_data_di_akhir();
				break;
            case 4:
                break;
        
            default:
                cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 4);	
}	

// void untuk dequeue nama konfirmasi sesuai prinsip fifo ( first in first out )
void menu_4b_admin_dequeue(Node_nama **front) {
    if (*front == NULL) {
        cout << "\n----------------------------------------" << endl;
        cout << "Tidak Ada Data dalam Riwayat Pembelian" << endl;
        cout << "----------------------------------------" << endl;
        return;
    }

    Node_nama *temp = *front;    // Simpan alamat node pertama
    *front = (*front)->next;    // Pindahkan pointer front ke node berikutnya
    delete temp;                // Hapus node pertama yang disimpan dalam 'temp'

    cout << "\n======================================================================" << endl;
    cout << "|       Node pertama pada riwayat pembelian berhasil dihapus         |" << endl;
    cout << "======================================================================" << endl;
}


// ====================================================================================================================================
// 																BAGIAN SEMUA USER
// ====================================================================================================================================

// Prototype bagian user
void login_user(), register_user(), menu_utama_user();

// void ketika memilih login program dengan user
void user(){
	int pilihan_menu_user;
	
	do {
		std::cout << "\033[1;31m"; // cetak teks dengan warna
		std::cout << "\nSystem: ";
		std::cout << "\033[0m";  // kembalikan warna ke semula
		std::cout << "Hey, welcome user. Create a account with login or register!\n" << std::endl; // pesan agar lebih keren dan menarik
		
		cout << "x====================================================x" << endl;
		std::cout << "|     	    	   |";
		std::cout << "\033[1;93m"; std::cout << " Menu Login User  "; std::cout << "\033[0m"; std::cout << "|              |" << std::endl;		
		cout << "x====================================================x" << endl;
		cout << "|                                                    |" << endl;
		cout << "|               1. Login with Account                |" << endl;
		cout << "|               2. Register 		             |" << endl;
		cout << "|                                                    |" << endl;
		cout << "x====================================================x" << endl;
		cout << "\nSilahkan pilih menu login user [1/2]: ";
		
		if (!(cin >> pilihan_menu_user)) {
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	            cout << "\nMenu hanya terdiri dari: \n" << "1. Login with Account \n"
				<< "2. Login Register\n"; 
				std::cout << "\033[1;31m"; 
				std::cout << "\nSystem: ";
				std::cout << "\033[0m"; 
				std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
	            continue;
            } 
            
            switch (pilihan_menu_user) {
            case 1:
            	tekan_enter(); // void untuk enter sebelum masuk ke void selanjutnya
        		bersihkan(); // output sebelumnya dibersihkan
				login_user(); // masuk ke menu login user
                break;
            case 2:
                tekan_enter(); // void untuk enter sebelum masuk ke void selanjutnya
				register_user(); // masuk ke menu register user
				break; 
			default:
				cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
			    break;
			}
} while (pilihan_menu_user !=2);
}

// void untuk login user dengan memasukkan username dan password yang sudah diregistrasikan ke dalam database csv
void login_user() {
    string input_username_user, input_password_user;
    Stack pembelianStack;

    bool login_berhasil = false; // Variabel untuk menandai apakah login berhasil

    std::cout << "\033[1;31m"; 
    std::cout << "\nSystem: ";
    std::cout << "\033[0m"; 
    std::cout << "Log in to Your Account! \n" << std::endl;
    
    cout << "x======================================x" << endl;
    std::cout << "|    ";
    std::cout << "\033[1;93m"; std::cout << "        Menu Login User  "; std::cout << "\033[0m"; std::cout << "         |" << std::endl;    
    cout << "x======================================x" << endl;
    cout << "|                                      |" << endl;
    cout << "|   USERNAME = .....                   |" << endl;
    cout << "|                                      |" << endl;
    cout << "|   PASSWORD = .....                   |" << endl;
    cout << "|                                      |" << endl;
    cout << "|                                      |" << endl;
    cout << "x======================================x" << endl;    
    cout << "\nMasukkan Username: ";
    cin >> input_username_user;
    cout << "Masukkan Password: ";
    cin >> input_password_user;

    // Buka file database_akun_user.csv untuk memeriksa nya
    ifstream file("database_akun_user.csv");

    if (file.is_open()) { // jika file dapat dibuka
        string line;

        while (getline(file, line)) {
            // Parsing baris dalam format "username,password"
            std::istringstream ss(line);
            string username, password;
            getline(ss, username, ',');
            getline(ss, password, ',');

            if (username == input_username_user && password == input_password_user) {
                login_berhasil = true; // Set login_berhasil menjadi true
                
                bersihkan();
                std::cout << "\033[1;31m"; 
                std::cout << "\nSystem: ";
                std::cout << "\033[0m"; 
                std::cout << "Login berhasil!" << std::endl;
                
                // menampilkan username dan password yang didaftarkan
                cout << "\nx======================================x" << endl;
                std::cout << "|    ";
                std::cout << "\033[1;93m"; std::cout << "           YOUR ACCOUNT  "; std::cout << "\033[0m"; std::cout << "         |" << endl;    
                cout << "x======================================x" << endl;
                cout << "|                                      |" << endl;
                cout << "|   YOUR USERNAME = " << input_username_user <<  "               |" << endl;
                cout << "|                                      |" << endl;
                cout << "|   YOUR PASSWORD = " << input_password_user << "               |" << endl;
                cout << "|                                      |" << endl;
                cout << "|                                      |" << endl;
                cout << "x======================================x\n" << endl;    
                break;
            }
        }
        file.close(); // tutup file setelah selesai

        if (!login_berhasil) {
            cout << "Login gagal. Username atau password tidak cocok.\n";
            return; // Menghentikan eksekusi setelah login gagal
        }
    } else {
        cout << "Gagal membuka file database_akun_user.csv.\n";
        return; // Menghentikan eksekusi jika terjadi kesalahan
    }

    if (login_berhasil) {
    }
    menu_utama_user();
}

// void untuk register user mendaftarkan username dan passwordnya
void register_user() {
    string input_username_user, input_password_user;

    cout << "\nx====================================================x" << endl;
    std::cout << "|     	    	 ";
    std::cout << "\033[95m"; std::cout << " Create a New Account "; std::cout << "\033[0m"; 
    std::cout << "              |" << std::endl;
    cout << "x====================================================x" << endl;
    cout << "|                                                    |" << endl;
    cout << "|          Your Username is Here : .....               |" << endl;
    cout << "|      	   Your Password is Here : *****             |" << endl;
    cout << "|                                                    |" << endl;
    cout << "x====================================================x" << endl;
    
    cout << "\nMasukkan username baru: ";
    cin >> input_username_user;
    cout << "Masukkan password: ";
    cin >> input_password_user;

    // Membuka file CSV
    ofstream file("database_akun_user.csv", ios::app);

    if (file.is_open()) {
        // Menulis data ke dalam file CSV
        file << input_username_user << "," << input_password_user << endl;

        // Menutup file
        file.close();

        std::cout << "\033[1;31m"; 
        std::cout << "\nSystem: ";
        std::cout << "\033[0m"; 
        std::cout << "Akun berhasil didaftarkan ke dalam database_akun_user.csv. Registrasi Berhasil!" << std::endl;
        user(); // masuk ke menu user
        
    } else {
    	
        std::cout << "\033[1;31m"; 
        std::cout << "\nSystem: ";
        std::cout << "\033[0m"; 
        std::cout << "Maaf terjadi kesalahan! Silahkan coba lagi" << std::endl;
    }
}

// void operasi stack untuk masukkan data pesanan user tetapi dengan membuat node baru dulu
void push_data_user(Stack& pembelianStack, Data_Pembelian_User data) {
    Node* newNode = new Node;        // Membuat node baru
    newNode->data = data;            // Menyimpan data pesanan ke dalam node
    newNode->next = pembelianStack.top;  // Menghubungkan node baru ke node teratas stack
    pembelianStack.top = newNode;    // Mengatur node baru sebagai node teratas stack
}

// void untuk menampilkan atau mendisplay data pesanan user dan ini terisi sesuai prinsip stack yaitu lifo (last in first out) otomatis data baru akan selalu diatas
void display(Node* top) {
    if (top == NULL) {
        cout << "\nDaftar Pesanan Kosong!" << endl;
    } else {
    	cout << "\n=======================================================" << endl;
        cout << "|              DAFTAR PESANAN PROPERTI:  " << endl;
        cout << "=======================================================" << endl;
        while (top != NULL) {
            cout << "|  Nama Properti: " << top->data.nama_properti_user << endl;
            cout << "|  ID Properti: " << top->data.id_properti_user << endl;
            cout << "|  Jenis Properti: " << top->data.jenis_properti_user << endl;
            cout << "|  Harga Properti: Rp." << top->data.harga_properti_user << endl;
            cout << "|  Harga Cicilan Per Bulan: Rp." << top->data.harga_cicilan_perbulan << endl;
            cout << "|  Uang Muka: Rp." << top->data.uang_muka << endl;
            cout << "=======================================================" << endl;
            top = top->next;
        }
        
    }
}

// void untuk operasi hapus pada stack data pesanan user dengan ini menghapus dengan prinsip lifo, data top akan dihapus setiap kali operasi pop
void pop(Node* &top, Data_Properti_Admin* &head) {
    if (top == NULL) {
        cout << "\nDaftar Pesanan tidak ada. Tidak ada pesanan yang dapat dihapus." << endl;
    } else {
        Node* temp = top;
        top = top->next;

        // Cari data properti admin yang sesuai dengan data yang dihapus dari keranjang
        Data_Pembelian_User pembelian = temp->data;
        Data_Properti_Admin* propertiBaru = new Data_Properti_Admin;
        propertiBaru->nama_properti_admin = pembelian.nama_properti_user;
        propertiBaru->id_properti_admin = pembelian.id_properti_user;
        propertiBaru->jenis_properti_admin = pembelian.jenis_properti_user;
        propertiBaru->harga_properti_admin = pembelian.harga_properti_user;
        propertiBaru->harga_cicilan_perbulan = pembelian.harga_cicilan_perbulan;
        propertiBaru->uang_muka = pembelian.uang_muka;

        // Setelah membuat data properti baru, tambahkan ke daftar properti admin
        if (head != NULL) {
            head->prev = propertiBaru;
            propertiBaru->next = head;
        }
        head = propertiBaru;

        cout << "Properti dari keranjang belanja telah dihapus dan kembali ke daftar properti admin." << endl;
        
        // Tambahkan kode ini untuk memperbarui total_data_properti
        total_data_properti++;
        num_properti++;

        delete temp;
    }
}

// void untuk menambahkan data pesanan user dengan operasi stack push 
void push(Node* &top, Data_Properti_Admin** propertiList, Data_Properti_Admin* &head) {
    // Periksa apakah ada data properti admin
    if (head == NULL) {
        cout << "\nDaftar properti admin kosong. Tidak ada properti yang dapat dibeli." << endl;
    } else {
        // Meminta ID properti yang ingin ditambahkan dari pengguna
        int idProperti;

        menu_2a_admin();

        do {
            cout << "Masukkan ID properti yang ingin ditambahkan ke keranjang belanja: ";
            cin >> idProperti;
            
            if (cin.fail()) {
                cout << "Masukkan ID yang benar berupa angka!" << endl;
                cin.clear();  // Menghapus flag kesalahan
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer
            } else {
                break;
            }
        } while (true);

        Data_Pembelian_User pembelianBaru;
        bool propertiDitemukan = false;

        // Cari properti berdasarkan ID
        Data_Properti_Admin* propertiTerpilih = head;
        Data_Properti_Admin* prevProperti = NULL;

        while (propertiTerpilih != NULL) {
            if (propertiTerpilih->id_properti_admin == idProperti) {
                // Salin data properti ke data pembelian
                pembelianBaru.nama_properti_user = propertiTerpilih->nama_properti_admin;
                pembelianBaru.id_properti_user = propertiTerpilih->id_properti_admin;
                pembelianBaru.jenis_properti_user = propertiTerpilih->jenis_properti_admin;
                pembelianBaru.harga_properti_user = propertiTerpilih->harga_properti_admin;
                pembelianBaru.harga_cicilan_perbulan = propertiTerpilih->harga_cicilan_perbulan;
                pembelianBaru.uang_muka = propertiTerpilih->uang_muka;

                // Hapus properti dari daftar properti admin
                if (prevProperti != NULL) {
                    prevProperti->next = propertiTerpilih->next;
                } else {
                    head = propertiTerpilih->next;
                }

                if (propertiTerpilih->next != NULL) {
                    propertiTerpilih->next->prev = prevProperti;
                }

                propertiDitemukan = true;
                break;
            }
            prevProperti = propertiTerpilih;
            propertiTerpilih = propertiTerpilih->next;
        }

        if (propertiDitemukan) {
            Node* nodeBaru = newNode(pembelianBaru);

            // Tambahkan node baru ke atas stack
            nodeBaru->next = top;
            top = nodeBaru;

            cout << "\nProperti dengan ID " << idProperti << " berhasil ditambahkan ke keranjang belanja." << endl;
        } else {
            cout << "\nProperti dengan ID " << idProperti << " tidak ditemukan." << endl;
        }

        total_data_properti--; 
        num_properti--;
    }
}

// ====================================================================================================================
// BAGIAN SORTING HARGA PROPERTI DENGAN MERGE SORT
// ====================================================================================================================

// Prototipe fungsi untuk mendukung merge sort harga properti secara ascending
Data_Properti_Admin* findMiddle(Data_Properti_Admin* head);
Data_Properti_Admin* Merge(Data_Properti_Admin* left, Data_Properti_Admin* right, bool ascending);

// Prototipe fungsi untuk mendukung merge sort harga properti secara descending
Data_Properti_Admin* MergeSortAsc(Data_Properti_Admin* head);
Data_Properti_Admin* MergeSortDesc(Data_Properti_Admin* head);

// Implementasi fungsi MergeSort untuk mengurutkan secara ascending
Data_Properti_Admin* MergeSortAsc(Data_Properti_Admin* head) {
    if (!head || !head->next) {
        return head; // Daftar kosong atau hanya satu elemen
    }

    // Temukan tengah daftar 
    Data_Properti_Admin* mid = findMiddle(head);

    // Bagian memisahkan daftar menjadi dua bagian
    Data_Properti_Admin* left = head;
    Data_Properti_Admin* right = mid->next;
    mid->next = NULL; // Pisahkan daftar menjadi dua

    // Rekursi untuk mengurutkan kedua bagian
    left = MergeSortAsc(left);
    right = MergeSortAsc(right);

    // Gabungkan dua daftar kembali yang sudah diurutkan
    return Merge(left, right, true);
}

// Implementasi fungsi MergeSort untuk mengurutkan secara descending
Data_Properti_Admin* MergeSortDesc(Data_Properti_Admin* head) {
    // Panggil MergeSortAsc untuk mengurutkan secara ascending
    head = MergeSortAsc(head);
    
    // Balikkan daftar untuk menghasilkan urutan descending
    Data_Properti_Admin* prev = NULL;
    Data_Properti_Admin* current = head;
    Data_Properti_Admin* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    head = prev;
    
    return head;
}

// Fungsi bantu untuk mencari tengah daftar
Data_Properti_Admin* findMiddle(Data_Properti_Admin* head) {
    if (!head) {
        return NULL;
    }

    Data_Properti_Admin* slow = head;
    Data_Properti_Admin* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Implementasi fungsi Merge Sort fokus untuk menggabungkan kembali
Data_Properti_Admin* Merge(Data_Properti_Admin* left, Data_Properti_Admin* right, bool ascending) {
    Data_Properti_Admin* merged = NULL;

    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }

    if ((ascending && left->harga_properti_admin <= right->harga_properti_admin) ||
        (!ascending && left->harga_properti_admin >= right->harga_properti_admin)) {
        merged = left;
        merged->next = Merge(left->next, right, ascending);
    } else {
        merged = right;
        merged->next = Merge(left, right->next, ascending);
    }

    return merged;
}

// prototype data properti admin head untuk mendukung operasi searching nama properti
int count_properties(Data_Properti_Admin* head);

// ====================================================================================================================
// BAGIAN SEARCHING NAMA PROPERTI DENGAN JUMP SEARCHING
// ====================================================================================================================

// Fungsi jump searching untuk mencari nama properti
int jumpSearchByPropertyName(Data_Properti_Admin* head, const string& targetPropertyName) {
    if (head == NULL) {
        cout << "Data properti masih kosong." << endl;
        return -1;
    }

    int n = 0;
    Data_Properti_Admin* current = head;
    bool found = false;
    int prev = 0;

    while (current != NULL) {
        n++;
        current = current->next;
    }

    int step = sqrt(n);
    int idx = min(step, n) - 1;
    current = head;

    while (current != NULL && current->nama_properti_admin < targetPropertyName) {
        prev = step;
        step += sqrt(n);
        idx = min(step, n) - 1;

        int i = 0;
        while (i < idx) {
            if (current->next != NULL) {
                current = current->next;
                i++;
            } else {
                break;
            }
        }
    }

    // Melakukan pencarian linear dari posisi sebelumnya
    while (current != NULL) {
        if (current->nama_properti_admin == targetPropertyName) {
            if (!found) {
                cout << "\n>>  Data berhasil ditemukan: " << endl;
                found = true;
            }
            cout << "===========================================================" << endl;
            cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
            cout << "===========================================================" << endl;
            cout << "|   Nama Properti: " << current->nama_properti_admin << endl;
            cout << "|   ID Properti: " << current->id_properti_admin << endl;
            cout << "|   Jenis Properti: " << current->jenis_properti_admin << endl;
            cout << "|   Harga Properti: Rp." << current->harga_properti_admin << endl;
            cout << "|   Harga Cicilan Per Bulan: Rp." << current->harga_cicilan_perbulan << endl;
            cout << "|   Uang Muka: Rp." << current->uang_muka << endl;
            cout << "===========================================================" << endl;
            cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
            cout << "===========================================================\n" << endl;
        }
        current = current->next;
        prev++;
    }

    if (!found) {
        cout << "Data tidak ditemukan." << endl;
    }

    return -1;
}


void menu_sorting_harga_properti() {
    int pilihan;

    // Periksa apakah daftar properti kosong
    if (head == NULL) {
        cout << "Daftar properti masih kosong. Tambahkan data terlebih dahulu." << endl;
        return;
    }

    do {
    	cout << ">>   Merge Sort" << endl;
        cout << "\nx===========================================================x" << endl;
        std::cout << "|       ";
        std::cout << "\033[95m"; std::cout << " SORTING NAMA DATA PROPERTI ADMIN DENGAN: "; std::cout << "\033[0m"; 
        std::cout << "          |" << std::endl;
        cout << "x===========================================================x" << endl;
        cout << "|                                                           |" << endl;
        cout << "|       1. Sorting Harga Properti secara Ascending          |" << endl;
        cout << "|       2. Sorting Harga Properti secara Descending         |" << endl;
        cout << "|       3. Back   					    |" << endl;
        cout << "|                                                           |" << endl;
        cout << "x===========================================================x" << endl;
        cout << "\nSilahkan pilih menu data  [1-3]: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n \n" << "1. l \n"
            << "2. \n" <<
            std::cout << "\033[1;31m"; 
            std::cout << "\nSystem: ";
            std::cout << "\033[0m"; 
            std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
            continue;
        }   

        switch(pilihan) {
            case 1:
                head = MergeSortAsc(head);
                cout << "\nData properti Admin berhasil disorting berdasarkan nama secara ascending!" << endl;
                break;
            case 2:    
                head = MergeSortDesc(head);
                cout << "\nData properti Admin berhasil disorting berdasarkan nama secara descending!" << endl;
                break;
            case 3:
                // Kembali ke menu sebelumnya
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 3);
}

// Void untuk input nama properti yang mau disearching
void input_searching_nama_properti() {
    if (head == NULL) {
        cout << "Daftar properti masih kosong. Tambahkan data terlebih dahulu." << endl;
        return;
    }

    menu_2a_admin(); // Menampilkan data properti

    string targetPropertyName;
    cout << "Masukkan nama properti yang ingin dicari: ";
    cin.ignore(); // Membersihkan buffer sebelum menggunakan getline
    getline(cin, targetPropertyName);

    // Lakukan pencarian menggunakan Jump Search
    int result = jumpSearchByPropertyName(head, targetPropertyName);

    if (result == -1) {
        cout << "Operasi berhasil!" << endl;
    }
}

// void untuk mau tampilkan data properti admin biasa, disorting, dan disearching untuk memudahkan user menemukan data yang diinginkan
void tampilkan_data_properti() {
    int pilihan;

    do {
        cout << "\nx===============================================================x" << endl;
        std::cout << "|           |";
        std::cout << "\033[0;33m"; std::cout << " TAMPILKAN DATA PROPERTI ADMIN DENGAN:  "; std::cout << "\033[0m"; std::cout << "|          |" << std::endl;
        cout << "x===============================================================x" << endl;
        cout << "|                                                               |" << endl;
        cout << "|        1. Tampilkan Data Properti Admin                       |" << endl;
        cout << "|        2. Sorting Data Properti Admin berdasarkan harga       |" << endl;
        cout << "|        3. Searching Data Properti Admin berdasarkan nama      |" << endl;
        cout << "|        4. Back                                                |" << endl;
        cout << "|                                                               |" << endl;
        cout << "x===============================================================x" << endl;
        cout << "\nSilahkan pilih menu data  [1-4]: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nMenu hanya terdiri dari: \n"
                 << "1. Tampilkan Data Properti Yang Dijual \n"
                 << "2. Sorting Data Properti Admin berdasarkan harga properti\n"
                 << "3. Searching Data Properti Admin berdasarkan nama properti\n";
            cout << "\033[1;31m"; 
            cout << "\nSystem: ";
            cout << "\033[0m"; 
            cout << "Maaf Silahkan coba lagi\n" << endl;
            continue;
        }

        switch(pilihan) {
            case 1:
                menu_2a_admin(); // void untuk menampilkan data properti admin
                break;
            case 2:
                menu_sorting_harga_properti(); // void untuk melakukan sorting harga properti
                break;
            case 3:
                input_searching_nama_properti(); // void untuk melakukan searching nama properti
				break;
            case 4:
                break; // kembali ke menu sebelumnya
            default:
                cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
                break;
        }

        if (pilihan == 4) {
            break;
        }
    } while (true);
}

// void untuk membuat node pada nama riwayat pembelian menggunakan parameter pada queue yaitu front dan rear
void input_nama_riwayat_pembelian(Node_nama** front, Node_nama** rear) {
    Node_nama *nodeBaru = newNode();  // Membuat node baru dengan error handling dan looping

    // Menambahkan node baru ke dalam queue
    if (*front == NULL) {
        // Jika antrian kosong, node baru menjadi elemen pertama dan terakhir
        *front = nodeBaru;
        *rear = nodeBaru;
    } else {
        // Jika antrian tidak kosong, node baru disambungkan ke elemen terakhir dan dijadikan elemen terakhir
        (*rear)->next = nodeBaru;
        *rear = nodeBaru;
    }
}

// void untuk pembayaran cash, ketika selesai semua data pesanan dihapus karena sudah melakukan pembayaran
void pembayaran_cash(Node_nama** front, Node_nama** rear, Node* top, Node** display_top) {
	bersihkan();
	
    if (top == NULL) {
        cout << "Belum ada data properti yang dimasukkan." << endl;
    } else {
        int total_pembayaran = 0; // Inisialisasi total pembayaran
		
        // Menampilkan data properti yang Anda pesan
        cout << "Transaksi dengan Cash\n" << endl;
        cout << "=================================================" << endl;
        cout << "|        Data properti yang Anda pesan:         |"  << endl;
        cout << "=================================================" << endl;
        while (top != NULL) {
            cout << "|   Nama Properti  : " << top->data.nama_properti_user << endl;
            cout << "|   ID Properti    : " << top->data.id_properti_user << endl;
            cout << "|   Jenis Properti : " << top->data.jenis_properti_user << endl;
            cout << "|   Harga Properti : Rp." << top->data.harga_properti_user << endl;
            cout << "=================================================" << endl;

            // Menambahkan harga properti ke total pembayaran
            total_pembayaran += top->data.harga_properti_user;

            top = top->next;
        }

        // Menampilkan total pembayaran
        cout << "\nTotal Pembayaran Anda adalah: Rp." << total_pembayaran << endl;
        cout << "\nTERIMA KASIH TELAH BELANJA DI TEMPAT KAMI ;}" << endl;
        cout << "Jangan lupa jika anda, teman anda, keluarga anda membutuhkan tempat yang modern dan elegan, segeralah datang ke agensi kami!!!" << endl;
        cout << "\nLo Siento User, semoga anda sekeluarga diberkati selalu selamanya" << endl;

        // Hapus semua isi keranjang belanja riwayat pembelian
        *front = NULL;
        *rear = NULL;
        *display_top = NULL; // Hapus data dari tampilan pesanan juga

    }
}

// void untuk pembayaran kpr, sama dengan cash jika sudah melakukan pembayaran semua data pesanan user dihapus
void pembayaran_kpr(Node_nama** front, Node_nama** rear, Node* top, Node** display_top) {
	bersihkan();
	
    if (top == NULL) {
        cout << "Belum ada data properti yang dimasukkan." << endl;
    } else {
        int total_cicilan = 0; // Inisialisasi total cicilan
        int total_uang_muka = 0; // Inisialisasi total uang muka

        // Menampilkan data properti yang dipesan oleh pengguna
        cout << "Transaksi dengan KPR\n" << endl;
        cout << "=================================================" << endl;
        cout << "|        Data properti yang Anda pesan:         |"  << endl;
        cout << "=================================================" << endl;
        while (top != NULL) {
            cout << "|   Nama Properti  : " << top->data.nama_properti_user << endl;
            cout << "|   ID Properti    : " << top->data.id_properti_user << endl;
            cout << "|   Jenis Properti : " << top->data.jenis_properti_user << endl;
            cout << "|   Harga Properti : Rp." << top->data.harga_properti_user << endl;
            cout << "=================================================" << endl;
			
			// logika penghitungan total cicilan dan uang muka yang akan ditampilkan
            total_cicilan += (top->data.harga_cicilan_perbulan / 12) * 0.10;
            total_uang_muka += (top->data.uang_muka / 2);

            top = top->next;
        }

        // Menampilkan total cicilan dan total uang muka
        cout << "\nTotal Harga Cicilan Perbulan: Rp." << total_cicilan << endl;
        cout << "Total Uang Muka: Rp. " << total_uang_muka << endl;
        cout << "Terima kasih telah belanja di agensi properti kami" << endl;
        cout << "\nLo Siento User, semoga anda sekeluarga diberkati selalu selamanya" << endl;

        // Hapus semua isi keranjang belanja riwayat pembelian
        *front = NULL;
        *rear = NULL;
        *display_top = NULL; // Hapus data dari tampilan pesanan juga

    }
}

// void untuk melakukan pembayaran secara cash atau kpr, berbeda dengan output yang ditampilkan
void menu_pembayaran(){
	int pilihan;
	
	do {
        cout << "\nx====================================================x" << endl;
        cout << "|                  LAKUKAN PEMBAYARAN DENGAN:        |" << endl;
        cout << "x====================================================x" << endl;
        cout << "|                                                    |" << endl;
        cout << "|  	1. Pembayaran Cash             	             |" << endl;
        cout << "|  	2. Pembayaran KPR                            |" << endl;
        cout << "|  	3. Batalkan pembayaran                       |" << endl;
        cout << "|                                                    |" << endl;
        cout << "x====================================================x" << endl;
        cout << "\nSilahkan pilih menu data  [1-3]: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n 1. Pembayaran Cash\n"
                 << "2. Pembayaran KPR \n"
                 << "3. Batalkan pembayaran \n";
            cout << "\033[1;31m"; 
            cout << "\nSystem: ";
            cout << "\033[0m"; 
            cout << "Maaf Silahkan coba lagi\n" << endl;
            continue;
        }

        switch(pilihan) {
            case 1:
			    pembayaran_cash(&front, &rear, TOP, &TOP);
			    menu_utama_user();
			    break;
            case 2:
                pembayaran_kpr(&front, &rear, TOP, &TOP);
                menu_utama_user();
                break;
            case 3:
				break;
            default:
                cout << "\nPilihan Menu tidak valid. Silakan coba lagi." << endl;
                break;
        }

        // Tambahkan break di sini agar keluar dari loop do-while jika pilihan adalah 4
        if (pilihan == 3) {
            break;
        }
    } while (true);
}

// void untuk menu utama user, ketika berhasil login user
void menu_utama_user() {
    int pilihan = 0; // Inisialisasi pilihan
    bool sudah_bayar = false;

    do {
        std::cout << "\033[1;31m"; // cetak teks dengan warna
        std::cout << "\nSystem: ";
        std::cout << "\033[0m";  // kembalikan warna ke semula
        std::cout << "Hey, Welcome User. I Hope You Enjoy Your Day ;)" << std::endl;
        std::cout << "        Thanks for Coming!\n" << std::endl;

        cout << "x===========================================================================x" << endl;
        std::cout << "|     	             	      |";
        std::cout << "\033[1;93m"; std::cout << " Menu Utama User  "; std::cout << "\033[0m"; std::cout << "|                          |" << std::endl;       
        cout << "x===========================================================================x" << endl;
        cout << "|                                                                           |" << endl;
        cout << "|               1. Push data properti ke dalam pesanan                      |" << endl;
        cout << "|               2. Tampilkan data berbagai properti yang dijual             |" << endl;
        cout << "|               3. Tampilkan berbagai properti dalam pesanan                |" << endl;
        cout << "|               4. Pop data properti dalam pesanan                          |" << endl;
        cout << "|               5. Lakukan pembayaran                                       |" << endl;
        cout << "|               6. Logout Akun User                                         |" << endl;
        cout << "|               7. Exit                                                     |" << endl;
        cout << "|                                                                           |" << endl;
        cout << "x===========================================================================x" << endl;
        cout << "\nSilahkan pilih menu [1-7]: ";
        cin >> pilihan;

        if (cin.fail() || pilihan < 1 || pilihan > 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pilihan tidak valid. Masukkan angka antara 1 sampai 7." << endl;
        } else {
            switch (pilihan) {
                case 1:
                    push(TOP, &propertiList, head);
                    break;
                case 2:
                    tampilkan_data_properti();
                    break;
                case 3:
                    if (sudah_bayar) {
                        // Jika sudah bayar, hapus semua data dalam keranjang belanja
                        while (TOP != NULL) {
                            pop(TOP, head);
                        }
                        cout << "Keranjang belanja kosong setelah pembayaran." << endl;
                    } else {
                        // Jika belum bayar, tampilkan data pesanan
                        display(TOP);
                    }
                    break;
                case 4:
                    pop(TOP, head);
                    break;
                case 5:
                    if (sudah_bayar) {
                        cout << "Anda sudah melakukan pembayaran." << endl;
                    } else {
                        menu_pembayaran();
                        // Jika pembayaran berhasil dilakukan, tandai bahwa sudah bayar
                        sudah_bayar = true;
                    }
                    break;
                case 6:
                    // ketika memilih logout akun user, tapi belum melakukan pembayaran otomatis menghapus data pada pesanan user
                    while (TOP != NULL) {
                        // Ambil data pesanan dari keranjang belanja
                        Data_Pembelian_User pembelian = TOP->data;

                        // Buat data properti admin baru
                        Data_Properti_Admin* propertiBaru = new Data_Properti_Admin;
                        propertiBaru->nama_properti_admin = pembelian.nama_properti_user;
                        propertiBaru->id_properti_admin = pembelian.id_properti_user;
                        propertiBaru->jenis_properti_admin = pembelian.jenis_properti_user;
                        propertiBaru->harga_properti_admin = pembelian.harga_properti_user;
                        propertiBaru->harga_cicilan_perbulan = pembelian.harga_cicilan_perbulan;
                        propertiBaru->uang_muka = pembelian.uang_muka;

                        // Tambahkan data properti admin baru ke daftar properti admin
                        if (head != NULL) {
                            head->prev = propertiBaru;
                        }
                        propertiBaru->next = head;
                        propertiBaru->prev = NULL;
                        head = propertiBaru;

                        // Hapus data pesanan dari keranjang belanja
                        Node* temp = TOP;
                        TOP = TOP->next;
                        delete temp;
                    }

                    cout << "Anda telah logout. Data pesanan telah dikembalikan ke admin." << endl;
                    menu_utama();
                    break;
                case 7:
                    animasi_loading();
                    exit_program();
                    break;
            }
        }

    } while (pilihan != 7); // Keluar dari loop ketika pilihan adalah 7 (Exit)
}

// void tampilan utama mau login dengan admin atau user
void menu_utama(){
	int pilihan_menu_login;
	animasi_loading();
	
	do {
	    	cout << "\n\n>> Programs: Sistem Penjualan Aneka Properti\n" << endl;
	    	cout << "    0============================================0" << endl;
	    	cout << "  0================================================0" << endl;
			cout << "0====================================================0" << endl;
			cout << "|                _________|_|_________	             |" << endl;
			cout << "|________________|                   |_______________|" << endl;
			cout << "|________________|   Login Dengan:   |_______________|" << endl;
			cout << "|  		 |___________________|		     |" << endl;
			cout << "|   		          | |         		     |" << endl;
			cout << "0====================================================0" << endl;
			cout << "|                                                    |" << endl;
			cout << "|                     1. Admin                       |" << endl;
			cout << "|                     2. User                        |" << endl;
			cout << "|                     3. Exit                        |" << endl;
			cout << "|                                                    |" << endl;
			cout << "0====================================================0" << endl;
			cout << "\nSilahkan pilih menu login dengan [1-3]: ";

			if (!(cin >> pilihan_menu_login)) {
				bersihkan();
	            cin.clear();
	            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	            cout << "Menu hanya terdiri dari: \n" << "1. Login Admin \n"
				<< "2. Login User\n"; 
				std::cout << "\033[1;31m"; 
				std::cout << "\nSystem: ";
				std::cout << "\033[0m"; 
				std::cout << "Maaf Silahkan coba lagi\n" << std::endl;
	            continue;
            }
            
            switch (pilihan_menu_login) {
            case 1:
            	tekan_enter();
        		bersihkan();
            	admin();
                break;
            case 2:
                tekan_enter();
        		bersihkan();
        		user();
                break;
            case 3:
            	animasi_loading();
            	exit_program();
            	break;
            }
	} while (pilihan_menu_login !=3);
	
}	

// void inti sebagai tampilan program penjualan aneka properti yang keren dan atraktif
int main () {
        cout << "Welcome to Our Program, Dear Brothers!" << endl;
        cout << "Enjoy....\n" << endl;
		cout << "x===================================================================x" << endl;
        cout << "| * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * |" << endl;
        cout << "|* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *|" << endl;                                                                
        cout << "| * * * * * * * * +===============================+ * * * * * * * * |" << endl;
        std::cout << "|=================|"; std::cout << "\033[1;34m"; std:cout << "     Sistem ";
		std::cout << "\033[1;31m"; std::cout << "Penjualan "; std::cout << "\033[1;93m"; std::cout << "Aneka    ";
		std::cout << "\033[0m"; std::cout << "|=================|\n"; std::cout << "|* * * * * * * * *|";
		std::cout << "\033[1;32m"; std::cout << "            Properti.          "; std::cout << "\033[0m"; 
		std::cout << "|* * * * * * * * *|" << std::endl;
        cout << "| * * * * * * * * +===============================+ * * * * * * * * |" << endl;
        cout << "|* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *|" << endl;
        cout << "| * * * +===================================================+ * * * |" << endl;
        cout << "|* * * *|                   [  Our Team  ]                  |* * * *|" << endl;
        cout << "| * * * |  ===============================================  | * * * |" << endl;
        cout << "|* * * *|  [ 1. Gerry Hasrom         /       2209106094. ]  |* * * *|" << endl;
        cout << "| * * * |  [ 2. Rheza Gerard Altama  /       2209106103. ]  | * * * |" << endl;
        cout << "|* * * *|  [ 3. Azhar Nur Hakim      /       2209106113. ]  |* * * *|" << endl;
        cout << "| * * * +===================================================+ * * * |" << endl;
        cout << "|* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *|" << endl;
        cout << "| * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * |" << endl;
        cout << "x===================================================================x" << endl;
        cout << "\nTekan Enter Untuk Masuk ke Program: " << endl; // masuk ke program dengan menekan enter
        tekan_enter();
        bersihkan();
    	menu_utama();

    return 0;
}


// ====================================================================================================
// 		`<					TERIMA KASIH KAMI SEKELOMPOK UCAPKAN  ;}                    >
// ====================================================================================================

			
			























