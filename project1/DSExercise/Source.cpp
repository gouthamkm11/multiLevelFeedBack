#include <iostream>//Used to handle input/output operations
#include <conio.h>
#include <dos.h>//Used for sleep
#include <stdio.h>//Standard input/output operations
#include <stdlib.h>//Memory allocation
#include <ctime>//Used for sleep
#include <Windows.h>//To include sleep time
using namespace std;
int counter = 0;  //Used for calculating the Execution Time
int count11 = 0;//Used t calculate the turn around time
int count1 = 0;// Dummy variable
int length, quantum; //Count of the process
struct node *head;//To declare the head node
struct node//This class defines the linked list structure
{
	int Data[8]; //Data is declared as array to store the Arv.Time,Burst Time,Waiting Time
	node *link;  //node pointer
};

void insert(int x[]) //Array function to insert data into the linked list
{
	node *temp = new node();   //This will create a dynamic memory location
	temp->Data[0] = x[0];      //Used to store the Arival Time from users input
	temp->Data[1] = x[1];     //Used to store the Burst Time from users input
	temp->Data[6] = -2;       //Fixing the default value
	temp->Data[7] = -1;       //Fixing the default value
	temp->link = head;        //To link the newly created list to the head node(Insertion at the head node)
	head = temp;			  //Head is linked with created node structure	
}


void chknewq()  //Working as expected, Used to check entry to new queue
{
	node *temp = new node();
	temp = head;
	while (temp != NULL)
	{
		if (temp->Data[5] > 0)
		{
			count11 = count11 + 1;
			//temp->link = head;
			//head = temp;
		}
		temp = temp->link;
	}
}

void chknewq1()  //Working as expected, Used to check entry to new queue
{
	node *temp = new node();
	temp = head;
	while (temp != NULL)
	{
		if (temp->Data[6] > 0)
		{
			count1 = count1 + 1;
			//temp->link = head;
			//head = temp;
		}
		temp = temp->link;
	}
}

void bubblesort()               //Used to sort the created linked list
{
	node *temp1, *temp2, *temp3, *temp4, *temp5;
	temp4 = NULL;
	while (temp4 != head->link)
	{
		temp3 = temp1 = head;
		temp2 = temp1->link;

		while (temp1 != temp4)
		{
			if (temp1->Data[0] > temp2->Data[0])
			{
				if (temp1 == head)
				{
					temp5 = temp2->link;
					temp2->link = temp1;
					temp1->link = temp5;
					head = temp2;
					temp3 = temp2;
				}
				else
				{
					temp5 = temp2->link;
					temp2->link = temp1;
					temp1->link = temp5;
					temp3->link = temp2;
					temp3 = temp2;
				}
			}
			else
			{
				temp3 = temp1;
				temp1 = temp1->link;
			}

			temp2 = temp1->link;
			if (temp2 == temp4)
			{
				temp4 = temp1;
			}
		}
	}
}


void waitprocess()   //Caluculation of WT,CT,TAT for Queue0
{
	node *temp = new node();
	cout << "Waiting time calculation for queue 0" << endl;
	temp = head;
	counter = temp->Data[0];
	while (temp != NULL)  //Traversing through the each node in linked List
	{
		if (counter >= temp->Data[0])
		{
			temp->Data[2] = counter - temp->Data[0];
			if (temp->Data[1] >= quantum)   //temp->Data[0] <= counter
			{
				temp->Data[3] = counter + quantum;
				counter = temp->Data[3];
				temp->Data[4] = temp->Data[3] - temp->Data[0];
				temp->Data[5] = temp->Data[1] - quantum;
			}
			else
			{
				//counter = temp->Data[0];  ---- When at is greater than previous completion time
				temp->Data[3] = counter + temp->Data[1];
				temp->Data[4] = temp->Data[3] - temp->Data[0];
				counter = temp->Data[3];
				temp->Data[5] = 0;
			}
		}
		else
		{
			counter = temp->Data[0];
			temp->Data[2] = counter - temp->Data[0];
			if (temp->Data[1] >= quantum)   //temp->Data[0] <= counter
			{
				temp->Data[3] = counter + quantum;
				counter = temp->Data[3];
				temp->Data[4] = temp->Data[3] - temp->Data[0];
				temp->Data[5] = temp->Data[1] - quantum;
			}
			else
			{
				//counter = temp->Data[0];  ---- When at is greater than previous completion time
				temp->Data[3] = counter + temp->Data[1];
				counter = temp->Data[3];
				temp->Data[4] = temp->Data[3] - temp->Data[0];
				temp->Data[5] = 0;
			}
		}
		temp = temp->link;
	}
}

