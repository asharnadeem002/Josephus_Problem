#include<iostream>
#include <SFML/Graphics.hpp>
#include<windows.h>
using namespace sf;
using namespace std;
                                                               
	template<class T>
	class Node {
	public:
		T data;
		Node *next;
	};

	template<class T>
	class Queue {									// linked list based Q
	private:
		Node<T> *root;
		int size;
		Node<T> *front;
		Node<T> *rear;

	public:
		Queue() {
			size = 0;
			root = new Node<T>;
			root->next = NULL;
			root->data = NULL;
			front = rear = root;
		}

		bool isEmpty() {
			if (size == 0)
				return true;
			else
				return false;
		}

		void eenque(T dt) {
			size = size + 1;
			if (front == root) {
				Node<T> *temp = new Node<T>;
				temp->data = dt;
				temp->next = NULL;
				root->next = temp;
				front = temp;
				rear = temp;

			}
			else if (size != 0 && front != root) {
				Node<T> *temp = new Node<T>;
				Node<T> *temp2 = root;
				for (int i = 1; i < size; i++)
					temp2 = temp2->next;
				temp->data = dt;
				temp->next = NULL;
				temp2->next = temp;
				rear = temp;

			}
			else {
				cout << "Error";
				size--;
			}
		}
		void deque() {
			if (!isEmpty()) {
				Node<T> *temp = root;
				temp->next = front->next;
				delete front;
				front = temp->next;
				size--;
			}
		}

		int sizee() {
			return size;
		}
		T frontt() {
			T dd;
			dd = front->data;
			return dd;

		}
		T rearr() {
			T dd;
			dd = rear->data;
			return dd;
		}
		int jose(int n, int k,int ded[],int start) {				// Josephus finding Function
			int s = n;
			int count = n;
			int flag = 0;
			int win = 0;
			int temp = 0;
			
			int j = 0;
			int skip = k;
			for (int i = 1; i < start; i++) {					//number of people to skip at Start
				eenque(frontt());
				deque();
			}
			while (count != 0) {
				for (int i = 0; i < k - 1; i++) {		//	Number of person who is not gonna be killed
					temp = frontt();
					eenque(temp);
					deque();
				}

				if (front->next == NULL) {					//Last person wins
					win = frontt();
					break;
				}
				ded[j] = frontt();						//Storing killed person in order
				j++;
				deque();								//remoivn killed person from queue
				count--;
			}
			return win;
		}
		~Queue() {
			cout << "Dest() called \n";					//Destructor
			while (size > 0) {
				delete root->next;
				size--;
			}
		}

	};

	int main() {

		Queue<int> list;
		
		int number, skip,start;
		cout << "Enter number of People : ";
		cin >> number;
		cout << "Enter skip number of people : ";
		cin >> skip;
		cout << "Enter starting number : ";
		cin >> start;
		int *ded=new int[number];

		for (int i = 1; i <= number; i++)					//enqueue from 1 to n
			list.eenque(i);
		
		cout << endl;
		int w = list.jose(number, skip,ded,start);			//Calling function

		for (int j = 0; j < number - 1; j++) {
			cout << ded[j] << " ";
		}

		int res = w;
		cout << "\nwinner = " << w << endl << endl;
		string ss = "The Last reamining  Is number :" + to_string(res);
		int k = 0,l=0;
		
//****************--SFML Window work--*******************************************


	sf::RenderWindow window(sf::VideoMode(1200, 650), "SFML works!");
	
	sf::Font text3d;
	if (!text3d.loadFromFile("fonts/3dfont.ttf")) {
		cout << "font load error" << endl;
		//return 0;
	}

	sf::Text d3d;
	string s = "The Last reamining  Is number :" + to_string(res);
	d3d.setFont(text3d);
	d3d.setCharacterSize(56);
	d3d.setFillColor(sf::Color::Black);
	d3d.setPosition(sf::Vector2f(450 , 200));
	
	
	d3d.setString(ss);

	sf::Texture texturbg;
	if (!texturbg.loadFromFile("backg.png")) {
		cout << "enemy load error" << endl;
		return 0;
	}

	sf::Sprite backgg;
	backgg.setTexture(texturbg);

	sf::Texture textur;
	if (!textur.loadFromFile("Enemy2.png")) {
		cout << "enemy load error"<<endl;
		return 0;
	}

	sf::Sprite enemy;
	enemy.setTexture(textur);
	enemy.scale(sf::Vector2f(0.3, 0.3));
	enemy.setPosition(sf::Vector2f(100 + k, 100 + l));

	sf::Texture texturd;

	if (!texturd.loadFromFile("Enemy2red.png")) {
		cout << "enemy load error" << endl;
		return 0;
	}

	sf::Sprite enemyd;
	enemyd.setTexture(texturd);
	enemyd.scale(sf::Vector2f(0.3, 0.3));
	enemyd.setPosition(sf::Vector2f(100 + k, 100 + l));
	
	int flag = 0;
	int counter = 1;
	
//-------------------------------------------------------------------------------
//**************** Display Sprites start  *****************************************

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(backgg);
		window.display();
	LL:
	
		k = l = 0;
		if (flag == 0) {
				
			for (int i = 0; i < number; i++) {							//Displays all the people first
				enemy.setPosition(sf::Vector2f(60 + k, 100 + l));
				k = k + 70;
				l = l + 40;
				d3d.setString(to_string(i + 1));
				d3d.setPosition(sf::Vector2f(80+k, 50+l));
				d3d.setFillColor(sf::Color::Black);
				window.draw(backgg);
				window.display();
				window.draw(d3d);
			
				window.draw(enemy);
				window.display();
				
				Sleep(250);
	
			}
			flag = 1;
		}
		else {
			for (int ii = 0; ii < number - 1; ii++) {				//Displays the killed person by order

				while (counter < ded[ii]) {							//iterate to display the killed person
					k = k + 70;
					l = l + 40;
					counter++;
				}
				window.draw(backgg);
				window.display();
				enemyd.setPosition(sf::Vector2f(60 + k, 100 + l));
				window.draw(enemyd);
				window.display();
				counter = 1;
				k = l = 0;
				Sleep(1200);


			}
			d3d.setPosition(sf::Vector2f(450, 200));
			d3d.setFillColor(sf::Color::Black);
			window.draw(backgg);
			window.display();
			d3d.setString(ss);
			window.draw(d3d);
			window.display();
			flag = 2;
		}
		
		Sleep(1000);
		if (flag != 2)
			goto  LL;
		else if (flag == 2) {					//Program ends
			
			while (window.isOpen()) {
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();

				}
			}
		}
	//}
			delete []ded;								//deleting dead array
	return 0;
}
