#include <iostream>
using namespace std;

int main(){
	int x; //deklarasi elemen
	
	cout << "Masukan jumlah elemen: ";
	cin >> x; //input jumlah elemen array
	
	int arr[x];
	int *ptr = arr; //pointer menunjuk ke array
	
	for(int i = 0; i < x; i++){
			cout << *(ptr + i); 
		} // input nilai menggunakan array
		
	// inisialisasi max, min , dan jumlah
	int max = *ptr, min = *ptr, jumlah = 0; 
	
	for(int i = 0; i < x; i++){
			cout << *(ptr + i) << " "; // isi array
		
	if (*(ptr + i) > max) max = *(ptr + i); // maximum
	if (*(ptr + i) > min) min = *(ptr + i); // minimum
	
	jumlah += *(ptr + i); // hitung jumlah
		}
	
	float rata = (float)jumlah/x; // rumus hitung rata-rata
	
	cout << "\nNilai maximum: " << max;
	cout << "\nNilai minimum: " << min;
	cout << "\nJumlah       : " << jumlah;
	cout << "\nRata-rata    : " << rata;
	// menampilkan hasil akhir :)
	return 0;	
}
