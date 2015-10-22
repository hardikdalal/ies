#include<conio.h>
#include<iostream>
#include<string>
#include<dos.h>
#include<fstream>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>



using namespace std;
const string path("D:\\\CATS\\");

class myException
{
	string errMsg;
public:
	myException()
	{
		errMsg="\n\n\nERR::";
	}
	void setError(string str)
	{
		errMsg=errMsg+str;
	}
	string getError()
	{
		return errMsg;
	}
};

class person
{
protected:
	int age;
	char fName[20],mName[20],lName[20],edu[20],gender;
public:
	person()
	{
		age=0;
		strcpy(fName,"");
		strcpy(mName,"");
		strcpy(lName,"");
		strcpy(edu,"");
		gender='X';
	}
	void getPersonalData()
	{
		cout<<"\nEnter details::";
		cout<<"\nFirst Name::";
		cin>>fName;
		cout<<"\nMiddle Name::";
		cin>>mName;
		cout<<"\nLast Name::";
		cin>>lName;
		getGender();
		getAge();
		cout<<"\nEducational Qualification::";
		cin>>edu;
	}
	void getGender()
	{
		cout<<"\nGender (press M for Male and F for female)::";
		gender=getche();
		try
		{
			if(gender!='M' && gender!='m' && gender!='F' && gender!='f')
			{
				myException ex1;
				ex1.setError("Invalid Gender. Gender must be either Male or Female");
				throw ex1;
			}
		}
		catch(myException ex)
		{
			cout<<ex.getError();
			getGender();
		}
	}
	void getAge()
	{
		cout<<"\n\nAge::";
		cin>>age;
		try
		{
			if(age<10 || age >50)
			{
				myException ex1;
				ex1.setError("Please enter appropriate age (Between 10 and 50)");
				throw ex1;
			}
		}
		catch(myException ex)
		{
			cout<<ex.getError();
			getAge();
		}
	}
};
class question
{
public:
	int level;
	char qString[100];
	char optString[4][100];
	int aIndex;
	question()
	{
		strcpy(qString,"");
		for(int i=0;i<4;i++)
			strcpy(optString[i],"");
		aIndex=-1;
		level=-1;
	}
	void newQuestion()
	{
		ofstream destFile;
		myException ex1;
		char tempLevel[2],temp;
		try
		{
			cout<<"\nNote:Press ; to end";
			cout<<"\nEnter Question::";
			cin.getline(qString,100,';');
			cout<<"\nEnter Options::";
			for(int i=0;i<4;i++)
			{
				cout<<"\nOption-"<<i+1<<"::";
				cin.getline(optString[i],100,';');
			}
			getIndex();
			getLevel();	
			cout<<"\nPress any key to review question.";
			getch();
			viewQuestion();
			cout<<"\n\nPress 1 to confirm question::";
			temp=getche();
			if(temp=='1')
			{
				itoa(level,tempLevel,10);
				string destPath(path);
				destPath=destPath+"\questions\level"+tempLevel+".dat";
				destFile.open(destPath,ios::app | ios::binary);
				if(!destFile.is_open())
				{
					ex1.setError("Cannot open question containing file");
					throw ex1;
				}
				destFile.write((char *)this,sizeof(*this));
				if(!destFile.good())
				{
					ex1.setError("Cannot write into file");
					throw ex1;
				}		
				cout<<"\n\n\nCongratulations!\nYou have successfully added a question in Level-"<<level;
			}
		}
		catch(myException ex)
		{
			cout<<ex.getError();	
		}
		destFile.close();
	}
	void viewQuestion()
	{
		cout<<"\n\n\nLevel-"<<level;
		cout<<"\nQuestion String::"<<qString;
		cout<<"\nOptions::";
		for(int i=0;i<4;i++)
		{
			cout<<"\n"<<i+1<<"::"<<optString[i];
		}
		cout<<"\nAnswer Index::"<<aIndex+1;
		cout<<"\n\nCorrect Answer::"<<optString[aIndex];
	}
	void flushValues()
	{
		strcpy(qString,"");
		for(int i=0;i<4;i++)
			strcpy(optString[i],"");
		aIndex=-1;
		level=-1;
	}
	void getLevel()
	{
		try
		{
			cout<<"\nEnter level number (between 0 and 9)::";
			cin>>level;
			if(level<1 || level >9)
			{
				myException ex1;
				ex1.setError("Invalid level number");
				throw ex1;
			}
		}
		catch(myException ex)
		{
			cout<<ex.getError();
			getLevel();
		}
	}
	void getIndex()
	{
		try
		{
			cout<<"\nEnter Answer Index (between 1 and 4)::";	
			cin>>aIndex;
			aIndex--;
			if(aIndex<0 || aIndex>3)
			{
				myException ex1;
				ex1.setError("Invalid answer index");
				throw ex1;
			}
		}
		catch(myException ex)
		{
			cout<<ex.getError();
		}
	}	
};
class testTaker : public person
{
	float score;
	int proScore;
	int gPoints[30];
public:
	testTaker()
	{
		person();
		age=0;
		score=0;
		proScore=0;
	}
	void showResult()
	{
		cout<<"\n\nYour Details::";
		cout<<"\n\nName::";
		if(gender=='M' || gender=='m')
			cout<<"Mr. ";
		else
			cout<<"Mrs. ";
		cout<<fName<<" "<<mName<<" "<<lName;
		cout<<"\tAge::"<<age<<" years";
		cout<<"\nEducational Qualification::"<<edu;
		cout<<"\n\nYour score is "<<score;
		cout<<"\nProficiency score "<<proScore;
		cout<<"\n\nProficiency Score Information\n\n";
		string sourcePath(path);
		char ch;
		sourcePath=sourcePath+"pro_information.txt";
		try
		{
			ifstream sourceFile(sourcePath);
			if(!sourceFile.is_open())
			{
				myException ex1;
				ex1.setError("Cannot open information file");
				throw ex1;
			}
			while(!sourceFile.eof())
			{
				sourceFile.unsetf(ios::skipws);
				sourceFile>>ch;
				cout<<ch;
			}
			sourceFile.close();
			cout<<"\n\n\nPress any key to view graphical performance of test";
			getch();
			showGraph();
		}
		catch(myException ex)
		{
			cout<<ex.getError();
		}
		cout<<"\n\n\nThank you.";
	}
	void startTest()
	{
		system("cls");
		myException ex1;
		int userScore=0;
		char levelNumber[2];
		int meanScore,total,scoreTotal;
		char tempScore[4],tempTotal[4],tempDiff[4];
		int  cCounter=0;
		string destPath(path);
		destPath=destPath+"mean.txt";
		ifstream meanFile(destPath);
		meanFile.getline(tempScore,99,';');
		meanFile.getline(tempTotal,99,';');
		meanFile.getline(tempDiff,99,';');
		meanFile.close();
		scoreTotal=atoi(tempScore);
		total=atoi(tempTotal);
		int diffLevel;
		if(total==0)
			meanScore=0;
		else
			meanScore=scoreTotal/total;
		
		diffLevel=atoi(tempDiff);
		if(diffLevel==0)
			diffLevel++;
		else if(diffLevel>9)
			diffLevel--;

		int qCounter=0,i;
		char tempIndex[2],tempLevel[2];
		int aIndex,userIndex;
		
		int rCounter=0;
		ifstream sourceFile[10];
		string sourcePath(path);
		string tempPath(sourcePath);
		question currQue;
		sourcePath=sourcePath+"\questions\\level";

		for(int i=1;i<10;i++)
		{
			itoa(i,tempLevel,10);
			tempPath=sourcePath+tempLevel+".dat";
			try
			{
				sourceFile[i].open(tempPath,ios::binary);
				if(!sourceFile[i].is_open())
				{					
					ex1.setError("Cannot open question containing file");
					throw ex1;
				}
			}
			catch(myException ex)
			{
				cout<<ex.getError();
				return;
			}
		}
		cCounter=0;
		time_t startTime,endTime;
		const int duration=60*15;
		int elapseTime=0;
		time(&startTime);
		int diffCounter=0;
		while(qCounter<30)
		{
			diffCounter=diffCounter+diffLevel;
			gPoints[qCounter]=diffLevel;
			if(!sourceFile[diffLevel].good() || sourceFile[diffLevel].eof())
				sourceFile[diffLevel].seekg(0,ios::beg);
			sourceFile[diffLevel].read((char*)&currQue,sizeof(currQue));
			qCounter++;
			time(&endTime);
			elapseTime=difftime(endTime,startTime);
			if(elapseTime>=duration)
			{
				cout<<"\n\n\nYou have exceeded time limit.";
				Sleep(2000);
				cout<<"\n\n\nPress any key to view results...";
				getch();
				system("cls");
				showResult();
				break;
			}
			system("cls");
			cout<<"\nTime elapsed::"<<elapseTime/60<<" Minute(s)\t\t\tYou are answering question "<<qCounter<<".";
			cout<<"\n\t     "<<elapseTime%60<<" Second(s)";
			cout<<"\n\nQuestion::";
			cout<<"\n"<<currQue.qString;
			for(i=0;i<4;i++)
			{
				cout<<"\nOption-"<<i+1<<"::"<<currQue.optString[i];
			}
			cout<<"\n\nEnter correct answer Index::";
			tempIndex[0]=getche();
			userIndex=atoi(tempIndex);
			--userIndex;
			
			if(tempIndex[0]==27)
			{
				cout<<"\n\n\nPress 1 to exit test::";
				tempIndex[0]=getche();
				if(tempIndex[0]=='1')
				{
					cout<<"\n\n\nTest Complete.";
					system("cls");
					showResult();
					break;
				}
			}
			if(userIndex==currQue.aIndex)
			{
				//correct->upgrade level
				cCounter++;
				userScore=userScore+diffLevel;
				if(cCounter==2)		
				{
					if(diffLevel<9)
						diffLevel++;
					cCounter=0;
				}
			}
			else
			{
				//incorrect->degrade level
				if(diffLevel>1)
					diffLevel--;
				cCounter=0;
			}
			currQue.flushValues();
		}
		diffCounter=diffCounter/qCounter;
		char meanData[15];
		scoreTotal=scoreTotal+userScore;
		total++;
		itoa(scoreTotal,tempScore,10);
		itoa(total,tempTotal,10);
		itoa(diffCounter,tempDiff,10);
		strcpy(meanData,tempScore);
		strcat(meanData,";");
		strcat(meanData,tempTotal);
		strcat(meanData,";");
		strcat(meanData,tempDiff);
		strcat(meanData,";");

		destPath=path;
		destPath=destPath+"mean.txt";
		ofstream meanFile2(destPath);
		meanFile2.write(meanData,sizeof(meanData));
		meanFile2.close();

		score=userScore;
		proScore=userScore-meanScore;

		system("cls");
		cout<<"\n\n\nCongratulations!\nYou have completed the test";
		cout<<"\n\n\nPress any key to view results";
		getch();
		system("cls");
		showResult();
	}
	void testTakerHome()
	{
		system("cls");
		char ch;
		cout<<"\n\n\nWelcome test taker to Computer Aptitude Test System";
		cout<<"\nPlease read the following instruction::\n";
		string instrString(path);
		instrString=instrString+"instruction.txt";
		ifstream instrFile(instrString);
		while(instrFile.good())
		{
			instrFile.unsetf(ios::skipws);
			instrFile>>ch;
			cout<<ch;
			Sleep(50);	
		}
		instrFile.close();
		cout<<"\n\n\nPress any key once you have read all instructions";
		getch();
		system("cls");
		getPersonalData();
		cout<<"\n\n\nPress any key to continue";
		getch();
		startTest();
	}
	void showGraph()
	{
		int i,j;
		cout<<"\n\n\n\nGraphical Performance::\n";
		cout<<"\n\n";
		cout<<"    Difficulty Levels\n   ";
		for(i=0;i<10;i++)
		{
			cout<<i+1<<" ";
		}
		cout<<"\n   ";
		for(i=0;i<10;i++)
		{
			cout<<"- ";
		}
		for(j=0;j<30;j++)
		{
			cout<<"\n"<<j+1;
			if(j<9)
				cout<<" |";
			else
				cout<<"|";
			for(i=0;i<10;i++)
			{
				if(gPoints[j]==i)
					cout<<"* ";
				else
					cout<<"  ";
			}
		}
		getch();	
	}
};
class admin
{
	char uName[20],password[20];
public:
	void adminHome();
	void newAccount();
	void import();
	bool login();
	friend bool getPassword(string &);
};

