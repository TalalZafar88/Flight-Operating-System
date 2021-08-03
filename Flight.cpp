#include<fstream>
#include<iostream>
#include<climits>
#include<sstream>
#include<windows.h>
#include<string>
using namespace std;

struct Node
{

	string city;
	int num;
	double hotel_price;
	Node* next;

};

struct Edge
{
	string start;
	string end;
	string airline;
	int price;
	int date;
	int month;
	int year;
	int takeoff;
	int landing;
	int time;
	bool flag;
	Edge* next;
};

struct Adjlist {
	Node* head;
};

struct Adjliste {

	Edge* head;

};

struct Date {
	string date;
	Adjliste* obj;

};

class Graph {

	Adjlist* list;
	Adjliste* liste;
	int ver;
	int current;
public:

	Graph(int n = 0) {

		ver = n;
		current = 0;
		list = new Adjlist[n];
		liste = new Adjliste[n];
		for (int i = 0; i < n; ++i) {

			list[i].head = new Node;
		}
		for (int i = 0; i < n; ++i) {

			liste[i].head = new Edge;
			liste[i].head->flag = false;
		}

	}

	void Createlist(string n, int price, int co) {
		list[current].head->city = n;
		list[current].head->num = co;
		list[current].head->hotel_price = price;
		list[current].head->next = NULL;
		liste[current].head->start = n;
		liste[current].head->flag = true;
		liste[current].head->next = NULL;

		current++;

	}

	void addedge(string s, string d, string airline, int price, int date,
		int month, int year, int take, int land) {

		Node* temp = new Node;
		Node* dest = new Node;
		Edge* temp1 = new Edge;
		Edge* dest1 = new Edge;
		dest->city = d;
		//dest->hotel_price = hotelprice;
		dest->next = NULL;
		dest1->airline = airline;
		dest1->start = s;
		dest1->date = date;
		dest1->month = month;
		dest1->year = year;
		if (take > 11) {
			take -= 12;
			dest1->takeoff = take;
		}
		else
			dest1->takeoff = take;

		if (land > 11) {
			land -= 12;
			dest1->landing = land;
		}
		else
			dest1->landing = land;

		dest1->price = price;
		dest1->end = d;
		dest1->time = abs(dest1->landing - dest1->takeoff);
		dest1->flag = false;
		dest1->next = NULL;
		bool check = false;
		for (int i = 0; i < ver; ++i) {

			if (list[i].head->city == s) {
				temp = list[i].head;
				temp->city = s;
				break;
			}

		}
		for (int i = 0; i < ver; ++i) {

			if (liste[i].head->start == s) {
				temp1 = liste[i].head;
				temp1->start = s;
				break;
			}

		}

		while (temp->next != NULL) {

			temp = temp->next;

		}

		temp->next = dest;

		while (temp1->next != NULL) {

			if (temp1->airline == dest1->airline && temp1->date == dest1->date
				&& temp1->price == dest1->price
				&& temp1->start == dest1->start && temp1->end == dest1->end)
				check = true;

			temp1 = temp1->next;

		}

		if (check == false)
			temp1->next = dest1;

	}

	void printlist() {

		for (int i = 0; i < ver; ++i) {

			Node* temp = list[i].head;
			cout << "Adjacency list for vertex " << temp->city << endl;

			while (temp != NULL) {

				if (temp->next != NULL)
					cout << temp->city << "->";

				else
					cout << temp->city << " ";

				temp = temp->next;

			}
			cout << endl;
			Edge* temp1 = liste[i].head;
			cout << "Adjacency list for Edges of " << temp1->start << endl
				<< endl;

			while (temp1 != NULL) {

				if (temp1->flag == false) {
					cout << temp1->airline << endl;
					cout << temp1->date << " " << temp1->month << " "
						<< temp1->year << endl;
					cout << temp1->takeoff << endl;
					cout << temp1->landing << endl;
					cout << temp1->price << endl;

				}
				temp1 = temp1->next;

			}

			cout << endl;

		}

	}

	int minDistance(int dist[], bool sptSet[]) {
		int min = INT_MAX, min_index;

		for (int v = 0; v < ver; v++)
			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], min_index = v;

