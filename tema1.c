#include <stdio.h>
#include <stdlib.h>
#include "operatii.c"
#include <string.h>
typedef struct vagon{
    char caracter;
    struct vagon* next;
    struct vagon* prev;
}Tvagon;
typedef struct trenuletul{
    Tvagon* locomotiva;
    Tvagon* mecanic;
}Ttrenulet;
typedef struct comenziNode{
    struct comenziNode* next;
    struct comenziNode* prev;
    char comanda[100];
    char param[1000];
}comenziNode;
typedef struct listaComenzi{
    comenziNode* first;
    comenziNode* last;
}listaComenzi;
listaComenzi* makeListaComenzi(){
    listaComenzi* lista=calloc(1,sizeof(listaComenzi));
    return lista;
}
comenziNode* makeComanda(){
    comenziNode* comanda=calloc(1,sizeof(comenziNode));
    return comanda;
}
Tvagon* createVagon(){
    Tvagon* vagon=calloc(1,sizeof(Tvagon));
    vagon->caracter='#';
    return vagon;
}
Tvagon* initLocomotiva(){
    Tvagon* locomotiva=calloc(1,sizeof(Tvagon));
    locomotiva->next=calloc(1,sizeof(Tvagon));
    locomotiva->prev=locomotiva->next;
    locomotiva->next->next=locomotiva;
    locomotiva->next->prev=locomotiva;
    locomotiva->next->caracter='#';
    return locomotiva;
}
void MOVE_RIGHT(Ttrenulet* trenuletul){
    if(trenuletul->mecanic->next==trenuletul->locomotiva){
        Tvagon* vagon=createVagon();
        vagon->next=trenuletul->locomotiva;
        trenuletul->locomotiva->prev->next=vagon;
        vagon->prev=trenuletul->locomotiva->prev;
        trenuletul->locomotiva->prev=vagon;
        trenuletul->mecanic=trenuletul->mecanic->next;
        return;
    }
    trenuletul->mecanic=trenuletul->mecanic->next;
}
void MOVE_LEFT(Ttrenulet* trenuletul){
    if(trenuletul->mecanic->prev==trenuletul->locomotiva){
        trenuletul->mecanic=trenuletul->locomotiva->prev;
        return;
    }
    trenuletul->mecanic=trenuletul->mecanic->prev;
}
void WRITE(Ttrenulet* trenuletul,char caracter){
    trenuletul->mecanic->caracter=caracter;
}
void SHOW(Ttrenulet* trenuletul,FILE* file){
    Tvagon* curr=trenuletul->locomotiva->next;
    do
    {
        if(curr==trenuletul->mecanic){
            fprintf(file,"|%c| ",curr->caracter);
            curr=curr->next;
        }else{
            fprintf(file,"%c ",curr->caracter);
            curr=curr->next;
        }
        

    } while (curr!=trenuletul->locomotiva);
    fprintf(file,"\n");
}
void CLEAR_CELL(Ttrenulet* trenuletul){
    if(trenuletul->mecanic->prev==trenuletul->mecanic->next){
        WRITE(trenuletul,'#');
        return;
    }
    Tvagon* tmp;
    tmp=trenuletul->mecanic;
    if(trenuletul->mecanic->prev==trenuletul->locomotiva){
        trenuletul->mecanic=trenuletul->locomotiva->prev;
    }
    else{
        trenuletul->mecanic=trenuletul->mecanic->prev;
    }
    tmp->prev->next=tmp->next;
    tmp->next->prev=tmp->prev;
    free(tmp);
    /*if(trenuletul->mecanic->prev==trenuletul->mecanic->next){
        WRITE(trenuletul,'#');
        return;
    }
    Tvagon* tmp=trenuletul->mecanic;
    if(tmp->prev==trenuletul->locomotiva){
        trenuletul->mecanic=trenuletul->locomotiva->prev;
        trenuletul->locomotiva->next=trenuletul->locomotiva->next->next;
        free(tmp);
    }else{
        tmp->prev->next=tmp->next;
        tmp->next->prev=tmp->prev;
        trenuletul->mecanic=tmp->prev;
        free(tmp);
    }*/
}
void CLEAR_ALL(Ttrenulet* trenuletul){
    while(trenuletul->mecanic->next!=trenuletul->mecanic->prev){
        CLEAR_CELL(trenuletul);
    }
    CLEAR_CELL(trenuletul);
}
void INSERT_LEFT(Ttrenulet* trenuletul,char caracter){
    if(trenuletul->mecanic->prev==trenuletul->locomotiva){
        printf("ERROR\n");
        return;
    }
    Tvagon* vagon=createVagon();
    vagon->prev=trenuletul->mecanic->prev;
    vagon->next=trenuletul->mecanic;
    trenuletul->mecanic->prev->next=vagon;
    trenuletul->mecanic->prev=vagon;
    trenuletul->mecanic=trenuletul->mecanic->prev;
    WRITE(trenuletul,caracter);
}
void INSERT_RIGHT(Ttrenulet* trenuletul,char caracter){
    Tvagon* vagon=createVagon();
    vagon->prev=trenuletul->mecanic;
    vagon->next=trenuletul->mecanic->next;
    trenuletul->mecanic->next->prev=vagon;
    trenuletul->mecanic->next=vagon;
    trenuletul->mecanic=trenuletul->mecanic->next;
    WRITE(trenuletul,caracter);
}
void SEARCH(Ttrenulet* trenuletul,char* word){
    int i = 0;
    char letter=word[i];
    Tvagon* tmp=trenuletul->mecanic;
    Tvagon* where;
    while(letter!='\0'){
        if(letter==tmp->caracter){
            if(i==0){
                where=tmp;
            }
            letter=word[++i];
        }else{
            letter=word[0];
        }
        tmp=tmp->next;
        if(tmp==trenuletul->mecanic){
            if(letter=='\0'){
                break;
            }
            printf("ERROR\n");
            return;
        }
    }
    trenuletul->mecanic=where;
}
void SEARCH_LEFT(Ttrenulet* trenuletul,char* word){
     int i = 0;
    char letter=word[i];
    Tvagon* tmp=trenuletul->mecanic;
    while(letter!='\0'){
        if(letter==tmp->caracter){
            letter=word[++i];
        }else{
            letter=word[0];
        }
        tmp=tmp->prev;
        if(tmp==trenuletul->locomotiva){
            if(letter=='\0'){
                break;
            }
            printf("ERROR\n");
            return;
        }
    }
    trenuletul->mecanic=tmp->next;
}
void SEARCH_RIGHT(Ttrenulet* trenuletul,char* word){
    int i = 0;
    char letter=word[i];
    Tvagon* tmp=trenuletul->mecanic;
    while(letter!='\0'){
        if(letter==tmp->caracter){
            letter=word[++i];
        }else{
            letter=word[0];
        }
        tmp=tmp->next;
        if(tmp==trenuletul->locomotiva){
            if(letter=='\0'){
                break;
            }
            printf("ERROR\n");
            return;
        }
    }
    trenuletul->mecanic=tmp->prev;
}
void SHOW_CURRENT(Ttrenulet* trenuletul,FILE* file){
    fprintf(file,"%c\n",trenuletul->mecanic->caracter);
}
void SWITCH(listaComenzi* lista){
    comenziNode* tmp=lista->first;
    comenziNode* tmp1;
    while(tmp!=NULL){
        tmp1=tmp->next;
        tmp->next=tmp->prev;
        tmp->prev=tmp1;
        tmp=tmp1;
    }
    tmp1=lista->first;
    lista->first=lista->last;
    lista->last=tmp1;
}
void EXECUTE(listaComenzi* lista,Ttrenulet* trenuletul){
    if(!(strcmp(lista->first->comanda,"MOVE_RIGHT"))){
        MOVE_RIGHT(trenuletul);
    }
    else if(!(strcmp(lista->first->comanda,"SWITCH"))){
        SWITCH(lista);
    }
    else if(!(strcmp(lista->first->comanda,"SEARCH_RIGHT"))){
        SEARCH_RIGHT(trenuletul,lista->first->param);
    }
    else if(!(strcmp(lista->first->comanda,"SEARCH_LEFT"))){
        SEARCH_LEFT(trenuletul,lista->first->param);
    }
    else if(!(strcmp(lista->first->comanda,"SEARCH"))){
        SEARCH(trenuletul,lista->first->param);
    }
    else if(!(strcmp(lista->first->comanda,"INSERT_RIGHT"))){
        INSERT_RIGHT(trenuletul,lista->first->param[0]);
    }
    else if(!(strcmp(lista->first->comanda,"INSERT_LEFT"))){
        INSERT_LEFT(trenuletul,lista->first->param[0]);
    }
    else if(!(strcmp(lista->first->comanda,"CLEAR_ALL"))){
        CLEAR_ALL(trenuletul);
    }
    else if(!(strcmp(lista->first->comanda,"CLEAR_CELL"))){
        CLEAR_CELL(trenuletul);
    }
    else if(!(strcmp(lista->first->comanda,"WRITE"))){
        WRITE(trenuletul,lista->first->param[0]);
    }
    else if(!(strcmp(lista->first->comanda,"MOVE_LEFT"))){
        MOVE_LEFT(trenuletul);
    }
    comenziNode* tmp=lista->first;
    lista->first=tmp->next;
    if(lista->first==NULL){
        lista->last=NULL;
    }
    free(tmp);
}
void free_trenuletul(Ttrenulet* trenuletul) {
    CLEAR_ALL(trenuletul);
    free(trenuletul->locomotiva->next);
    free(trenuletul->locomotiva);
    free(trenuletul);
}
void free_lista(listaComenzi* lista){
    free(lista);
}


