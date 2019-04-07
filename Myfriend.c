#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void notice(int x){


	if(x==1){
		system("clear");
		printf("ATTENTION :::::Dado incorreto:::::ATTENTION\n\n");
	}
	printf("********************************\n");
	printf("* Quero conversar:   PRESS <1> *\n");
	printf("* Sou Administrador: PRESS <2> *\n");
	printf("* desejo sair:       PRESS <3> *\n");
	printf("********************************\n");

}

int menu(){

	char a=0;
	int valor;
	char senha[50];
	int pass;


	scanf("%c",&a);

	while(a!='1' && a!='2' && a!='3'){
		notice(1);
		scanf("%c",&a);
	}
	switch(a){
		case '1':
		valor = 1;
		break;
		case '2':
		printf("Digite sua senha:\n");
		scanf("%s",senha);
		if(strlen(senha)==4){
			pass = strcmp(senha,"9438");
			if(pass == 0){
				valor = 2;
			}
			else{
				notice(1);
				valor = menu();
			}
		}
		else{
			notice(1);
			valor = menu();
		}
		
		
		break;
		case '3':
		valor = 3;
		break;
	}
	return valor;
}

void print(char BOX[][100]){

	int i;

	system("clear");
	printf("\t**********My Friend***********\n\n");
	for(i=0;i<5;i++){
		printf("%s\n",BOX[i]);
		printf("\n");
	}
	printf("\n********************************************************************************\n");
}

void talk(){
	
	FILE *arq;
	int count;
	int tam;
	char **perg;
	char **resp;
	char BOX[5][100];
	char msg[100],send[100];
	int i,j,ouro;

	system("clear");
	printf("Iniciando......\n");

	arq = fopen("ask.txt","r");
	if(arq == NULL){
		printf("falha ao abrir arquivo(ask)\n");
		exit(1);
	}
	count = 0;
	while(fgets(msg,100,arq)!=NULL){
		count++;
	}
	rewind(arq);
	perg = (char **) malloc(count * sizeof(char *));
	for(i=0;i<count;i++){
		perg[i] = (char *) malloc(100 * sizeof(char));
	}
	j = 0;
	while(fgets(msg,100,arq)!=NULL){
		tam = strlen(msg);
		msg[tam-1] = '\0';
		strcpy(perg[j],msg);
		j++;
	}
	fclose(arq);
	arq = fopen("ans.txt","r");
	if(arq == NULL){
		printf("falha ao abrir arquivo(ans)\n");
		for(i=0;i<count;i++){
			free(perg[i]);
		}
		free(perg);
		exit(1);
	}
	resp = (char **) malloc(count * sizeof(char *));
	for(i=0;i<count;i++){
		resp[i] = (char *) malloc(100 * sizeof(char));
	}
	j = 0;
	while(fgets(msg,100,arq)!=NULL){
		tam = strlen(msg);
		msg[tam-1] = '\0';
		strcpy(resp[j],msg);
		j++;
	}
	fclose(arq);
	arq = fopen("question.txt","a");
	if(arq == NULL){
		printf("falha ao abrir arquivo(question)\n");
		for(i=0;i<count;i++){
			free(resp[i]);
			free(perg[i]);
		}
		free(resp);
		free(perg);
	}
	for(i=0;i<5;i++){
		strcpy(BOX[i]," ");
	}
	strcpy(BOX[0],"Digite (SAIR) em maiusculo. Para sair do chat");
	while(1){
		print(BOX);
		scanf(" %[^\n]",msg);
		if(strcmp(msg,"SAIR")==0){
			break;
		}
		for(i=0;i<4;i++){
			strcpy(BOX[i],BOX[i+1]);
		}
		strcpy(BOX[4],"Voce: ");
		strcat(BOX[4],msg);
		print(BOX);
		ouro = -1;
		for(i=0;i<count;i++){
			if(strcmp(msg,perg[i])==0){
				ouro = i;
				break;
			}
		}
		strcpy(send,"friend: ");
		if(ouro == -1){
			fputs(msg,arq);
			fputc('\n',arq);
			strcat(send,"Estou em fase de teste. Nao sei responder isso ainda");
		}
		else{
			strcat(send,resp[ouro]);
		}
		for(i=0;i<4;i++){
			strcpy(BOX[i],BOX[i+1]);
		}
		strcpy(BOX[4],send);
	}

	for(i=0;i<count;i++){
		free(resp[i]);
		free(perg[i]);
	}
	free(resp);
	free(perg);
	fclose(arq);
}

