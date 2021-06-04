#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <fcntl.c>
#include <string.h>
#include <pthread.h>


int total;
int it =0;
//int gen=0;
int mm,nn;
int** sarr;
int** rarr;
int** farr;
void *paral(void *arg);
void rowtest(int i);
int neighborNum2(int i,int j);
void call_sig();
int runn;
int seqn;
int end = 3;

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_t tid[10000];

void call_sig(){
	sleep(1);
	//pthread_cond_broadcast(&cond);
	pthread_cond_signal(&cond);
}

void mkthr(int **arr,int repeat,int m, int n,int runnum)
{
	FILE *fp;
	char head[30] = "gen_";
	char extra[20];
	char tail[10] = ".matrix";
	char buff;
	char seqarr[20];
	
	strcpy(extra,head);

	FILE *rfp;
	char resf[20] = "output.matrix";
	mm = m;
	nn = n;
	runn = runnum;
	
	total = repeat;//세대 진행을 할 총 수행 횟수
	int status;
	//int num_threads = runnum;
	//pthread_t tid[num_threads];
	
	//이거 지웠음!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//pthread_t tid[10000];
	int *id = (int*)malloc(sizeof(int)*runnum);

	//세대 진행시 임시저장할 이차원 배열
	sarr = (int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++)
		sarr[i] = (int*)malloc(sizeof(int)*n);

	farr = (int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++)
		farr[i] = (int*)malloc(sizeof(int)*n);

	rarr = (int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++)
		rarr[i] = (int*)malloc(sizeof(int)*n);

	

	//rarr에 arr을 복사
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			rarr[i][j] = arr[i][j];
			farr[i][j] = arr[i][j];
		}
		
	for(int k=1;k<=repeat;k++){

		seqn = k;
		it =0;
			//runnum개의 스레드 생성
		printf("스레드 생성\n");
		for(int i=0;i<runnum;i++)
		{
			id[i] = i;
			
			if(pthread_create(&tid[i],NULL,paral,NULL) != 0){
					fprintf(stderr,"pthread_creat error\n");
					exit(1);
			}
		}
		//}
		sleep(3);


		for(int i =0;i<m;i++)
			for(int j=0;j<n;j++)
				rarr[i][j] = farr[i][j];

		//중간 파일 이름 생성
		strcpy(head,extra);
		sprintf(seqarr,"%d",seqn);
		strcat(head,seqarr);
		strcat(head,tail);
		
		//중간 파일 생성
		fp = fopen(head,"w+");
		if(fp == NULL)
		{
			fprintf(stderr,"fopen error for %s\n",head);
			exit(1);
		}

		//중간 파일 내용 작성
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{
				fprintf(fp,"%d",rarr[i][j]);
				fprintf(fp," ");
			}
			fprintf(fp,"\n");
		}

		fclose(fp);

		//스레드 반납
		/*printf("스레드 반납 시작\n");

		for(int i=0;i<runnum;i++){
			pthread_join(tid[i],(void*)&status);
			printf("스레드 %d 반납완료\n",i);
			//pthread_cond_signal(&cond);
		}*/
	}

	//rarr의 내용을 arr에 넣어줌
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			arr[i][j] = rarr[i][j];

	//output.matrix파일 생성
	rfp = fopen(resf,"w+");
	if(rfp == NULL)
	{
		fprintf(stderr,"fopen error for %s\n",resf);
		exit(1);
	}

	//outpu.matrix 파일 내용 생성
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			fprintf(rfp,"%d",arr[i][j]);
			fprintf(rfp," ");
		}
		fprintf(rfp,"\n");
	}



	printf("mutex 해제\n");
	pthread_mutex_destroy(&mutex);
	printf("cond 해제\n");
	pthread_cond_destroy(&cond);

	printf("리턴시작\n");
	return;
}


