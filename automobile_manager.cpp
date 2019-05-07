#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <ctime>
#include <stdio.h>
using namespace std;
void delete_record_automobile()
{
  ifstream file;
  ofstream temp;
  string line;
  int i = 0, flag = 0;
  file.open("automobile.txt");
  temp.open("temp.txt");
  file.seekg(0, ios::beg);
  while (getline(file, line))
  {
    for (i = 0; i < line.length(); i++)
    {
      if (line[i] == '$')
        flag = 1;
    }
    if (flag == 1)
    {
      flag = 0;
      continue;
    }
    i = 0;
    while (line[i] != '$' && line[i] != '#')
    {
      temp << line[i];
      i++;
    }
    temp << '#';

    temp << endl;
  }
  file.close();
  temp.close();
  remove("automobile.txt");
  rename("temp.txt", "automobile.txt");
}
void delete_record_customer()
{
  ifstream file;
  ofstream temp;
  string line;
  int i = 0, flag = 0;
  file.open("customer.txt");
  temp.open("temp.txt");
  file.seekg(0, ios::beg);
  while (getline(file, line))
  {
    for (i = 0; i < line.length(); i++)
    {
      if (line[i] == '$')
        flag = 1;
    }
    if (flag == 1)
    {
      flag = 0;
      continue;
    }
    i = 0;
    while (line[i] != '$' && line[i] != '#')
    {
      temp << line[i];
      i++;
    }
    temp << '#';

    temp << endl;
  }
  file.close();
  temp.close();
  remove("customer.txt");
  rename("temp.txt", "customer.txt");
}
class Automobile
{
  char automobile_id[20];
  char automobile_name[20];
  char in_stock[20];
  char price[20], service_charge[20];
  char buffer[500];

public:
  void input();
  void output();
  string search(char key[], int mode);
  void modify(int stocks, int qntity, int mode, char key[]);
  void pack();
  void unpack();
  void Delete();
  void Write();
  friend string check(Automobile obj, char key[]);
  friend string auto_calculate(Automobile obj1, char key[]);
  friend string final_calculate(Automobile obj1, char key[]);
  friend void change_Stock(Automobile obj, int stocks, int qntity, char key[]);
};
class Customer
{
  char customer_id[20];
  char customer_name[20];
  char customer_address[25];
  string automobile_orders;
  char quantity[5];
  char automobile_id[20];
  char ordered_date[25];
  char buffer[500];

public:
  int input();
  void output();
  int search(char key[]);
  void modify(int mode);
  void pack();
  void unpack();
  void Delete();
  void Write();
  string check(Automobile ob, char key[])
  {
    return ob.search(key, 2);
  }
  string auto_calculate(Automobile obj1, char key[])
  {
    return obj1.search(key, 3);
  }
  friend void change_Stock(Automobile obj, int stocks, int qntity, char key[])
  {
    obj.modify(stocks, qntity, 2, key);
  }
  string final_calculate(Automobile obj1, char key[])
  {
    return obj1.search(key, 1);
  }
};
void Automobile::Delete()
{
  modify(0, 0, 1, NULL);
}

