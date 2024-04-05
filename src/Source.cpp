
////DSA Project - Netflix 2
////By: Faizaan Al Faisal (342626) & Muhammad Osama Ehsaan (353698)
////BSCS-10-A

///*****************************************************************************************************************************************/
////libraries + data structures + algorithms


//#include <iostream>
//#include <fstream> //file manipulation
//#include <sstream> //stream manipulation
//#include <string> //some string manipulation functions

////#include "AVL_Trees.cpp" //using as placeholder for red-black trees until fully implemented
//#include "RedBlackTrees.cpp" //including red black trees implementation
//#include "DoublyLinkedList.cpp" //including dll implementation to allow O(1) insertion/deletion to front and back nodes
//#include "Graphs.cpp" //including my version of graphs to create links between genres of films, to determine other similar movies
//#include "VectorImplementation.cpp" //including my own implementation of vectors, is dynamic array with pop_back and push_back functions
////and can directly access any index, if need be

//#include "MergeSort.cpp" //including my merge sort algorithm to sort edges by weight, bool operators overloaded in edge class

//using namespace std;



///*****************************************************************************************************************************************/
////parsing functions



//DoublyLinearList<string> SplitBy(const string& st, const char& x) //split any input string "st" on any instances of character "x"
//{
//	DoublyLinearList<string> output; //output in the form of a vector
//	istringstream buf(st); //input stream for getline
//	string s;
//	while (getline(buf, s, x)) //getline into string "s" up to each instance of char/delimiter "x"
//	{
//		while (s[0] == ' ')
//			s.erase(0, 1); //if first character of a string is a space, modify string to erase that character
//		output.push_back(s); //add the string to output vector
//	}
//	return output;
//}

//string removeQuotes(string st) //remove quotes at beginning and end of a string
//{
//	if (st[0] == '"') st.erase(0, 1); //remove front character
//	if (st[st.length() - 1] == '"') st.pop_back(); //remove last character
//	return st;
//}

//DoublyLinearList<string> splitMultiVal(const string& st) //split string if it contains multiple entries
//{
//	DoublyLinearList<string> out;
//	if (st[0] == '"') //if first character is ", then string contains multiple characters, split it if so
//	{
//		out.push_back(removeQuotes(st));
//		out = SplitBy(out.front(), ',');
//	}
//	else out.push_back(st); //otherwise simply return input string in form of dll
//	return out;
//}

//bool ValidRow(string row) //if row contains an invalid character, return false
//{
//	for (int i = 0; i < row.size(); i++)
//		if ((int)row[i] < 0 || (int)row[i] > 127) return false; //return false if any of the string contains an invalid char
//	return true;
//}



///*****************************************************************************************************************************************/
////class defintions



////forward declaration of all classes, since other classes use them
//class Actor;
//class Director;
//class Country;
//class Genre;
//class Rating;

////class codes:
//class Show
//{
//public:
//	string title;
//	string description;
//	short unsigned int release_year;
//	short unsigned int duration;
//	bool is_movie; //true if it is a movie, false if it is a show
//	Vector<RBTNode<Actor>*> cast;
//	Vector<RBTNode<Director>*> directing_team;
//	Vector<RBTNode<Genre>*> genres;
//	RBTNode<Rating>* rating; //a movie has only 1 rating

//	//RedBlackTree<RBTNode<Genre>*> genre;
//	Show(bool im = true, string t = "", unsigned short int rel = 2000, string d = "",
//		short unsigned int dur = 1, RBTNode<Rating>* r = NULL)
//		: is_movie(im), title(t), release_year(rel), description(d), duration(dur), rating(r) {}
//	//default + parameterized constructor

//	friend ostream& operator<<(ostream& os, const Show& s) //overloading operator for printing
//	{
//		os << " Title: " << s.title << "\n";
//		os << " Duration: " << s.duration;
//		if (s.is_movie) //if movie, duration is given in minutes
//			os << " Minutes\n";
//		else //if show, duration is given in seasons
//		{
//			if (s.duration == 1) os << " Season\n";
//			else os << " Seasons\n";
//		}
//		os << " Release Year: " << s.release_year << "\n";
//		if (s.is_movie)
//			os << " Type: Movie\n";
//		else os << " Type: Show\n";
//		os << " Description: " << s.description << "\n";
//		return os;
//	}