void *paral(void *arg){
	//FILE *fp;
	//FILE *rfp;
	//int neighbor =0;

	//파일 이름 생성
	//int seqn = *((int*)arg);
	
	/*char head[30] = "gen_";
	char extra[20];
	char tail[10] = ".matrix";
	char buff[10];*/

	//char resf[20] = "output.matrix";
	//char seqarr[20];
	int st;

	pthread_t pid;
	int rto = total;
	//int it=0;
	int arn=0;

	for(int i=0;i<runn;i++){
		printf("tid[%d] = %u\n",i,(unsigned int)tid[i]);
	}
	
	//strcpy(extra,head);

	
	//pthread_mutex_lock(&mutex);
	
	printf("im in paral\n");

	//스레드 행동 시작
	//while(total)
	//{
	//it = 0;

	printf("total : %d\n",total);

	//it이라는 변수를 여러개의 스레드가 독립적으로 접근
	pthread_mutex_lock(&mutex);

	//행 단위로 실행
	while(it<mm)
	{
		pid = pthread_self();
		if((pthread_equal(tid[arn%runn],pid))!=0)
			pthread_cond_signal(&cond);
		pthread_cond_wait(&cond,&mutex);

		if(it>=mm)
			break;

		arn++;
			

		rowtest(it);
			

		for(int i=0;i<nn;i++)
			farr[it][i] = sarr[it][i];
		it++;//위치 바꾼 후
		pthread_mutex_unlock(&mutex);
		printf("%u 스레드 실행\n",(unsigned int)pid);


			//pthread_cond_wait(&cond2,&mutex);
			//if((arn%runn)==0&&it<mm){
			//	pthread_cond_signal(&cond2);
				//call_sig();
			//}
		//it++; //위치 바꾸기 전
		if(it<mm)
			pthread_cond_signal(&cond);
		else
			pthread_cond_broadcast(&cond);
		
	}


	
	for(int i=0;i<runn;i++){
		pthread_join(tid[i],NULL);
		printf("스레드 반납 %d\n",i);
	}


		//total--;
	//farr에 임시저장한 내용을 rarr에 넣어줌
	/*for(int i=0;i<mm;i++)
		for(int j=0;j<nn;j++)
			rarr[i][j] = farr[i][j];
		
		
		
	//중간파일 이름 생성
	strcpy(head,extra);
	sprintf(seqarr,"%d",seqn);
	strcat(head,seqarr);
	strcat(head,tail);
	seqn++;

	//중간파일 생성
	fp = fopen(head,"w+");
	if(fp = NULL)
	{
		fprintf(stderr,"fopen error for %s\n",head);
		exit(1);
	}

	//중간 파일 내용 작성
	for(int i=0;i<mm;i++)
	{
		for(int j=0;j<nn;j++){
			fprintf(fp,"%d",rarr[i][j]);
			fprintf(fp," ");
		}
		fprintf(fp,"\n");
	}

	fclose(fp);*/



	return NULL;
}


void rowtest(int i)
{
	printf("im in rowtest\n");
	int neighbor =0;
	for(int j=0;j<nn;j++){
		//내가 살아있는 세포일 경우
		if(rarr[i][j] == 1){
			neighbor = neighborNum2(i,j);
			if(neighbor<=2||neighbor>=7)
				sarr[i][j] = 0;
			else if(neighbor>=3&&neighbor<=6)
				sarr[i][j] = 1;
		}

		//내가 죽어있는 세포일 경우
		else if(rarr[i][j] == 0){
			neighbor = neighborNum2(i,j);
			if(neighbor == 4)
				sarr[i][j] = 1;
			else
				sarr[i][j] = 0;
		}
	}

	return;
}

int neighborNum2(int i,int j){
	printf("im in neighborNum2\n");
	int cnt =0;
	for(int p = i-1;p<=i+1;p++){
		for(int q = j-1;q<=j+1;q++){
			if(p == i&&q==j)
				continue;
			if(p<0||p>=mm||q<0||q>=nn)
				continue;
			if(rarr[p][q] == 1)
				cnt++;
		}
	}

	return cnt;
}

