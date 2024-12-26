#include <stdio.h>

 struct Account{
 	char useName[100];
 	char passWord[100];
 };

void logIn(struct Account accounts[],int size);
void signIn(struct Account accounts[],int *size,FILE *file);

int main(){
	struct Account accounts[100];
	int size=0;
	int chose;
	FILE *file;
	file= fopen("accounts.bin","rb");
	if (file != NULL){
		while (fread(&accounts[size],sizeof(struct Account),1,file)){
			size++;
		}
		fclose(file);
	}
	do {
		printf("========MENU======== \n");
		printf("1.dang nhap \n");
		printf("2.dang ki \n");
		printf("3.thoat \n");
		scanf("%d",&chose);
		getchar();
		
		switch(chose){
			case 1:
				logIn(accounts,size);
				break;
			case 2:
				file = fopen("aaccounts.bin","ab");
				if (file != NULL){
					signIn(accounts,&size,file);
					fclose(file);
				} else {
					printf("khong mo duoc file ! \n");
				}
				break;
			case 3:
				printf("chuong trinh ket thuc !");
				break;
			default :
				printf("khong co trong menu !\n");
		}
	} while (chose!=3);
	
	return 0;
}
void logIn(struct Account accounts[],int size){
	char useName[100];
	char passWord[100];
	printf("moi ban nhap tai khoan ");
	fgets(useName,100,stdin);
	useName[strcspn(useName,"\n")]='\0';
	printf("moi ban nhap mat khau ");
	fgets(passWord,100,stdin);
	passWord[strcspn(passWord,"\n")]='\0';
	for (int i=0;i<size;i++){
		if (strcmp(accounts[i].useName,useName)==0 && strcmp(accounts[i].passWord,passWord)==0){
		    printf("dang nhap thanh cong \n");
		    return 2;
	    }
	}
	printf("dang nhap that bai . tai khoan hoac mat khau khong chinh xac ! \n");
}
void signIn(struct Account accounts[],int *size,FILE *file){
	if (*size>=100){
		printf("so luong tai khai da toi da , khong the dang ki ! \n");
		return 3;
	}
	struct Account newAccounts;
	char check[100];
	printf("nhap tai khoan \n");
	fgets(newAccounts.useName,100,stdin);
	newAccounts.useName[strcspn(newAccounts.useName,"\n")]='\0';
	for (int i=0;i<*size;i++){
		if (strcmp(accounts[i].useName,newAccounts.useName)==0){
			printf("tai khoan da ton tai ! \n");
			return 4;
		}
	}
	printf("nhap mat khau ");
	fgets(newAccounts.passWord,100,stdin);
	newAccounts.passWord[strcspn(newAccounts.passWord,"\n")]='\0';
	printf("nhap lai mat khau ");
	fgets(check,100,stdin);
	check[strcspn(check,"\n")]='\0';
	if (strcmp(newAccounts.passWord,check)!=0){
		printf("mat khau khong khop ! \n");
		return 5;
	}
	accounts[*size]=newAccounts;
	(*size)++;
	fseek(file, 0, SEEK_SET); 
    for (int i = 0; i < *size; i++) {
        fwrite(&accounts[i], sizeof(struct Account), 1, file);
    }
	printf("dang ki thanh cong ! \n");
}

