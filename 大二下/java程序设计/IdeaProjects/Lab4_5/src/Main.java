
public class Main {
    public static void main(String[] args) {
        for(TrafficLight a:TrafficLight.values()){
            System.out.println(a.name()+" RGB:"+a.red+","+a.green+","+a.blue);
        }
    }
}
enum TrafficLight{
    RED(255,0,0),YELLOW(255,255,0),GREEN(0,255,0);
    int red;
    int green;
    int blue;
    TrafficLight(int r,int g,int b){
        this.red=r;
        this.green=g;
        this.blue=b;
    }
}