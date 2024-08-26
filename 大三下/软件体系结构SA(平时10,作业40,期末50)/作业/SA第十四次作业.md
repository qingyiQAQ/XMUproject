# SA第十四次作业

1、试用Bridge模式完成下列事情：饮料的杯子有大、中、小；行为有：加奶，加糖，啥都不加。

定义Drink抽象类，代表饮料的类型，为Bridge模式中的行为部分，含一个方法pourDrink()，代表饮料的添加行为。

```java
public abstract class Drink {
    public abstract void pourDrink();
}
```

定义Cup抽象类，代表饮料的杯子大小，为Bridge模式中的抽象部分，含有一个Drink变量，将抽象部分和实现部分连接起来，让客户端可以灵活地选择不同大小的杯子以及不同的行为。

```java
public abstract class Cup {
    Drink drink;

    public Cup(Drink drink) {
        this.drink = drink;
    }
    
    public abstract void pourDrink();
}
```

定义Drink的实现类AddMilk、AddSugar、NoAddition，实现Drink中的具体行为pourdrink()，分别为加奶、加糖，啥也不加。

```java
public class AddMilk extends Drink{
    public void pourDrink() {
        System.out.println("加奶");
    }
}
```

```java
public class AddSugar extends Drink{
    public void pourDrink() {
        System.out.println("加糖");
    }
}
```

```java
public class NoAddition extends Drink {
    public void pourDrink() {
        System.out.println("啥也不加");
    }
}
```

定义Cup的实现类BigCup、MediumCup、SmallCup，实现Cup中的行为pourDrink()，在这个方法中既继承父类中Drink变量的行为，又定义自己的行为。分别为大杯、中杯、小杯。

```java
public class BigCup extends Cup {
    
    public BigCup(Drink drink) {
        super(drink);
    }
    
    public void pourDrink() {
        System.out.print("这是大杯");
        drink.pourDrink();
    }
}
```

```java
public class MediumCup extends Cup {

    public MediumCup(Drink drink) {
        super(drink);
    }

    public void pourDrink() {
        System.out.print("这是中杯");
        drink.pourDrink();
    }
}
```

```java
public class SmallCup extends Cup{
    public SmallCup(Drink drink) {
        super(drink);
    }

    public void pourDrink() {
        System.out.print("这是小杯");
        drink.pourDrink();
    }
}
```

Main方法

```java
public class Main {
    public static void main(String[] args) {
        BigCup bigCup = new BigCup(new AddMilk());
        bigCup.pourDrink();
        SmallCup smallCup = new SmallCup(new AddSugar());
        smallCup.pourDrink();
        MediumCup mediumCup = new MediumCup(new NoAddition());
        mediumCup.pourDrink();
    }
}
```

运行结果

![image-20240508201809523](C:\Users\CC507\AppData\Roaming\Typora\typora-user-images\image-20240508201809523.png)