 	//Libraries
	#include <iostream>
	#include<fstream>
	#include <ctime>
	#include<cstdlib>
	#include<stdlib.h>
    #include<windows.h>
	#include"header.h"
	using namespace std;
	
	
	//Main Function 
	int main()
	{   
	    
	    srand(time(0));
		bool flag,flag2;
		int choice,choice2;
		goal_();  
		display_goal();                                 //Print goal state 
		cout<<endl<<endl;
		cout<<"\n Enter 1 if you want to take the numbers from txt file\n enter 0 if you want to generate random numbers\n\n choice: ";
		cin>>choice;
		if(choice==0)
		{
		do                                              //randomly initialize initial state
		{  
			init_();                                   //initialize initial state
		    flag=is_solvable(goal,initial);
		    if(flag==true)                             //check to terminate the loop if initial state is solvable
			{   
				break;
			}
	    }
	    while(1);
	    }
	    else if (choice==1)                            //will initialize initial state from text file
	    {
	    ifstream iFile;
		iFile.open("input.txt");
		if(!iFile)                                     //check to handle exception
		{
			cout<<" Error opening in file ";
		}
		else
		{
		for(int i=0;i<5;++i)
		{
			for (int j=0;j<5;++j)
			{
				iFile>>initial[i][j];
			}
		}
	    }
		iFile.close();
		}
		else                                            //check to handle exception
		{
		cout<<" Wrong input ";	
		}
	    display_initial();                             //print intial state 
	    cout<<"\n\t\t\t----------------------------------Puzzle is Solvable-----------------------------------\n\n\n";
	    cout<<"\n Enter \"L\" to move the tile to Left   ";                    //instructions
		cout<<"\n Enter \"R\" to move the tile to Right   ";
		cout<<"\n Enter \"D\" to move the tile to Down   ";
	    cout<<"\n Enter \"U\" to move the tile to Up \n  ";
		do
		{
		legal_moves();
	    make_move();	   
	    display_goal();                   //Print goal state                     
	    cout<<"\n\n";
	    cout<<"\t Initial state is : "<<endl;
	    display_initial();
	    cout<<"\n\tif you want to end the enter any number\n";
        cout<<"\t press 0 to continue :";
		cin>>choice2;
		if(choice2!=0)
		{
		break;	
		}
	    else
	    {
	    	continue;
		}
		flag2=is_goal(initial,goal);
	    }
	    
	    while(flag2==false);
	    if(flag2!=true)
	    {
	    	cout<<"\n---------------------------------------------------------------You did not reached the goal state------------------------------------------------------\n";
		}
	    print_path();	                          //function to print the path after goal state is reached
		
	}
	
