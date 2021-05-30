#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int neighborNum(int **arr,int i,int j,int m,int n);

void seqt(int **arr,int repeat,int m,int n){
	FILE *sfp;
	int neighbor =0;//이웃세포의 수
	int seqn =1;//파일의 이름에 들어갈 순서
	char head[30] = "gen_";
	char seqarr[20];
	char extra[20];
	char tail[10] = ".matrix";
	char buff[10];

	strcpy(extra,head);

	int **sarr = (int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++){
		sarr[i] = (int*)malloc(sizeof(int)*n);
	}

	//세대 진행 시작
	while(repeat--){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				//내가 살아있는 세포일 경우
				if(arr[i][j]==1){
					neighbor = neighborNum(arr,i,j,m,n);
					if(neighbor<=2 || neighbor>=7)
						sarr[i][j] = 0;
					else if(neighbor>=3&&neighbor<=6)
						sarr[i][j] = 1;
				}
				//내가 죽어있는 세포일 경우
				else if(arr[i][j] == 0){
					neighbor = neighborNum(arr,i,j,m,n);
					if(neighbor==4)
						sarr[i][j] = 1;
					else
						sarr[i][j] = 0;
				}

			}
		}
		//sarr에 세대 진행하고 저장해둔 생의 유무를 arr로 옮김
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				arr[i][j] = sarr[i][j];
			}
		}
	
		//중간파일 이름 생성
		strcpy(head,extra);
		sprintf(seqarr,"%d",seqn);
		strcat(head,seqarr);
		strcat(head,tail);
		//printf("%s\n",head);
		seqn++;
		//strcpy(head,extra);

		//중간파일 생성
		sfp = fopen(head,"w+");
		if(sfp == NULL){
			fprintf(stderr,"fopen error for %s\n",head);
			exit(1);
		}

		//파일에 매트릭스 받아쓰기
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				fprintf(sfp,"%d",arr[i][j]);
				fprintf(sfp," ");
			}
			fprintf(sfp,"\n");
		}


		fclose(sfp);


	}
	
	
	return;
}

int neighborNum(int **arr,int i,int j,int m,int n){
	int cnt =0;
	for(int p = i-1;p <=i+1;p++){
		for(int q = j-1;q<=j+1;q++){
			if(p==i&&q==j)
				continue;
			if(p<0||p >= m||q<0||q>=n)
				continue;
			if(arr[p][q] == 1)
				cnt++;
		}
	}

	return cnt;

}
