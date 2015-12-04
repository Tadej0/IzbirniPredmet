#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
//vsak ucenec bo v zbirki vpisan najmanj dvakrat, za vsak predmet posebej
//ko jih bom hotel izpisati bom preveril ce je aktiven podatek
//namesto da podatek oziroma predmet zbrisem, ga samo deaktiviram

	int id_predmeta;
	int id_ucenca;
	int aktiven;  //0...ni aktiven 1...aktiven  profil
} tip_zbirke;

typedef struct {
	int id_predmeta;
	char ime[20];    //ime predmeta
	int max_uc;      //omejitev ucencev
	int trenutno_uc; //trenutno vpisanih ucencev
	int st_ur;
} tip_predmeti;

typedef struct {
	int id_ucenca;
	char ime[10];          //ime
	char priimek[10];      //priimek
	char up_ime[10];       //uporabnisko ime osebe
	char geslo[10];        //geslo
	int st_ur;           //stevilo ur: 2 ali 3

	//naredi se seznam predmetov ki jih oseba ima

	char razred_oddelek[5];
	int pravice;           // 0: ucenec 1: ucitelj
	int st_ur_trenutno;    //koliko ur je ze
} tip_osebe;



void vnos_predmetov() {
	system("CLS");
	printf("\n\tVNOS PREDMETOV\n");
	int id_predmet;
	tip_predmeti *predmet=(tip_predmeti*)malloc(sizeof(tip_predmeti));
	FILE *predmetna=fopen("predmeti.dat","rb+");
	if(!predmetna) {
		predmetna = fopen("predmeti.dat","wb+");
		id_predmet=0;
	} else {

		while(fread(predmet,sizeof(tip_predmeti),1,predmetna)) {
			id_predmet=(predmet->id_predmeta)+1;
		}
	}
	freopen("predmeti.dat","ab+",predmetna);

	char tmp_ime[20];
	int tmp_max_uc;
	int tmp_st_ur;

	printf("Ime predmeta: ");
	scanf("%s",&tmp_ime);
	printf("Maksimalno stevilo ucencev: ");
	scanf("%d",&tmp_max_uc);
	printf("Koliko ur ima predmet? [2/3] ");
	scanf("%d",&tmp_st_ur);
	strcpy(predmet->ime,tmp_ime);
	predmet->max_uc=tmp_max_uc;
	predmet->st_ur=tmp_st_ur;
	predmet->trenutno_uc=0;
	predmet->id_predmeta=id_predmet;
	fwrite(predmet,sizeof(tip_predmeti),1,predmetna);
	fclose(predmetna);

	system("PAUSE");
}

void vnos_ucencev() {
	tip_osebe *oseba=(tip_osebe*)malloc(sizeof(tip_osebe));
	char tmp_ime[10];
	char tmp_priimek[15];
	char tmp_up_ime[10];
	char tmp_razred_oddelek[5];
	char tmp_geslo[10];
	int tmp_pravice;
	int tmp_st_ur;
	int tmp=0;
	system("CLS");
	printf("\n\tVNOS OSEB\n");
	printf("Vnesi: \n");
	printf("1: ucenca\n");
	printf("2: ucitelja\n");
	int izbira;
	scanf("%d",&izbira);
	if (izbira==2) {
		tmp=1;
		system("CLS");
		printf("\tVNOS UCITELJA [vse pravice]");
		printf("\nIme: ");
		scanf("%s",&tmp_ime);
		printf("Priimek:");
		scanf("%s",&tmp_priimek);
		printf("Uporabnisko ime: ");
		scanf("%s",&tmp_up_ime);
		printf("Geslo: ");
		scanf("%s",&tmp_geslo);
		strcpy(tmp_razred_oddelek,"prof.");
		tmp_pravice=1;
		system("CLS");
		printf("\n\tVnos novega ucitelja uspesen!\n");
	} else if(izbira==1) {
		tmp=1;
		system("CLS");
		tmp_pravice=0;
		printf("\tVNOS UCENCA [omejene pravice]");
		printf("\nIme: ");
		scanf("%s",&tmp_ime);
		printf("Priimek:");
		scanf("%s",&tmp_priimek);
		printf("Razred in oddelek: ");
		scanf("%s",&tmp_razred_oddelek);
		printf("Uporabnisko ime: ");
		scanf("%s",&tmp_up_ime);
		printf("Geslo: ");
		scanf("%s",&tmp_geslo);

		char odgovor[2];
		printf("Soglasje starsev [DA/NE]: ");
		scanf("%s",&odgovor);
		if ((strcmp(odgovor,"DA")==0)||(strcmp(odgovor,"da")==0)) {
			printf("Uposteva se dodatna ura!");
			tmp_st_ur=3;
		} else tmp_st_ur=2;
		system("CLS");

		printf("\n\tVnos novega ucenca uspesen!\n");
	} else printf("Neveljavna izbira!");

	if(tmp==1) {            //ce je izbral 1 ali 2 potem se zapisejo podatki v datoteko
		int id_oseba;
		FILE *osebna=fopen("podatki.dat","rb+");
		if(!osebna) {
			osebna = fopen("podatki.dat","wb+");
			id_oseba=0;
		} else {
			while(fread(oseba,sizeof(tip_osebe),1,osebna)) {
				id_oseba=(oseba->id_ucenca)+1;
			}
		}

		freopen("podatki.dat","ab+",osebna);
		strcpy(oseba->ime,tmp_ime);
		strcpy(oseba->priimek,tmp_priimek);
		strcpy(oseba->up_ime,tmp_up_ime);
		strcpy(oseba->geslo,tmp_geslo);
		strcpy(oseba->razred_oddelek,tmp_razred_oddelek);
		oseba->pravice=tmp_pravice;
		oseba->st_ur=tmp_st_ur;
		oseba->st_ur_trenutno=0;
		oseba->id_ucenca=id_oseba;
		fwrite(oseba,sizeof(tip_osebe),1,osebna);

		fclose(osebna);
	}
	system("PAUSE");
}


