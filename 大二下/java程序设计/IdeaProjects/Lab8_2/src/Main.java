import java.util.*;
import java.util.regex.Pattern;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个句子:");
        String sentence = scanner.nextLine();//获得用户输入
        Pattern PATTERN = Pattern.compile("[\\p{Punct}\\s]+");//一个或多个空格或标点符号的pattern
        String[] words= PATTERN.matcher(sentence).replaceAll(" ").toLowerCase().split("\\s+");//去掉标点符号转化为空格转化为小写转化为字符串数组
        Map<String, Integer> wordCount = new HashMap<>();//建立哈希表用于储存每个单词出现次数
        for (String word : words) {
            if (wordCount.containsKey(word)) {
                wordCount.put(word, wordCount.get(word) + 1);
            } else {
                wordCount.put(word, 1);
            }
        }
        for (String key : wordCount.keySet()) {
            System.out.println("单词:" + key + ",出现次数:" + wordCount.get(key));
        }
    }
}