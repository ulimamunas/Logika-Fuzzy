#include <iostream>
#include <iomanip>

using namespace std;

void fuzzification(float x, float a, float b, float c, float &u1, float &u2, float &u3) {
    //variabel untuk menyimpan nilai keanggotaan
    float uLeft;  //nilai keanggotaan untuk setengah trapesium (kiri)
    float uCenter; //nilai keanggotaan untuk segitiga tengah
    float uRight; //nilai keanggotaan untuk setengah trapesium (kanan)

    //variabel untuk menyimpan nilai titik-titik batas himpunan fuzzy
    float left_a, left_b; //nilai  a dan b untuk trapesium kiri
    float center_a, center_b, center_c; //nilai a, b, dan c untuk segitiga tengah
    float right_a, right_b; //nilai a dan b untuk trapesium kanan

    //inisialisasi nilai titik-titik batas
    left_a = a;
    left_b = b;
    center_a = a;
    center_b = b;
    center_c = c;
    right_a = b;
    right_b = c;

    //fuzzy trapesium kiri
    if (x <= left_a) uLeft = 1;
    if (x > left_a && x < left_b) {
        uLeft = (left_b - x) / (left_b - left_a); //rumus turun
    }
    if (x >= left_b) uLeft = 0;

    //cout << "uLeft : " << uLeft << endl;   //to be replaced
    u1 = uLeft; //menyimpan nilai keanggotaan trapesium kiri

    //fuzzy segitiga tengah
    if (x <= center_a || x >= center_c) uCenter = 0;
    if (x > center_a && x < center_b) {
        uCenter = (x - center_a) / (center_b - center_a); //rumus naik
    }
    if (x == center_b) uCenter = 1;
    if (x > center_b && x < center_c) {
        uCenter = (center_c - x) / (center_c - center_b); //rumus turun
    }
    //cout << "uCenter : " << uCenter << endl;//to be replaced
    u2 = uCenter; //menyimpan nilai keanggotaan segitiga tengah

    //fuzzy trapesium kanan
    if (x <= right_a) uRight = 0;
    if (x > right_a && x < right_b) {
        uRight = (x - right_a) / (right_b - right_a); //rumus naik
    }
    if (x >= right_b) uRight = 1;
    //cout << "uRight : " << uRight << endl;//to be replaced
    u3 = uRight; //menyimpan nilai keanggotaan trapesium kanan
}

void and_rules(float f1, float f2, float temp, float &conclusion) {
    //aturan AND
    //f1 dan f2  adl nilai keanggotaan dari 2 kondisi
    if (f1 >= f2) temp = f2; else temp = f1; //membandingkan nilai f1 dan f2, jika f1 lebih besar/= f2 maka nilai temp menjadi f2
    if (temp >= conclusion) conclusion = temp; //membandingkan nilai temp dengan nilai conclusion, jika nilai temp lebih besar/= comclusion maka nilai conclusion diupdate dengan nilai temp
}

void determine_sample(float a, float b, float c, float d, float &s1, float &s2, float &s3) {  //from output fuzzy
    s1 = (a+b)/2; //menghitung nilai sample 1
    s2 = (b+c)/2; //menghitung nilai sample 2
    s3 = (c+d)/2; //menghitung nilai sample 3
}

void defuzzification(float u1, float u2, float u3, float s1, float s2, float s3, float &result) {
    result = ((u1*s1)+(u2*s2)+(u3*s3))/(u1+u2+u3); //menghitung jumlah dari ketiga nilai sample berdasarkan keanggotaan masing-masing dibagi dengan jumlah total nilai keanggotaan
}

int main()
{
    float x_stok, uSedikit, uLumayan, uBanyak; //stok barang
    float x_permintaan, uRendah, uStandar, uTinggi; //permintaan pelanggan
    float murah, normal, mahal; //harga
    float sample1, sample2, sample3; //untuk defuzzification
    float harga; //harga outcome
    cout << fixed << setprecision(2);

    cout << "Masukkan x untuk stok barang : ";
    cin >> x_stok;
    cout << "Masukkan x untuk permintaan pelanggan : ";
    cin >> x_permintaan;
    fuzzification(x_stok, 40, 60, 80, uSedikit, uLumayan, uBanyak); //stok barang
    fuzzification(x_permintaan, 40, 60, 80, uRendah, uStandar, uTinggi); //permintaan pelanggan

    cout << "Fuzzification of stok barang : " << endl;
    cout << "uSedikit = " << uSedikit << endl;
    cout << "uLumayan = " << uLumayan << endl;
    cout << "uBanyak = " << uBanyak << endl;

    cout << "Fuzzification of permintaan pelanggan : " << endl;
    cout << "uRendah = " << uRendah << endl;
    cout << "uStandar = " << uStandar << endl;
    cout << "uTinggi = " << uTinggi << endl;

    //rules
    and_rules(uSedikit, uRendah, murah, murah);
    and_rules(uSedikit, uStandar, murah, murah);
    and_rules(uSedikit, uTinggi, mahal, mahal);
    and_rules(uLumayan, uRendah, normal, normal);
    and_rules(uLumayan, uStandar, murah, murah);
    and_rules(uLumayan, uTinggi, normal, normal);
    and_rules(uBanyak, uRendah, murah, murah);
    and_rules(uBanyak, uStandar, normal, normal);
    and_rules(uBanyak, uTinggi, normal, normal);

    cout << "\nConclusion : " << endl;
    cout << "uMurah = " << murah << endl;
    cout << "uNormal = " << normal << endl;
    cout << "uMahal = " << mahal << endl;

    //sample for defuzzification
    determine_sample(0, 40, 80, 100, sample1, sample2, sample3);
    cout << "\nSample value for defuzzification : " << endl;
    cout << "Sample 1 = " << sample1 << endl;
    cout << "Sample 2 = " << sample2 << endl;
    cout << "Sample 3 = " << sample3 << endl;

    //defuzzification
    defuzzification(murah, normal, mahal, sample1, sample2, sample3, harga);
    cout << "\n\nHARGA :" << endl;
    cout << harga << endl;
    return 0;
}
