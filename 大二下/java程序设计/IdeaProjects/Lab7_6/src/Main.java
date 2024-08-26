public class Main {
    public static void main(String[] args) {

    }
}
class Pair <F,S> {
    public F first;
    public S second;
    public void setFirst(F first){
        this.first=first;
    }
    public void setSecond(S second){
        this.second=second;
    }
    public F getFirst(){
        return this.first;
    }
    public S getSecond(){
        return this.second;
    }
}