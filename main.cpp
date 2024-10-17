#include <iostream>
#include <string.h>
#include "My_own_string.h"

using namespace std;

//jesli zajdzie taka potrzeba to szybko zmieniamy typ danych gdzie przechowujemy koordynaty i wys, szer.
#define CORDSTP int

const int INF = 1000;

std::ostream& operator<<(std::ostream& ostr, const My_own_string& string)
{
	ostr << string.my_string;
	return ostr;
}

istream& operator>> (istream& in, My_own_string& string)
{

	char* buff = new char[1000];
	memset(&buff[0], 0, sizeof(buff));
	in >> buff;
	string = My_own_string{ buff };
	delete[] buff;
	return in;

}

template<typename T>
class List {
	struct Node {
		T val;
		Node* next;
		Node* prev;
	};

	Node* head;
	Node* tail;
	int size;

public:

	List() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void add(T _val) {

		if (head == nullptr) {
			head = new Node;

			if (head == nullptr)
				return;

			head->val = _val;
			head->prev = nullptr;
			head->next = nullptr;
			tail = head;
		}
		else {
			tail->next = new Node;
			tail->next->prev = tail;
			tail = tail->next;
			tail->next = nullptr;
			tail->val = _val;
		}

		size++;
	}

	void Delete(int index)
	{
		if (index >= size || index < 0)
		{
			return;
		}

		Node* curr = head;

		for (int i = 0; i < index; i++)
		{
			curr = curr->next;
		}

		if (curr->prev != nullptr) {
			curr->prev->next = curr->next;
		}
		if (curr->next != nullptr) {
			curr->next->prev = curr->prev;
		}

		if (index == 0)
		{
			head = curr->next;

			if (size == 1) {
				tail = nullptr;
			}
		}

		delete curr;
		size--;
	}


	T get(int index) {
		if (index < 0 || index >= size) {
			exit(1);
			return T();
		}

		Node* curr = head;

		for (int i = 0; i < index; i++) {
			curr = curr->next;
		}

		return curr->val;
	}

	T operator[](int index) {
		return get(index);
	}

	int getSize() {
		return size;
	}

	void clear() {
		for (int i = 0; i < getSize();) {
			Delete(i);
		}
	}
};

template <typename T>
class Queue {
	List<T> lista;

public:

	int getSize() {
		return lista.getSize();
	}

	void enqueue(T val) {
		lista.add(val);
	}

	T dequeue() {
		if (lista.getSize() > 0) {
			T to_ret = lista.get(0);
			lista.Delete(0);
			return to_ret;
		}
		return T();
	}
};

struct FlightCon {
	My_own_string city1;
	My_own_string city2;
	int time;
};

struct Request {
	My_own_string city1;
	My_own_string city2;
	int type;
};

class City {
	struct LinkNode {
		City* neighbour;
		int dist;
		bool oneway;
	};


	My_own_string name;
	int x, y;
	int counter_of_neigbors;

	My_own_string create_name_of_city(char** arr, int w, int h, int plusMinusY, int plusMinusX)
	{
		My_own_string city;
		char tmp_word[100];
		int offset = 0;
		int _x = x + plusMinusX, _y = y + plusMinusY;

		while (_x - 1 >= 0 && ((arr[_y][_x - 1] >= 'A' && arr[_y][_x - 1] <= 'Z') || (arr[_y][_x - 1] >= '0' && arr[_y][_x - 1] <= '9'))) {
			_x--;
		}

		do {
			tmp_word[offset] = arr[_y][_x];
			offset++;
			_x++;
		} while ((_x < w && arr[_y][_x] >= 'A' && arr[_y][_x] <= 'Z') || (arr[_y][_x] >= '0' && arr[_y][_x] <= '9'));

		tmp_word[offset] = '\0';

		city = tmp_word;

		return city;
	}