		return min_index;
	}

	void printPath(int parent[], int j) {

		if (parent[j] == -1)
			return;

		printPath(parent, parent[j]);

		string a;
		for (int i = 0; i < ver; ++i) {

			Node* temp = list[i].head;
			if (temp->num == j) {
				a = temp->city;
				break;
			}

		}

		cout << "->" << a;
	}

	void dijkstra(int** graph, int src, int d)
	{
		int abzc = this->ver;

		int* dist = new int[abzc];

		bool* sptSet = new bool[abzc];

		int* parent = new int[abzc];

		for (int i = 0; i < ver; i++)
		{
			dist[i] = INT_MAX;
			sptSet[i] = false;
			parent[src] = -1;
		}

		dist[src] = 0;

		for (int count = 0; count < ver - 1; count++)
		{

			int u = minDistance(dist, sptSet);

			sptSet[u] = true;

			for (int v = 0; v < ver; v++) {

				if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
					&& dist[u] + graph[u][v] < dist[v])
				{
					parent[v] = u;
					dist[v] = dist[u] + graph[u][v];
				}

			}

		}
		printSolution(dist, ver, parent, src, d);
	}

	void printSolution(int dist[], int n, int parent[], int src, int d) {


		string a;
		bool flag = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (temp->num == src) {
				a = temp->city;

				break;
			}

		}

		cout << "Source" << "                 " << "              "
			<< "Route";

		cout << endl;

		for (int i = 0; i < ver; ++i) {

			Node* temp = list[i].head;

			if (d == temp->num) {

				if (dist[i] == INT_MAX) {
					flag = false;
					break;
				}
				cout << a << "->" << temp->city << "     " << dist[i]
					<< "          " << a;
				printPath(parent, i);
				cout << endl;
				flag = true;
			}

		}
		if (flag == false) {
			cout << endl;
			cout << endl;
			cout
				<< ">>>>>>>>>>>>>>>>>>SORRY NO AVAILABLE FLIGHT<<<<<<<<<<<<<<<<<<<<<<<<<<";

		}

	}



	void addedge1(Edge* curr, string s, string d, string airline, int price,
		int date, int month, int year, int take, int land, int time) {

		Edge* dest1 = new Edge;
		dest1->airline = airline;
		dest1->start = s;
		dest1->date = date;
		dest1->month = month;
		dest1->year = year;
		dest1->takeoff = take;
		dest1->landing = land;
		dest1->time = time;
		dest1->price = price;
		dest1->end = d;
		dest1->flag = false;
		dest1->next = NULL;

		curr->next = dest1;

	}
	void transit(string source, string dest, int date, string transit) {

		string midway;
		Edge* cur = new Edge;
		Edge* t = cur;
		Edge* temp1 = new Edge;
		for (int i = 0; i < ver; ++i) {

			Edge* temp = liste[i].head;
			if (temp->start == source) {
				temp1 = temp;
				break;
			}

		}


		while (temp1->next != NULL) {

			if (temp1->end == transit && temp1->date == date) {
				addedge1(cur, temp1->start, temp1->end, temp1->airline,
					temp1->price, temp1->date, temp1->month, temp1->year,
					temp1->takeoff, temp1->landing, temp1->time);
				cur = cur->next;

				midway = temp1->end;

			}

			temp1 = temp1->next;

		}

		Edge* temp2 = new Edge;

		for (int i = 0; i < ver; ++i) {

			Edge* temp = liste[i].head;
			if (temp->start == midway) {

				temp2 = temp;
				break;
			}

		}

		while (temp2 != NULL) {

			if (temp2->end == dest && temp2->date == date) {
				addedge1(cur, temp2->start, temp2->end, temp2->airline,
					temp2->price, temp2->date, temp1->month, temp1->year,
					temp2->takeoff, temp2->landing, temp2->time);
				cur = cur->next;

			}

			temp2 = temp2->next;

		}

		t = t->next;
		for (int i = 0; i < 1; ++i) {

			while (t != NULL) {
				cout << t->start << " ";
				cout << t->end << " ";
				cout << t->date << "/" << t->month << "/" << t->year << " ";
				cout << t->takeoff << ":00 ";
				cout << t->landing << ":00 ";
				cout << t->price << " ";
				cout << t->airline << " ";
				cout << endl;

				t = t->next;
			}

		}

	}

	void shortest(string s, string s1, int dt) {


		int size = ver;
		bool ck = false;
		int** price = new int* [size];
		for (int i = 0; i < size; ++i) {

			price[i] = new int[size];

		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				price[i][j] = 0;

			}
		}

		string** b = new string * [size];
		for (int i = 0; i < size; ++i) {

			b[i] = new string[size];
		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				Node* temp = list[j].head;

				if (j != size - 1)
					b[i][j] = temp->city;

				else
					b[i][j] = "Sydney";

			}

		}

		for (int i = 0; i < size - 1; ++i) {

			for (int j = 0; j < size; ++j) {
				Edge* temp1 = liste[i].head->next;

				if (i == j) {
					price[i][j] = 0;
				}

				else {

					while (temp1 != NULL) {

						if ((b[i][j] == temp1->end && temp1->date == dt)) {

							if (price[i][j] == 0) {
								price[i][j] = temp1->price;
								ck = true;
							}

							else if (price[i][j] > temp1->price)
								price[i][j] = temp1->price;

							temp1 = temp1->next;
						}

						else
							temp1 = temp1->next;
					}

					if (ck == false) {
						temp1 = liste[i].head->next;
						while (temp1 != NULL) {

							if ((b[i][j] == temp1->end && temp1->date == dt + 1)
								|| (b[i][j] == temp1->end
									&& temp1->date == dt - 1)) {

								if (price[i][j] == 0) {
									price[i][j] = temp1->price;

								}

								else if (price[i][j] > temp1->price)
									price[i][j] = temp1->price;

								temp1 = temp1->next;
							}

							else
								temp1 = temp1->next;

						}

					}

				}

			}

		}

		int num;
		bool check = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s == temp->city) {
				num = temp->num;
				check = true;
				break;
			}

		}
		int num2;
		bool check1 = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s1 == temp->city) {
				num2 = temp->num;
				check1 = true;
				break;
			}

		}

		if (check1 == false || check == false) {

			cout << "INVALID DATA" << endl;
			return;
		}

		dijkstra(price, num, num2);

	}

	void shortest1(string s, string s1) {

		int size = ver;
		bool ck = false;
		int** price = new int* [size];
		for (int i = 0; i < size; ++i) {

			price[i] = new int[size];

		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				price[i][j] = 0;

			}
		}

		string** b = new string * [size];
		for (int i = 0; i < size; ++i) {

			b[i] = new string[size];
		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				Node* temp = list[j].head;

				if (j != size - 1)
					b[i][j] = temp->city;

				else
					b[i][j] = "Sydney";

			}

		}

		for (int i = 0; i < size - 1; ++i) {

			for (int j = 0; j < size; ++j) {
				Edge* temp1 = liste[i].head->next;

				if (i == j) {
					price[i][j] = 0;
				}

				else {

					while (temp1 != NULL) {

						if (b[i][j] == temp1->end) {

							if (price[i][j] == 0) {
								price[i][j] = temp1->price;
								ck = true;
							}

							else if (price[i][j] > temp1->price)
								price[i][j] = temp1->price;

							temp1 = temp1->next;
						}

						else
							temp1 = temp1->next;
					}



				}

			}

		}

		int num;
		bool check = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s == temp->city) {
				num = temp->num;
				check = true;
				break;
			}

		}
		int num2;
		bool check1 = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s1 == temp->city) {
				num2 = temp->num;
				check1 = true;
				break;
			}

		}

		if (check1 == false || check == false) {

			cout << "INVALID DATA" << endl;
			return;
		}

		dijkstra(price, num, num2);

	}

	void Traveltime(string s, string s1, int dt) {

		int size = ver;
		bool ck = false;
		int** time = new int* [size];
		for (int i = 0; i < size; ++i) {

			time[i] = new int[size];

		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				time[i][j] = 0;

			}
		}

		string** b = new string * [size];
		for (int i = 0; i < size; ++i) {

			b[i] = new string[size];
		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				Node* temp = list[j].head;

				if (j != size - 1)
					b[i][j] = temp->city;

				else
					b[i][j] = "Sydney";

			}

		}

		int** diff = new int* [size];
		for (int i = 0; i < size; ++i) {

			diff[i] = new int[size];
		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				diff[i][j] = 0;

			}
		}
		/////////////////////////////////////


		for (int i = 0; i < size - 1; ++i) {

			for (int j = 0; j < size; ++j) {
				Edge* temp1 = liste[i].head->next;

				if (i == j) {
					diff[i][j] = 0;
				}

				else {

					while (temp1 != NULL) {

						if ((b[i][j] == temp1->end && temp1->date == dt)) {

							if (diff[i][j] == 0) {
								diff[i][j] = temp1->time;
								ck = true;
							}

							else if (diff[i][j] > temp1->time)
								diff[i][j] = temp1->time;

							temp1 = temp1->next;
						}

						else
							temp1 = temp1->next;
					}

					if (ck == false) {
						temp1 = liste[i].head->next;
						while (temp1 != NULL) {

							if ((b[i][j] == temp1->end && temp1->date == dt + 1)
								|| (b[i][j] == temp1->end
									&& temp1->date == dt - 1)) {

								if (diff[i][j] == 0) {
									diff[i][j] = temp1->time;

								}

								else if (diff[i][j] > temp1->time)
									diff[i][j] = temp1->time;

								temp1 = temp1->next;
							}

							else
								temp1 = temp1->next;

						}

					}

				}

			}

		}



		////////////////////////////////////





		int num;
		bool check = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s == temp->city) {
				num = temp->num;
				check = true;
				break;
			}

		}
		int num2;
		bool check1 = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s1 == temp->city) {
				num2 = temp->num;
				check1 = true;
				break;
			}

		}

		if (check1 == false || check == false) {

			cout << "INVALID DATA" << endl;
			return;
		}

		dijkstra(diff, num, num2);

	}

	void airline(string s, string s1, string airline, int dt) {

		int size = ver;
		int** price = new int* [size];
		for (int i = 0; i < size; ++i) {

			price[i] = new int[size];

		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				price[i][j] = 0;

			}
		}

		string** b = new string * [size];
		for (int i = 0; i < size; ++i) {

			b[i] = new string[size];
		}

		for (int i = 0; i < size; ++i) {

			for (int j = 0; j < size; ++j) {

				Node* temp = list[j].head;

				if (j != size - 1)
					b[i][j] = temp->city;

				else
					b[i][j] = "Sydney";

			}

		}

		for (int i = 0; i < size - 1; ++i) {

			for (int j = 0; j < size; ++j) {
				Edge* temp1 = liste[i].head->next;

				if (i == j) {
					price[i][j] = 0;
				}

				else {

					while (temp1 != NULL) {

						if ((b[i][j] == temp1->end && temp1->airline == airline
							&& temp1->date == dt)) {

							if (price[i][j] == 0) {
								price[i][j] = temp1->price;

							}

							else if (price[i][j] > temp1->price)
								price[i][j] = temp1->price;

							temp1 = temp1->next;
						}

						else
							temp1 = temp1->next;
					}

				}

			}

		}

		int num;
		bool check = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s == temp->city) {
				num = temp->num;
				check = true;
				break;
			}

		}
		int num2;
		bool check1 = false;
		for (int i = 0; i < ver; ++i) {
			Node* temp = list[i].head;
			if (s1 == temp->city) {
				num2 = temp->num;
				check1 = true;
				break;
			}

		}

		if (check1 == false || check == false) {

			cout << "INVALID DATA" << endl;
			return;
		}

		dijkstra(price, num, num2);

	}

	void direct(string source, string dest, int date) {
		Edge* cur = new Edge;
		Edge* t = cur;
		for (int i = 0; i < ver; ++i) {

			Edge* temp = liste[i].head->next;
			while (temp != NULL) {

				if (temp->start == source && temp->end == dest
					&& temp->date == date) {

					addedge1(cur, temp->start, temp->end, temp->airline,
						temp->price, temp->date, temp->month, temp->year,
						temp->takeoff, temp->landing, temp->time);
					cur = cur->next;

				}

				temp = temp->next;
			}

		}

		t = t->next;
		cout << "Direct Flights " << endl;
		while (t != NULL) {

			cout << t->start << " " << t->end << " " << t->date << "/"
				<< t->month << "/" << t->year << endl;

			t = t->next;

		}

	}

};


