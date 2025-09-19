#include<stdio.h> // included untuk standard input output function
#include<stdlib.h> // included untuk memory allocation
#include<string.h> // included untuk manipulasi string

//definisikan structure untuk trie
struct trie {
    char ch; //untuk menyimpan karakter
    int isWord; //untuk mengetahui apakah node ini akhiran kata/bukan ("1" berarti iya)
    char desc[100]; //untuk menyimpan deskripsi dari slang wordnya
    struct trie* edge[128]; //node children yang berisi pointer ke 128 node lain berdasarkan ASCII
}*root = NULL; //deklarasikan root trie adalah NULL

//function untuk membuat node baru
struct trie* createNode(char ch) {
    struct trie* node = (struct trie*) malloc(sizeof(trie));
    node->ch = ch;
    node->isWord = 0;
	for(int i = 0;i<128;i++){
		node->edge[i] = 0;
	}
    return node;
}

//function untuk search slang word ada atau tidak
int exist(struct trie* curr, char* word) {
	
    while (*word) {
        if (curr == NULL || curr->edge[*word] == NULL) return 0;
        curr = curr->edge[*word];
        word++;
    }
    return curr != NULL && curr->isWord;
}

//function untuk insert slang word baru ke trie
void insertWord(struct trie* curr, char* word, char* desc) {
	if (root == NULL) root = createNode('*');
	
	curr = root;
    while (*word) {
        if (curr->edge[*word] == NULL) {
            curr->edge[*word] = createNode(*word);
        }
        curr = curr->edge[*word];
        word++;
    }
    curr->isWord = 1;
    strcpy(curr->desc, desc);
}

//function untuk search slang word
void searchWord(struct trie* curr, char search[100]){

	int check = -1;
    for(int i=0;i<strlen(search);i++) {
        if (curr == NULL || curr->edge[search[i]] == NULL){
        	check = 0;
        	break;
		}
        curr = curr->edge[search[i]];
    }
    
	if(check == 0){
		printf("\nThere is no word \"%s\" in the dictionary.\n", search);
	}else{
		printf("\nSlang word : %s\n", search);
		printf("Description : %s\n", curr->desc);
	}
}

//function untuk print slang word
void printTrieContents(struct trie* Node, char buffer[100], int depth, int* number) {
  if (Node == NULL) return;

    buffer[depth] = Node->ch;
    if (Node->isWord) {
        buffer[depth+1] = '\0';
        printf("%d. %s\n", (*number)++, buffer + 1);
    }

    for (int i = 0; i < 128; i++) {
        if (Node->edge[i] != NULL) {
            printTrieContents(Node->edge[i], buffer, depth + 1, number);
        }
    }
}

//function untuk mencari slang word dengan prefix tertentu
void searchPrefix(struct trie* curr, char prefix[100]){
    char buffer[100];
    int depth = 0;
    buffer[depth++]=prefix[0];

    for(int i=0;i<strlen(prefix);i++) {
       if(curr->edge[prefix[i]]== NULL){
    		printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
    		return;
		}
        curr = curr->edge[prefix[i]];
        buffer[depth++] = prefix[i];
    }
    
    printf("\nWords starts with \"%s\":\n", prefix);
    int number = 1;
	
    if (curr != NULL && curr->isWord) {
        buffer[depth+1] = '\0';
        printf("%d. %s\n", number, buffer+1);
        number++;
    }

    for (int i = 0; i < 128; i++) {
        if (curr->edge[i] != NULL) {
            printTrieContents(curr->edge[i], buffer, depth, &number);
        }
    }
	
}

//function untuk print semua slang words
void printAllSlangWords(struct trie* root) {
    char buffer[100];
    int number = 1;
    if(root == NULL){
    	printf("There is no slang words yet in the dictionary.\n");
    	return;
	}
	
	printf("\nList of all slang words in the dictionary:\n");
    printTrieContents(root, buffer, 0, &number);
}


//function untuk menghitung banyak kata
int countWords(char *str) {
	/*deklarasikan variabel count (jumlah kata) dan inWord(untuk menandai apakah karakter ada dalam sebuah kata) 
	dan inisialisaikan menjadi 0*/

    int count = 0;
    int inWord = 0;

    //loop setiap karakter dalam string str
    while (*str) {
        //jika karakter bukan spasi, dan sebelumnya bukan dalam kata
        if (*str != ' ' && !inWord) {
            inWord = 1; //mulai kata baru
            count++;    //tambah jumlah kata
        }
        //jika karakter adalah spasi
        else if (*str == ' ') {
            inWord = 0; //tandai sedang di luar kata
        }
        str++; //lanjut ke karakter berikutnya
    }

    return count; //fungsi akan me-return nilai dari count (jumlah kata)
}

