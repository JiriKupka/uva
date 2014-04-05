#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>

using namespace std;

struct card {
	int value;
	int color;
};

int card_value_to_int(char card_value) {
	if(card_value>='2'&&card_value<='9') return card_value-'0';
	else {
		if(card_value=='T') return 10;
		if(card_value=='J') return 11;
		if(card_value=='Q') return 12;
		if(card_value=='K') return 13;
		if(card_value=='A') return 14;
	}
	return -1;
}

int card_color_to_int(char card_color) {
	if(card_color=='C') return 1;
	else if(card_color=='D') return 2;
	else if(card_color=='H') return 3;
	else if(card_color=='S') return 4;
	return -1;
}


void load_cards(char cc[10][3],card *player1,card *player2) {
	for(int i=0;i<5;i++) {
		player1[i] = (card) {card_value_to_int(cc[i][0]),card_color_to_int(cc[i][1])};
		//cout << "val: " << player1[i].value << endl;
	}
	for(int i=5;i<10;i++) {
		player2[i-5] = (card) {card_value_to_int(cc[i][0]),card_color_to_int(cc[i][1])};
		//cout << "val2: " << player2[i-5].value << endl;
	}
}

int hight_card(card *player1, card *player2) {
	//cout << "Hight card ";
	int p1_max = 0, p2_max = 0;
	for(int i=0;i<5;i++) {
		if(player1[4-i].value!=player2[4-i].value) {
			p1_max = player1[4-i].value;
			p2_max = player2[4-i].value;
			break;
		}
	}

	//cout << "K1: " << p1_max;
	//cout << "K2: " << p2_max;
	if(p1_max>p2_max) return 0;
	else if(p1_max<p2_max) return 1;
	return -1;
}

int straight_flush(card *player1, card *player2) {
	//cout << "Straight flush ";
	int p1_has = 0, p2_has = 0;

	for(int i=0;i<4;i++) {
		if(((player1[i].value+1)==player1[i+1].value)&&(player1[0].color==player1[i].color)) p1_has += 1;
		if(((player2[i].value+1)==player2[i+1].value)&&(player2[0].color==player2[i].color)) p2_has += 1;
	}

	if(p1_has==4&&p2_has!=4) return 0;
	else if(p1_has!=4&&p2_has==4) return 1;
	else if(p1_has==4&&p2_has==4) return hight_card(player1,player2);
	return -2;
}

int four_kind(card *player1, card *player2) {
	//cout << "Four kind ";
	map<int, int> p1;
	map<int, int> p2;

	int p1_has = 0, p2_has = 0;

	for(int i=0;i<5;i++) {
		p1[player1[i].value] = p1[player1[i].value]+1;
		p2[player2[i].value] = p2[player2[i].value]+1;

		if(p1[player1[i].value]==4) p1_has = player1[i].value;
		if(p2[player2[i].value]==4) p2_has = player2[i].value;
	}

	if(p1_has>p2_has) return 0;
	else if(p1_has<p2_has) return 1;
	else if((p1_has!=0||p2_has!=0)&&p1_has==p2_has) return -1;
	return -2;
}

int full_house(card *player1, card *player2) {
	//cout << "Full house ";
	map<int, int> p1;
	map<int, int> p2;

	bool p1_has_two = false, p2_has_two = false;
	int p1_has_three = 0, p2_has_three = 0;

	for(int i=0;i<5;i++) {
		p1[player1[i].value] = p1[player1[i].value]+1;
		p2[player2[i].value] = p2[player2[i].value]+1;
		//cout << endl << "P1 val: " << player1[i].value << endl << " stav: " << p1[player1[i].value];
		//cout << endl << "P2 val: " << player2[i].value << endl << " stav: " << p2[player2[i].value];
	}

	for(int i=0;i<5;i++) {
		//cout << "stav: " << p1[player1[i].value] << endl;
		//cout << "stav 2: " << p2[player2[i].value] << endl;

		if(p1[player1[i].value]==2) {
			//cout << "p1 ma 2 karty hodnoty " << player1[i].value;
			p1_has_two = true;
		}
		if(p1[player1[i].value]==3) {
			//cout << "p1 ma 3 karty hodnoty " << player1[i].value;
			p1_has_three = player1[i].value;
		}
		if(p2[player2[i].value]==2) {
			//cout << "p3 ma 2 karty hodnoty " << player2[i].value;
			p2_has_two = true;
		}
		if(p2[player2[i].value]==3) {
			//cout << "p3 ma 3 karty hodnoty " << player2[i].value;
			p2_has_three = player2[i].value;
		}
	}

	if((p1_has_two&&p1_has_three!=0)&&(!p2_has_two||p2_has_three==0)) return 0;
	else if((p2_has_two&&p2_has_three!=0)&&(!p1_has_two||p1_has_three==0)) return 1;
	else if((p1_has_two&&p1_has_three!=0)&&(p2_has_two&&p2_has_three!=0)) {
		if(p1_has_three>p2_has_three) return 0;
		else if(p1_has_three<p2_has_three) return 1;
		else if((p1_has_three!=0||p2_has_three!=0)&&p1_has_three==p2_has_three) return -1;
	}
	return -2;
}

int flush(card *player1, card *player2) {
	//cout << "Flush ";
	int p1_color_count = 0, p2_color_count = 0;

	for(int i=0;i<5;i++) {
		if(player1[i].color==player1[0].color) p1_color_count += 1;
		if(player2[i].color==player2[0].color) p2_color_count += 1;
	}

	if(p1_color_count==5&&p2_color_count!=5) return 0;
	else if(p1_color_count!=5&&p2_color_count==5) return 1;
	else if(p1_color_count==5&&p2_color_count==5) {
		if(player1[4].value>player2[4].value) return 0;
		else if(player1[4].value<player2[4].value) return 1;
		else if(player1[4].value==player2[4].value) return hight_card(player1,player2);
	}
	return -2;
}

