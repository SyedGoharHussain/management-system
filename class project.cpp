#include<iostream>
#include <fstream>

using namespace std;

const int MAX_RECORDS = 100;
  
class sweets
{
	private:
	    int record_count;
	    int sweet_id;
		string sweet_name, sweet_type;
		double sweet_price;
	public:
	    sweets() { record_count = 0; }
	    void add_record();
		void store_record();
		void view_record();
		void search_record(int temp_id);
		void update_record(int temp_id);
		void delete_rec(int temp_id);
		void buy_sweets();
		void admin_portal();
		void customer_portal();
	
};

int main()
{
    int choice;
    sweets sweet_obj;
	
	cout<<"\n\t\tWELCOME TO OUR SWEET SHOP\n";
    do
    {
        cout << "1. Owner\n2. Customer\n3. Exit\n";
        cout << "Enter your choice :\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            sweet_obj.admin_portal();
            break;
        case 2:
            sweet_obj.customer_portal();
            break;
        case 3:
            return 0;
        default:
            break;
        }

    } while (choice != 3);
    cout << "\n\n";

    return 0;
}

void sweets::add_record()
{
    int numRecords;
    cout << "Enter the number of records you want to add: ";
    cin >> numRecords;

    for (int i = 0; i < numRecords; ++i)
    {
        cout << "\nEnter the details of the sweet " << i + 1 << ":";
        cout << "Id : ";
        cin >> sweet_id;
        cout << "Name : ";
        cin >> sweet_name;
        cout << "Type : ";
        cin >> sweet_type;
        cout << "Price : ";
        cin >> sweet_price;
        store_record();
    }
}

void sweets::store_record()
{
    ofstream outfile;
    outfile.open("SweetInformation.txt", ios::app);
    if (record_count > 0)
        outfile << endl;  
    outfile << sweet_id << " " << sweet_name << " " << sweet_type << " " << sweet_price;
    record_count++;
    outfile.close();
}

void sweets :: view_record()
{
    ifstream infile;
    infile.open("SweetInformation.txt");

    if (!infile)
    {
        cerr << "Error opening file." << endl;
        return;
    }

    cout << "Id\tName\tType\tPrice" << endl;
    while (infile >> sweet_id >> sweet_name >> sweet_type >> sweet_price)
    {
        cout << sweet_id << "\t" << sweet_name << "\t" << sweet_type << "\t" << sweet_price << endl;
    }

    infile.close();
    cout << "\n\n";
}

void sweets :: search_record(int temp_id)
{
    bool found = false;
    ifstream infile;
    infile.open("SweetInformation.txt");
    while (infile >> sweet_id >> sweet_name >> sweet_type >> sweet_price)
    {
        if (sweet_id == temp_id)
        {
            cout << sweet_id << "\t" << sweet_name << "\t" << sweet_type << "\t" << sweet_price << endl;
            found = true;
            break;
        }
    }

    infile.close();

    if (!found)
    {
        cout << "Record not found!" << endl;
    }
}

void sweets :: update_record(int temp_id)
{
    bool found = false;

    ifstream infile;
    infile.open("SweetInformation.txt");

    ofstream outfile;
    outfile.open("temp.txt", ios::app);

    while (infile >> sweet_id >> sweet_name >> sweet_type >> sweet_price)
    {
        if (sweet_id == temp_id)
        {
            add_record();
            outfile << sweet_id << " " << sweet_name << " " << sweet_type << " " << sweet_price << endl;
            found = true;
        }
        else
        {
            outfile << sweet_id << " " << sweet_name << " " << sweet_type << " " << sweet_price << endl;
        }
    }

    infile.close();
    outfile.close();

    remove("SweetInformation.txt");
    rename("temp.txt", "SweetInformation.txt");

    if (!found)
    {
        cout << "Record not found!" << endl;
    }
    else
    {
        cout << "Sweet record updated successfully!" << endl;
    }
    cout << "\n\n";
}

void sweets::delete_rec(int temp_id)
{
    bool found = false;

    ifstream infile;
    infile.open("SweetInformation.txt");

    ofstream outfile;
    outfile.open("temp.txt");

    while (infile >> sweet_id >> sweet_name >> sweet_type >> sweet_price)
    {
        if (sweet_id == temp_id)
        {
            found = true;
            record_count--; // Decrease the record count when a record is deleted
        }
        else
        {
            outfile << sweet_id << " " << sweet_name << " " << sweet_type << " " << sweet_price << endl;
        }
    }

    infile.close();
    outfile.close();

    if (!found)
    {
        cout << "Record not found!" << endl;
    }
    else
    {
        remove("SweetInformation.txt");
        rename("temp.txt", "SweetInformation.txt");
        cout << "Sweet record deleted successfully!" << endl;
    }
    cout << "\n\n";
}


