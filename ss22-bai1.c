#include <stdio.h>

 struct Student{
 	char id[15];
 	char name[50];
 	int age;
 };
 
void showStudent(struct Student students[],int size,FILE *file);
void addStudent(struct Student students[],int *size,FILE *file);
void fixStudent(struct Student students[],int size,FILE *file);
void deleteStudent(struct Student students[],int *size,FILE *file);
void findStudent(struct Student students[],int size,FILE *file);
void sortStudent(struct Student students[],int size,FILE *file);

int main(){
	struct Student students[100]={
		{"Ms01","Ha Minh Trang",18},
		{"Ms02","Nguyen Huy Hoan",18},
		{"Ms03","Le Phu Toan",18},
		{"Ms04","An Hai Dung",18},
		{"Ms05","La The Phong",18}
	};
	int chose;
	FILE *file;
	file= fopen("danhsach.bin","wb");
	int size=5;
	for (int i=0;i<size;i++){
		fwrite(&students[i],sizeof(students[i]),1,file);
	}
	fclose(file);
	do {
		printf("========MENU======== \n");
		printf("1.in danh sach sinh vien \n");
		printf("2.them sinh vien \n");
		printf("3.sua thong tin sinh vien \n");
		printf("4.xoa sinh vien \n");
		printf("5.tim kiem sinh vien \n");
		printf("6.sap xep danh sach sinh vien \n");
		printf("7.thoat \n");
		scanf("%d",&chose);
		getchar();
		switch(chose){
			case 1:
				file= fopen("danhsach.bin","rb");
				showStudent(students,size,file);
				fclose(file);
				break;
			case 2:
				file= fopen("danhsach.bin","ab");
				addStudent(students,&size,file);
				fclose(file);
				break;
			case 3:
				file= fopen("danhsach.bin","wb");
				fixStudent(students,size,file);
				fclose(file);
				break;
			case 4:
				file= fopen("danhsach.bin","wb");
				deleteStudent(students,&size,file);
				fclose(file);
				break;
			case 5:
				file= fopen("danhsach.bin","rb");
				findStudent(students,size,file);
				fclose(file);
				break;
			case 6:
				file= fopen("danhsach.bin","wb");
				sortStudent(students,size,file);
				fclose(file);
				break;
			case 7:
				printf("chuong trinh ket thuc !");
				break;
			default :
				printf("khong co trong menu ! \n");
		}
	} while (chose!=7);
	
	
	
	return 0;
}
void showStudent(struct Student students[],int size,FILE *file){
	if (file==NULL){
    	printf("khong mo duoc file \n");
    	return 2;
	}
	for (int i=0;i<size;i++){
		fread(&students[i],sizeof(students[i]),1,file);
		printf("thong tin sinh vien thu %d \n",i+1);
		printf("id : %s \n",students[i].id);
		printf("ten : %s \n",students[i].name);
		printf("tuoi : %d \n",students[i].age);
	}
}
void addStudent(struct Student students[],int *size,FILE *file){
	if (file==NULL){
    	printf("khong mo duoc file \n");
    	return 2;
	}
	if (*size>=100){
		printf("sinh vien da day khong the them \n");
		return 1;
	}
	struct Student newStudent;
	printf("nhap thong tin sinh vien ban muon them \n");
	printf("id : ");
	fgets(newStudent.id,15,stdin);
	newStudent.id[strcspn(newStudent.id,"\n")]='\0';
	printf("ten : ");
	fgets(newStudent.name,15,stdin);
	newStudent.name[strcspn(newStudent.name,"\n")]='\0';
	printf("tuoi : ");
	scanf("%d",&newStudent);
	getchar();
	students[*size]=newStudent;
	(*size)++;
	printf("them thanh cong ! \n");
}
void fixStudent(struct Student students[],int size,FILE *file){
	if (file==NULL){
    	printf("khong mo duoc file \n");
    	return 2;
	}
	char text[15];
	int check=0;
	printf("moi ban nhap id sinh vien muon sua ");
	fgets(text,15,stdin);
	text[strcspn(text,"\n")]='\0';
	for (int i=0;i<size;i++){
		if (strcmp(students[i].id,text)==0){
			check=1;
			printf("nhap ten moi ");
			fgets(students[i].name,50,stdin);
			students[i].name[strcspn(students[i].name,"\n")]='\0';
			printf("nhap tuoi moi ");
			scanf("%d",&students[i].age);
			getchar();
		}
	}
	if (check==0){
		printf("khong co sinh vien ! \n");
	}
}
void deleteStudent(struct Student students[],int *size,FILE *file){
	if (file==NULL){
    	printf("khong mo duoc file \n");
    	return 2;
	}
	char text[15];
	int flag=0;
	printf("moi ban nhap id sinh vien muon xoa ");
	fgets(text,15,stdin);
	text[strcspn(text,"\n")]='\0';
	for (int i=0;i<size;i++){
		if (strcmp(students[i].id,text)==0){
			flag=1;
			for (int j=0;j<size;j++){
				students[i]=students[i+1];
			}
			(*size)--;
			break;
		}
	}
	if (flag==0){
		printf("khong tim thay sinh vien \n");
	}
}
void findStudent(struct Student students[],int size,FILE *file){
	if (file==NULL){
    	printf("khong mo duoc file \n");
    	return 2;
	}
	int check=0;
	char text[15];
	printf("moi ban nhap id sinh vien muon tim ");
	fgets(text,15,stdin);
	text[strcspn(text,"\n")]='\0';
	for (int i=0;i<size;i++){
		if (strcmp(students[i].id,text)==0){
		    check=1;
		    printf("ten sinh vien : %s \n",students[i].name);
		    printf("tuoi sinh vien : %d \n",students[i].age);
	    }
	}
	if (check==0){
		printf("khong tim thay sinh vien \n");
	}
}
void sortStudent(struct Student students[],int size,FILE *file){
	if (file==NULL){
    	printf("khong mo duoc file \n");
    	return 2;
	}
	struct Student temp;
	for (int i=0;i<size-1;i++){
		for (int j=i+1;j<size;j++){
			if (strcmp(students[i].name,students[j].name)>0){
				temp=students[i];
				students[i]=students[j];
				students[j]=temp;
			}
		}
	}
}


