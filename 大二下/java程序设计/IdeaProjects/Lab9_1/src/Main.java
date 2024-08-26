import java.util.*;
import java.util.regex.Pattern;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String article = "";
        System.out.println("请输入文章(输入q结束):");
        while (true){
            String a = scanner.nextLine();
            if(!a.equals("q")) article=article+a;
            else break;
        }//获得输入
        print_all_words(article);
        print_sentence_contain(article,"the");
    }
    static void print_all_words(String article){
        Pattern PATTERN = Pattern.compile("[^a-zA-Z0-9]+");//一个或多个除字母或数字以外所有符号的pattern
        String[] words= PATTERN.matcher(article).replaceAll(" ").toLowerCase().split("\\s+");//去掉标点符号转化为空格转化为小写转化为字符串数组
        Set<String> nonredundant_words = new HashSet<>();//建立哈希表用于删除重复单词
        nonredundant_words.addAll(Arrays.asList(words));
        System.out.print("出现了以下单词:");
        int count=0;
        for (String s : nonredundant_words) {
            System.out.print(s+" ");
            count++;
            if(count%10==0)System.out.print("\n");
        }
        System.out.println("共"+count+"个单词");
        System.out.print("\n");
    }
    static  void print_sentence_contain(String s,String word){
        Pattern PATTERN = Pattern.compile("[^a-zA-Z0-9]+");
        String[] sentences = s.split("\\.");
        System.out.println("包含"+word+"的句子有:");
        int count=0;
        for(String sentence:sentences){
            String[] words = PATTERN.matcher(sentence).replaceAll(" ").toLowerCase().split("\\s+");
            List<String> list = Arrays.asList(words);
            if(list.contains(word)){
                System.out.println(sentence);
                count++;
            }
        }
        System.out.println("共"+count+"个句子");
    }
}