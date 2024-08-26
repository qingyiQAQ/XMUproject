public class Main {
    public static void main(String[] args) {
        Object a = new Object();
        Object b = a;
        int c = 5;
        int d = 5;
        if(isEqualTo(a,b))System.out.println("yes!");
        else System.out.println("no!");
        if(isEqualTo(c,d))System.out.println("yes!");
        else System.out.println("no!");
    }
    public static <T> boolean isEqualTo(T a,T b){
        if(a.equals(b))return true;
        else return false;
    }
}