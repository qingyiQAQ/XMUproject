public class Main {
    public static void main(String[] args) throws Exception {
        try{
            someMethod();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
    public static void someMethod() throws Exception{
        try {
            someMethod2();
        }
        catch (Exception e) {
            throw e;
        }
    }
    public static void someMethod2() throws Exception{
        throw new Exception("一个异常");
    }
}