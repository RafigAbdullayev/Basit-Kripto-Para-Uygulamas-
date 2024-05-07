#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_HESAP_SAYISI = 100;

int gunSayaci = 1;

enum HesapTuru {
    GENEL,
    OZEL
};

class Hesap {
private:
    int id;
    string sifre;
    double tlBakiye;
    double kriptoBakiye;
    HesapTuru hesapTuru;

public:
    Hesap() {
        id = rand() % 800000 + 100000;
        tlBakiye = 0.0;
        kriptoBakiye = 0.0;
        hesapTuru = GENEL; // Varsay�lan olarak genel hesap
    }

    int getId() const {
        return id;
    }

    void setSifre(const string& sifre) {
        this->sifre = sifre;
    }

    string getSifre() const {
        return sifre;
    }

    double getTlBakiye() const {
        return tlBakiye;
    }

    double getKriptoBakiye() const {
        return kriptoBakiye;
    }

    HesapTuru getHesapTuru() const {
        return hesapTuru;
    }

    void setHesapTuru(HesapTuru tur) {
        hesapTuru = tur;
    }

    void tlYatir(double miktar) {
        tlBakiye += miktar;
    }

    void tlDenKriptoAl(double miktar, double kriptoDegeri) {
        if (tlBakiye >= miktar) {
            tlBakiye -= miktar;
            kriptoBakiye += miktar / kriptoDegeri;
        }
        else {
            cout << "Yetersiz bakiye!\n";
        }
    }

    void kriptoSat(double miktar, double kriptoDegeri) {
        if (kriptoBakiye >= miktar) {
            kriptoBakiye -= miktar;
            tlBakiye += miktar * kriptoDegeri;
        }
        else {
            cout << "Yetersiz kripto bakiye!\n";
        }
    }

    double hesaplaKriptoDegeri(double oncekiDeger) const {
        double degisimOrani = 0.01;
        double dususOrani = 0.05;

        if (gunSayaci % 15 == 0) {
            oncekiDeger -= (oncekiDeger * dususOrani);
        }
        else {
            oncekiDeger += (oncekiDeger * degisimOrani);
        }

        cout << "G�n " << gunSayaci << " - Kripto De�eri: " << oncekiDeger << "\n";

        return oncekiDeger;
    }

    double hesaplaOzelKriptoDegeri(double oncekiDeger) const {
        // �zel hesaplar i�in kripto de�eri hesapla
        double degisimOrani = 0.05;
        double dususOrani = 0.1;

        if (gunSayaci == 1) {
            // �lk g�n i�in �zel hesap kripto de�eri 1 TL olmal�
            return 1.0;
        }

        if (gunSayaci % 10 == 0) {
            oncekiDeger -= (oncekiDeger * dususOrani);
        }
        else {
            oncekiDeger += (oncekiDeger * degisimOrani);
        }

        cout << "G�n " << gunSayaci << " - �zel Kripto De�eri: " << oncekiDeger << "\n";

        return oncekiDeger;
    }
};