//	//overloading boolean comparison operators, based on Show names:
//	friend bool operator<(const Show& s1, const Show& s2)
//	{
//		return s1.title < s2.title;
//	}
//	friend bool operator>(const Show& s1, const Show& s2)
//	{
//		return s1.title > s2.title;
//	}
//	friend bool operator==(const Show& s1, const Show& s2)
//	{
//		return s1.title == s2.title;
//	}
//	friend bool operator!=(const Show& s1, const Show& s2)
//	{
//		return s1.title != s2.title;
//	}
//};

//class Actor
//{
//public:
//	string name;
//	Vector<RBTNode<Show>*> played_in;
//	Vector<RBTNode<Actor>*> co_actors;

//	Actor(string n = "") : name(n) {}
//	//default + parameterized constructor

//	friend ostream& operator<<(ostream& os, const Actor& a) //overloading operator for printing
//	{
//		os << a.name << "\n";
//		return os;
//	}

//	//overloading boolean comparison operators, based on actor names:
//	friend bool operator<(const Actor& a1, const Actor& a2)
//	{
//		return a1.name < a2.name;
//	}
//	friend bool operator>(const Actor& a1, const Actor& a2)
//	{
//		return a1.name > a2.name;
//	}
//	friend bool operator==(const Actor& a1, const Actor& a2)
//	{
//		return a1.name == a2.name;
//	}
//	friend bool operator!=(const Actor& a1, const Actor& a2)
//	{
//		return a1.name != a2.name;
//	}
//};

//class Director
//{
//public:
//	string name;
//	Vector<RBTNode<Show>*> directed;

//	Director(string n = "") : name(n) {}

//	friend ostream& operator<<(ostream& os, const Director& st) //overloading operator for printing
//	{
//		os << st.name << "\n";
//		return os;
//	}

//	//overloading boolean comparison operators, based on Director names:
//	friend bool operator<(const Director& d1, const Director& d2)
//	{
//		return d1.name < d2.name;
//	}
//	friend bool operator>(const Director& d1, const Director& d2)
//	{
//		return d1.name > d2.name;
//	}
//	friend bool operator==(const Director& d1, const Director& d2)
//	{
//		return d1.name == d2.name;
//	}
//	friend bool operator!=(const Director& d1, const Director& d2)
//	{
//		return d1.name != d2.name;
//	}
//};

//class Country
//{
//public:
//	string name;
//	Country(string n = "") : name(n) {}

//	friend ostream& operator<<(ostream& os, const Country& c) //overloading operator for printing
//	{
//		os << c.name << "\n";
//		return os;
//	}

//	//overloading boolean comparison operators for rbtree insertions, based on country names:
//	friend bool operator<(const Country& c1, const Country& c2)
//	{
//		return c1.name < c2.name;
//	}
//	friend bool operator>(const Country& c1, const Country& c2)
//	{
//		return c1.name > c2.name;
//	}
//	friend bool operator==(const Country& c1, const Country& c2)
//	{
//		return c1.name == c2.name;
//	}
//	friend bool operator!=(const Country& c1, const Country& c2)
//	{
//		return c1.name != c2.name;
//	}

//};

//class Genre
//{
//public:
//	string name;
//	Genre(string n = "") : name(n) {}

//	friend ostream& operator<<(ostream& os, const Genre& g) //overloading operator for printing
//	{
//		os << g.name << "\n";
//		return os;
//	}

//	//overloading boolean comparison operators, based on genre names:
//	friend bool operator<(const Genre& g1, const Genre& g2)
//	{
//		return g1.name < g2.name;
//	}
//	friend bool operator>(const Genre& g1, const Genre& g2)
//	{
//		return g1.name > g2.name;
//	}
//	friend bool operator==(const Genre& g1, const Genre& g2)
//	{
//		return g1.name == g2.name;
//	}
//	friend bool operator!=(const Genre& g1, const Genre& g2)
//	{
//		return g1.name != g2.name;
//	}
//};

//class Rating
//{
//public:
//	string name;
//	Rating(string n = "") : name(n) {}
	
//	friend ostream& operator<<(ostream& os, const Rating& r) //overloading operator for printing
//	{
//		os << r.name << "\n";
//		return os;
//	}

