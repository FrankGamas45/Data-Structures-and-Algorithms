#ifndef COLLECTION_H
#define COLLECTION_H
#include <string>
#include <iostream>
#include "Stress_ball.h"

enum class Sort_choice{bubble_sort, insertion_sort, selection_sort};

class Empty_Collection{};
template<typename Obj, typename F1, typename F2>
class Collection{
    Obj* array;
    int size;
    int capacity;
    void resize();
public:
    Collection();
    Collection(int cap);
    Collection(const Collection& c);
    Collection& operator=(const Collection& c);
    ~Collection();
    Collection(Collection&& c);
    Collection& operator=(Collection&& c);
    void insert_item(const Obj& sb);
    bool contains(const Obj& sb) const;
    Obj remove_any_item();
    void remove_this_item(const Obj& sb);
    void make_empty();
    bool is_empty() const;
    int total_items() const;
    int total_items(F1 s) const;
    int total_items(F2 c) const;
    void print_items() const;
    Obj& operator[](int i);
    const Obj& operator[](int i) const;
};

template<typename Obj, typename F1, typename F2>
ostream& operator<<(ostream&, const Collection<Obj,F1,F2>& c);
template<typename Obj, typename F1, typename F2>
Collection<Obj,F1,F2> make_union(const Collection<Obj,F1,F2>& c1, const Collection<Obj,F1,F2>& c2);
template<typename Obj, typename F1, typename F2>
void swap(Collection<Obj,F1,F2>& c1, Collection<Obj,F1,F2>& c2);
template<typename Obj, typename F1, typename F2>
void sort_by_size(Collection<Obj,F1,F2>& c, Sort_choice sort);
template<typename Obj, typename F1, typename F2>
Collection<Obj,F1,F2>::Collection(): size(0), capacity(0), array(NULL){}
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1, F2>::Collection(int cap): size(0), capacity(cap), array(new Obj[cap]){}
template<typename Obj, typename F1, typename F2>
Collection<Obj, F1,F2>::Collection(const Collection& c): size(c.size), capacity(c.capacity), array(new Obj[c.capacity]){
    for(int i = 0; i < c.size; i++){
        array[i] = c.array[i];
    }
}

template<typename Obj, typename F1, typename F2>
Collection<Obj,F1,F2>& Collection<Obj,F1,F2>::operator=(const Collection& c){
    if(this != &c){
        make_empty();
        size = c.size;
        capacity = c.capacity;
        array = new Obj[capacity];
        for(int i = 0; i < c.size; i++){
            array[i] = c.array[i];
        }
    }
    return *this;
}

template<typename Obj, typename F1, typename F2>
Collection<Obj,F1,F2>::~Collection(){
    make_empty();
}
template<typename Obj, typename F1, typename F2>
Collection<Obj,F1,F2>::Collection(Collection&& c): size(c.size), capacity(c.capacity), array(c.array){
    c.array = NULL;
    c.size = 0;
    c.capacity = 0;
}
template<typename Obj, typename F1, typename F2>
Collection<Obj,F1,F2>& Collection<Obj,F1,F2>::operator=(Collection&& c){
    if(this != &c){
        make_empty();
        size = c.size;
        capacity = c.capacity;
        array = c.array;
        c.array = NULL;
        c.size = 0;
        c.capacity = 0;
    }
    return *this;
}

template<typename Obj, typename F1, typename F2>
void Collection<Obj,F1,F2>::resize(){
    if(capacity == 0) capacity = 1;
    capacity *= 2;
    Obj* temp = new Obj[capacity];
    for(int i = 0; i < size; i++){
        temp[i] = array[i];
    }
    delete array;
    array = temp;
}
template<typename Obj, typename F1, typename F2>
void Collection<Obj,F1,F2>::insert_item(const Obj& sb){
    if(size == capacity){
        resize();
    }
    array[size++] = sb;
}

template<typename Obj, typename F1, typename F2>
bool Collection<Obj,F1,F2>::contains(const Obj& sb) const{
    for(int i = 0; i < size; i++){
        if(array[i] == sb){
            return true;
        }
    }
    return false;
}
template<typename Obj, typename F1, typename F2>
Obj Collection<Obj,F1,F2>::remove_any_item(){
    if(is_empty()) throw Empty_Collection();
    int ri = rand()%size;
    Obj res= array[ri];
    remove_this_item(res);
    return res;
}

template<typename Obj, typename F1, typename F2>
void Collection<Obj,F1,F2>::remove_this_item(const Obj& sb){
    if(is_empty()) throw Empty_Collection();
    int ri = -1;
    for(int i = 0; i < size; i++){
        if(array[i] == sb){
            ri = i;
            break;
        }
    }
    if(ri == -1) return;
    for(int i = ri; i < size-1; i++){
        array[i] = array[i+1];
    }
    size--;
}
template<typename Obj, typename F1, typename F2>
void Collection<Obj,F1,F2>::make_empty(){
    if(array != NULL) delete[] array;
    size = 0;
    capacity = 0;
    array = NULL;
}
template<typename Obj, typename F1, typename F2>
bool Collection<Obj,F1,F2>::is_empty() const{
    return size == 0;
}
template<typename Obj, typename F1, typename F2>
int Collection<Obj,F1,F2>::total_items() const{
    return size;
}