//Wait Process 2
void waitprocess2()
{
	node *temp = new node();
	cout << "Waiting Time Calculation for Queue 1" << endl;
	temp = head;
	quantum = 16;
	while (temp != NULL)
	{
		if (temp->Data[5] != 0)
		{
			temp->Data[0] = temp->Data[3]; //C.T becomes the A.T
			temp->Data[1] = temp->Data[5];//Remaining Burst time becomes the Actual Burst Time
			if (counter >= temp->Data[0])
			{
				temp->Data[2] = counter - temp->Data[0];
				if (temp->Data[1] >= quantum)   //temp->Data[0] <= counter
				{
					temp->Data[3] = counter + quantum;
					counter = temp->Data[3];
					temp->Data[4] = temp->Data[3] - temp->Data[0];
					temp->Data[6] = temp->Data[1] - quantum;
				}
				else
				{
					//counter = temp->Data[0];  ---- When at is greater than previous completion time
					temp->Data[3] = counter + temp->Data[1];
					temp->Data[4] = temp->Data[3] - temp->Data[0];
					counter = temp->Data[3];
					temp->Data[6] = 0;
				}
			}
			else
			{
				counter = temp->Data[0];
				temp->Data[2] = counter - temp->Data[0];
				if (temp->Data[1] >= quantum)   //temp->Data[0] <= counter
				{
					temp->Data[3] = counter + quantum;
					counter = temp->Data[3];
					temp->Data[4] = temp->Data[3] - temp->Data[0];
					temp->Data[6] = temp->Data[1] - quantum;
				}
				else
				{
					//counter = temp->Data[0];  ---- When at is greater than previous completion time
					temp->Data[3] = counter + temp->Data[1];
					counter = temp->Data[3];
					temp->Data[4] = temp->Data[3] - temp->Data[0];
					temp->Data[6] = 0;
				}
			}
		}
		temp = temp->link;
	}
}

//Wait Process3
void waitprocess3()
{
	node *temp = new node();
	cout << "Waiting Time Calculation for Queue 2" << endl;
	temp = head;
	while (temp != NULL)
	{
		if (temp->Data[6] > 0)
		{
			temp->Data[0] = temp->Data[3]; //C.T becomes the A.T
			temp->Data[1] = temp->Data[6]; //Remaining Burst time becomes the Actual Burst Time
			if (counter >= temp->Data[0])
			{
				temp->Data[2] = counter - temp->Data[0];
				temp->Data[3] = counter + temp->Data[1];
				counter = temp->Data[3];
				temp->Data[4] = temp->Data[3] - temp->Data[0];
				temp->Data[7] = 0;
			}
			else
			{
				counter = temp->Data[0];
				temp->Data[2] = counter - temp->Data[0];
				temp->Data[3] = counter + temp->Data[1];
				counter = temp->Data[3];
				temp->Data[4] = temp->Data[3] - temp->Data[0];
				temp->Data[7] = 0;
			}
		}
		temp = temp->link;
	}
}


