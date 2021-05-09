#include <stdio.h>
#define MAX_PATH 1000

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



struct Station build_station_(char type, unsigned short
line_nb, int id);

struct Station build_station();

unsigned short is_valid_station(const struct Station *s);

void print_station(const struct Station *s);

unsigned short is_valid_path_iter(const struct Path *p);

unsigned short is_valid_path_rec(const struct Path
*p, unsigned short curr_size);

void print_path(const struct Path *p);

int main(){

    struct Station st1 = build_station();
    struct Station st2 = build_station();
    struct Path test;
    test.path_size=2;
    test.stationSeq[0]=st1;
    test.stationSeq[1]=st2;
    print_path(&test);
    return 0;
}

struct Station build_station_(char type, unsigned short
line_nb, int id){
    struct Station dummyStation;
    dummyStation.type=type;
    dummyStation.line_nb=line_nb;
    dummyStation.id=id;
    return dummyStation;
}

struct Station build_station(){
    char dummyType;
    unsigned short dummyLine_nb;
    int dummyId;
    printf("Enter the station type:\n");
    scanf(" %c", &dummyType);
    printf("Enter the station line number:\n");
    scanf("%hu", &dummyLine_nb);
    printf("Enter the station ID:\n");
    scanf("%d", &dummyId);
    return build_station_(dummyType, dummyLine_nb, dummyId);
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

void print_station(const struct Station *s){
    if (is_valid_station(s)==0){
        if (s->type=='b'){
            printf("%d is a bus station using line %hu.\n", s->id, s->line_nb);
        }
        else{
             printf("%d is a metro station using line %hu.\n", s->id, s->line_nb);
        }
    }
}

unsigned short is_valid_path_iter(const struct Path *p){
    for(int i=1; i<p->path_size; i++){
        if (p->stationSeq[i].id==p->stationSeq[i-1].id){
            if(p->stationSeq[i].type==p->stationSeq[i-1].type && p->stationSeq[i].line_nb==p->stationSeq[i-1].line_nb){
                printf("Error: path goes from a station to itself\n");
                return 0;
            }
        }
        else{
            if (p->stationSeq[i].type==p->stationSeq[i-1].type && p->stationSeq[i].line_nb==p->stationSeq[i-1].line_nb){
               if (p->stationSeq[i].id-p->stationSeq[i-1].id>10 || p->stationSeq[i].id-p->stationSeq[i-1].id<-10){
                    printf("Error: stations are not consecutive\n");
                    return 0;
                }
            }
            else{
                printf("Error: stations are not consecutive\n");
                return 0;
            }
        }
    }
    return 1;
}

unsigned short is_valid_path_rec(const struct Path
*p, unsigned short curr_size){
    if(curr_size==0){
        return 1;
    }

    if (p->stationSeq[curr_size].id==p->stationSeq[curr_size-1].id){
        if(p->stationSeq[curr_size].type==p->stationSeq[curr_size-1].type && p->stationSeq[curr_size].line_nb==p->stationSeq[curr_size-1].line_nb){
            return 0;
        }
        return is_valid_path_rec(p,curr_size-1);
    }

        else{
            if (p->stationSeq[curr_size].type==p->stationSeq[curr_size-1].type && p->stationSeq[curr_size].line_nb==p->stationSeq[curr_size-1].line_nb){
               if (p->stationSeq[curr_size].id-p->stationSeq[curr_size-1].id>10 || p->stationSeq[curr_size].id-p->stationSeq[curr_size-1].id<-10){
                    printf("Error: stations are not consecutive\n");
                    return 0;
                }
                return is_valid_path_rec(p,curr_size-1);
            }
            else{
                printf("Error: stations are not consecutive\n");
                return 0;
            }
        }
}

void print_path(const struct Path *p){
    if(is_valid_path_rec(p,p->path_size-1)){
        for(int i=0; i<p->path_size; i++){
            printf("->");
            print_station(&p->stationSeq[i]);
            }
    }
}

