#include <iostream>
#include <string>
using namespace std;

class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;
    virtual ~SortieAudio() {}
};

class HautParleur : public SortieAudio {
public:
    void ouvrir() override { cout << "Haut-Parleur ouvert" << endl; }
    void jouer(const string& son) override { cout << "Haut-Parleur joue : " << son << endl; }
    void fermer() override { cout << "Haut-Parleur fermé" << endl; }
};

class CasqueBT : public SortieAudio {
public:
    void ouvrir() override { cout << "Casque Bluetooth connecté" << endl; }
    void jouer(const string& son) override { cout << "Casque Bluetooth joue : " << son << endl; }
    void fermer() override { cout << "Casque Bluetooth déconnecté" << endl; }
};

class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override { cout << "Sortie HDMI activée" << endl; }
    void jouer(const string& son) override { cout << "Sortie HDMI joue : " << son << endl; }
    void fermer() override { cout << "Sortie HDMI désactivée" << endl; }
};

void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique.mp3");
    sortie->fermer();
}

int main() {
    SortieAudio* peripheriques[3];
    peripheriques[0] = new HautParleur();
    peripheriques[1] = new CasqueBT();
    peripheriques[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        tester(peripheriques[i]);
    }

    for (int i = 0; i < 3; i++) {
        delete peripheriques[i];
    }

    return 0;
}