	void check_around_star(char** arr, int w, int h) //
	{
		if (x - 1 >= 0 && y + 1 < h && ((arr[y + 1][x - 1] >= 'A' && arr[y + 1][x - 1] <= 'Z') || (arr[y + 1][x - 1] >= '0' && arr[y + 1][x - 1] <= '9')))
		{
			name = create_name_of_city(arr, w, h, 1, -1); //goralewo
		}
		else if (y - 1 >= 0 && x - 1 >= 0 && ((arr[y - 1][x - 1] >= 'A' && arr[y - 1][x - 1] <= 'Z') || (arr[y - 1][x - 1] >= '0' && arr[y - 1][x - 1] <= '9')))
		{
			name = create_name_of_city(arr, w, h, -1, -1); //lewodol
		}
		else if (y - 1 >= 0 && ((arr[y - 1][x] >= 'A' && arr[y - 1][x] <= 'Z') || (arr[y - 1][x] >= '0' && arr[y - 1][x] <= '9'))) //dol
		{
			name = create_name_of_city(arr, w, h, -1, 0);
		}
		else if (y + 1 < h && ((arr[y + 1][x] >= 'A' && arr[y + 1][x] <= 'Z') || (arr[y + 1][x] >= '0' && arr[y + 1][x] <= '9')))
		{
			name = create_name_of_city(arr, w, h, 1, 0); //gora
		}
		else if (y + 1 < h && x + 1 < w && ((arr[y + 1][x + 1] >= 'A' && arr[y + 1][x + 1] <= 'Z') || (arr[y + 1][x + 1] >= '0' && arr[y + 1][x + 1] <= '9')))
		{
			name = create_name_of_city(arr, w, h, 1, 1); //goradol
		}
		else if (y - 1 >= 0 && x + 1 < w && ((arr[y - 1][x + 1] >= 'A' && arr[y - 1][x + 1] <= 'Z') || (arr[y - 1][x + 1] >= '0' && arr[y - 1][x + 1] <= '9')))
		{
			name = create_name_of_city(arr, w, h, -1, 1); //prawodol
		}
		else if (x + 1 < w && ((arr[y][x + 1] >= 'A' && arr[y][x + 1] <= 'Z') || (arr[y][x + 1] >= '0' && arr[y][x + 1] <= '9')))
		{
			name = create_name_of_city(arr, w, h, 0, 1); //praw
		}
		else if (x - 1 >= 0 && ((arr[y][x - 1] >= 'A' && arr[y][x - 1] <= 'Z') || (arr[y][x - 1] >= '0' && arr[y][x - 1] <= '9')))
		{
			name = create_name_of_city(arr, w, h, 0, -1); //lewo
		}



	}


public:
	List<LinkNode> neighbors;
	My_own_string getName() {
		return name;
	}

	City() {
		x = 0;
		y = 0;
		counter_of_neigbors = 0;
	}

	City* getCityFlights(List<City*>* cities, My_own_string string) {
		for (int i = 0; i < cities->getSize(); i++) {
			if (strcmp((*cities)[i]->getName().my_string, string.my_string) == 0) {
				return (*cities)[i];
			}
		}
		return nullptr;
	}

	City(int _x, int _y) : x(_x), y(_y), counter_of_neigbors(0) {}

	City(My_own_string _name) {
		name = _name;
		x = 0;
		y = 0;
	}

	int getNeiboursDistance(int index)
	{
		return neighbors.get(index).dist;
	}


	void addLink(City* _neighbour, int _dist, bool _oneway) {
		counter_of_neigbors++;
		LinkNode g_node;
		g_node.neighbour = _neighbour;
		g_node.dist = _dist;
		g_node.oneway = _oneway;
		neighbors.add(g_node);

	}

	City* get_neighbour(int i) {
		return neighbors[i].neighbour;
	}

