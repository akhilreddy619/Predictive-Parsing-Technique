#include<iostream>
#include<cstring>
using namespace std;
class prod
{
	private:
		char first[10][10],rhs[20][20],lhs[10],follow[10][10],nt[20],t[20],pro[20][20][20],st[20];
		int no[10],n,a[10],noa,l,b,k,p[10],w,temp[10][2],u,j,h;
		char rh[10][10],nr[10][10],rs[10][10],all[20][20],s[20],dd[20][20],lh,ak[20][20];
		int m,g,min;		
	public:
		//"all" is used for storing productions after eliminating left recursion.
		//"dd" is used for storing productions after eliminating left factoring.
		//"first" and "follow" are used to store first and follow of each non terminal (only) here.
		prod()
		{
			m=0;g=0;min=100;
			for(int i=0;i<20;i++)
			for(int j=0;j<20;j++)
			all[i][j]=dd[i][j]=ak[i][j]='\0';			
			j=0;h=0;
			l=0;b=0;k=0,w=0;u=0;
			for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
			{
				temp[i][j]=0;
				first[i][j]='\0';
				follow[i][j]='\0';
			}
			n=0;
			for(int i=0;i<10;i++)
			st[i]='\0';
			for(int i=0;i<10;i++)
			lhs[i]='\0';
			for(int i=0;i<10;i++)
			no[i]=p[i]=0;
			for(int i=0;i<20;i++)
			for(int j=0;j<20;j++)
			rhs[i][j]='\0';
			for(int i=0;i<20;i++)
			for(int j=0;j<20;j++)
			for(int k=0;k<20;k++)
			pro[i][j][k]='\0';    //array to produce a table of productions for parsing.
		}
		void checks(char *str)   //finding terminals and non terminals.
		{
			int flag=0;
				char *s=str;
				for(int p=0;p<strlen(s);p++) //search begins
				{
					if(s[p]>=65 && s[p]<=90) //if the character is a capital letter,then it is stored in "nt".
					{
						if(nt=='\0')  //initially "nt" is empty.
						{
							nt[j++]=s[p];
							if(s[p+1]=='-' && s[p+2]=='>')
							p=p+2;
						}    //stored first non terminal of LHS and skipping "->".
						else
						{
							flag=0;
							for(int l=0;l<sizeof(nt)/sizeof(nt[0]);l++) //when "nt" is not empty.
							if(nt[l]==s[p]) 
							flag=1;              //if the NT is already found, it is not stored in "nt"
							if(flag==0)
							{
								nt[j++]=s[p];
							}
							if(s[p+1]=='-' && s[p+2]=='>')  //skipping "->".
							p=p+2;
						}
					}
					else if(!(s[p]>=65 && s[p]<=90) && s[p]!='e' && s[p]!='/') //search for terminals.
					{
						if(nt=='\0')  //initially "t" is empty and "t" stores terminals.
						t[h++]=s[p];
						else    //if not empty, adds the terminal to the top.  
						{
							flag=0;
							for(int l=0;l<sizeof(t)/sizeof(t[0]);l++)
							if(t[l]==s[p])
							flag=1;
							if(flag==0)
							{
								t[h++]=s[p];
							}
						}
					}
				}
				int l;
				for(l=0;l<h;l++) 
				if(t[l]=='$')
				break;
				if(l==h)
				t[h++]='$';  //storing "$" into "t".
		}		
		void makeprod(char *str)  //separates LHS and RHS
		{
			char r[20];
			strcpy(r,str+3); //copies RHS into "r"
			int j=0;
			lhs[k++]=str[0];
			n++;noa=0;
			for(int i=0;r[i]!='\0';i++)  //RHS is split into multiple alternatives.
			{
				if(r[i]!='/')
				rhs[b][j++]=r[i];
				else
				{
					rhs[b++][j]='\0';
					j=0;
					noa++;
				}
			}

			b++;
			p[w++]=b;    //"p" is used to count total no. of productions traversed.
			noa++;
			no[l++]=noa; //"no" stores no. of alternatives for each productions.
		}
		void first_chk() //finding first.
		{
			int m=0;
			int t=b-1;  //"t" gives total no of alternatives entirely.
			for(int i=n-1;i>=0;i--)
			{
				for(int j=0;j<no[i];j++)
				{
					if(!(rhs[t][0]>=65 && rhs[t][0]<=90))
					{
						first[i][m++]=rhs[t][0];    //storing terminals into "first"
						t--;
					}
					else   //if the character is a NT
					{
						int x;
						char c=rhs[t][0];
						for(x=0;x<n;x++)
						if(c==lhs[x] && lhs[x]!='\0')  //if first(x) is empty then skip 1 iteration 
						if(first[x][0]=='\0')
						continue;
						else
						{
							for(int z=0;z<a[x];z++)  //else copying the first(x) into first(i)
							{
								int flag=0;
								for(int l=0;l<strlen(first[i]);l++)
								if(first[x][z]==first[i][l])
								flag=1;
								if(flag==0)
								first[i][m++]=first[x][z];
							}
							int s=1,len=strlen(rhs[t]);
							while(first[i][0]=='e' && s<len)  //if NT contains epsillon go to next NT
							{
								int g;
								char c=rhs[t][s];
								for(g=0;g<n;g++)
								if(c==lhs[g] && lhs[g]!='\0')
								if(first[g][0]=='\0')
								continue;
								else
								{
									for(int z=0;z<a[g];z++)
									{
										int flag=0;
										for(int l=0;l<strlen(first[i]);l++)
										if(first[g][z]==first[i][l])
										flag=1;
										if(flag==0)
										first[i][m++]=first[g][z];
									}
								}
								s++;		
							}
							t--;
						}
					}
				}
				a[i]=m;  //"a" is used to store the no. of terminals in each first(NT)
				m=0;
			}
		}
		void follow_chk()  //finding follow(x)
		{
			int m=1;
			follow[0][0]='$'; //initially start symbol ha $ in its follow.
			for(int i=0;i<n;i++) //iterations for "n" no. of NT
			{
				int flag=0;
				for(int j=0;j<b;j++)
				{
					int z;
					for(z=0;z<strlen(rhs[j]);z++)
					if(lhs[i]==rhs[j][z])
					{
						flag=1;
						if(flag==1)
						{
							if(rhs[j][z+1]!='\0')   //A-> aBb and b!='e' then follow(B)=first(b)
							{
								if(!(rhs[j][z+1]>=65 && rhs[j][z+1]<=90))
								follow[i][m++]=rhs[j][z+1];
								else
								{
									int flag=0,r=0;
									for(int a=0;a<n;a++)
									{
										if(rhs[j][z+1]==lhs[a])
										{
											for(r=0;r<strlen(first[a]);r++)
											{
												flag=0;
												for(int l=0;l<strlen(follow[i]);l++)
												if(first[a][r]==follow[i][l])
												flag=1;
												if(flag==0 && first[a][r]!='e')
												follow[i][m++]=first[a][r];	
											}
											
										}										
										if(rhs[j+1][0]=='e') //this if for X->+TX/e
										{
											for(r=0;r<strlen(follow[a]);r++)
											{
												flag=0;
												for(int l=0;l<strlen(follow[i]);l++)
												if(follow[a][r]==follow[i][l])
												flag=1;
												if(flag==0 && follow[a][r]!='e')
												follow[i][m++]=follow[a][r];	
											}
										}
										flag=0;
									}
								}
							}
							else  //if A->aBb and b='e' then add follow(A) to follow(B)
							{
								int q;
								for(q=0;q<n;q++)
								{
									if(j>=p[q])
									continue;
									else 
									break;
								}
								if(follow[q][0]=='\0')  
								{
									temp[u++][0]=q;
									temp[u-1][1]=i;
								}
								if(strcmp(follow[i],follow[q])!=0)
								strcat(follow[i],follow[q]);
							}
						}
					}
				}
				m=0;
			}
			if(u>0) //This is used in SLR grammar to find follow(L) and follow(R)
			{
				for(int i=0;i<u;i++)
				{
					int x=temp[i][1];
					int y=temp[i][0];
					strcpy(follow[x],follow[y]);
				}
			}
		}
		void table()  //parse table construction
		{
			for(int i=0;i<j;i++)
			for(int j=0;j<h;j++)
			if(pro[i][j][0]=='\0')  //initially assigning all values to be "error"
			strcpy(pro[i][j],"error");
			for(int z=0;z<b;z++)  //checking each alternative
			{
				if(rhs[z][0]!='e' & (rhs[z][0]>=65 && rhs[z][0]<=90)) //if rhs[z][o] is NT
				{
					int q;
					for(q=0;q<n;q++)  //finding the position of NT
					{
						if(z>=p[q])
						continue;
						else 
						break;
					}
					int flag=0;
					for(int i=0;i<strlen(first[q]);i++)  //copying the rhs into the position
					{
						int l;
						for(l=0;l<h;l++)
						{
							if(first[q][i]==t[l])
							break;
						}
						if(strcmp(pro[q][l],"error")==0) //only if "error" is stored already
						strcpy(pro[q][l],rhs[z]);
						else       //otherwise concatenate the old string with present alternative
						{
							strcat(pro[q][l],"/");
							strcat(pro[q][l],rhs[z]);
						}
					}
				}
				else if(!(rhs[z][0]>=65 && rhs[z][0]<=90) && rhs[z][0]!='e') // for terminals
				{
					int q;
					for(q=0;q<n;q++)  
					{
						if(z>=p[q])
						continue;
						else 
						break;
					}					
					int l;
					for(l=0;l<h;l++)
					{
						if(rhs[z][0]==t[l])
						break;
					}
					if(strcmp(pro[q][l],"error")==0)  //copying into table
					strcpy(pro[q][l],rhs[z]);	
					else
					{
						strcat(pro[q][l],"/");
						strcat(pro[q][l],rhs[z]);									
					}

				}
				else  //for epsilon, find follow(A) and copy into the table
				{
					int q;
					for(q=0;q<n;q++)
					{
						if(z>=p[q])
						continue;
						else 
						break;
					}
					for(int i=0;i<strlen(follow[q]);i++)
					{
						int l;
						for(l=0;l<h;l++)
						{
							if(follow[q][i]==t[l])
							break;
						}
						if(strcmp(pro[q][l],"error")==0)
						strcpy(pro[q][l],rhs[z]);
					}
				}
			}
			cout<<"Parse Table is: \n";
			cout<<"\t";
			for(int i=0;i<h;i++)
			cout<<t[i]<<"\t";
			cout<<"\n";
			for(int i=0;i<j;i++)
			{
				cout<<lhs[i]<<"\t";
				for(int j=0;j<h;j++)
				cout<<pro[i][j]<<"\t";
				cout<<"\n";
			}
		}
		void parse()  //parsing the string
		{
			char str[20];
			cout<<"enter a string\n";
			cin>>str;
			st[0]='$';
			st[1]=lhs[0];
			int top=0;
			for(int i=0;i<j;i++)  //if any / is found then it is not LL(1) grammar
			{
				for(int j=0;j<h;j++)
				{
					for(int k=0;pro[i][j][k]!='\0';k++)
					if(pro[i][j][k]=='/')
					top=1;
				}
			}
			if(top==1)
			cout<<"String cannot be parsed\n";
			else  //otherwise string can be parsed
			{
				int l,a,c=strlen(st),x=0,flag=0;
				while(c!=1)
				{
					if(st[c-1]>=65 && st[c-1]<=90)  //if NT, then replace it with its rhs
					{
						for(int i=0;i<sizeof(nt)/sizeof(nt[0]);i++)
						if(st[c-1]==lhs[i])
						{
							flag=1;
							l=i;
							break;
						}
						flag=0;
						for(int i=0;i<sizeof(t)/sizeof(t[0]);i++)
						if(str[x]==t[i])
						{
							flag=1;
							a=i;
							break;
						}
						flag=0;
						if(strcmp(pro[l][a],"error")!=0)
						{
							int g=0;
							char f[10];
							for(int i=0;i<10;i++)
							f[i]='\0';
							for(int i=strlen(pro[l][a])-1;i>=0;i--)
							f[g++]=pro[l][a][i];
							g=0;
							st[c-1]='\0';
							c--;
							if(f[0]!='e')
							strcat(st,f);
							cout<<st<<"\n";
							c=strlen(st);						
						}
						else
						break;
					}
					else  //if terminal and matched with string input pop it
					{
						if(st[c-1]==str[x])
						{
							st[c-1]='\0';
							x++;
							c--;
						}
						else
						break;
						cout<<st<<"\n";
					}
				}
				if(c==1)
				cout<<"string accepted\n";
				else
				cout<<"rejected\n";					
			}
		}
		void display() //to display NT and T and first(x) and follow(x)
		{
			cout<<"non terminals are \n";  //non terminals
			for(int i=0;i<j;i++)
			cout<<nt[i]<<" ";
			cout<<"\n\n";
			cout<<"terminals are \n";  //terminals
			for(int i=0;i<h;i++)
			cout<<t[i]<<" ";
			cout<<"\n\n";
			for(int i=0;i<n;i++)  //first(x)
			{
				cout<<"First of "<<lhs[i]<<" ";
				for(int j=0;j<a[i];j++)
				cout<<first[i][j]<<" ";
				cout<<"\n";
			}
			cout<<"\n";
			for(int i=0;i<n;i++) //follow(x)
			{
				cout<<"follow of "<<lhs[i]<<" ";
				for(int j=0;follow[i][j]!='\0';j++)
				cout<<follow[i][j]<<" ";
				cout<<"\n";				
			}
			cout<<"\n";
		}
		void makeprod1(char *str)  //separates lhs and rhs of a production
		{
			noa=0;
			for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
			rh[i][j]='\0';			
			lh=str[0];
			char r[20];
			strcpy(r,str+3);
			int j=0;
			for(int i=0;r[i]!='\0';i++)
			{
				if(r[i]!='/')
				rh[noa][j++]=r[i];
				else
				{
					rh[noa++][j]='\0';
					j=0;
				}
			}
			noa++;
		}
		void left(string sr)  //left recursion
		{
			for(int i=0;i<10;i++)
			for(int j=0;j<10;j++)
			rs[i][j]=nr[i][j]='\0';		
			int ct=0,k=0,l=0;
			for(int i=0;i<noa;i++)
			{
				if(lh==rh[i][0])    //store the alternatives with LR into "rs"
				{
					strcat(rh[i],sr.c_str());
					strcpy(rs[k],rh[i]+1);
					k++;
				}
				else  //store the alternatives without LR into "nr"
				{
					strcpy(nr[l],rh[i]);
					strcat(nr[l],sr.c_str());
					l++;
				}
			}
			if(l==noa)  //if length of "nr"=total no. of alternatives,then store them into "all" normally
			{
				all[m][0]=lh;
				strcat(all[m],"->");
				for(int i=0;i<noa;i++)
				{
					strcat(all[m],rh[i]);
					strcat(all[m],"/");
				}
				m++;
			}
			else  //if left recursion terms exist
			{
				all[m][0]=lh;
				strcat(all[m],"->");
				for(int i=0;i<l;i++)
				{
					strcat(all[m],nr[i]);
					strcat(all[m],"/");
				}
				m++;
				all[m][0]=sr[0];
				strcat(all[m],"->");
				for(int i=0;i<k;i++)
				{
					strcat(all[m],rs[i]);
					strcat(all[m],"/");
				}
				strcat(all[m],"e");
				m++;								
			}
		}
		void fac_call()  //function to send obtained strings as i/p to perform left factoring
		{
			string pp[5]={"A","B","C","D","Q"};
			int t=0;			
			for(int i=0;i<m;i++)
			{
				if(all[i][strlen(all[i])-1]=='/')
				all[i][strlen(all[i])-1]='\0';
				char f[20];
				strcpy(f,all[i]);
				makeprod1(f);
				factors(pp[t++]);
			}			
		}
		void factors(string ss)  //left factoring function
		{
			for(int i=0;i<20;i++)
			s[i]='\0';			  //"s" is used to store common sub string
			int h=1,y=1,t=1,z=0;
			int a[10],min=100;
			char sr[20][20],b[20][20];  //"sr" is used to store LF terms,"b"- to store non LF terms
			for(int i=0;i<20;i++)
			for(int j=0;j<20;j++)
			b[i][j]=sr[i][j]='\0';
			strcpy(sr[0],rh[0]);
			char c=rh[0][0];
			for(int i=1;i<noa;i++) //based on first character rhs is separated into "sr" and "b"
			{
				if(c==rh[i][0])
				strcpy(sr[h++],rh[i]);
				else
				strcpy(b[z++],rh[i]);
			}
			s[0]=c;
			for(int i=0;i<h;i++) //finding the min. length of alternative in the LF terms
			{
				a[i]=strlen(sr[i]);
				if(a[i]<min)
				min=a[i];
			}
			for(int j=1;j<min;j++)  //finding common sub-string from LF terms
			{
				for(int k=1;k<h;k++)
				{
					if(sr[0][j]==sr[k][j])
					t++;
				}
				if(t==h)
				{
					s[y++]=sr[0][j];
					t=1;
				}
				else
				{
					s[y]='\0';
					break;
				}
			}
			if(h==1) //if no LF exists
			{
				dd[g][0]=lh;
				strcat(dd[g],"->");
				for(int i=0;i<noa;i++)
				{
					strcat(dd[g],rh[i]);
					strcat(dd[g],"/");
				}
				g++;
			} 
			else  //if LF exists,storing the productions into "dd" as non-LF terms
			{
				dd[g][0]=lh;
				strcat(dd[g],"->");
				strcat(dd[g],s);
				strcat(dd[g],ss.c_str());				
				strcat(dd[g],"/");
				for(int i=0;i<z;i++)
				{
					strcat(dd[g],b[i]);
					strcat(dd[g],"/");
				}
				g++;
				dd[g][0]=ss[0];
				strcat(dd[g],"->");
				if(strlen(s)==min)
				{
					strcat(dd[g],"e/");
					for(int i=0;i<h;i++)
					{
						char w[20];
						strcpy(w,sr[i]+min);
						strcat(dd[g],w);
						if(i!=h-1)
						strcat(dd[g],"/");
					}
					g++;
				}
				else
				{
					for(int i=0;i<h;i++)
					{
						char w[20];
						strcpy(w,sr[i]+min);
						strcat(dd[g],w);
						strcat(dd[g],"/");
					}
					g++;
				}
			}
		}
		void calling()  //function to call checks,first_chk,follow_chk
		{
			for(int i=0;i<g;i++)
			{
				if(dd[i][strlen(dd[i])-1]=='/')
				dd[i][strlen(dd[i])-1]='\0';
				strcpy(ak[i],dd[i]);
			}
			for(int i=0;i<g;i++)
			{
				makeprod(ak[i]);
				checks(ak[i]);  //finds terminals and NT
			}
			first_chk(); //performs first(x)
			follow_chk(); //performs follow(x)
			display();  //displays the o/p
			table();  // displays the parse table
			parse();  //parses the given string
		}
		void display1() //function to show productions after LR and LF
		{
			cout<<"after left recursion "<<"\n";
			for(int i=0;i<m;i++)
			{
				for(int j=0;all[i][j]!='\0';j++)
				cout<<all[i][j];
				cout<<"\n";
			}
			cout<<"\n";
			cout<<"after left factoring "<<"\n";
			for(int i=0;i<g;i++)
			{
				for(int j=0;dd[i][j]!='\0';j++)
				cout<<dd[i][j];
				cout<<"\n";
			}
			cout<<"\n";	
		}		
};
int main()
{
	prod p;
	char str[20][20];
	int n,l=0;
	string op[5]={"X","Y","Z","U","V"};	
	cout<<"enter no of productions\n";
	cin>>n;
	cout<<"enter productions\n";
	for(int i=0;i<n;i++)
	cin>>str[i];
	for(int i=0;i<n;i++)
	{
		p.makeprod1(str[i]);
		p.left(op[l++]);
	}
	p.fac_call();
	p.display1();
	p.calling();
	return 0;
}