int main(){
    //INIT TRENULETUL
    Ttrenulet* trenuletul=calloc(1,sizeof(Ttrenulet));
    trenuletul->locomotiva=initLocomotiva();
    trenuletul->mecanic=trenuletul->locomotiva->next;
    //INIT LISTA DE COMENZI
    listaComenzi* lista=makeListaComenzi();
    //CITESTE COMENZILE
    FILE * file;
    file=fopen("tema1.in","r");
    FILE *output_file;
    output_file = fopen("tema1.out", "w");
    int n=0;
    fscanf(file,"%d",&n);
    char command[100];
    lista->first=lista->last=makeComanda();
    fscanf(file,"%s",command);
    if(strcmp(command,"EXECUTE")){  
        if(!strcmp(command,"SHOW")){
            SHOW(trenuletul,output_file);
        }else if(!strcmp(command,"SHOW_CURRENT")){
            SHOW_CURRENT(trenuletul,output_file);
        }
        else if(!(strcmp(command,"SWITCH"))){
            SWITCH(lista);
        }
        else{
            strcpy(lista->first->comanda,command);
        }
    }
    if((strcmp(lista->first->comanda,"SEARCH") == 0 || strcmp(lista->first->comanda,"SEARCH_LEFT") == 0 || 
        strcmp(lista->first->comanda,"SEARCH_RIGHT") == 0 || strcmp(lista->first->comanda,"WRITE") == 0 || 
        strcmp(lista->first->comanda,"INSERT_RIGHT") == 0 || strcmp(lista->first->comanda,"INSERT_LEFT") == 0)){
        fscanf(file,"%s",lista->first->param);
    }
    for(int i = 1;i<n;i++){
        comenziNode* tmp=makeComanda();
        fscanf(file,"%s",command);
        if(!strcmp(command,"EXECUTE")){  
            EXECUTE(lista,trenuletul);
            free(tmp);
            continue;
        }
        else if(!strcmp(command,"SHOW")){
            SHOW(trenuletul,output_file);
            free(tmp);
            continue;
        }
        else if(!strcmp(command,"SHOW_CURRENT")){
            SHOW_CURRENT(trenuletul,output_file);
            free(tmp);
            continue;
        }
        else if(!(strcmp(command,"SWITCH"))){
            SWITCH(lista);
            free(tmp);
            continue;
        }
        else{
            strcpy(tmp->comanda,command);
        }
        if((strcmp(tmp->comanda,"SEARCH") == 0 || strcmp(tmp->comanda,"SEARCH_LEFT") == 0 || 
        strcmp(tmp->comanda,"SEARCH_RIGHT") == 0 || strcmp(tmp->comanda,"WRITE") == 0 || 
        strcmp(tmp->comanda,"INSERT_RIGHT") == 0 || strcmp(tmp->comanda,"INSERT_LEFT") == 0)){
            fscanf(file,"%s",tmp->param);
        }
        lista->last->next=tmp;
        tmp->prev=lista->last;
        lista->last=tmp;
    }
    free_lista(lista);
    free_trenuletul(trenuletul);
    fclose(file);
    fclose(output_file);
    return 0;
}
