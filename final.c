#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "list.h"

int main(int arg,char *argv[]){
	int **arr;	
	int ch;//accpet character
	int *rearr;//accept array before arr
	int size;//file's size
	int m=0,n=0;//row & col
	int p=0,q=0;//row & col
	int k=0;
	int repeat=0;
	int selectnum, runnum;//selcectnum for run
	
	
	//input.matrix로 파일 열기
	FILE *fp = fopen(argv[1],"r");
	if(fp == NULL){
		fprintf(stderr,"fopen error for %s\n",argv[1]);
		exit(1);
	}

	//파일의 사이즈 구하기
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	//rearr = malloc(size+1);
	rearr = (int*)malloc(sizeof(int)*(size+1));
	memset(rearr,0,size+1);

	fseek(fp,0,SEEK_SET);

	//실제 size의 2배값이 나옴 => ' '을 포함해서
	printf("size = %d\n",size);

	while((ch = fgetc(fp)) != EOF){
		//printf("%d ",ch);
		rearr[k++] = ch;
		if(ch == '\n')
			m++;
	}
	printf("k = %d\n",k);

	
	//행  구하기 성공
	printf("m = %d\n",m);

	n = (size/2)/m;
	printf("n = %d\n",n);

	//이차원 배열 동적할당
	arr = (int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++){
		arr[i] = (int*)malloc(sizeof(int)*n);
	}


	
	for(int i=0;i<size;i++){
		if(rearr[i] == 49)
			arr[p][q] = rearr[i]-'0';
		else if(rearr[i] == 48)
			arr[p][q] = rearr[i]-'0';
		else if(rearr[i] == '\n'){
			p++;
			q =0;
		}
		else if(rearr[i]!='\n')
			q++;
	}

	
	for(int i=0;i<m;i++){
		printf("%d->",i);
		for(int j=0;j<n;j++){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}


	
	//------------------------------------------------------------------------------------------------------------------
	

	

	while(1){
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
		}

		else if(selectnum == 3){
			printf("Child Process의 개수: ");
			scanf("%d",&runnum);
			//프로세서들의 id들을 모두 출력& 총 수행시간 ms단위로 출력
		}
		else if(selectnum == 4){
			printf("Thread의 개수: ");
			scanf("%d",&runnum);
			//스레드들의 id들을 모두 출력& 총 수행시간 ms단위로 출력
		}
	}



	return 0;
}
