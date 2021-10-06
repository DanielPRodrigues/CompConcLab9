        #include <stdio.h>
        #include <stdlib.h>
        #include <pthread.h>
        #include <semaphore.h>
        #define threadc 1
        #define threadp 1
        #define n 5

        //variáveis globais
        int b[n]; //buffer
        int iter;
        int y=0,z=0; //for
        int k = 0; //constante
        sem_t buffercheio, slotvazio;

        //thread produtora
        void *produtor (void *t) {
        while(y<iter) {
        sem_wait(&slotvazio);
        while (k>(n-2)){
        printf("O consumidor precisou ser ativo\n");
        sem_post(&buffercheio);
        sem_wait(&slotvazio);
        }
        b[k]=rand()%1000+1;
        k++;
        y++;
        sem_post(&slotvazio);
        }
        pthread_exit(NULL);
        }

        //thread consumidora
        void *consumidor (void *t) {
        while(z<iter) {
        sem_wait(&buffercheio);
        while(k>=1){
        b[k]=NULL;
        k--;
        z++;
        if(k<n-1){
        printf("Liberou espaco no buffer\n");
        sem_post(&slotvazio);
        }}}
        pthread_exit(NULL);
        }


        int main(int argc, char *argv[]) {
        int i, j, l;
        pthread_t threads[threadc];
        printf("Digite o numero iteracoes (pelo menos 5): ");
        scanf("%d",&iter);
        puts("");


        //semáforo
        sem_init(&slotvazio, 0, 0);
        sem_init(&buffercheio, 0, 0);
        sem_post(&slotvazio);


        for (i = 0; i < threadp; i++) { //criando threads
        pthread_create(&threads[i], NULL, produtor, NULL);
        }
        for (j = threadp; j < (threadc+threadp); j++) {
        pthread_create(&threads[j], NULL, consumidor, NULL);
        }


        //funçao pthread join
        for (l = 0; l < (threadc+threadp); l++) {
        pthread_join(threads[l], NULL);
        }

        return 0;
        }
