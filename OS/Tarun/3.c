#include <stdio.h> 
struct process { 
	char name; 
	int at, bt, ct, wt, tt; 
	int complete; 
	float ntt; 
} p[10]; 
int m; 

void sortByArrival() 
{ 
	struct process temp; 
	int i, j; 

	for (i = 0; i < m - 1; i++) { 
		for (j = i + 1; j < m; j++) { 
			if (p[i].at > p[j].at) { 
				temp = p[i]; 
				p[i] = p[j]; 
				p[j] = temp; 
			} 
		} 
	} 
} 

void main() 
{ 
	int i, j, t, sum_bt = 0; 
	char c; 
	float avgwt = 0, avgtt = 0; 
	m = 5; 
    int number=0;
    printf("Enter the number of processes.");
    scanf("%d",&number);
    int arriv[30];
    int burst[30];
    for (int flag = 0; flag < number; flag++)
    {
        printf("Enter the arrival time and the burst time of the processes.");
        scanf("%d%d",&arriv[flag],&burst[flag]);
    }
	for (i = 0, c = 'A'; i < m; i++, c++) { 
		p[i].name = c; 
		p[i].at = arriv[i]; 
		p[i].bt = burst[i]; 

		p[i].complete = 0; 		
		sum_bt += p[i].bt; 
	} 

	sortByArrival(); 
	printf("\nName\tArrival Time\tBurst Time\tWaiting Time"); 
	printf("\tTurnAround Time\t Normalized TT"); 
	for (t = p[0].at; t < sum_bt;) { 
		float hrr = -9999; 
		float temp; 
		int loc; 
		for (i = 0; i < m; i++) { 
			if (p[i].at <= t && p[i].complete != 1) { 
				temp = (p[i].bt + (t - p[i].at)) / p[i].bt; 
				if (hrr < temp) { 
					hrr = temp; 
					loc = i; 
				} 
			} 
		} 

		t += p[loc].bt; 
		p[loc].wt = t - p[loc].at - p[loc].bt; 
		p[loc].tt = t - p[loc].at; 
		avgtt += p[loc].tt; 
		p[loc].ntt = ((float)p[loc].tt / p[loc].bt); 
		p[loc].complete = 1;
		avgwt += p[loc].wt; 
		printf("\n%c\t\t%d\t\t", p[loc].name, p[loc].at); 
		printf("%d\t\t%d\t\t", p[loc].bt, p[loc].wt); 
		printf("%d\t\t%f", p[loc].tt, p[loc].ntt); 
	} 
	printf("\nThe Average waiting time:%f\n", avgwt / m); 
	printf("The Average Turn Around time:%f\n", avgtt / m); 
} 