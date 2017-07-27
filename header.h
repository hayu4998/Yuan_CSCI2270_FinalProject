#ifndef HEADER_HPP
#define HEADER_HPP

#include<vector>
using namespace std;
struct adjecent;

struct vertex{
    string name;
    vector<adjecent> adj;
    float longitude;
    float latitude;
    float H;
    float G;
    float F;
    bool flag;
    vertex *parent;
};

struct adjecent{
    vertex *v;
    string road;
    float distance;
};



struct Array{
    vertex *v;
};

class Astar{

    private:
        Array open[1000];
        Array close[1000];
        int openhead;
        int opentail;
        int closehead;
        int closetail;

        void sorting();
        vertex *searchnode(string);
    public:

        void calH(vertex*);
        vector<vertex> vertices;
        Astar(){openhead=0;opentail=0;closehead=0;closetail=0;};
        ~Astar(){};
        void traceback(vertex*);
        bool check(vertex*);

        void presetup();
        void quickinsert(string, float,float);
        void searchpath(string,string);
        void deletecity(string);
        void deletepath(string,string,string);
        void insertcity(string);
        void insertpath(string,float,string,string);
};
#endif // HEADER