void admin::adminHome()
{
	myException ex1;
	admin tempAdmin;
	char tempScore[5],tempTotal[5],tempLevel[5],temp;
	string destPath(path);
	string sourcePath(path);
	int scoreTotal,total,meanScore;
	destPath=destPath+"mean.txt";
	ifstream meanFile(destPath,ios::in);
	ifstream sourceFile;
	meanFile.getline(tempScore,99,';');
	meanFile.getline(tempTotal,99,';');
	meanFile.close();
	scoreTotal=atoi(tempScore);
	total=atoi(tempTotal);
	if(total==0)
		meanScore=0;
	else
		meanScore=scoreTotal/total;
	char ch=0;
	string tempPassword;
	question que;
	int qCounter=0;
	do
	{
		system("cls");
		cout<<"\n\n\nAdministrator Home";
		cout<<"\n\nPress";
		cout<<"\n1.Average score of test takers";
		cout<<"\n2.Total test takers";
		cout<<"\n3.Add question";
		cout<<"\n4.Add question from existing file";
		cout<<"\n5.View Questions";
		cout<<"\n6.Change password";
		cout<<"\n(0 to Logout)\n";
		ch=getche();
		switch(ch)
		{
		case '1':
			cout<<"\n\n\nAverage score of Test takers::"<<meanScore;
			getch();
			break;
		case '2':
			cout<<"\n\n\nTotal Test takers::"<<total;
			getch();
			break;
		case '3':
			que.newQuestion();
			getch();
			break;
		case '4':
			import();
			getch();
			break;
		case '5':
			cout<<"\n\nEnter level::";
			que.getLevel();
			itoa(que.level,tempLevel,10);
			sourcePath="";
			sourcePath=path+"\questions\\level"+tempLevel+".dat";
			try
			{
				sourceFile.open(sourcePath,ios::binary);
				if(!sourceFile.is_open())
				{
					ex1.setError("Cannot open question containing file");
					throw ex1;
				}			
				cout<<"\n\nPress 0 to exit\n(Press 1 for Previous question or 2 for Next question)\n";
				qCounter=0;
				while(sourceFile.good())
				{
					que.flushValues();
					sourceFile.read((char*)&que,sizeof(que));
					if(sourceFile.bad())
					{
						cout<<"\n\nEnd of File";
						temp=getche();
						break;
					}
					system("cls");
					cout<<"\n\n\nQuestion Number::"<<qCounter<<"\n";
					que.viewQuestion();
					temp=getch();
					if(temp=='0')
						break;
					if(temp=='1')
					{
						if(qCounter<=0)
						{
							cout<<"\n\nNote:You are on first question\n";
							getch();
						}
						else
						{
							qCounter--;
							sourceFile.seekg(qCounter*sizeof(que),ios::beg);
						}
					}					
					else if(temp=='2')
						qCounter++;
				}
			}
			catch(myException ex)
			{
				cout<<ex1.getError();
			}
			sourceFile.close();
			break;
		case '6':
			if(getPassword(tempPassword))
			{
				string userName;
				cout<<"\n\nEnter a user name::";
				cin>>userName;
				try
				{
					string filePath(path);
					int counter=0;
					admin tempObj;
					filePath=filePath+"login.dat";
					ofstream destFile(filePath,ios::binary | ios::trunc);
					if(!destFile.is_open())
					{
						ex1.setError("Cannot open login file");
						throw ex1;
					}
					
					strcpy(tempAdmin.password,tempPassword.c_str());
					strcpy(tempAdmin.uName,userName.c_str());
					destFile.write((char *)&tempAdmin,sizeof(tempAdmin));
					cout<<"\n\nPassword successfully changed";
				}
				catch(myException ex)
				{
					cout<<ex.getError();
				}
			}
			getch();
			break;
		case '0':
			cout<<"\n\n\nLogging out of system";
			break;
		default:
			cout<<"\n\n\nERR:Please enter appropriate choice.";
		}
	}
	while(ch!='0');
}
bool admin::login()
{
	admin tempAdmin;
	string uTemp,pTemp;
	string sourcePath(path);
	myException ex1;
	sourcePath=sourcePath+"login.dat";
	system("cls");
	try
	{
		ifstream adminFile(sourcePath,ios::binary | ios::in);
		if(!adminFile.is_open())
		{
			ex1.setError("Cannot Open Login.dat");
			throw ex1;
		}
		adminFile.read((char*)&tempAdmin,sizeof(tempAdmin));
		if(adminFile.good())
			adminFile.seekg(0,ios::beg);
		else
		{
			adminFile.close();
			newAccount();
			return false;
		}
		cout<<"\n\n\nUser Name::";
		cin>>uTemp;
		if(!getPassword(pTemp))
		{
			ex1.setError("Cannot login");
			throw ex1;
		}
		adminFile.read((char *)&tempAdmin,sizeof(tempAdmin));
		if(strcmp(uTemp.c_str(),tempAdmin.uName)==0 && strcmp(pTemp.c_str(),tempAdmin.password)==0)
		{
			adminFile.close();
			return true;
		}
		adminFile.close();
		return false;
	}
	catch(myException ex)
	{
		cout<<ex.getError();
		return false;
	}
}
void admin::newAccount()
{
	admin newAdmin;
	admin tempAdmin;
	myException ex1;
	string sourcePath(path);
	cout<<"\n\n\nNo administrator account available.";
	cout<<"\nPlease create a new account";
	cout<<"\n\nUsername::";
	cin>>newAdmin.uName;
	string password;
	try
	{
		if(!getPassword(password))
		{
			ex1.setError("Cannot create account");
			throw ex1;
		}
		strcpy(newAdmin.password,password.c_str());
		sourcePath=sourcePath+"login.dat";
		ofstream sourceFile(sourcePath, ios::binary |ios::out | ios::trunc);
		sourceFile.write((char *)&newAdmin,sizeof(newAdmin));
		sourceFile.close();
		cout<<"\n\n\nCongratulations! You have successfully created your account";
		cout<<"\nPress any key to login.";
		getch();
	}
	catch(myException ex)
	{
		cout<<ex.getError();
	}
}
void admin::import()
{
	char tempIndex[15];
	char tempLevel[15];
	char qString[100],optString[4][50];
	int level;
	myException ex1;
	question que;
	system("cls");
	char sourcePath[100];
	int qCount=0,i=0;
	char ch;
	
	bool flag=false;
	cout<<"\nEnter full path of the file along with file name\n(Press ; to end)::";
	cin.getline(sourcePath,99,';');
	for(int i=0;i<strlen(sourcePath);i++)
	{
		sourcePath[i]=sourcePath[i+1];
	}
	ifstream sourceFile(sourcePath);
	ofstream destFile[10];
	string destPath(path);
	string tempPath(sourcePath);
	destPath=destPath+"\questions\\level";
	for(int i=1;i<10;i++)
	{
		itoa(i,tempLevel,10);
		tempPath=destPath+tempLevel+".dat";
		try
		{
			destFile[i].open(tempPath,ios::binary|ios::app);
			if(!destFile[i].is_open())
			{
				ex1.setError("Cannot open question containing file");
				throw ex1;
			}
		}
		catch(myException ex)
		{
			cout<<ex.getError();
			return;
		}
	}
	try
	{	
		if(!sourceFile.is_open())
		{
			ex1.setError("Cannot open file");
			throw ex1;
		}
		while(sourceFile.good())
		{
			sourceFile.getline(tempLevel,1);
			sourceFile.getline(tempLevel,99,';');
			i=0;
			while(!isdigit(tempLevel[i]))
				i++;
			if(!isdigit(tempLevel[i]))
			{
				ex1.setError("Invalid format of file");
				throw ex1;
			}
			que.level=atoi(tempLevel);
			strcpy(tempIndex,"");
			sourceFile.getline(tempIndex,99,';');
			i=0;
			while(!isdigit(tempIndex[i]))
				i++;
			if(!isdigit(tempIndex[i]))
			{
				ex1.setError("Invalid format of file");
				throw ex1;
			}
			que.aIndex=atoi(tempIndex);
			--que.aIndex;
			if(que.aIndex<0 || que.aIndex>3)
			{
				ex1.setError("Invalid answer index");
				throw ex1;
			}
			sourceFile.getline(que.qString,99,';');
			for(int i=0;i<4;i++)
			{
				sourceFile.getline(que.optString[i],99,';');
			}
			if(flag==true)
			{
				destFile[que.level].write((char *)&que,sizeof(que));
				qCount++;
				continue;
			}
			que.viewQuestion();
			cout<<"\n\nPress 1 if you want to insert this question\n(Press 0 to exit or\n2 to insert all questions in this file or\n3 to skip this question)::";
			ch=getche();
			if(ch=='0')
				break;
			else if(ch=='3')
				continue;
			else if(ch=='2')
				flag=true;
			else if(ch=='1')
			{
				destFile[que.level].write((char *)&que,sizeof(que));
				qCount++;
			}
			
		}
	}
	catch(myException ex)
	{
		cout<<ex.getError();
	}
	sourceFile.close();
	for(int i=1;i<10;i++)
		destFile[i].close();
	cout<<"\nNumber of Question imported::"<<qCount;
	cout<<"\n\nPress any key to continue.";
}

