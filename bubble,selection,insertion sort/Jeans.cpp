#include "Jeans.h"

Jeans::Jeans(){
    color = Jeans_colors(rand()%4);
    size = Jeans_sizes(rand()%4);
}

Jeans::Jeans(Jeans_colors c, Jeans_sizes s): color(c), size(s) {}

Jeans_colors Jeans::get_color() const{
    return color;
}

Jeans_sizes Jeans::get_size() const{
    return size;
}

bool Jeans::operator==(const Jeans& sb){
    return color == sb.color && size == sb.size;
}

ostream& operator<<(ostream& o, const Jeans& sb){
    o << "(";
    Jeans_colors color = sb.get_color();
    Jeans_sizes size = sb.get_size();

    switch(color){
        case Jeans_colors::white: o << "red"; break;
        case Jeans_colors::black: o << "black"; break;
        case Jeans_colors::blue: o << "blue"; break;
        case Jeans_colors::grey: o << "grey"; break;
    }

    o << ", ";

    switch(size){
        case Jeans_sizes::small: o << "small"; break;
        case Jeans_sizes::medium: o << "medium"; break;
        case Jeans_sizes::large: o << "large"; break;
        case Jeans_sizes::xlarge: o << "xlarge"; break;
    }

    o << ")";
    return o;
}