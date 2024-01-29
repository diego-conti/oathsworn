
class Series {
    ex series;
    ex indet;
    int order;
    ex truncated;
    static ex truncated_series(ex series, ex indet, int order)  {   
        return series_to_poly(GiNaC::series(series,indet,order));        
    }
public:
    Series()=default;
    Series(const Series&)=default;
    Series& operator=(const Series& o)=default;
    Series(ex series, ex indet, int order=2): series{series}, indet{indet}, order{order}, truncated{truncated_series(series,indet,order)} {
    }
    ex truncated_to_order(int order) {
        if (order>this->order) {
            this->order=order; 
            return truncated=truncated_series(series, indet,order);
        }
        ex result=truncated;
        for (int n = order;n<this->order;++n)
            result-=pow(indet,n)*truncated.coeff(indet,n);
        return result;
    }
};
