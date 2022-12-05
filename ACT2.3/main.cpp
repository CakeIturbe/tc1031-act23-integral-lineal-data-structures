// =================================================================
//
// File: main.cpp
// Author: DIEGO ITURBE BRAVO
// Date: 4/DEC/2022
//
// =================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Node{
	private:
		string data;
		Node *prev;
		Node *next;

		friend class LinkedList;
};

class LinkedList{
	public:
		LinkedList();
		~LinkedList();
		string getFront() const;
		string getBack() const;
		void addFront(string dt);
		void addBack(string dt);
		void removeFront();
		void removeBack();
		void printReverse();
		void printForward();
		bool empty() const;
		void addSort(string val);
		void addBefore(Node *temp, string val);
		void filterPrint();
	private:
		Node *header;
		Node *trailer;
};

void openFile(ifstream& inFile,string fname){
	inFile.open(fname);
	if (inFile.is_open()){
		// cout << "Successfully opened file"<<endl;
	}
	else{
		cout << "Failed to open file" << endl;
		exit(-1);
	}
}

vector<string> processFile(ifstream& inFile,int i, int limit){
	//read line by line
	vector<string> content;
	string line;
	int cont=0;
	
	while (!inFile.eof() && i < limit){
		i++;
		getline(inFile,line);
		// bool found = line.find('.');
		//found == 1 == No se encontro punto
		if(inFile.good()){
			content.push_back(line);
			
		}
		cont++;

	} 
	return content;
}

void search(string prefix, string linea, vector<string> &coincidencias){
	string busqueda = linea.substr( 17, 3 );
	if (prefix == busqueda){
		coincidencias.push_back(linea); 
	}

}


int main(int argc, char* argv[]) {
	ifstream inFile;
	openFile(inFile,"input1.txt");
	//obtener linea 1
	vector<string> linea1 = processFile(inFile,0,1);
	string linea, linea2;
	char delimiter= ' ';
	vector<string> linea1separada;
	for (int i = 0; i < linea1.size(); i++){
		stringstream x(linea1[i]);
		while (getline(x, linea, delimiter)) {
        linea1separada.push_back(linea);
		}
	}
	stringstream nP(linea1separada[0]);
	string prefix = linea1separada[1];
	nP >> argc;
	// obtener lineas registros
	vector<string> r1 = processFile(inFile,1,argc+1);
	vector<string> coincidencias;
	for (int i = 0; i < r1.size() ; i++){
		stringstream y(r1[i]);
		while (getline(y,linea2)){
			search(prefix, linea2, coincidencias);
		}
	}

	// BUSCAR COINCIDENCIAS
	LinkedList ll;
	for(int i = 0; i < coincidencias.size() ; i++){
		ll.addSort(coincidencias[i]);
	}
	ll.filterPrint();
	return 0;
}

LinkedList::LinkedList(){
	header = new Node;
	trailer = new Node;
	header-> next = trailer;
	trailer-> prev = header;
	header-> prev = NULL;
	trailer-> next = NULL;
};

string LinkedList::getFront() const {
	return header-> next-> data;
}
string LinkedList::getBack() const {
	return trailer->prev->data;
}

void LinkedList::addSort(string val){
	Node *temp = new Node;
	temp = header ->next;
	if (empty() == true){
		addFront(val);
	}
	
	else{
		int valor, valorHead, valorTail, valorMedio;
		stringstream y1(val.substr(3,2));
		string Head= header->next->data;
		stringstream y2(Head.substr(3,2));
		y1>>valor;
		y2>>valorHead;
		string Tail= trailer->prev->data;
		stringstream y3(Tail.substr(3,2));
		y3>>valorTail;
		if (valor <= valorHead){
			addFront(val);
		}

		else if (valor >= valorTail){
			addBack(val);
		}
		else{
			string Medio= temp->data;
			stringstream y4(Medio.substr(3,2));
			y4>>valorMedio;
			while (valorMedio < valor ){
				temp = temp ->next;
				Medio= temp->data;
				stringstream y4(Medio.substr(3,2));
				y4>>valorMedio;
			}
			addBefore(temp,val);
			
		}
	}
}

void LinkedList::addBefore(Node *temp, string val){
	Node *nd = new Node;
	nd->data=val;
	nd->prev = temp -> prev;
	nd->next = temp;

	temp -> prev -> next = nd;
	temp -> prev = nd;
}

void LinkedList::addFront(string dt){
	Node *nd = new Node;
	nd->data=dt;
	nd->prev = header;
	nd->next = header -> next;

	header -> next -> prev = nd;
	header -> next = nd;
}

void LinkedList::addBack(string dt){
	Node *nd= new Node;
	nd->data = dt;
	nd->prev = trailer -> prev;
	nd->next = trailer;

	trailer->prev->next = nd;
	trailer->prev = nd;
}

void LinkedList::removeFront(){
	Node *nd=header->next->next;
	delete header->next;
	header->next=nd;
	nd->prev=header;
}

