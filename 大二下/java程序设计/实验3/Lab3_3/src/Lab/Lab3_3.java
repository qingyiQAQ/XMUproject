package Lab;

import java.util.Scanner;
import java.util.Random;

public class Lab3_3 {
	public static void main(String[] args) {
		Test test=new Test();
		test.input();
	}
}//主函数调用test类输入输出
class Lesson {
	String l_num;
	String l_name;
}//定义课程类，课程基本信息包括：课程编号、课程名称
class Student {
	String s_num;
	String s_name;
	String s_class;
	String s_telephone;
	//定义学生类，学生基本属性包括：学号、姓名、班级、电话，电话可以为空
	public void input_student(String num,String name,String class_) {
		s_num=num;
		s_name=name;
		s_class=class_;
		s_telephone="";
	}
	public void input_Student(String num,String name,String class_,String telephone) {
		s_num=num;
		s_name=name;
		s_class=class_;
		s_telephone=telephone;
	}
	//设计重载函数使电话可为空
}
class Lesson_Student{
	Student student;
	Lesson lesson;
	int Grade;
}//定义成绩类，用于联系不同学生不同课程的成绩
class Test {
	void input() {
		Student a=new Student();
		Student b=new Student();
		//创建2个学生类对象
		Lesson c=new Lesson();
		Lesson d=new Lesson();
		//创建2个课程类对象
		System.out.println("请输入第一个学生信息（若电话为空则输入/)");
		input_student(a);
		print_student(a);
		System.out.println("请输入第二个学生信息（若电话为空则输入/)");
		input_student(b);
		print_student(b);
		//提示用户输入两个学生信息
		System.out.println("请输入第一个课程信息");
		input_lesson(c);
		System.out.println("请输入第二个课程信息");
		input_lesson(d);
		//提示用户输入两个课程信息
		Random rand=new Random();
		Lesson_Student n1=new Lesson_Student();
		n1.student=a;
		n1.lesson=c;
		n1.Grade=rand.nextInt(100)+1;
		//进行一次选课（第一个学生选择了第一门课程）并随机生成成绩
		Lesson_Student n2=new Lesson_Student();
		n2.student=b;
		n2.lesson=d;
		n2.Grade=rand.nextInt(100)+1;
		//进行一次选课（第二个学生选择了第二门课程）并随机生成成绩
		print_grade(n1);
		print_grade(n2);
		//输出成绩
	}
	void input_student(Student a) {
		Scanner scanner = new Scanner(System.in);
		System.out.print("请输入学生学号：");
		a.s_num=scanner.next();
		System.out.print("请输入学生姓名：");
		a.s_name=scanner.next();
		System.out.print("请输入学生班级：");
		a.s_class=scanner.next();
		System.out.print("请输入学生电话：");
		a.s_telephone=scanner.next();
		if(a.s_telephone.equals("/"))a.input_student(a.s_num, a.s_name, a.s_class);
		else a.input_Student(a.s_num, a.s_name, a.s_class, a.s_telephone);
	}//用于输入学生信息的方法
	void input_lesson(Lesson a) {
		Scanner scanner = new Scanner(System.in);
		System.out.print("请输入课程编号：");
		a.l_num=scanner.next();
		System.out.print("请输入课程名称：");
		a.l_name=scanner.next();
	}//用于输入课程信息的方法
	void print_student(Student a) {
		System.out.println("学号："+a.s_num+" 姓名："+a.s_name+" 班级："+a.s_class+" 电话："+a.s_telephone);
	}//用于输出学生信息的方法
	void print_lesson(Lesson a) {
		System.out.println("编号："+a.l_num+" 名称："+a.l_name);
	}//用于输出课程信息的方法
	void print_grade(Lesson_Student n) {
		System.out.println("学生"+n.student.s_name+"的课程"+n.lesson.l_num+"成绩为："+n.Grade);
	}//用于输出成绩1的方法
}
