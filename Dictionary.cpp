/***
* Riddhi Mundhra 
* rmundhra
* 2025 Winter CSE101 PA7
* Dictionary.cpp
* Dictionary ADT Implementation
***/ 





#include "Dictionary.h"

Dictionary::Dictionary(){
    nil = new Node("", 0);
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;

}



Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("", 0);
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
    if(D.root!=D.nil){
        preOrderCopy(D.root, nil);
    }
}

void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::preOrderString(std::string& s, Node*R) const{
    if(R!=nil){
        s+=R->key+"\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

Dictionary::~Dictionary(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
    delete nil;
}

void Dictionary::inOrderString(std::string& s, Node*R) const{
    if(R!=nil){
        inOrderString(s, R->left);
        s+=R->key+ " : "+ std::to_string(R->val)+"\n";
        inOrderString(s, R->right);
       
    }
}



Dictionary::Node* Dictionary::findMin(Node* R){
    while(R->left!=nil){
        R = R->left;
    }
    return R;

}


Dictionary::Node* Dictionary::findMax(Node* R){
    while(R->right!=nil){
        R = R->right;
    }
    return R;

}


   Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
        if(R==nil || k==R->key){
            return R;
        }
        else if(k<R->key){
            return search(R->left, k);
        }
        else{
            return search(R->right, k);
        }
   }

Dictionary::Node* Dictionary::findNext(Node*N){
    if(N->right !=nil){
        return findMin(N->right);
    }

    Node*p = N->parent;
    while(p!=nil && N==p->right){
        N = p;
        p = p->parent;
    }
    return p;
}

Dictionary::Node* Dictionary::findPrev(Node*N){
    if(N->left !=nil){
        return findMax(N->left);
    }

    Node*p = N->parent;
    while(p!=nil && N==p->left){
        N = p;
        p = p->parent;
    }
    return p;
}

int Dictionary::size() const{
    return num_pairs;
}

 keyType Dictionary::currentKey() const{
        if(current!=nil){
          return current->key;
    }
    else{
        throw std::logic_error("Can't return current key");
    }
 }

 valType& Dictionary::currentVal() const{
    if(current!=nil){
          return current->val;
    }
    else{
        throw std::logic_error("Can't return current val");
    }
  
 }

 void Dictionary::Transplant(Node*u,Node*v){
    if(u->parent==nil){
        root = v;
    }
    else if(u==u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    if(v!=nil){
        v->parent = u->parent;
    }

 }

   void Dictionary::remove(keyType k){
    Node*z = search(root, k);
     if(z->left == nil){
        Transplant( z, z->right);
     }
     else if(z->right == nil){
        Transplant(z, z->left);
     }
     else{
        Node*y = findMin(z->right);
        if(y->parent !=z){
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
     }

     if(z==current){
        current = nil;
     }
     delete z;
     num_pairs--;
   }


  bool Dictionary:: hasCurrent() const{
    if(current!=nil){
        return true;
    }
    else{
        return false;
    }
  }

  void Dictionary::Insert(Node*z){
    Node*y = nil;
    Node*x = root;
    while(x!=nil){
        y = x;
        if(z->key<x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
     z->parent = y;
        if(y==nil){
            root = z;
        }

        else if(z->key<y->key){
            y->left = z;
        }
        else{
            y->right = z;

        }

    
  }

void Dictionary::setValue(keyType k, valType v){
   
    if(contains(k)){
         Node*found = search(root, k);
        found->val = v;
    }
    else{
        Node*create = new Node(k, v);
        create->left = nil;
        create->right = nil;
        Insert(create);
        num_pairs++;

    }
}

void Dictionary::begin(){
    if(root!=nil){
        current = findMin(root);
    }
}

void Dictionary::end(){
    if(root!=nil){
        current = findMax(root);
    }
}

 void Dictionary:: next(){
    if(current!=nil){
        Node*next = findNext(current);
        if(next!=nil){
            current = next;
        }
        else{
            current = nil;
        }

    }
 }

 valType& Dictionary::getValue(keyType k) const{
    Node*n = search(root, k);
    return n->val;
 }


void Dictionary:: prev(){
        if(current!=nil){
        Node*previous = findPrev(current);
        if(previous!=nil){
            current = previous;
        }
        else{
            current = nil;
        }

    }

}


bool Dictionary::contains(keyType k) const{
    Node*n = search(root, k);
    if(n!=nil){
        return true;
    }
    else{
        return false;
    }
}

    void Dictionary::postOrderDelete(Node* R){
        if(R!=nil){
            postOrderDelete(R->left);
            postOrderDelete(R->right);
            delete R;
        }
    }

void Dictionary::preOrderCopy(Node*R, Node*N){
    if(R!=nil){
        Node*n = new Node(R->key, R->val);
        n->parent = N;
        if(N==nil){
            root = n;
      }
      else if(n->key<N->key){
        N->left = n;
      }
      else{
        N->right = n;
      }

      num_pairs++;

      preOrderCopy(R->left, n);
      preOrderCopy(R->right, n);
    }

}

 std::string Dictionary::to_string() const{
    std::string final;
    inOrderString(final, root);
    return final;
 }

 std::string Dictionary::pre_string() const{
    std::string total;
    preOrderString(total, root);
    return total;
 }

 bool Dictionary::equals(const Dictionary& D) const{
    std:: string s;
    std:: string l;
    inOrderString(s, root);
    D.inOrderString(l, D.root);
    if(s==l){
        return true;
    }
    else{
        return false;
    }
 }


 std::ostream& operator<<( std::ostream& stream, Dictionary& D){
    return stream<<D.to_string();

 }

 bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
 }

   Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this!=&D){
        Dictionary temp(D);
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;

   }






