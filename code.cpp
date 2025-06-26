#include <stdio.h>
#include <stdlib.h>

struct nodo{
	unsigned int distanza_da_zero;
	unsigned int colore;
};

struct grafo100{
	unsigned int indice_grafo;
	unsigned int sommatoria_cammini_minimi;
};

struct grafo{
	unsigned int indice_grafo;
	unsigned int sommatoria_cammini_minimi;
	struct grafo* avanti;
	struct grafo* indietro;
};

struct grafo* crea_grafo (unsigned int indice, unsigned int somma){
    struct grafo* p = (struct grafo*) malloc(sizeof(struct grafo));
    p->indice_grafo = indice;
    p->sommatoria_cammini_minimi = somma;
    p->avanti = NULL;
    p->indietro = NULL;
    return p;
}

char* stringtok(char* destinazione, char* stringa, char carattere){
	char* output = destinazione;
	while( *stringa != carattere ){
		*output = *stringa;
		output++;
		stringa++;
	}
	*output = '\0';
	stringa++;
	char* str = stringa;
	return str;
}

unsigned int atoimio(char* stringa){
	unsigned int output = 0;
	for(int i=0; stringa[i]!='\0'; i++){
		if(stringa[i]!='\n')
			output = (output*10)+stringa[i]-'0';
	}
	return output;
}

