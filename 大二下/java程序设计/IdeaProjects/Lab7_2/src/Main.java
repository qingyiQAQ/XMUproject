public class Main {
    public static void main(String[] args) {
        try {
            SomeClass obj = new SomeClass();
        } catch (Exception e) {
            System.out.println("捕获到异常：" + e.getMessage());
        }
    }
}
class SomeClass {
    SomeClass() throws Exception {
        throw new Exception("构造方法失败");
    }
}