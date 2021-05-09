#include <stdio.h>
#include <limits.h>
#define MAX_NETWORK 50
#define MAX_PATH 1000
int $ = INT_MAX;

struct Station
{
    char type;
    unsigned short line_nb;
    int id;
};

struct Path
{
    unsigned short path_size;
    struct Station stationSeq[MAX_PATH];

};

struct Network
{
    int network_size;
    int adj_matrix[MAX_NETWORK][MAX_NETWORK];
    struct Station station[MAX_NETWORK];
};

struct Network build_small_network();

unsigned short is_network_valid_iter(const struct Network
*n);

unsigned short is_valid_station(const struct Station *s);

void swap(int * p1, int * p2);

unsigned short find_cheapest_line(const struct Network
*n);

int main(){

    struct Network n;
    n=build_small_network();

    printf("%d", find_cheapest_line(&n));


    return 0;
}




struct Network build_small_network(){
    struct Network dummyNetwork;

    dummyNetwork.network_size=12;
    int dummyAdjMatrix[MAX_NETWORK][MAX_NETWORK]={
        {$,11,6,$,$,$,$,$,$,$,$,$},
        {11,$,$,$,$,$,8,$,$,$,$,$},
        {$,$,$,10,7,$,$,$,$,$,$,$},
        {$,$,15,$,$,$,$,$,$,$,14,$},
        {$,$,$,$,$,8,$,$,$,$,$,$},
        {$,$,$,$,$,$,$,$,$,$,$,$},
        {$,8,$,$,$,$,$,9,$,$,$,$},
        {$,$,$,$,$,$,9,$,3,$,$,$},
        {$,$,$,$,$,$,$,3,$,9,$,$},
        {$,$,$,$,$,$,$,$,7,$,$,$},
        {$,$,$,$,$,$,$,$,$,13,$,$},
        {$,$,$,12,$,$,$,$,$,$,$,$}};

    for(int i=0; i<dummyNetwork.network_size; i++){
        for (int j=0; j<dummyNetwork.network_size; j++){
            dummyNetwork.adj_matrix[i][j]=dummyAdjMatrix[i][j];
        }
    }


    dummyNetwork.station[0]=(struct Station){'m',1,10};
    dummyNetwork.station[1]=(struct Station){'m',2,10};
    dummyNetwork.station[2]=(struct Station){'m',1,11};
    dummyNetwork.station[3]=(struct Station){'b',42,11};
    dummyNetwork.station[4]=(struct Station){'m',1,12};
    dummyNetwork.station[5]=(struct Station){'m',1,13};
    dummyNetwork.station[6]=(struct Station){'m',2,21};
    dummyNetwork.station[7]=(struct Station){'m',2,22};
    dummyNetwork.station[8]=(struct Station){'m',2,23};
    dummyNetwork.station[9]=(struct Station){'b',42,23};
    dummyNetwork.station[10]=(struct Station){'b',42,122};
    dummyNetwork.station[11]=(struct Station){'b',42,132};

    return dummyNetwork;
}


void swap(int * p1, int * p2){
int temp = *p1;
*p1 = *p2;
*p2 = temp;
}


unsigned short is_valid_station(const struct Station *s){
    if (s->type=='m'){
        if (s->line_nb>2 || s->line_nb==0){
            printf("%d is not a valid metro station.\n", s->id);
            return 0;
        }
        return 1;
    }
    else if (s->type=='b'){
        if (s->line_nb>150){
            printf("%d is not a valid bus station.\n", s->id);
            return 0;
            }
        return 1;
        }

    else{
        printf("This station (%d) is neither a bus nor a metro station. This station is invalid.\n",s->id);
        return 0;
    }
}


unsigned short is_network_valid_iter(const struct Network
*n){

    for (int e = 1; e < n->network_size; e++){

        if (is_valid_station(&n->station[e-1])==0){
            return 0;
        }


        if (n->station[e].id >= n->station[e-1].id){
            if (n->station[e].id == n->station[e-1].id){
                if (n->station[e].line_nb < n->station[e-1].line_nb){
                    return 0;
                }
                if (n->station[e].line_nb == n->station[e-1].line_nb && n->station[e].type == 'm' && n->station[e-1].type=='b'){
                    return 0;
                }  
            }
        }
        else{
            return 0;
        }



        for (int f=0; f < n->network_size; f++){
            if(n->adj_matrix[e-1][f]<0){
                return 0;
            }
        }
        
        
    }

    return 1;
}


unsigned short find_cheapest_line(const struct Network
*n){

    struct lineType{
        char type;
        int line_nb;
    };

    int dummyArray[n->network_size];
    
    for(int o=0; o<n->network_size;o++){
        dummyArray[0]=n->station[o].line_nb;
    }
    
    int difLines=n->network_size;

    for (int q=0; q<n->network_size; q++){
        for (int f = 0; f < q; f++){
            if (dummyArray[q]==dummyArray[f]){
                dummyArray[f]= -1;
                difLines--;
            }
        }    
    }

    struct lineType linesArray[difLines];

    int a=0;

    for (int y = 0; y < n->network_size; y++){
        if (dummyArray[y]!=-1){
           linesArray[a].type = n->station[y].type;
           linesArray[a].line_nb = n->station[y].line_nb; 
           a++; 
        }
    }

    float prices[a];
    int normConst[a];

    for (int t = 0; t < a; t++)
    {
        normConst[t]=1;
    }
    


    for ( int b = 0; b < a; b++){

        for (int g=0; g<n->network_size; g++){

            for (int h=0; h<n->network_size; h++){

                if (n->adj_matrix[g][h]!=$ && n->station[g].line_nb==linesArray[b].line_nb && n->station[g].type==linesArray[b].type){

                    prices[b]+=n->adj_matrix[g][h];
                    normConst[b]++;
                }
            }   
        }
    }

    for (int j = 0; j < a; j++)
    {
        prices[j]=prices[j]/normConst[j];
    }

    int indexMin;

    for (int z = 1; z < a; z++){
        if (prices[z]<prices[a]){
            indexMin=z;
        }  
    }
    
    if ( linesArray[indexMin].type=='m'){
        return linesArray[indexMin].line_nb+99;
    }
    else{
        return linesArray[indexMin].line_nb;
    }
}