int main () {
    	unsigned int n_nodi, K, Z;
    	unsigned int tutti_colorati;
    	unsigned int cont = 0;
    	unsigned int sommatoria;
    	unsigned int distanza_nuova=0;
    	unsigned int condition = 0;
    	unsigned int media;
    	unsigned int temp1, temp2;
    	unsigned int v;
    	char AggiungiGrafo[15];
    	char ACapo[2];
    	char str[100000];
    	char q[100000];
		char* w;
		struct grafo* min=NULL;
		struct grafo* max=NULL;
		struct grafo* inizio=NULL;
		struct grafo* nuovo=NULL;
		struct grafo* scorritore=NULL;
	 
    	if (fscanf (stdin, "%d", &n_nodi) == -1)                 
        	printf ("Error\n");

    	if (fscanf (stdin, "%d", &K) == -1)
        	printf ("Error\n");

    	unsigned int MAT[n_nodi][n_nodi];
    	unsigned int minimo_indice = 0;
    	unsigned int minimo_distanza;
    	unsigned int somma_riga;
    	struct grafo100 GRAFI[120];
		struct nodo NODI[n_nodi];
		NODI[0].distanza_da_zero = 0;
    	NODI[0].colore = 1;
		int i=0;
		int j=0;
	
		if(fgets(ACapo, 2, stdin)==NULL)
			printf("Error"); 
	
		while(!feof(stdin)){	              
   
			if(fgets(AggiungiGrafo, 15, stdin)==NULL && condition==0)
    			printf("Error");

    	    if(AggiungiGrafo[0]!='T'){
        	
				condition=0;
        		i=0;
        	
        		while( i!=n_nodi ){
            
					j = 0;
            
			    	if(fgets(str, 100000, stdin)==NULL)
            	    	printf("Error");
                
   					while (j != n_nodi){
   						if(j==0)
   							w = stringtok (q,str,',');
   						else{
   							if(j!=n_nodi-1)
								w = stringtok (q,w,',');
							else
								w = stringtok (q,w,'\0');
						}
						MAT[i][j] = atoimio(q);					 
						j++;                                            
        	    	}
					i++;
        		}
        		
        		somma_riga = 0;
        		j=1;
        		
				while( j != n_nodi ){
					NODI[j].distanza_da_zero = MAT[0][j];
					NODI[j].colore = 0;
					somma_riga = somma_riga + MAT[0][j];
					j++;
				} 
		
				tutti_colorati = 1;
			
				if( somma_riga == 0)
					tutti_colorati = 0;
			
				while( tutti_colorati != 0 ){
					tutti_colorati = 0;
					j=1;
					minimo_distanza = 2099999999; 
				                  
					while( j != n_nodi ){
						if( NODI[j].colore != 1 ){
							if( NODI[j].distanza_da_zero != 0 ){
								if( NODI[j].distanza_da_zero < minimo_distanza ){
									minimo_distanza = NODI[j].distanza_da_zero;
									minimo_indice = j;
								}
							}
						}
						j++;
					}
					
					NODI[minimo_indice].colore = 1;
					i=1;
				
					while( i != n_nodi ){
						if( MAT[minimo_indice][i] != 0 ){
							if( NODI[i].colore != 1 ){
								distanza_nuova = MAT[minimo_indice][i] + minimo_distanza;
								if( distanza_nuova < NODI[i].distanza_da_zero || NODI[i].distanza_da_zero == 0 )
									NODI[i].distanza_da_zero = distanza_nuova;
							}
						}
						if( NODI[i].colore != 1 && NODI[i].distanza_da_zero != 0 )
							tutti_colorati=1;
						i++;
					}
				}       	

				sommatoria=0;  

				for(int d=0; d!=n_nodi; d++)
					sommatoria = sommatoria + NODI[d].distanza_da_zero;

				if(K<100){
					if(cont==0){
					GRAFI[0].indice_grafo = 0;
					GRAFI[0].sommatoria_cammini_minimi = sommatoria;
				}
				else{
					if(cont<K){
						v = cont;
						GRAFI[v].indice_grafo = v;
						GRAFI[v].sommatoria_cammini_minimi = sommatoria;
						while( v!=0 && GRAFI[v].sommatoria_cammini_minimi < GRAFI[v-1].sommatoria_cammini_minimi ){
							temp1 = GRAFI[v].indice_grafo;
							temp2 = GRAFI[v].sommatoria_cammini_minimi;
							GRAFI[v].indice_grafo = GRAFI[v-1].indice_grafo;
							GRAFI[v].sommatoria_cammini_minimi = GRAFI[v-1].sommatoria_cammini_minimi;
							GRAFI[v-1].indice_grafo = temp1;
							GRAFI[v-1].sommatoria_cammini_minimi = temp2;
							v--;
						}
					}
					else{
						v = K-1;
						if( sommatoria < GRAFI[v].sommatoria_cammini_minimi ){
							GRAFI[v].indice_grafo = cont;
							GRAFI[v].sommatoria_cammini_minimi = sommatoria;
						}
						while( v!=0 && GRAFI[v].sommatoria_cammini_minimi < GRAFI[v-1].sommatoria_cammini_minimi ){
							temp1 = GRAFI[v].indice_grafo;
							temp2 = GRAFI[v].sommatoria_cammini_minimi;
							GRAFI[v].indice_grafo = GRAFI[v-1].indice_grafo;
							GRAFI[v].sommatoria_cammini_minimi = GRAFI[v-1].sommatoria_cammini_minimi;
							GRAFI[v-1].indice_grafo = temp1;
							GRAFI[v-1].sommatoria_cammini_minimi = temp2;
							v--;
						}	
					}	
				}	
			}
			
			else{
				nuovo = crea_grafo(cont,sommatoria);
				if(cont==0){
					min = nuovo;
					max = nuovo;
				}
				else{
					if(cont==1){
						if( nuovo->sommatoria_cammini_minimi > min->sommatoria_cammini_minimi ){
							min->avanti = nuovo;
							max = nuovo;
							max->indietro = min;
						}
						else{
							nuovo->avanti = min;
							max->indietro = nuovo;
							min = nuovo;
						}
					}
					else{
						if( nuovo->sommatoria_cammini_minimi > max->sommatoria_cammini_minimi ){
							max->avanti = nuovo;
							nuovo->indietro = max;
							max = nuovo;
						}
						else{
							if( nuovo->sommatoria_cammini_minimi < min->sommatoria_cammini_minimi ){
								nuovo->avanti = min;
								min->indietro = nuovo;
								min = nuovo;
							}
							else{
								media = (min->sommatoria_cammini_minimi+max->sommatoria_cammini_minimi)/2;
								if( nuovo->sommatoria_cammini_minimi < media ){
									scorritore = min;
									while( nuovo->sommatoria_cammini_minimi > scorritore->avanti->sommatoria_cammini_minimi )
										scorritore = scorritore->avanti;
									nuovo->avanti = scorritore->avanti;
									scorritore->avanti = nuovo;
									nuovo->indietro = scorritore;
									scorritore->avanti->indietro = nuovo;
								}
								else{
									scorritore = max;
									while( nuovo->sommatoria_cammini_minimi < scorritore->indietro->sommatoria_cammini_minimi )
										scorritore = scorritore->indietro;
									nuovo->avanti = scorritore;
									scorritore->indietro->avanti = nuovo;
									nuovo->indietro = scorritore->indietro;
									scorritore->indietro = nuovo;
								}
							}
						}
					}
				}
			}
			cont++;	                                           
		}           
	                                    
    	else{
        	condition++;
       		if(condition<=1){
       			if(K>cont)
       				Z = cont;
   				else
        			Z = K;
        		if(K>100){
        			inizio = min;
        			for(int i=0; i!=Z-1; i++){
        				if(cont!=0){
        					printf("%d ",inizio->indice_grafo);
        					inizio = inizio->avanti;
						}
    					else
    						break;
    				}
    				if(cont!=0)
            	    	printf("%d",inizio->indice_grafo);
    				printf("\n");
				}
				else{
					for(int i=0; i!=Z-1; i++){
                    	if(cont!=0)
                    	   	printf("%d ",GRAFI[i].indice_grafo);
                   		else
                   			break;
                	}
                	if(cont!=0)
                    	printf("%d",GRAFI[Z-1].indice_grafo);
               		printf("\n");
				}
			}
		}		 
	}                                                         		
    return(0);
}
