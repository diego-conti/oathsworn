
template<typename T>
void print_csvline(ostream& os,T t) {
    os<<t<<endl;
}

template<typename T, typename... Args>
void print_csvline(ostream& os,T t, Args... args) {
    os<<t<<",";
    print_csvline(os,args...);
}