void Automobile ::input()
{

  cout << "Enter the Automobile ID:" << endl;
  cin >> automobile_id;
  cout << "Enter the Automobile Name:" << endl;
  fflush(stdin);
  gets(automobile_name);
  cout << "Enter Number of Automobile in Stocks:" << endl;
  cin >> in_stock;
  cout << "Enter the Price of the Automobile:" << endl;
  cin >> price;
  cout << "Enter the Service Charges:" << endl;
  cin >> service_charge;
}
void Automobile ::output()
{
  istream &flush();
  fstream file;
  string line;
  system("CLS");
  file.open("automobile.txt", ios::in);
  file.seekg(0, ios::beg);
  if (file.is_open())
  {
    while (getline(file, line))
    {

      for (int i = 0; i < line.length(); i++)
        buffer[i] = line[i];
      unpack();
      cout << "----------------------------------" << endl;
      cout << "Automobile ID:" << automobile_id << endl;
      cout << "Automobile Name:" << automobile_name << endl;
      cout << "In Stock:" << in_stock << endl;
      cout << "Price: " << price << " Rs" << endl;
      cout << "Service charge:" << service_charge << endl;
      cout << "----------------------------------" << endl;
    }
    file.close();
  }
  else
  {

    cout << "Error !! cant open file!!File doesn't exist!!" << endl;
  }
}
void Automobile::pack()
{

  strcpy(buffer, automobile_id);
  strcat(buffer, "|");
  strcat(buffer, automobile_name);
  strcat(buffer, "|");
  strcat(buffer, in_stock);
  strcat(buffer, "|");
  strcat(buffer, price);
  strcat(buffer, "|");
  strcat(buffer, service_charge);
  strcat(buffer, "|");

  strcat(buffer, "#");
}
void Automobile ::unpack()
{

  char *ptr = buffer;
  while (*ptr != '#')
  {
    if (*ptr == '|')
      *ptr = '\0';
    ptr++;
  }
  ptr = buffer;
  strcpy(automobile_id, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(automobile_name, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(in_stock, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(price, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(service_charge, ptr);
}
void Automobile ::Write()
{
  fstream os("automobile.txt", ios::out | ios::app);
  os.write(buffer, strlen(buffer));
  os << endl;
  os.close();
}
void Automobile ::modify(int stocks = 0, int qntity = 0, int mode = 0, char keys[] = NULL)
{

  fstream file;
  string line;
  char del = '$';
  file.open("automobile.txt", ios::in | ios::out);

  int found = 0, choice, len;
  char key[30];
  if (mode == 0 || mode == 1)
  {
    cout << "enter the automobile id: ";
    cin >> key;
  }
  else if (mode == 2)
  {
    strcpy(key, keys);
  }
  if (file.is_open())
  {
    while (!file.eof() && !found)
    {
      file.getline(buffer, '#');
      len = strlen(buffer);
      unpack();
      if (strcmp(automobile_id, key) == 0)
      {
        int pos = file.tellg();
        pos = pos - len - 2;
        file.seekg(pos, ios::beg);
        file << del;
        if (mode == 0)
        {
          cout << "1> Automobile Name " << endl;
          cout << "2> In Stocks " << endl;
          cout << "3> Price of Automobile " << endl;
          cout << "4> Service charge on Automobile " << endl;
          cout << "Enter What to Modify: ";
          cin >> choice;
          switch (choice)
          {
          case 1:
            cout << "Enter the new Automobile Name: ";
            fflush(stdin);
            gets(automobile_name);
            break;
          case 2:
            cout << "Enter the new Stocks: ";
            fflush(stdin);
            gets(in_stock);

            break;
          case 3:
            cout << "Enter the new Price: ";
            cin >> price;
            break;
          case 4:
            cout << "Enter the new Service Charges:";
            cin >> service_charge;
            break;
          default:
            cout << "Invalid input given";
          }
        }
        else if (mode == 2)
        {
          int val_in_stock = (stocks - qntity);
          ostringstream temp;
          temp << val_in_stock;
          std::string str = temp.str();
          char *vlue = const_cast<char *>(str.c_str());
          strcpy(in_stock, vlue);

          if (!val_in_stock)
          {
            strcpy(in_stock, "0");
          }

          cout << "instock : " << in_stock << endl;
        }
        else if (mode == 1)
        {
          cout << "Automobile Details Deleted !!!" << endl;
          automobile_id[0] = '$';
        }
        found = 1;
        pack();
        Write();
      }
    }
  }
  else
  {
    cout << "Error!can't open file !File doesn't exist !! " << endl;
    return;
  }
  if (!found)
    cout << "\n The Id does not exist !! TRY AGAIN !!" << endl;
  file.close();
  delete_record_automobile();
}
string Automobile ::search(char key[], int mode)
{
  istream &flush();
  fstream file;
  string line;
  int found = 0;

  file.open("automobile.txt", ios::in);
  if (file.is_open())
  {
    while (getline(file, line))
    {
      for (int i = 0; i < line.length(); i++)
        buffer[i] = line[i];
      unpack();
      if (strcmp(automobile_id, key) == 0)
      {
        if (mode == 0)
        {
          system("CLS");
          cout << "Automobile Present!!! " << endl;
          cout << "----------------------------------" << endl;
          cout << "Automobile ID:" << automobile_id << endl;
          cout << "Automobile Name:" << automobile_name << endl;
          cout << "In Stock:" << in_stock << endl;
          cout << "Price: " << price << " Rs" << endl;
          cout << "Service charge:" << service_charge << endl;
          cout << "----------------------------------" << endl;
          found = 1;
        }
        if (mode == 2)
        {
          return in_stock;
        }
        else if (mode == 1)
        {
          unsigned long int cost, charges, total;
          stringstream val1(price);
          stringstream val2(service_charge);
          val1 >> cost;
          val2 >> charges;
          total = cost + charges;
          stringstream ss;
          ss << total;
          string str = ss.str();

          return str;
        }
        else
        {
          return automobile_name;
        }
      }
    }
  }
  else
  {
    cout << "Error!Can't open file ! file doesn't exist !!" << endl;
  }
  if (!found)
  {
    cout << "Automobile  Details Not Present!!!" << endl;
    return "Details not present";
  }
  file.close();
  return 0;
}
/* :::::::::::::::::::::CUSTOMER CLASS METHODS ::::::::::::::::::::::::*/
void Customer::Delete()
{
  modify(1);
}
int Customer ::input()
{
  Automobile obj;
  string in_stock;
  int stocks, qntity;
  cout << "Enter Customer ID:" << endl;
  cin >> customer_id;
  cout << "Enter Customer Name:" << endl;
  cin >> customer_name;
  cout << "Enter Customer Address:" << endl;
  cin >> customer_address;
  cout << "Enter Automobile ID to Book: " << endl;
  cin >> automobile_id;
  cout << "Enter the quantity: " << endl;
  cin >> quantity;
  in_stock = check(obj, automobile_id);

  if (in_stock == "Details not present")
  {
    return 1;
  }
  stringstream val1(in_stock);
  stringstream val2(quantity);
  val1 >> stocks;
  val2 >> qntity;
  int i = 0;
  if (qntity > stocks)
  {
    cout << "Enough Stock not available, Available stock: " << in_stock << endl;
    return 1;
  }
  else
  {

    change_Stock(obj, stocks, qntity, automobile_id);
    time_t rawtime;
    struct tm *timeinfo;
    char time_stamp[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_stamp, sizeof(time_stamp), "%d-%m-%Y", timeinfo);
    string str(time_stamp);
    for (; i < sizeof(time_stamp); i++)
    {
      ordered_date[i] = time_stamp[i];
    }
    ordered_date[i] = '\0';
  }

  return 0;
}
void Customer ::output()
{
  istream &flush();
  fstream file;
  string line, final_cost;
  Automobile obj;
  unsigned long int total_cost = 0, qntity = 0;
  int i = 0;
  system("CLS");
  file.open("customer.txt", ios::in);
  if (file.is_open())
  {
    while (getline(file, line))
    {

      for (i = 0; i < line.length(); i++)
        buffer[i] = line[i];
      unpack();
      automobile_orders = auto_calculate(obj, automobile_id);
      final_cost = final_calculate(obj, automobile_id);
      if (final_cost != "\0")
      {
        stringstream val1(final_cost);
        stringstream val2(quantity);
        val1 >> total_cost;
        val2 >> qntity;
        total_cost = total_cost * qntity;
      }

      cout << "----------------------------------" << endl;
      cout << "Customer ID: " << customer_id << endl;
      cout << "Customer Name: " << customer_name << endl;
      cout << "Customer Address: " << customer_address << endl;
      cout << "Quantity: " << quantity << endl;
      cout << "Automobile booked: " << automobile_orders << endl;
      cout << "Ordered Date:" << ordered_date << endl;
      cout << "Total Cost: " << total_cost << " Rs" << endl;
      cout << "----------------------------------" << endl;
    }
  }
  else
  {
    cout << "Error! can't open file!File doesn't  exist !!" << endl;
  }
  file.close();
}
void Customer ::Write()
{
  fstream os("customer.txt", ios::out | ios::app);
  os.write(buffer, strlen(buffer));
  os << endl;
  os.close();
}
void Customer::pack()
{

  strcpy(buffer, customer_id);
  strcat(buffer, "|");
  strcat(buffer, customer_name);
  strcat(buffer, "|");
  strcat(buffer, customer_address);
  strcat(buffer, "|");
  strcat(buffer, automobile_id);
  strcat(buffer, "|");
  strcat(buffer, quantity);
  strcat(buffer, "|");
  strcat(buffer, ordered_date);
  strcat(buffer, "|");
  strcat(buffer, "#");
}
void Customer ::unpack()
{

  char *ptr = buffer;
  while (*ptr != '#')
  {
    if (*ptr == '|')
      *ptr = '\0';
    ptr++;
  }
  ptr = buffer;
  strcpy(customer_id, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(customer_name, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(customer_address, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(automobile_id, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(quantity, ptr);
  ptr = ptr + strlen(ptr) + 1;
  strcpy(ordered_date, ptr);
}
int Customer ::search(char key[])
{
  Automobile obj;
  string final_cost;
  unsigned long int total_cost, qntity;
  istream &flush();
  fstream file;
  string line;
  int found = 0;
  system("CLS");
  file.open("customer.txt", ios::in);
  if (file.is_open() && !found)
  {
    while (getline(file, line))
    {
      for (int i = 0; i < line.length(); i++)
        buffer[i] = line[i];
      unpack();
      automobile_orders = auto_calculate(obj, automobile_id);
      final_cost = final_calculate(obj, automobile_id);
      if (final_cost != "\0")
      {
        stringstream val1(final_cost);
        stringstream val2(quantity);
        val1 >> total_cost;
        val2 >> qntity;
        total_cost = total_cost * qntity;
      }

      if (strcmp(customer_id, key) == 0)
      {

        cout << "Customer Present!!! " << endl;
        cout << "----------------------------------" << endl;
        cout << "Customer ID:" << customer_id << endl;
        cout << "Customer Name:" << customer_name << endl;
        cout << "Customer Address:" << customer_address << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Automobile booked: " << automobile_orders << endl;
        cout << "Ordered Date:" << ordered_date << endl;
        cout << "Total Cost : " << total_cost << " Rs" << endl;
        cout << "----------------------------------" << endl;
        found = 1;
      }
    }
  }
  else
  {
    cout << "Can't open file! File doesn't exist !!!" << endl;
    return 0;
  }

  if (!found)
    cout << "Customer Details Not Present!!!" << endl;
  file.close();
  return 0;
}
void Customer ::modify(int mode = 0)
{
  Automobile obj;
  int stocks, qntity;
  fstream file;
  string line;
  string in_stock;
  int i = 0;
  istream &flush();
  char del = '$';
  char key[30];

  int found = 0, choice, len;
  cout << "Enter The Customer ID: " << endl;
  cin >> key;

  file.open("customer.txt", ios::in | ios ::out);
  file.seekg(0, ios::beg);
  if (file.is_open())
  {
    while (getline(file, line) && !found)
    {

      for (i = 0; i < line.length(); i++)
        buffer[i] = line[i];
      buffer[i] = '\0';
      len = strlen(buffer);
      unpack();

      if (strcmp(customer_id, key) == 0)
      {

        int pos = file.tellg();
        pos = pos - len - 1;
        file.seekg(pos, ios::beg);
        file << del;
        if (mode == 0)
        {
          cout << "1> Customer Name " << endl;
          cout << "2> Customer Address " << endl;
          cout << "3> Quantity of Automobile " << endl;
          cout << "4> Automobile ID " << endl;
          cout << "Enter What to Modify: ";
          cin >> choice;
          switch (choice)
          {
          case 1:
            cout << "Enter the Customer Name: ";
            fflush(stdin);
            gets(customer_name);
            break;
          case 2:
            cout << "Enter the customer Address: ";
            fflush(stdin);
            gets(customer_address);
            break;
          case 3:
            cout << "Enter the quantity of Automobile: ";
            cin >> quantity;
            in_stock = check(obj, automobile_id);

            if (in_stock == "Details not present")
            {
              file.close();
              return;
            }
            else
            {
              stringstream val1(in_stock);
              stringstream val2(quantity);
              val1 >> stocks;
              val2 >> qntity;
              if (qntity > stocks)
              {
                cout << "Enough Stock not available, Available stock: " << in_stock << endl;
                file.close();
                return;
              }
              else
              {

                change_Stock(obj, stocks, qntity, automobile_id);
              }
            }
            break;
          case 4:
            cout << "Enter the new Automobile ID:";
            cin >> automobile_id;
            in_stock = check(obj, automobile_id);
            if (in_stock == "Details not present")
            {
              file.close();
              return;
            }
            else
            {
              stringstream val1(in_stock);
              stringstream val2(quantity);
              val1 >> stocks;
              val2 >> qntity;
              if (qntity > stocks)
              {
                cout << "Enough Stock not available, Available stock: " << in_stock << endl;
                file.close();
                return;
              }
              else
              {

                change_Stock(obj, stocks, qntity, automobile_id);
              }
            }
            break;
          default:
            cout << "Invalid input given";
          }
        }
        else if (mode == 1)
        {
          cout << "Customer Deleted !!!" << endl;
          customer_id[0] = '$';
        }
        found = 1;
        pack();
        Write();
        break;
      }
    }
  }
  else
  {
    cout << "Error! Can't open file !File doesn't exist !!" << endl;
    return;
  }
  if (!found)
  {
    cout << "\n The Id does not exist !! TRY AGAIN !!" << endl;
    file.close();
    return;
  }
  file.close();
  delete_record_customer();
}
/*:::::::::::::::::::Automobile menu:::::::::::::::::::*/
void automobile_menu()
{
  int choice = 0;
  Automobile ob;
  system("CLS");
  while (choice < 6 && choice > 0)
  {
    char key[30];

    cout << "1> Insert an AutoMobile Info " << endl;
    cout << "2> Display all Automobile Info " << endl;
    cout << "3> Search for a Automobile: " << endl;
    cout << "4> Modify an Automobile Details: " << endl;
    cout << "5> Delete an Automobile Details" << endl;
    cout << "6> Back to Previous Section " << endl;
    cout << "Enter the Choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ob.input();
      ob.pack();
      ob.Write();
      break;
    case 2:

      ob.output();
      break;
    case 3:

      cout << "Enter The Automobile ID: " << endl;
      cin >> key;
      ob.search(key, 0);
      break;
    case 4:

      ob.modify();
      break;
    case 5:
      ob.Delete();
      break;
    }
  }
}
/*:::::::::::::::::::Customer menu:::::::::::::::::::*/
void customer_menu()
{
  char key[30];
  int choice = 0;
  int flag = 0;
  Customer custmer;
  system("CLS");
  while (choice < 6 && choice > 0)
  {
    cout << "1> Insert A Customer Info " << endl;
    cout << "2> Display all Customer Info " << endl;
    cout << "3> Search a Customer " << endl;
    cout << "4> Modify a Customer Details " << endl;
    cout << "5>Delete a Customer Details " << endl;
    cout << "6> Back to Previous Section " << endl;
    cout << "Enter the choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      flag = custmer.input();
      if (flag == 0)
      {
        custmer.pack();
        custmer.Write();
      }
      break;
    case 2:
      custmer.output();
      break;
    case 3:

      cout << "Enter The Customer ID: " << endl;
      cin >> key;
      custmer.search(key);
      break;
    case 4:
      custmer.modify();
      break;
    case 5:
      custmer.Delete();
      break;
    }
  }
}
main()
{
  int choice = 1;
  system("CLS");
  cout << "::::::::::::::::::::::::::::::::::AUTOMOBILE MANAGEMENT SYSTEM::::::::::::::::::::::::::::::::" << endl;
  while (choice < 3 && choice > 0)
  {
    cout << "1> Query Related to Automobile" << endl;
    cout << "2>Query Related to Customers" << endl;
    cout << "3>Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      automobile_menu();
      break;
    case 2:
      customer_menu();
      break;
    }
    system("CLS");
  }
  cout << "############## END of the Automobile Management System! Press any key to exit..... ############" << endl;
  getch();
  return 0;
}