bool getPassword(string & strPassword)
{
	int i=0;
	char ch='\0';
	cout<<"\nPassword::";
	do
	{
		ch=getch();
		if(ch==13)
			break;
		else if(ch==8)
		{
			i--;
			if(i>=0)
			{
				cout<<"\b \b";
				strPassword.pop_back();
			}
		}
		else
		{
			i++;
			cout<<"*";
			strPassword.push_back(ch);
		}
	}
	while(true);
	try
	{
		myException ex1;
		if(strPassword.empty())
		{
			ex1.setError("Password cannot be blank");
			throw ex1;
		}
		if(strPassword.length()<5)
		{
			ex1.setError("Length of password must be greater than or equal to 5");
			throw ex1;
		}
		for(int i=0;i<strPassword.length();i++)
		{
			if(iscntrl(strPassword.at(i))!=0)
			{
				ex1.setError("Password cannot contain control character");
				throw ex1;
			}
			if(ispunct(strPassword.at(i))!=0)
			{
				ex1.setError("Password cannot contain punctuation character");
				throw ex1;
			}
			if(isspace(strPassword.at(i))!=0)
			{
				ex1.setError("Password cannot contain space");
				throw ex1;
			}
		}
		return true;
	}
	catch(myException ex)
	{
		cout<<ex.getError();
	}
	return false;
}

void main()
{
	testTaker tObj;
	admin aObj;
	char choice='\0';
	do
	{
		cout<<"\n\n\n\tComputer Aptitude Test System";
		cout<<"\n\nPress\n1 for Administrator\n2 for Test taker\n(0 to exit)\n";
		choice=getche();
		switch(choice)
		{
		case '1':
			if(aObj.login())
				aObj.adminHome();
			else
			{
				cout<<"\nIncorrect username and/or password";
				getch();
			}
			break;
		case '2':
			tObj.testTakerHome();
			break;
		default:
			cout<<"\n\n\nERR:Please enter appropriate choice.";
			continue;
		}
	}
	while(choice!='0');
}
