/*Amirhossein Forouzani 02/05/2019*/
#include<iostream>
#include <cstdlib>
#include <sstream>
#include<fstream>
#include <string>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include <istream>
#include <random>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
class City
{
private:
    int CityNoX;
    int City_X;
    int City_Y;
public:
    void Init_City (int CityNo,int X, int Y)
    {
        CityNoX = CityNo;
        City_X = X;
        City_Y = Y;
    }
    int return_x()
    {
        return City_X;
    }
    int return_y()
    {
        return City_X;
    }
    int return_num()
    {
        return CityNoX;
    }

    /*your code*/
};
class SimulatedAnnealing
{
private:
    double T_start;//intial temperature
    double T_end;//end temperature
    float beta;
    int citysize;
    City *cities;//we want you to practice citiespointer in this lab
public:
//help:   https://github.com/arjun-krishna/TSP/blob/master/simulatedAnnealing.cpp
    SimulatedAnnealing()
    {
        cities = NULL;
    }
    run(double value1, double value2, float value3, ifstream &infile)
    {
        // string in;
        T_start = value1;
        T_end = value2;
        beta = value3;
        infile.open("Lab5_partI_input.txt");
        infile>>citysize;
        cities = new City[citysize];
        for(int j = 0 ; j < citysize; j++)
        {
            int num;
            int  x;
            int  y;
            infile>>num;
            infile>>x;
            infile>>y;
            //cout<<y<<endl;
            cities[j].Init_City(num,x,y);
        }
        City *town;
        town = new City[citysize];
        town = genRand(cities);
        for(int j= 0 ; j<citysize; j++)
        {

            //  cout<<town[j].return_x()<<"hi"<<endl;
            // cout<<cities[j].return_x()<<"hi  cc"<<endl;
        }
//        for (int i = 0 ; i<citysize-1;i++){
//        int yy = cities[i].return_x();
//        int xx = town[i].return_x();
//        cout<<xx<<"what?"<<endl;
//        cout<<yy<<"what city?"<<endl;
//    }
        City *best;
        best = new City[citysize];
        int min_tour = travel_cost(town);
        best = town;
        for(int i=0; i<1000; i++)
        {
            random_shuffle(&town[0],&town[citysize-1]);
            for(int j= 0 ; j<citysize; j++)
            {
                //cout<<town[j].return_x()<<"hi"<<endl;
            }
            double tCost = travel_cost(town);
            if(tCost < min_tour)
            {
                min_tour = tCost;
                best = town;
            }
        }
        town = best;
        double p,expP,deltaE;

        for(double T=T_start; T > T_end; T*=beta)
        {
            for(int i=0; i<500; i++)
            {
                City *c;
                c = new City[citysize];
                // for (int j= 0 ;j<citysize;j++ ){
                c = genRand(town);
                // }
                deltaE = evaluate(town) - evaluate(c);
                deltaE /= T;
                p = 1 / (1+exp(-1*deltaE));
                expP = randProb();
                //cout<< expP<<endl;
                if(expP < p)   // move
                {
                    town = c;
                    // cout<< min_tour<<endl;
                    double tCost = travel_cost(town);
                    if(tCost < min_tour )
                    {
                        best = town;
                        min_tour = tCost;
                        // cout<< min_tour<<endl;
                    }
                }
            }
        }
        fstream Files;
        Files.open("Lab5_partI_task1_output", ios::out | ios::app);
        cout<< min_tour<<endl;
        Files<<"final distance of SA method: "<<min_tour<<endl;
        for (int i = 0; i<citysize; i++)
        {
            cout<<best[i].return_num()<<endl;
            Files<<best[i].return_num()<<endl;
        }

    }
    double randProb()
    {
        double p = (rand() / (RAND_MAX + 1.0));
        return p;
    }

    int cost(City city1,City city2)
    {
        int x1=0;
        int y1=0;
        int x2=0;
        int y2=0;
        x1=city1.return_x();
        // cout<<x1;
        y1=city1.return_y();
        x2=city2.return_x();
        y2=city2.return_y();
        double x = x1 - x2; //calculating number to square in next step
        double y = y1 - y2;
        double dist;
        dist = pow(x, 2) + pow(y, 2);//calculating Euclidean distance
        dist = sqrt(dist);
        return dist;
    }
    static int myrandom (int i)
    {
        return rand()%i;
    }
    int travel_cost(City *cit)
    {
        //cit = new City[citysize];
        int tour_cost = 0;
        int num = citysize;
        num = num-1;
        for (int i = 0; i<num; i++ )
        {
            tour_cost += cost(cit[i],cit[i+1]);

        }
        tour_cost += cost(cit[num],cit[0]);
        // cout<<tour_cost<<endl;
        return tour_cost;
    }
    City* genRand(City *city)
    {
        int l,a,b;
        //city = new City[citysize];
        City temp;
        //temp = new City[citysize];
        //temp = nullptr;
        l = citysize;
        a = rand()%l;
        //cout<<a<<endl;
        b = rand()%l;
        //cout<<b<<endl;
        temp = city[a];
        city[a] = city[b];
        city[b] = temp;
        //int blah = city[a].return_x();
        //cout<<blah<<"hi"<<endl;

        return city;
        // }
    }
    double evaluate(City *cities)
    {
        return travel_cost(cities);
    }
//   ~SimulatedAnnealing()
    // {
    //      delete[] cities;
    //  }
};
class Greedy
{
private:
    //int num;
    int citysize;
    City *cities;
public:
    Greedy()
    {
        cities = NULL;
    }
    run(ifstream &infile)
    {
        infile.open("Lab5_partI_input.txt");
        infile>>citysize;
        cities = new City[citysize];
        for(int j = 0 ; j < citysize; j++)
        {
            int num;
            int  x;
            int  y;
            infile>>num;
            infile>>x;
            infile>>y;
            //cout<<y<<endl;
            cities[j].Init_City(num,x,y);
        }
        /*...*/
    }
        int cost(City city1,City city2)
        {
            int x1=0;
            int y1=0;
            int x2=0;
            int y2=0;
            x1=city1.return_x();
            // cout<<x1;
            y1=city1.return_y();
            x2=city2.return_x();
            y2=city2.return_y();
            double x = x1 - x2; //calculating number to square in next step
            double y = y1 - y2;
            double dist;
            dist = pow(x, 2) + pow(y, 2);//calculating Euclidean distance
            dist = sqrt(dist);
            return dist;
        }
        int travel_cost(City *cit)
        {
            //cit = new City[citysize];
            int tour_cost = 0;
            int num = citysize;
            num = num-1;
            for (int i = 0; i<num; i++ )
            {
                tour_cost += cost(cit[i],cit[i+1]);

            }
            tour_cost += cost(cit[num],cit[0]);
            // cout<<tour_cost<<endl;
            return tour_cost;
        }

    ~Greedy()
    {
        /*...*/
    }
    /*...*/
};
/*...*/
int main()
{
    ifstream input;
    //input.open("Lab5_partI_input");
    SimulatedAnnealing SA;
    SA.run(100,1,0.95,input);
    /*...*/
    return 0;
}
