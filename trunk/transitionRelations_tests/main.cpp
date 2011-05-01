/*
 * @author: Fernando Augusto Fernandes Braz
 */
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class QBF
{
public:      
      int id;
      bool value;
      void print()
      {
           cout << "QBF " << id << ": " << value << endl;     
      }
};

class Node
{
public:
      int id;
      vector<Node*> children;
      vector<QBF*> properties;
      void print()
      {
           cout << "Children: " << children.size() << endl;     
           cout << "Properties: " << properties.size() << endl;
      }
      string getProperties(bool linha)
      {
         string str = "";
         stringstream ss;
         for (int i = 0; i < properties.size(); i++)
         {
             ss << properties.at(i)->id;          
             if (!properties.at(i)->value) str += "!";
             str += ss.str();
             if (linha) str += "'";
             if (i < properties.size()-1) str += " & ";
             ss.str("");
         }            
         return str; 
      }
};

string getTransitionRelations(Node * pai)
{
     string transitionRelations = "";
     string propertiesPai = pai->getProperties(false);
     for (int i = 0; i < pai->children.size(); i++)
     {
         string propertiesFilho = pai->children.at(i)->getProperties(true);
         transitionRelations += "( " + propertiesPai + " & " + propertiesFilho + " )";
         if (i < pai->children.size()-1) transitionRelations += " | ";
     }  
     return transitionRelations; 
}

int main(int argc, char *argv[])
{
    
    QBF * a = new QBF;
    QBF * b = new QBF;
    QBF * a1 = new QBF;
    QBF * b1 = new QBF;
    QBF * c1 = new QBF;
    QBF * d1 = new QBF;
    
    a->id = a1->id = 1;
    a->value = true;
    a1->value = false;
    
    b->id = b1->id = 2;
    b->value = true;
    b1->value = true;
    
    c1->id = 3;
    c1->value = true;
    
    d1->id = 4;
    d1->value = false;        
    
    Node * pai = new Node;
    Node * filho1 = new Node;
    Node * filho2 = new Node;
    Node * filho3 = new Node;        
    
    pai->id = 1;
    filho1->id = 2;
    filho2->id = 3;
    filho3->id = 4;        
    
    pai->properties.push_back(a);
    pai->properties.push_back(b);    
    
    filho1->properties.push_back(a1);
    filho1->properties.push_back(b1);
    
    filho2->properties.push_back(b1);
    filho2->properties.push_back(c1);
    
    filho3->properties.push_back(a1);
    filho3->properties.push_back(d1);        
        
    pai->children.push_back(filho1);
    pai->children.push_back(filho2);
    pai->children.push_back(filho3);        
    cout << getTransitionRelations(pai) << endl;
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
