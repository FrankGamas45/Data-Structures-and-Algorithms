#include <iostream>
#include <fstream>
#include <sstream>
#include "Stress_ball.h"
#include "Collection.h"

template<typename Obj, typename F1, typename F2>
istream& operator>>(istream& is, Collection<Obj,F1,F2>& c)
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
void test_stress_balls(){
        Stress_ball stress_ball_1 = Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::large);
        Stress_ball stress_ball_2 = Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::large);
        Stress_ball stress_ball_3 = Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::small);
        Stress_ball stress_ball_4 = Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::medium);
        Collection<Stress_ball,Stress_ball_colors,Stress_ball_sizes> collection_1;
        Collection<Stress_ball,Stress_ball_colors,Stress_ball_sizes> collection_2(3);
        Collection<Stress_ball,Stress_ball_colors,Stress_ball_sizes> collection_3(5);
        Collection<Stress_ball,Stress_ball_colors,Stress_ball_sizes> collection_file(1);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_4);
        collection_1.insert_item(stress_ball_1);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::small));
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        Collection<Stress_ball,Stress_ball_colors,Stress_ball_sizes> collection_4 = collection_1;
        Collection<Stress_ball,Stress_ball_colors,Stress_ball_sizes> collection_5(move(collection_4));
        collection_1.insert_item(Stress_ball(Stress_ball_colors::green, Stress_ball_sizes::small));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::medium));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.insert_item(Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large));
        collection_2.remove_this_item(stress_ball_2);        
        collection_2.print_items();
        ifstream ifs("stress_ball2.data");
        ifs >> collection_file;
        collection_file.insert_item(stress_ball_3);
        collection_file.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_3);
        collection_2.insert_item(stress_ball_2);
        collection_2.insert_item(stress_ball_1);
        
        collection_file.print_items();
        collection_3 = make_union(collection_file,collection_2);
        if(collection_3.total_items() == (collection_file.total_items() + collection_2.total_items())){ 
                          sort_by_size(collection_2,Sort_choice::insertion_sort);                           
                          cout<<collection_3;
        }
}

