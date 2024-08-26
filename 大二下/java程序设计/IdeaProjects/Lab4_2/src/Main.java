
import java.lang.Number;
import java.lang.Comparable;
public class Main {
    public static void main(String[] args) {
        Rational a=new Rational();
        a.Rational(1,2);
        Rational b=new Rational();
        b.Rational(2,3);
        Rational c=new Rational();
        c.denominator=b.denominator;
        c.numerator=b.numerator;
        System.out.println(c.add(a).toString());
        c.denominator=b.denominator;
        c.numerator=b.numerator;
        System.out.println(c.subtract(a).toString());
        c.denominator=b.denominator;
        c.numerator=b.numerator;
        System.out.println(c.multiply(a).toString());
        c.denominator=b.denominator;
        c.numerator=b.numerator;
        System.out.println(c.divide(a).toString());
    }
}
class Rational extends Number implements Comparable<Rational>{
    long numerator;//分子
    long denominator;//分母
    Rational Rational(){
        this.denominator=1;
        this.numerator=0;
        return this;
    }//创建一个分子为0分母为1的有理数
    Rational Rational(long numerator,long denominator){
        if (denominator == 0) {
            throw new IllegalArgumentException("Denominator cannot be zero.");
        }
        else {
            long gcd= gcd(denominator,numerator);
            this.denominator = denominator/gcd;
            this.numerator = numerator/gcd;
            return this;
        }
    }//利用指定的分子分母创建一个有理数（分母不为0）
    long getNumerator(Rational rational){

        return rational.numerator;
    }//返回该有理数的分子
    long getDenominator(Rational rational){

        return rational.denominator;
    }//返回该有理数的分母
    Rational add(Rational other){
        long new_num=numerator*other.denominator+denominator*other.numerator;
        long new_den=denominator*other.denominator;
        return Rational(new_num,new_den);
    }//返回该有理数与另一个有理数的和
    Rational subtract(Rational other){
        long new_num=numerator*other.denominator-denominator*other.numerator;
        long new_den=denominator*other.denominator;
        return Rational(new_num,new_den);
    }//返回该有理数与另一个有理数的差
    Rational multiply(Rational other) {
        long new_num = numerator * other.numerator;
        long new_den = denominator * other.denominator;
        return Rational(new_num, new_den);
    }//返回该有理数与另一个有理数的积
    Rational divide(Rational other) {
        if (other.numerator == 0) {
            throw new ArithmeticException("Divisor cannot be zero.");
        }
        long new_num = numerator * other.denominator;
        long new_den = denominator * other.numerator;
        return Rational(new_num, new_den);
    }//返回该有理数与另一个有理数的商
    public String toString(){
        if(denominator==1)return numerator+"";
        return numerator+"/"+denominator;
    }
    @Override
    public int intValue() {
        return (int) doubleValue();
    }
    @Override
    public long longValue() {
        return (long) doubleValue();
    }
    @Override
    public float floatValue() {
        return (float) doubleValue();
    }
    @Override
    public double doubleValue() {
        return (double) numerator / denominator;
    }
    @Override
    public int compareTo(Rational other) {
        long diff = numerator * other.denominator - denominator * other.numerator;
        if (diff == 0) {
            return 0;
        } else if (diff > 0) {
            return 1;
        } else {
            return -1;
        }
    }
    //重写相关函数
    private static long gcd(long a,long b)
    {
        return (a==0?b:gcd(b%a,a));
    }//取最大公因数的方法，方便将分式简化
}