int straight(card *player1, card *player2) {
	//cout << "Straight ";
	int p1[5], p2[5];
	bool p1_has = true, p2_has = true;

	for(int i=0;i<4;i++) {
		if(player1[i].value+1!=player1[i+1].value) p1_has = false;
		if(player2[i].value+1!=player2[i+1].value) p2_has = false;
	}

	if(p1_has&&!p2_has) return 0;
	else if(!p1_has&&p2_has) return 1;
	else if(p1_has&&p2_has) {
		if(p1[4]>p2[4]) return 0;
		else if(p1[4]<p2[4]) return 1;
		else if(p1[4]==p2[4]) return -1;
	}
	return -2;
}

int three_kind(card *player1, card *player2) {
	//cout << "Three kind ";
	map<int, int> p1;
	map<int, int> p2;

	int p1_has = 0, p2_has = 0;

	for(int i=0;i<5;i++) {
		p1[player1[i].value] = p1[player1[i].value]+1;
		p2[player2[i].value] = p2[player2[i].value]+1;

		if(p1[player1[i].value]==3) {
			p1_has = player1[i].value;
			//cout << "User has 3 card of " << player1[i].value;
		}
		if(p2[player2[i].value]==3) {
			p2_has = player2[i].value;
			//cout << "User has 3 card of " << player2[i].value;
		}
	}

	if(p1_has>p2_has) return 0;
	else if(p1_has<p2_has) return 1;
	else if((p1_has!=0||p2_has!=0)&&p1_has==p2_has) return -1;
	return -2;
}

int two_pairs(card *player1, card *player2) {
	//cout << "Two pairs ";
	map<int, int> p1;
	map<int, int> p2;

	int p1_has = 0, p2_has = 0, p1_has2 = 0, p2_has2 = 0;
	int p1_count = 0, p2_count = 0;

	for(int i=0;i<5;i++) {
		p1[player1[i].value] = p1[player1[i].value]+1;
		p2[player2[i].value] = p2[player2[i].value]+1;

		if(p1[player1[i].value]==2) {
			if(player1[i].value>p1_has) {
				p1_has2 = p1_has;
				p1_has = player1[i].value;
			}
			p1_count++;
		}
		if(p2[player2[i].value]==2) {
			if(player2[i].value>p2_has) {
				p2_has2 = p2_has;
				p2_has = player2[i].value;
			}
			p2_count++;
		}
	}

	// cout << "Nejvyssi: " << p1_has;
	// cout << "Nejvyssi 2: " << p2_has;

	if(p1_count==2&&p2_count!=2) return 0;
	else if(p2_count!=2&&p2_count==2) return 1;
	else if(p1_count==2&&p2_count==2) {
		if(p1_has>p2_has) return 0;
		else if(p1_has<p2_has) return 1;
		else if((p1_has!=0||p2_has!=0)&&p1_has==p2_has) {
			if(p1_has2>p2_has2) return 0;
			else if(p1_has2<p2_has2) return 1;
			else if((p1_has2!=0||p2_has2!=0)&&p1_has2==p2_has2) return hight_card(player1,player2);
		}
	}
	return -2;
}

int one_pair(card *player1, card *player2) {
	//cout << "On pair ";
	map<int, int> p1;
	map<int, int> p2;

	int p1_has = 0, p2_has = 0;

	for(int i=0;i<5;i++) {
		p1[player1[i].value] = p1[player1[i].value]+1;
		p2[player2[i].value] = p2[player2[i].value]+1;

		if(p1[player1[i].value]==2) p1_has = player1[i].value;
		if(p2[player2[i].value]==2) p2_has = player2[i].value;
	}

	if(p1_has>p2_has) return 0;
	else if(p1_has<p2_has) return 1;
	else if((p1_has!=0||p2_has!=0)&&p1_has==p2_has) return hight_card(player1,player2);
	return -2;
}


int get_winner(card *player1,card *player2) {
	int result;
	// result = 0 - vyhrál první hráč
	// result = 1 - vyhrál druhý hráč
	// result = -1 - nerozhodně
	// result = -2 - žádný výsledek, pošli dál

	result = straight_flush(player1,player2);
	if(result==-2) result = four_kind(player1,player2);
	if(result==-2) result = full_house(player1,player2);
	if(result==-2) result = flush(player1,player2);
	if(result==-2) result = straight(player1,player2);
	if(result==-2) result = three_kind(player1,player2);
	if(result==-2) result = two_pairs(player1,player2);
	if(result==-2) result = one_pair(player1,player2);
	if(result==-2) result = hight_card(player1,player2);

	return result;
}

int compare(const void *a, const void *b) {
	return ((*(card*)a).value - (*(card*)b).value);
}

int main(void) {
	char cc[10][3];
	int result;
	card *player1 = new card[5];
	card *player2 = new card[5];

	while(scanf("%s %s %s %s %s %s %s %s %s %s",
		cc[0],cc[1],cc[2],cc[3],cc[4],cc[5],
		cc[6],cc[7],cc[8],cc[9])==10) {
		load_cards(cc,player1,player2);

		qsort(player1, 5, sizeof(card), compare);
		qsort(player2, 5, sizeof(card), compare);

		result = get_winner(player1,player2);
		if(result==0) cout << "Black wins." << endl;
		else if(result==1) cout << "White wins." << endl;
		else if(result==-1) cout << "Tie." << endl;
		//else cout << "Error" << endl;
	}

}