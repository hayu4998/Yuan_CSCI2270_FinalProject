#include<vector>
#include<iostream>
#include<string>
#include<string.h>
#include<algorithm>
#include <math.h>
#include"header.h"
using namespace std;

void Astar::sorting(){
    int i, j;
    for(i=openhead+1;i<opentail;i++){
        vertex *index=open[i].v;
        j=i;
        while(j>openhead && open[j-1].v->F > index->F){
            open[j]=open[j-1];
            j--;
        }
        open[j].v=index;
    }

}

void Astar::calH(vertex *c1){
    int deter=vertices.size();
    vertex *c2= NULL;
    for(int i=0;i<deter;i++){
        c2=new vertex;
        vertex *c2=&vertices[i];
        float lon1=c1->longitude/180*3.1415926;
        float lon2=c2->longitude/180*3.1415926;
        float lat1=c1->latitude/180*3.1415926;
        float lat2=c2->latitude/180*3.1415926;

        float dlon = lon2 - lon1;
        float dlat = lat2 - lat1;
        float R=3959;

        float a = pow((sin(dlat/2)),2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2),2);
        float c = 2 * atan2( sqrt(a), sqrt(1-a) );
        float d = R * c;
        c2->H=d;
        c2->F=c2->G+c2->H;
    }
}

vertex *Astar::searchnode(string city){
    int deter=vertices.size();

    for(int i=0;i<deter;i++){
        if(vertices[i].name==city){
            return &vertices[i];
        }
    }
    return NULL;

}

void Astar::insertpath(string path,float distance,string city1,string city2){

    vertex *c1=searchnode(city1);
    vertex *c2=searchnode(city2);
    if(c1==NULL || c2==NULL){
        cout<<"Invalid City input"<<endl;
    }
    else{
        adjecent av;
        av.v = c2;
        av.road = path;
        av.distance=distance;
        c1->adj.push_back(av);

        adjecent ac;
        ac.v = c1;
        ac.road = path;
        ac.distance=distance;
        c2->adj.push_back(ac);
    }

}

void Astar::quickinsert(string city, float lat, float lon){
     vertex v;
        v.name = city;
        v.latitude=lat;
        v.longitude=lon;
        v.flag=false;
        v.G=10000000000;
        v.parent=NULL;
        vertices.push_back(v);
}

void Astar::insertcity(string city){
    string longi;
    float longitude;
    string alt;
    float latitude;
    string distant;
    string high;
    string city2;

    cout<<"Enter the latitude of the city in N"<<endl;
    getline(cin,alt);
    latitude=atof(alt.c_str());

    cout<<"Enter the longitude of the city in W"<<endl;
    getline(cin,longi);
    longitude=atof(longi.c_str());

    cout<<"Enter one other city that it connected to"<<endl;
    getline(cin,city2);
    transform(city2.begin(),city2.end(), city2.begin(), ::toupper);

    cout<<"Enter the path name"<<endl;
    getline(cin,high);

    cout<<"Enter the length of path"<<endl;
    getline(cin,distant);
    float dist=atof(distant.c_str());

    int deter=vertices.size();
    bool found = false;
    for(int i = 0; i < deter; i++){
        if(vertices[i].name == city){
            found = true;
            cout<<vertices[i].name<<" already exist."<<endl;
        }
    }
    if(found == false){
        quickinsert(city,latitude,longitude);
        insertpath(high,dist,city,city2);
    }
}

void Astar::searchpath(string start,string destinatioin){
    cout<<"searching path"<<endl;

    vertex *D=searchnode(destinatioin);

    vertex *S=searchnode(start);
    if(S==NULL||D==NULL){
        cout<<"invalid city name"<<endl;
        return;
    }
    D->flag=true;
    open[opentail].v=S;
    opentail++;
    calH(D);
    S->G=0;

    while(openhead!=opentail){
        vertex *current= open[openhead].v;

        if (current->flag==true){

            cout<<"The path is "<< close[closehead].v->name;
            traceback(current);
            cout<<endl;
            cout<<"With total distance of "<<current->G<<" miles"<<endl;
            D->flag=false;
            for(int i=0;i<vertices.size();i++){
                vertices[i].G=1000000000;
                vertices[i].parent=NULL;
            }
            for(int j=0;j<1000;j++){
                open[j].v=NULL;
                close[j].v=NULL;
            }
            openhead=0;
            opentail=0;
            closehead=0;
            closetail=0;

            return;
        }
        openhead++;

        close[closetail].v=current;

        closetail++;

        for(int i=0;i<current->adj.size();i++){
            bool deter=check(current->adj[i].v);
            if (deter==true){

            }
            else{
                vertex *neighbor=searchnode(current->adj[i].v->name);
                open[opentail].v=neighbor;

                opentail++;

                float tend=current->G+current->adj[i].distance;

                if(tend<neighbor->G){
                    //cout<<neighbor->name<<endl;
                    neighbor->parent=current;
                    neighbor->G=tend;
                    neighbor->F=neighbor->G+neighbor->H;
                    neighbor=NULL;
                }
            }

        }

        sorting();
    }
    cout<<"Cant find a valid path"<<endl;

}

bool Astar::check(vertex *v){
    for(int i= closehead;i<closetail;i++){
        if(close[i].v==v){
            return true;
        }
    }
    return false;
}

void Astar::traceback(vertex*d){
    if(d->parent->parent==NULL){
        for(int i=0;i<d->parent->adj.size()+1;i++){
            if(d->parent->adj[i].v==d){
                cout<<" -->" <<d->parent->adj[i].road<<"-->"<<d->name;
            }
        }
    }
    else{
        traceback(d->parent);

        for(int i=0;i<d->parent->adj.size()+1;i++){
            if(d->parent->adj[i].v==d){
                cout<<" -->" <<d->parent->adj[i].road<<"-->"<<d->name;
            }
        }
    }

}