void printing()   //Output the data
{
	node *temp1 = head;
	while (temp1 != NULL) //Traversing through each node
	{
		cout << "Arrival Time is:" << temp1->Data[0] << endl;
		cout << "Burst Time is:" << temp1->Data[1] << endl;
		cout << "Waiting Time is:" << temp1->Data[2] << endl;
		cout << "Turn Around Time is:" << temp1->Data[4] << endl;
		cout << "Completion Time: " << temp1->Data[3] << endl;
		cout << "Remaining Burst time" << temp1->Data[5] << endl;
		cout << "-------------------------" << endl;
		temp1 = temp1->link;
	}
	//cout << "Average Waiting Time" << awt << endl;
	//cout << "Average Turn Around Time" << atr << endl;
}


void printing1()   //Output the data
{
	node *temp2 = new node();
	temp2 = head;
	while (temp2 != NULL) //Traversing through each node
	{
		if (temp2->Data[6] >= 0)
		{
			cout << "Arrival Time is:" << temp2->Data[0] << endl;
			cout << "Burst Time is:" << temp2->Data[1] << endl;
			cout << "Waiting Time is:" << temp2->Data[2] << endl;
			cout << "Turn Around Time is:" << temp2->Data[4] << endl;
			cout << "Completion Time: " << temp2->Data[3] << endl;
			cout << "Remaining Burst time" << temp2->Data[6] << endl;
			cout << "-------------------------" << endl;
		}
		temp2 = temp2->link;
	}
}

void printing2()   //Output the data
{
	node *temp2 = new node();
	temp2 = head;
	while (temp2 != NULL) //Traversing through each node
	{
		if (temp2->Data[7] == 0)
		{
			cout << "Arrival Time is:" << temp2->Data[0] << endl;
			cout << "Burst Time is:" << temp2->Data[1] << endl;
			cout << "Waiting Time is:" << temp2->Data[2] << endl;
			cout << "Turn Around Time is:" << temp2->Data[4] << endl;
			cout << "Completion Time: " << temp2->Data[3] << endl;
			cout << "Remaining Burst time" << temp2->Data[7] << endl;
			cout << "-------------------------" << endl;
		}
		temp2 = temp2->link;
	}
}


int main()
{
	node *first = new node();
	head = NULL;
	quantum = 8;
	int at, bt, data[2];
	cout << "How many process need to be created" << endl;
	cin >> length;
	/*cout << "Enter the quantum " << endl;
	cin >> quantum;*/
	srand(time(NULL));
	for (int i = 0; i < length; i++)
	{
		Sleep(10);
		at = rand() % 10;
		bt = rand() % 15 + 10;
		data[0] = at;
		data[1] = bt;
		insert(data);
	}
	bubblesort();
	waitprocess();//This will calculate the W.T,T.A.T and R.T for RRq=8;
				  //insert1();
				  //turnaprocess();
	printing();
	chknewq();
	if (count11 >= 1)
	{
		cout << count11 << " Process moved to Q1" << endl;
		cout << "Executed Time for Q0 is: " << counter << endl;
		waitprocess2();
		printing1();
	}
	else if(count11 == 0 && count1 == 0)
	{
		cout << "All process got executed in Q0" << endl;
	}
	chknewq1();
	if(count11 >= 1 && count1 >= 1)	
	{
	cout << count1 << " Process moved to Q2" << endl;
	cout << "Executed Time for Q1 is: " << counter << endl;
	waitprocess3();
	printing2();
	}
	else if(count1 == 0)
	{
	cout << "Remaining process got executed in Q1" << endl;
	}
	/*if (count11 >= 1)
	{
	cout << count11 << " Process moved to Q1" << endl;
	cout << "Executed Time for Q1 is: " << counter << endl;
	waitprocess2();
	printing1();
	}
	else
	{
	cout << "All process got executed in Q1" << endl;
	}
	/*if (count11 >= 1)
	{
	cout << count11 << " Process moved to Q2" << endl;
	cout << "Executed Time for Q2 is: " << counter << endl;
	waitprocess3();
	printing1();
	}
	else
	{
	cout << "All process got executed " << endl;
	}
	waitprocess3();
	printing();*/
}