template<typename Obj, typename F1, typename F2>
int Collection<Obj,F1,F2>::total_items(F2 s) const {
    int sum = 0;
    for(int i = 0; i < size; i++){
        if(array[i].get_size() == s){
            sum++;
        }
    }
    return sum;
}
template<typename Obj, typename F1, typename F2>
int Collection<Obj,F1,F2>::total_items(F1 c) const {
    int sum = 0;
    for(int i = 0; i < size; i++){
        if(array[i].get_color() == c){
            sum++;
        }
    }
    return sum;
}
template<typename Obj, typename F1, typename F2>
void Collection<Obj,F1,F2>::print_items() const{
    for(int i = 0; i < size; i++){
        cout << array[i] << endl;
    }
}
template<typename Obj, typename F1, typename F2>
Obj& Collection<Obj,F1,F2>::operator[](int i){
    return array[i];
}
template<typename Obj, typename F1, typename F2>
const Obj& Collection<Obj,F1,F2>::operator[](int i) const{
    return array[i];
}
template<typename Obj, typename F1, typename F2>
ostream& operator<<(ostream& os, const Collection<Obj,F1,F2>& c)
{
  for(int i = 0; i < c.total_items(); i++){
        os << c[i] << endl;
    }
  return os;
}

/*istream& operator>>(istream& is, Collection& c)
{
  Stress_ball_sizes size;
  Stress_ball_colors color;
  string size_str, color_str;
  bool fail = false;
  while (true) {
    is >> color_str >> size_str;
    if (!is) break;
    if (color_str == "red")
      color = Stress_ball_colors::red;
    else if (color_str == "blue")
      color = Stress_ball_colors::blue;
    else if (color_str == "green")
      color = Stress_ball_colors::green;
    else if (color_str == "yellow")
      color = Stress_ball_colors::yellow;
    else {
      fail = true;
      break;
    }
    if (size_str == "small")
      size = Stress_ball_sizes::small;
    else if (size_str == "medium")
      size = Stress_ball_sizes::medium;
    else if (size_str == "large")
      size = Stress_ball_sizes::large;
    else {
      fail = true;
      break;
    }
    c.insert_item(Stress_ball(color, size));
  }
  if (fail) {
    cout << ">>> Wrong Stress_ball input\n";
    cout << ">>> Collection is empty\n";
    c.make_empty();
  }
  return is;
}*/
template<typename Obj, typename F1, typename F2>
Collection<Obj,F1,F2> make_union(const Collection<Obj,F1,F2>& c1, const Collection<Obj,F1,F2>& c2)
{
  Collection<Obj,F1,F2> c3 = c1;
  for (int i = 0; i < c2.total_items(); i++)
    c3.insert_item(c2[i]);
  return c3;
}

template<typename Obj, typename F1, typename F2>
void swap(Collection<Obj,F1,F2>& c1, Collection<Obj,F1,F2>& c2)
{
  Collection<Obj,F1,F2> tmp = move(c1);
  c1 = move(c2);
  c2 = move(tmp);
}

// to use by sort functions
template<typename Obj, typename F1, typename F2>
void swap(Obj& sb1, Obj& sb2)
{
  Obj tmp = sb1;
  sb1 = sb2;
  sb2 = tmp;
}

// bubble sort
template<typename Obj, typename F1, typename F2>
void bubble_sort(Collection<Obj,F1,F2>& c)
{
  int n = c.total_items();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n-i-1; j++)
      if (c[j].get_size() > c[j+1].get_size())
	swap(c[j], c[j+1]);
  }
}
template<typename Obj, typename F1, typename F2>
void insertion_sort(Collection<Obj,F1,F2>& c){
    Collection<Obj,F1,F2> small, med, large;
    for(int i = 0; i < c.total_items(); i++){
        switch(c[i].get_size()){
            case F2::small: small.insert_item(c[i]); break;
            case F2::medium: med.insert_item(c[i]); break;
            case F2::large: large.insert_item(c[i]); break;
        }
    }
    c.make_empty();
    c = make_union(small,make_union(med,large));
}


template<typename Obj, typename F1, typename F2>
void selection_sort(Collection<Obj,F1,F2>& c){
    int smallest;
    for(int i = 0; i < c.total_items(); i++){
        smallest = i;
        for(int j = i; j < c.total_items(); j++){
            if(c[j].get_size() < c[smallest].get_size()){
                smallest = j;
            }
        }
        swap(c[i],c[smallest]);
    }
}
template<typename Obj, typename F1, typename F2>
void sort_by_size(Collection<Obj,F1,F2>& c, Sort_choice sort)
{
  switch (sort) {
  case Sort_choice::bubble_sort:
    bubble_sort(c);
    break;
  case Sort_choice::insertion_sort:
    insertion_sort(c);
    break;
  case Sort_choice::selection_sort:
    selection_sort(c);
    break;
  }
}
#endif