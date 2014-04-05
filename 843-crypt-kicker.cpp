#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int a_range = 'z'-'a';

bool check_dict(char *dict, char encrypted, char decrypted) {
	if(dict[encrypted-'a']!='*'&&dict[encrypted-'a']!=decrypted) return false;
	for(char i='a';i<='z';i++) {
		if(dict[i-'a']==decrypted&&i!=encrypted) return false;
	}
	return true;
}


bool decrypt_sentence(int n, char **words, int word_counter, char *sentence,int sentence_length, char *dict) {
	if(n>sentence_length) return true;

	int length = 0;
	char *temp = new char[a_range+1];

	memcpy(temp,dict,sizeof(char)*a_range);

	for(int i = n; sentence[i]!=' '&&sentence[i]!='\0'; i++) length++;

	for(int word = 0; word<word_counter; word++) {
		if(strlen(words[word])!=length) continue;
		
		bool is_ok = true;

		for(int i=0; i<length; i++) {
			char encrypted = sentence[n+i];
			char decrypted = words[word][i];
			
			if(check_dict(dict,encrypted,decrypted)) dict[encrypted-'a'] = decrypted;

			else {
				is_ok = false;
				break;
			}
		}
		if(is_ok) {
			if(decrypt_sentence(n+length+1,words,word_counter,sentence,sentence_length,dict)) return true;
		}

		memcpy(dict,temp,sizeof(char)*a_range);
	}

	return false;
}


int main(void) {
	int word_counter, sentence_length;
	scanf("%d",&word_counter);

	char **words = new char*[word_counter];
	char *sentence = new char[80];
	char *encrypted_dict = new char[a_range+1];

	for(int i=0; i<word_counter; i++) {
		char *word = new char;
		scanf("%s\n",word);
		words[i] = word;
	}

	// Načítání celého řádku, ne pouze jednoho slova
	// Zdroj: http://stackoverflow.com/questions/2718819/how-to-read-scanf-with-spaces/2718952#2718952
	while(scanf("%80[^\n]%*c", sentence)==1) {
		sentence_length = strlen(sentence);

		for(int i='a'; i <= 'z'; i++) {
			encrypted_dict[i-'a'] = '*';
		}

		decrypt_sentence(0,words,word_counter,sentence,sentence_length,encrypted_dict);

		int length = strlen(sentence);
		for(int i=0; i<length; i++) {
			if(sentence[i]==' ') cout << ' ';
			else cout << encrypted_dict[sentence[i]-'a'];
		}
		cout << endl;
	}

	return 0;
}