//	//overloading boolean comparison operators for rbtree insertions, based on rating names:
//	friend bool operator<(const Rating& r1, const Rating& r2)
//	{
//		return r1.name < r2.name;
//	}
//	friend bool operator>(const Rating& r1, const Rating& r2)
//	{
//		return r1.name > r2.name;
//	}
//	friend bool operator==(const Rating& r1, const Rating& r2)
//	{
//		return r1.name == r2.name;
//	}
//	friend bool operator!=(const Rating& r1, const Rating& r2)
//	{
//		return r1.name != r2.name;
//	}
//};




///*****************************************************************************************************************************************/
////additional functions:
////these include functions that print extra information related to any node
////also include functions that initialize and manage the graphs



//template <class T> void RedBlackTree<T>::PrintMoviesPlayedInBy(RBTNode<Actor>* actor)
//{
//	if (actor != NULL)
//	{
//		PrintMoviesPlayedInBy(actor->leftChild);
//		cout << "\033[0;36m Actor: " << actor->data << "\033[0m";
//		for (int i = 0; i < actor->data.played_in.size(); i++)
//			cout << actor->data.played_in.arr[i]->data << "\n";
//		cout << "\n\n";
//		PrintMoviesPlayedInBy(actor->rightChild);
//	}
//}

//template <class T> void RedBlackTree<T>::PrintMoviesDirectedBy(RBTNode<Director>* director)
//{
//	if (director != NULL)
//	{
//		PrintMoviesDirectedBy(director->leftChild);
//		cout << "\033[0;36m Director: " << director->data << "\033[0m";
//		for (int i = 0; i < director->data.directed.size(); i++)
//			cout << director->data.directed.arr[i]->data << "\n";
//		cout << "\n\n";
//		PrintMoviesDirectedBy(director->rightChild);
//	}
//}

//template <class T> void RedBlackTree<T>::PrintGenresFor(RBTNode<Show>* show)
//{
//	if (show != NULL)
//	{
//		PrintGenresFor(show->leftChild);
//		cout << "\033[0;36m Genres for the Film: \033[0m" << show->data.title << "\n ";
//		for (int i = 0; i < show->data.genres.size(); i++)
//			cout << show->data.genres.arr[i]->data << " ";
//		cout << "\n";
//		PrintGenresFor(show->rightChild);
//	}
//}

//void PrintAdjacentVerticesTo(GraphVertex<RBTNode<Show>*>* showVertex) //print all adjacent vertices to the given graph vertex
//{
//	cout << "\033[0;36m Printing Vertices Adjacent to Vertex: \033[0m" << showVertex->data->data.title << "\n";
//	if (showVertex->adjacentTo.size() == 0)
//	{
//		cout << "\033[0;33m No adjacent edges!\033[0m \n ";
//		return;
//	}
//	for (int i = 0; i < showVertex->adjacentTo.size(); i++)
//	{
//		cout << "\033[0;33m Vertex: \033[0m" << showVertex->adjacentTo.arr[i].destination->data->data.title << "\n"; //print name of movie
//		cout << "\033[0;33m Weight: \033[0m" << showVertex->adjacentTo.arr[i].weight << "\n\n";
//	}
//	cout << "\n\n";
//}

//void addCommonGenreEdges(GraphList<RBTNode<Show>*> &graph, RBTNode<Show>* show) //add links from show node to all existing nodes in graph
//{
//	graph.addVertex(show); //add given show info to graph
//	GraphVertex<RBTNode<Show>*> *source, *destination; //source and destination node pointers
//	source = graph.vertices.end(); //source is most recently added element
//	double weight = 0;
//	for (int i = 0; i < graph.vertices.size(); i++)
//	{
//		weight = 0; //reinitialize weight at every iteration
//		destination = graph.vertices.arr[i];
		
//		if (source == destination) continue; //skip iteration if source and destination are the same, no need to recommend same movie

//		int sourceGenreCount = show->data.genres.size();
//		int destinationGenreCount = destination->data->data.genres.size();

//		if (show->data.rating->data == destination->data->data.rating->data && show->data.rating->data.name != "")
//			weight += 1;
//		//if source and destination have the same rating, increment weight
//		for (int sGenres = 0; sGenres < sourceGenreCount; sGenres++)
//			for (int dGenres = 0; dGenres < destinationGenreCount; dGenres++)
//				if (show->data.genres.arr[sGenres] == destination->data->data.genres.arr[dGenres])
//						weight += 1;
//		//for all genres in source and destination, increment weight for every common genre
				
