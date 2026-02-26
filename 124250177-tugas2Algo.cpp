#include <iostream>
using namespace std;

struct Data{
	string nama;
	int harga;
	};
	
int main() {
	Data dataBuku[5] = {
		{"Kancil yang Bijak", 60000},
		{"Kisah Sang Kancil", 50000},
		{"Monyet Serakah", 60000},
		{"Pulang", 98000},
		{"Tentang Kamu", 110000},
		};
	
	string cari;
	int pilihan;
	
	cout << "Masukkan nama buku yang dicari: ";
	getline(cin, cari);
	
	cout << "=== PILIH METODE PENCARIAN BUKU ===" << endl;
	cout << "1. Sequential Search." << endl;
	cout << "2. Binary search." << endl;
	cout << "Pilih Metode: ";
	cin >> pilihan;
	
	if (pilihan == 1) { //with sequential search
		int i = 0;
		bool found = false;
		
		for(i = 0; i < 5; i++){
			if(dataBuku[i].nama == cari){
				found = true;
				break;
				} 
			}
		
	
	if(found) {
		cout << "Buku Ditemukan!" << endl;
		cout << "Harga: Rp." << dataBuku[i].harga << endl;
	} else {
		cout << "Buku tidak Ditemukan, Silahkan coba lagi" << endl;
		}
	}
	
	else if(pilihan == 2){ //with binary search
		int i = 0;
		int j = 4;
		int k;
		bool found = false;
		
		while((!found) && (i <= j)){
			k = (i + j)/2;
			
			if(dataBuku[k].nama == cari){
				found = true;
				break;
				} else if (cari < dataBuku[k].nama){
					j = k - 1;
					} else {
					i = k + 1;
				}
			}
		
	
	if (found){
		cout << "Buku Ditemukan!" << endl;
		cout << "Harga: Rp." << dataBuku[k].harga << endl;
	} else {
		cout << "Buku tidak Ditemukan, Silahkan coba lagi" << endl;
		}
	}	
}
	
	

