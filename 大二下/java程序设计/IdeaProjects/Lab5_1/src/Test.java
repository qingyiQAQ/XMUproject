import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scanner =new Scanner(System.in);
        Student s[] = new Student[4];
        s[0]=new Undergraduate_Student("00001","张三","101");
        s[1]=new Undergraduate_Student("00002","李四","102");
        s[2]=new Postgraduate_Student("00003","王五","103","导师1");
        s[3]=new Postgraduate_Student("00004","赵六","104","导师2");
        Course c[] = new Course[4];
        c[0]=new Required_Course("01","语文");
        c[1]=new Required_Course("02","数学");
        c[2]=new Elective_Course("03","物理");
        c[3]=new Elective_Course("04","化学");
        while(true)
        {
            int n;
            System.out.println("-----------------------------------------------------");
            System.out.println("1.输出所有学生。");
            System.out.println("2.输出所有课程。");
            System.out.println("3.为所有学生自动选择必修课。");
            System.out.println("4.秘书手动选课。");
            System.out.println("5.输出每个学生的选课信息。");
            System.out.println("请输入要执行的程序：");
            n=scanner.nextInt();
            switch(n){
                case 1:print_student(s,4);break;
                case 2:print_course(c,4);break;
                case 3:select_auto(s,c,4,2);break;
                case 4:select_self(s,c);break;
                case 5:print_student_course(s,4);break;
            }
        }
    }
    static void select_auto(Student a[],Course b[],int student_num,int course_num){
        System.out.println("正在进行自动选课...");
        for(int i=0;i<student_num;i++){
            for(int j=0;j<course_num;j++){
                a[i].s_course[a[i].course_num+j]=b[j];a[i].getCourse(a[i].getCourse_num())=b[j];
                System.out.println("学生"+a[i].s_name+"已选课程"+b[j].c_name);
            }
            a[i].course_num+=course_num;
        }
        System.out.println("自动选课完毕");
    }//自动选课方法
    static void select_self(Student s[],Course c[]){
        Scanner scanner =new Scanner(System.in);
        System.out.println("请选择学生为之选课：");
        print_student(s,4);
        int a=scanner.nextInt();
        System.out.println("请为学生"+s[a-1].s_name+"选择课程：");
        print_course(c,4);
        int b=scanner.nextInt();
        select_course(s[a-1],c[b-1]);
        System.out.println("选择完毕");
    }//手动选课方法
    static void select_course(Student a,Course b){
        a.s_course[a.course_num]=b;
        a.course_num++;
    }//选课方法
    static void print_student_course(Student s[],int student_num){
        for(int i=0;i<student_num;i++){
            System.out.print("学生"+s[i].s_name+"的课程有：");
            for(int j=0;j<s[i].course_num;j++){
                System.out.print(s[i].s_course[j].c_name+" ");
            }
            System.out.print("\n");
        }
    }//输出所有学生的所有课程
    static void print_student(Student s[],int student_num){
        for(int i=0;i<student_num;i++){
            System.out.println((i+1)+"."+s[i].s_name);
        }
    }//输出所有学生
    static void print_course(Course c[],int course_num){
        for(int i=0;i<course_num;i++){
            System.out.println((i+1)+"."+c[i].c_name);
        }
    }//输出所有课程
}
class Student {
    private String s_num;
    private String s_name;
    private String s_class;
    private int course_num=0;//已选课程数目
    private Course s_course[]=new Course[100];
    Student(String num,String name,String class_) {
        this.s_num=num;
        this.s_name=name;
        this.s_class=class_;
    }
    String getS_num(){
        return this.s_num;
    }
    String getS_name(){
        return this.s_name;
    }
    String getS_class(){
        return this.s_class;
    }
    int getCourse_num(){
        return this.course_num;
    }
    Course getCourse(int i){
        return this.s_course[i];
    }
}
class Postgraduate_Student extends Student{
    private String s_teacher;

    Postgraduate_Student(String num, String name, String class_,String teacher) {
        super(num, name, class_);
        this.s_teacher=teacher;
    }
    String getS_teacher(){
        return this.s_teacher;
    }
}//研究生子类
class Undergraduate_Student extends Student{

    Undergraduate_Student(String num, String name, String class_) {
        super(num, name, class_);
    }
}//本科生子类
class Course {
    private String c_num;
    private String c_name;
    private String c_credit;
    Course(String num,String name){
      this.c_name=name;
      this.c_num=num;
    }
}
class Grade{
    private Student student;
    private Course course;
    private int grade=-1;
}
class Required_Course extends Course{

    Required_Course(String num, String name) {
        super(num, name);
    }
}//必修课子类
class Elective_Course extends Course{

    Elective_Course(String num, String name) {
        super(num, name);
    }
}//选修课子类