	int getCounterNeigbors()
	{
		return counter_of_neigbors;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void setCityName(char** arr, int w, int h) {
		check_around_star(arr, w, h); //do uzupelnienia
	}

	bool isLinkOneWay(int index) {
		return neighbors[index].oneway;
	}
};

struct Point {
	int x;
	int y;
};

City* getCity(List<City*>* cities, int _x, int _y) {
	for (int i = 0; i < cities->getSize(); i++) {
		if ((*cities)[i]->getX() == _x && (*cities)[i]->getY() == _y) {
			return (*cities)[i];
		}
	}
	return nullptr;
}

int map(My_own_string& city_name, List<City*>* miasta) {
	for (int i = 0; i < (*miasta).getSize(); i++) {
		if (strcmp((*miasta)[i]->getName().my_string, city_name.my_string) == 0) {
			return i;
		}
	}
	return -1;
}

struct GraphNode {
	City* city;
	City* prev;
	int tentaive_dist;
	bool visited;
};

int getCityIndex(My_own_string cityName, List<City*> cities)
{
	short size = cities.getSize();
	for (int i = 0; i < size; i++)
	{
		if (strcmp(cities[i]->getName().my_string, cityName.my_string) == 0)
		{
			return i;
		}
	}
	return 0; //city was not found 
}

int find_shortest_path(City* start, City* dest, List <City*>& cities, List<City*>& shortest_path, Request* req, int iterate)
{
	int cities_count = cities.getSize();
	GraphNode* graph = new GraphNode[cities_count];

	if (strcmp(start->getName().my_string, dest->getName().my_string) == 0)
	{
		return 0;
	}

	auto getGraphIndex = [&](City* city) {
		return getCityIndex(city->getName(), cities);
	};

	auto findShortest = [&]() {
		int shortest_dist = INT_MAX;
		int ret_index = getCityIndex(dest->getName(), cities);

		for (int i = 0; i < cities_count; i++) {
			if (graph[i].visited == false && graph[i].tentaive_dist < shortest_dist) {
				shortest_dist = graph[i].tentaive_dist;
				ret_index = i;
			}
		}

		return ret_index;
	};

	auto allIncluded = [&]() {
		for (int i = 0; i < cities_count; i++) {
			if (graph[i].visited == false)
				return false;
		}
		return true;
	};

	//inicjujemy graf
	for (int i = 0; i < cities_count; i++) {
		graph[i].city = cities[i];

		if (graph[i].city == start)
			graph[i].tentaive_dist = 0;
		else
			graph[i].tentaive_dist = INT_MAX;

		graph[i].visited = false;
	}

	//--------------------Dijkstra------------------------------------
	while (!graph[getGraphIndex(dest)].visited) {
		City* curr = graph[findShortest()].city;
		int nei_count = curr->getCounterNeigbors();

		for (int i = 0; i < nei_count; i++) {
			City* nei = curr->get_neighbour(i);

			

			if (graph[getGraphIndex(nei)].visited == false && graph[getGraphIndex(curr)].tentaive_dist + curr->getNeiboursDistance(i) < graph[getGraphIndex(nei)].tentaive_dist) {
				graph[getGraphIndex(nei)].tentaive_dist = graph[getGraphIndex(curr)].tentaive_dist + curr->getNeiboursDistance(i);
				graph[getGraphIndex(nei)].prev = curr;
			}
		}

		graph[getGraphIndex(curr)].visited = true;
	}
	//--------------------Dijkstra_wykonany--------------------------

	if (graph[getGraphIndex(dest)].tentaive_dist == INT_MAX)
		return -1;

	City* curr = dest;
	shortest_path.clear();


	do {

		if (curr != dest)
			shortest_path.add(curr);
		curr = graph[getGraphIndex(curr)].prev;
		
	} while (curr != start);

	int distance = graph[getGraphIndex(dest)].tentaive_dist;
	delete[] graph;
	return distance;
}

struct Path {
	CORDSTP x;
	CORDSTP y;
	int dist;
};

void findNeighbours(City* city, List<City*>& cities, char** map, bool** visited_arr, CORDSTP h, CORDSTP w) {
	//funkcja implementuje algorytm BFS, zmodyfikowany na potrzeby zadania
	Queue<Path> kolejka;
	char next_char;
	Path curr;

	//ustawienie tablicy odwiedzin na false;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			visited_arr[i][j] = false;
		}
	}

	//lambda wykonujaca niezbedne sprawdzenia. Jesli trafi na # to dodaje do kolejki (realizujac algorytm),
	//jesli trafi na * to dodaje miasto do sasiadow miasta bazowego i nie dodaje do kolejki (zatrzymuje przeszukiwanie tej sciezki)
	auto addVert = [&](CORDSTP x, CORDSTP y) {
		if (x >= w || x < 0)
			return;

		if (y >= h || y < 0)
			return;

		if (visited_arr[y][x] == false) {
			next_char = map[y][x];
			visited_arr[y][x] = true;

			if (next_char == '#')
				kolejka.enqueue({ x, y, curr.dist + 1 });
			else if (next_char == '*') {
				//kolejka.enqueue({ x, y, curr.dist + 1 });
				city->addLink(getCity(&cities, x, y), curr.dist + 1, 0);
			}
		}
	};

	kolejka.enqueue({ city->getX(), city->getY(), 0 });
	visited_arr[city->getY()][city->getX()] = true;

	while (kolejka.getSize() != 0) {
		curr = kolejka.dequeue();

		addVert(curr.x + 1, curr.y);
		addVert(curr.x - 1, curr.y);
		addVert(curr.x, curr.y + 1);
		addVert(curr.x, curr.y - 1);
	}
}