//		if (weight != 0 && source != destination)
//		{
//			source->addEdge(destination, weight);
//			if (!graph.isDirected) destination->addEdge(source, weight);
//		}
//	}
//}

//template <class T> void SortGraphEdgesByWeight(GraphList<T> &graph) //sort all edges in graphs in descending order
//{
//	for (int i = 0; i < graph.vertices.size(); i++)
//	{
//		if (graph.vertices.arr[i]->adjacentTo.numElements != 0)
//		{
//			GraphEdge<RBTNode<Show>*>* edgeArray = graph.vertices.arr[i]->adjacentTo.arr;
//			//merge sort edges by their weights
//			MergeSort(edgeArray, 0, graph.vertices.arr[i]->adjacentTo.size() - 1);
//		}
//	}
//}



////Search information in RB Trees by any given search term:
//Vector<RBTNode<Show>*> SearchShowsBy(RBTNode<Show>* current, Vector<RBTNode<Show>*> vec, const string& st)
//{
//	if (current != NULL)
//	{
//		//cout << " Current node: " << current->data.title << "\n";
//		vec = SearchShowsBy(current->leftChild, vec, st);

//		string title = current->data.title;
//		string searchTerm = st;
//		for (int i = 0; i < title.size(); i++)
//			title[i] = tolower(title[i]);
//		for (int i = 0; i < searchTerm.size(); i++)
//			searchTerm[i] = tolower(searchTerm[i]);
//		if (title.find(searchTerm) != string::npos)
//			vec.push_back(current);

//		vec = SearchShowsBy(current->rightChild, vec, st);
//	}
//	return vec;
//}

//Vector<RBTNode<Actor>*> SearchActorsBy(RBTNode<Actor>* current, Vector<RBTNode<Actor>*> vec, const string& st)
//{
//	if (current != NULL)
//	{
//		//cout << " Current node: " << current->data.name << "\n";
//		vec = SearchActorsBy(current->leftChild, vec, st);

//		string name = current->data.name;
//		string searchTerm = st;
//		for (int i = 0; i < name.size(); i++)
//			name[i] = tolower(name[i]);
//		for (int i = 0; i < searchTerm.size(); i++)
//			searchTerm[i] = tolower(searchTerm[i]);
//		if (name.find(searchTerm) != string::npos)
//			vec.push_back(current);

//		vec = SearchActorsBy(current->rightChild, vec, st);
//	}
//	return vec;
//}

//Vector<RBTNode<Director>*> SearchDirectorsBy(RBTNode<Director>* current, Vector<RBTNode<Director>*> vec, const string& st)
//{
//	if (current != NULL)
//	{
//		//cout << " Current node: " << current->data.name << "\n";
//		vec = SearchDirectorsBy(current->leftChild, vec, st);

//		string name = current->data.name;
//		string searchTerm = st;
//		for (int i = 0; i < name.size(); i++)
//			name[i] = tolower(name[i]);
//		for (int i = 0; i < searchTerm.size(); i++)
//			searchTerm[i] = tolower(searchTerm[i]);
//		if (name.find(searchTerm) != string::npos)
//			vec.push_back(current);

//		vec = SearchDirectorsBy(current->rightChild, vec, st);
//	}
//	return vec;
//}



///*****************************************************************************************************************************************/
////main function


//int main()
//{
//	//fstream csvFile;
//	fstream txtFile;
//	txtFile.open("test sample.txt", ios::in); //open file as read-only
//	//converted csv file to a tab-delimited txt file, as certain columns had instances
//	//where they both were and were not separated by double-quotes, which caused logical issues in running
//	string title, type, actor, director, country, date, rating, duration, listed_in, description;
//	short unsigned int rel_year;
//	bool t; //for type of entry, whether show is a movie or tv show


//	//declaring red black trees for storage
//	RedBlackTree<Show> showsTree;
//	RedBlackTree<Director> directorsTree;
//	RedBlackTree<Actor> actorsTree;
//	RedBlackTree<Genre> genresTree;
//	RedBlackTree<Rating> ratingsTree;

