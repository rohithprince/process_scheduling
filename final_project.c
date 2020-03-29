#include<stdio.h>
#include<string.h>
struct schedule{
	int Job_id;
	int Arri_time;
	int Bur_time;
	int Complet_time;
	int Remain_time;//rbt
}fqueue[100],squeue[100],rqueue[100];
int z, zfc=0,zsc=0, readycount=0;
int timequantum;

void Schedule_by_round_robin(){
	int time= rqueue[0].Arri_time, cont=0, pp=0, i, prc;
	while(time!=120 && pp!=readycount){
		for(i=0; i<=cont; i++){
			if(rqueue[i].Remain_time > timequantum){
				time=time + timequantum;
				rqueue[i].Remain_time -= timequantum;
			}
			else if(rqueue[i].Remain_time <=timequantum && rqueue[i].Remain_time !=0){
				time += rqueue[i].Remain_time;
				rqueue[i].Remain_time =0;
				rqueue[i].Complet_time = time;
				pp++;
			}
			else;
		}
		int first = cont+1;
		for(prc= first; prc<readycount; prc++){
			if(rqueue[prc].Arri_time <= time){
				cont++;
			}
		}
	}	
}

////

///
void Taking_input_both_queues(){
	int aic=0, bic= 0, Minimum, Flag;
	if( zfc!=0  && zsc!=0){
		while(aic<zsc && bic<zfc){
			if(fqueue[bic].Arri_time == squeue[aic].Arri_time){
				rqueue[readycount] = fqueue[bic];
				readycount++;
				bic++;
				rqueue[readycount]= squeue[aic];
				readycount++;
				aic++;
			}
			else if(fqueue[bic].Arri_time < squeue[aic].Arri_time){
				rqueue[readycount]= fqueue[bic];
				readycount++;
				bic++;
			}
			else if(fqueue[bic].Arri_time > squeue[aic].Arri_time){
				rqueue[readycount]= squeue[aic];
				readycount++;
				aic++;
			}
			else;
		}
		if(readycount != (zfc+zsc)){
			if(zfc!=bic){
				while(bic!=zfc){
					rqueue[readycount]= fqueue[bic];
					readycount++;
					bic++;
				}
			}
			else if(zsc!=aic){
				while(aic!=zsc){
					rqueue[readycount]= squeue[aic];
					readycount++;
					aic++;
				}
			}
		}
	}
	else if(zfc==0){
		while(aic!=zsc){
			rqueue[readycount]= squeue[aic];
			readycount++;
			aic++;
		}
	}
	else if(zsc==0){
		while(bic!=zfc){
		rqueue[readycount]= fqueue[bic];
			readycount++;
			bic++;
		}
	}
	else {
		printf("\n No valid Jobs available\n");
	}}
void Data(){
	
	int Queryt,i, k;
	printf("Enter total no of queries: "); scanf("%d", &z);
	if(z==0) { printf("\n No queries has be accepeted\n"); }
	else{
		printf("\nEnter timequantum for each Process: "); scanf("%d", &timequantum);
		
		for(i=0; i<z; i++){
			printf("n:Press 1(faculty) or 0(student) "); scanf("%d",&Queryt);
			if(Queryt==1){
				printf("Query Id: "); scanf("%d", &fqueue[zfc].Job_id);
				printf("Arrival Time: "); scanf("%d", &k);
				if(k<1000 || k>1200){
					printf("\n Entered wrong slot time ");
					Data();
				}
				else{fqueue[zfc].Arri_time= k-1000;}
				printf("Burst time: "); scanf("%d", &fqueue[zfc].Bur_time);	 fqueue[zfc].Remain_time= fqueue[zfc].Bur_time; 
				zfc++;
			} else{
				printf("Query Id: "); scanf("%d", &squeue[zsc].Job_id);
				printf("Arrival Time: "); scanf("%d", &k); 
				if(k<1000 || k>1200){
					printf("\nEntered wrong slot time\n");
					Data();
				}
				else {squeue[zsc].Arri_time= k-1000; }
				printf("Burst time: "); scanf("%d", &squeue[zsc].Bur_time);	 squeue[zsc].Remain_time= squeue[zsc].Bur_time;
				zsc++;
			}
		}
	}}
void Display_output(){
	
	int p=0, tot=0, sum=0; 
	double Avg;
	printf("\nHere is the summary....\n");
	printf("\nQuery ID\tArrival Time\tRessolving Time\tCompletion Time\tTurn Around Time\tWaiting Time");
	for(p; p<readycount; p++){
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",
		rqueue[p].Job_id, (rqueue[p].Arri_time+1000), rqueue[p].Bur_time, (rqueue[p].Complet_time+1000), (rqueue[p].Complet_time-rqueue[p].Arri_time), ((rqueue[p].Complet_time-rqueue[p].Arri_time)- rqueue[p].Bur_time));
		tot= rqueue[p].Complet_time;
		sum+= (rqueue[p].Complet_time-rqueue[p].Arri_time);}
			Avg = sum/readycount;
	printf("\n\nTotal time Spent for all queries: %d", tot);
	printf("\nAverage query time taken is : %f", Avg);//lf
	printf("\nAll queries have been solved");}





void main(){
	
	printf("\n \t \t \t \t \t------Important Notice------\n");
	printf("****Available from 10AM to 12PM only *.");
	printf("\n \n**** Please enter arrival time of process in format 1000 to 1200.\n for example 10AM=1000,10:30AM=1030.*");
	printf("\n \n**** Time units are in minutes.\n\n\n");
	Data();
	Taking_input_both_queues();
	Schedule_by_round_robin();
	Display_output();
}