void izpis_predmetov() {
	system("CLS");
	printf("\n\tIZPIS PREDMETOV\n");
	FILE *predmetna=fopen("predmeti.dat","rb");
	tip_predmeti *predmet=(tip_predmeti*)malloc(sizeof(tip_predmeti));
	while(fread(predmet,sizeof(tip_predmeti),1,predmetna)) {
		printf("\n\tIme predmeta: %s",predmet->ime);
		printf("\nOmejitev stevila ucence: %d",predmet->max_uc);
		printf("\nStevilo ur, ki jih predmet predstavlja: %d",predmet->st_ur);
		printf("\n");
	}
	fclose(predmetna);
	system("PAUSE");
}


void vpis_admin() {
	system("CLS");
	int izbira=0;
	while (izbira!=4) {
		printf("Pozdravljeni v ADMIN meniju!\n");
		printf("\n1: Vnos novega predmeta");
		printf("\n2: Vnos novega ucenca/ucitelja");
		printf("\n3: Izpis trenutnih predmetov");
		printf("\n4: Izhod iz programa");
		printf("\n\nIzbira: ");
		scanf("%d",&izbira);
		if (izbira==1) vnos_predmetov();
		if (izbira==2) vnos_ucencev();
		if (izbira==3) izpis_predmetov();
		system("CLS");
	}
}


void izpis_nezasedenih_predmetov() {
	system("CLS");
	printf("\n\tIZPIS NEZASEDENIH PREDMETOV\n");
	FILE *predmetna=fopen("predmeti.dat","rb+");

	tip_predmeti *predmet=(tip_predmeti*)malloc(sizeof(tip_predmeti));
	while(fread(predmet,sizeof(tip_predmeti),1,predmetna)) {

		if(predmet->trenutno_uc<=predmet->max_uc) {
			printf("\n\tIme predmeta: %s",predmet->ime);
			printf("\nProstih mest: %d",((predmet->max_uc)-(predmet->trenutno_uc)));
			printf("\n");
		}
	}
	fclose(predmetna);
	system("PAUSE");
}


