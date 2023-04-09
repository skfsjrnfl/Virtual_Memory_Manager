#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

int* reference;
int* frame;
int* frameinfo;
int framesize;
bool Finding(int item);
int Findlarge();
bool Frameempty();

int main() {
	int pagenumber, windowsize, referencesize;
	FILE* fp;
	if ((fp = fopen("input.txt", "r") )== NULL) {
		printf("Can't open input.txt");
		exit(1);
	}
	fscanf(fp, "%d %d %d %d", &pagenumber, &framesize, &windowsize, &referencesize);

	reference =(int*) malloc(sizeof(int) * referencesize);
	frame =(int*) malloc(sizeof(int) * framesize);
	frameinfo =(int*) malloc(sizeof(int) * framesize);
	for (int i = 0; i < referencesize; i++) {
		fscanf(fp, "%d", reference + i);
		if ((reference[i] < 0) || (reference[i] >= pagenumber)) {
			printf("Wrong Reference string\n");
			printf("Over the scope of pagenumber");
			exit(1);
		}
	}
	for (int i = 0; i < framesize; i++) {
		frame[i] = -1;
	}
	fclose(fp); 
	//input save & frame initiate

	//MIN algorithm
	printf("MIN algorithm\n\n");
	
	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	int faultcount = 0;
	for (int i = 0; i < referencesize; i++) {
		printf("| %2d| %2d |",i,reference[i]);
		if (!(Finding(reference[i]))) {
			faultcount++;
			if (Frameempty()) {
				for (int j = 0; j < framesize; j++) {
					if (frame[j] == -1) {
						frame[j] = reference[i];
						break;
					}
				}
			}//Empty space remain
			else {
				for (int j = 0; j < framesize; j++) {
					frameinfo[j] = referencesize;
					for (int k = i + 1; k < referencesize; k++) {
						if (frame[j] == reference[k]) {
							frameinfo[j] = k - i;
							break;
						}
					}
				}
				frame[Findlarge()] = reference[i]; //victim select
			}

			for (int j = 0; j < framesize; j++) {
				if (frame[j]==-1){
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("F |\n");//memory state print

		}//page fault
		else {
			for (int j = 0; j < framesize; j++) {
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("  |\n");
		}//Not page fault
	}
	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	printf("Total fault number: %d \n\n\n", faultcount);


	//

	//Initiate
	for (int i = 0; i < framesize; i++) {
		frame[i] = -1;
		frameinfo[i] = -1;
	}
	faultcount = 0;
	//

	//FIFO algorithm
	printf("\nFIFO algorithm\n\n");

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	int fifocount = 0;
	for (int i = 0; i < referencesize; i++) {
		printf("| %2d| %2d |", i,reference[i]);
		if (!(Finding(reference[i]))) {

			faultcount++;
			frame[fifocount] = reference[i];//victim select
			fifocount = (fifocount + 1) % framesize;


			for (int j = 0; j < framesize; j++) {
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("F |\n");//memory state print

		}//page fault
		else {
			for (int j = 0; j < framesize; j++) {
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("  |\n");
		}//Not page fault
	}

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	printf("Total fault number: %d \n\n\n", faultcount);


	//


	//Initiate
	for (int i = 0; i < framesize; i++) {
		frame[i] = -1;
		frameinfo[i] = -1;
	}
	faultcount = 0;
	//


	//LRU algorithm
	printf("\nLRU algorithm\n\n");

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	for (int i = 0; i < referencesize; i++) {
		printf("| %2d| %2d |", i,reference[i]);
		if (!(Finding(reference[i]))) {
			faultcount++;
			if (Frameempty()) {
				for (int j = 0; j < framesize; j++) {
					if (frame[j] == -1) {
						frame[j] = reference[i];
						frameinfo[j] = referencesize - i;
						break;
					}
				}
			}//Empty space remain
			else {
				int victim = Findlarge();
				frame[victim] = reference[i]; //victim select
				frameinfo[victim] = referencesize - i;
			}

			for (int j = 0; j < framesize; j++) {
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("F |\n");//memory state print

		}//page fault
		else {
			for (int j = 0; j < framesize; j++) {
				if (frame[j] == reference[i]) {
					frameinfo[j] = referencesize - i;
				}
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("  |\n");
		}//Not page fault
	}

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	printf("Total fault number: %d \n\n\n", faultcount);

	
	//

	//Initiate
	for (int i = 0; i < framesize; i++) {
		frame[i] = -1;
		frameinfo[i] = 0;
	}
	faultcount = 0;
	//


	//LFU algorithm
	printf("\nLFU algorithm\n\n");

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");
	int* tiebreak = malloc(sizeof(int) * framesize);

	for (int i = 0; i < referencesize; i++) {
		printf("| %2d| %2d |", i,reference[i]);
		if (!(Finding(reference[i]))) {
			faultcount++;
			if (Frameempty()) {
				for (int j = 0; j < framesize; j++) {
					if (frame[j] == -1) {
						frame[j] = reference[i];
						frameinfo[j]++;
						tiebreak[j] = i;
						break;
					}
				}
			}//Empty space remain
			else {
				int victim=0;
				for (int j = 0; j < framesize; j++) {
					if (frameinfo[j] < frameinfo[victim]) {
						victim = j;
					}
					else if (frameinfo[j] == frameinfo[victim]) {
						if (tiebreak[j] < tiebreak[victim]) {
							victim = j;
						}
					}
				}
				
				frame[victim] = reference[i]; //victim select
				frameinfo[victim] = 1;
				tiebreak[victim] = i;
			}

			for (int j = 0; j < framesize; j++) {
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("F |\n");//memory state print

		}//page fault
		else {
			for (int j = 0; j < framesize; j++) {
				if (frame[j] == reference[i]) {
					frameinfo[j]++;
					tiebreak[j] = i;
				}
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("  |\n");
		}//Not page fault
	}
	free(tiebreak);

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	printf("Total fault number: %d \n\n\n", faultcount);
	//

		//Initiate
	for (int i = 0; i < framesize; i++) {
		frame[i] = -1;
		frameinfo[i] = 0;
	}
	faultcount = 0;
	//

	//Clock algorithm
	printf("\nClock algorithm\n\n");
	int clockpointer = 0;

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	for (int i = 0; i < referencesize; i++) {
		printf("| %2d| %2d |", i,reference[i]);
		if (!(Finding(reference[i]))) {
			faultcount++;
			if (Frameempty()) {
				for (int j = 0; j < framesize; j++) {
					if (frame[j] == -1) {
						frame[j] = reference[i];
						frameinfo[j] = 1;
						break;
					}
				}
			}//Empty space remain
			else {
				int victim;
				while (1) {
					if (frameinfo[clockpointer] == 0) {
						victim = clockpointer;
						break;
					}
					frameinfo[clockpointer] = 0;
					clockpointer = (clockpointer + 1) % framesize;
				}
				frame[victim] = reference[i]; //victim select
				frameinfo[victim] = 1;
			}

			for (int j = 0; j < framesize; j++) {
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("F |\n");//memory state print

		}//page fault
		else {
			for (int j = 0; j < framesize; j++) {
				if (frame[j] == reference[i]) {
					frameinfo[j] = 1;
				}
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("  |\n");
		}//Not page fault
	}

	printf("-------");
	for (int p = 0; p < framesize; p++) {
		printf("--");
	}
	printf("------\n");

	printf("Total fault number: %d \n\n\n", faultcount);
	//

	//Initiate
	
	faultcount = 0;
	frame = (int*)realloc(frame, sizeof(int) * pagenumber);
	frameinfo = (int*)realloc(frameinfo, sizeof(int) * pagenumber);
	if (frame == NULL) {
		printf("failed reallocation");
		exit(1);
	}
	if (frame == NULL) {
		printf("failed reallocation");
		exit(1);
	}
	for (int i = 0; i < pagenumber; i++) {
		frame[i] = -1;
		frameinfo[i] = -3;
	}
	//
	
	//WS algorithm
	printf("\nWS algorithm\n\n");

	printf("-------");
	for (int p = 0; p < pagenumber; p++) {
		printf("--");
	}
	printf("------\n");

	for (int i = 0; i < referencesize; i++) {
		printf("| %2d| %2d |", i,reference[i]);
		if ((frame[reference[i]] == -1)) {
			faultcount++;
			frame[reference[i]] = reference[i];
			frameinfo[reference[i]] = i;

			for (int j = 0; j < pagenumber; j++) {
				if ((i - frameinfo[j]) > windowsize) {
					frame[j] = -1;
				}
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("F |\n");//memory state print

		}//page fault
		else {
			frameinfo[reference[i]] = i;
			for (int j = 0; j < pagenumber; j++) {
				if ((i - frameinfo[j]) > windowsize) {
					frame[j] = -1;
				}
				if (frame[j] == -1) {
					printf("  ");
				}
				else {
					printf("%d ", frame[j]);
				}
			}
			printf("  |\n");
		}//Not page fault
	}

	printf("-------");
	for (int p = 0; p < pagenumber; p++) {
		printf("--");
	}
	printf("------\n");

	printf("Total fault number: %d \n\n\n", faultcount);
	//




	//ending
	
	free(frame);
	free(frameinfo);
	free(reference);
	
}
bool Finding(int item) {
	for (int i = 0; i < framesize; i++) {
		if (frame[i] == item) {
			return true;
		}
	}
	return false;
}
int Findlarge() {
	int m=0;
	for (int i = 0; i < framesize; i++) {
		if (frameinfo[i] > frameinfo[m]) {
			m = i;
		}
	}
	return m;
}

bool Frameempty() {
	for (int i = 0; i < framesize; i++) {
		if (frame[i] == -1)
			return true;
	}
	return false;
}
