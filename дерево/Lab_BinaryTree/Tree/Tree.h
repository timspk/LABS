#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <iomanip>

template <typename T>
class Tree {
private:
	Tree<T>* left;
	Tree<T>* right;
	Tree<T>* parent;
	T data;

	Tree<T>* build_balanced_bst(const std::vector<T>&, int, int, bool);
	void DrawElement(Tree<T>*, int, int, int, int, int, sf::RenderWindow&);

public:
	Tree();
	Tree(T);
	~Tree();

	T get_data();
	void replace(T);
	void delete_left();
	void delete_right();
	void insert_left(T);
	void insert_right(T);
	void view_direct();
	void view_symmetric();
	void view_reverse();
	void copy_list(std::list<T>&);
	void print_tree(int);
	void delete_tree();

	void insert(T);
	void erase(T);
	void set_left(Tree<T>*);
	void set_right(Tree<T>*);

	int getHeight();
	int countNodes();
	int obh(Tree<T>* node);
	void print_vert();

	void fillBlanks(int);

	Tree<T>* eject_left();
	Tree<T>* eject_right();
	Tree<T>* get_left();
	Tree<T>* get_right();
	Tree<T>* get_parent();
	Tree<T>* copy();
	Tree<T>* search_all(T);
	Tree<T>* search_sort(T);
	Tree<T>* next();
	Tree<T>* prev();
	Tree<T>* find_min();
	Tree<T>* find_max();
	Tree<T>* balanced(int);

	void in_order_traversal(std::vector<T>&);
	Tree<T>* create_bst_from_balanced_tree();
	void DrawT();
};

template <typename T>
Tree<T>::Tree() {
	left = right = parent = nullptr;
}

template <typename T>
Tree<T>::Tree(T data) {
	this->data = data;
	left = right = parent = nullptr;
}

template <typename T>
Tree<T>::~Tree() {
	delete this;
}


template <typename T>
T Tree<T>::get_data() {
	return data;
}

template <typename T>
void Tree<T>::replace(T data) {
	Tree<T>* search_tree = new Tree<T>();
	std::list<T> list1;
	this->copy_list(list1);
	for (auto data : list1) {
		search_tree->insert(data);
	}

	Tree<T>* current = search_tree->search_sort(data);
	if (current == nullptr) return;

	if (current->left == nullptr && current->right == nullptr) {
		current->data = -1;
		return;
	}

}

template <typename T>
void Tree<T>::delete_left() {
	if (left != NULL) {
		left->delete_left();
		left->delete_right();
		delete left;
	}
}

template <typename T>
void Tree<T>::delete_right() {
	if (right != NULL) {
		right->delete_left();
		right->delete_right();
		delete right;
	}
}

template <typename T>
void Tree<T>::insert_left(T data) {
	Tree<T>* new_node = new Tree(data);
	if (this->left != nullptr) {
		this->left->parent = new_node;
		new_node->left = this->left;
	}
	this->left = new_node;
	new_node->parent = this;
}

template <typename T>
void Tree<T>::insert_right(T data) {
	Tree<T>* new_node = new Tree(data);
	if (this->right != nullptr) {
		this->right->parent = new_node;
		new_node->right = this->right;
	}
	this->right = new_node;
	new_node->parent = this;

}

template <typename T>
void Tree<T>::view_direct() {
	if (this == nullptr) {
		return;
	}
	else {
		std::cout << this->get_data() << ' ';
		this->get_left()->view_direct();
		this->get_right()->view_direct();
	}
}

template <typename T>
void Tree<T>::view_symmetric() {
	if (this != nullptr) {
		this->left->view_symmetric();
		std::cout << this->data << ' ';
		this->right->view_symmetric();
	}
}

template <typename T>
void Tree<T>::view_reverse() {
	if (this != nullptr) {
		this->left->view_reverse();
		this->right->view_reverse();
		std::cout << this->data << ' ';
	}
}

template <typename T>
void Tree<T>::copy_list(std::list<T>& list1) {
	if (this == nullptr) {
		return;
	}
	else {
		list1.push_back(this->get_data());
		this->get_left()->view_direct();
		this->get_right()->view_direct();
	}
}

template <typename T>
void Tree<T>::print_tree(int level) {
	if (this != NULL) {
		this->left->print_tree(level + 1);
		for (int i = 1; i < level; i++) std::cout << "	";
		std::cout << this->get_data() << std::endl;
		this->right->print_tree(level + 1);
	}
}