void vpis_v_predmet(char tmp_up[10]) {
	int id_predmet;
	int id_ucenec;

	system("CLS");
	printf("\tVpis v predmet:\n");
	char tmp_predmet[20];
	printf("\nVpisite v kateri predmet se zelite vpisati: ");
	scanf("%s",&tmp_predmet);

	FILE *predmetna=fopen("predmeti.dat","rb");
	tip_predmeti *predmet=(tip_predmeti*)malloc(sizeof(tip_predmeti));

	//NAJPREJ PREVERIM CE SE UCENEC SPLOH LAHKO VPISE V PREDMET

	int najden=0;          //ce predmet obstaja se postavi na 1
	int prevec=0;          //ce je prevec vpisanih se postavi na 1
	while(fread(predmet,sizeof(tip_predmeti),1,predmetna)) {
		if (strcmp(tmp_predmet,predmet->ime)==0) {
			id_predmet=predmet->id_predmeta;
			najden=1;
			if (((predmet->max_uc)-(predmet->trenutno_uc))<=0)prevec=1;
		}
	}
	fclose(predmetna);
	if(najden==0) printf("\nPredmet NE obstaja!!!");
	else printf("\nTa predmet obstaja");
	if(prevec==1) printf("\nV predmet se ne morete vpisati saj je ze zapolnjen!");
	else printf("\nPredmet je se prost");

	int ure=0;    // ce je prevec ur se postavi na 1
	if((najden==1)&&(prevec==0)) {
		FILE *osebna=fopen("podatki.dat","rb");
		tip_osebe *oseba=(tip_osebe*)malloc(sizeof(tip_osebe));

		// edit by Dejan Sraka
		// Napaka: branje iz neprave datoteke vnese nakljuèno vrednost za id_ucenca
		//
		//while(fread(predmet,sizeof(tip_predmeti),1,predmetna)){
		// popravljeno spodaj
		while(fread(oseba, sizeof(tip_osebe),1,osebna)) {
			if((strcmp((oseba->up_ime),tmp_up)==0)) {
				id_ucenec=oseba->id_ucenca;
				if(oseba->st_ur_trenutno>=oseba->st_ur) ure=1;
			}
		}
		fclose(osebna);
	}
	if(ure==1) printf("Vpisani ste k prevec predmetom!");
	system("PAUSE");
	int povecanje;
	fpos_t poisci;

	//CE SE UCENEC LAHKO VPISE V PREDMET SE POVECA STEVEC ZA PREDMET IN PRI UCENCU!!!
	if((ure==0) && (najden==1) && (prevec==0)) { //se pravi ustreza vsem kriterijem

		//povecam stevilo ucencev v predmetu
		FILE *predmetna=fopen("predmeti.dat","rb+");
		tip_predmeti *predmet=(tip_predmeti*)malloc(sizeof(tip_predmeti));
		fgetpos(predmetna,&poisci);
		while(fread(predmet,sizeof(tip_predmeti),1,predmetna)) {

			if (strcmp(tmp_predmet,predmet->ime)==0) {

				predmet->trenutno_uc=predmet->trenutno_uc+1;
				povecanje=predmet->st_ur;
				fsetpos(predmetna,&poisci);
				fwrite(predmet,sizeof(tip_predmeti),1,predmetna);
				break;
			}
			fgetpos(predmetna,&poisci);

		}
		fclose(predmetna);


		fpos_t poisci;
		//sedaj povecam se ucenceve podatke
		FILE *osebna=fopen("podatki.dat","rb+");
		tip_osebe *oseba=(tip_osebe*)malloc(sizeof(tip_osebe));
		fgetpos(osebna,&poisci);
		while(fread(oseba,sizeof(tip_osebe),1,osebna)) {
			if((strcmp(oseba->up_ime,tmp_up)==0)) {
				oseba->st_ur_trenutno=(oseba->st_ur_trenutno)+povecanje;
				//tevilo ur se ne povecuje pri ucencih

				fsetpos(osebna,&poisci);

				fwrite(oseba,sizeof(tip_osebe),1,osebna);
				break;
			}
			fgetpos(osebna,&poisci);
		}
		fclose(osebna);

		tip_zbirke *baza=(tip_zbirke*)malloc(sizeof(tip_zbirke));
		FILE *baza_podatkov=fopen("baza.dat","ab");
		baza->aktiven=1;
		baza->id_predmeta=id_predmet;
		baza->id_ucenca=id_ucenec;
		fwrite(baza,sizeof(tip_zbirke),1,baza_podatkov);
		fclose(baza_podatkov);
	}
}

void izpis_izbranih(char tmp_up[10]) {
	system("CLS");
	int id_predmet;
	int id_ucenec;
	printf("\tIzbrani predmeti: \n\n");
	FILE *osebna=fopen("podatki.dat","rb");
	tip_osebe *oseba=(tip_osebe*)malloc(sizeof(tip_osebe));

	// edit by D.S.
	// nepravo branje
	//
	//while(fread(oseba,sizeof(tip_predmeti),1,osebna)){
	while(fread(oseba,sizeof(tip_osebe),1,osebna)) {
		if((strcmp((oseba->up_ime),tmp_up)==0)) {
			id_ucenec=oseba->id_ucenca;
		}
	}
	fclose(osebna);

	FILE *baza_podatkov=fopen("baza.dat","rb");
	tip_zbirke *baza=(tip_zbirke*)malloc(sizeof(tip_zbirke));
	while(fread(baza,sizeof(tip_zbirke),1,baza_podatkov)) {
		// edit by Dejan Sraka
		// Napaka: strcmp pri èemer ste vhodna parametra vstavili dve tevili
		//
		// if((strcmp(baza->id_ucenca,id_ucenec)==0)&&(baza->aktiven==1)){
		// popravljeno spodaj
		if((baza->id_ucenca == id_ucenec)&&(baza->aktiven==1)) {
			id_predmet=baza->id_predmeta;
			FILE *predmetna=fopen("predmeti.dat","rb");
			tip_predmeti *predmet=(tip_predmeti*)malloc(sizeof(tip_predmeti));
			while(fread(predmet,sizeof(tip_predmeti),1,predmetna)) {
				// edit by Dejan Sraka
				// Napaka: strcmp pri èemer ste vhodna parametra vstavili dve tevili
				//
				// if (strcmp(id_predmet,predmet->id_predmeta)==0) printf("\n->%s",predmet->ime);
				// popravljeno spodaj
				if (id_predmet == predmet->id_predmeta) {
					printf("->%s\n",predmet->ime);
					break;
				}
			}
			fclose(predmetna);
		}
	}
	fclose(osebna);
	fclose(baza_podatkov);
	system("PAUSE");
}


