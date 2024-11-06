#include<iostream>
#include<fstream>

using namespace std;

class Helper 
{

public:

	static int StringLength(char* str)
	{
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}

	static int StringLength(const char* str)
	{
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}

	static void StringCopy(char*& dest, const char*& src)
	{
		int len = StringLength(src);

		delete[] dest; //delete destination

		//create new dynamic space at destination according to the size of source with 1 additional space for null character
		dest = new char[len + 1];

		//deep copy src in dest
		for (int i = 0; i <= len; i++)
			dest[i] = src[i];

		//in the loop (i less than EQUAL TO l) automatically deep copies source till null character, so no need to write an extra statement for null character
	}

	static void StringCopy(char*& dest, char*& src)
	{
		int len = StringLength(src);

		delete[] dest; //delete destination

		//create new dynamic space at destination according to the size of source with 1 additional space for null character
		dest = new char[len + 1];

		//deep copy src in dest
		for (int i = 0; i <= len; i++)
			dest[i] = src[i];

		//in the loop (i less than EQUAL TO l) automatically deep copies source till null character, so no need to write an extra statement for null character
	}

	static char* GetStringFromBuffer(char* str)
	{
		int len = StringLength(str);
		//create new string dynamically:
		char* newstr = new char[len + 1];
		//copy str in new string:
		StringCopy(newstr, str);
		return newstr;
	}

	static char* GetStringFromBuffer(const char* str)
	{
		int len = StringLength(str);
		//create new string dynamically:
		char* newstr = new char[len + 1];
		//copy str in new string:
		StringCopy(newstr, str);
		return newstr;
	}
	
	static bool Compare(char* Str, char* StrToFind)
	{
		int strLen = StringLength(Str);
		int tofindLen = StringLength(StrToFind);

		//this loop iterates through the main string
		for (int i = 0; i <= strLen; i++)
		{
			//if any mismatch occurs:
			if (Str[i] != StrToFind[i])
				return false;
		}

		//if no mismatch occurs:
		return true;
	}

	static bool Compare(char* Str, const char* StrToFind)
	{
		int strLen = StringLength(Str);
		int tofindLen = StringLength(StrToFind);

		//this loop iterates through the main string
		for (int i = 0; i <= strLen; i++)
		{
			//if any mismatch occurs:
			if (Str[i] != StrToFind[i])
				return false;

		}

		//if no mismatch occurs:
		return true;
	}

	static char* IntToCharPtr(int num) //number is passed as parameter that is to be converted to character array
	{
		int copy = num; //copy of num is made so that when we perform operations on copy, num stays same.
		int size = 0; //size of character array to be formed

		//algo to calculate size of character array to be formed:
		while (num > 0)
		{
			size++;
			num = num / 10;
		}

		//dynamic allocation of character array of size found:
		char* newArr = new char[size + 1]; //size+1 to accomodate numm

		newArr[size] = '\0'; //null over the last index
		
		for (int i = size - 1; copy > 0; i--)
		{
			int remainder = copy % 10; //gives the right most digit
			newArr[i] = remainder + 48; //ASCII 48 added to covert to character
			copy = copy / 10; 
		}

		return newArr;
	}

	static char* StringConcatenate(const char* Cstring1, char*& Cstring2)
	{

		int l1 = StringLength(Cstring1);
		int l2 = StringLength(Cstring2);

		// Allocate memory for the concatenated string
		char* newArr = new char[l1 + l2 + 1];

		// Deep copy string1 to the beginning of newArr
		for (int i = 0; i < l1; i++)
		{
			newArr[i] = Cstring1[i];
		}

		//Deep copy string2 to the end of the newArr
		for (int i = 0; i < l2; i++)
		{
			newArr[l1 + i] = Cstring2[i];
		}

		// Write null character over the last element of newArr
		newArr[l1 + l2] = '\0';

		return newArr;

	}

	static char* CreateNewID(const char* code, int num)
	{
		char* newIDNumber = IntToCharPtr(num); //gives numerical part of new id to be formed

		//following concatinates code "c" for comment, or "post" for post to the above newIDNumber
		char* newID = StringConcatenate(code, newIDNumber); 
		
		return newID;
	}