template <typename T>
void Tree<T>::delete_tree() {
	this->delete_left();
	this->delete_right();
	delete this;
}

template <typename T>
void Tree<T>::insert(T data) {
	Tree<T>* current = this;
	while (current != nullptr) {
		if (data > current->data) {
			if (current->right != nullptr) {
				current = current->right;
			}
			else {
				current->insert_right(data);
				return;
			}
		}
		else if (data < current->data) {
			if (current->left != nullptr) {
				current = current->left;
			}
			else {
				current->insert_left(data);
				return;
			}
		}
		else return;
	}
}

template <typename T>
void Tree<T>::erase(T data) {
	Tree<T>* to_erase = this->search_sort(data);
	Tree<T>* te_parent = to_erase->parent;
	if (to_erase->left == nullptr && to_erase->right == nullptr) {
		if (te_parent->left == to_erase) {
			te_parent->left == nullptr;
		}
		else {
			te_parent->right == nullptr;
		}
		delete to_erase;
	}
	else if (to_erase->left == nullptr && to_erase->right != nullptr) {
		if (te_parent->left == to_erase) {
			te_parent->left == to_erase->right;
		}
		else {
			te_parent->right == to_erase->right;
		}
		to_erase->right->parent = te_parent;
		delete to_erase;
	}
	else if (to_erase->left != nullptr && to_erase->right == nullptr) {
		if (te_parent->left == to_erase) {
			te_parent->left == to_erase->left;
		}
		else {
			te_parent->right == to_erase->left;
		}
		to_erase->left->parent = te_parent;
		delete to_erase;
	}
	else {
		Tree<T>* next = to_erase->next();
		to_erase->data = next->data;
		if (next == next->parent->left) {
			next->parent->left = next->right;
			if (next->right != nullptr) {
				next->right->parent = next->parent;
			}
		}
		else {
			next->parent->right = next->right;
			if (next->right != nullptr) {
				next->right->parent = next->parent;
			}
		}
		delete next;
	}
}


template <typename T>
void Tree<T>::set_left(Tree<T>* tree) {
	left = tree;
}

template <typename T>
void Tree<T>::set_right(Tree<T>* tree) {
	right = tree;
}

template <typename T>
int Tree<T>::getHeight() {
	int h1 = 0, h2 = 0;
	if (this == NULL) return 0;
	if (this->left != NULL) h1 = this->left->getHeight();
	if (this->right != NULL) h2 = this->right->getHeight();
	if (h1 >= h2) return h1 + 1;
	else return h2 + 1;
}

template <typename T>
int Tree<T>::countNodes() {
	if (this == NULL) return 0;
	if ((this->left == nullptr) && (this->right == nullptr)) return 1;
	int l = 0;
	int r = 0;
	if (this->left != nullptr) l = this->left->countNodes();
	if (this->right != nullptr) r = this->right->countNodes();
	return l + r + 1;
}

template <typename T>
int Tree<T>::obh(Tree<T>* tree) {
	std::ofstream f("print.txt");

	int countNodes = tree->countNodes();
	std::queue<Tree<T>*> q;
	q.push(tree);
	while (!q.empty()) {
		Tree<T>* temp = q.front();
		q.pop();
		f << temp->data << std::endl;
		if (temp->left)
			q.push(temp->left);
		if (temp->right)
			q.push(temp->right);

	}
	f.close();
	return countNodes;
}

template <typename T>
void Tree<T>::fillBlanks(int i) {
	if (i == 1) {
		return;
	}
	if (!this->right) {
		this->insert_right(-1);
	}
	if (!this->left) {
		this->insert_left(-1);
	}
	this->right->fillBlanks(i - 1);
	this->left->fillBlanks(i - 1);
}

