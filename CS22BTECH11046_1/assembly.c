#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* hextobin(char input[9]);
void Rtype(char *key);
void Itype(char *key);
void Btype(char *key);
void Stype(char *key);
void Jtype(char *key);
void Utype(char *key);
int decimal(char input[],int n);



int main(){
FILE* file;
char hex[9];
int count=0,h=0;
char opcode[8];

file = fopen("hex.txt","r");

if (file == NULL) {
return 1;
}

while (fgets(hex, sizeof(hex), file) != NULL) {
char* thex = strtok(hex, " \t\n");
if (thex != NULL) {
count++;
}
}
//printf("%d\n",count);

fseek(file, 0, SEEK_SET);
char hexarr[count][9];
while (fgets(hex, sizeof(hex), file) != NULL) {   
char* f_hex = strtok(hex, " \t\n");
if (f_hex != NULL) {
strncpy(hexarr[h], f_hex, sizeof(hexarr[h]));
 hexarr[h][8]='\0';
h++;
 }
 }

fclose(file);

for(int i=0;i<count;i++){
char* binary =hextobin(hexarr[i]);
strncpy(opcode,binary+25,7);
opcode[7]='\0';
//printf("%s\n",opcode);
if(strcmp(opcode,"0110011")==0){
Rtype(binary);}

else if(strcmp(opcode,"0010011")==0 || strcmp(opcode,"0000011")==0 || strcmp(opcode,"1100111")==0){

Itype(binary);}

else if(strcmp(opcode,"0100011")==0){
Stype(binary);}

else if(strcmp(opcode,"1100011")==0){
Btype(binary);
  }
  
else if(strcmp(opcode,"1101111")==0){
Jtype(binary);
  }
  
else if(strcmp(opcode,"0110111")==0){
Utype(binary);
  }

}

return 0;
}


char* hextobin(char input[9]){
char *bin =malloc(33*(sizeof(char)));
int j=0;
for(int i=0;i<8;i++){
if(input[i]== '0'){
bin[j++]='0';
bin[j++]='0';
bin[j++]='0';
bin[j++]='0';
}
else if(input[i]== '1'){
bin[j++]='0';
bin[j++]='0';
bin[j++]='0';
bin[j++]='1';
}
else if(input[i]== '2'){
bin[j++]='0';
bin[j++]='0';
bin[j++]='1';
bin[j++]='0';
}
else if(input[i]== '3'){
bin[j++]='0';
bin[j++]='0';
bin[j++]='1';
bin[j++]='1';
}
else if(input[i]== '4'){
bin[j++]='0';
bin[j++]='1';
bin[j++]='0';
bin[j++]='0';
}
else if(input[i]== '5'){
bin[j++]='0';
bin[j++]='1';
bin[j++]='0';
bin[j++]='1';
}
else if(input[i]== '6'){
bin[j++]='0';
bin[j++]='1';
bin[j++]='1';
bin[j++]='0';
}
else if(input[i]== '7'){
bin[j++]='0';
bin[j++]='1';
bin[j++]='1';
bin[j++]='1';
}
else if(input[i]== '8'){
bin[j++]='1';
bin[j++]='0';
bin[j++]='0';
bin[j++]='0';
}
else if(input[i]== '9'){
bin[j++]='1';
bin[j++]='0';
bin[j++]='0';
bin[j++]='1';
}
else if(input[i]== 'a'){
bin[j++]='1';
bin[j++]='0';
bin[j++]='1';
bin[j++]='0';
}
else if(input[i]== 'b'){
bin[j++]='1';
bin[j++]='0';
bin[j++]='1';
bin[j++]='1';
}
else if(input[i]== 'c'){
bin[j++]='1';
bin[j++]='1';
bin[j++]='0';
bin[j++]='0';
}
else if(input[i]== 'd'){
bin[j++]='1';
bin[j++]='1';
bin[j++]='0';
bin[j++]='1';
}
else if(input[i]== 'e'){
bin[j++]='1';
bin[j++]='1';
bin[j++]='1';
bin[j++]='0';
}
else if(input[i]== 'f'){
bin[j++]='1';
bin[j++]='1';
bin[j++]='1';
bin[j++]='1';
}
}
bin[32]='\0';


return bin;
}



int decimal(char input[],int n){
int res=0;

for(int i=0;i<n;i++){
if(input[i]=='0'){
res = res*2;}
else if(input[i]=='1'){
res = res*2 +1;	
	}
}
return res;
}


