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

unsigned short find_cheapest_line(const struct Network
*n);

int main(){



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


unsigned short is_valid_station(const struct Station *s){
    if (s->type=='m'){
        if (s->line_nb>2 || s->line_nb==0){
            printf("%d is not a valid metro station.\n", s->id);
            return 1;
        }
        return 0;
    }
    else if (s->type=='b'){
        if (s->line_nb>99){
            printf("%d is not a valid bus station.\n", s->id);
            return 1;
            }
        return 0;
        }

    else{
        printf("This station (%d) is neither a bus nor a metro station. This station is invalid.\n",s->id);
        return 1;
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

    int cheapestLineIndex=0;
    int costLines[n->network_size];
    int normConst[n->network_size];

    costLines[0]=0;
    normConst[0]=0;

    if(is_network_valid_iter(&n)){
        for (int g=0; g<n->network_size; g++){
            for (int h=0; h<n->network_size; h++){
                if (n->adj_matrix[g][h]!=$){
                    costLines[g]+=n->adj_matrix[g][h];
                    normConst[g]++;
                }
            }   
        }
    }
    else{
        return USHRT_MAX;
    }

    for (int q=0; q<n->network_size; q++){
        costLines[q]=costLines[q]/normConst[q];
    }
    

    for (int t=1; t<n->network_size; t++){
        if (costLines[t]<costLines[t-1]){
            cheapestLineIndex=t;
        }
    }

    if (n->station[cheapestLineIndex].type=='m'){
        return n->station[cheapestLineIndex].line_nb+99;
    }
    else{
        return n->station[cheapestLineIndex].line_nb;
    }
    
}