void izpis_iz_predmeta(char tmp_up[10]) {
	printf("\tIzpis iz predmeta:\n\n");
	char predmet_tmp[20];
	int id_predmeta;
	int id_ucenec;
	fpos_t poisci;

	printf("\nVpisite ime predmeta iz katerega se zelite izpisati: ");
	scanf("%s",&predmet_tmp);
	FILE *osebna=fopen("podatki.dat","rb");
	tip_osebe *oseba=(tip_osebe*)malloc(sizeof(tip_osebe));
	// edit by Dejan Sraka
	// Napaka pri branju iz datoteke. V datoteki osebna so podatki tipa tip_osebe
	// vi pa berete velikost podatka tip_predmeti
	//
	// while(fread(oseba,sizeof(tip_predmeti),1,osebna)){
	// popravljeno spodaj
	while(fread(oseba,sizeof(tip_osebe),1,osebna)) {
		if((strcmp((oseba->up_ime),tmp_up)==0)) {
			id_ucenec=oseba->id_ucenca;
		}
	}

	fclose(osebna);

	int tmp=0;
	int predmet_ur;
	// edit by D.S.
	//FILE *predmetna=fopen("predmeti.dat","rb");
	FILE *predmetna=fopen("predmeti.dat","rb+");// tudi za pisanje
	tip_predmeti *predmet=(tip_predmeti*)malloc(sizeof(tip_predmeti));
	fgetpos(predmetna,&poisci);

	while(fread(predmet,sizeof(tip_predmeti),1,predmetna)) {
		if (strcmp(predmet_tmp,predmet->ime)==0) {
			predmet_ur=predmet->st_ur;
			predmet->trenutno_uc=predmet->trenutno_uc-1;
			id_predmeta=predmet->id_predmeta;
			fsetpos(predmetna,&poisci);
			fwrite(predmet,sizeof(tip_predmeti),1,predmetna);
			fpos_t poisci2;
			// edit by D.S.
			//FILE *baza_podatkov=fopen("baza.dat","rb");
			FILE *baza_podatkov=fopen("baza.dat","rb+");// tudi za pisanje
			// edit by D.S.
			// shranjujete kazalec napaène datoteke
			// popravljeno spodaj
			//
			// fgetpos(predmetna,&poisci2);
			fgetpos(baza_podatkov,&poisci2);
			tip_zbirke *baza=(tip_zbirke*)malloc(sizeof(tip_zbirke));
			while(fread(baza,sizeof(tip_zbirke),1,baza_podatkov)) {
				// comment by D.S.
				// kaj pa ce je bil ucenec vpisan v predmet in se je ze izpisal?
				// id_predmeta in id_ucenca bosta zapisana v istem zapisu, a zapis ne bo aktalen!
				if((id_predmeta==baza->id_predmeta)&&(id_ucenec==baza->id_ucenca)) {
					//tukaj se zacikla
					// edit by D.S.
					// uporabljate datoteèni kazalec napaène datoteke
					// popravljeno spodaj
					//
					//fsetpos(predmetna,&poisci);
					fsetpos(baza_podatkov,&poisci2);
					baza->aktiven=0;
					fwrite(baza,sizeof(tip_zbirke),1,baza_podatkov);
					fclose(baza_podatkov);
					//break;
					tmp=1;
					break;
				}

				//tmp=1;

				// shranjujete datoteèni kazalec napaène datoteke
				// popravljeno spodaj
				//
				//fgetpos(predmetna,&poisci2);
				fgetpos(baza_podatkov,&poisci2);
			}
			// edit by D.S.
			// spodnja vrstica se ne izvede vsakokrat temveè le ob menjavi predmeta, kar ni pravilno
			// vrstico sem zapisal izven if stavka
			//
			//fgetpos(predmetna,&poisci);
			break;
		}
		// edit by D.S.
		// pred vsakim branjem novega podatka je potrebno dobili pozicijo datoteènega kazalca pred branjem
		// dodal spodnjo vrstico
		fgetpos(predmetna,&poisci);
	}
	fclose(predmetna);
	if(tmp==1) {
		//FILE *osebna=fopen("podatki.dat","rb");
		FILE *osebna=fopen("podatki.dat","rb+");// tudi za pisanje
		// edit by D.S.
		// shranjujete datoteèni kazalec napaène datoteke
		// popravljeno spodaj
		//
		//fgetpos(predmetna,&poisci);
		fpos_t poisci3;
		fgetpos(osebna,&poisci3);
		// edit by D.S.
		// nepravo branje
		//
		//while(fread(oseba,sizeof(tip_predmeti),1,osebna)){
		while(fread(oseba,sizeof(tip_osebe),1,osebna)) {
			if((strcmp((oseba->up_ime),tmp_up)==0)) {
				//fsetpos(predmetna,&poisci);
				fsetpos(osebna,&poisci3);
				oseba->st_ur_trenutno=oseba->st_ur_trenutno-predmet_ur;
				fwrite(oseba,sizeof(tip_osebe),1,osebna);
				break;
			}
			//fgetpos(predmetna,&poisci);
			fgetpos(osebna,&poisci3);
		}
		fclose(osebna);
	}
}