template <typename T>
void Tree<T>::print_vert() {

	Tree<T>* tree = this->copy();
	int height = tree->getHeight();
	tree->fillBlanks(height);
	int amount = obh(tree);
	std::ifstream f("print.txt");
	T* mas = new T[amount];
	for (int i = 0; i < amount; i++) {
		char str[255];
		f.getline(str, 255);
		mas[i] = atoi(str);
	}
	f.close();
	int count = 0;
	int* spaces = new int[height];
	spaces[0] = 0;
	for (int i = 1; i < height; i++) {
		spaces[i] = spaces[i - 1] * 2 + 1;
	}
	if (height == 1) {
		std::cout << std::setw(5) << mas[0] << std::endl;
	}
	else
	{
		for (int i = 0, l = height - 1; i < height - 1; i++, l--) {
			for (int j = 0, k = 0; j < pow(2, i); j++, k++) {
				if (k == 0) {
					for (int u = 0; u < spaces[l]; u++) {
						std::cout << std::setw(5) << ' ';
					}
				}
				else {
					for (int u = 0; u < spaces[l + 1]; u++) {
						std::cout << std::setw(5) << ' ';
					}
				}
				if (mas[count] != -1)
					std::cout << std::setw(5) << mas[count++];
				else
					std::cout << std::setw(5) << ' ';
			}
			std::cout << std::endl;
		}

		T* last_str = new T[pow(2, height - 1)];
		for (int i = 0; i < pow(2, height - 1); i++) {
			last_str[i] = 2000000000;
		}

		int sch1 = 0;
		int sch2 = spaces[height - 2] + 1;

		for (int i = count; i < amount; i += 2) {
			if (i <= amount - 1) {
				last_str[sch1] = mas[i];
				sch1 += 2;
			}
			if (i + 1 <= amount - 1) {
				last_str[sch2] = mas[i + 1];
				sch2 += 2;
			}
			if (sch1 >= pow(2, height - 1) || sch2 >= pow(2, height - 1)) {
				sch1 = 1;
				sch2 = spaces[height - 2] + 2;
			}
		}

		for (int i = 0; i < pow(2, height - 1); i++)
			if (last_str[i] != 2000000000) last_str[i] = mas[count++];

		for (int i = 0; i < pow(2, height - 1); i++)
			if (last_str[i] != 2000000000 && last_str[i] != -1) std::cout << std::setw(5) << last_str[i] << std::setw(5) << ' ';
			else std::cout << std::setw(5) << ' ' << std::setw(5) << ' ';

		std::cout << std::endl;
		delete[] last_str;
	}
	delete[]mas;
	delete[]spaces;
}

template <typename T>
Tree<T>* Tree<T>::eject_left() {
	Tree<T>* temp = left;
	left = nullptr;
	if (temp != nullptr) {
		temp->parent = nullptr;
	}
	return temp;
}

template <typename T>
Tree<T>* Tree<T>::eject_right() {
	Tree<T>* temp = right;
	right = nullptr;
	if (temp != nullptr) {
		temp->parent = nullptr;
	}
	return temp;
}

template <typename T>
Tree<T>* Tree<T>::get_left() {
	return left;
}

template <typename T>
Tree<T>* Tree<T>::get_right() {
	return right;
}

template <typename T>
Tree<T>* Tree<T>::get_parent() {
	return parent;
}

template <typename T>
Tree<T>* Tree<T>::copy() {
	Tree<T>* new_tree = new Tree<T>(data);
	if (left != nullptr) {
		new_tree->left = left->copy();
		new_tree->left->parent = new_tree;
	}
	if (right != nullptr) {
		new_tree->right = right->copy();
		new_tree->right->parent = new_tree;
	}
	return new_tree;
}