void adm(){

	FILE *arq;
	FILE *perg;
	FILE *resp;
	char **cur;
	char buffer[100];
	int count;
	int i,j,k,tam;
	char msg[100];

	system("clear");
	printf("Iniciando...\n");

	arq = fopen("question.txt","r");
	if(arq == NULL){
		printf("falha ao abrir arquivo(question)\n");
		exit(1);
	}
	count = 0;
	while(fgets(msg,100,arq)!=NULL){
		count++;
	}
	cur = (char **) malloc(count * sizeof(char *));
	for(i=0;i<count;i++){
		cur[i] = (char *) malloc(100 * sizeof(char));
	}
	rewind(arq);
	j=0;
	while(fgets(msg,100,arq)!=NULL){
		tam = strlen(msg);
		msg[tam-1] = '\0';
		strcpy(cur[j],msg);
		j++;
	}
	fclose(arq);
	perg = fopen("ask.txt","a");
	if(perg == NULL){
		printf("Falha ao abrir arquivo(ask)\n");
		for(i=0;i<count;i++){
			free(cur[i]);
		}
		free(cur);
		exit(1);
	}
	resp = fopen("ans.txt","a");
	if(resp == NULL){
		printf("Falha ao abrir arquivo(ans)\n");
		for(i=0;i<count;i++){
			free(cur[i]);
		}
		free(cur);
		fclose(perg);
		exit(1);
	}
	system("clear");
	k = 0;
	while(1){
		scanf(" %[^\n]",msg);
		if(strcmp(msg,"PERGUNTAS")==0){
			printf("tenho %d coisas para aprender!\n",count-k);
		}
		else if(strcmp(msg,"EXIT")==0){
			arq = fopen("question.txt","w");
			if(arq == NULL){
				printf("falha ao abrir arquivo(question)\n");
				break;
			}
			while(k!=count){
				fputs(cur[k],arq);
				fputc('\n',arq);
				k++;
			}
			fclose(arq);
			printf("Ate a proxima!\n");
			break;
		}
		printf("Como devo responder um:\n");
		printf("%s\n",cur[k]);
		scanf(" %[^\n]",buffer);
		while(strcmp(buffer,"REPEAT")==0){
			k++;
			system("clear");
			printf("Como devo responder um:\n");
		    printf("%s\n",cur[k]);
		    scanf(" %[^\n]",buffer);
		}
		fputs(cur[k],perg);
		fputc('\n',perg);
		fputs(buffer,resp);
		fputc('\n',resp);
		printf("\nME diga uma pergunta parecida com esta.\n");
		scanf(" %[^\n]",msg);
		while(strcmp(msg,"FIM")!=0){
			fputs(msg,perg);
			fputc('\n',perg);
			fputs(buffer,resp);
			fputc('\n',resp);
			printf("Armazenado.Se tiver mais, continue:\n");
			scanf(" %[^\n]",msg);
		}
		system("clear");
		printf("Salvo na memoria. Deseja continuar ?\n");
		k++;
		if(k==count){
			system("clear");
			printf("Por hoje acabou. Ate mais..\n");
			arq = fopen("question.txt","w");
			fclose(arq);
			break;
		}
	}
	fclose(resp);
	fclose(perg);
	for(i=0;i<count;i++){
		free(cur[i]);
	}
	free(cur);
}


int main(){
	
	int mod;

	system("clear");

	printf("\t*****Seja Bem-vindo ao \"Myfriend\"*****\n\n");
	notice(2);
	mod = menu();
	if(mod == 1){
		talk();
	}
	else if(mod == 2){
		adm();
	}

	return 0;
}