void vpis_ucenec(char tmp_up[10]) {
	system("CLS");
	int izbira=0;
	while (izbira!=5) {
		printf("Pozdravljeni v meniju za ucence:\n");
		printf("\n1: Izpis predmetov ki se niso zasedeni");
		printf("\n2: Vpis v predmet");
		printf("\n3: Izpis iz predmeta");
		printf("\n4: Izpis izbranih predmetov");
		printf("\n5: Izhod iz programa");

		printf("\n\nIzbira: ");
		scanf("%d",&izbira);
		if (izbira==1) izpis_nezasedenih_predmetov();
		if (izbira==2) vpis_v_predmet(tmp_up);
		if (izbira==3) izpis_iz_predmeta(tmp_up);
		if (izbira==4) izpis_izbranih(tmp_up);

		system("CLS");
	}
}


void zacetek() {
	FILE *podatki=fopen("podatki.dat","rb");
	char tmp_geslo[10],tmp_up[10];
	if (!podatki) {
		printf("Pozdravljeni! Trenutno ni shranjenih se nobenih uporabniskih imen in gesel! \n");
		printf("Prosim vnesite [prednastavljeno] uporabnisko ime in geslo \n\n");
		printf("POZOR! KO SE VPISETE SE NAJPREJ REGISTRIRAJTE!!!(varnostni razlogi)\n\n");
		printf("Uporabnisko ime: ");
		scanf("%s",&tmp_up);
		printf("Geslo: ");
		scanf("%s",&tmp_geslo);
		if ((strcmp(tmp_up,"admin")==0) && (strcmp(tmp_geslo,"admin12")==0)) vpis_admin();
		else {
			system("CLS");
			printf("Uporabnisko ime in geslo se ne ujemata!\nProgram se bo zakljucil...\n");
		}
	}

	else {
		tip_osebe *oseba=(tip_osebe*)malloc(sizeof(tip_osebe));
		printf("Pozdravljeni! \n");
		printf("Prosim vnesite uporabnisko ime in geslo: \n\n");
		printf("Uporabnisko ime: ");
		scanf("%s",&tmp_up);
		printf("Geslo: ");
		scanf("%s",&tmp_geslo);
		int tmp=0;
		system("CLS");
		while(fread(oseba,sizeof(tip_osebe),1,podatki)) {
			if((strcmp((oseba->up_ime),tmp_up)==0)&&(strcmp((oseba->geslo),tmp_geslo)==0)) {
				printf("\tPozdravljeni, %s %s\n\n",oseba->ime,oseba->priimek);
				system("PAUSE");
				tmp=1;
				int izbira;
				izbira=oseba->pravice;
				if (izbira==0) {
					vpis_ucenec(tmp_up);
					break;
				} else {
					vpis_admin();
					break;
				}
			}
		}
		if(tmp==0)printf("Uporabnisko ime in geslo se NE ujemata!\nProgram se bo zakljucil...");
		fclose(podatki);
	}
}

int main() {
	zacetek();
	printf("\n");
	system("PAUSE");
}
