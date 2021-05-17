#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
private:
    Node* Par;
    int data;
    vector<Node*> chi_v;
public:
    Node(int dt) {
        this->data = dt;
        this->Par = NULL;
    }
    friend class Tree;
};

class Tree {
private:
    Node* root;
    vector<Node*> node_v;
    
public:
    Tree(int dt) {
        Node* newNode = new Node(dt);
        this->root = newNode;
        this->node_v.push_back(newNode);
    }
    // 부모( dt1)에 자식(dt2) 삽입
    void Insert(int dt1, int dt2) {
        if(dt1 == dt2) {
            return;
        }
        Node* newNode = new Node(dt2);
       
        for(int i = 0; i < node_v.size(); i++) {
            if(node_v[i]->data == dt1) {
                node_v[i]->chi_v.push_back(newNode);
                node_v.push_back(newNode);
                newNode->Par = node_v[i];
               
                return ;
            }
            
        }
        cout << -1 << endl;
    }
    
    void Delete(int dt) {
        for(int i = 0; i < node_v.size(); i++) {
            if(node_v[i]->data == dt) {
                if(node_v[i] == root) {
                    cout << -1 << endl;
                    return ;
                }
                for (Node* child : node_v[i]->chi_v) {
                    node_v[i]->Par->chi_v.push_back(child);
                    child->Par = node_v[i]->Par;
                }
                
                for (int j = 0; j < node_v[i]->Par->chi_v.size(); j++) {
                    if(node_v[i]->Par->chi_v[j]->data == dt) {
                        node_v[i]->Par->chi_v.erase(node_v[i]->Par->chi_v.begin()+j);
                    }
                }
                node_v.erase(node_v.begin() + i);
                delete node_v[i];
               
                return;
            }
            
            
        }
        cout << -1 << endl;
    }
    
    //부모 출력
    void Print(int dt) {
        for(int i = 0; i < node_v.size(); i++) {
            if(node_v[i]->data == dt) {
                if(node_v[i] == root) {
                    cout << -1 << endl;
                    return ;
                }
                cout << node_v[i]->Par->data << endl;
                return;
            }
            
        }
        cout << -1 << endl;
    }
    
  
    
    
};



int main() {
    
    Tree a(1);

    
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        string M;
        cin >> M;
        
        if(M == "insert") {
            int dt1, dt2;
            cin >> dt1 >> dt2;
            a.Insert(dt1, dt2);
        }
        else if(M == "delete") {
            int dt1;
            cin >> dt1;
            a.Delete(dt1);
        }
        else if(M == "print") {
            int dt1;
            cin >> dt1;
            a.Print(dt1);
        }
    }
    
    return 0;
}
//#include<iostream>
//#include<algorithm>
//using namespace std;
//#define maxNum 500001
//
//int n;
//pair<int, int> a[maxNum];
//
//int main() {
//    cin >> n;
//    for (int i = 0; i < n; i++) {
//        cin >> a[i].first;
//        a[i].second = i;
//    }
//    sort(a, a + n);
//
//    int answer = 0;
//    for (int i = 0; i < n; i++) {
//        answer = max(answer, a[i].second - i);
//    }
//    cout << answer+1;
//    
//	return 0;
//}