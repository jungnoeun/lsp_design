#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int arg,char *argv[]){
	int **arr;	
	int ch;//accpet character
	int *rearr;//accept array before arr
	int size;//file's size
	int m=0,n=0;//row & col
	int p=0,q=0;//row & col
	int k=0;
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
	rearr = malloc(size+1);
	memset(rearr,0,size+1);

	fseek(fp,0,SEEK_SET);

	//실제 size의 2배값이 나옴 => ' '을 포함해서
	printf("size = %d\n",size);

	while((ch = fgetc(fp))!=EOF){
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




	//-------------------------------------------------------------------------------------------------------
	//이 밑으로는 실패작들
	//행m과 열n의 값 구하기
	
	/*while((ch = fgetc(fp))!=EOF){
		//printf("%d ",ch-'0');
		if(ch == 48 || ch == 49){
			m++;
		}
		else if(ch == '\n')
			n++;
	}
	printf("\n행과 열 (처음): %d %d\n",m,n);
	m/=n;

	arr = (int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++){
		arr[i] = (int*)malloc(sizeof(int)*n);
	}
	printf("동적할당 후 행과 열(전): %d %d\n",m,n);

	//rewind(fp);
	//fclose(fp);
	printf("file fseek before?\n");
	//fseek(fp,0L,SEEK_SET);
	printf("file fseek after\n");
	
	fp2 = freopen(fname,"r",fp);

	printf("재 오픈 후 파일의 값: ");
	//배열에 매트릭스 값 넣기
	while((ch = fgetc(fp2))!=EOF){
		printf("%d ",ch);
		if(ch == '\n')
			q++;
		if(ch == 48||ch == 49)
			arr[p++][q] = ch - '0';
		else if(ch == ' ')
			continue;
	}
	*/

	//printf("행과 열: %d %d\n",p,q);
	
	//------------------------------------------------------------------------------------------------------------------
	
	
	//구현 완료
	/*printf("동작수행선택--> (1)프로그램종료 (2)순차처리 (3)Process 병렬처리 (4)스레드 병렬처리\n");
	scanf("%d",&selectnum);

	

	if(selectnum == 1){
		fclose(fp);
		exit(0);
	}

	//if(selectnum == 2)
	while(selectnum != 1){
		printf("동작수행선택 --> (1)프로그램종료 (순차처리) (3)Process 병렬처리 (4)스레드 병렬처리\n");
		scanf("%d",&selectnum);

		if(selectnum == 1){
			fclose(fp);
			exit(0);
		}
		
		//else if(selectnum == 2)

		else if(selectnum == 3){
			printf("Child Process의 개수: ");
			scanf("%d",&runnum);
		}
		else if(selectnum == 4){
			printf("Thread의 개수: ");
			scanf("%d",&runnum);
		}
	}*/



	return 0;
}
