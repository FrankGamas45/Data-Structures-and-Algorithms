#include "Collection.h"
#include "Stress_ball.h"

Collection::Collection(): size(0), capacity(0), array(NULL){}
Collection::Collection(int cap): size(0), capacity(cap), array(new Stress_ball[cap]){}
Collection::Collection(const Collection& c): size(c.size), capacity(c.capacity), array(new Stress_ball[c.capacity]){
    for(int i = 0; i < c.size; i++){
        array[i] = c.array[i];
    }
}
Collection& Collection::operator=(const Collection& c){
    if(this != &c){
        make_empty();
        size = c.size;
        capacity = c.capacity;
        array = new Stress_ball[capacity];
        for(int i = 0; i < c.size; i++){
            array[i] = c.array[i];
        }
    }
    return *this;
}
Collection::~Collection(){
    make_empty();
}
Collection::Collection(Collection&& c): size(c.size), capacity(c.capacity), array(c.array){
    c.array = NULL;
    c.size = 0;
    c.capacity = 0;
}
Collection& Collection::operator=(Collection&& c){
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

void Collection::resize(){
    if(capacity == 0) capacity = 1;
    capacity *= 2;
    Stress_ball* temp = new Stress_ball[capacity];
    for(int i = 0; i < size; i++){
        temp[i] = array[i];
    }
    delete array;
    array = temp;
}
void Collection::insert_item(const Stress_ball& sb){
    if(size == capacity){
        resize();
    }
    array[size++] = sb;
}
bool Collection::contains(const Stress_ball& sb) const{
    for(int i = 0; i < size; i++){
        if(array[i] == sb){
            return true;
        }
    }
    return false;
}
Stress_ball Collection::remove_any_item(){
    if(is_empty()) throw Empty_Collection();
    int ri = rand()%size;
    Stress_ball res = array[ri];
    remove_this_item(res);
    return res;
}
void Collection::remove_this_item(const Stress_ball& sb){
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
void Collection::make_empty(){
    if(array != NULL) delete[] array;
    size = 0;
    capacity = 0;
    array = NULL;
}
bool Collection::is_empty() const{
    return size == 0;
}
int Collection::total_items() const{
    return size;
}
int Collection::total_items(Stress_ball_sizes s) const {
    int sum = 0;
    for(int i = 0; i < size; i++){
        if(array[i].get_size() == s){
            sum++;
        }
    }
    return sum;
}
int Collection::total_items(Stress_ball_colors c) const {
    int sum = 0;
    for(int i = 0; i < size; i++){
        if(array[i].get_color() == c){
            sum++;
        }
    }
    return sum;
}
void Collection::print_items() const{
    for(int i = 0; i < size; i++){
        cout << array[i] << endl;
    }
}
Stress_ball& Collection::operator[](int i){
    return array[i];
}
const Stress_ball& Collection::operator[](int i) const{
    return array[i];
}

ostream& operator<<(ostream& os, const Collection& c)
{
  for(int i = 0; i < c.total_items(); i++){
        os << c[i] << endl;
    }
  return os;
}

istream& operator>>(istream& is, Collection& c)
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
}

Collection make_union(const Collection& c1, const Collection& c2)
{
  Collection c3 = c1;
  for (int i = 0; i < c2.total_items(); i++)
    c3.insert_item(c2[i]);
  return c3;
}

void swap(Collection& c1, Collection& c2)
{
  Collection tmp = move(c1);
  c1 = move(c2);
  c2 = move(tmp);
}

// to use by sort functions
void swap(Stress_ball& sb1, Stress_ball& sb2)
{
  Stress_ball tmp = sb1;
  sb1 = sb2;
  sb2 = tmp;
}

// bubble sort
void bubble_sort(Collection& c)
{
  int n = c.total_items();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n-i-1; j++)
      if (c[j].get_size() > c[j+1].get_size())
	swap(c[j], c[j+1]);
  }
}

void insertion_sort(Collection& c){
    Collection small, med, large;
    for(int i = 0; i < c.total_items(); i++){
        switch(c[i].get_size()){
            case Stress_ball_sizes::small: small.insert_item(c[i]); break;
            case Stress_ball_sizes::medium: med.insert_item(c[i]); break;
            case Stress_ball_sizes::large: large.insert_item(c[i]); break;
        }
    }
    c.make_empty();
    c = make_union(small,make_union(med,large));
}

void selection_sort(Collection& c){
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

void sort_by_size(Collection& c, Sort_choice sort)
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