	~Helper()
	{
		//empty as nothing new is formed
	}

	//functions in Helper class have been made static so that they can always be called without making an object of Heper class
};

class Date;
class Post;
class Object;
class Page;
class User;
class Comment;
class Memory;
class Activity;
class Facebook;

class Date
{

private:

	int day;
	int month;
	int year;

public:

	static Date systemDate; //common for all objects, thats why it is made static

	Date() //constructor
	{
		day = 0;
		month = 0;
		year = 0;
	}

	static void setSystemDate(int d, int m, int y) //setter
	{
		cout << "Command:                Set current System Date 15 11 2017\n";
		systemDate.day = d;
		systemDate.month = m;
		systemDate.year = y;
	}

	void ReadDateFromFile(ifstream& fin)
	{
		fin >> day;
		fin >> month;
		fin >> year;
	}

	//overloaded operator== to check if any date is of today or in 1 day's range:
	bool operator==(Date d) 
	{
		if (((day == d.day || day == (d.day - 1)) && (month == d.month) && (year == d.year)) || ((d.month == month - 1 && day - 1 == 0)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	static int differenceInYears(Date& d1, Date& d2)
	{
		int difference = d2.year - d1.year;
		return difference; 
	}

	bool CompareDayAndMonth()
	{
		bool flag = (day == systemDate.day && month == systemDate.month);
		//return true if day and month are same, otherwise false 
		return flag;
	}

	void PrintDate()
	{
		cout << "(" << day << "/" << month << "/" << year << ")";
	}

	~Date() //destructor
	{
		//empty as no new memory was allocated on heap
	}
	
};

//intialising static currentDate by explicitly calling default constructor:
Date Date::systemDate = Date();

class Object //parent class of user class and page class
{

private:

	char* ID; //could be of user or page

public:

	Object() //constructor
	{
		ID = 0;
	}

	//following three virtual functions are made to enable polymorphism of these functions with functions of page class and user class with same names

	virtual void addToTimeLine(Post* p) 
	{
		//pages and users have distinct timelines
	}

	virtual void PrintCurrent() 
	{
		//displays active user or page
	}

    virtual void PrintListView() 
	{
		//will print id, fname and lname for user, or id and title for page
	}

	void SetID(char* id) //setter
	{
		ID = Helper::GetStringFromBuffer(id);
	}

	char* GetID() //getter
	{
		return ID;
	}

	virtual ~Object() //destructor
	{
		if (ID) //to avoid null reference exception
		{
			delete[]ID;
		}
	}

};

class Activity
{

private:

	int type; //4 options
	char* value; //activity description

public:

	Activity() //constructor
	{
		value = 0; //text of activity
		type = 0; //4 options of activities are available
	}

	void ReadActivityFromFile(ifstream& fin)
	{
		char buffer[50];
		fin >> type; //4 activity options
		fin.getline(buffer, 50); //reads activity text
		value = Helper::GetStringFromBuffer(buffer);
	}

	void PrintActivity()
	{
		//options:
		if (type == 1)
			cout << " is feeling ";
		else if (type == 2)
			cout << " is thinking about ";
		else if (type == 3)
			cout << " is making ";
		else if (type == 4)
			cout << " is celebrating ";

		cout << value; //print text

	}

	~Activity() //destructor
	{
		if (value != 0) //to avoid null reference exception
		{
			delete[]value;
		}
	}

};

class Comment 
{

private:

	char* ID;
	char* text;
	Object* sharedBy; //aggregation as user or pages stay if comment is deleted, and one comment can be owned by one either a page or a user 

public:

	static int commentsCount;

	Comment() //constructor
	{
		text = 0;
		ID = 0;
		sharedBy = 0;
	}

	//overloaded constructor:
	Comment(const char* txt, Object* obj)
	{
		ID = Helper::CreateNewID("c",++commentsCount);
		text = Helper::GetStringFromBuffer(txt);
		sharedBy = obj;
	}

	void SetComment(char* id, char* txt, Object* obj) //setter
	{
		ID = Helper::GetStringFromBuffer(id);
		text = Helper::GetStringFromBuffer(txt);
		sharedBy = obj;
	}

	
	//getter:
	char* GetID()
	{
		return ID;
	}


	void PrintComment()
	{
		cout << "\n\t";
		sharedBy->PrintCurrent(); //prints current page's or user's title or name respectively
		cout << " wrote:" << text << ".\n";
	}

	~Comment() //destructor
	{
		if (ID) //shouldnt be null
		{
			delete[]ID;
		}
		if (text) //shouldnt be null
		{
			delete[]text; //shouldnt be null
		}
	}

};

//declaring static variable in gliobal scope:
int Comment::commentsCount = 0;

class Post 
{

private:

	char* ID;
	char* text;
	int type;  //1 for simple post, 2 for activity post
	Activity* activity; 
	Date postDate; //composition, as post class cannot be formed without this object of Date
	Object* sharedBy; //could be liked by either user or page 
	Object** likedBy; //could be liked by either user or page
	int likedByCount; 
	Comment** comments;
	int commentsCount; 

public:

	//made postsCount static as it is common for all objects of class Post
	static int postsCount;

	Post() //constructor
	{
		
		ID = 0;
		text = 0;
		type = 0;
		activity = 0;
		sharedBy = 0;
		likedBy = 0;
		likedByCount = 0;
		comments = 0;
		commentsCount = 0;
		
	}

	void ReadPostsFromFile(ifstream& fin) 
	{
		fin >> type;
		char buffer[100];
		fin >> buffer; 
		ID = Helper::GetStringFromBuffer(buffer);

		postDate.ReadDateFromFile(fin); //reads date of posting

		fin.getline(buffer, 100); 
		fin.getline(buffer, 100); //re written because there was an extra space in file
		text = Helper::GetStringFromBuffer(buffer);

		if (type == 2) // that means it is an activity type post
		{
			activity = new Activity; //object made on heap
			activity->ReadActivityFromFile(fin); //reading activity details
		}
	}

	void SharedBy(Object* obj) 
	{
		//post can be shared by either user or page
		sharedBy = obj; 
	}

	void addToLikedBy(Object* obj) 
	{
		if (obj) 
		{
			if (likedBy == 0) 
			{
				//make new objects list for the first time liking
				likedBy = new Object * [10];
			}
			if (likedByCount < 10)
			{
				likedBy[likedByCount] = obj; //add
				likedByCount++;
			}
		}
	}

	void AddComment(Comment* c) 
	{
		if (c != 0) // if c exists
		{
			if (comments == 0)
			{
				//make new objects list for the first time commenting
				comments = new Comment * [10];
			}
			if (commentsCount < 10)
			{
				comments[commentsCount] = c; //add
				commentsCount++;
			}
		}
	}

	virtual void PrintPost(bool dateCheck = true, bool commentCheck = true)
	{

		cout << "\n\n---";
		sharedBy->PrintCurrent();

		if (activity) //if post is of type activity, this variable will have one of 1 to 4 but not default value 0
		{
			activity->PrintActivity();
			cout << endl;
		}
		else //simple post (with no activity)
		{
			cout << " shared";
		}
		cout << " \"" << text << "\""; 
	
		if(dateCheck)
		{
			postDate.PrintDate();
		}

		//printing comments
		for (int i = 0; i < commentsCount; i++)
		{
			if(commentCheck) //to avoid null reference exception
			{
				comments[i]->PrintComment();
			}
		}

	}

	void PrintLikedByList() 
	{

		cout << "Command:				View Liked By List: (" << ID << ")\n";
		cout << "------------------------------------------------------------------------------------------------------------------------\n";

		if (likedBy ) //if there are any likes on posts (avoids null reference exception)
		{
			cout<< "\nPost Liked By : \n";

			for (int i = 0; i < likedByCount; i++)
			{
				likedBy[i]->PrintListView();
			}
		}
		else
		{
			cout << "\n Post has no likes.";
		}

		cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
	}

	Comment* GetLastComment() //getter
	{
		Comment* temp = comments[commentsCount - 1];
		return temp;
	}

	char* GetID() //getter
	{
		return ID;
	}

	Date& getDate() //getter
	{
		return postDate;
	}

	void SetValues(Object* obj, const char* txt) //setter
	{
		ID = Helper::CreateNewID("post", ++postsCount);
		sharedBy = obj;
		postDate = Date::systemDate;
		text = Helper::GetStringFromBuffer(txt);
	}

	Object* GetSharedBy() //getter
	{
		return sharedBy;
	}

	char* GetText() //getter
	{
		return text;
	}

	~Post() //destructor
	{

		//validity checks have been added to avoid null reference exception

		if (ID != 0)
		{
			delete[]ID;
		}

		if (text != 0)
		{
			delete[]text;
		}

		if (activity != 0)
		{
			delete activity;
		}

		if (likedBy != 0)
		{
			delete[]likedBy;
		}

		if (comments != 0)
		{
			//deletion of double pointer comments:
			for (int i = 0; i < commentsCount; i++) 
			{
				if (comments[i]) //to avoid null reference exception
				{
					delete comments[i];
				}
			}
			delete[]comments;
		}

	}
};

//declaring static variable in global scope:
int Post::postsCount = 0;

class Page : public Object //polymorphism with class object
{

private:
	
	char* title;
	Post** timeLine; 
	int timeLineCount;

public:

	Page() 
	{
		title = 0;
		timeLine = 0;
		timeLineCount = 0;
	}

	void ReadPagesFromFile(ifstream& fin) 
	{
		char temp[100];
		fin >> temp; //reads id
		SetID(temp);

		fin.getline(temp, 100); //getline is used to read everything after page ID, i.e. page title
		title = Helper::GetStringFromBuffer(temp);
	}

	void PrintCurrent() //polymorphism with class object
	{
		cout << title;
	}

	void PrintListView() //polymorphism with class object
	{
		cout << GetID() << " - " << title << endl;
	}

	void addToTimeLine(Post* p) 
	{
		if (p) //if post exists
		{
			if (timeLine == 0)
			{
				//create new in the first go
				timeLine = new Post * [10];
			}
			if (timeLineCount < 10)
			{
				timeLine[timeLineCount] = p; //add
				timeLineCount++;
			}
		}
	}

	int GetTimeLineCount() //getter
	{
		return timeLineCount;
	}

	void PrintLatest()
	{
		if (timeLine != 0) //to avoid null reference exception
		{
			for (int i = 0; i < timeLineCount; i++)
			{
				if (timeLine[i]->getDate() == Date::systemDate)
				{
					timeLine[i]->PrintPost(false);
				}
			}
		}
	}

	void PrintPage() 
	{

		cout << "\nCommand:				View Page(" << GetID() << "):";
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		cout << title << " - Timeline\n";

		if (timeLine != 0) 
		{
			for (int i = 0; i < timeLineCount; i++)
			{
				timeLine[i]->PrintPost();
			}
		}
	}

	~Page() //destructor
	{

		//validity checks have been added to avoid null reference exceptions

		if (title != 0)
		{
			delete[]title;
		}
		if (timeLine != 0)
		{
			//deletion of double pointer timeLine:
			for (int i = 0; i < timeLineCount; i++)
			{
				if (timeLine[i])
				{
					delete timeLine[i];
				}
			}
			delete[]timeLine;
		}
	}
};

class User : public Object 
{

private:

	char* FName;
	char* LName;
	User** friendList; 
	int friendsCount;
	Page** likedPages;
	int likedPagesCount;
	Post** timeLine; 
	int timeLineCount;
	
public:

	User() 
	{

		FName = 0;
		LName = 0;
		likedPages = 0;
		likedPagesCount = 0;
		friendList = 0;
		friendsCount = 0;
		timeLine = 0;
		timeLineCount = 0;
	
	}

	void ReadUsersFromFile(ifstream& fin)
	{
		char buffer[50];
		fin >> buffer;
		SetID(buffer); // sets user ID
		fin >> buffer; //reads user's First Name
		FName = Helper::GetStringFromBuffer(buffer);
		fin >> buffer; //reads user's Last Name
		LName = Helper::GetStringFromBuffer(buffer);
	}

	void addToLikedPages (Page* p) 
	{
		if (p) //if page exists
		{
			if (likedPagesCount == 0)
			{
				//create new on the first time
				likedPages = new Page * [10];
			}
			if (likedPagesCount < 10)
			{
				likedPages[likedPagesCount] = p; //add
				likedPagesCount++;
			}
		}
	}

	void addToFriendList(User* u) 
	{

		if (u) //user exists
		{
			if (friendsCount == 0)
			{
				//create new on the first go
				friendList = new User * [10];
			}
			if (friendsCount < 10)
			{
				friendList[friendsCount] = u; //friend has been added
				friendsCount++; 
			}
		} 
		
	}

	void PrintCurrent() //polymorphism with class object
	{
		cout << FName << " " << LName;
	}

	void PrintCurrentUser() //to be used while setting user
	{
		cout << FName << " " << LName << " successfully set as current user.";
	}

	void PrintListView() //polymorphism with class object
	{
		cout << GetID() << " - " << FName << " " << LName << endl;
	}

	void PrintLikedPages()
	{
		cout << "\nCommand:                View Liked Pages";
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << FName << " " << LName << " - Liked Pages \n\n";
		
		if (likedPages) //liked pages shouldnt be null, there has to atleast one liked page
		{
			for (int i = 0; i < likedPagesCount; i++)
			{
				likedPages[i]->PrintListView(); //printing
			}
		}
		else
		{
			cout << "\nNo pages are liked by this user\n";
		}
		
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
	}

	void PrintFriendList()
	{
		cout << "\n\nCommand:                View Friend List";
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << FName << " " << LName << " - Friends List \n\n";

		if (friendList) //friendList == 0 would mean there was no friend in the list
		{
			for (int i = 0; i < friendsCount; i++)
			{
				friendList[i]->PrintListView(); //printing
			}
		}
		else
		{
			cout << "\nThe user has no friends\n";
		}

		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
	
	}

	void PrintLatest()
	{
		if (timeLine != 0)
		{
			for (int i = 0; i < timeLineCount; i++)
			{
				if (timeLine[i]->getDate() == Date::systemDate)
				{
					timeLine[i]->PrintPost(false);
				}
			}
		}
	}

	void addToTimeLine(Post* p)
	{
		if (p) //if p exists
		{
			if (timeLine == 0)
			{
				//create new in the first go
				timeLine = new Post * [10];
			}
			if (timeLineCount < 10)
			{
				timeLine[timeLineCount] = p; //add
				timeLineCount++;
			}
		}
	}

	void PrintHome(Date d) 
	{

		cout << "\nCommand:				View Home\n";
		cout << "------------------------------------------------------------------------------------------------------------------------\n";
		cout << FName << " " << LName << " - Home Page:\n";

		if (friendList) //to avoid null reference exception
		{
			for (int i = 0; i < friendsCount; i++)
			{
						friendList[i]->PrintLatest();
			}
		}

		if (likedPages) //to avoid null reference exception
		{
			for (int i = 0; i < likedPagesCount; i++) 
			{
					likedPages[i]->PrintLatest();
			}
		}

		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	}

	void PrintTimeLine() //polymorphism with class object
	{

		cout << "\nCommand:				View Time Line:\n";
		cout << "------------------------------------------------------------------------------------------------------------------------\n";
		cout << FName << " " << LName << " - Home Page:\n";

		for (int i = 0; i < timeLineCount; i++) 
		{
			timeLine[i]->PrintPost();
		}

		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
	}

	void WriteComment(Post* p, const char* comment) 
	{
		cout << "\nCommand:				Post Comment(" << p->GetID() << ", \"" << comment << "\")";

		Comment* newComment = new Comment(comment, this);
		p->AddComment(newComment);

	}

	Post* FindOldestPost(int& n)
	{

		int max = 0, index = 0;

		for (int i = 0; i < timeLineCount; i++)
		{
			n = Date::differenceInYears(timeLine[i]->getDate(), Date::systemDate);
			
			if (max < n)
			{
				max = n;
				index = i;	
			}

		}

		n = max;

		if (timeLine[index]->getDate().CompareDayAndMonth())
		{
			return timeLine[index];
		}
		else
		{
			return 0;
		}

	}

	void PrintMemories()
	{
		cout << "\nCommand:				SeeYourMemories()";

		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << "\nWe hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n";
		int n = 0;
 
		for (int i = 0; i < timeLineCount; i++)
		{
			n = Date::differenceInYears(timeLine[i]->getDate(), Date::systemDate);
			if (timeLine[i]->getDate().CompareDayAndMonth() && n)
			{
				cout << "\nOn this day\n" << n << "years ago\n";
				timeLine[i]->PrintPost();
			}
		}

		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";

	}

	~User() //destructor
	{
		if (FName)
		{
			delete[]FName;
		}

		if (LName)
		{
			delete[]LName;
		}

		if (friendList)
		{
			delete[]friendList;
		}

		if (likedPages)
		{
			delete[]likedPages;
		}

		if (timeLine)
		{
			delete[]timeLine;
		}

		//validity checks have been added to avoid null reference exception

	}
};

class Memory : public Post //polymorphism with post class
{

private: 

	Post* mainPost;

public:

	Memory() //constructor
	{
		mainPost = 0;
	}

	//setter:
	void SetMemory(Post* p, const char* txt)
	{ 
		mainPost = p;
		//setter called:
		SetValues(p->GetSharedBy(), txt);
	}

	void PrintPost(bool dateCheck = true, bool commentCheck = true)
	{
		
		cout << "\n\n---";
		GetSharedBy()->PrintCurrent();
		cout << " shared a Memory~~~";
		getDate().PrintDate();
		cout << "\n \"" << GetText() << ".\"";
		mainPost->PrintPost(true,false);
	}

	~Memory() //destructor
	{
		//empty as no new memoryy was made
	}

};

class Facebook 
{

private: 

	Page** pages;
	int pagesCount;
	User** users;
	int usersCount;
	Post** posts;

public:

	Facebook() 
	{

		pages = 0;
		pagesCount = 0;
		users = 0;
        usersCount = 0;
		posts = 0;
		
	}
	
	Page* SearchPageByID(char* id) 
	{
		for (int i = 0; i < pagesCount; i++) 
		{
			//compare both ids:
			bool flag = Helper::Compare(pages[i]->GetID(), id);

			if (flag)
			{
				return pages[i];
			}
		}

		//return null if id doesnt match
		return 0;
	}

	Page* SearchPageByID(const char* id) 
	{
		
		for (int i = 0; i < pagesCount; i++)
		{
			//compare both ids
			bool flag = Helper::Compare(pages[i]->GetID(), id);
			if (flag)
			{
				return pages[i];
			}
		}

		//return null if id doesnt match
		return 0;
	}

	User* SearchUserByID(char* id) 
	{

		for (int i = 0; i < usersCount; i++) 
		{
			//compare both ids:
			bool flag = Helper::Compare(users[i]->GetID(), id);
			
			if (flag)
			{
				return users[i];
			}
		}

		//return null if id doesnt match
		return 0;

	}

	User* SearchUserByID(const char* id) 
	{
		for (int i = 0; i < usersCount; i++)
		{
			//compare both ids:
			bool flag = Helper::Compare(users[i]->GetID(), id);

			if (flag)
			{
				return users[i];
			}
		}

		//return null if id doesnt match
		return 0;
	}

	Post* SearchPostByID(const char* id) 
	{
		if (id)
		{
			for (int i = 0; i < Post::postsCount; i++)
			{
				//compare both ids:
				bool flag = Helper::Compare(posts[i]->GetID(), id);

				if (flag)
				{
					return posts[i];
				}

			}
		}

		//return null if id doesnt match
		return 0;
	}

	Object* SearchObjectByID(char* id)
	{
		if (id[0] == 'u')
		{
			//first element 'u' means object was of user
			User* temp;
			temp = SearchUserByID(id);
			return temp;
		}
		else
		{
			//first element 'p' means object was of page
			Page* temp;
			temp = SearchPageByID(id);
			return temp;
		}
	}


	void LoadPagesFromFile(const char* Filename)
	{
		ifstream fin;
		fin.open(Filename);
		fin >> pagesCount; 
		//create array for pages (pagesCount has been read from file)
		pages = new Page * [pagesCount];
		for (int i = 0; i < pagesCount; i++) 
		{
			//create objects of page at all indexes of pages
			pages[i] = new Page();
			pages[i]->ReadPagesFromFile(fin); //read
		}
		fin.close();
	}
	
	void LoadUsersFromFile(const char* FileName)
	{

		ifstream fin;
		fin.open(FileName);
		fin >> usersCount;

		//creates array for users (usersCount has been read from file)
		users = new User * [usersCount];

		char*** TempUserIDs;
		//triple pointer TempUserID will point towards the users, each of which will points to their 10 friends, which will point to their ids of type char
		TempUserIDs = new char** [usersCount];

		for (int i = 0; i < usersCount; i++)
		{
			//all users will point to 10 friends each
			TempUserIDs[i] = new char* [10];
			//array formed outside loop now needs tohae user objects ateach index:
			users[i] = new User;
			users[i]->ReadUsersFromFile(fin); //will read user id, first and last names
			
			char buffer[10];
			buffer[0] = ' '; //can be initialised with anything other than '-'

			int j = 0;
			while (buffer[0] != '-') //will iterate untill -1 
			{
				//read and store friend ids in designated space
				fin >> buffer; 
				TempUserIDs[i][j] = Helper::GetStringFromBuffer(buffer);
				j++;
			}

			TempUserIDs[i][j] = 0; //to be reused later
			buffer[0] = ' '; //re-initialise

			//liking pages:
			while (buffer[0] != '-') //will iterate until -1
			{
				fin >> buffer;
				Page* p = SearchPageByID(buffer);
				users[i]->addToLikedPages(p);
			}

		}

		//Adding friends:
		for (int i = 0; i < usersCount; i++)
		{
			int j = 0;
			while (TempUserIDs[i][j] != 0)
			{
				User* u = SearchUserByID(TempUserIDs[i][j]);
				users[i]->addToFriendList(u);
				//deletion of triple pointer begins here:
				delete[]TempUserIDs[i][j];
				j++;
			}
			//deletion:
			delete[] TempUserIDs[i];

		}

		//deletion:
		delete[] TempUserIDs;
	}

	void LoadPostsFromFile(const char* fileName) 
	{
		ifstream fin;
		fin.open(fileName);
		fin >> Post::postsCount;

		if (Post::postsCount != 0)
		{
			//create new list of posts
			posts = new Post * [Post::postsCount];
		}

		for(int i = 0; i < Post::postsCount; i++) 
		{
			//create objects of post at all indexes of pages
			posts[i] = new Post;
			posts[i]->ReadPostsFromFile(fin); //read
			
			char buffer[50];
			buffer[0] = ' '; //could be any character other than '-'

			fin >> buffer; 
			Object* obj;
			obj = SearchObjectByID(buffer); //will decide if user posted or page posted

			posts[i]->SharedBy(obj);
			obj->addToTimeLine(posts[i]); //add

			//following loop will iterate untill -1 is found
			while (buffer[0] != '-') 
			{
				fin >> buffer;
				obj = SearchObjectByID(buffer);
				posts[i]->addToLikedBy(obj); //add
			}
		}
	}

	void LoadCommentsFromFile(const char* FileName) 
	{
		ifstream fin;
		fin.open(FileName);
		
		fin >> Comment::commentsCount;

		Comment* comments;

		for (int i = 0; i < Comment::commentsCount; i++)
		{
			//create comment class objects at all indices of comments list
			comments = new Comment;
			
			char id[5];
			fin >> id;
			
			char buffer[50];
			fin >> buffer;
			
			char text[100];
			Post* temp = SearchPostByID(buffer);
			
			fin >> buffer;
			Object* obj = SearchObjectByID(buffer);
			fin.getline(text, 100);

			comments->SetComment(id, text, obj);
			temp->AddComment(comments);
		}
	}

	void ExpandPosts(Post* p)
	{
		Post::postsCount++;
		Post** latest; //declaration of new expanded list

		//new list of size+1 will be formed:
		latest = new Post * [Post::postsCount];
		for (int i = 0; i < Post::postsCount - 1; i++)
		{
			//copying all older posts:
			latest[i] = posts[i];
		}

		latest[Post::postsCount - 1] = p;
		//deleting previous posts list:
		delete[]posts;

		//pointing old posts list to latest list
		posts = latest;
	}

	void ShareMemory(Post* p, const char* txt)
	{
		Memory* m;
		m = new Memory;
		m->SetMemory(p, txt);
		//this memory will be a new post, so expact posts list
		ExpandPosts(m);
	}

	void LoadFacebook() //loads all the files
	{
		LoadPagesFromFile("SocialNetworkPages.txt"); //loads the pages file
		LoadUsersFromFile("SocialNetworkUsers.txt"); //loads the users file
		LoadPostsFromFile("SocialNetworkPosts.txt"); //loads the posts file
		LoadCommentsFromFile("SocialNetworkComments.txt"); //loads the comments file
	}

	void RunFacebook() //runs all the required functionalities
	{	
		//Printing System Date:
		Date::setSystemDate(15, 11, 2017);
		cout << "System Date: ";
		Date systemDate;
		Date::systemDate.PrintDate();
	
		//initialising re usable pointer for this function
		const char* required;

		required = "u7";
		cout << "\n\nCommand:				Set Current User \"" << required << "\""<< endl;
		User* activeUser = SearchUserByID(required); 

		if (activeUser != 0) //to avoid null reference exception
		{	
			activeUser->PrintCurrentUser(); 
			activeUser->PrintFriendList();
			activeUser->PrintLikedPages();
			activeUser->PrintHome(Date::systemDate);
			activeUser->PrintTimeLine();
			
			required = "post5";
			Post* requiredPost = SearchPostByID(required);
			requiredPost->PrintLikedByList();

			cout << "\nCommand:				Like Post(" << requiredPost->GetID() << ")\n";
			requiredPost->addToLikedBy(activeUser);
			requiredPost->PrintLikedByList();

			required = "post4";
			requiredPost = SearchPostByID(required);
			activeUser->WriteComment(requiredPost, "Good Luck for your Result");
			cout << "\nCommand:				View Post(" << requiredPost->GetID() << ")";
			cout << "\n---------------------------------------------------------------------------------------------------------------------\n";
			requiredPost->PrintPost();

			required = "post8";
			requiredPost = SearchPostByID(required);
			cout << "\n--------------------------------------------------------------------------------------------------------------------\n";
			activeUser->WriteComment(requiredPost, "Thanks for all the wishes." );
			cout << "\nCommand:				View Post(" << requiredPost->GetID() << ")";
			cout << "\n--------------------------------------------------------------------------------------------------------------------\n";
			requiredPost->PrintPost();
			cout << "\n--------------------------------------------------------------------------------------------------------------------\n";
			
			required = "post10";
			requiredPost = SearchPostByID(required);
			activeUser->PrintMemories();

			cout << "\nCommand:				Share Memory(" << requiredPost->GetID() << "), \"Never thought I will be Specialized in this field.\"";
			ShareMemory(requiredPost, "Never thought I will be Specialized in this field.");
			activeUser->addToTimeLine(posts[Post::postsCount - 1]);
			activeUser->PrintTimeLine();
			
			required = "p1";
			Page* reqPage = SearchPageByID(required);
			reqPage->PrintPage();

		}
		else
		{
			cout << "\nSORRY! User (" << required << ") does not exist";
		}

		required = "u11";
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:				Set Current User " << required << endl;
		activeUser = SearchUserByID(required);
		
		if (activeUser!= 0) //to avoid null reference exception 
		{
			activeUser->PrintCurrentUser();
			cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
			activeUser->PrintHome(Date::systemDate);
			activeUser->PrintTimeLine();
		}

	}

	~Facebook() //destructor
	{
		//validity checks have been added to avoid null reference  exception

		if (pages!= 0) 
		{
			//deletion of double pointer pages:
			for (int i = 0; i < pagesCount; i++)
			{
					if (pages[i])
					{
						delete pages[i];
					}
			}
			delete[]pages;
		}

		if (users != 0) 
		{
			//deletion of double pointer users:
			for (int i = 0; i < usersCount; i++)
			{
				if (users[i])
				{
					delete users[i];
				}
			}
			delete[]users;
		}

		if (posts != 0) 
		{
			delete[]posts;
		}

	}

};

int main() 
{

	Facebook fb; 
	fb.LoadFacebook(); //loads all the 4 files provided
	fb.RunFacebook(); //executes all required functionalities

	system("pause");
	return 0;

}