template <typename T>
Tree<T>* Tree<T>::search_all(T key) {
	if (data == key) {
		return this;
	}
	if (left != nullptr) {
		Tree<T>* result = left->search_all(key);
		if (result != nullptr) {
			return result;
		}
	}
	if (right != nullptr) {
		Tree<T>* result = right->search_all(key);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}

template <typename T>
Tree<T>* Tree<T>::search_sort(T data) {
	if (this == nullptr || this->data == data) {
		return this;
	}
	else if (data > this->data) {
		return this->right->search_sort(data);
	}
	else {
		return this->left->search_sort(data);
	}
}

template <typename T>
Tree<T>* Tree<T>::next() {
	Tree<T>* current = this;
	if (current->right != nullptr) {
		return current->right->find_min();
	}
	Tree<T>* temp = current->parent;
	while (temp != nullptr && current == temp->right) {
		current = temp;
		temp = current->parent;
	}
	return temp;
}

template <typename T>
Tree<T>* Tree<T>::prev() {
	if (left != nullptr) {
		Tree<T>* temp = left;
		while (temp->right != nullptr) {
			temp = temp->right;
		}
		return temp;
	}
	else {
		Tree<T>* temp = this;
		while (temp->parent != nullptr && temp->parent->left == temp) {
			temp = temp->parent;
		}
		return temp->parent;
	}
}

template <typename T>
Tree<T>* Tree<T>::find_min() {
	if (this->left == nullptr) {
		return this;
	}
	return this->left->find_min();
}

template <typename T>
Tree<T>* Tree<T>::find_max() {
	if (this->right == nullptr) {
		return this;
	}
	return this->right->find_max();
}

template <typename T>
Tree<T>* Tree<T>::balanced(int count) {
	if (count <= 0) {
		return nullptr;
	}
	T data;
	std::cout << "Enter value: ";
	std::cin >> data;
	Tree<T>* temp = new Tree<T>(data);
	temp->set_left(balanced(count / 2));
	temp->set_right(balanced(count - count / 2 - 1));
	return temp;
}

template <typename T>
Tree<T>* Tree<T>::build_balanced_bst(const std::vector<T>& vect, int start, int end, bool prevMidR) {
	if (start > end) {
		return nullptr;
	}

	int mid = start + (end - start) / 2;
	if (prevMidR && (mid + (end - start) % 2 <= end)) mid += (end - start) % 2;
	//if (prevMidR) std::cout << "L " << vect[mid] << std::endl;
	//else std::cout << "R " << vect[mid] << std::endl;
	Tree<T>* new_node = new Tree<T>(vect[mid]);
	new_node->left = build_balanced_bst(vect, start, mid - 1, true);
	new_node->right = build_balanced_bst(vect, mid + 1, end, false);

	return new_node;
}

template <typename T>
void Tree<T>::in_order_traversal(std::vector<T>& vect) {
	if (left != nullptr) {
		left->in_order_traversal(vect);
	}

	vect.push_back(data);
	if (right != nullptr) {
		right->in_order_traversal(vect);
	}

}

template <typename T>
Tree<T>* Tree<T>::create_bst_from_balanced_tree() {
	std::vector<T> sorted_data;
	this->in_order_traversal(sorted_data);
	sort(sorted_data.begin(), sorted_data.end());
	return build_balanced_bst(sorted_data, 0, sorted_data.size() - 1, false);
}

template <typename T>
void Tree<T>::DrawT()
{
	int height = getHeight();

	int radius = 80 / height;
	int heightDifference = (radius * 2) + 10;

	sf::RenderWindow window(sf::VideoMode(pow(2, height) * (radius + 10) * 2 ,
		(height * heightDifference) + radius), "Binary Tree");

	window.clear(sf::Color(128, 128, 128));

	DrawElement(this, pow(2, height) * (radius + 10), 1, height, radius * 3, radius, window);

	window.display();

	while (window.isOpen())
	{
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
		}
	}
}

template <typename T>
void Tree<T>::DrawElement(Tree<T>* tree, int xpos, int curLevel, int totalLevel, int shift, int radius, sf::RenderWindow& window)
{
	sf::Vector2f position = { static_cast<float>(xpos), static_cast<float>((radius * 2) + (radius * 2 + 10) * (curLevel - 1)) };

	sf::CircleShape circle(static_cast<float>(radius));

	circle.setFillColor(sf::Color::White);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(3);

	circle.setPosition(position.x - static_cast<float>(radius), position.y - static_cast<float>(radius));

	T element = tree->get_data();

	sf::Text text;
	std::ostringstream buffer;
	buffer << std::fixed << std::setprecision(1) << element;

	sf::Font font;
	font.loadFromFile("Arial.TTF");
	text.setFont(font);

	text.setString(buffer.str());
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setCharacterSize(radius * 0.75);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(position.x, position.y));

	window.draw(circle);

	window.draw(text);

	if (tree->left != nullptr) {
		sf::VertexArray line(sf::Lines, 2);
		position.x -= radius;
		line[0].position = position;
		position.x += radius;
		line[1].position = { static_cast<float>(xpos - shift * (totalLevel - curLevel)), static_cast<float>((radius)+(radius * 2 + 10) * (curLevel)) };
		window.draw(line);
		DrawElement(tree->left, xpos - shift * (totalLevel - curLevel), curLevel + 1, totalLevel, shift, radius, window);
	}

	if (tree->right != nullptr) {
		sf::VertexArray line(sf::Lines, 2);
		position.x += radius;
		line[0].position = position;
		position.x -= radius;
		line[1].position = { static_cast<float>(xpos + shift * (totalLevel - curLevel)), static_cast<float>((radius)+(radius * 2 + 10) * (curLevel)) };
		window.draw(line);
		DrawElement(tree->right, xpos + shift * (totalLevel - curLevel), curLevel + 1, totalLevel, shift, radius, window);
	}
}