//	//a graph of all shows, and the edges (and their weights) represent common genres between the nodes
//	//functions similarly to a recommendation system, higher weight = more likely to recommend, since similar tastes
//	GraphList<RBTNode<Show>*> showsLinkedByGenre(false); //create an undirected graph


//	//vectors to insert pointers into relevant locations
//	Vector<RBTNode<Actor>*> actorsInShow;
//	Vector<RBTNode<Director>*> directorsInShow;
//	Vector<RBTNode<Genre>*> showGenres; //show may have multiple genres, directors, actors, so using Vectors
//	//RBTNode<Rating>* showRating; //only 1 rating per show
//	//RBTNode<Show>* currentShow;
	
//	if (txtFile.is_open()) //if file has successfully opened
//	{
//		string txtRow; //keeps full row of txt file
//		DoublyLinearList<string> tabSplitRows; //txt file splits columns based on tabs '\t' characters
//		DoublyLinearList<string> multiValRow; //for columns with multiple values, store their information in deque
		
//		getline(txtFile, txtRow); //read + ignore first line
//		while (getline(txtFile, txtRow)) //read all lines available
//		{
//			if (!ValidRow(txtRow)) continue; //if row is invalid, skip line and read next line:

//			tabSplitRows = SplitBy(txtRow, '\t'); //split rows by '\t' tabs, contains a single columns of dataset at each node
//			//cout << " test initial \n\n";
//			tabSplitRows.pop_front(); //remove show_id

//			type = tabSplitRows.front(); //read type
//			tabSplitRows.pop_front(); //remove type
//			if (type == "Movie") t = true;
//			else t = false;
//			//cout << " test type \n\n";


//			title = tabSplitRows.front(); //read title
//			tabSplitRows.pop_front(); //remove title
			
//			//cout << " test title \n\n";
			
			
//			multiValRow = splitMultiVal(tabSplitRows.front()); //directors
//			//cout << " pre test directors \n\n";
//			while(!multiValRow.IsEmpty())
//			{
//				director = multiValRow.front();
//				//cout << " director: " << director << "\n";
//				multiValRow.pop_front();
//				directorsTree.Insert(Director(director));
//				directorsInShow.push_back(directorsTree.targetNode);
//				//push most recently inserted director into a new
//			}
//			tabSplitRows.pop_front(); //remove directors from deque


//			multiValRow = splitMultiVal(tabSplitRows.front()); //actors
//			//cout << " pre test actors \n";
//			while (!multiValRow.IsEmpty())
//			{
//				actor = multiValRow.front();
//				//cout << " actor: " << actor << "\n";
//				multiValRow.pop_front();
//				actorsTree.Insert(Actor(actor));
//				actorsInShow.push_back(actorsTree.targetNode); //AVL Tree has a member targetNode which keeps track of most recent inserted node
//				//push into vector
//			}
//			tabSplitRows.pop_front(); //actors removed


//			tabSplitRows.pop_front(); //country removed
//			tabSplitRows.pop_front(); //date added removed


//			rel_year = stoi(tabSplitRows.front()); //release year, data member of show (which obj is not yet created)
//			tabSplitRows.pop_front(); //release year removed


//			rating = tabSplitRows.front();
//			ratingsTree.Insert(Rating(rating)); //create a new ratings object
//			tabSplitRows.pop_front(); //rating removed

			
			
//			duration = tabSplitRows.front(); //duration
//			int dur = stoi(duration); //stoi() retrieves integers from any string till it encounters a non-numeric character
//			//cout << dur << "\n";
//			tabSplitRows.pop_front(); //duration removed


//			listed_in = tabSplitRows.front(); //listed_in / genres
//			multiValRow = splitMultiVal(listed_in);
//			while (!multiValRow.IsEmpty())
//			{
//				listed_in = multiValRow.front();
//				multiValRow.pop_front();
//				genresTree.Insert(Genre(listed_in)); //targetNode is updated to inserted/already existing genre now
//				showGenres.push_back(genresTree.targetNode);
//			}
//			tabSplitRows.pop_front(); //listed_in removed


//			description = tabSplitRows.front(); //description
//			description = removeQuotes(description);
//			tabSplitRows.pop_front(); //description removed

			
//			showsTree.Insert(Show(t, title, rel_year, description, dur, ratingsTree.targetNode));
//			//create a show with all desired attributes