void Astar::deletecity(string city){
    vertex *det=searchnode(city);
    if(det==NULL){
        cout<<"The node doesn't exist"<<endl;
        return;
    }
    else{
        for(int i=0;i<det->adj.size();i++){
            deletepath(det->adj[i].road,det->name,det->adj[i].v->name);
        }
        for(int j=0;j<vertices.size();j++){
            if(vertices[j].name==det->name){
                vertices.erase(vertices.begin()+j);
            }
        }
    }
}

void Astar::deletepath(string path, string city1, string city2){
    vertex *c1=searchnode(city1);
    vertex *c2=searchnode(city2);
    if(c1==NULL || c2==NULL){
        cout<<"Invalid City input"<<endl;
    }
    else{
        for(int i=0;i<c1->adj.size();i++){
            if(c1->adj[i].v==c2){
                c1->adj.erase(c1->adj.begin()+i);
            }
        }
        for(int i=0;i<c2->adj.size();i++){
            if(c2->adj[i].v==c1){
                c2->adj.erase(c2->adj.begin()+i);
            }
        }
    }
}

void Astar::presetup(){
    quickinsert("DENVER" ,39.7392,104.9903);
    quickinsert("BOULDER" ,40.0150,105.2705);
    quickinsert("WESTMINSTER",39.8367,105.0372);
    quickinsert("FORT COLLIONS",40.5853,105.0844);
    quickinsert("LONGMONT",40.1672,105.1019);
    quickinsert("BLACK HAWK",39.7969,105.4939);
    quickinsert("GREELEY",40.4233,104.7091);
    quickinsert("LOVELAND",40.3978,105.0750);

    insertpath("I-70",37.9,"DENVER","BLACK HAWK");
    insertpath("I-25 + US 36",11.3,"DENVER","WESTMINSTER");
    insertpath("US 287",25.7,"WESTMINSTER","LONGMONT");
    insertpath("I-25",63.4,"DENVER","GREELEY");
    insertpath("CO-119 + BOULDER CANYON DR",35.7,"BLACK HAWK","BOULDER");
    insertpath("US 36",20.2,"WESTMINSTER","BOULDER");
    insertpath("CO-119",15.6,"BOULDER","LONGMONT");
    insertpath("US 287",17.3,"LONGMONT","LOVELAND");
    insertpath("US 34",20.6,"LOVELAND","GREELEY");
    insertpath("US 287",13.6,"LOVELAND","FORT COLLIONS");
    insertpath("CO-14 + CO RD 33",30.9,"FORT COLLIONS","GREELEY");

}

int main(){
    Astar A;
    A.presetup();
    //A.searchpath("DENVER","BOULDER");
    //A.searchpath("BLACK HAWK","GREELEY");

    cout<<"Navigation Program powered by A star"<<endl;
    cout<<"Only use for longitude and latitude in north America"<<endl;
    cout<<"===================================="<<endl;
    int choice=0;
    while (choice!=6){
        cout<<"Please choice the operation below"<<endl;
        cout<<"1.Navigation between two destination"<<endl;
        cout<<"2.insert city into the map"<<endl;
        cout<<"3.insert path into the map"<<endl;
        cout<<"4.delete city"<<endl;
        cout<<"5.delete path"<<endl;
        cout<<"6.quit"<<endl;
        string cho;
        getline(cin,cho);
        choice=atoi(cho.c_str());

        if (choice == 1){   //Navigation
            string start;
            string destination;
            cout<<"Enter the starting city"<<endl;
            getline(cin,start);
            cout<<"Enter your destination"<<endl;
            getline(cin,destination);
            transform(start.begin(), start.end(), start.begin(), ::toupper);
            transform(destination.begin(), destination.end(), destination.begin(), ::toupper);
            A.searchpath(start,destination);


        }
        if(choice==2){      //insert city
            cout<<"Enter city name"<<endl;
            string City;
            getline(cin,City);
            transform(City.begin(),City.end(), City.begin(), ::toupper);
            A.insertcity(City);

        }
        if(choice==3){      //insert path
            string path;
            string start;
            string destination;

            cout<<"Enter the path name"<<endl;
            getline(cin,path);
            cout<<"Enter one of the city's name"<<endl;
            getline(cin,start);
            cout<<"Enter the other city's name"<<endl;
            getline(cin,destination);

            transform(start.begin(), start.end(), start.begin(), ::toupper);
            transform(destination.begin(), destination.end(), destination.begin(), ::toupper);
            cout<<"Enter the length of path"<<endl;
            string distant;
            getline(cin,distant);
            float dist=atof(distant.c_str());

            A.insertpath(path,dist,start,destination);

        }
        if(choice==4){      //delete city
            cout<<"Enter city name"<<endl;
            string City;
            getline(cin,City);
            transform(City.begin(),City.end(), City.begin(), ::toupper);
            A.deletecity(City);
        }
        if(choice==5){      //delete path
            string start;
            string destination;
            cout<<"Enter one of the city's name"<<endl;
            getline(cin,start);
            cout<<"Enter the other city's name"<<endl;
            getline(cin,destination);
            cout<<"Enter path name"<<endl;
            string path;
            getline(cin,path);
            transform(start.begin(), start.end(), start.begin(), ::toupper);
            transform(destination.begin(), destination.end(), destination.begin(), ::toupper);
            A.deletepath(path,start,destination);
        }

    }

}
