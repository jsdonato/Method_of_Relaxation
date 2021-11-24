#ifndef point_h
#define point_h

class Point{
public:
   Point() : x(0.0), y(0.0), v(0.0) {}
    
   Point(double x_n, double y_n, double v_n) : x(x_n), y(y_n), v(v_n) {}
    
   void set_V(double v_n){
      v = v_n;
   }
    
   double X(){
      return x;
   }
    
   double Y(){
      return y;
   }
    
   double V(){
      return v;
   }
private:
   double x;
   double y;
   double v;
};

#endif
