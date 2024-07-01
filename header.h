	//Libraries
	#include <iostream>
	#include<fstream>
	#include <ctime>
	#include<cstdlib>
	#include<stdlib.h>
    #include<windows.h>
	
	
	using namespace std;
	//Global Arrays:
	int goal[5][5];
	int initial[5][5];
	char path[1000]={'\0'};
	
	//Global Variable:
	int x;                                //row index for 25th tile
	int y;                               //coloumn index for 25th tile
	int z=0;                            //variable to store moves in path[] 
	int total_count=0;                 //total legal moves takes by user        
	
	//Functions decleration:
	void init_();
	void goal_();
	void display_goal();
	void display_initial();
	bool is_solvable(int a1[5][5],int a2[5][5]);
	bool is_goal(int a3[5][5],int a4[5][5]);
	int legal_moves();
	void make_move();
	void print_path();
	
	
	void init_()
	{
		int num;
		
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				initial[i][j]=0;
			}
		}
		for(int i=0;i<5;++i)
		{
		for(int j=0;j<5;++j)
		{
		    Za:
		    num=rand()%25+1;                   //generation of random numbers
		    initial[i][j]=num;
		
		    for(int k=0;k<5;++k)
		    {
		        for(int x=0;x<5;++x)
		        {
		        	if(num==initial[k][x])
		        	{
		        		if(x==j&&k==i)
		        		{
		        			
						}
						else
						{
							goto Za;
						}
					}
				}
		   	}    
		}
	
	}
	  	 
	}
	void goal_()
	{
	  int num;
	  for(int i=0;i<5;++i)
	  {
	  	for(int j=0;j<5;++j)
	  	{
	  	    Za:
	  	    num=rand()%25+1;
	  	    goal[i][j]=num;
	  	
	  	    for(int k=0;k<5;++k)
		    {
		        for(int x=0;x<5;++x)
		        {
		        	if(num==goal[k][x])
		        	{
		        		if(x==j&&k==i)
		        		{
		        			
						}
						else
						{
							goto Za;
						}
					}
				}
	       	}    
		}
	  
	  }
	}
	void display_goal()
	{  
	 cout<<"\tGoal state is : "<<endl;
		for(int i=0;i<5;i++)
		 {
		 	cout<<"\t\t\t\t";
		 	for(int j=0;j<5;++j)
		 	{
		 	    if(goal[i][j]==25)
				 {
				 cout<<" "<<"\t";
				 x=i;
				 y=j;
	
				 }	
				 else
				 {
				  cout<<goal[i][j]<<"\t";
				 }
			}
			cout<<endl<<endl;
		 }
		}
	void display_initial()
	{   
	    cout<<"\t Initial state is : "<<endl;
		for(int i=0;i<5;i++)
		 {
		 	cout<<"\t\t\t\t";
		 	for(int j=0;j<5;++j)
		 	{
		 	    if(initial[i][j]==25)
				 {
				 cout<<" "<<"\t";
				 x=i;
				 y=j;
	
				 }	
				 else
				 {
				  cout<<initial[i][j]<<"\t";
				 }
			}
			cout<<endl<<endl;
		 }
		}
	bool is_solvable(int a1[5][5],int a2[5][5])	
	{
			 int count1=0,count2=0,temp;
	     for(int i=0;i<5;i++)                  //will count inverstion in initial state
		   {
		 	for(int j=0;j<5;++j)
		 	{
		 		temp=a1[i][j];
		 	     for(int k=i+1;k<5;++k)
		 	    {
		 	     for (int x=j+1;x<5;++x)
				  {
				  	if (temp>a1[k][x])
				  	{
				  		++count1;	
					}
				  }	
				}
			}
		}
	 
		for(int i=0;i<5;i++)                  //will count inverstion in goal state
		   {
		 	for(int j=0;j<5;++j)
		 	{
		 		temp=a2[i][j];
		 	     for(int k=i+1;k<5;++k)
		 	    {
		 	     for (int x=j+1;x<5;++x)
				  {
				  	if (temp>a2[k][x])
				  	{
				  	++count2;	
					}
				  }	
				}
			}
		    }	
		if(count1%2==0)      //will return true if and only idf inversion of both arrays will be even
		{
		   if(count2%2==0)
		    {
			  return true;
	     	} 
	     	else
	    	{
			  return false;
	    	}
	    }
	    else if(count1%2==1)    //will return true if and only idf inversion of both arrays will be odd
		{
		   if(count2%2==1)
		    {
			  return true;
	     	} 
	     	else
	    	{
			  return false;
	    	}
	    } 
	}
	int legal_moves()
	{
		// system("Color f6");
		bool n=false;
	  if(initial[0][0]==25)	
	  {
	  	cout<<" Legal Moves are : \n\t Left \n\t Up \n ";        //will tell legal moves if space is at upper left corner
	  	n=true;
	  }
	  else if(initial[0][4]==25)	                             //will tell legal moves if space is at upper right corner
	  {
	  	cout<<" Legal Moves are : \n\t Right \n\t Up \n ";
	  	n=true;
	  }
	  else if(initial[4][0]==25)	                             //will tell legal moves if spaces is at lower left corner
	  {
	  	cout<<" Legal Moves are : \n\t Down \n\t Left \n ";
	  	n=true;
	  }
	  else if(initial[4][4]==25)	                             //will tell legal moves if space is at lower right corner
	  {
	  	cout<<" Legal Moves are : \n\t Down \n\t Right \n ";
	  	n=true;
	  }
	  else if(1)
	  {
	  	for(int j=1;j<4;++j)                                     //will tell legal moves if space in the first row except corner
	  {
	  	 if(initial[0][j]==25)	
	  {
	  	cout<<" Legal Moves are : \n\t Left \n\t Right \n\t Up \n ";
	  	n=true;
	  	break;
	  	
	  }
	     else if(initial[4][j]==25)                              //will tell legal moves if space in the last row except corner	
	  {
	  	cout<<" Legal Moves are : \n\t Left \n\t Right \n\t Down \n ";
	  	n=true;
	  	break;
	  }
	  }
	  for(int i=1;i<4;++i)                                      //will tell legal moves if space in the first coloumn except corner	
	  {   
	   if(initial[i][0]==25)	
	  {
	  	cout<<" Legal Moves are : \n\t Left \n\t Up \n\t Down \n ";
	  	n=true;
	  	break;
	  } 
	     else if(initial[i][4]==25)	                            //will tell legal moves if space in the last coloumn except corner	
	  {
	  	cout<<" Legal Moves are : \n\t Right \n\t Up \n\t Down \n ";
	  	n=true;
	  	break;
	  }
	  }
	  }
	  if(n==false)                                              //will tell legal move for all other positions
	  {
	  	cout<<" Legal Moves are : \n\t Left \n\t Right \n\t Up \n\t Down \n ";
	  }
	  
	}
	void make_move()
	{
		char choice;
		int temp=0;

	    cout<<"\n Enter Direction : ";
	    cin>>choice;
	    path[z]=choice;                                                        // will store moves in path[] to print later
	    ++z;
	    total_count++;
	    switch(choice)
	    {
	    	case'u':                                                            // case to move the tile upward
	    	
			case 'U': 
		    	{
		    		x++;
		    		if(x!=5)
					{
						temp=initial[x][y];
			    		initial[x][y]=initial[--x][y];
			    		initial[x][y]=temp;
					}
					break;	
				}
			
	    	
			case'd':                                                            //case to move the tile downward	
		    case'D':
	    		{
				 x--;
	    		 if(x!=-1)
	    		 {
	    		 	temp=initial[x][y];
		    		 initial[x][y]=initial[++x][y];
		    		 initial[x][y]=temp;
				 }
				break;
				}
			
			case'r':                                                            //case to move the tile right
		    case'R':
	    		{
	    		--y;
	    		if(y!=-1)
				{
					temp=initial[x][y];
				initial[x][y]=initial[x][++y];
				initial[x][y]=temp;
				
				}
				break;	
				}
			
			case'l':                                                            //case to move the tile left
			case'L':
	    		{
				 ++y;
	    		if(y!=5)
				{
					temp=initial[x][y];
					initial[x][y]=initial[x][--y];
					initial[x][y]=temp;
					
				}
				break;	
				}
			
			default :                                                            //case to handle exception
				{
					cout<<"\n Wrong input\n";
				}
	  
		}
	}
	bool is_goal(int a3[5][5],int a4[5][5])
	{
	   for(int i=0;i<5;i++)                                    //this function will return true if goal state is equal to initial state 
		   {
		 	for(int j=0;j<5;++j)
		 	{
		 	if(a3[i][j]!=a4[i][j])
		 	{
		 		return false;
		 		break;
			 }
			}
		
		}  
		cout<<"\n----------------------------------------------------------congratulations------------------------------------------------------------";
		cout<<"\n--------------------------------------------------------You reached Goal state ---------------------------------------------------\n";
		return true;	
	}
	void print_path()
	{   
	     
	     ofstream oFile;
		 oFile.open("Puzzle Report.txt",ios::out) ;
		 oFile<<"Your Puzzle Report is as follow : ";
	     oFile<<"\n\t Your total moves are : "<<total_count;
	     oFile<<"\n\t Your moves from initial to goal state is as follow :   ";
		cout<<"\n--------------------------------------------------------------- Your Puzzle Report is as follow -----------------------------------------------------------";
	    cout<<"\n\t Your total moves are : "<<total_count;
	    cout<<"\n\t Your moves from initial to goal state is as follow :   ";
	 	for(int i=0;path[i]!='\0';++i)
	 	{
	 		switch(path[i])
	 		{
	 			case('u'):
	 		    case('U'):
	 		    	{
	 		    		oFile<<"UP\t";
	 		    		cout<<"UP\t";
	 		    		break;
					 }
			    case('d'):
	 		    case('D'):
	 		    	{
	 		    	    oFile<<"DOWN\t";
	 		    		cout<<"DOWN\t";
	 		    		break;
					 }
				case('l'):
	 		    case('L'):
	 		    	{
	 		    		oFile<<"LEFT\t";
	 		    		cout<<"LEFT\t";
	 		    		break;
					 }
				case('r'):
	 		    case('R'):
	 		    	{
	 		    		oFile<<"RIGHT\t";
	 		    		cout<<"RIGHT\t";
	 		    		break;
					 }
			 }
	 		
		 }
	
	    oFile.close();
		cout<<"\n\tYou can see you game report in the text file";
	    cout<<endl<<endl;
	}
	
	
	
 	
