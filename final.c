#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include "list.h"

int main(int arg,char *argv[]){
	int **arr;	
	char ch;//accpet character
	int *rearr;//accept array before arr
	int size;//file's size
	int m=0,n=0;//row & col
	int p=0,q=0;//row & col
	int k=0;
	int repeat=0;
	int selectnum, runnum;//selcectnum for run
	int *pid;//for id by return
	
	clock_t start,finish;
	double duration;

	while(1){

		start = clock();
		//input.matrix로 파일 열기
		FILE *fp = fopen(argv[1],"r");
		if(fp == NULL){
			fprintf(stderr,"fopen error for %s\n",argv[1]);
			exit(1);
		}

		

		fseek(fp,0,SEEK_SET);
		m=0,n=0;
		//행과 열의 개수 구하기
		while((ch = fgetc(fp))!=EOF){
			if(ch=='0' || ch == '1')
				n++;
			else if(ch=='\n')
				m++;
		}

	
		n/=m;

		//printf("m과 n의 값 = %d %d\n",m,n);

		arr = (int**)malloc(sizeof(int*)*m);
		for(int i=0;i<m;i++)
			arr[i] = (int*)malloc(sizeof(int)*n);

		
		fseek(fp,0,SEEK_SET);
		//arr 배열에 파일의 값 넣기
		p=0,q=0;
		while((ch = fgetc(fp))!=EOF)
		{
			if(ch == '0'||ch == '1'){
				*(*(arr+q)+p) = atoi(&ch);
				p++;
			}
			if(ch == '\n'){
				q++;
				p=0;
			}
		}

	
		/*for(int i=0;i<m;i++){
			printf("%d->",i);
			for(int j=0;j<n;j++){
				printf("%d ",arr[i][j]);
			}
			printf("\n");
		}*/
	

	
		printf("동작수행선택 --> (1)프로그램종료 (2)순차처리 (3)Process 병렬처리 (4)스레드 병렬처리\n");
		scanf("%d",&selectnum);
		
		if(selectnum == 1){
			fclose(fp);
			exit(0);
		}
		
		printf("세대 수 입력: ");
		scanf("%d", &repeat);

		//최종 파일과 중간 파일은 각 분할된 소스파일내에서 하자
		if(selectnum == 2){
			printf("순차처리 시작\n");
			//총 수행시간 ms단위로 출력
			seqt(arr,repeat,m,n);
			finish = clock();
			duration = (double)(finish-start);
			printf("순차처리 경과시간 = %f(ms단위)\n",duration);

		}

		else if(selectnum == 3){
			printf("Child Process의 개수: ");
			scanf("%d",&runnum);
			//프로세서들의 id들을 모두 출력& 총 수행시간 ms단위로 출력
			pid = (int*)malloc(sizeof(int)*runnum);
			pid = child(arr,repeat,m,n,runnum);

		}
		else if(selectnum == 4){
			printf("Thread의 개수: ");
			scanf("%d",&runnum);

			//result = (unsigned int**)malloc(sizeof(unsigned int*)*repeat);
			//for(int i=0;i<repeat;i++)
			//	result[i] = (unsigned int*)malloc(sizeof(unsigned int)*runnum);

			//result = mkthr(arr,repeat,m,n,runnum);
			//스레드들의 id들을 모두 출력& 총 수행시간 ms단위로 출력
			mkthr(arr,repeat,m,n,runnum);
			finish = clock();
			duration = (double)(finish-start);
			printf("스레드 병렬처리 경과시간 = %f(ms단위)\n",duration);
			
		}
	}



	return 0;
}
