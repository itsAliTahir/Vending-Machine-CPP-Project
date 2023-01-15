#include <iostream>
#include <fstream>
using namespace std;
struct node{
	string name;
	int price;	
	node *next;
};
class list{
		node *head;
		node *tail;
	public:		
		list()
		{
			head = NULL;
			tail = NULL;
		}
	void insertion(string,int);
	void display();
	void purchase(int);
	void deleteitem();
	void history();
};
int main()
{
	char opt, opt2;
	int money, price;
	string name;
	list obj;
	obj.insertion("Pepsi",3);
	obj.insertion("Sprite",3);
	obj.insertion("Snacks",2);
	obj.insertion("Biscuits",2);
	obj.insertion("Chocolate",5);
	obj.insertion("Waffers",1);
	do
	{
		cout << "\n\t\tMenu\n";
		cout << "--------------------------------\n";
		cout << "User Mode\n";
		cout << " 1. Buy Items\n";
		cout << " 2. View Available Items\n\n";
		cout << "Admin Mode\n";
		cout << " 3. Add New Item\n";
		cout << " 4. Delete Existing Item\n";
		cout << " 5. View Purchased History\n";
		cout << " 6. Exit Program\n";
		cout << "--------------------------------\n\n";		
		cout << " Enter your option: ";
		cin >> opt;
		system("CLS");
		switch(opt)
		{
		 start:
			case '1':
				obj.display();
				cout << "Please enter Cash (in $): ";
				cin >> money;	
				obj.purchase(money);
				break;
			case '2':
				obj.display();
				break;				
			case '3':
				cout << "Enter Item Name: ";
				getline(cin>>ws,name);
				cout << "Enter Item Price: ";
				cin >> price;
				obj.insertion(name,price);
				break;
			case '4':
				obj.deleteitem();
				break;
			case '5':
				obj.history();
				break;
			case '6':				
				break;
			default:
				cout << "Incorrect Option";	
				break;
		}
		cout << endl;
		system("pause");
		system("CLS");
		
	}while(opt!='6');
}
void list::insertion(string str, int pri)
{
	node *temp = new node;
	temp->name = str;
	temp->price = pri;
	temp->next=NULL;
	if (head==NULL)
	{
		head = temp;
		tail = temp;
	}
	else
	{
		tail->next =temp;
		tail = temp;
	}
}
void list::display()
{
	node *temp;
	temp = head;
	int counter=0;
	cout << "Available Items\n\n";
	if (head == NULL)
	{
		cout << "No item to buy";
	}
	else
	{
		cout << "Item Name\t\t Price" <<endl;
		while (temp!=NULL)
		{			
			cout << ++counter << ". "<< temp -> name << "\t\t   " << temp->price << "\n";
			temp = temp->next;
		}
		cout << "\n\n";
	}
}

void list::purchase(int money)
{
	int option, quantity, re;
	reBuy:
	node *temp;
	temp = head;	
	cout << "What do you want to purchase: ";
	cin >> option;
	cout << "Enter Quantity: ";
	cin >> quantity;
	for(int i=1;i<option;i++)
	{
		temp = temp->next;
	}
	if (quantity*temp->price<=money)
	{
		cout << "You bought " << quantity << " x " << temp->name << "\t Price: " << quantity*temp->price << "$\n";
		ofstream myFile;
		myFile.open("PurchaseHistory.csv", std::ios::app);
		myFile <<"Item: " << temp->name << ",Price: " << temp->price << ",Quantity: " << quantity <<",Paid: " <<money <<",Returned: " <<money-(temp->price*quantity) <<", ";
		myFile.close();
		money = money-(temp->price*quantity);
		cout << "Remaining: " << money << "$\n\n";
		cout << "Want to Purchase Something else?\n";
		cout << "1. Yes\t 2. No\t : ";
		cin >> re;
		if (re==1)
		{
			system("CLS");
			display();
			goto reBuy;
		}
		else 
		{
			system("CLS");	
			cout << "Returned: " << money <<"$";
		}
	}
	else 
	{
		system("CLS");	
		cout << "Insufficent Amount\n";
		cout << "Returned: " << money <<"$";
	}
}

void list::deleteitem()
{
	string str;
	node *temp, *pre;
	temp = head;
	cout << "Enter Item Name to Delete: ";
	getline(cin >> ws, str);
	if (head == NULL)
	{
		cout << "No Item";
		return;
	}
	else if (head->name == str)
	{
		temp = head;
		head = head->next;
		delete temp;
		cout << "Deleted Successfully";
		return;
	}
	else
	{
		while (temp!=NULL)
		{
			if (temp->name == str && temp->next!= NULL)
			{
				pre->next=temp->next;
				delete temp;			
				cout << "Deleted Successfully";
				return;
			}
			if (temp->name == str && temp->next == NULL)
			{
				pre->next = NULL;
				tail = pre;
				tail->next = NULL;	
				delete temp;
				cout << "Deleted Successfully";
				return;
			}
			pre = temp;
			temp = temp -> next;
		}
	}
}
void list::history()
{
	string line;
	ifstream myFile;
	myFile.open("PurchaseHistory.csv");
	cout << " ";
	while (myFile.good())
	{
		getline(myFile, line, ',');	
		cout << line << "\t";
		getline(myFile, line, ',');
		cout << line << "\t";
		getline(myFile, line, ',');
		cout << line << "\t";							
		getline(myFile, line, ',');
		cout << line << "\t";
		getline(myFile, line, ',');
		cout << line << "\n";			
	}
	myFile.close();
}