//function untuk cek spasi
int checkSpace(char *word){
	//deklarasikan variabel space dan set menjadi 0
	int space = 0;
	
	//lakukan looping sebanyak panjang dari kata

	for(int i=0;i<strlen(word);i++){
		if(word[i]==' '){
		space++; //jika karakter saat ini dari word adalah spasi maka space bertambah
		}
	}
	
	return space;  //fungsi akan mengembalikan nilai dari variabel space
}

int main(){
	//deklarasi variabel choice dan set menjadi 0
	int choice = 0;
	
	//tampilkan menu
	do{
		printf("Menu :\n");
		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang words\n");
		printf("5. Exit\n");
		
		//input choice
		printf("Enter your choice : ");
		scanf("%d", &choice); fflush(stdin);
		
		//kondisi untuk choice
		switch(choice){
			//jika user input angka 1
			case 1:
				//deklarasi string untuk slang word dan deskripsinya
				char word[100];
				char desc[100];
				
				/* minta kata yang mau diinput (harus lebih dari 1 karakter dan tanpa spasi (nilai dari fungsi checkSpace(word)) adalah 0). 
				jika tidak, program akan terus meminta inputan */
				do{
					printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
					scanf("%[^\n]", word); getchar();

				}while(strlen(word)<2 || checkSpace(word)!=0);
				
				/* minta deskripsi kata yang sudah diinput (harus lebih dari 2 kata). 
				jika tidak, program akan terus meminta inputan */
				do{
					printf("Input a new slang word description [Must be more than 2 words]: ");
					scanf("%[^\n]", desc); getchar();
					
				}while(countWords(desc)<=2);
				
				/* cek apakah kata tersebut sudah ada di trie/belum dengan menggunakan function exist,
				dan simpan dalam variabel check (0 berarti belum ada kata tersebut dalam trie, 
				1 berarti sudah ada) */
				int check;
				check = exist(root, word);
				
				//insert kata ke dalam trie
				insertWord(root, word, desc);
				puts("");
				
				/* jika check nya 0 (kata belum pernah diinput sebelumnya), maka program akan mengeluarkan output "Successfully released a new slang word."
				jika check nya 1 (kata sudah pernah diinput sebelumnya), maka program mengeluarkan output "Successfully updated a slang word." */
				if(check == 0){
			    	printf("Successfully released a new slang word.\n");
				}else if(check == 1){
					printf("Successfully updated a slang word.\n");
				}
				
				//minta user tekan tombol "enter" untuk melanjutkan program
				printf("Press enter to continue...\n");
				getchar();
				
				break;
				
			//jika user input angka 2
			case 2:
				//deklarasi string "search" untuk menyimpan kata yang mau dicari
				char search[100];
				
				/* minta input kata yang mau dicari (harus lebih dari 1 karakter dan tanpa spasi. (nilai dari fungsi checkSpace(word)) adalah 0)
				jika tidak, program akan terus meminta inputan */ 
				do{
					printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
					scanf("%[^\n]", search); getchar();
				}while(strlen(search)<2 || checkSpace(search)!=0);
				
				//panggil function searchWord
				searchWord(root, search);
				puts("");
				
				//minta user tekan tombol "enter" untuk melanjutkan program
				printf("Press enter to continue...\n");
				getchar();
				
				break;
			
			//jika user input angka 3
			case 3:
				//deklarasikan string "prefix" untuk menyimpan prefix yang mau dicari
				char prefix[100];
				
				//input prefix yang mau dicari
				printf("Input a prefix to be searched: ");
				scanf("%[^\n]", prefix); getchar();
				
				//panggil function searchPrefix
				searchPrefix(root, prefix);
				puts("");
				
				//minta user tekan tombol "enter" untuk melanjutkan program
				printf("Press enter to continue...\n");
				getchar();
				
				break;
			
			//jika user input angka 4	
			case 4:
				//panggil function printAllSlangWords
				printAllSlangWords(root);
				
				//minta user tekan tombol "enter" untuk melanjutkan program
				printf("Press enter to continue...\n");
				getchar();
				break;
				
			//jika user input angka 5
			case 5:
				//program akan menampilkan kalimat "Thank you... Have a nice day :)"
				printf("Thank you... Have a nice day :)\n");
				break;
				
			//jika user input angka di luar 1-5
			default:
				/* validasi input choice, jika inputnya bukan angka di antara 1-5,
				maka program akan meminta inputan yang benar */
				printf("Invalid input. Please enter a number between 1 and 5\n");
				puts("");
		}
		
	}while(choice!=5); //program akan menutup jika user memilih menu ke 5
	
	
	return 0;
}
