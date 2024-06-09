//Hill cipher
#include<stdio.h>
#include<conio.h> 
#include<string.h>

char arr[26];

int find_pos(char a) {
	int i;
	for(i=0; i<26; i++) {
		if(a == arr[i])	return i;
	}
	return -1;
}

void encrypt(char pt[], char ct[], int key[2][2], int ct_arr[]) {
	int pt_len = strlen(pt), i, j=0, k=0;
	for(i=0; i<pt_len; i+=2) {
		//int t1 = find_pos(pt[i]);
		int t1=pt[i]-97;
		printf("t1:%d ",t1);
		int t2 = find_pos(pt[i+1]);
		
		int p1 = t1*key[0][0] + t2*key[0][1];
		int p2 = t1*key[1][0] + t2*key[1][1];
		
		ct_arr[k++] = p1;
		ct_arr[k++] = p2;
		printf("%d %d",p1,p2);
		ct[j++] = (char)(p1%26 + 97);
		printf("%c\n",ct[j-1]);
		
		ct[j++] = (char)(p2%26 + 97);
		printf("%c\n",ct[j-1]);
		
	}
	ct[j] = '\0';
}

void decrypt(char ct[], int inv[2][2], int ct_arr[], char dt[]) {
	int i, j=0;
	int det = inv[0][0]*inv[1][1] - inv[0][1]*inv[1][0];
	if(det == 0)	{
		printf("\nDet is 0.");
		return;
	}
	for(i=0; i<strlen(ct); i+=2) {
		int t1 = ct_arr[i];
		int t2 = ct_arr[i+1];
		
		int p1 = t1*inv[0][0] + t2*inv[0][1];
		int p2 = t1*inv[1][0] + t2*inv[1][1];
		
		p1 = p1/det;
		p2 = p2/det;
		
		dt[j++] = arr[p1];
		dt[j++] = arr[p2];
	}
	dt[j] = '\0';
}

int main() {
	char pt[30], ct[30], dt[30];
	int key[2][2], i, j, ct_arr[30];
	printf("Enter the plain text: ");
	scanf("%s", &pt);
	printf("Enter the key matrix: ");
	for(i=0; i<2; i++) {
		for(j=0; j<2; j++) {
			scanf("%d", &key[i][j]);
		}
	}
	
	for(i=0; i<26; i++) {
		arr[i] = (char)(97+i);
	}
	
	encrypt(pt, ct, key, ct_arr);
	printf("\n Cipher text: %s", ct);
		
	int inv[2][2];
	inv[0][0] = key[1][1];
	inv[1][1] = key[0][0];
	inv[0][1] = -key[0][1];
	inv[1][0] = -key[1][0];
	
	decrypt(ct, inv, ct_arr, dt);
	printf("\n Original text: %s", dt);	
	return 0;
}


//Playfair cipher


//#include<stdio.h>
//#include<conio.h>
//#include<string.h>
//
//void make_table(char matrix[5][5], char key[], int key_len) {
//	int i, x = 0 , y = 0;
//	int flag[26];
//	for(i=0; i<26; i++)	flag[i] = 0;
//	for(i=0; i<key_len; i++) {
//		char now = key[i];
//		if(now == 'j')	now = 'i';
//		if(flag[(int)now - 97] == 0)	{
//			matrix[x][y++] = now;
//			if(y == 5) {
//				x++;
//				y = 0;
//			}
//			flag[(int)now - 97] = 1;
//		}
//	}
//	for(i=0; i<26; i++) {
//		if((char)(i+97) == 'j')	continue;
//		else {
//			if(flag[i] == 0) {
//				matrix[x][y++] = (char)(i+97);
//				if(y == 5) {
//					x++;
//					y = 0;
//				}
//				flag[i] = 1;
//			}
//			
//		}
//	}
//	
//	for(x=0; x<5; x++) {
//		for(y=0; y<5; y++) {
//			printf("%c ", matrix[x][y]);
//		}
//		printf("\n");
//	}
//}
//
//void format_message(char new_msg[], char msg[], int msg_len) {
//	int i=0, j=0;
//	while(i<msg_len) {
//		new_msg[j++] = msg[i];
//		if(i+1<msg_len) {
//			if(msg[i] == msg[i+1]) {
//				new_msg[j++] = 'x';
//			}
//			else {
//				new_msg[j++] = msg[i+1];
//				i++;
//			}
//		}
//		i++;
//	}
//	if(j%2 != 0)	new_msg[j++] = 'x';
//	new_msg[j] = '\0';
//}
//
//void search(char a, char b, int arr[], char matrix[5][5]) {
//	if(a == 'j')	a = 'i';
//	else if(b == 'j')	b = 'i';
//	int i, j;
//	for(i=0; i<5; i++) {
//		for(j=0; j<5; j++) {
//			if(matrix[i][j] == a) {
//				arr[0] = i;
//				arr[1] = j;
//			}
//			else if(matrix[i][j] == b) {
//				arr[2] = i;
//				arr[3] = j;
//			}
//		}
//	}
//}
//
//void encrypt(char msg[], char matrix[5][5]) {
//	int i;
//	for(i=0; i<strlen(msg); i+=2) {
//		int a[4];
//		search(msg[i], msg[i+1], a, matrix);
//		if(a[0] == a[2]) {
//			msg[i] = matrix[a[0]][(a[1]+1)%5];
//			msg[i+1] = matrix[a[2]][(a[3]+1)%5];
//		}
//		else if(a[1] == a[3]) {
//			msg[i] = matrix[(a[0]+1)%5][a[1]];
//			msg[i+1] = matrix[(a[2]+1)%5][a[3]];
//		}
//		else {
//			msg[i] = matrix[a[0]][a[3]];
//			msg[i+1] = matrix[a[2]][a[1]];
//		}
//	}
//}
//
//void decrypt(char msg[], char matrix[5][5]) {
//	int i;
//	for(i=0; i<strlen(msg); i+=2) {
//		int a[4];
//		search(msg[i], msg[i+1], a, matrix);
//		if(a[0] == a[2]) {
//			msg[i] = matrix[a[0]][(a[1]+4)%5];
//			msg[i+1] = matrix[a[2]][(a[3]+4)%5];
//		}
//		else if(a[1] == a[3]) {
//			msg[i] = matrix[(a[0]+4)%5][a[1]];
//			msg[i+1] = matrix[(a[2]+4)%5][a[3]];
//		}
//		else {
//			msg[i] = matrix[a[0]][a[3]];
//			msg[i+1] = matrix[a[2]][a[1]];
//		}
//	}
//}
//
//int main() {
//	char msg[30], enc[30], dec[30], key[30];
//	printf("Enter the message: ");
//	gets(msg);
//	printf("Enter the key: ");
//	gets(key);
//	int msg_len = strlen(msg), key_len = strlen(key);
//	char matrix[5][5];
//	char new_msg[30];
//	make_table(matrix, key, key_len);
//	format_message(new_msg, msg, msg_len);
//	printf("\nThe formatted message is: %s", new_msg);
//	encrypt(new_msg, matrix);
//	printf("\nThe encrypted string is: %s", new_msg);
//	decrypt(new_msg, matrix);
//	printf("\nThe decrypted string is: %s", new_msg);
//	return 0;
//}