int main()
{

	int counter = 0;
	fstream f1;
	f1.open("HotelCharges_perday.txt");
	int co = 0;
	while (!f1.eof()) {
		string b;
		int p;

		f1 >> b;
		f1 >> p;
		counter++;

	}

	f1.close();
	cout << counter << endl;
	Graph a(counter + 1);


	//fstream f1;
	f1.open("HotelCharges_perday.txt");
	//int co = 0;
	co = 0;
	while (!f1.eof()) {
		string b;
		int p;

		f1 >> b;
		f1 >> p;
		a.Createlist(b, p, co);
		co++;

		p = 0;



	}
	a.Createlist("Sydney", 0, co);
	f1.close();

	ifstream f2;
	f2.open("Flights.txt");
	string b1;
	string b2;
	string b3;
	string b4;
	string b5;
	int b6;
	string b7;
	string temp;
	int x;
	int y;
	int z = 2019;
	int count = 1;
	int start;
	int end;
	while (!f2.eof()) {

		f2 >> b1;
		f2 >> b2;
		f2 >> b3;
		f2 >> b4;
		f2 >> b5;
		f2 >> b6;
		f2 >> b7;




		for (unsigned int i = 0; i < b3.length(); ++i) {

			if (b3[i] != '/' && b3[i] != ' ')
				temp += b3[i];

			else {
				if (count == 1) {
					stringstream uu(temp);
					uu >> x;

					temp = "";
				}
				else if (count == 2) {
					stringstream uu(temp);
					uu >> y;
					temp = "";
				}
				else {
					stringstream uu(temp);
					uu >> z;
					temp = "";
				}

				count++;
			}

		}

		temp = "";
		count = 1;

		for (unsigned int i = 0; i < b4.length(); ++i) {

			if (b4[i] != ':')
				temp += b4[i];

			else {

				stringstream az(temp);
				az >> start;
				break;
			}

		}

		temp = "";
		for (unsigned int i = 0; i < b5.length(); ++i) {

			if (b5[i] != ':')
				temp += b5[i];

			else {
				stringstream az(temp);
				az >> end;
				break;

			}

		}

		temp = "";


		a.addedge(b1, b2, b7, b6, x, y, z, start, end);

	}

	//a.printlist();



	string al;
	//cout << "Enter Airline ";
	//cin >> al;

	//a.shortest(city1, city2,dt); ye shortest path ke leye
	//  a.direct(city1,city2,dt);   ye direct flights ke leye hai
	// a.airline(city1,city2,al,dt);   //ye airline ki basis pe choti flight btati hai
	// a.transit(city1,city2,dt,transit);
	//a.Traveltime(city1,city2,dt);


	/////////////////////////////


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);



	cout << "                            WELCOME TO THE FLIGHT OPERATING SYSTEM  " << endl;

	cout << " The Available AirLines are :" << endl;
	cout << " (1) EMIRATES AIRWAYS" << endl << " (2) QATAR AIRWAYS" << endl << " (3) ANA AIRWAYS" << endl << endl;

	cout << " We Are Operationg Our Flight Operation In the following Cities for the current Ongoing Plan" << endl;


	cout << " (1) Islamabad " << endl << " (2) Newyork " << endl << " (3) Paris " << endl << " (4) Tokyo " << endl << " (5) London " << endl << " (6) Singapore " << endl;


	cout << " (7) Hongkong " << endl << " (8) Berlin " << endl << " (9) Seoul " << endl << " (10) Amsterdam " << endl << endl << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 78);
	cout << "We Hope that You Enjoy Out Services :') " << endl << endl;

	//int choice;
	int choice = 190;

	cout << "Please Pick an Option of the Following to Book Your Flight according to Your respective requirement " << endl << endl;
	cout << "Press 1 to Book a Flight of a certain Airline going to a certain destination on a specific date with minimal travel cost" << endl;
	cout << "Press 2 to Book a Flight going to a certain destination on a specific date with minimal travel time" << endl;
	cout << "Press 3 to Book a Flight going to a certain destination on a specific date with Preferred Airline" << endl;
	cout << "Press 4 to Book a Flight going to a certain destination on a specific date with a Transit Stay of Your own choice " << endl;
	cout << "Press 5 to Book a Flight going to a certain destination on a specific date with Direct Flight" << endl;
	cout << "Press 6 to Book a Flight going to a certain destination with minimal travel cost " << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << endl << endl;

	while (choice < 0 or choice>6)
	{
		cout << "Please Enter Your Valid Choice :') " << endl;
		cin >> choice;
	}



	string source;
	string destination;
	string airline;
	int day;
	int month;
	int year;
	string transit;
	if (choice == 1)
	{

		cout << "                 BOOKING " << endl;


		cout << "PLEASE ENTER YOUR SOURCE CITY" << endl;
		cin >> source;

		cout << "PLEASE ENTER YOUR DESTINATION CITY" << endl;
		cin >> destination;

		cout << "PLEASE ENTER DATE (day of the date)" << endl;
		cin >> day;

		cout << "PLEASE ENTER Month (month of the date)" << endl;
		cin >> month;

		cout << "PLEASE ENTER Year  (year of the date)" << endl;
		cin >> year;

		a.shortest(source, destination, day);
	}
	if (choice == 2)
	{
		cout << "                 BOOKING " << endl;


		cout << "PLEASE ENTER YOUR SOURCE CITY" << endl;
		cin >> source;

		cout << "PLEASE ENTER YOUR DESTINATION CITY" << endl;
		cin >> destination;

		cout << "PLEASE ENTER DATE (day of the date)" << endl;
		cin >> day;

		cout << "PLEASE ENTER Month (month of the date)" << endl;
		cin >> month;

		cout << "PLEASE ENTER Year (year of the date)" << endl;
		cin >> year;

		a.Traveltime(source, destination, day);


	}
	if (choice == 3)
	{
		cout << "                 BOOKING " << endl;


		cout << "PLEASE ENTER YOUR SOURCE CITY" << endl;
		cin >> source;

		cout << "PLEASE ENTER YOUR DESTINATION CITY" << endl;
		cin >> destination;

		cout << "PLEASE ENTER DATE (day of the date)" << endl;
		cin >> day;

		cout << "PLEASE ENTER Month (month of the date)" << endl;
		cin >> month;

		cout << "PLEASE ENTER Year (year of the date)" << endl;
		cin >> year;

		cout << "PLEASE ENTER Your Prefered airline" << endl;
		cin >> al;


		a.airline(source, destination, al, day);

	}
	if (choice == 4)
	{
		cout << "                 BOOKING " << endl;


		cout << "PLEASE ENTER YOUR SOURCE CITY" << endl;
		cin >> source;

		cout << "PLEASE ENTER YOUR DESTINATION CITY" << endl;
		cin >> destination;

		cout << "PLEASE ENTER DATE (day of the date)" << endl;
		cin >> day;

		cout << "PLEASE ENTER Month (month of the date)" << endl;
		cin >> month;

		cout << "PLEASE ENTER Year (year of the date)" << endl;
		cin >> year;

		cout << "PLEASE ENTER THE CITY FOR TRANSIT OF YOUR CHOICE " << endl;
		cin >> transit;

		a.transit(source, destination, day, transit);

	}
	if (choice == 5)
	{
		cout << "                 BOOKING " << endl;


		cout << "PLEASE ENTER YOUR SOURCE CITY" << endl;
		cin >> source;

		cout << "PLEASE ENTER YOUR DESTINATION CITY" << endl;
		cin >> destination;

		cout << "PLEASE ENTER DATE (day of the date)" << endl;
		cin >> day;

		cout << "PLEASE ENTER Month (month of the date)" << endl;
		cin >> month;

		cout << "PLEASE ENTER Year (year of the date)" << endl;
		cin >> year;
		a.direct(source, destination, day);

	}

	if (choice == 6)
	{
		cout << "                 BOOKING " << endl;


		cout << "PLEASE ENTER YOUR SOURCE CITY" << endl;
		cin >> source;

		cout << "PLEASE ENTER YOUR DESTINATION CITY" << endl;
		cin >> destination;


		a.shortest1(source, destination);

	}








}