void Rtype(char *key){

char f7[8];
char rs2[6];
char rs1[6];
char f3[4];
char rd[6];

strncpy(f7, key, 7);
f7[7]='\0';

strncpy(rs2, key+7, 5);
rs2[5]='\0';
int value_2= decimal(rs2,5);
strncpy(rs1, key+12, 5);
rs1[5]='\0';
int value_1= decimal(rs1,5);
strncpy(f3, key+17, 3);
f3[3]='\0';

strncpy(rd, key+20, 5);
rd[5]='\0';
int value= decimal(rd,5);

if(strcmp(f7,"0000000")==0){
if(strcmp(f3,"000")==0){
printf("add x%d, x%d, x%d \n",value,value_1,value_2);
}
else if(strcmp(f3,"111")==0){
printf("and x%d, x%d, x%d \n",value,value_1,value_2);
}
else if(strcmp(f3,"110")==0){
printf("or x%d, x%d, x%d \n",value,value_1,value_2);
}
else if(strcmp(f3,"100")==0){
printf("xor x%d, x%d, x%d \n",value,value_1,value_2);
}
else if(strcmp(f3,"001")==0){
printf("sll x%d, x%d, x%d \n",value,value_1,value_2);
}
else if(strcmp(f3,"101")==0){
printf("srl x%d, x%d, x%d \n",value,value_1,value_2);
}
		}
else if(strcmp(f7,"0100000")==0){
if(strcmp(f3,"000")==0){
printf("sub x%d, x%d, x%d \n",value,value_1,value_2);
}
else if(strcmp(f3,"101")==0){
printf("sra x%d, x%d, x%d \n",value,value_1,value_2);
}
}
}



void Itype(char *key){
char f6[7];
char imm[13];
char rs1[6];
char f3[4];
char rd[6];
char opc[8];
char imm_2[7];

strncpy(f6, key, 6);
f6[6]='\0';

strncpy(imm_2, key+6, 6);
imm_2[6]='\0';
int immediate_2 = decimal(imm_2,6);

strncpy(imm, key, 12);
imm[12]='\0';
int immediate = decimal(imm,12);

strncpy(rs1, key+12, 5);
rs1[5]='\0';
int value_1= decimal(rs1,5);

strncpy(f3, key+17, 3);
f3[3]='\0';

strncpy(rd, key+20, 5);
rd[5]='\0';
int value= decimal(rd,5);

strncpy(opc,key+25,7);
opc[7]='\0';

if(strcmp(opc,"0010011")==0){
if(strcmp(f3,"000")==0){
printf("addi x%d, x%d, %d \n",value,value_1,immediate);
}
else if(strcmp(f3,"111")==0){
printf("andi x%d, x%d, %d \n",value,value_1,immediate);
}
else if(strcmp(f3,"110")==0){
printf("ori x%d, x%d, %d \n",value,value_1,immediate);
}
else if(strcmp(f3,"100")==0){
printf("xori x%d, x%d, %d \n",value,value_1,immediate);
}
			
else if(strcmp(f3,"001")==0){
printf("slli x%d, x%d, %d \n",value,value_1,immediate);
}
else if(strcmp(f3,"101")==0 && strcmp(f6,"000000")){
printf("srli x%d, x%d, %d \n",value,value_1,immediate_2);
}
else if(strcmp(f3,"101")==0 && strcmp(f6,"010000")){
printf("srai x%d, x%d, %d \n",value,value_1,immediate_2);
}
		}

else if(strcmp(opc,"0000011")==0){
if(strcmp(f3,"000")==0){
printf("lb x%d, %d(x%d)\n",value,immediate,value_1);
}
else if(strcmp(f3,"001")==0){
printf("lh x%d, %d(x%d)\n",value,immediate,value_1);
}
else if(strcmp(f3,"010")==0){
printf("lw x%d, %d(x%d)\n",value,immediate,value_1);
}
else if(strcmp(f3,"011")==0){
printf("ld x%d, %d(x%d)\n",value,immediate,value_1);
}
else if(strcmp(f3,"100")==0){
printf("lbu x%d, %d(x%d)\n",value,immediate,value_1);
}
else if(strcmp(f3,"101")==0){
printf("lhu x%d, %d(x%d)\n",value,immediate,value_1);
}
else if(strcmp(f3,"110")==0){
printf("lwu x%d, %d(x%d)\n",value,immediate,value_1);
}
		}
		
else if(strcmp(opc,"1100111")==0)
if(strcmp(f3,"000")==0){
printf("jalr x%d, %d(x%d)\n",value,immediate,value_1);
}
}




