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

class Queue{

    private:
        int size;
        Array *store=NULL;
        int head ;
        int tail ;

    public:
        int count ;
        Queue();
        ~Queue();
        void setup(int);
        void enqueue(vertex*);
        vertex *dequeue();
        void sorting();
        void reset();
        bool check(vertex*);
};

class Astar{

    private:
        Queue open;
        Queue close;
        vertex *searchnode(string);

    public:

        void calH(vertex*);
        vector<vertex> vertices;
        Astar(){open.setup(1000);close.setup(1000);};
        ~Astar(){};
        void traceback(vertex*);


        void presetup();
        void quickinsert(string, float,float);
        void searchpath(string,string);
        void deletecity(string);
        void deletepath(string,string,string);
        void insertcity(string);
        void insertpath(string,float,string,string);
};
#endif // HEADER
