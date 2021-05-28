#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int neighborNum(int **arr,int i,int j,int m,int n);

void seqt(int **arr,int repeat,int m,int n){
	FILE *sfp;
	int neighbor =0;//이웃세포의 수

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
