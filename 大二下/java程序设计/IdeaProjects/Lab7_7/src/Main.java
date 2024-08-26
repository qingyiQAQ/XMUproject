import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Employee employee = new Employee(new SalariedCompensationModel(1000));
        System.out.println("SalariedCompensation员工收入为："+employee.earnings());
        employee = new Employee(new HourlyCompensationModel(25,40));
        System.out.println("HourlyCompensation员工收入为："+employee.earnings());
        employee = new Employee(new CommissionCompensationModel(2000,0.5));
        System.out.println("CommissionCompensation员工收入为："+employee.earnings());
        employee = new Employee(new BasePlusCommissionCompensationModel(2000,0.2,600));
        System.out.println("BasePlusCommissionCompensation员工收入为："+employee.earnings());
        double a,b,c;
        Scanner scanner=new Scanner(System.in);
        System.out.println("输入SalariedCompensation员工的weeklySalary：");
        a = scanner.nextDouble();
        employee = new Employee(new SalariedCompensationModel(a));
        System.out.println("SalariedCompensation员工收入为："+employee.earnings());
        System.out.println("输入HourlyCompensation员工的wage和hours：");
        a = scanner.nextDouble();
        b = scanner.nextDouble();
        employee = new Employee(new HourlyCompensationModel(a,b));
        System.out.println("HourlyCompensation员工收入为："+employee.earnings());
        System.out.println("输入CommissionCompensation员工的grossSales和commissionRate：");
        a = scanner.nextDouble();
        b = scanner.nextDouble();
        employee = new Employee(new CommissionCompensationModel(a,b));
        System.out.println("CommissionCompensation员工收入为："+employee.earnings());
        System.out.println("输入BasePlusCommissionCompensation员工的grossSales,commissionRate和baseSalary：");
        a = scanner.nextDouble();
        b = scanner.nextDouble();
        c = scanner.nextDouble();
        employee = new Employee(new BasePlusCommissionCompensationModel(a,b,c));
        System.out.println("BasePlusCommissionCompensation员工收入为："+employee.earnings());
    }
}
class Employee{
    private final CompensationModel compensationModel;
    public Employee(CompensationModel compensationModel) {
        this.compensationModel = compensationModel;
    }
    public double earnings() {
        return compensationModel.earnings();
    }
}
interface CompensationModel{
    default double earnings(){
        return 0;
    }
}
class SalariedCompensationModel implements CompensationModel{
    double weeklySalary;
    public SalariedCompensationModel(double weeklySalary){
        this.weeklySalary = weeklySalary;
    }
    @Override
    public double earnings() {
        return weeklySalary;
    }
}
class HourlyCompensationModel implements CompensationModel{
    double wage;
    double hours;
    public HourlyCompensationModel(double wage,double hours){
        this.wage=wage;
        this.hours=hours;
    }
    @Override
    public double earnings() {
        if(hours>40)return wage*40+wage*3*(hours-40);
        return wage*hours;
    }
}
class CommissionCompensationModel implements CompensationModel{
    double grossSales;
    double commissionRate;
    public CommissionCompensationModel(double grossSales,double commissionRate){
        this.commissionRate=commissionRate;
        this.grossSales=grossSales;
    }
    @Override
    public double earnings() {
        return grossSales*commissionRate;
    }
}
class BasePlusCommissionCompensationModel implements CompensationModel{
    double grossSales;
    double commissionRate;
    double baseSalary;
    public BasePlusCommissionCompensationModel(double grossSales,double commissionRate,double baseSalary){
        this.baseSalary=baseSalary;
        this.commissionRate=commissionRate;
        this.grossSales=grossSales;
    }
    @Override
    public double earnings() {
        return baseSalary + grossSales*commissionRate;
    }
}