//			//adding ptrs for actors, directors, genres, countries, etc. into showsTree
//			for(int i = 0; i < actorsInShow.size(); i++) //adds actors ptrs for current movie based on information from this row
//			{
//				RBTNode<Actor>* x = actorsInShow.arr[i];
//				showsTree.targetNode->data.cast.push_back(x);
//				//cout << x->data << "\n";
//			}
//			for (int i = 0; i < directorsInShow.size(); i++) //same as above for directors
//			{
//				RBTNode<Director>* x = directorsInShow.arr[i];
//				showsTree.targetNode->data.directing_team.push_back(x);
//				//cout << x->data << "\n";
//			}
//			for (int i = 0; i < showGenres.size(); i++) //same as above for genres
//			{
//				RBTNode<Genre>* x = showGenres.arr[i];
//				showsTree.targetNode->data.genres.push_back(x);
//			}

//			//adding show ptrs to directors, actors, movies
//			for (int i = 0; i < showsTree.targetNode->data.cast.size(); i++)
//				showsTree.targetNode->data.cast.arr[i]->data.played_in.push_back(showsTree.targetNode);

//			for (int i = 0; i < showsTree.targetNode->data.directing_team.size(); i++)
//				showsTree.targetNode->data.directing_team.arr[i]->data.directed.push_back(showsTree.targetNode);


//			addCommonGenreEdges(showsLinkedByGenre, showsTree.targetNode); //add all connections from targetNode to all pre-existing nodes


//			//clear all vectors and deques for further use just in case they are not already cleared
//			directorsInShow.clear();
//			actorsInShow.clear();
//			showGenres.clear();

//			tabSplitRows.clear();
//			multiValRow.clear();
//		}

//		txtFile.close(); //close text file after parsing is completed


//		//sort edges of graph by weight
//		SortGraphEdgesByWeight(showsLinkedByGenre);


//		//cout << "\033[0;33m Movies in Tree: \033[0m \n";
//		//showsTree.InOrderPrint(showsTree.root);
//		//cout << "\n\n\n";

//		//cout << "\033[0;33m Directors in Tree: \033[0m \n";
//		//directorsTree.InOrderPrint(directorsTree.root);
//		//cout << "\n\n\n";

//		//cout << "\033[0;33m Actors in Tree: \033[0m \n";
//		//actorsTree.InOrderPrint(actorsTree.root);
//		//cout << "\n\n\n";


//		//cout << "\n\n" << showsTree.root->data;

//		//cout << "\n\n Actors in Show: \n";
//		////cout << "\n " << showsTree.root->leftChild->data.cast.size();
//		//for (int i = 0; i < showsTree.root->data.directing_team.size(); i++)
//		//	cout << " " << showsTree.root->data.directing_team.arr[i]->data;


//		//cout << "Movies played in by: ";
//		//actorsTree.Search(Actor("Damandeep Singh Baggan"));
//		//RBTNode<Actor>* temp = actorsTree.loc;
//		//cout << temp->data << "\n\n";
//		//for (int i = 0; i < temp->data.played_in.size(); i++)
//		//	cout << "\n " << temp->data.played_in.arr[i]->data;

//		//actorsTree.PrintMoviesPlayedInBy(actorsTree.root);
//		//directorsTree.PrintMoviesDirectedBy(directorsTree.root);
//		//showsTree.PrintGenresFor(showsTree.root);

//		//ratingsTree.InOrderPrint(ratingsTree.root);
//		//genresTree.InOrderPrint(genresTree.root);
//		//cout << showsLinkedByGenre.vertices.size() << "\n\n";


//		//for (int i = 0; i < showsLinkedByGenre.vertices.size(); i++)
//		//	PrintAdjacentVerticesTo(showsLinkedByGenre.vertices.arr[i]);
//		Vector<RBTNode<Show>*> searchResults;
//		searchResults = SearchShowsBy(showsTree.root, searchResults, "Tra");
//		if (searchResults.size() == 0) cout << " Nothing found!\n";
//		for (int i = 0; i < searchResults.size(); i++)
//		{
//			RBTNode<Show>* tempResults = searchResults.arr[i];
//			cout << " Returned Titles: " << tempResults->data.title << "\n";
//		}
//		//cout << showsLinkedByGenre.vertices.arr[0];
//	}
//	else cout << " file did not open\n\n";
//}


////code end
///*****************************************************************************************************************************************/
