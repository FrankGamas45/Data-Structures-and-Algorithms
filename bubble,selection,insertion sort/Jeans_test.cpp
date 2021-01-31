#include <iostream>
#include <fstream>
#include <sstream>
#include "Jeans.h"
#include "Collection.h"

template<typename Obj, typename F1, typename F2>
istream& operator>>(istream& is, Collection<Obj,F1,F2>& c)
{
  Jeans_sizes size;
  Jeans_colors color;
  string size_str, color_str;
  bool fail = false;
  while (true) {
    is >> color_str >> size_str;
    if (!is) break;
    if (color_str == "white")
      color = Jeans_colors::white;
    else if (color_str == "blue")
      color = Jeans_colors::blue;
    else if (color_str == "black")
      color = Jeans_colors::black;
    else if (color_str == "grey")
      color = Jeans_colors::grey;
    else {
      fail = true;
      break;
    }
    if (size_str == "small")
      size = Jeans_sizes::small;
    else if (size_str == "medium")
      size = Jeans_sizes::medium;
    else if (size_str == "large")
      size = Jeans_sizes::large;
    else if (size_str == "xlarge")
      size = Jeans_sizes::xlarge;
    else {
      fail = true;
      break;
    }
    c.insert_item(Jeans(color, size));
  }
  if (fail) {
    cout << ">>> Wrong Stress_ball input\n";
    cout << ">>> Collection is empty\n";
    c.make_empty();
  }
  return is;
}
void test_jeans(){
        Jeans jeans_1 = Jeans(Jeans_colors::grey, Jeans_sizes::small);
        Jeans jeans_2 = Jeans(Jeans_colors::grey, Jeans_sizes::large);
        Jeans jeans_3 = Jeans(Jeans_colors::blue, Jeans_sizes::large);
        Jeans jeans_4 = Jeans(Jeans_colors::black, Jeans_sizes::medium);
        Collection<Jeans,Jeans_colors,Jeans_sizes> collection_0;
        Collection<Jeans,Jeans_colors,Jeans_sizes> collection_1;
        Collection<Jeans,Jeans_colors,Jeans_sizes> collection_2(3);
        Collection<Jeans,Jeans_colors,Jeans_sizes> collection_3(5);
        Collection<Jeans,Jeans_colors,Jeans_sizes> collection_file(1);
        collection_0.insert_item(jeans_1);
        collection_0.make_empty();
        collection_1.insert_item(jeans_1);
        collection_2.insert_item(jeans_2);
        
        collection_2.print_items();
        collection_2.insert_item(Jeans(Jeans_colors::blue, Jeans_sizes::small));
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        Collection<Jeans,Jeans_colors,Jeans_sizes> collection_copy(collection_1);
        collection_1.insert_item(Jeans(Jeans_colors::black, Jeans_sizes::small));
        Collection<Jeans,Jeans_colors,Jeans_sizes> collection_7 = move(collection_1);
        collection_2.insert_item(Jeans(Jeans_colors::blue, Jeans_sizes::medium));
        collection_2.insert_item(Jeans(Jeans_colors::grey, Jeans_sizes::large));
        collection_2.insert_item(Jeans(Jeans_colors::grey, Jeans_sizes::large));
        collection_2.remove_this_item(jeans_2);
        
        collection_2.print_items();
        collection_copy.make_empty();
        if(collection_2.is_empty()){
            collection_2.insert_item(Jeans(Jeans_colors::black, Jeans_sizes::small));
        }
        ifstream ifs("jeans2.data");
        ifs >> collection_file;
        collection_file.insert_item(jeans_3);
        collection_file.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_3);
        collection_2.insert_item(jeans_2);
        collection_2.insert_item(jeans_1);
        
        collection_file.print_items();
      
                    swap(collection_file,collection_2);
                    collection_3 = make_union(collection_file,collection_2);                
                     if((collection_3.total_items() - collection_2.total_items()) == collection_file.total_items()){
                          sort_by_size(collection_2,Sort_choice::selection_sort);
                          cout<<collection_3;
                     }
}