void sweets::buy_sweets()
{
    cout<<"\n--------------------------------------------------------\n";
    view_record();
    cout<<"\n--------------------------------------------------------\n";
    
    
	char buy_more;
    double total_cost = 0;
    do
    {
        int id, quantity;
        bool found = false;

        cout << "Enter the ID of the sweet you want to buy: ";
        cin >> id;

        ifstream infile("SweetInformation.txt");
        while (infile >> sweet_id >> sweet_name >> sweet_type >> sweet_price)
        {
            if (sweet_id == id)
            {
                found = true;
                break;
            }
        }
        infile.close();

        if (!found)
        {
            cout << "Sweet with ID " << id << " not found!" << endl;
            continue;
        }
		cout<<"\n--------------------------------------------------------\n";
        cout << "Enter the quantity of " << sweet_name << " you want to buy: ";
        cin >> quantity;
        double sweet_total_price = sweet_price * quantity;
		cout<<"\n--------------------------------------------------------\n";
        cout << "Total price for " << quantity << " " << sweet_name << "(s): $" << sweet_total_price << endl;

        total_cost = total_cost + sweet_total_price;
        cout<<"\n--------------------------------------------------------\n";
        cout << "Do you want to buy more sweets? (y/n): ";
        cin >> buy_more;
        
    } 
	while (buy_more == 'y' || buy_more == 'Y');
	cout<<"\n--------------------------------------------------------\n";
    cout << "Total cost for all sweets: $" << total_cost << endl;
    cout << "\n\n";
}


void sweets :: admin_portal()
{
    system("cls");
    int choice, temp;
    int temp_pass;
    cout << "Enter password : ";
    cin >> temp_pass;
    if (temp_pass == 123)
    {
        do
        {
            cout << "\n\nSelect an option!" << endl;
            cout << "1. Add Sweet" << endl;
            cout << "2. View Sweet" << endl;
            cout << "3. Search Sweet" << endl;
            cout << "4. Update Sweet" << endl;
            cout << "5. Delete Sweet" << endl;
            cout << "6. Exit" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
            	cout<<"\n--------------------------------------------------------\n";
                add_record();
                cout<<"\n--------------------------------------------------------\n";
                break;
            case 2:
            	cout<<"\n--------------------------------------------------------\n";
                view_record();
                cout<<"\n--------------------------------------------------------\n";
                break;
            case 3:
            	cout<<"\n--------------------------------------------------------\n";
                cout << "Enter sweet Id : ";
                cin >> temp;
                search_record(temp);
                cout<<"\n--------------------------------------------------------\n";
                break;
            case 4:
            	cout<<"\n--------------------------------------------------------\n";
                cout << "Enter sweet Id : ";
                cin >> temp;
                update_record(temp);
                cout<<"\n--------------------------------------------------------\n";
                break;
            case 5:
            	cout<<"\n--------------------------------------------------------\n";
                cout << "Enter sweet Id : ";
                cin >> temp;
                delete_rec(temp);
                cout<<"\n--------------------------------------------------------\n";
                break;
            case 6:
                return;
                break;
            default:
                cout << "Enter valid choice!" << endl;
                break;
            }
        } while (choice != 6);
    }
    else
    {
        cout << "Incorrect Password!" << endl;
    }
    cout << "\n\n";
}

void sweets :: customer_portal()
{
    system("cls");
    int choice, temp;
    do
    {
        cout << "Enter your choice :\n";
        cout << "1. View sweets\n2. Search Sweets\n3. Buy Sweets\n4. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        	cout<<"\n--------------------------------------------------------\n";
            view_record();
            cout<<"\n--------------------------------------------------------\n";
            break;
        case 2:
        	cout<<"\n--------------------------------------------------------\n";
            cout << "Enter sweet Id : ";
            cin >> temp;
            search_record(temp);
            cout<<"\n--------------------------------------------------------\n";
            break;
        case 3:
            buy_sweets();
            break;
        case 4:
            return;
            break;
        default:
            cout << "Enter valid choice!" << endl;
            break;
        }
    } while (choice != 4);
    cout << "\n\n";
}