void LinkedList::removeBack(){
	Node *nd=trailer->prev->prev;
	delete trailer->prev;
	trailer->prev=nd;
	nd->next=trailer;
}

void LinkedList::filterPrint(){
	Node *nd=header->next;
	string nodo;
	int month;
	vector<string> jan,janR,feb,febR,mar,marR,apr,aprR,may,jun,jul,aug,sep,oct,nov,dec,mayR,junR,julR,augR,sepR,octR,novR,decR; 
	while(nd!=trailer){
		nodo = nd->data;
		string month(nodo.substr(3,2));
		
		if (month == "01"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				jan.push_back(nodo);
				
			}
			else{
				janR.push_back(nodo);
			}
		}
		else if (month == "02"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				feb.push_back(nodo);
				
			}
			else{
				febR.push_back(nodo);
			}
		}
		else if (month == "03"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				mar.push_back(nodo);
				
			}
			else{
				marR.push_back(nodo);
			}
		}
		else if (month == "04"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				apr.push_back(nodo);
				
			}
			else{
				aprR.push_back(nodo);
			}
		}
		else if (month == "05"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				may.push_back(nodo);
				
			}
			else{
				mayR.push_back(nodo);
			}
		}
		else if (month == "06"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				jun.push_back(nodo);
				
			}
			else{
				junR.push_back(nodo);
			}
		}
		else if (month == "07"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				jul.push_back(nodo);
				
			}
			else{
				julR.push_back(nodo);
			}
		}
		else if (month == "08"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				aug.push_back(nodo);
				
			}
			else{
				augR.push_back(nodo);
			}
		}
		else if (month == "09"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				sep.push_back(nodo);
				
			}
			else{
				sepR.push_back(nodo);
			}
		}
		else if (month == "10"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				oct.push_back(nodo);
				
			}
			else{
				octR.push_back(nodo);
			}
		}
		else if (month == "11"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				nov.push_back(nodo);
				
			}
			else{
				novR.push_back(nodo);
			}
		}
		else if (month == "12"){
			string yS(nodo.substr(15,1));
			if (yS == "M"){
				dec.push_back(nodo);
				
			}
			else{
				decR.push_back(nodo);
			}
		}
		nd=nd->next;
	}
	if (jan.size() != 0 && janR.size() != 0){
		int x = jan.size();
		int z = janR.size();
		cout<<"jan"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(jan[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(janR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (feb.size() != 0 && feb.size() != 0){
		int x = feb.size();
		int z = febR.size();
		cout<<"feb"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(feb[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(feb[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (mar.size() != 0 && marR.size() != 0){
		int x = mar.size();
		int z = marR.size();
		cout<<"mar"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(mar[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(mar[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (apr.size() != 0 && aprR.size() != 0){
		int x = apr.size();
		int z = aprR.size();
		cout<<"apr"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(apr[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(aprR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (may.size() != 0 && mayR.size() != 0){
		int x = may.size();
		int z = mayR.size();
		cout<<"may"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(may[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(mayR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (jun.size() != 0 && junR.size() != 0){
		int x = jun.size();
		int z = junR.size();
		cout<<"jun"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(jun[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(junR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (jul.size() != 0 && julR.size() != 0){
		int x = jul.size();
		int z = julR.size();
		cout<<"jul"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(jul[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(julR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (aug.size() != 0 && augR.size() != 0){
		int x = aug.size();
		int z = augR.size();
		cout<<"aug"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(aug[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(augR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (sep.size() != 0 && sepR.size() != 0){
		int x = sep.size();
		int z = sepR.size();
		cout<<"sep"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(sep[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(sepR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (oct.size() != 0 && octR.size() != 0){
		int x = oct.size();
		int z = octR.size();
		cout<<"oct"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(oct[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(octR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (nov.size() != 0 && novR.size() != 0){
		int x = nov.size();
		int z = novR.size();
		cout<<"nov"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(nov[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(novR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
	if (dec.size() != 0 && decR.size() != 0){
		int x = dec.size();
		int z = decR.size();
		cout<<"dec"<<endl;
		cout<< "M "<<x<<": ";
		for (int i =0; i< x;i++){
			string a(dec[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
		cout<< "R "<<z<<": ";
		for (int i =0; i< z;i++){
			string a(decR[i].substr(17,5));
			cout<< a << " ";
		}
		cout<<endl;
	}
}

void LinkedList::printReverse(){
	Node *nd=trailer->prev;
	while(nd!=header){
		cout<<nd->data<<" ";
		nd=nd->prev;
	}

}
void LinkedList::printForward(){
	Node *nd=header->next;
	while(nd!=trailer){
		cout<<nd->data<<" ";
		nd=nd->next;
	}
}

// =================================================================
// Returns if the DoubleLinkedList is empty or not
//
// @returns true if the DoubleLinkedList is empty, false otherwise.
// =================================================================
bool LinkedList::empty() const {
	return (header->next == trailer );
}

LinkedList::~LinkedList(){
	while(header->next != trailer){
		removeFront();
	}
	delete header;
	delete trailer;
}