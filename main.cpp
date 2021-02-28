#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

const int numberOfpopulations = 25;
const int numberOfdimentions = 2;
const int numberOfmaxiter = 50;

double get_random(double min, double max) {
    /* Returns a random double between min and max */
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

class Population{
    public:
        int dimension = numberOfdimentions;
        vector<double> position;
        void push_data() {
            for (int i = 0; i < dimension; i++) {
                double d1 = get_random(-50, 50);
                position.push_back(d1);
            }
        }

        void print_pos(){
            cout << "i'm at : [" ;
            for (auto i = position.begin(); i != position.end(); ++i)
                cout << *i << " ";
            cout << "]" << endl;
        }
};

class Optimizer{
    public:
        int n_populations = numberOfpopulations;
        vector<Population> populations;
        Population gbest;
        double gbest_value = 1.79769e+308 ;
        Population gworst;
        double gworst_value = 2.22507e-308;
        vector<double> func_value;

        double fitness(Population population){
           double x = population.position[0];
           double y = population.position[1];
           // booth function
           return pow((x + 2 * y - 7) , 2) + pow ((2 * x  + y - 5), 2);
        }

        void print_pos_op(){
            for ( int i  = 0 ;  i < n_populations ; i++ ){
                populations.at(i).print_pos();
            }
        }

        void setGbest(){
            for ( int  i  = 0; i < n_populations ; i++){
                double fit_candicate = fitness(populations.at(i));
                    if(fit_candicate < gbest_value){
                        gbest_value = fit_candicate;
                        gbest = populations.at(i);
                    }
            }
        }

        void setGworst(){
            gworst_value = 2.22507e-308;
            for ( int  i  = 0; i < n_populations ; i++){
                double fit_candicate = fitness(populations.at(i));
                if(fit_candicate >  gworst_value){
                    gworst_value = fit_candicate;
                    gworst = populations.at(i);
                }
            }
        }

        void calculate_f(){
            func_value.clear();
            for ( int  i  = 0 ; i < n_populations ;  i++ ){
                double fit_candicate  =  fitness(populations.at(i));
                func_value.push_back(fit_candicate);
            }
        }

        void changePopulation(){
            for ( int i = 0 ; i < n_populations ; i++ ){
                Population new_population;
                for ( int j  = 0 ; j < numberOfdimentions ; j++){
                    double  new_pos_of_population  = populations.at(i).position.at(j) +
                            get_random(0,1) * (gbest.position.at(j) - abs(populations.at(i).position.at(j))) -
                            get_random(0,1) * (gworst.position.at(j) - abs(populations.at(i).position.at(j))) ;
                    new_population.position.push_back(new_pos_of_population);
                }
                double new_fitness  =  fitness(new_population);
                if ( new_fitness < fitness(populations.at(i))){
                    populations.at(i) = new_population;
                }

            }
        }
};

int main(){
    srand(time(NULL));
    Optimizer op;
    for ( int i = 0 ; i <  numberOfpopulations ; i++ ){
        Population p;
        p.push_data();
        op.populations.push_back(p);
    }
    for( int i = 0 ;  i < numberOfmaxiter ; i++){
        op.print_pos_op();
        op.calculate_f();
        op.setGbest();
        op.setGworst();
        for ( int j  = 0 ;  j <  numberOfpopulations ; j++ ){
            cout  << op.func_value.at(j) << " ";
        }
        cout << endl;
        op.changePopulation();
    }
    cout << "result best is : ";
    op.gbest.print_pos() ;
    cout << "value best is : " <<  op.gbest_value ;
    return 0;
}