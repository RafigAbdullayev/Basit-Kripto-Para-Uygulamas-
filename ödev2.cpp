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
        hesapTuru = GENEL; // Varsayýlan olarak genel hesap
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

        cout << "Gün " << gunSayaci << " - Kripto Deðeri: " << oncekiDeger << "\n";

        return oncekiDeger;
    }

    double hesaplaOzelKriptoDegeri(double oncekiDeger) const {
        // Özel hesaplar için kripto deðeri hesapla
        double degisimOrani = 0.05;
        double dususOrani = 0.1;

        if (gunSayaci == 1) {
            // Ýlk gün için özel hesap kripto deðeri 1 TL olmalý
            return 1.0;
        }

        if (gunSayaci % 10 == 0) {
            oncekiDeger -= (oncekiDeger * dususOrani);
        }
        else {
            oncekiDeger += (oncekiDeger * degisimOrani);
        }

        cout << "Gün " << gunSayaci << " - Özel Kripto Deðeri: " << oncekiDeger << "\n";

        return oncekiDeger;
    }
};

int main() {
    setlocale(LC_ALL, "Turkish");
    srand(time(0));

    Hesap genelHesap; // Genel hesap
    Hesap hesaplar[MAX_HESAP_SAYISI]; // Hesap nesnelerini tutan dizi

    double genelKriptoDegeri = 1.0; // Genel kripto deðeri
    double ozelKriptoDegeri = 1.0; // Özel hesap kripto deðeri

    int hesapSayisi = 0;

    int secim;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Yeni Hesap Oluþtur\n";
        cout << "2. Hesaba Giriþ Yap(Hesap Oluþturduysanýz Burdan Giriþ Yapýn)\n";
        cout << "0. Çýkýþ\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
        case 1: {
            if (hesapSayisi < MAX_HESAP_SAYISI) {
                Hesap yeniHesap;
                cout << "Hesap ID oluþturuldu: " << yeniHesap.getId() << "\n";
                string sifre;
                cout << "Hesap þifresi oluþturun: ";
                cin >> sifre;

                int hesapTuruSecim;
                cout << "Hesap türü (0: Genel, 1: Özel): ";
                cin >> hesapTuruSecim;

                if (hesapTuruSecim == 1) {
                    yeniHesap.setHesapTuru(OZEL);
                }

                yeniHesap.setSifre(sifre);
                hesaplar[hesapSayisi] = yeniHesap;  // Diziyi kullanarak yeni hesabý ekle
                hesapSayisi++;
            }
            else {
                cout << "Maksimum hesap sayýsýna ulaþýldý.\n";
            }
            break;
        }
        case 2:
            if (hesapSayisi > 0) {
                int girilenId;
                string girilenSifre;

                cout << "Hesap ID: ";
                cin >> girilenId;
                cout << "Hesap þifresi: ";
                cin >> girilenSifre;

                bool girisBasarili = false;
                for (int i = 0; i < hesapSayisi; ++i) {
                    if (girilenSifre == hesaplar[i].getSifre() && girilenId == hesaplar[i].getId()) {
                        cout << "Giriþ baþarýlý!\n";

                        int anaMenuSecim;
                        do {
                            cout << "\n--- ANA MENU ---\n";
                            cout << "1. TL Yatýr\n";
                            cout << "2. TL'den Kripto Al\n";
                            cout << "3. Kripto Sat\n";
                            cout << "4. Bakiye Görüntüle\n";
                            cout << "5. Günü Atlama\n";
                            cout << "6. Listele\n";
                            cout << "0. Menuye Don\n";
                            cout << "Seçiminiz: ";
                            cin >> anaMenuSecim;

                            switch (anaMenuSecim) {
                            case 1: {
                                cout << "Yatýrýlacak TL miktarýný girin: ";
                                double tlMiktar;
                                cin >> tlMiktar;
                                hesaplar[i].tlYatir(tlMiktar);

                                // Bakiye görüntüleme
                                cout <<endl << "Güncellenmiþ Bakiyeler:\n";
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            }
                            case 2: {
                                cout << "TL'den alýnacak kripto miktarýný girin: ";
                                double alinanKriptoMiktar;
                                cin >> alinanKriptoMiktar;

                                hesaplar[i].tlDenKriptoAl(alinanKriptoMiktar, genelKriptoDegeri);

                                // Bakiye görüntüleme
                                cout << "Güncellenmiþ Bakiyeler:\n";
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            }

                            case 3: {
                                cout << "Satýlacak kripto miktarýný girin: ";
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

                                // Bakiye görüntüleme
                                cout << "Güncellenmiþ Bakiyeler:\n";
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            }

                            case 4:
                                cout << "TL Bakiye: " << hesaplar[i].getTlBakiye() << " TL\n";
                                cout << "Kripto Bakiye: " << hesaplar[i].getKriptoBakiye() << " Kripto\n";
                                break;
                            case 5:
                                ++gunSayaci; // Gün sayacýný artýr
                                if (hesaplar[i].getHesapTuru() == OZEL) {
                                    ozelKriptoDegeri = hesaplar[i].hesaplaOzelKriptoDegeri(ozelKriptoDegeri);
                                }
                                else {
                                    genelKriptoDegeri = hesaplar[i].hesaplaKriptoDegeri(genelKriptoDegeri);
                                }
                                cout << "Yeni gün: " << gunSayaci << "\n";
                                break;
                            case 6: { // Yeni case ekleniyor
                                cout << "\n--- TÜM HESAPLAR ---\n";
                                for (int j = 0; j < hesapSayisi; ++j) {
                                    cout << "Hesap ID: " << hesaplar[j].getId() << "\n";
                                    cout << "Hesap Türü: " << (hesaplar[j].getHesapTuru() == OZEL ? "Özel" : "Genel") << "\n";
                                    cout << "TL Bakiye: " << hesaplar[j].getTlBakiye() << " TL\n";
                                    cout << "Kripto Bakiye: " << hesaplar[j].getKriptoBakiye() << " Kripto\n";
                                    cout << "-------------------\n";
                                }
                                break;
                            }
                            case 0:
                                cout << "Menüye dönülüyor\n";
                                break;
                            default:
                                cout << "Geçersiz seçim!\n";
                                break;
                            }
                        } while (anaMenuSecim != 0);
                        girisBasarili = true;
                    }
                }
                if (!girisBasarili) {
                    cout << "Hatali ID veya þifre. Giriþ baþarýsýz.\n";
                }
            }
            else {
                cout << "Önce yeni bir hesap oluþturun!\n";
            }
            break;
        case 0:
            cout << "Çýkýþ yapýlýyor...\n";
            break;
        default:
            cout << "Geçersiz seçim!\n";
            break;
        }
    } while (secim != 0);

    return 0;
}