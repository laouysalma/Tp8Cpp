#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

struct Vec3 {
    float x, y, z;
    Vec3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}
    float distance(const Vec3& o) const { return sqrt((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y)+(z-o.z)*(z-o.z)); }
    float dot(const Vec3& o) const { return x*o.x + y*o.y + z*o.z; }
    Vec3 normalize() const { float l = sqrt(x*x+y*y+z*z); return (l>0)?Vec3(x/l,y/l,z/l):Vec3(); }
};

class Lumiere {
public:
    virtual float intensite(const Vec3& point) const = 0;
    virtual ~Lumiere() = default;
};

class LumiereDirectionnelle : public Lumiere {
    Vec3 direction;
    float couleur;
public:
    LumiereDirectionnelle(const Vec3& dir,float c) : direction(dir.normalize()), couleur(c) {}
    float intensite(const Vec3& point) const override { return couleur; }
};

class LumierePonctuelle : public Lumiere {
    Vec3 position;
    float attenuation, intensiteBase;
public:
    LumierePonctuelle(const Vec3& pos,float att,float base) : position(pos), attenuation(att), intensiteBase(base) {}
    float intensite(const Vec3& point) const override {
        float d = position.distance(point);
        return intensiteBase / (1 + attenuation*d*d);
    }
};

class LumiereSpot : public Lumiere {
    Vec3 position, direction;
    float angleOuverture, intensiteBase;
public:
    LumiereSpot(const Vec3& pos,const Vec3& dir,float angle,float base) : position(pos), direction(dir.normalize()), angleOuverture(angle), intensiteBase(base) {}
    float intensite(const Vec3& point) const override {
        Vec3 dirVersPoint(point.x-position.x, point.y-position.y, point.z-position.z);
        dirVersPoint = dirVersPoint.normalize();
        float angle = acos(direction.dot(dirVersPoint));
        if(angle<angleOuverture) return intensiteBase/(1+position.distance(point)*position.distance(point));
        else return 0;
    }
};

float calculerEclairage(const Vec3& point,const vector<unique_ptr<Lumiere>>& lumieres){
    float total=0;
    for(const auto& l: lumieres) total+=l->intensite(point);
    return total;
}

int main(){
    vector<unique_ptr<Lumiere>> lumieres;
    lumieres.push_back(make_unique<LumiereDirectionnelle>(Vec3(1,-1,0),1.5f));
    lumieres.push_back(make_unique<LumierePonctuelle>(Vec3(0,5,0),0.1f,3.0f));
    lumieres.push_back(make_unique<LumiereSpot>(Vec3(0,3,3),Vec3(0,-1,-1),0.7f,5.0f));

    vector<Vec3> points = {Vec3(0,0,0), Vec3(2,2,0), Vec3(0,5,2)};
    for(const auto& p: points)
        cout<<"Eclairage au point ("<<p.x<<","<<p.y<<","<<p.z<<") = "<<calculerEclairage(p, lumieres)<<endl;

    return 0;
}