int main()
{
	CORDSTP h, w;
	int l;
	int req;
	bool** visited_map = nullptr;

	short counter_of_cities = 0;
	cin >> w;
	cin >> h;

	char** tab = new char* [h];
	visited_map = new bool* [h];

	for (int i = 0; i < h; i++) {
		tab[i] = new char[w];
		visited_map[i] = new bool[w];
	}

	List<City*> cities;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> tab[i][j];
			if (tab[i][j] == '*')
			{
				cities.add(new City(j, i));
				counter_of_cities++;
			}
		}
	}

	for (int i = 0; i < cities.getSize(); i++) {
		cities[i]->setCityName(tab, w, h);
	}

	for (int i = 0; i < cities.getSize(); i++) {
		findNeighbours(cities[i], cities, tab, visited_map, h, w);
	}

	cin >> l;
	FlightCon* flights = new FlightCon[l];//Warszwa Gdansk 3

	if (l > 0)
	{
		for (int i = 0; i < l; i++) {
			cin >> flights[i].city1;
			cin >> flights[i].city2;
			cin >> flights[i].time;
		}
	}


	for (int i = 0; i < l; i++)
	{
		if (map(flights[i].city1, &cities) == -1 || map(flights[i].city2, &cities) == -1)
		{
			continue;
		}
		cities[map(flights[i].city1, &cities)]->addLink(cities[map(flights[i].city2, &cities)], flights[i].time, 1);
		//cities[map(flights[i].city2, &cities)]->addLink(cities[map(flights[i].city1, &cities)], -1, 0);
	}

	delete[] flights;
	cin >> req;

	if (req <= 0)
		return 1;

	Request* reqs = new Request[req];

	for (int i = 0; i < req; i++) {
		cin >> reqs[i].city1;
		cin >> reqs[i].city2;
		cin >> reqs[i].type;
	}

	List<City*> shortest_path;


	for (int i = 0; i < req; i++)
	{
		shortest_path.clear();
		City* start = cities[map(reqs[i].city1, &cities)];
		City* end = cities[map(reqs[i].city2, &cities)];
		int dist = find_shortest_path(start, end, cities, shortest_path, reqs, i);

		if (reqs[i].type == 1) 
		{
			cout << dist << " ";
			for (int j = 0; j < shortest_path.getSize(); j++) {
				
				cout << shortest_path[shortest_path.getSize() - j - 1]->getName() << " ";
			}
			cout << endl;
		}
		else {
			cout << dist << endl;
		}
		
	}

	for (int i = 0; i < h; i++) {
		delete[] tab[i];
		delete[] visited_map[i];
	}

	delete[] visited_map;
	delete[] tab;
	delete[] reqs;
}