void Btype(char *key){

char imm[13];
char imm_12[2];
char imm_11[2];
char imm_10_5[7];
char rs2[6];
char rs1[6];
char f3[4];
char imm_4_1[5];


strncpy(imm_12, key, 1);
imm_12[1]='\0';

strncpy(imm_10_5, key+1, 6);
imm_10_5[6]='\0';

strncpy(rs2, key+7, 5);
rs2[5]='\0';
int value_2= decimal(rs2,5);

strncpy(rs1, key+12, 5);
rs1[5]='\0';
int value_1= decimal(rs1,5);

strncpy(f3, key+17, 3);
f3[3]='\0';

strncpy(imm_4_1, key+20, 4);
imm_4_1[4]='\0';

strncpy(imm_11, key+24, 1);
imm_11[1]='\0';

strcpy(imm, imm_12);
strcat(imm, imm_11);
strcat(imm, imm_10_5);
strcat(imm, imm_4_1);
imm[12]='\0';

int value = decimal(imm,12);


if(strcmp(f3,"000")==0){
printf("beq x%d, x%d, %d \n",value_1,value_2,value);
}
else if(strcmp(f3,"001")==0){
printf("bne x%d, x%d, %d \n",value_1,value_2,value);
}
else if(strcmp(f3,"100")==0){
printf("blt x%d, x%d, %d \n",value_1,value_2,value);
}
else if(strcmp(f3,"101")==0){
printf("bge x%d, x%d, %d \n",value_1,value_2,value);
}
else if(strcmp(f3,"110")==0){
printf("blt x%d, x%d, %d \n",value_1,value_2,value);
}
else if(strcmp(f3,"111")==0){
printf("bgeu x%d, x%d, %d \n",value_1,value_2,value);
}
 		

}



void Stype(char *key){

char imm[13];
char imm_11_5[8];
char rs2[6];
char rs1[6];
char f3[4];
char imm_4_0[6];


strncpy(imm_11_5, key, 7);
imm_11_5[7]='\0';

strncpy(rs2, key+7, 5);
rs2[5]='\0';
int value_2= decimal(rs2,5);

strncpy(rs1, key+12, 5);
rs1[5]='\0';
int value_1= decimal(rs1,5);

strncpy(f3, key+17, 3);
f3[3]='\0';

strncpy(imm_4_0, key+20, 5);
imm_4_0[5]='\0';

strcpy(imm,imm_11_5);
strcat(imm, imm_4_0);
int immediate = decimal(imm,12);


if(strcmp(f3,"000")==0){
printf("sb x%d, %d(x%d)\n",value_2,immediate,value_1);
}
else if(strcmp(f3,"001")==0){
printf("sh x%d, %d(x%d)\n",value_2,immediate,value_1);
}
else if(strcmp(f3,"010")==0){
printf("sw x%d, %d(x%d)\n",value_2,immediate,value_1);
}
else if(strcmp(f3,"011")==0){
printf("sd x%d, %d(x%d)\n",value_2,immediate,value_1);
}
		
}



void Jtype(char *key){

char imm[21];
char imm_20[2];
char imm_10_1[11];
char imm_11[2];
char imm_19_12[9];
char rd[6];


strncpy(imm_20, key, 1);
imm_20[1]='\0';

strncpy(imm_10_1, key+1, 10);
imm_10_1[10]='\0';

strncpy(imm_11, key+11, 1);
imm_11[1]='\0';

strncpy(imm_19_12, key+12, 8);
imm_19_12[8]='\0';

strncpy(rd, key+20, 5);
rd[5]='\0';
int value= decimal(rd,5);

strcpy(imm,imm_20);
strcat(imm, imm_19_12);
strcat(imm, imm_11);
strcat(imm, imm_10_1);
imm[20]='\0';



printf("jal x%d, %s\n",value,imm);


		
}


void Utype(char *key){

char imm[21];

char rd[6];


strncpy(imm, key, 20);
imm[20]='\0';


strncpy(rd, key+20, 5);
rd[5]='\0';
int value= decimal(rd,5);


int immediate = decimal(imm,20);



printf("lui x%d, %s\n",value,imm);
		
}

