#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;
    virtual ~Plugin() = default;

    static unique_ptr<Plugin> creerPlugin(const string& type);
};

class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override { return "Correcteur Orthographique"; }
    string traiter(const string& texte) override {
        string t = texte;
        size_t pos;
        while ((pos = t.find("aimee")) != string::npos) t.replace(pos, 5, "j'aime ");
        while ((pos = t.find("etdiente")) != string::npos) t.replace(pos,12, "etudiante");
        while ((pos = t.find("info")) != string::npos) t.replace(pos, 4, "informatique");
        return t;
    }
};

class TraducteurAnglais : public Plugin {
public:
    string nom() const override { return "Traducteur Anglais"; }
    string traiter(const string& texte) override {
        string t = texte;
        size_t pos;
        while ((pos = t.find("bonjour")) != string::npos) t.replace(pos,7, "hello");
        while ((pos = t.find("etudiante")) != string::npos) t.replace(pos,9, "student");
        while ((pos = t.find("annee")) != string::npos) t.replace(pos, 5, "year");
        return t;
    }
};

class AnalyseurStyle : public Plugin {
public:
    string nom() const override { return "Analyseur de Style"; }
    string traiter(const string& texte) override {
        int phrasesLongues = 0;
        string t = texte;
        size_t start = 0;
        while (true) {
            size_t end = t.find('.', start);
            if (end == string::npos) break;
            if (end - start > 80) phrasesLongues++;
            start = end + 1;
        }
        if (phrasesLongues > 0)
            t += "\n(" + to_string(phrasesLongues) + " phrase(s) trop longue(s))";
        return t;
    }
};

unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") return make_unique<CorrecteurOrthographique>();
    if (type == "traducteur") return make_unique<TraducteurAnglais>();
    if (type == "analyseur") return make_unique<AnalyseurStyle>();
    return nullptr;
}

int main() {
    string texte;
    cout << "Entrez un texte : ";
    getline(cin, texte);

    vector<unique_ptr<Plugin>> plugins;
    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    for (auto& p : plugins) {
        texte = p->traiter(texte);
        cout << "\n[" << p->nom() << "]\n" << texte << endl;
    }

    return 0;
}