int main() {
    setlocale(LC_ALL, "Turkish");
    srand(time(0));

    Hesap genelHesap; // Genel hesap
    Hesap hesaplar[MAX_HESAP_SAYISI]; // Hesap nesnelerini tutan dizi

    double genelKriptoDegeri = 1.0; // Genel kripto de�eri
    double ozelKriptoDegeri = 1.0; // �zel hesap kripto de�eri

    int hesapSayisi = 0;

    int secim;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Yeni Hesap Olu�tur\n";
        cout << "2. Hesaba Giri� Yap(Hesap Olu�turduysan�z Burdan Giri� Yap�n)\n";
        cout << "0. ��k��\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
        case 1: {
            if (hesapSayisi < MAX_HESAP_SAYISI) {
                Hesap yeniHesap;
                cout << "Hesap ID olu�turuldu: " << yeniHesap.getId() << "\n";
                string sifre;
                cout << "Hesap �ifresi olu�turun: ";
                cin >> sifre;

                int hesapTuruSecim;
                cout << "Hesap t�r� (0: Genel, 1: �zel): ";
                cin >> hesapTuruSecim;

                if (hesapTuruSecim == 1) {
                    yeniHesap.setHesapTuru(OZEL);
                }

                yeniHesap.setSifre(sifre);
                hesaplar[hesapSayisi] = yeniHesap;  // Diziyi kullanarak yeni hesab� ekle
                hesapSayisi++;
            }
            else {
                cout << "Maksimum hesap say�s�na ula��ld�.\n";
            }
            break;
        }
        case 2:
            if (hesapSayisi > 0) {
                int girilenId;
                string girilenSifre;

                cout << "Hesap ID: ";
                cin >> girilenId;
                cout << "Hesap �ifresi: ";
                cin >> girilenSifre;

                bool girisBasarili = false;
                for (int i = 0; i < hesapSayisi; ++i) {
                    if (girilenSifre == hesaplar[i].getSifre() && girilenId == hesaplar[i].getId()) {
                        cout << "Giri� ba�ar�l�!\n";

                        int anaMenuSecim;
                        do {
                            cout << "\n--- ANA MENU ---\n";
                            cout << "1. TL Yat�r\n";
                            cout << "2. TL'den Kripto Al\n";
                            cout << "3. Kripto Sat\n";
                            cout << "4. Bakiye G�r�nt�le\n";
                            cout << "5. G�n� Atlama\n";
                            cout << "6. Listele\n";
                            cout << "0. Menuye Don\n";
                            cout << "Se�iminiz: ";
                            cin >> anaMenuSecim;

                            switch (anaMenuSecim) {
                            case 1: {
                                cout << "Yat�r�lacak TL miktar�n� girin: ";
                                double tlMiktar;
                                cin >> tlMiktar;
                                hesaplar[i].tlYatir(tlMiktar);

                                // Bakiye g�r�nt�leme
                                cout <<endl << "G�ncellenmi� Bakiyeler:\n";
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            }
                            case 2: {
                                cout << "TL'den al�nacak kripto miktar�n� girin: ";
                                double alinanKriptoMiktar;
                                cin >> alinanKriptoMiktar;

                                hesaplar[i].tlDenKriptoAl(alinanKriptoMiktar, genelKriptoDegeri);

                                // Bakiye g�r�nt�leme
                                cout << "G�ncellenmi� Bakiyeler:\n";
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            }

                            case 3: {
                                cout << "Sat�lacak kripto miktar�n� girin: ";
                                double satilanKriptoMiktar;
                                cin >> satilanKriptoMiktar;

                                double oncekiKriptoDegeri;

                                if (hesaplar[i].getHesapTuru() == OZEL) {
                                    oncekiKriptoDegeri = ozelKriptoDegeri;
                                    ozelKriptoDegeri = hesaplar[i].hesaplaOzelKriptoDegeri(ozelKriptoDegeri);
                                }
                                else {
                                    oncekiKriptoDegeri = genelKriptoDegeri;
                                    genelKriptoDegeri = hesaplar[i].hesaplaKriptoDegeri(genelKriptoDegeri);
                                }

                                hesaplar[i].kriptoSat(satilanKriptoMiktar, hesaplar[i].getHesapTuru() == OZEL ? ozelKriptoDegeri : genelKriptoDegeri);

                                // Bakiye g�r�nt�leme
                                cout << "G�ncellenmi� Bakiyeler:\n";
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            }

                            case 4:
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            case 5:
                                ++gunSayaci; // G�n sayac�n� art�r
                                if (hesaplar[i].getHesapTuru() == OZEL) {
                                    ozelKriptoDegeri = hesaplar[i].hesaplaOzelKriptoDegeri(ozelKriptoDegeri);
                                }
                                else {
                                    genelKriptoDegeri = hesaplar[i].hesaplaKriptoDegeri(genelKriptoDegeri);
                                }
                                cout << "Yeni g�n: " << gunSayaci << "\n";
                                break;
                            case 6: { // Yeni case ekleniyor
                                cout << "\n--- T�M HESAPLAR ---\n";
                                for (int j = 0; j < hesapSayisi; ++j) {
                                    cout << "Hesap ID: " << hesaplar[j].getId() << "\n";
                                    cout << "Hesap T�r�: " << (hesaplar[j].getHesapTuru() == OZEL ? "�zel" : "Genel") << "\n";
                                    cout << "TL Bakiye: " << hesaplar[j].getTlBakiye() << " TL\n";
                                    cout << "Kripto Bakiye: " << hesaplar[j].getKriptoBakiye() << " Kripto\n";
                                    cout << "-------------------\n";
                                }
                                break;
                            }
                            case 0:
                                cout << "Men�ye d�n�l�yor\n";
                                break;
                            default:
                                cout << "Ge�ersiz se�im!\n";
                                break;
                            }
                        } while (anaMenuSecim != 0);
                        girisBasarili = true;
                    }
                }
                if (!girisBasarili) {
                    cout << "Hatali ID veya �ifre. Giri� ba�ar�s�z.\n";
                }
            }
            else {
                cout << "�nce yeni bir hesap olu�turun!\n";
            }
            break;
        case 0:
            cout << "��k�� yap�l�yor...\n";
            break;
        default:
            cout << "Ge�ersiz se�im!\n";
            break;
        }
    } while (secim != 0);

    return 0;
}